#ifndef __TYPES_H__
#define __TYPES_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct String {
    uint8_t *data;
    uintmax_t length;
};

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

#endif // __TYPES_H__
