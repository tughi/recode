#ifndef __test_H__
#define __test_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>


struct test__Shape;

struct test__Square;

struct test__Circle;

struct test__Shape {
    void *self;
    int32_t (*area)(void *self);
};

struct test__Square {
    int32_t side;
};

struct test__Circle {
    int32_t radius;
};

struct test__Shape *__alloc_test__Shape_value(struct test__Shape value);

struct test__Square *__alloc_test__Square_value(struct test__Square value);

struct test__Circle *__alloc_test__Circle_value(struct test__Circle value);

int32_t test__ptest__Square__area(struct test__Square *self);

int32_t test__ptest__Circle__area(struct test__Circle *self);

int32_t test__main();

void *malloc(uint64_t size);

#endif // __test_H__
