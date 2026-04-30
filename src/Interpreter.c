#include "Interpreter.h"
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

static void frame_bind(Frame *frame, IR_Value *key, int64_t value) {
    if (frame->size == frame->capacity) {
        frame->capacity = frame->capacity == 0 ? 4 : frame->capacity * 2;
        frame->items = realloc(frame->items, frame->capacity * sizeof(Binding));
    }
    frame->items[frame->size++] = (Binding){.key = key, .value = value};
}

static int64_t frame_lookup(Frame *frame, IR_Value *key) {
    for (size_t i = frame->size; i > 0; i--) {
        if (frame->items[i - 1].key == key) {
            return frame->items[i - 1].value;
        }
    }
    fprintf(stderr, "Interpreter: unbound value '%.*s'\n", (int)key->name.length, key->name.content);
    exit(1);
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

static int64_t run_function(IR_Module *module, IR_Function *function, int64_t *args, size_t argc);

static Step execute_instruction(IR_Module *module, IR_Instruction *instruction, Frame *frame, size_t previous_label) {
    switch (instruction->kind) {
    case IR_INSTRUCTION__BR: {
        int64_t condition = frame_lookup(frame, instruction->arguments.items[0]);
        size_t target = condition != 0 ? instruction->br_instruction.true_label : instruction->br_instruction.false_label;
        return (Step){.kind = STEP_JUMP, .jump_label = target};
    }
    case IR_INSTRUCTION__CALL: {
        IR_Value *callee_ref = instruction->arguments.items[0];
        IR_Function *callee = find_function(module, callee_ref->name);
        if (callee == NULL) {
            fprintf(stderr, "Interpreter: unknown function '%.*s'\n", (int)callee_ref->name.length, callee_ref->name.content);
            exit(1);
        }
        size_t argc = instruction->arguments.size - 1;
        int64_t *args = argc == 0 ? NULL : malloc(argc * sizeof(int64_t));
        for (size_t i = 0; i < argc; i++) {
            args[i] = frame_lookup(frame, instruction->arguments.items[i + 1]);
        }
        int64_t result = run_function(module, callee, args, argc);
        free(args);
        frame_bind(frame, &instruction->result, result);
        return (Step){.kind = STEP_NEXT};
    }
    case IR_INSTRUCTION__CONST:
        frame_bind(frame, &instruction->result, instruction->const_instruction.value);
        return (Step){.kind = STEP_NEXT};
    case IR_INSTRUCTION__JMP:
        return (Step){.kind = STEP_JUMP, .jump_label = instruction->jmp_instruction.label};
    case IR_INSTRUCTION__PHI:
        for (size_t i = 0; i < instruction->arguments.size; i++) {
            if (instruction->phi_instruction.labels[i] == previous_label) {
                int64_t value = frame_lookup(frame, instruction->arguments.items[i]);
                frame_bind(frame, &instruction->result, value);
                return (Step){.kind = STEP_NEXT};
            }
        }
        fprintf(stderr, "Interpreter: phi '%.*s' has no entry for predecessor @%zu\n", (int)instruction->result.name.length, instruction->result.name.content, previous_label);
        exit(1);
    case IR_INSTRUCTION__RET:
        return (Step){.kind = STEP_RETURN, .return_value = frame_lookup(frame, instruction->arguments.items[0])};
    }
    fprintf(stderr, "Interpreter: unknown instruction kind %d\n", instruction->kind);
    exit(1);
}

static IR_Block *find_block(IR_Function *function, size_t label) {
    for (size_t i = 0; i < function->blocks.size; i++) {
        if (function->blocks.items[i]->label == label) {
            return function->blocks.items[i];
        }
    }
    return NULL;
}

static int64_t run_function(IR_Module *module, IR_Function *function, int64_t *args, size_t argc) {
    if (argc != function->parameters.size) {
        fprintf(stderr, "Interpreter: '%.*s' expects %zu argument(s), got %zu\n", (int)function->name.length, function->name.content, function->parameters.size, argc);
        exit(1);
    }
    if (function->blocks.size == 0) {
        fprintf(stderr, "Interpreter: '%.*s' has no blocks\n", (int)function->name.length, function->name.content);
        exit(1);
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
            Step step = execute_instruction(module, block->instructions.items[i], &frame, previous_label);
            if (step.kind == STEP_NEXT) {
                continue;
            }
            if (step.kind == STEP_JUMP) {
                IR_Block *target = find_block(function, step.jump_label);
                if (target == NULL) {
                    fprintf(stderr, "Interpreter: '%.*s' has no block @%zu\n", (int)function->name.length, function->name.content, step.jump_label);
                    exit(1);
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
            fprintf(stderr, "Interpreter: '%.*s' block @%zu fell off without a terminator\n", (int)function->name.length, function->name.content, block->label);
            exit(1);
        }
    }
}

int64_t interpret(IR_Module *module) {
    String main_name = string_from("$main");
    IR_Function *main_fn = find_function(module, main_name);
    if (main_fn == NULL) {
        fprintf(stderr, "Interpreter: no $main function\n");
        exit(1);
    }
    return run_function(module, main_fn, NULL, 0);
}
