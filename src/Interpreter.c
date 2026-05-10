#include "Interpreter.h"
#include "Panic.h"
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    IR_Module *module;
    uint8_t *globals_data;
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

static uint8_t *value_address(Interpreter *interpreter, uint8_t *frame_data, IR_Value *value) {
    uint8_t *base = value->name.content[0] == '$' ? interpreter->globals_data : frame_data;
    return base + value->slot.offset;
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
    size_t jump_label;
} Step;

static void run_function(Interpreter *interpreter, IR_Function *function, uint8_t **argument_addresses, size_t argument_count, uint8_t *return_address, Source_Location call_location);

static Step execute_add_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data) {
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    switch (instruction->result.type->kind) {
    case IR_TYPE__I8:
        *(int8_t *)result_address = *(int8_t *)left_address + *(int8_t *)right_address;
        break;
    case IR_TYPE__I16:
        *(int16_t *)result_address = *(int16_t *)left_address + *(int16_t *)right_address;
        break;
    case IR_TYPE__I32:
        *(int32_t *)result_address = *(int32_t *)left_address + *(int32_t *)right_address;
        break;
    case IR_TYPE__I64:
    case IR_TYPE__ISIZE:
        *(int64_t *)result_address = *(int64_t *)left_address + *(int64_t *)right_address;
        break;
    case IR_TYPE__U8:
        *(uint8_t *)result_address = *(uint8_t *)left_address + *(uint8_t *)right_address;
        break;
    case IR_TYPE__U16:
        *(uint16_t *)result_address = *(uint16_t *)left_address + *(uint16_t *)right_address;
        break;
    case IR_TYPE__U32:
        *(uint32_t *)result_address = *(uint32_t *)left_address + *(uint32_t *)right_address;
        break;
    case IR_TYPE__U64:
    case IR_TYPE__USIZE:
        *(uint64_t *)result_address = *(uint64_t *)left_address + *(uint64_t *)right_address;
        break;
    default:
        break;
    }
    return (Step){.kind = STEP_NEXT};
}

static Step execute_alloc_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data) {
    uint8_t *payload_address = frame_data + instruction->alloc_instruction.payload_slot.offset;
    memset(payload_address, 0, instruction->alloc_instruction.payload_slot.size);
    *(uint8_t **)value_address(interpreter, frame_data, &instruction->result) = payload_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_br_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data) {
    bool condition = *(bool *)value_address(interpreter, frame_data, instruction->arguments.items[0]);
    size_t target = condition ? instruction->br_instruction.true_label : instruction->br_instruction.false_label;
    return (Step){.kind = STEP_JUMP, .jump_label = target};
}

static Step execute_call_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data) {
    IR_Value *callee_value = instruction->arguments.items[0];
    IR_Function *callee = *(IR_Function **)value_address(interpreter, frame_data, callee_value);
    size_t argument_count = instruction->arguments.size - 1;
    uint8_t **argument_addresses = argument_count == 0 ? NULL : malloc(argument_count * sizeof(uint8_t *));
    for (size_t i = 0; i < argument_count; i++) {
        argument_addresses[i] = value_address(interpreter, frame_data, instruction->arguments.items[i + 1]);
    }
    uint8_t *return_address = NULL;
    if (instruction->result.type != NULL && instruction->result.type != ir_type_void()) {
        return_address = value_address(interpreter, frame_data, &instruction->result);
    }
    run_function(interpreter, callee, argument_addresses, argument_count, return_address, instruction->location);
    free(argument_addresses);
    return (Step){.kind = STEP_NEXT};
}

