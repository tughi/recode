#pragma once

#include "IR.h"
#include <time.h>

static inline uint64_t profile_time(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000000000u + (uint64_t)ts.tv_nsec;
}

void profile_report(IR_Module *module);
