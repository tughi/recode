#ifndef __test_H__
#define __test_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>


struct test_Point {
    int32_t x;
    int32_t y;
};

struct test_Line {
    struct test_Point p1;
    struct test_Point p2;
};

struct test_Point *__alloc__test_Point__(struct test_Point value);

struct test_Line *__alloc__test_Line__(struct test_Line value);

int32_t test__main();

void *malloc(uint64_t size);

#endif // __test_H__