static Step execute_cast_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data) {
    IR_Value *source_value = instruction->arguments.items[0];
    uint8_t *source_address = value_address(interpreter, frame_data, source_value);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    if ((source_value->type->kind == IR_TYPE__PTR || source_value->type->kind == IR_TYPE__MULTI_PTR) && (instruction->result.type->kind == IR_TYPE__PTR || instruction->result.type->kind == IR_TYPE__MULTI_PTR)) {
        *(uint8_t **)result_address = *(uint8_t **)source_address;
        return (Step){.kind = STEP_NEXT};
    }
    int64_t widened_data = 0;
    switch (source_value->type->kind) {
    case IR_TYPE__I8:
        widened_data = (int64_t)*(int8_t *)source_address;
        break;
    case IR_TYPE__I16:
        widened_data = (int64_t)*(int16_t *)source_address;
        break;
    case IR_TYPE__I32:
        widened_data = (int64_t)*(int32_t *)source_address;
        break;
    case IR_TYPE__I64:
    case IR_TYPE__ISIZE:
        widened_data = *(int64_t *)source_address;
        break;
    case IR_TYPE__U8:
        widened_data = (int64_t)*(uint8_t *)source_address;
        break;
    case IR_TYPE__U16:
        widened_data = (int64_t)*(uint16_t *)source_address;
        break;
    case IR_TYPE__U32:
        widened_data = (int64_t)*(uint32_t *)source_address;
        break;
    case IR_TYPE__U64:
    case IR_TYPE__USIZE:
        widened_data = (int64_t)*(uint64_t *)source_address;
        break;
    default:
        break;
    }
    switch (instruction->result.type->kind) {
    case IR_TYPE__I8:
        *(int8_t *)result_address = (int8_t)widened_data;
        break;
    case IR_TYPE__I16:
        *(int16_t *)result_address = (int16_t)widened_data;
        break;
    case IR_TYPE__I32:
        *(int32_t *)result_address = (int32_t)widened_data;
        break;
    case IR_TYPE__I64:
    case IR_TYPE__ISIZE:
        *(int64_t *)result_address = widened_data;
        break;
    case IR_TYPE__U8:
        *(uint8_t *)result_address = (uint8_t)widened_data;
        break;
    case IR_TYPE__U16:
        *(uint16_t *)result_address = (uint16_t)widened_data;
        break;
    case IR_TYPE__U32:
        *(uint32_t *)result_address = (uint32_t)widened_data;
        break;
    case IR_TYPE__U64:
    case IR_TYPE__USIZE:
        *(uint64_t *)result_address = (uint64_t)widened_data;
        break;
    default:
        break;
    }
    return (Step){.kind = STEP_NEXT};
}

