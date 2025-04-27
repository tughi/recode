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

struct test__Point *__alloc_test__Point_value(struct test__Point value);

struct test__Line *__alloc_test__Line_value(struct test__Line value);

int32_t test__main();

void *malloc(uint64_t size);

#endif // __test_H__
