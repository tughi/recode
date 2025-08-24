#ifndef __test_H__
#define __test_H__

#include "builtin_types.h"


struct test_Vehicle {
    int32_t wheels;
};

struct test_Car {
    struct test_Vehicle super;
};

struct test_Sports_Car {
    struct test_Car super;
    bool turbo;
};

int32_t test__main();

#endif // __test_H__