static Step execute_cmp_eq_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data) {
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    bool result = false;
    switch (instruction->arguments.items[0]->type->kind) {
    case IR_TYPE__BOOL:
        result = *(bool *)left_address == *(bool *)right_address;
        break;
    case IR_TYPE__I8:
    case IR_TYPE__U8:
        result = *(uint8_t *)left_address == *(uint8_t *)right_address;
        break;
    case IR_TYPE__I16:
    case IR_TYPE__U16:
        result = *(uint16_t *)left_address == *(uint16_t *)right_address;
        break;
    case IR_TYPE__I32:
    case IR_TYPE__U32:
        result = *(uint32_t *)left_address == *(uint32_t *)right_address;
        break;
    case IR_TYPE__I64:
    case IR_TYPE__ISIZE:
    case IR_TYPE__U64:
    case IR_TYPE__USIZE:
    case IR_TYPE__MULTI_PTR:
    case IR_TYPE__PTR:
    case IR_TYPE__PROC:
        result = *(uint64_t *)left_address == *(uint64_t *)right_address;
        break;
    default:
        break;
    }
    *(bool *)result_address = result;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_cmp_ge_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data) {
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    bool result = false;
    switch (instruction->arguments.items[0]->type->kind) {
    case IR_TYPE__BOOL:
        result = *(bool *)left_address >= *(bool *)right_address;
        break;
    case IR_TYPE__I8:
        result = *(int8_t *)left_address >= *(int8_t *)right_address;
        break;
    case IR_TYPE__I16:
        result = *(int16_t *)left_address >= *(int16_t *)right_address;
        break;
    case IR_TYPE__I32:
        result = *(int32_t *)left_address >= *(int32_t *)right_address;
        break;
    case IR_TYPE__I64:
    case IR_TYPE__ISIZE:
        result = *(int64_t *)left_address >= *(int64_t *)right_address;
        break;
    case IR_TYPE__U8:
        result = *(uint8_t *)left_address >= *(uint8_t *)right_address;
        break;
    case IR_TYPE__U16:
        result = *(uint16_t *)left_address >= *(uint16_t *)right_address;
        break;
    case IR_TYPE__U32:
        result = *(uint32_t *)left_address >= *(uint32_t *)right_address;
        break;
    case IR_TYPE__U64:
    case IR_TYPE__USIZE:
        result = *(uint64_t *)left_address >= *(uint64_t *)right_address;
        break;
    default:
        break;
    }
    *(bool *)result_address = result;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_cmp_gt_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data) {
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    bool result = false;
    switch (instruction->arguments.items[0]->type->kind) {
    case IR_TYPE__BOOL:
        result = *(bool *)left_address > *(bool *)right_address;
        break;
    case IR_TYPE__I8:
        result = *(int8_t *)left_address > *(int8_t *)right_address;
        break;
    case IR_TYPE__I16:
        result = *(int16_t *)left_address > *(int16_t *)right_address;
        break;
    case IR_TYPE__I32:
        result = *(int32_t *)left_address > *(int32_t *)right_address;
        break;
    case IR_TYPE__I64:
    case IR_TYPE__ISIZE:
        result = *(int64_t *)left_address > *(int64_t *)right_address;
        break;
    case IR_TYPE__U8:
        result = *(uint8_t *)left_address > *(uint8_t *)right_address;
        break;
    case IR_TYPE__U16:
        result = *(uint16_t *)left_address > *(uint16_t *)right_address;
        break;
    case IR_TYPE__U32:
        result = *(uint32_t *)left_address > *(uint32_t *)right_address;
        break;
    case IR_TYPE__U64:
    case IR_TYPE__USIZE:
        result = *(uint64_t *)left_address > *(uint64_t *)right_address;
        break;
    default:
        break;
    }
    *(bool *)result_address = result;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_cmp_le_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data) {
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    bool result = false;
    switch (instruction->arguments.items[0]->type->kind) {
    case IR_TYPE__BOOL:
        result = *(bool *)left_address <= *(bool *)right_address;
        break;
    case IR_TYPE__I8:
        result = *(int8_t *)left_address <= *(int8_t *)right_address;
        break;
    case IR_TYPE__I16:
        result = *(int16_t *)left_address <= *(int16_t *)right_address;
        break;
    case IR_TYPE__I32:
        result = *(int32_t *)left_address <= *(int32_t *)right_address;
        break;
    case IR_TYPE__I64:
    case IR_TYPE__ISIZE:
        result = *(int64_t *)left_address <= *(int64_t *)right_address;
        break;
    case IR_TYPE__U8:
        result = *(uint8_t *)left_address <= *(uint8_t *)right_address;
        break;
    case IR_TYPE__U16:
        result = *(uint16_t *)left_address <= *(uint16_t *)right_address;
        break;
    case IR_TYPE__U32:
        result = *(uint32_t *)left_address <= *(uint32_t *)right_address;
        break;
    case IR_TYPE__U64:
    case IR_TYPE__USIZE:
        result = *(uint64_t *)left_address <= *(uint64_t *)right_address;
        break;
    default:
        break;
    }
    *(bool *)result_address = result;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_cmp_lt_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data) {
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    bool result = false;
    switch (instruction->arguments.items[0]->type->kind) {
    case IR_TYPE__BOOL:
        result = *(bool *)left_address < *(bool *)right_address;
        break;
    case IR_TYPE__I8:
        result = *(int8_t *)left_address < *(int8_t *)right_address;
        break;
    case IR_TYPE__I16:
        result = *(int16_t *)left_address < *(int16_t *)right_address;
        break;
    case IR_TYPE__I32:
        result = *(int32_t *)left_address < *(int32_t *)right_address;
        break;
    case IR_TYPE__I64:
    case IR_TYPE__ISIZE:
        result = *(int64_t *)left_address < *(int64_t *)right_address;
        break;
    case IR_TYPE__U8:
        result = *(uint8_t *)left_address < *(uint8_t *)right_address;
        break;
    case IR_TYPE__U16:
        result = *(uint16_t *)left_address < *(uint16_t *)right_address;
        break;
    case IR_TYPE__U32:
        result = *(uint32_t *)left_address < *(uint32_t *)right_address;
        break;
    case IR_TYPE__U64:
    case IR_TYPE__USIZE:
        result = *(uint64_t *)left_address < *(uint64_t *)right_address;
        break;
    default:
        break;
    }
    *(bool *)result_address = result;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_cmp_ne_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data) {
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    bool result = false;
    switch (instruction->arguments.items[0]->type->kind) {
    case IR_TYPE__BOOL:
        result = *(bool *)left_address != *(bool *)right_address;
        break;
    case IR_TYPE__I8:
    case IR_TYPE__U8:
        result = *(uint8_t *)left_address != *(uint8_t *)right_address;
        break;
    case IR_TYPE__I16:
    case IR_TYPE__U16:
        result = *(uint16_t *)left_address != *(uint16_t *)right_address;
        break;
    case IR_TYPE__I32:
    case IR_TYPE__U32:
        result = *(uint32_t *)left_address != *(uint32_t *)right_address;
        break;
    case IR_TYPE__I64:
    case IR_TYPE__ISIZE:
    case IR_TYPE__U64:
    case IR_TYPE__USIZE:
    case IR_TYPE__MULTI_PTR:
    case IR_TYPE__PTR:
    case IR_TYPE__PROC:
        result = *(uint64_t *)left_address != *(uint64_t *)right_address;
        break;
    default:
        break;
    }
    *(bool *)result_address = result;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_const_instruction(IR_Instruction *instruction, uint8_t *frame_data) {
    uint8_t *result_address = frame_data + instruction->result.slot.offset;
    int64_t result = instruction->const_instruction.value;
    switch (instruction->result.type->kind) {
    case IR_TYPE__BOOL:
        *(bool *)result_address = result != 0;
        break;
    case IR_TYPE__I8:
        *(int8_t *)result_address = (int8_t)result;
        break;
    case IR_TYPE__I16:
        *(int16_t *)result_address = (int16_t)result;
        break;
    case IR_TYPE__I32:
        *(int32_t *)result_address = (int32_t)result;
        break;
    case IR_TYPE__I64:
    case IR_TYPE__ISIZE:
        *(int64_t *)result_address = result;
        break;
    case IR_TYPE__U8:
        *(uint8_t *)result_address = (uint8_t)result;
        break;
    case IR_TYPE__U16:
        *(uint16_t *)result_address = (uint16_t)result;
        break;
    case IR_TYPE__U32:
        *(uint32_t *)result_address = (uint32_t)result;
        break;
    case IR_TYPE__U64:
    case IR_TYPE__USIZE:
        *(uint64_t *)result_address = (uint64_t)result;
        break;
    default:
        break;
    }
    return (Step){.kind = STEP_NEXT};
}

static Step execute_div_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data) {
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    if (*(int64_t *)right_address == 0) {
        runtime_error(interpreter, instruction->location, "Division by zero");
    }
    switch (instruction->result.type->kind) {
    case IR_TYPE__I8:
        *(int8_t *)result_address = *(int8_t *)left_address / *(int8_t *)right_address;
        break;
    case IR_TYPE__I16:
        *(int16_t *)result_address = *(int16_t *)left_address / *(int16_t *)right_address;
        break;
    case IR_TYPE__I32:
        *(int32_t *)result_address = *(int32_t *)left_address / *(int32_t *)right_address;
        break;
    case IR_TYPE__I64:
    case IR_TYPE__ISIZE:
        *(int64_t *)result_address = *(int64_t *)left_address / *(int64_t *)right_address;
        break;
    case IR_TYPE__U8:
        *(uint8_t *)result_address = *(uint8_t *)left_address / *(uint8_t *)right_address;
        break;
    case IR_TYPE__U16:
        *(uint16_t *)result_address = *(uint16_t *)left_address / *(uint16_t *)right_address;
        break;
    case IR_TYPE__U32:
        *(uint32_t *)result_address = *(uint32_t *)left_address / *(uint32_t *)right_address;
        break;
    case IR_TYPE__U64:
    case IR_TYPE__USIZE:
        *(uint64_t *)result_address = *(uint64_t *)left_address / *(uint64_t *)right_address;
        break;
    default:
        break;
    }
    return (Step){.kind = STEP_NEXT};
}

