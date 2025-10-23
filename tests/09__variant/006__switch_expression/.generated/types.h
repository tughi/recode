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
        bool variant_1;
        int8_t variant_2;
        int32_t variant_3;
    };
};

struct test_Literal {
    struct test_Value value;
};

#endif // __TYPES_H__
