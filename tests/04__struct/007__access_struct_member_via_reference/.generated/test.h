#ifndef __test_H__
#define __test_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>


struct test__Point;

struct test__Line;

struct test__Point {
    int32_t x;
    int32_t y;
};

struct test__Line {
    struct test__Point p1;
    struct test__Point p2;
};

int32_t test__main();

#endif // __test_H__