static Step execute_jmp_instruction(IR_Instruction *instruction) {
    return (Step){.kind = STEP_JUMP, .jump_label = instruction->jmp_instruction.label};
}

static Step execute_load_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data) {
    uint8_t *address = *(uint8_t **)value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    memcpy(result_address, address, instruction->result.slot.size);
    return (Step){.kind = STEP_NEXT};
}

static Step execute_mod_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data) {
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    if (*(int64_t *)right_address == 0) {
        runtime_error(interpreter, instruction->location, "Modulo by zero");
    }
    switch (instruction->result.type->kind) {
    case IR_TYPE__I8:
        *(int8_t *)result_address = *(int8_t *)left_address % *(int8_t *)right_address;
        break;
    case IR_TYPE__I16:
        *(int16_t *)result_address = *(int16_t *)left_address % *(int16_t *)right_address;
        break;
    case IR_TYPE__I32:
        *(int32_t *)result_address = *(int32_t *)left_address % *(int32_t *)right_address;
        break;
    case IR_TYPE__I64:
    case IR_TYPE__ISIZE:
        *(int64_t *)result_address = *(int64_t *)left_address % *(int64_t *)right_address;
        break;
    case IR_TYPE__U8:
        *(uint8_t *)result_address = *(uint8_t *)left_address % *(uint8_t *)right_address;
        break;
    case IR_TYPE__U16:
        *(uint16_t *)result_address = *(uint16_t *)left_address % *(uint16_t *)right_address;
        break;
    case IR_TYPE__U32:
        *(uint32_t *)result_address = *(uint32_t *)left_address % *(uint32_t *)right_address;
        break;
    case IR_TYPE__U64:
    case IR_TYPE__USIZE:
        *(uint64_t *)result_address = *(uint64_t *)left_address % *(uint64_t *)right_address;
        break;
    default:
        break;
    }
    return (Step){.kind = STEP_NEXT};
}

