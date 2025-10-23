#ifndef __TYPES_H__
#define __TYPES_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct String {
    uint8_t *data;
    uintmax_t length;
};

struct test_Point {
    int32_t x;
    int32_t y;
};

struct test_Line {
    struct test_Point p1;
    struct test_Point p2;
};

#endif // __TYPES_H__
