#ifndef __test_H__
#define __test_H__

#include "builtin_types.h"


struct test_Vehicle {
    int32_t wheels;
};

struct test_Car {
    struct test_Vehicle super;
};

struct test_Wheeled {
    void *self;
    int32_t (*get_wheels)(void *self);
};

int32_t ptest_Vehicle__get_wheels(struct test_Vehicle *self);

int32_t test__main();

#endif // __test_H__