static Step execute_mul_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data) {
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    switch (instruction->result.type->kind) {
    case IR_TYPE__I8:
        *(int8_t *)result_address = *(int8_t *)left_address * *(int8_t *)right_address;
        break;
    case IR_TYPE__I16:
        *(int16_t *)result_address = *(int16_t *)left_address * *(int16_t *)right_address;
        break;
    case IR_TYPE__I32:
        *(int32_t *)result_address = *(int32_t *)left_address * *(int32_t *)right_address;
        break;
    case IR_TYPE__I64:
    case IR_TYPE__ISIZE:
        *(int64_t *)result_address = *(int64_t *)left_address * *(int64_t *)right_address;
        break;
    case IR_TYPE__U8:
        *(uint8_t *)result_address = *(uint8_t *)left_address * *(uint8_t *)right_address;
        break;
    case IR_TYPE__U16:
        *(uint16_t *)result_address = *(uint16_t *)left_address * *(uint16_t *)right_address;
        break;
    case IR_TYPE__U32:
        *(uint32_t *)result_address = *(uint32_t *)left_address * *(uint32_t *)right_address;
        break;
    case IR_TYPE__U64:
    case IR_TYPE__USIZE:
        *(uint64_t *)result_address = *(uint64_t *)left_address * *(uint64_t *)right_address;
        break;
    default:
        break;
    }
    return (Step){.kind = STEP_NEXT};
}

static Step execute_neg_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data) {
    uint8_t *source_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    switch (instruction->result.type->kind) {
    case IR_TYPE__I8:
        *(int8_t *)result_address = -*(int8_t *)source_address;
        break;
    case IR_TYPE__I16:
        *(int16_t *)result_address = -*(int16_t *)source_address;
        break;
    case IR_TYPE__I32:
        *(int32_t *)result_address = -*(int32_t *)source_address;
        break;
    case IR_TYPE__I64:
    case IR_TYPE__ISIZE:
        *(int64_t *)result_address = -*(int64_t *)source_address;
        break;
    default:
        break;
    }
    return (Step){.kind = STEP_NEXT};
}

static Step execute_not_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data) {
    uint8_t *source_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    bool result = *(bool *)source_address;
    *(bool *)result_address = !result;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_offset_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data) {
    uint8_t *base = *(uint8_t **)value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    if (instruction->offset_instruction.struct_field == NULL) {
        // indexed form: base + index * sizeof(pointee)
        IR_Type *pointee = instruction->arguments.items[0]->type->pointee;
        size_t index = 0;
        memcpy(&index, value_address(interpreter, frame_data, instruction->arguments.items[1]), instruction->arguments.items[1]->slot.size);
        *(uint8_t **)result_address = base + index * ir_type_size(pointee);
    } else {
        IR_Type *struct_type = instruction->arguments.items[0]->type->pointee;
        String field_name = instruction->offset_instruction.struct_field->name;
        size_t field_offset = 0;
        for (size_t i = 0; i < struct_type->struct_field_count; i++) {
            if (string_equals(struct_type->struct_fields[i]->name, field_name)) {
                break;
            }
            field_offset += ir_type_size(struct_type->struct_fields[i]->type);
        }
        *(uint8_t **)result_address = base + field_offset;
    }
    return (Step){.kind = STEP_NEXT};
}

static Step execute_phi_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, size_t previous_label) {
    for (size_t i = 0; i < instruction->arguments.size; i++) {
        if (instruction->phi_instruction.labels[i] == previous_label) {
            uint8_t *source_address = value_address(interpreter, frame_data, instruction->arguments.items[i]);
            uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
            memcpy(result_address, source_address, instruction->result.slot.size);
            return (Step){.kind = STEP_NEXT};
        }
    }
    runtime_error(interpreter, instruction->location, "Phi '%.*s' has no entry for predecessor @%zu", STRING(instruction->result.name), previous_label);
}

