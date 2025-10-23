#ifndef __TYPES_H__
#define __TYPES_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct String {
    uint8_t *data;
    uintmax_t length;
};

struct test_Shape {
    void *self;
    int32_t (*area)(void *self);
};

struct test_Square {
    int32_t side;
};

struct test_Circle {
    int32_t radius;
};

#endif // __TYPES_H__
