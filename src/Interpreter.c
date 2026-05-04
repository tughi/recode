#include "Interpreter.h"
#include "Panic.h"
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    IR_Value *key;
    int64_t value;
} Binding;

typedef struct {
    Binding *items;
    size_t size;
    size_t capacity;
} Frame;

typedef struct {
    int64_t *cells;
    size_t size;
    size_t capacity;
} Heap;

static int64_t heap_alloc(Heap *heap) {
    if (heap->size == heap->capacity) {
        heap->capacity = heap->capacity == 0 ? 16 : heap->capacity * 2;
        heap->cells = realloc(heap->cells, heap->capacity * sizeof(int64_t));
    }
    heap->cells[heap->size] = 0;
    return (int64_t)heap->size++;
}

typedef struct {
    IR_Module *module;
    Heap heap;
    Frame globals;
} Interpreter;

static void print_runtime_error(Interpreter *interpreter, Source_Location location, const char *format, ...) {
    fprintf(stderr, "%.*s:%zu:%zu: ", STRING(interpreter->module->source.path), location.line, location.column);
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    fprintf(stderr, "\n");
}

#define runtime_error(interpreter, location, ...)                \
    do {                                                         \
        print_runtime_error(interpreter, location, __VA_ARGS__); \
        panic();                                                 \
    } while (0)

static void frame_bind(Frame *frame, IR_Value *key, int64_t value) {
    if (frame->size == frame->capacity) {
        frame->capacity = frame->capacity == 0 ? 4 : frame->capacity * 2;
        frame->items = realloc(frame->items, frame->capacity * sizeof(Binding));
    }
    frame->items[frame->size++] = (Binding){.key = key, .value = value};
}

static int64_t frame_lookup(Interpreter *interpreter, Frame *frame, IR_Value *key, Source_Location location) {
    for (size_t i = frame->size; i > 0; i--) {
        if (frame->items[i - 1].key == key) {
            return frame->items[i - 1].value;
        }
    }
    for (size_t i = interpreter->globals.size; i > 0; i--) {
        if (interpreter->globals.items[i - 1].key == key) {
            return interpreter->globals.items[i - 1].value;
        }
    }
    runtime_error(interpreter, location, "Unbound value '%.*s'", STRING(key->name));
}

static IR_Function *find_function(Interpreter *interpreter, String name) {
    for (size_t i = 0; i < interpreter->module->functions.size; i++) {
        if (string_equals(interpreter->module->functions.items[i]->name, name)) {
            return interpreter->module->functions.items[i];
        }
    }
    return NULL;
}

typedef enum {
    STEP_NEXT,
    STEP_JUMP,
    STEP_RETURN,
} Step_Kind;

typedef struct {
    Step_Kind kind;
    union {
        size_t jump_label;
        int64_t return_value;
    };
} Step;

static int64_t run_function(Interpreter *interpreter, IR_Function *function, int64_t *args, size_t argc, Source_Location call_location);

static int64_t mask_to_type(int64_t value, IR_Type *type) {
    switch (type->kind) {
    case IR_TYPE__I8:
        return (int8_t)value;
    case IR_TYPE__I16:
        return (int16_t)value;
    case IR_TYPE__U8:
        return (uint8_t)value;
    case IR_TYPE__U16:
        return (uint16_t)value;
    case IR_TYPE__U32:
        return (uint32_t)value;
    case IR_TYPE__U64:
    case IR_TYPE__USIZE:
        return (int64_t)(uint64_t)value;
    default:
        return value;
    }
}

static bool is_unsigned_type(IR_Type *type) {
    switch (type->kind) {
    case IR_TYPE__U8:
    case IR_TYPE__U16:
    case IR_TYPE__U32:
    case IR_TYPE__U64:
    case IR_TYPE__USIZE:
        return true;
    default:
        return false;
    }
}

