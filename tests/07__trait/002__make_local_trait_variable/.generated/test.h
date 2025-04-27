#ifndef __test_H__
#define __test_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>


struct test__Dog;

struct test__Animal;

struct test__Dog {
    int32_t age;
};

struct test__Animal {
    void *self;
    int32_t (*legs)(void *self);
};

int32_t test__ptest__Dog__legs(struct test__Dog *self);

int32_t test__main();

#endif // __test_H__