static Step execute_placeholder_instruction(Interpreter *interpreter, IR_Instruction *instruction) {
    runtime_error(interpreter, instruction->location, "Unresolved placeholder '%.*s'", STRING(instruction->result.name));
}

static Step execute_ret_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address) {
    if (instruction->arguments.size > 0 && return_address != NULL) {
        IR_Value *source_value = instruction->arguments.items[0];
        memcpy(return_address, value_address(interpreter, frame_data, source_value), source_value->slot.size);
    }
    return (Step){.kind = STEP_RETURN};
}

static Step execute_store_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data) {
    uint8_t *address = *(uint8_t **)value_address(interpreter, frame_data, instruction->arguments.items[0]);
    IR_Value *source_value = instruction->arguments.items[1];
    memcpy(address, value_address(interpreter, frame_data, source_value), source_value->slot.size);
    return (Step){.kind = STEP_NEXT};
}

static Step execute_struct_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data) {
    IR_Type *struct_type = instruction->result.type;
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    for (size_t i = 0; i < instruction->arguments.size; i++) {
        IR_Struct_Field *field = instruction->struct_instruction.fields[i];
        size_t field_offset = 0;
        for (size_t j = 0; j < struct_type->struct_field_count; j++) {
            if (struct_type->struct_fields[j] == field) {
                break;
            }
            field_offset += ir_type_size(struct_type->struct_fields[j]->type);
        }
        IR_Value *source_value = instruction->arguments.items[i];
        memcpy(result_address + field_offset, value_address(interpreter, frame_data, source_value), source_value->slot.size);
    }
    return (Step){.kind = STEP_NEXT};
}

static Step execute_sub_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data) {
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    switch (instruction->result.type->kind) {
    case IR_TYPE__I8:
        *(int8_t *)result_address = *(int8_t *)left_address - *(int8_t *)right_address;
        break;
    case IR_TYPE__I16:
        *(int16_t *)result_address = *(int16_t *)left_address - *(int16_t *)right_address;
        break;
    case IR_TYPE__I32:
        *(int32_t *)result_address = *(int32_t *)left_address - *(int32_t *)right_address;
        break;
    case IR_TYPE__I64:
    case IR_TYPE__ISIZE:
        *(int64_t *)result_address = *(int64_t *)left_address - *(int64_t *)right_address;
        break;
    case IR_TYPE__U8:
        *(uint8_t *)result_address = *(uint8_t *)left_address - *(uint8_t *)right_address;
        break;
    case IR_TYPE__U16:
        *(uint16_t *)result_address = *(uint16_t *)left_address - *(uint16_t *)right_address;
        break;
    case IR_TYPE__U32:
        *(uint32_t *)result_address = *(uint32_t *)left_address - *(uint32_t *)right_address;
        break;
    case IR_TYPE__U64:
    case IR_TYPE__USIZE:
        *(uint64_t *)result_address = *(uint64_t *)left_address - *(uint64_t *)right_address;
        break;
    default:
        break;
    }
    return (Step){.kind = STEP_NEXT};
}

