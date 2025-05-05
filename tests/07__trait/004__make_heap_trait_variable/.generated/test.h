#ifndef __test_H__
#define __test_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>


struct test_Shape;

struct test_Square;

struct test_Circle;

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

struct test_Shape *__alloc__test_Shape__(struct test_Shape value);

struct test_Square *__alloc__test_Square__(struct test_Square value);

struct test_Circle *__alloc__test_Circle__(struct test_Circle value);

int32_t ptest_Square__area(struct test_Square *self);

int32_t ptest_Circle__area(struct test_Circle *self);

int32_t test__main();

void *malloc(uint64_t size);

#endif // __test_H__
