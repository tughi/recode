#pragma once

#include "IR.h"
#include <time.h>

static inline uint64_t profile_time(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000000000u + (uint64_t)ts.tv_nsec;
}

typedef struct Profile_Call {
    IR_Function *function;
    struct Profile_Call *parent;
    struct Profile_Call **children;
    size_t children_size;
    size_t children_capacity;
    uint64_t time;
    uint64_t calls;
} Profile_Call;

Profile_Call *profile_call_child(Profile_Call *parent, IR_Function *function);

void profile_show(IR_Module *module);