static Step execute_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, size_t previous_label) {
    switch (instruction->kind) {
    case IR_INSTRUCTION__ADD:
        return execute_add_instruction(interpreter, instruction, frame_data);
    case IR_INSTRUCTION__ALLOC:
        return execute_alloc_instruction(interpreter, instruction, frame_data);
    case IR_INSTRUCTION__BR:
        return execute_br_instruction(interpreter, instruction, frame_data);
    case IR_INSTRUCTION__CALL:
        return execute_call_instruction(interpreter, instruction, frame_data);
    case IR_INSTRUCTION__CAST:
        return execute_cast_instruction(interpreter, instruction, frame_data);
    case IR_INSTRUCTION__CMP_EQ:
        return execute_cmp_eq_instruction(interpreter, instruction, frame_data);
    case IR_INSTRUCTION__CMP_GE:
        return execute_cmp_ge_instruction(interpreter, instruction, frame_data);
    case IR_INSTRUCTION__CMP_GT:
        return execute_cmp_gt_instruction(interpreter, instruction, frame_data);
    case IR_INSTRUCTION__CMP_LE:
        return execute_cmp_le_instruction(interpreter, instruction, frame_data);
    case IR_INSTRUCTION__CMP_LT:
        return execute_cmp_lt_instruction(interpreter, instruction, frame_data);
    case IR_INSTRUCTION__CMP_NE:
        return execute_cmp_ne_instruction(interpreter, instruction, frame_data);
    case IR_INSTRUCTION__CONST:
        return execute_const_instruction(instruction, frame_data);
    case IR_INSTRUCTION__DIV:
        return execute_div_instruction(interpreter, instruction, frame_data);
    case IR_INSTRUCTION__JMP:
        return execute_jmp_instruction(instruction);
    case IR_INSTRUCTION__LOAD:
        return execute_load_instruction(interpreter, instruction, frame_data);
    case IR_INSTRUCTION__MOD:
        return execute_mod_instruction(interpreter, instruction, frame_data);
    case IR_INSTRUCTION__MUL:
        return execute_mul_instruction(interpreter, instruction, frame_data);
    case IR_INSTRUCTION__NEG:
        return execute_neg_instruction(interpreter, instruction, frame_data);
    case IR_INSTRUCTION__NOT:
        return execute_not_instruction(interpreter, instruction, frame_data);
    case IR_INSTRUCTION__OFFSET:
        return execute_offset_instruction(interpreter, instruction, frame_data);
    case IR_INSTRUCTION__PHI:
        return execute_phi_instruction(interpreter, instruction, frame_data, previous_label);
    case IR_INSTRUCTION__PLACEHOLDER:
        return execute_placeholder_instruction(interpreter, instruction);
    case IR_INSTRUCTION__RET:
        return execute_ret_instruction(interpreter, instruction, frame_data, return_address);
    case IR_INSTRUCTION__STORE:
        return execute_store_instruction(interpreter, instruction, frame_data);
    case IR_INSTRUCTION__STRUCT:
        return execute_struct_instruction(interpreter, instruction, frame_data);
    case IR_INSTRUCTION__SUB:
        return execute_sub_instruction(interpreter, instruction, frame_data);
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

static void call_external(Interpreter *interpreter, IR_Function *function, uint8_t **argument_addresses, uint8_t *return_address, Source_Location call_location) {
    switch (function->which) {
    case IR_EXTERNAL_FUNCTION__exit:
        exit((int)*(int32_t *)argument_addresses[0]);
        break;
    case IR_EXTERNAL_FUNCTION__fputc: {
        int32_t c = *(int32_t *)argument_addresses[0];
        FILE *stream = (FILE *)*(uint8_t **)argument_addresses[1];
        int result = fputc(c, stream);
        if (return_address != NULL) {
            *(int32_t *)return_address = (int32_t)result;
        }
        break;
    }
    case IR_EXTERNAL_FUNCTION__free: {
        void *ptr = (void *)*(uint8_t **)argument_addresses[0];
        free(ptr);
        break;
    }
    case IR_EXTERNAL_FUNCTION__malloc: {
        size_t size = *(size_t *)argument_addresses[0];
        uint8_t *result = malloc(size);
        *(uint8_t **)return_address = result;
        break;
    }
    case IR_EXTERNAL_FUNCTION__realloc: {
        void *ptr = (void *)*(uint8_t **)argument_addresses[0];
        size_t size = *(size_t *)argument_addresses[1];
        uint8_t *result = realloc(ptr, size);
        *(uint8_t **)return_address = result;
        break;
    }
    default:
        runtime_error(interpreter, call_location, "Unknown external function '%.*s'", STRING(function->name));
    }
}

static void run_function(Interpreter *interpreter, IR_Function *function, uint8_t **argument_addresses, size_t argument_count, uint8_t *return_address, Source_Location call_location) {
    if (argument_count != function->parameters.size) {
        runtime_error(interpreter, call_location, "'%.*s' expects %zu argument(s), got %zu", STRING(function->name), function->parameters.size, argument_count);
    }
    if (function->is_external) {
        call_external(interpreter, function, argument_addresses, return_address, call_location);
        return;
    }
    if (function->blocks.size == 0) {
        runtime_error(interpreter, function->location, "'%.*s' has no blocks", STRING(function->name));
    }

    uint8_t *frame_data = function->frame_size > 0 ? calloc(function->frame_size, 1) : NULL;
    for (size_t i = 0; i < argument_count; i++) {
        IR_Value *parameter_value = function->parameters.items[i];
        memcpy(frame_data + parameter_value->slot.offset, argument_addresses[i], parameter_value->slot.size);
    }

    IR_Block *block = function->blocks.items[0];
    size_t previous_label = SIZE_MAX;
    while (true) {
        bool terminated = false;
        for (size_t i = 0; i < block->instructions.size; i++) {
            IR_Instruction *instruction = block->instructions.items[i];
            Step step = execute_instruction(interpreter, instruction, frame_data, return_address, previous_label);
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
            free(frame_data);
            return;
        }
        if (!terminated) {
            runtime_error(interpreter, block->location, "'%.*s' block @%zu fell off without a terminator", STRING(function->name), block->label);
        }
    }
}

int64_t interpret(IR_Module *module, int argc, char *argv[]) {
    String main_name = string_from("$main");
    Interpreter interpreter = {.module = module};
    IR_Function *main_function = find_function(&interpreter, main_name);
    if (main_function == NULL) {
        fprintf(stderr, "%.*s: No $main function\n", STRING(module->source.path));
        panic();
    }
    if (main_function->return_type->kind != IR_TYPE__I32 && main_function->return_type->kind != IR_TYPE__VOID) {
        fprintf(stderr, "%.*s:%zu:%zu: Unsupported return type", STRING(module->source.path), main_function->location.line, main_function->location.column);
        fprint_ir_type(stderr, main_function->return_type);
        fputc('\n', stderr);
        panic();
    }
    interpreter.globals_data = module->globals_size > 0 ? calloc(module->globals_size, 1) : NULL;
    for (size_t i = 0; i < module->global_variables.size; i++) {
        IR_Global_Variable *global_variable = module->global_variables.items[i];
        if (!global_variable->is_external) {
            continue;
        }
        uint8_t *host_address;
        if (string_equals_cstr(global_variable->name, "$optind")) {
            host_address = (uint8_t *)&optind;
        } else if (string_equals_cstr(global_variable->name, "$stdout")) {
            host_address = (uint8_t *)&stdout;
        } else if (string_equals_cstr(global_variable->name, "$stderr")) {
            host_address = (uint8_t *)&stderr;
        } else if (string_equals_cstr(global_variable->name, "$stdin")) {
            host_address = (uint8_t *)&stdin;
        } else {
            todo("Add support for external: %.*s", STRING(global_variable->name));
        }
        *(uint8_t **)(interpreter.globals_data + global_variable->value.slot.offset) = host_address;
    }
    for (size_t i = 0; i < module->functions.size; i++) {
        IR_Function *function = module->functions.items[i];
        *(IR_Function **)(interpreter.globals_data + function->value.slot.offset) = function;
    }
    size_t main_arguments_count = main_function->parameters.size;
    uint8_t **main_argument_addresses = main_arguments_count == 0 ? NULL : malloc(main_arguments_count * sizeof(uint8_t *));
    int32_t main_argc = (int32_t)argc;
    char **main_argv = argv;
    if (main_arguments_count > 0) {
        if (main_function->parameters.items[0]->type != ir_type_i32()) {
            fprintf(stderr, "%.*s:%zu:%zu: $main first parameter must be i32, got ", STRING(module->source.path), main_function->location.line, main_function->location.column);
            fprint_ir_type(stderr, main_function->parameters.items[0]->type);
            fputc('\n', stderr);
            panic();
        }
        main_argument_addresses[0] = (uint8_t *)&main_argc;
        if (main_arguments_count > 1) {
            if (main_function->parameters.items[1]->type != ir_type_multipointer(&module->types, ir_type_multipointer(&module->types, ir_type_u8()))) {
                fprintf(stderr, "%.*s:%zu:%zu: $main second parameter must be [*][*]u8, got ", STRING(module->source.path), main_function->location.line, main_function->location.column);
                fprint_ir_type(stderr, main_function->parameters.items[1]->type);
                fputc('\n', stderr);
                panic();
            }
            main_argument_addresses[1] = (uint8_t *)&main_argv;
            if (main_arguments_count > 2) {
                fprintf(stderr, "%.*s:%zu:%zu: $main has too many parameters\n", STRING(module->source.path), main_function->location.line, main_function->location.column);
                panic();
            }
        }
    }
    int32_t main_return = 0;
    uint8_t *main_return_address = main_function->return_type->kind == IR_TYPE__I32 ? (uint8_t *)&main_return : NULL;
    run_function(&interpreter, main_function, main_argument_addresses, main_arguments_count, main_return_address, main_function->location);
    free(main_argument_addresses);
    free(interpreter.globals_data);
    return main_function->return_type->kind == IR_TYPE__I32 ? (int64_t)main_return : 0;
}