static Step execute_instruction(Interpreter *interpreter, IR_Instruction *instruction, Frame *frame, size_t previous_label) {
    switch (instruction->kind) {
    case IR_INSTRUCTION__ADD: {
        int64_t left = frame_lookup(interpreter, frame, instruction->arguments.items[0], instruction->location);
        int64_t right = frame_lookup(interpreter, frame, instruction->arguments.items[1], instruction->location);
        frame_bind(frame, &instruction->result, mask_to_type(left + right, instruction->result.type));
        return (Step){.kind = STEP_NEXT};
    }
    case IR_INSTRUCTION__ADDRESS: {
        IR_Value *target = instruction->arguments.items[0];
        if (target->kind == IR_VALUE__FUNCTION) {
            IR_Function *function = find_function(interpreter, target->name);
            if (function == NULL) {
                runtime_error(interpreter, instruction->location, "Unknown function '%.*s'", STRING(target->name));
            }
            frame_bind(frame, &instruction->result, (int64_t)(uintptr_t)function);
            return (Step){.kind = STEP_NEXT};
        }
        frame_bind(frame, &instruction->result, frame_lookup(interpreter, frame, target, instruction->location));
        return (Step){.kind = STEP_NEXT};
    }
    case IR_INSTRUCTION__ALLOC:
        frame_bind(frame, &instruction->result, heap_alloc(&interpreter->heap));
        return (Step){.kind = STEP_NEXT};
    case IR_INSTRUCTION__BR: {
        int64_t condition = frame_lookup(interpreter, frame, instruction->arguments.items[0], instruction->location);
        size_t target = condition != 0 ? instruction->br_instruction.true_label : instruction->br_instruction.false_label;
        return (Step){.kind = STEP_JUMP, .jump_label = target};
    }
    case IR_INSTRUCTION__CALL: {
        IR_Value *callee_value = instruction->arguments.items[0];
        IR_Function *callee;
        if (callee_value->kind == IR_VALUE__FUNCTION) {
            callee = find_function(interpreter, callee_value->name);
            if (callee == NULL) {
                runtime_error(interpreter, instruction->location, "Unknown function '%.*s'", STRING(callee_value->name));
            }
        } else {
            int64_t function_pointer = frame_lookup(interpreter, frame, callee_value, instruction->location);
            callee = (IR_Function *)(uintptr_t)function_pointer;
        }
        size_t call_arguments_count = instruction->arguments.size - 1;
        int64_t *call_arguments = call_arguments_count == 0 ? NULL : malloc(call_arguments_count * sizeof(int64_t));
        for (size_t i = 0; i < call_arguments_count; i++) {
            call_arguments[i] = frame_lookup(interpreter, frame, instruction->arguments.items[i + 1], instruction->location);
        }
        int64_t result = run_function(interpreter, callee, call_arguments, call_arguments_count, instruction->location);
        free(call_arguments);
        if (instruction->result.type != ir_type_void()) {
            frame_bind(frame, &instruction->result, result);
        }
        return (Step){.kind = STEP_NEXT};
    }
    case IR_INSTRUCTION__CMP_EQ: {
        int64_t left = frame_lookup(interpreter, frame, instruction->arguments.items[0], instruction->location);
        int64_t right = frame_lookup(interpreter, frame, instruction->arguments.items[1], instruction->location);
        frame_bind(frame, &instruction->result, left == right);
        return (Step){.kind = STEP_NEXT};
    }
    case IR_INSTRUCTION__CMP_GE: {
        int64_t left = frame_lookup(interpreter, frame, instruction->arguments.items[0], instruction->location);
        int64_t right = frame_lookup(interpreter, frame, instruction->arguments.items[1], instruction->location);
        bool result = is_unsigned_type(instruction->arguments.items[0]->type) ? (uint64_t)left >= (uint64_t)right : left >= right;
        frame_bind(frame, &instruction->result, result);
        return (Step){.kind = STEP_NEXT};
    }
    case IR_INSTRUCTION__CMP_GT: {
        int64_t left = frame_lookup(interpreter, frame, instruction->arguments.items[0], instruction->location);
        int64_t right = frame_lookup(interpreter, frame, instruction->arguments.items[1], instruction->location);
        bool result = is_unsigned_type(instruction->arguments.items[0]->type) ? (uint64_t)left > (uint64_t)right : left > right;
        frame_bind(frame, &instruction->result, result);
        return (Step){.kind = STEP_NEXT};
    }
    case IR_INSTRUCTION__CMP_LE: {
        int64_t left = frame_lookup(interpreter, frame, instruction->arguments.items[0], instruction->location);
        int64_t right = frame_lookup(interpreter, frame, instruction->arguments.items[1], instruction->location);
        bool result = is_unsigned_type(instruction->arguments.items[0]->type) ? (uint64_t)left <= (uint64_t)right : left <= right;
        frame_bind(frame, &instruction->result, result);
        return (Step){.kind = STEP_NEXT};
    }
    case IR_INSTRUCTION__CMP_LT: {
        int64_t left = frame_lookup(interpreter, frame, instruction->arguments.items[0], instruction->location);
        int64_t right = frame_lookup(interpreter, frame, instruction->arguments.items[1], instruction->location);
        bool result = is_unsigned_type(instruction->arguments.items[0]->type) ? (uint64_t)left < (uint64_t)right : left < right;
        frame_bind(frame, &instruction->result, result);
        return (Step){.kind = STEP_NEXT};
    }
    case IR_INSTRUCTION__CMP_NE: {
        int64_t left = frame_lookup(interpreter, frame, instruction->arguments.items[0], instruction->location);
        int64_t right = frame_lookup(interpreter, frame, instruction->arguments.items[1], instruction->location);
        frame_bind(frame, &instruction->result, left != right);
        return (Step){.kind = STEP_NEXT};
    }
    case IR_INSTRUCTION__CONST:
        frame_bind(frame, &instruction->result, instruction->const_instruction.value);
        return (Step){.kind = STEP_NEXT};
    case IR_INSTRUCTION__DIV: {
        int64_t left = frame_lookup(interpreter, frame, instruction->arguments.items[0], instruction->location);
        int64_t right = frame_lookup(interpreter, frame, instruction->arguments.items[1], instruction->location);
        if (right == 0) {
            runtime_error(interpreter, instruction->location, "Division by zero");
        }
        int64_t div_result = is_unsigned_type(instruction->result.type) ? (int64_t)((uint64_t)left / (uint64_t)right) : left / right;
        frame_bind(frame, &instruction->result, mask_to_type(div_result, instruction->result.type));
        return (Step){.kind = STEP_NEXT};
    }
    case IR_INSTRUCTION__JMP:
        return (Step){.kind = STEP_JUMP, .jump_label = instruction->jmp_instruction.label};
    case IR_INSTRUCTION__LOAD: {
        int64_t address = frame_lookup(interpreter, frame, instruction->arguments.items[0], instruction->location);
        if (address < 0 || (size_t)address >= interpreter->heap.size) {
            runtime_error(interpreter, instruction->location, "Load from invalid address %lld", (long long)address);
        }
        frame_bind(frame, &instruction->result, interpreter->heap.cells[address]);
        return (Step){.kind = STEP_NEXT};
    }
    case IR_INSTRUCTION__MOD: {
        int64_t left = frame_lookup(interpreter, frame, instruction->arguments.items[0], instruction->location);
        int64_t right = frame_lookup(interpreter, frame, instruction->arguments.items[1], instruction->location);
        if (right == 0) {
            runtime_error(interpreter, instruction->location, "Modulo by zero");
        }
        int64_t mod_result = is_unsigned_type(instruction->result.type) ? (int64_t)((uint64_t)left % (uint64_t)right) : left % right;
        frame_bind(frame, &instruction->result, mask_to_type(mod_result, instruction->result.type));
        return (Step){.kind = STEP_NEXT};
    }
    case IR_INSTRUCTION__MUL: {
        int64_t left = frame_lookup(interpreter, frame, instruction->arguments.items[0], instruction->location);
        int64_t right = frame_lookup(interpreter, frame, instruction->arguments.items[1], instruction->location);
        frame_bind(frame, &instruction->result, mask_to_type(left * right, instruction->result.type));
        return (Step){.kind = STEP_NEXT};
    }
    case IR_INSTRUCTION__NEG:
        frame_bind(frame, &instruction->result, mask_to_type(-frame_lookup(interpreter, frame, instruction->arguments.items[0], instruction->location), instruction->result.type));
        return (Step){.kind = STEP_NEXT};
    case IR_INSTRUCTION__NOT:
        frame_bind(frame, &instruction->result, !frame_lookup(interpreter, frame, instruction->arguments.items[0], instruction->location));
        return (Step){.kind = STEP_NEXT};
    case IR_INSTRUCTION__PHI:
        for (size_t i = 0; i < instruction->arguments.size; i++) {
            if (instruction->phi_instruction.labels[i] == previous_label) {
                int64_t value = frame_lookup(interpreter, frame, instruction->arguments.items[i], instruction->location);
                frame_bind(frame, &instruction->result, value);
                return (Step){.kind = STEP_NEXT};
            }
        }
        runtime_error(interpreter, instruction->location, "Phi '%.*s' has no entry for predecessor @%zu", STRING(instruction->result.name), previous_label);
    case IR_INSTRUCTION__PLACEHOLDER:
        runtime_error(interpreter, instruction->location, "Unresolved placeholder '%.*s'", STRING(instruction->result.name));
    case IR_INSTRUCTION__RET: {
        int64_t return_value = 0;
        if (instruction->arguments.size > 0) {
            return_value = frame_lookup(interpreter, frame, instruction->arguments.items[0], instruction->location);
        }
        return (Step){.kind = STEP_RETURN, .return_value = return_value};
    }
    case IR_INSTRUCTION__STORE: {
        int64_t address = frame_lookup(interpreter, frame, instruction->arguments.items[0], instruction->location);
        int64_t value = frame_lookup(interpreter, frame, instruction->arguments.items[1], instruction->location);
        if (address < 0 || (size_t)address >= interpreter->heap.size) {
            runtime_error(interpreter, instruction->location, "Store to invalid address %lld", (long long)address);
        }
        interpreter->heap.cells[address] = value;
        return (Step){.kind = STEP_NEXT};
    }
    case IR_INSTRUCTION__SUB: {
        int64_t left = frame_lookup(interpreter, frame, instruction->arguments.items[0], instruction->location);
        int64_t right = frame_lookup(interpreter, frame, instruction->arguments.items[1], instruction->location);
        frame_bind(frame, &instruction->result, mask_to_type(left - right, instruction->result.type));
        return (Step){.kind = STEP_NEXT};
    }
    }
    runtime_error(interpreter, instruction->location, "Unknown instruction kind %d", instruction->kind);
}

