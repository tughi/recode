#ifndef __test_H__
#define __test_H__

#include "builtin_types.h"


struct test_Dog {
    int32_t age;
};

struct test_Animal {
    void *self;
    int32_t (*legs)(void *self);
};

int32_t ptest_Dog__legs(struct test_Dog *self);

int32_t test__main();

#endif // __test_H__
