#ifndef __TYPES_H__
#define __TYPES_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct String {
    uint8_t *data;
    uintmax_t length;
};

struct test_Value {
    int32_t variant;
    union {
        uintmax_t variant_1;
        int32_t *variant_2;
        int64_t *variant_3;
    };
};

#endif // __TYPES_H__