static IR_Block *find_block(IR_Function *function, size_t label) {
    for (size_t i = 0; i < function->blocks.size; i++) {
        if (function->blocks.items[i]->label == label) {
            return function->blocks.items[i];
        }
    }
    return NULL;
}

static int64_t call_external(Interpreter *interpreter, IR_Function *function, int64_t *args, size_t argc, Source_Location call_location) {
    (void)argc;
    if (string_equals_cstr(function->name, "$exit")) {
        exit((int)args[0]);
    }
    if (string_equals_cstr(function->name, "$fputc")) {
        return (int64_t)fputc((int)args[0], (FILE *)(uintptr_t)args[1]);
    }
    runtime_error(interpreter, call_location, "Unknown external function '%.*s'", STRING(function->name));
}

static int64_t run_function(Interpreter *interpreter, IR_Function *function, int64_t *args, size_t argc, Source_Location call_location) {
    if (argc != function->parameters.size) {
        runtime_error(interpreter, call_location, "'%.*s' expects %zu argument(s), got %zu", STRING(function->name), function->parameters.size, argc);
    }
    if (function->is_external) {
        return call_external(interpreter, function, args, argc, call_location);
    }
    if (function->blocks.size == 0) {
        runtime_error(interpreter, function->location, "'%.*s' has no blocks", STRING(function->name));
    }

    Frame frame = {0};
    for (size_t i = 0; i < argc; i++) {
        frame_bind(&frame, function->parameters.items[i], args[i]);
    }

    IR_Block *block = function->blocks.items[0];
    size_t previous_label = SIZE_MAX;
    while (true) {
        bool terminated = false;
        for (size_t i = 0; i < block->instructions.size; i++) {
            IR_Instruction *instruction = block->instructions.items[i];
            Step step = execute_instruction(interpreter, instruction, &frame, previous_label);
            if (step.kind == STEP_NEXT) {
                continue;
            }
            if (step.kind == STEP_JUMP) {
                IR_Block *target = find_block(function, step.jump_label);
                if (target == NULL) {
                    runtime_error(interpreter, instruction->location, "'%.*s' has no block @%zu", STRING(function->name), step.jump_label);
                }
                previous_label = block->label;
                block = target;
                terminated = true;
                break;
            }
            // STEP_RETURN
            free(frame.items);
            return step.return_value;
        }
        if (!terminated) {
            runtime_error(interpreter, block->location, "'%.*s' block @%zu fell off without a terminator", STRING(function->name), block->label);
        }
    }
}

