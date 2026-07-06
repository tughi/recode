#pragma once

#include "IR.h"
#include <stdint.h>

typedef struct Call_Frame Call_Frame;
struct Call_Frame {
    IR_Function *function;
    IR_Block *block;
    IR_Instruction *instruction;
    uint8_t *frame_data;
    uint8_t *globals_data;
    Call_Frame *caller;
};

typedef struct Observer Observer;
struct Observer {
    void (*on_step)(Observer *self, Call_Frame *current_frame);
    void (*on_heap_alloc)(Observer *self, uint8_t *address, size_t size, Source_Location location);
    void (*on_heap_free)(Observer *self, uint8_t *address);
};

int64_t interpret(IR_Module *module, int argc, char *argv[], Observer *inspector);
