#ifndef __TYPES_H__
#define __TYPES_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct String {
    uint8_t *data;
    uintmax_t length;
};

struct test_Result__5_21 {
    bool success;
    union {
        int32_t value;
        int32_t error;
    };
};

#endif // __TYPES_H__
