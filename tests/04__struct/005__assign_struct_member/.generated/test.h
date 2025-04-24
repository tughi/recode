#ifndef __test_H__
#define __test_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>


struct Point;

struct Line;

struct Point {
    int32_t x;
    int32_t y;
};

struct Line {
    struct Point p1;
    struct Point p2;
};

int32_t test__main();

#endif // __test_H__
