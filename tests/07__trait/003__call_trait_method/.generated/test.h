#ifndef __test_H__
#define __test_H__

#include "builtin_types.h"


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

int32_t ptest_Square__area(struct test_Square *self);

int32_t ptest_Circle__area(struct test_Circle *self);

int32_t test__main();

#endif // __test_H__
