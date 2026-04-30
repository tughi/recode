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

static int64_t run_function(IR_Module *module, IR_Function *function, int64_t *args, size_t argc);

static int64_t execute_instruction(IR_Module *module, IR_Instruction *instruction, Frame *frame) {
    switch (instruction->kind) {
    case IR_INSTRUCTION__CONST:
        frame_bind(frame, &instruction->result, instruction->const_instruction.value);
        return 0;
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
        return 0;
    }
    case IR_INSTRUCTION__RET:
        return frame_lookup(frame, instruction->arguments.items[0]);
    }
    fprintf(stderr, "Interpreter: unknown instruction kind %d\n", instruction->kind);
    exit(1);
}

static int64_t run_function(IR_Module *module, IR_Function *function, int64_t *args, size_t argc) {
    if (argc != function->parameters.size) {
        fprintf(stderr, "Interpreter: '%.*s' expects %zu argument(s), got %zu\n",
                (int)function->name.length, function->name.content,
                function->parameters.size, argc);
        exit(1);
    }
    if (function->blocks.size != 1) {
        fprintf(stderr, "Interpreter: '%.*s' has %zu blocks; control flow not supported yet\n",
                (int)function->name.length, function->name.content, function->blocks.size);
        exit(1);
    }

    Frame frame = {0};
    for (size_t i = 0; i < argc; i++) {
        frame_bind(&frame, function->parameters.items[i], args[i]);
    }

    IR_Block *block = function->blocks.items[0];
    int64_t result = 0;
    bool returned = false;
    for (size_t i = 0; i < block->instructions.size; i++) {
        IR_Instruction *instruction = block->instructions.items[i];
        if (instruction->kind == IR_INSTRUCTION__RET) {
            result = execute_instruction(module, instruction, &frame);
            returned = true;
            break;
        }
        execute_instruction(module, instruction, &frame);
    }

    free(frame.items);

    if (!returned) {
        fprintf(stderr, "Interpreter: '%.*s' fell off the end without ret\n",
                (int)function->name.length, function->name.content);
        exit(1);
    }
    return result;
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
