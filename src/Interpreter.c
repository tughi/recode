#include "Interpreter.h"
#include "Panic.h"
#include "Profiler.h"
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <dirent.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define INTERPRETER_STACK_SIZE (8 * 1024 * 1024)

struct Interpreter {
    IR_Module *module;
    uint8_t *globals_data;
    uint8_t *stack_data;
    size_t stack_used;
    Observer *observer;
    Call_Frame *current_frame;
    bool aborted;
    bool profiling;
    uint64_t *profile_child_time;
};

static void print_runtime_error(Interpreter *interpreter, Source_Location location, const char *format, ...) {
    fprintf(stderr, "%.*s:%zu:%zu: ", STRING(interpreter->module->lexed_file.file.path), location.line, location.column);
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

static inline void copy_slot(uint8_t *destination, const uint8_t *source, size_t size) {
    switch (size) {
    case 1:
        *destination = *source;
        break;
    case 2:
        *(uint16_t *)destination = *(const uint16_t *)source;
        break;
    case 4:
        *(uint32_t *)destination = *(const uint32_t *)source;
        break;
    case 8:
        *(uint64_t *)destination = *(const uint64_t *)source;
        break;
    default:
        memcpy(destination, source, size);
        break;
    }
}

static uint8_t *value_address(Interpreter *interpreter, uint8_t *frame_data, IR_Value *value) {
    uint8_t *base = value->kind <= IR_VALUE__GLOBAL_VARIABLE ? interpreter->globals_data : frame_data;
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

struct Step {
    Step_Kind kind;
    IR_Block *jump_block;
};

static void run_function(Interpreter *interpreter, IR_Function *function, uint8_t **argument_addresses, size_t argument_count, uint8_t *return_address, Source_Location call_location);

static Step execute_add_i8_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(int8_t *)result_address = *(int8_t *)left_address + *(int8_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_add_i16_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(int16_t *)result_address = *(int16_t *)left_address + *(int16_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_add_i32_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(int32_t *)result_address = *(int32_t *)left_address + *(int32_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_add_i64_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(int64_t *)result_address = *(int64_t *)left_address + *(int64_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_add_u8_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(uint8_t *)result_address = *(uint8_t *)left_address + *(uint8_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_add_u16_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(uint16_t *)result_address = *(uint16_t *)left_address + *(uint16_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_add_u32_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(uint32_t *)result_address = *(uint32_t *)left_address + *(uint32_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_add_u64_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(uint64_t *)result_address = *(uint64_t *)left_address + *(uint64_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_and_u8_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(uint8_t *)result_address = *(uint8_t *)left_address & *(uint8_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_and_u16_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(uint16_t *)result_address = *(uint16_t *)left_address & *(uint16_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_and_u32_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(uint32_t *)result_address = *(uint32_t *)left_address & *(uint32_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_and_u64_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(uint64_t *)result_address = *(uint64_t *)left_address & *(uint64_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_alloc_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *payload_address = frame_data + instruction->alloc_instruction.payload_slot.offset;
    memset(payload_address, 0, instruction->alloc_instruction.payload_slot.size);
    *(uint8_t **)value_address(interpreter, frame_data, &instruction->result) = payload_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_br_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    bool condition = *(bool *)value_address(interpreter, frame_data, instruction->arguments.items[0]);
    IR_Block *target = condition ? instruction->br_instruction.true_block : instruction->br_instruction.false_block;
    return (Step){.kind = STEP_JUMP, .jump_block = target};
}

static Step execute_brx_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *value_address_ = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    int64_t value = 0;
    switch (instruction->arguments.items[0]->type->kind) {
    case IR_TYPE__I8:
        value = (int64_t)*(int8_t *)value_address_;
        break;
    case IR_TYPE__I16:
        value = (int64_t)*(int16_t *)value_address_;
        break;
    case IR_TYPE__I32:
        value = (int64_t)*(int32_t *)value_address_;
        break;
    case IR_TYPE__I64:
    case IR_TYPE__ISIZE:
        value = *(int64_t *)value_address_;
        break;
    case IR_TYPE__U8:
        value = (int64_t)*(uint8_t *)value_address_;
        break;
    case IR_TYPE__U16:
        value = (int64_t)*(uint16_t *)value_address_;
        break;
    case IR_TYPE__U32:
        value = (int64_t)*(uint32_t *)value_address_;
        break;
    case IR_TYPE__U64:
    case IR_TYPE__USIZE:
        value = (int64_t)*(uint64_t *)value_address_;
        break;
    default:
        break;
    }
    size_t count = instruction->brx_instruction.count;
    size_t index = (value >= 0 && value < (int64_t)(count - 1)) ? (size_t)value : count - 1;
    return (Step){.kind = STEP_JUMP, .jump_block = instruction->brx_instruction.blocks[index]};
}

static Step execute_call_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    IR_Value *callee_value = instruction->arguments.items[0];
    IR_Function *callee = *(IR_Function **)value_address(interpreter, frame_data, callee_value);
    size_t argument_count = instruction->arguments.size - 1;
    uint8_t *argument_addresses[instruction->arguments.size];
    for (size_t i = 0; i < argument_count; i++) {
        argument_addresses[i] = value_address(interpreter, frame_data, instruction->arguments.items[i + 1]);
    }
    uint8_t *callee_return_address = NULL;
    if (instruction->result.type != NULL && instruction->result.type->kind != IR_TYPE__VOID) {
        callee_return_address = value_address(interpreter, frame_data, &instruction->result);
    }
    run_function(interpreter, callee, argument_addresses, argument_count, callee_return_address, instruction->location);
    return (Step){.kind = STEP_NEXT};
}

static Step execute_cast_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
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

static Step execute_cmp_eq_u8_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(bool *)result_address = *(uint8_t *)left_address == *(uint8_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_cmp_eq_u16_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(bool *)result_address = *(uint16_t *)left_address == *(uint16_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_cmp_eq_u32_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(bool *)result_address = *(uint32_t *)left_address == *(uint32_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_cmp_eq_u64_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(bool *)result_address = *(uint64_t *)left_address == *(uint64_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_cmp_ge_i8_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(bool *)result_address = *(int8_t *)left_address >= *(int8_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_cmp_ge_i16_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(bool *)result_address = *(int16_t *)left_address >= *(int16_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_cmp_ge_i32_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(bool *)result_address = *(int32_t *)left_address >= *(int32_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_cmp_ge_i64_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(bool *)result_address = *(int64_t *)left_address >= *(int64_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_cmp_ge_u8_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(bool *)result_address = *(uint8_t *)left_address >= *(uint8_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_cmp_ge_u16_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(bool *)result_address = *(uint16_t *)left_address >= *(uint16_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_cmp_ge_u32_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(bool *)result_address = *(uint32_t *)left_address >= *(uint32_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_cmp_ge_u64_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(bool *)result_address = *(uint64_t *)left_address >= *(uint64_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_cmp_gt_i8_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(bool *)result_address = *(int8_t *)left_address > *(int8_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_cmp_gt_i16_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(bool *)result_address = *(int16_t *)left_address > *(int16_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_cmp_gt_i32_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(bool *)result_address = *(int32_t *)left_address > *(int32_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_cmp_gt_i64_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(bool *)result_address = *(int64_t *)left_address > *(int64_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_cmp_gt_u8_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(bool *)result_address = *(uint8_t *)left_address > *(uint8_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_cmp_gt_u16_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(bool *)result_address = *(uint16_t *)left_address > *(uint16_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_cmp_gt_u32_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(bool *)result_address = *(uint32_t *)left_address > *(uint32_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_cmp_gt_u64_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(bool *)result_address = *(uint64_t *)left_address > *(uint64_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_cmp_le_i8_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(bool *)result_address = *(int8_t *)left_address <= *(int8_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_cmp_le_i16_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(bool *)result_address = *(int16_t *)left_address <= *(int16_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_cmp_le_i32_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(bool *)result_address = *(int32_t *)left_address <= *(int32_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_cmp_le_i64_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(bool *)result_address = *(int64_t *)left_address <= *(int64_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_cmp_le_u8_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(bool *)result_address = *(uint8_t *)left_address <= *(uint8_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_cmp_le_u16_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(bool *)result_address = *(uint16_t *)left_address <= *(uint16_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_cmp_le_u32_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(bool *)result_address = *(uint32_t *)left_address <= *(uint32_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_cmp_le_u64_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(bool *)result_address = *(uint64_t *)left_address <= *(uint64_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_cmp_lt_i8_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(bool *)result_address = *(int8_t *)left_address < *(int8_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_cmp_lt_i16_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(bool *)result_address = *(int16_t *)left_address < *(int16_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_cmp_lt_i32_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(bool *)result_address = *(int32_t *)left_address < *(int32_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_cmp_lt_i64_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(bool *)result_address = *(int64_t *)left_address < *(int64_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_cmp_lt_u8_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(bool *)result_address = *(uint8_t *)left_address < *(uint8_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_cmp_lt_u16_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(bool *)result_address = *(uint16_t *)left_address < *(uint16_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_cmp_lt_u32_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(bool *)result_address = *(uint32_t *)left_address < *(uint32_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_cmp_lt_u64_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(bool *)result_address = *(uint64_t *)left_address < *(uint64_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_cmp_ne_u8_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(bool *)result_address = *(uint8_t *)left_address != *(uint8_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_cmp_ne_u16_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(bool *)result_address = *(uint16_t *)left_address != *(uint16_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_cmp_ne_u32_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(bool *)result_address = *(uint32_t *)left_address != *(uint32_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_cmp_ne_u64_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(bool *)result_address = *(uint64_t *)left_address != *(uint64_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_const_bool_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)interpreter;
    (void)return_address;
    (void)previous_block;
    *(bool *)(frame_data + instruction->result.slot.offset) = instruction->const_instruction.value != 0;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_const_i8_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)interpreter;
    (void)return_address;
    (void)previous_block;
    *(int8_t *)(frame_data + instruction->result.slot.offset) = (int8_t)instruction->const_instruction.value;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_const_i16_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)interpreter;
    (void)return_address;
    (void)previous_block;
    *(int16_t *)(frame_data + instruction->result.slot.offset) = (int16_t)instruction->const_instruction.value;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_const_i32_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)interpreter;
    (void)return_address;
    (void)previous_block;
    *(int32_t *)(frame_data + instruction->result.slot.offset) = (int32_t)instruction->const_instruction.value;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_const_i64_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)interpreter;
    (void)return_address;
    (void)previous_block;
    *(int64_t *)(frame_data + instruction->result.slot.offset) = (int64_t)instruction->const_instruction.value;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_const_u8_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)interpreter;
    (void)return_address;
    (void)previous_block;
    *(uint8_t *)(frame_data + instruction->result.slot.offset) = (uint8_t)instruction->const_instruction.value;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_const_u16_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)interpreter;
    (void)return_address;
    (void)previous_block;
    *(uint16_t *)(frame_data + instruction->result.slot.offset) = (uint16_t)instruction->const_instruction.value;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_const_u32_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)interpreter;
    (void)return_address;
    (void)previous_block;
    *(uint32_t *)(frame_data + instruction->result.slot.offset) = (uint32_t)instruction->const_instruction.value;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_const_u64_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)interpreter;
    (void)return_address;
    (void)previous_block;
    *(uint64_t *)(frame_data + instruction->result.slot.offset) = (uint64_t)instruction->const_instruction.value;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_const_ptr_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)interpreter;
    (void)return_address;
    (void)previous_block;
    *(uint8_t **)(frame_data + instruction->result.slot.offset) = (uint8_t *)(uintptr_t)instruction->const_instruction.value;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_dbg_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)interpreter;
    (void)instruction;
    (void)frame_data;
    (void)return_address;
    (void)previous_block;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_div_i8_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    if (*(int8_t *)right_address == 0) {
        runtime_error(interpreter, instruction->location, "Division by zero");
    }
    *(int8_t *)result_address = *(int8_t *)left_address / *(int8_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_div_i16_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    if (*(int16_t *)right_address == 0) {
        runtime_error(interpreter, instruction->location, "Division by zero");
    }
    *(int16_t *)result_address = *(int16_t *)left_address / *(int16_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_div_i32_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    if (*(int32_t *)right_address == 0) {
        runtime_error(interpreter, instruction->location, "Division by zero");
    }
    *(int32_t *)result_address = *(int32_t *)left_address / *(int32_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_div_i64_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    if (*(int64_t *)right_address == 0) {
        runtime_error(interpreter, instruction->location, "Division by zero");
    }
    *(int64_t *)result_address = *(int64_t *)left_address / *(int64_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_div_u8_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    if (*(uint8_t *)right_address == 0) {
        runtime_error(interpreter, instruction->location, "Division by zero");
    }
    *(uint8_t *)result_address = *(uint8_t *)left_address / *(uint8_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_div_u16_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    if (*(uint16_t *)right_address == 0) {
        runtime_error(interpreter, instruction->location, "Division by zero");
    }
    *(uint16_t *)result_address = *(uint16_t *)left_address / *(uint16_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_div_u32_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    if (*(uint32_t *)right_address == 0) {
        runtime_error(interpreter, instruction->location, "Division by zero");
    }
    *(uint32_t *)result_address = *(uint32_t *)left_address / *(uint32_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_div_u64_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    if (*(uint64_t *)right_address == 0) {
        runtime_error(interpreter, instruction->location, "Division by zero");
    }
    *(uint64_t *)result_address = *(uint64_t *)left_address / *(uint64_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_jmp_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)interpreter;
    (void)frame_data;
    (void)return_address;
    (void)previous_block;
    return (Step){.kind = STEP_JUMP, .jump_block = instruction->jmp_instruction.block};
}

static Step execute_load_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *address = *(uint8_t **)value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    copy_slot(result_address, address, instruction->result.slot.size);
    return (Step){.kind = STEP_NEXT};
}

static Step execute_mod_i8_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    if (*(int8_t *)right_address == 0) {
        runtime_error(interpreter, instruction->location, "Modulo by zero");
    }
    *(int8_t *)result_address = *(int8_t *)left_address % *(int8_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_mod_i16_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    if (*(int16_t *)right_address == 0) {
        runtime_error(interpreter, instruction->location, "Modulo by zero");
    }
    *(int16_t *)result_address = *(int16_t *)left_address % *(int16_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_mod_i32_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    if (*(int32_t *)right_address == 0) {
        runtime_error(interpreter, instruction->location, "Modulo by zero");
    }
    *(int32_t *)result_address = *(int32_t *)left_address % *(int32_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_mod_i64_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    if (*(int64_t *)right_address == 0) {
        runtime_error(interpreter, instruction->location, "Modulo by zero");
    }
    *(int64_t *)result_address = *(int64_t *)left_address % *(int64_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_mod_u8_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    if (*(uint8_t *)right_address == 0) {
        runtime_error(interpreter, instruction->location, "Modulo by zero");
    }
    *(uint8_t *)result_address = *(uint8_t *)left_address % *(uint8_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_mod_u16_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    if (*(uint16_t *)right_address == 0) {
        runtime_error(interpreter, instruction->location, "Modulo by zero");
    }
    *(uint16_t *)result_address = *(uint16_t *)left_address % *(uint16_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_mod_u32_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    if (*(uint32_t *)right_address == 0) {
        runtime_error(interpreter, instruction->location, "Modulo by zero");
    }
    *(uint32_t *)result_address = *(uint32_t *)left_address % *(uint32_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_mod_u64_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    if (*(uint64_t *)right_address == 0) {
        runtime_error(interpreter, instruction->location, "Modulo by zero");
    }
    *(uint64_t *)result_address = *(uint64_t *)left_address % *(uint64_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_mul_i8_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(int8_t *)result_address = *(int8_t *)left_address * *(int8_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_mul_i16_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(int16_t *)result_address = *(int16_t *)left_address * *(int16_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_mul_i32_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(int32_t *)result_address = *(int32_t *)left_address * *(int32_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_mul_i64_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(int64_t *)result_address = *(int64_t *)left_address * *(int64_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_mul_u8_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(uint8_t *)result_address = *(uint8_t *)left_address * *(uint8_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_mul_u16_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(uint16_t *)result_address = *(uint16_t *)left_address * *(uint16_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_mul_u32_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(uint32_t *)result_address = *(uint32_t *)left_address * *(uint32_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_mul_u64_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(uint64_t *)result_address = *(uint64_t *)left_address * *(uint64_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_neg_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
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

static Step execute_not_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *source_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    bool result = *(bool *)source_address;
    *(bool *)result_address = !result;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_offset_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *base = *(uint8_t **)value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    if (instruction->offset_instruction.struct_field == NULL) {
        // indexed form: base + index * sizeof(item)
        size_t index = 0;
        copy_slot((uint8_t *)&index, value_address(interpreter, frame_data, instruction->arguments.items[1]), instruction->arguments.items[1]->slot.size);
        *(uint8_t **)result_address = base + index * instruction->offset_instruction.item_size;
    } else {
        *(uint8_t **)result_address = base + instruction->offset_instruction.field_offset;
    }
    return (Step){.kind = STEP_NEXT};
}

static Step execute_or_u8_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(uint8_t *)result_address = *(uint8_t *)left_address | *(uint8_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_or_u16_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(uint16_t *)result_address = *(uint16_t *)left_address | *(uint16_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_or_u32_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(uint32_t *)result_address = *(uint32_t *)left_address | *(uint32_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_or_u64_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(uint64_t *)result_address = *(uint64_t *)left_address | *(uint64_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_phi_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    for (size_t i = 0; i < instruction->arguments.size; i++) {
        if (instruction->phi_instruction.blocks[i] == previous_block) {
            uint8_t *source_address = value_address(interpreter, frame_data, instruction->arguments.items[i]);
            uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
            copy_slot(result_address, source_address, instruction->result.slot.size);
            return (Step){.kind = STEP_NEXT};
        }
    }
    runtime_error(interpreter, instruction->location, "Phi '%.*s' has no entry for predecessor @%zu", STRING(instruction->result.name), previous_block == NULL ? 0 : previous_block->label);
}

static Step execute_placeholder_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)frame_data;
    (void)return_address;
    (void)previous_block;
    runtime_error(interpreter, instruction->location, "Unresolved placeholder '%.*s'", STRING(instruction->result.name));
}

static Step execute_ret_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)previous_block;
    if (instruction->arguments.size > 0 && return_address != NULL) {
        IR_Value *source_value = instruction->arguments.items[0];
        copy_slot(return_address, value_address(interpreter, frame_data, source_value), source_value->slot.size);
    }
    return (Step){.kind = STEP_RETURN};
}

static Step execute_shl_u8_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    if (*(uint8_t *)right_address >= 8) {
        runtime_error(interpreter, instruction->location, "Shift out of range");
    }
    *(uint8_t *)result_address = *(uint8_t *)left_address << *(uint8_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_shl_u16_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    if (*(uint16_t *)right_address >= 16) {
        runtime_error(interpreter, instruction->location, "Shift out of range");
    }
    *(uint16_t *)result_address = *(uint16_t *)left_address << *(uint16_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_shl_u32_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    if (*(uint32_t *)right_address >= 32) {
        runtime_error(interpreter, instruction->location, "Shift out of range");
    }
    *(uint32_t *)result_address = *(uint32_t *)left_address << *(uint32_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_shl_u64_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    if (*(uint64_t *)right_address >= 64) {
        runtime_error(interpreter, instruction->location, "Shift out of range");
    }
    *(uint64_t *)result_address = *(uint64_t *)left_address << *(uint64_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_shr_i8_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    if (*(uint8_t *)right_address >= 8) {
        runtime_error(interpreter, instruction->location, "Shift out of range");
    }
    *(int8_t *)result_address = *(int8_t *)left_address >> *(int8_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_shr_i16_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    if (*(uint16_t *)right_address >= 16) {
        runtime_error(interpreter, instruction->location, "Shift out of range");
    }
    *(int16_t *)result_address = *(int16_t *)left_address >> *(int16_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_shr_i32_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    if (*(uint32_t *)right_address >= 32) {
        runtime_error(interpreter, instruction->location, "Shift out of range");
    }
    *(int32_t *)result_address = *(int32_t *)left_address >> *(int32_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_shr_i64_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    if (*(uint64_t *)right_address >= 64) {
        runtime_error(interpreter, instruction->location, "Shift out of range");
    }
    *(int64_t *)result_address = *(int64_t *)left_address >> *(int64_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_shr_u8_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    if (*(uint8_t *)right_address >= 8) {
        runtime_error(interpreter, instruction->location, "Shift out of range");
    }
    *(uint8_t *)result_address = *(uint8_t *)left_address >> *(uint8_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_shr_u16_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    if (*(uint16_t *)right_address >= 16) {
        runtime_error(interpreter, instruction->location, "Shift out of range");
    }
    *(uint16_t *)result_address = *(uint16_t *)left_address >> *(uint16_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_shr_u32_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    if (*(uint32_t *)right_address >= 32) {
        runtime_error(interpreter, instruction->location, "Shift out of range");
    }
    *(uint32_t *)result_address = *(uint32_t *)left_address >> *(uint32_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_shr_u64_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    if (*(uint64_t *)right_address >= 64) {
        runtime_error(interpreter, instruction->location, "Shift out of range");
    }
    *(uint64_t *)result_address = *(uint64_t *)left_address >> *(uint64_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_store_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *address = *(uint8_t **)value_address(interpreter, frame_data, instruction->arguments.items[0]);
    IR_Value *source_value = instruction->arguments.items[1];
    copy_slot(address, value_address(interpreter, frame_data, source_value), source_value->slot.size);
    return (Step){.kind = STEP_NEXT};
}

static Step execute_struct_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    for (size_t i = 0; i < instruction->arguments.size; i++) {
        IR_Value *source_value = instruction->arguments.items[i];
        copy_slot(result_address + instruction->struct_instruction.field_offsets[i], value_address(interpreter, frame_data, source_value), source_value->slot.size);
    }
    return (Step){.kind = STEP_NEXT};
}

static Step execute_sub_i8_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(int8_t *)result_address = *(int8_t *)left_address - *(int8_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_sub_i16_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(int16_t *)result_address = *(int16_t *)left_address - *(int16_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_sub_i32_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(int32_t *)result_address = *(int32_t *)left_address - *(int32_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_sub_i64_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(int64_t *)result_address = *(int64_t *)left_address - *(int64_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_sub_u8_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(uint8_t *)result_address = *(uint8_t *)left_address - *(uint8_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_sub_u16_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(uint16_t *)result_address = *(uint16_t *)left_address - *(uint16_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_sub_u32_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(uint32_t *)result_address = *(uint32_t *)left_address - *(uint32_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_sub_u64_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(uint64_t *)result_address = *(uint64_t *)left_address - *(uint64_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_xor_u8_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(uint8_t *)result_address = *(uint8_t *)left_address ^ *(uint8_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_xor_u16_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(uint16_t *)result_address = *(uint16_t *)left_address ^ *(uint16_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_xor_u32_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(uint32_t *)result_address = *(uint32_t *)left_address ^ *(uint32_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static Step execute_xor_u64_instruction(Interpreter *interpreter, IR_Instruction *instruction, uint8_t *frame_data, uint8_t *return_address, IR_Block *previous_block) {
    (void)return_address;
    (void)previous_block;
    uint8_t *left_address = value_address(interpreter, frame_data, instruction->arguments.items[0]);
    uint8_t *right_address = value_address(interpreter, frame_data, instruction->arguments.items[1]);
    uint8_t *result_address = value_address(interpreter, frame_data, &instruction->result);
    *(uint64_t *)result_address = *(uint64_t *)left_address ^ *(uint64_t *)right_address;
    return (Step){.kind = STEP_NEXT};
}

static IR_Instruction_Execute instruction_executor(IR_Instruction *instruction) {
    switch (instruction->kind) {
    case IR_INSTRUCTION__ADD:
        switch (instruction->result.type->kind) {
        case IR_TYPE__I8:
            return execute_add_i8_instruction;
        case IR_TYPE__I16:
            return execute_add_i16_instruction;
        case IR_TYPE__I32:
            return execute_add_i32_instruction;
        case IR_TYPE__I64:
        case IR_TYPE__ISIZE:
            return execute_add_i64_instruction;
        case IR_TYPE__U8:
            return execute_add_u8_instruction;
        case IR_TYPE__U16:
            return execute_add_u16_instruction;
        case IR_TYPE__U32:
            return execute_add_u32_instruction;
        case IR_TYPE__U64:
        case IR_TYPE__USIZE:
            return execute_add_u64_instruction;
        default:
            break;
        }
        break;
    case IR_INSTRUCTION__ALLOC:
        return execute_alloc_instruction;
    case IR_INSTRUCTION__AND:
        switch (instruction->result.type->kind) {
        case IR_TYPE__I8:
        case IR_TYPE__U8:
            return execute_and_u8_instruction;
        case IR_TYPE__I16:
        case IR_TYPE__U16:
            return execute_and_u16_instruction;
        case IR_TYPE__I32:
        case IR_TYPE__U32:
            return execute_and_u32_instruction;
        case IR_TYPE__I64:
        case IR_TYPE__ISIZE:
        case IR_TYPE__U64:
        case IR_TYPE__USIZE:
            return execute_and_u64_instruction;
        default:
            break;
        }
        break;
    case IR_INSTRUCTION__BR:
        return execute_br_instruction;
    case IR_INSTRUCTION__BRX:
        return execute_brx_instruction;
    case IR_INSTRUCTION__CALL:
        return execute_call_instruction;
    case IR_INSTRUCTION__CAST:
        return execute_cast_instruction;
    case IR_INSTRUCTION__CMP_EQ:
        switch (instruction->arguments.items[0]->type->kind) {
        case IR_TYPE__BOOL:
        case IR_TYPE__I8:
        case IR_TYPE__U8:
            return execute_cmp_eq_u8_instruction;
        case IR_TYPE__I16:
        case IR_TYPE__U16:
            return execute_cmp_eq_u16_instruction;
        case IR_TYPE__I32:
        case IR_TYPE__U32:
            return execute_cmp_eq_u32_instruction;
        case IR_TYPE__I64:
        case IR_TYPE__ISIZE:
        case IR_TYPE__U64:
        case IR_TYPE__USIZE:
        case IR_TYPE__MULTI_PTR:
        case IR_TYPE__PTR:
        case IR_TYPE__PROC:
            return execute_cmp_eq_u64_instruction;
        default:
            break;
        }
        break;
    case IR_INSTRUCTION__CMP_GE:
        switch (instruction->arguments.items[0]->type->kind) {
        case IR_TYPE__I8:
            return execute_cmp_ge_i8_instruction;
        case IR_TYPE__I16:
            return execute_cmp_ge_i16_instruction;
        case IR_TYPE__I32:
            return execute_cmp_ge_i32_instruction;
        case IR_TYPE__I64:
        case IR_TYPE__ISIZE:
            return execute_cmp_ge_i64_instruction;
        case IR_TYPE__BOOL:
        case IR_TYPE__U8:
            return execute_cmp_ge_u8_instruction;
        case IR_TYPE__U16:
            return execute_cmp_ge_u16_instruction;
        case IR_TYPE__U32:
            return execute_cmp_ge_u32_instruction;
        case IR_TYPE__U64:
        case IR_TYPE__USIZE:
            return execute_cmp_ge_u64_instruction;
        default:
            break;
        }
        break;
    case IR_INSTRUCTION__CMP_GT:
        switch (instruction->arguments.items[0]->type->kind) {
        case IR_TYPE__I8:
            return execute_cmp_gt_i8_instruction;
        case IR_TYPE__I16:
            return execute_cmp_gt_i16_instruction;
        case IR_TYPE__I32:
            return execute_cmp_gt_i32_instruction;
        case IR_TYPE__I64:
        case IR_TYPE__ISIZE:
            return execute_cmp_gt_i64_instruction;
        case IR_TYPE__BOOL:
        case IR_TYPE__U8:
            return execute_cmp_gt_u8_instruction;
        case IR_TYPE__U16:
            return execute_cmp_gt_u16_instruction;
        case IR_TYPE__U32:
            return execute_cmp_gt_u32_instruction;
        case IR_TYPE__U64:
        case IR_TYPE__USIZE:
            return execute_cmp_gt_u64_instruction;
        default:
            break;
        }
        break;
    case IR_INSTRUCTION__CMP_LE:
        switch (instruction->arguments.items[0]->type->kind) {
        case IR_TYPE__I8:
            return execute_cmp_le_i8_instruction;
        case IR_TYPE__I16:
            return execute_cmp_le_i16_instruction;
        case IR_TYPE__I32:
            return execute_cmp_le_i32_instruction;
        case IR_TYPE__I64:
        case IR_TYPE__ISIZE:
            return execute_cmp_le_i64_instruction;
        case IR_TYPE__BOOL:
        case IR_TYPE__U8:
            return execute_cmp_le_u8_instruction;
        case IR_TYPE__U16:
            return execute_cmp_le_u16_instruction;
        case IR_TYPE__U32:
            return execute_cmp_le_u32_instruction;
        case IR_TYPE__U64:
        case IR_TYPE__USIZE:
            return execute_cmp_le_u64_instruction;
        default:
            break;
        }
        break;
    case IR_INSTRUCTION__CMP_LT:
        switch (instruction->arguments.items[0]->type->kind) {
        case IR_TYPE__I8:
            return execute_cmp_lt_i8_instruction;
        case IR_TYPE__I16:
            return execute_cmp_lt_i16_instruction;
        case IR_TYPE__I32:
            return execute_cmp_lt_i32_instruction;
        case IR_TYPE__I64:
        case IR_TYPE__ISIZE:
            return execute_cmp_lt_i64_instruction;
        case IR_TYPE__BOOL:
        case IR_TYPE__U8:
            return execute_cmp_lt_u8_instruction;
        case IR_TYPE__U16:
            return execute_cmp_lt_u16_instruction;
        case IR_TYPE__U32:
            return execute_cmp_lt_u32_instruction;
        case IR_TYPE__U64:
        case IR_TYPE__USIZE:
            return execute_cmp_lt_u64_instruction;
        default:
            break;
        }
        break;
    case IR_INSTRUCTION__CMP_NE:
        switch (instruction->arguments.items[0]->type->kind) {
        case IR_TYPE__BOOL:
        case IR_TYPE__I8:
        case IR_TYPE__U8:
            return execute_cmp_ne_u8_instruction;
        case IR_TYPE__I16:
        case IR_TYPE__U16:
            return execute_cmp_ne_u16_instruction;
        case IR_TYPE__I32:
        case IR_TYPE__U32:
            return execute_cmp_ne_u32_instruction;
        case IR_TYPE__I64:
        case IR_TYPE__ISIZE:
        case IR_TYPE__U64:
        case IR_TYPE__USIZE:
        case IR_TYPE__MULTI_PTR:
        case IR_TYPE__PTR:
        case IR_TYPE__PROC:
            return execute_cmp_ne_u64_instruction;
        default:
            break;
        }
        break;
    case IR_INSTRUCTION__CONST:
        switch (instruction->result.type->kind) {
        case IR_TYPE__BOOL:
            return execute_const_bool_instruction;
        case IR_TYPE__I8:
            return execute_const_i8_instruction;
        case IR_TYPE__I16:
            return execute_const_i16_instruction;
        case IR_TYPE__I32:
            return execute_const_i32_instruction;
        case IR_TYPE__I64:
        case IR_TYPE__ISIZE:
            return execute_const_i64_instruction;
        case IR_TYPE__U8:
            return execute_const_u8_instruction;
        case IR_TYPE__U16:
            return execute_const_u16_instruction;
        case IR_TYPE__U32:
            return execute_const_u32_instruction;
        case IR_TYPE__U64:
        case IR_TYPE__USIZE:
            return execute_const_u64_instruction;
        case IR_TYPE__MULTI_PTR:
        case IR_TYPE__PTR:
            return execute_const_ptr_instruction;
        default:
            break;
        }
        break;
    case IR_INSTRUCTION__DBG_BIND:
    case IR_INSTRUCTION__DBG_LINE:
        return execute_dbg_instruction;
    case IR_INSTRUCTION__DIV:
        switch (instruction->result.type->kind) {
        case IR_TYPE__I8:
            return execute_div_i8_instruction;
        case IR_TYPE__I16:
            return execute_div_i16_instruction;
        case IR_TYPE__I32:
            return execute_div_i32_instruction;
        case IR_TYPE__I64:
        case IR_TYPE__ISIZE:
            return execute_div_i64_instruction;
        case IR_TYPE__U8:
            return execute_div_u8_instruction;
        case IR_TYPE__U16:
            return execute_div_u16_instruction;
        case IR_TYPE__U32:
            return execute_div_u32_instruction;
        case IR_TYPE__U64:
        case IR_TYPE__USIZE:
            return execute_div_u64_instruction;
        default:
            break;
        }
        break;
    case IR_INSTRUCTION__JMP:
        return execute_jmp_instruction;
    case IR_INSTRUCTION__LOAD:
        return execute_load_instruction;
    case IR_INSTRUCTION__MOD:
        switch (instruction->result.type->kind) {
        case IR_TYPE__I8:
            return execute_mod_i8_instruction;
        case IR_TYPE__I16:
            return execute_mod_i16_instruction;
        case IR_TYPE__I32:
            return execute_mod_i32_instruction;
        case IR_TYPE__I64:
        case IR_TYPE__ISIZE:
            return execute_mod_i64_instruction;
        case IR_TYPE__U8:
            return execute_mod_u8_instruction;
        case IR_TYPE__U16:
            return execute_mod_u16_instruction;
        case IR_TYPE__U32:
            return execute_mod_u32_instruction;
        case IR_TYPE__U64:
        case IR_TYPE__USIZE:
            return execute_mod_u64_instruction;
        default:
            break;
        }
        break;
    case IR_INSTRUCTION__MUL:
        switch (instruction->result.type->kind) {
        case IR_TYPE__I8:
            return execute_mul_i8_instruction;
        case IR_TYPE__I16:
            return execute_mul_i16_instruction;
        case IR_TYPE__I32:
            return execute_mul_i32_instruction;
        case IR_TYPE__I64:
        case IR_TYPE__ISIZE:
            return execute_mul_i64_instruction;
        case IR_TYPE__U8:
            return execute_mul_u8_instruction;
        case IR_TYPE__U16:
            return execute_mul_u16_instruction;
        case IR_TYPE__U32:
            return execute_mul_u32_instruction;
        case IR_TYPE__U64:
        case IR_TYPE__USIZE:
            return execute_mul_u64_instruction;
        default:
            break;
        }
        break;
    case IR_INSTRUCTION__NEG:
        return execute_neg_instruction;
    case IR_INSTRUCTION__NOT:
        return execute_not_instruction;
    case IR_INSTRUCTION__OFFSET:
        return execute_offset_instruction;
    case IR_INSTRUCTION__OR:
        switch (instruction->result.type->kind) {
        case IR_TYPE__I8:
        case IR_TYPE__U8:
            return execute_or_u8_instruction;
        case IR_TYPE__I16:
        case IR_TYPE__U16:
            return execute_or_u16_instruction;
        case IR_TYPE__I32:
        case IR_TYPE__U32:
            return execute_or_u32_instruction;
        case IR_TYPE__I64:
        case IR_TYPE__ISIZE:
        case IR_TYPE__U64:
        case IR_TYPE__USIZE:
            return execute_or_u64_instruction;
        default:
            break;
        }
        break;
    case IR_INSTRUCTION__PHI:
        return execute_phi_instruction;
    case IR_INSTRUCTION__PLACEHOLDER:
        return execute_placeholder_instruction;
    case IR_INSTRUCTION__RET:
        return execute_ret_instruction;
    case IR_INSTRUCTION__SHL:
        switch (instruction->result.type->kind) {
        case IR_TYPE__I8:
        case IR_TYPE__U8:
            return execute_shl_u8_instruction;
        case IR_TYPE__I16:
        case IR_TYPE__U16:
            return execute_shl_u16_instruction;
        case IR_TYPE__I32:
        case IR_TYPE__U32:
            return execute_shl_u32_instruction;
        case IR_TYPE__I64:
        case IR_TYPE__ISIZE:
        case IR_TYPE__U64:
        case IR_TYPE__USIZE:
            return execute_shl_u64_instruction;
        default:
            break;
        }
        break;
    case IR_INSTRUCTION__SHR:
        switch (instruction->result.type->kind) {
        case IR_TYPE__I8:
            return execute_shr_i8_instruction;
        case IR_TYPE__I16:
            return execute_shr_i16_instruction;
        case IR_TYPE__I32:
            return execute_shr_i32_instruction;
        case IR_TYPE__I64:
        case IR_TYPE__ISIZE:
            return execute_shr_i64_instruction;
        case IR_TYPE__U8:
            return execute_shr_u8_instruction;
        case IR_TYPE__U16:
            return execute_shr_u16_instruction;
        case IR_TYPE__U32:
            return execute_shr_u32_instruction;
        case IR_TYPE__U64:
        case IR_TYPE__USIZE:
            return execute_shr_u64_instruction;
        default:
            break;
        }
        break;
    case IR_INSTRUCTION__STORE:
        return execute_store_instruction;
    case IR_INSTRUCTION__STRUCT:
        return execute_struct_instruction;
    case IR_INSTRUCTION__SUB:
        switch (instruction->result.type->kind) {
        case IR_TYPE__I8:
            return execute_sub_i8_instruction;
        case IR_TYPE__I16:
            return execute_sub_i16_instruction;
        case IR_TYPE__I32:
            return execute_sub_i32_instruction;
        case IR_TYPE__I64:
        case IR_TYPE__ISIZE:
            return execute_sub_i64_instruction;
        case IR_TYPE__U8:
            return execute_sub_u8_instruction;
        case IR_TYPE__U16:
            return execute_sub_u16_instruction;
        case IR_TYPE__U32:
            return execute_sub_u32_instruction;
        case IR_TYPE__U64:
        case IR_TYPE__USIZE:
            return execute_sub_u64_instruction;
        default:
            break;
        }
        break;
    case IR_INSTRUCTION__XOR:
        switch (instruction->result.type->kind) {
        case IR_TYPE__I8:
        case IR_TYPE__U8:
            return execute_xor_u8_instruction;
        case IR_TYPE__I16:
        case IR_TYPE__U16:
            return execute_xor_u16_instruction;
        case IR_TYPE__I32:
        case IR_TYPE__U32:
            return execute_xor_u32_instruction;
        case IR_TYPE__I64:
        case IR_TYPE__ISIZE:
        case IR_TYPE__U64:
        case IR_TYPE__USIZE:
            return execute_xor_u64_instruction;
        default:
            break;
        }
        break;
    }
    return execute_placeholder_instruction;
}

static void prepare_module(IR_Module *module) {
    for (size_t f = 0; f < module->functions.size; f++) {
        IR_Function *function = module->functions.items[f];
        if (function->is_external) {
            continue;
        }
        for (size_t b = 0; b < function->blocks.size; b++) {
            IR_Block *block = function->blocks.items[b];
            for (size_t i = 0; i < block->instructions.size; i++) {
                block->instructions.items[i]->execute = instruction_executor(block->instructions.items[i]);
            }
        }
    }
}

static void call_external(Interpreter *interpreter, IR_Function *function, uint8_t **argument_addresses, uint8_t *return_address, Source_Location call_location) {
    switch (function->which) {
    case IR_EXTERNAL_FUNCTION__SDL_CreateRenderer: {
        SDL_Window *window = (SDL_Window *)*(uint8_t **)argument_addresses[0];
        int index = *(int32_t *)argument_addresses[1];
        Uint32 flags = *(uint32_t *)argument_addresses[2];
        SDL_Renderer *result = SDL_CreateRenderer(window, index, flags);
        *(uint8_t **)return_address = (uint8_t *)result;
        break;
    }
    case IR_EXTERNAL_FUNCTION__SDL_CreateWindow: {
        const char *title = (const char *)*(uint8_t **)argument_addresses[0];
        int x = *(int32_t *)argument_addresses[1];
        int y = *(int32_t *)argument_addresses[2];
        int w = *(int32_t *)argument_addresses[3];
        int h = *(int32_t *)argument_addresses[4];
        Uint32 flags = *(uint32_t *)argument_addresses[5];
        SDL_Window *result = SDL_CreateWindow(title, x, y, w, h, flags);
        *(uint8_t **)return_address = (uint8_t *)result;
        break;
    }
    case IR_EXTERNAL_FUNCTION__SDL_Delay:
        SDL_Delay(*(uint32_t *)argument_addresses[0]);
        break;
    case IR_EXTERNAL_FUNCTION__SDL_DestroyRenderer:
        SDL_DestroyRenderer((SDL_Renderer *)*(uint8_t **)argument_addresses[0]);
        break;
    case IR_EXTERNAL_FUNCTION__SDL_DestroyWindow:
        SDL_DestroyWindow((SDL_Window *)*(uint8_t **)argument_addresses[0]);
        break;
    case IR_EXTERNAL_FUNCTION__SDL_GetError: {
        const char *result = SDL_GetError();
        *(uint8_t **)return_address = (uint8_t *)result;
        break;
    }
    case IR_EXTERNAL_FUNCTION__SDL_GetWindowID: {
        Uint32 result = SDL_GetWindowID((SDL_Window *)*(uint8_t **)argument_addresses[0]);
        *(uint32_t *)return_address = (uint32_t)result;
        break;
    }
    case IR_EXTERNAL_FUNCTION__SDL_GetWindowSize: {
        SDL_Window *window = (SDL_Window *)*(uint8_t **)argument_addresses[0];
        int *w = (int *)*(uint8_t **)argument_addresses[1];
        int *h = (int *)*(uint8_t **)argument_addresses[2];
        SDL_GetWindowSize(window, w, h);
        break;
    }
    case IR_EXTERNAL_FUNCTION__SDL_Init: {
        SDL_SetMainReady();
        int result = SDL_Init(*(uint32_t *)argument_addresses[0]);
        *(int32_t *)return_address = (int32_t)result;
        break;
    }
    case IR_EXTERNAL_FUNCTION__SDL_PollEvent: {
        SDL_Event *event = (SDL_Event *)*(uint8_t **)argument_addresses[0];
        int result = SDL_PollEvent(event);
        *(int32_t *)return_address = (int32_t)result;
        break;
    }
    case IR_EXTERNAL_FUNCTION__SDL_Quit:
        SDL_Quit();
        break;
    case IR_EXTERNAL_FUNCTION__SDL_RenderClear:
        SDL_RenderClear((SDL_Renderer *)*(uint8_t **)argument_addresses[0]);
        break;
    case IR_EXTERNAL_FUNCTION__SDL_RenderDrawLine: {
        SDL_Renderer *renderer = (SDL_Renderer *)*(uint8_t **)argument_addresses[0];
        int x1 = *(int32_t *)argument_addresses[1];
        int y1 = *(int32_t *)argument_addresses[2];
        int x2 = *(int32_t *)argument_addresses[3];
        int y2 = *(int32_t *)argument_addresses[4];
        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
        break;
    }
    case IR_EXTERNAL_FUNCTION__SDL_RenderDrawPoint: {
        SDL_Renderer *renderer = (SDL_Renderer *)*(uint8_t **)argument_addresses[0];
        int x = *(int32_t *)argument_addresses[1];
        int y = *(int32_t *)argument_addresses[2];
        SDL_RenderDrawPoint(renderer, x, y);
        break;
    }
    case IR_EXTERNAL_FUNCTION__SDL_RenderDrawRect: {
        SDL_Renderer *renderer = (SDL_Renderer *)*(uint8_t **)argument_addresses[0];
        const SDL_Rect *rect = (const SDL_Rect *)*(uint8_t **)argument_addresses[1];
        SDL_RenderDrawRect(renderer, rect);
        break;
    }
    case IR_EXTERNAL_FUNCTION__SDL_RenderFillRect: {
        SDL_Renderer *renderer = (SDL_Renderer *)*(uint8_t **)argument_addresses[0];
        const SDL_Rect *rect = (const SDL_Rect *)*(uint8_t **)argument_addresses[1];
        SDL_RenderFillRect(renderer, rect);
        break;
    }
    case IR_EXTERNAL_FUNCTION__SDL_RenderPresent:
        SDL_RenderPresent((SDL_Renderer *)*(uint8_t **)argument_addresses[0]);
        break;
    case IR_EXTERNAL_FUNCTION__SDL_RenderSetClipRect: {
        SDL_Renderer *renderer = (SDL_Renderer *)*(uint8_t **)argument_addresses[0];
        const SDL_Rect *rect = (const SDL_Rect *)*(uint8_t **)argument_addresses[1];
        SDL_RenderSetClipRect(renderer, rect);
        break;
    }
    case IR_EXTERNAL_FUNCTION__SDL_SetRenderDrawColor: {
        SDL_Renderer *renderer = (SDL_Renderer *)*(uint8_t **)argument_addresses[0];
        Uint8 r = *(uint8_t *)argument_addresses[1];
        Uint8 g = *(uint8_t *)argument_addresses[2];
        Uint8 b = *(uint8_t *)argument_addresses[3];
        Uint8 a = *(uint8_t *)argument_addresses[4];
        SDL_SetRenderDrawColor(renderer, r, g, b, a);
        break;
    }
    case IR_EXTERNAL_FUNCTION__SDL_WaitEvent: {
        SDL_Event *event = (SDL_Event *)*(uint8_t **)argument_addresses[0];
        int result = SDL_WaitEvent(event);
        *(int32_t *)return_address = (int32_t)result;
        break;
    }
    case IR_EXTERNAL_FUNCTION__closedir: {
        DIR *dir = (DIR *)*(uint8_t **)argument_addresses[0];
        int result = closedir(dir);
        if (return_address != NULL) {
            *(int32_t *)return_address = (int32_t)result;
        }
        break;
    }
    case IR_EXTERNAL_FUNCTION__exit:
        exit((int)*(int32_t *)argument_addresses[0]);
        break;
    case IR_EXTERNAL_FUNCTION__fclose: {
        FILE *stream = (FILE *)*(uint8_t **)argument_addresses[0];
        int result = fclose(stream);
        if (return_address != NULL) {
            *(int32_t *)return_address = (int32_t)result;
        }
        break;
    }
    case IR_EXTERNAL_FUNCTION__fopen: {
        const char *path = (const char *)*(uint8_t **)argument_addresses[0];
        const char *mode = (const char *)*(uint8_t **)argument_addresses[1];
        FILE *result = fopen(path, mode);
        *(uint8_t **)return_address = (uint8_t *)result;
        break;
    }
    case IR_EXTERNAL_FUNCTION__fflush: {
        FILE *stream = (FILE *)*(uint8_t **)argument_addresses[0];
        int result = fflush(stream);
        if (return_address != NULL) {
            *(int32_t *)return_address = (int32_t)result;
        }
        break;
    }
    case IR_EXTERNAL_FUNCTION__fputc: {
        int32_t c = *(int32_t *)argument_addresses[0];
        FILE *stream = (FILE *)*(uint8_t **)argument_addresses[1];
        int result = fputc(c, stream);
        if (return_address != NULL) {
            *(int32_t *)return_address = (int32_t)result;
        }
        break;
    }
    case IR_EXTERNAL_FUNCTION__fputs: {
        const char *s = (const char *)*(uint8_t **)argument_addresses[0];
        FILE *stream = (FILE *)*(uint8_t **)argument_addresses[1];
        int result = fputs(s, stream);
        if (return_address != NULL) {
            *(int32_t *)return_address = (int32_t)result;
        }
        break;
    }
    case IR_EXTERNAL_FUNCTION__fread: {
        void *ptr = (void *)*(uint8_t **)argument_addresses[0];
        size_t size = *(size_t *)argument_addresses[1];
        size_t nmemb = *(size_t *)argument_addresses[2];
        FILE *stream = (FILE *)*(uint8_t **)argument_addresses[3];
        size_t result = fread(ptr, size, nmemb, stream);
        *(size_t *)return_address = result;
        break;
    }
    case IR_EXTERNAL_FUNCTION__free: {
        void *ptr = (void *)*(uint8_t **)argument_addresses[0];
        if (interpreter->observer != NULL && ptr != NULL) {
            interpreter->observer->on_heap_free(interpreter->observer, ptr);
        }
        free(ptr);
        break;
    }
    case IR_EXTERNAL_FUNCTION__fseek: {
        FILE *stream = (FILE *)*(uint8_t **)argument_addresses[0];
        long offset = (long)*(int64_t *)argument_addresses[1];
        int whence = *(int32_t *)argument_addresses[2];
        int result = fseek(stream, offset, whence);
        *(int32_t *)return_address = (int32_t)result;
        break;
    }
    case IR_EXTERNAL_FUNCTION__ftell: {
        FILE *stream = (FILE *)*(uint8_t **)argument_addresses[0];
        long result = ftell(stream);
        *(int64_t *)return_address = (int64_t)result;
        break;
    }
    case IR_EXTERNAL_FUNCTION__fwrite: {
        void *ptr = (void *)*(uint8_t **)argument_addresses[0];
        size_t size = *(size_t *)argument_addresses[1];
        size_t nmemb = *(size_t *)argument_addresses[2];
        FILE *stream = (FILE *)*(uint8_t **)argument_addresses[3];
        size_t result = fwrite(ptr, size, nmemb, stream);
        *(size_t *)return_address = result;
        break;
    }
    case IR_EXTERNAL_FUNCTION__get_dirent_name: {
        struct dirent *entry = (struct dirent *)*(uint8_t **)argument_addresses[0];
        const char *result = entry->d_name;
        *(uint8_t **)return_address = (uint8_t *)result;
        break;
    }
    case IR_EXTERNAL_FUNCTION__malloc: {
        size_t size = *(size_t *)argument_addresses[0];
        uint8_t *result = malloc(size);
        if (interpreter->observer != NULL && result != NULL) {
            interpreter->observer->on_heap_alloc(interpreter->observer, result, size, call_location);
        }
        *(uint8_t **)return_address = result;
        break;
    }
    case IR_EXTERNAL_FUNCTION__memcpy: {
        void *destination = (void *)*(uint8_t **)argument_addresses[0];
        void *source = (void *)*(uint8_t **)argument_addresses[1];
        size_t size = *(size_t *)argument_addresses[2];
        *(uint8_t **)return_address = memcpy(destination, source, size);
        break;
    }
    case IR_EXTERNAL_FUNCTION__opendir: {
        const char *name = (const char *)*(uint8_t **)argument_addresses[0];
        DIR *result = opendir(name);
        *(uint8_t **)return_address = (uint8_t *)result;
        break;
    }
    case IR_EXTERNAL_FUNCTION__readdir: {
        DIR *dir = (DIR *)*(uint8_t **)argument_addresses[0];
        struct dirent *result = readdir(dir);
        *(uint8_t **)return_address = (uint8_t *)result;
        break;
    }
    case IR_EXTERNAL_FUNCTION__realloc: {
        void *ptr = (void *)*(uint8_t **)argument_addresses[0];
        size_t size = *(size_t *)argument_addresses[1];
        uint8_t *result = realloc(ptr, size);
        if (interpreter->observer != NULL) {
            if (ptr != NULL) {
                interpreter->observer->on_heap_free(interpreter->observer, ptr);
            }
            if (result != NULL) {
                interpreter->observer->on_heap_alloc(interpreter->observer, result, size, call_location);
            }
        }
        *(uint8_t **)return_address = result;
        break;
    }
    case IR_EXTERNAL_FUNCTION__strlen: {
        const char *s = (const char *)*(uint8_t **)argument_addresses[0];
        *(size_t *)return_address = strlen(s);
        break;
    }
    default:
        runtime_error(interpreter, call_location, "Unknown external function '%.*s'", STRING(function->name));
    }
}

static void profile_function_exit(Interpreter *interpreter, IR_Function *function, uint64_t start_time, uint64_t child_time, uint64_t *caller_child_time) {
    uint64_t elapsed = profile_time() - start_time;
    function->profile.exclusive_time += elapsed - child_time;
    function->profile.active_calls--;
    if (function->profile.active_calls == 0) {
        function->profile.inclusive_time += elapsed;
    }
    interpreter->profile_child_time = caller_child_time;
    if (caller_child_time != NULL) {
        *caller_child_time += elapsed;
    }
}

static void run_function(Interpreter *interpreter, IR_Function *function, uint8_t **argument_addresses, size_t argument_count, uint8_t *return_address, Source_Location call_location) {
    if (argument_count != function->parameters.size) {
        runtime_error(interpreter, call_location, "'%.*s' expects %zu argument(s), got %zu", STRING(function->name), function->parameters.size, argument_count);
    }

    bool profiling = interpreter->profiling;
    uint64_t profile_start = 0;
    uint64_t child_time = 0;
    uint64_t *caller_child_time = NULL;
    if (profiling) {
        function->profile.calls++;
        function->profile.active_calls++;
        caller_child_time = interpreter->profile_child_time;
        interpreter->profile_child_time = &child_time;
        profile_start = profile_time();
    }

    if (function->is_external) {
        call_external(interpreter, function, argument_addresses, return_address, call_location);
        if (profiling) {
            profile_function_exit(interpreter, function, profile_start, child_time, caller_child_time);
        }
        return;
    }
    if (function->blocks.size == 0) {
        runtime_error(interpreter, function->location, "'%.*s' has no blocks", STRING(function->name));
    }

    size_t frame_size = (function->frame_size + 7) & ~(size_t)7;
    if (interpreter->stack_used + frame_size > INTERPRETER_STACK_SIZE) {
        runtime_error(interpreter, call_location, "Stack overflow calling '%.*s'", STRING(function->name));
    }
    uint8_t *frame_data = interpreter->stack_data + interpreter->stack_used;
    interpreter->stack_used += frame_size;
    memset(frame_data, 0, function->frame_size);
    for (size_t i = 0; i < argument_count; i++) {
        IR_Value *parameter_value = function->parameters.items[i];
        copy_slot(frame_data + parameter_value->slot.offset, argument_addresses[i], parameter_value->slot.size);
    }

    Call_Frame frame = {
        .function = function,
        .block = function->blocks.items[0],
        .instruction = NULL,
        .frame_data = frame_data,
        .globals_data = interpreter->globals_data,
        .caller = interpreter->current_frame,
    };
    interpreter->current_frame = &frame;
    if (profiling) {
        frame.block->execution_count++;
    }

    IR_Block *previous_block = NULL;
    while (true) {
        bool terminated = false;
        for (size_t i = 0; i < frame.block->instructions.size; i++) {
            IR_Instruction *instruction = frame.block->instructions.items[i];
            frame.instruction = instruction;
            if (interpreter->observer != NULL && !interpreter->aborted) {
                interpreter->observer->on_step(interpreter->observer, &frame, &interpreter->aborted);
            }
            if (interpreter->aborted) {
                interpreter->current_frame = frame.caller;
                interpreter->stack_used -= frame_size;
                if (profiling) {
                    profile_function_exit(interpreter, function, profile_start, child_time, caller_child_time);
                }
                return;
            }
            Step step = instruction->execute(interpreter, instruction, frame_data, return_address, previous_block);
            if (step.kind == STEP_NEXT) {
                continue;
            }
            if (step.kind == STEP_JUMP) {
                previous_block = frame.block;
                frame.block = step.jump_block;
                if (profiling) {
                    frame.block->execution_count++;
                }
                terminated = true;
                break;
            }
            // STEP_RETURN
            interpreter->current_frame = frame.caller;
            interpreter->stack_used -= frame_size;
            if (profiling) {
                profile_function_exit(interpreter, function, profile_start, child_time, caller_child_time);
            }
            return;
        }
        if (!terminated) {
            runtime_error(interpreter, frame.block->location, "'%.*s' block @%zu fell off without a terminator", STRING(function->name), frame.block->label);
        }
    }
}

int64_t interpret(IR_Module *module, int argc, char *argv[], Observer *observer, bool profiling) {
    String main_name = string_from("$main");
    Interpreter interpreter = {.module = module, .observer = observer, .profiling = profiling};
    prepare_module(module);
    IR_Function *main_function = find_function(&interpreter, main_name);
    if (main_function == NULL) {
        fprintf(stderr, "%.*s: No $main function\n", STRING(module->lexed_file.file.path));
        panic();
    }
    if (main_function->return_type->kind != IR_TYPE__I32 && main_function->return_type->kind != IR_TYPE__VOID) {
        fprintf(stderr, "%.*s:%zu:%zu: Unsupported return type", STRING(module->lexed_file.file.path), main_function->location.line, main_function->location.column);
        fprint_ir_type(stderr, main_function->return_type);
        fputc('\n', stderr);
        panic();
    }
    interpreter.globals_data = module->globals_size > 0 ? calloc(module->globals_size, 1) : NULL;
    interpreter.stack_data = malloc(INTERPRETER_STACK_SIZE);
    interpreter.stack_used = 0;
    for (size_t i = 0; i < module->global_variables.size; i++) {
        IR_Global_Variable *global_variable = module->global_variables.items[i];
        if (global_variable->is_external) {
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
        } else {
            uint8_t *payload_address = interpreter.globals_data + global_variable->payload_slot.offset;
            if (global_variable->payload_data != NULL) {
                memcpy(payload_address, global_variable->payload_data, global_variable->payload_slot.size);
            }
            *(uint8_t **)(interpreter.globals_data + global_variable->value.slot.offset) = payload_address;
        }
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
            fprintf(stderr, "%.*s:%zu:%zu: $main first parameter must be i32, got ", STRING(module->lexed_file.file.path), main_function->location.line, main_function->location.column);
            fprint_ir_type(stderr, main_function->parameters.items[0]->type);
            fputc('\n', stderr);
            panic();
        }
        main_argument_addresses[0] = (uint8_t *)&main_argc;
        if (main_arguments_count > 1) {
            if (main_function->parameters.items[1]->type != ir_type_multipointer(&module->types, ir_type_multipointer(&module->types, ir_type_u8()))) {
                fprintf(stderr, "%.*s:%zu:%zu: $main second parameter must be [*][*]u8, got ", STRING(module->lexed_file.file.path), main_function->location.line, main_function->location.column);
                fprint_ir_type(stderr, main_function->parameters.items[1]->type);
                fputc('\n', stderr);
                panic();
            }
            main_argument_addresses[1] = (uint8_t *)&main_argv;
            if (main_arguments_count > 2) {
                fprintf(stderr, "%.*s:%zu:%zu: $main has too many parameters\n", STRING(module->lexed_file.file.path), main_function->location.line, main_function->location.column);
                panic();
            }
        }
    }
    int32_t main_return = 0;
    uint8_t *main_return_address = main_function->return_type->kind == IR_TYPE__I32 ? (uint8_t *)&main_return : NULL;
    run_function(&interpreter, main_function, main_argument_addresses, main_arguments_count, main_return_address, main_function->location);
    free(main_argument_addresses);
    free(interpreter.stack_data);
    free(interpreter.globals_data);
    return main_function->return_type->kind == IR_TYPE__I32 ? (int64_t)main_return : 0;
}
