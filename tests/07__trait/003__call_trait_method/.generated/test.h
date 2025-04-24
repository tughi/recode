#ifndef __test_H__
#define __test_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>


struct Shape;

struct Square;

struct Circle;

struct Shape {
    void *self;
    int32_t (*area)(void *self);
};

struct Square {
    int32_t side;
};

struct Circle {
    int32_t radius;
};

int32_t test__pSquare__area(struct Square *self);

int32_t test__pCircle__area(struct Circle *self);

int32_t test__main();

#endif // __test_H__