int64_t interpret(IR_Module *module) {
    String main_name = string_from("$main");
    Interpreter interpreter = {.module = module};
    IR_Function *main_function = find_function(&interpreter, main_name);
    if (main_function == NULL) {
        fprintf(stderr, "%.*s: No $main function\n", STRING(module->source.path));
        panic();
    }
    if (main_function->return_type->kind != IR_TYPE__I32 && main_function->return_type->kind != IR_TYPE__VOID) {
        fprintf(stderr, "%.*s:%zu:%zu: Unsupported return type", STRING(module->source.path), main_function->location.line, main_function->location.column);
        ir_type_fprintf(stderr, main_function->return_type);
        fputc('\n', stderr);
        panic();
    }
    for (size_t i = 0; i < module->global_variables.size; i++) {
        IR_Global_Variable *global_variable = module->global_variables.items[i];
        int64_t address = heap_alloc(&interpreter.heap);
        if (string_equals_cstr(global_variable->name, "$optind")) {
            interpreter.heap.cells[address] = 1;
        } else if (string_equals_cstr(global_variable->name, "$stdout")) {
            interpreter.heap.cells[address] = (int64_t)(uintptr_t)stdout;
        } else if (string_equals_cstr(global_variable->name, "$stderr")) {
            interpreter.heap.cells[address] = (int64_t)(uintptr_t)stderr;
        } else if (string_equals_cstr(global_variable->name, "$stdin")) {
            interpreter.heap.cells[address] = (int64_t)(uintptr_t)stdin;
        }
        frame_bind(&interpreter.globals, &global_variable->value, address);
    }
    int64_t result = run_function(&interpreter, main_function, NULL, 0, main_function->location);
    free(interpreter.globals.items);
    free(interpreter.heap.cells);
    return main_function->return_type->kind == IR_TYPE__I32 ? result : 0;
}
