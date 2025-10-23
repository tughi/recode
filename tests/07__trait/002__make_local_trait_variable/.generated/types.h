#ifndef __TYPES_H__
#define __TYPES_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct String {
    uint8_t *data;
    uintmax_t length;
};

struct test_Dog {
    int32_t age;
};

struct test_Animal {
    void *self;
    int32_t (*legs)(void *self);
};

#endif // __TYPES_H__
