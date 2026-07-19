#pragma once

#include "IR.h"
#include <mach/mach_time.h>

// Raw mach ticks (~3x cheaper than clock_gettime); convert with profile_nanoseconds for display.
static inline uint64_t profile_time(void) {
    return mach_absolute_time();
}

uint64_t profile_nanoseconds(uint64_t ticks);

typedef struct Profile_Call {
    IR_Function *function;
    struct Profile_Call *parent;
    struct Profile_Call **children;
    size_t children_size;
    size_t children_capacity;
    uint64_t time;
    uint64_t calls;
    uint64_t bytes;
} Profile_Call;

Profile_Call *profile_call_child(Profile_Call *parent, IR_Function *function);

void profile_save(IR_Module *module, const char *path);

void profile_show(IR_Module *module);
