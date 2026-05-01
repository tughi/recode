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

static void print_runtime_error(IR_Module *module, Source_Location location, const char *format, ...) {
    fprintf(stderr, "%.*s:%zu:%zu: ", STRING(module->source.path), location.line, location.column);
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    fprintf(stderr, "\n");
}

#define runtime_error(module, location, ...)                \
    do {                                                    \
        print_runtime_error(module, location, __VA_ARGS__); \
        panic();                                            \
    } while (0)

static void frame_bind(Frame *frame, IR_Value *key, int64_t value) {
    if (frame->size == frame->capacity) {
        frame->capacity = frame->capacity == 0 ? 4 : frame->capacity * 2;
        frame->items = realloc(frame->items, frame->capacity * sizeof(Binding));
    }
    frame->items[frame->size++] = (Binding){.key = key, .value = value};
}

static int64_t frame_lookup(Frame *frame, IR_Value *key, IR_Module *module, Source_Location location) {
    for (size_t i = frame->size; i > 0; i--) {
        if (frame->items[i - 1].key == key) {
            return frame->items[i - 1].value;
        }
    }
    runtime_error(module, location, "Unbound value '%.*s'", STRING(key->name));
}

static IR_Function *find_function(IR_Module *module, String name) {
    for (size_t i = 0; i < module->functions.size; i++) {
        if (string_equals(module->functions.items[i].name, name)) {
            return &module->functions.items[i];
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

static int64_t run_function(IR_Module *module, IR_Function *function, int64_t *args, size_t argc, Source_Location call_location, Heap *heap);

static Step execute_instruction(IR_Module *module, IR_Function *function, IR_Instruction *instruction, Frame *frame, size_t previous_label, Heap *heap) {
    switch (instruction->kind) {
    case IR_INSTRUCTION__ADD: {
        int64_t left = frame_lookup(frame, instruction->arguments.items[0], module, instruction->location);
        int64_t right = frame_lookup(frame, instruction->arguments.items[1], module, instruction->location);
        frame_bind(frame, &instruction->result, left + right);
        return (Step){.kind = STEP_NEXT};
    }
    case IR_INSTRUCTION__ALLOC:
        frame_bind(frame, &instruction->result, heap_alloc(heap));
        return (Step){.kind = STEP_NEXT};
    case IR_INSTRUCTION__BR: {
        int64_t condition = frame_lookup(frame, instruction->arguments.items[0], module, instruction->location);
        size_t target = condition != 0 ? instruction->br_instruction.true_label : instruction->br_instruction.false_label;
        return (Step){.kind = STEP_JUMP, .jump_label = target};
    }
    case IR_INSTRUCTION__CALL: {
        IR_Value *callee_ref = instruction->arguments.items[0];
        IR_Function *callee = find_function(module, callee_ref->name);
        if (callee == NULL) {
            runtime_error(module, instruction->location, "Unknown function '%.*s'", STRING(callee_ref->name));
        }
        size_t argc = instruction->arguments.size - 1;
        int64_t *args = argc == 0 ? NULL : malloc(argc * sizeof(int64_t));
        for (size_t i = 0; i < argc; i++) {
            args[i] = frame_lookup(frame, instruction->arguments.items[i + 1], module, instruction->location);
        }
        int64_t result = run_function(module, callee, args, argc, instruction->location, heap);
        free(args);
        frame_bind(frame, &instruction->result, result);
        return (Step){.kind = STEP_NEXT};
    }
    case IR_INSTRUCTION__CMP_EQ: {
        int64_t left = frame_lookup(frame, instruction->arguments.items[0], module, instruction->location);
        int64_t right = frame_lookup(frame, instruction->arguments.items[1], module, instruction->location);
        frame_bind(frame, &instruction->result, left == right);
        return (Step){.kind = STEP_NEXT};
    }
    case IR_INSTRUCTION__CMP_GE: {
        int64_t left = frame_lookup(frame, instruction->arguments.items[0], module, instruction->location);
        int64_t right = frame_lookup(frame, instruction->arguments.items[1], module, instruction->location);
        frame_bind(frame, &instruction->result, left >= right);
        return (Step){.kind = STEP_NEXT};
    }
    case IR_INSTRUCTION__CMP_GT: {
        int64_t left = frame_lookup(frame, instruction->arguments.items[0], module, instruction->location);
        int64_t right = frame_lookup(frame, instruction->arguments.items[1], module, instruction->location);
        frame_bind(frame, &instruction->result, left > right);
        return (Step){.kind = STEP_NEXT};
    }
    case IR_INSTRUCTION__CMP_LE: {
        int64_t left = frame_lookup(frame, instruction->arguments.items[0], module, instruction->location);
        int64_t right = frame_lookup(frame, instruction->arguments.items[1], module, instruction->location);
        frame_bind(frame, &instruction->result, left <= right);
        return (Step){.kind = STEP_NEXT};
    }
    case IR_INSTRUCTION__CMP_LT: {
        int64_t left = frame_lookup(frame, instruction->arguments.items[0], module, instruction->location);
        int64_t right = frame_lookup(frame, instruction->arguments.items[1], module, instruction->location);
        frame_bind(frame, &instruction->result, left < right);
        return (Step){.kind = STEP_NEXT};
    }
    case IR_INSTRUCTION__CMP_NE: {
        int64_t left = frame_lookup(frame, instruction->arguments.items[0], module, instruction->location);
        int64_t right = frame_lookup(frame, instruction->arguments.items[1], module, instruction->location);
        frame_bind(frame, &instruction->result, left != right);
        return (Step){.kind = STEP_NEXT};
    }
    case IR_INSTRUCTION__CONST:
        frame_bind(frame, &instruction->result, instruction->const_instruction.value);
        return (Step){.kind = STEP_NEXT};
    case IR_INSTRUCTION__DIV: {
        int64_t left = frame_lookup(frame, instruction->arguments.items[0], module, instruction->location);
        int64_t right = frame_lookup(frame, instruction->arguments.items[1], module, instruction->location);
        if (right == 0) {
            runtime_error(module, instruction->location, "Division by zero");
        }
        frame_bind(frame, &instruction->result, left / right);
        return (Step){.kind = STEP_NEXT};
    }
    case IR_INSTRUCTION__JMP:
        return (Step){.kind = STEP_JUMP, .jump_label = instruction->jmp_instruction.label};
    case IR_INSTRUCTION__LOAD: {
        int64_t address = frame_lookup(frame, instruction->arguments.items[0], module, instruction->location);
        if (address < 0 || (size_t)address >= heap->size) {
            runtime_error(module, instruction->location, "Load from invalid address %lld", (long long)address);
        }
        frame_bind(frame, &instruction->result, heap->cells[address]);
        return (Step){.kind = STEP_NEXT};
    }
    case IR_INSTRUCTION__MOD: {
        int64_t left = frame_lookup(frame, instruction->arguments.items[0], module, instruction->location);
        int64_t right = frame_lookup(frame, instruction->arguments.items[1], module, instruction->location);
        if (right == 0) {
            runtime_error(module, instruction->location, "Modulo by zero");
        }
        frame_bind(frame, &instruction->result, left % right);
        return (Step){.kind = STEP_NEXT};
    }
    case IR_INSTRUCTION__MUL: {
        int64_t left = frame_lookup(frame, instruction->arguments.items[0], module, instruction->location);
        int64_t right = frame_lookup(frame, instruction->arguments.items[1], module, instruction->location);
        frame_bind(frame, &instruction->result, left * right);
        return (Step){.kind = STEP_NEXT};
    }
    case IR_INSTRUCTION__NEG:
        frame_bind(frame, &instruction->result, -frame_lookup(frame, instruction->arguments.items[0], module, instruction->location));
        return (Step){.kind = STEP_NEXT};
    case IR_INSTRUCTION__PHI:
        for (size_t i = 0; i < instruction->arguments.size; i++) {
            if (instruction->phi_instruction.labels[i] == previous_label) {
                int64_t value = frame_lookup(frame, instruction->arguments.items[i], module, instruction->location);
                frame_bind(frame, &instruction->result, value);
                return (Step){.kind = STEP_NEXT};
            }
        }
        runtime_error(module, instruction->location, "Phi '%.*s' has no entry for predecessor @%zu", STRING(instruction->result.name), previous_label);
    case IR_INSTRUCTION__PLACEHOLDER:
        runtime_error(module, instruction->location, "Unresolved placeholder '%.*s'", STRING(instruction->result.name));
    case IR_INSTRUCTION__RET: {
        IR_Value *returned = instruction->arguments.items[0];
        if (!string_equals(returned->type.name, function->return_type.name)) {
            runtime_error(module, instruction->location, "'%.*s' returns '%.*s' but ret yields '%.*s' of type '%.*s'", STRING(function->name), STRING(function->return_type.name), STRING(returned->name), STRING(returned->type.name));
        }
        return (Step){.kind = STEP_RETURN, .return_value = frame_lookup(frame, returned, module, instruction->location)};
    }
    case IR_INSTRUCTION__STORE: {
        int64_t address = frame_lookup(frame, instruction->arguments.items[0], module, instruction->location);
        int64_t value = frame_lookup(frame, instruction->arguments.items[1], module, instruction->location);
        if (address < 0 || (size_t)address >= heap->size) {
            runtime_error(module, instruction->location, "Store to invalid address %lld", (long long)address);
        }
        heap->cells[address] = value;
        return (Step){.kind = STEP_NEXT};
    }
    case IR_INSTRUCTION__SUB: {
        int64_t left = frame_lookup(frame, instruction->arguments.items[0], module, instruction->location);
        int64_t right = frame_lookup(frame, instruction->arguments.items[1], module, instruction->location);
        frame_bind(frame, &instruction->result, left - right);
        return (Step){.kind = STEP_NEXT};
    }
    }
    runtime_error(module, instruction->location, "Unknown instruction kind %d", instruction->kind);
}

static IR_Block *find_block(IR_Function *function, size_t label) {
    for (size_t i = 0; i < function->blocks.size; i++) {
        if (function->blocks.items[i]->label == label) {
            return function->blocks.items[i];
        }
    }
    return NULL;
}

static int64_t run_function(IR_Module *module, IR_Function *function, int64_t *args, size_t argc, Source_Location call_location, Heap *heap) {
    if (argc != function->parameters.size) {
        runtime_error(module, call_location, "'%.*s' expects %zu argument(s), got %zu", STRING(function->name), function->parameters.size, argc);
    }
    if (function->blocks.size == 0) {
        runtime_error(module, function->location, "'%.*s' has no blocks", STRING(function->name));
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
            Step step = execute_instruction(module, function, instruction, &frame, previous_label, heap);
            if (step.kind == STEP_NEXT) {
                continue;
            }
            if (step.kind == STEP_JUMP) {
                IR_Block *target = find_block(function, step.jump_label);
                if (target == NULL) {
                    runtime_error(module, instruction->location, "'%.*s' has no block @%zu", STRING(function->name), step.jump_label);
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
            runtime_error(module, block->location, "'%.*s' block @%zu fell off without a terminator", STRING(function->name), block->label);
        }
    }
}

int64_t interpret(IR_Module *module) {
    String main_name = string_from("$main");
    IR_Function *main_function = find_function(module, main_name);
    if (main_function == NULL) {
        fprintf(stderr, "%.*s: No $main function\n", STRING(module->source.path));
        panic();
    }
    if (!string_equals_cstr(main_function->return_type.name, "i32")) {
        runtime_error(module, main_function->location, "$main must return i32, got '%.*s'", STRING(main_function->return_type.name));
    }
    Heap heap = {0};
    int64_t result = run_function(module, main_function, NULL, 0, main_function->location, &heap);
    free(heap.cells);
    return result;
}
