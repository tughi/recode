#ifndef __test_H__
#define __test_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>


struct Dog;

struct Animal;

struct Dog {
    int32_t age;
};

struct Animal {
    void *self;
    int32_t (*legs)(void *self);
};

int32_t test__pDog__legs(struct Dog *self);

int32_t test__main();

#endif // __test_H__
