#ifndef __TYPES_H__
#define __TYPES_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct String {
    uint8_t *data;
    uintmax_t length;
};

struct test_Integer {
    int32_t variant;
    union {
        int8_t variant_1;
        int32_t variant_2;
    };
};

struct test_Value {
    int32_t variant;
    union {
        bool variant_1;
        struct test_Integer variant_2;
    };
};

#endif // __TYPES_H__
