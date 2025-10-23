#ifndef __TYPES_H__
#define __TYPES_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct String {
    uint8_t *data;
    uintmax_t length;
};

struct test_Addition;

struct test_Subtraction;

struct test_Expression {
    int32_t variant;
    union {
        int32_t variant_1;
        struct test_Addition *variant_2;
        struct test_Subtraction *variant_3;
    };
};

struct test_Addition {
    struct test_Expression left;
    struct test_Expression right;
};

struct test_Subtraction {
    struct test_Expression left;
    struct test_Expression right;
};

#endif // __TYPES_H__
