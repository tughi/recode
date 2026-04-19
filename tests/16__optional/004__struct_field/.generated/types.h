#ifndef __TYPES_H__
#define __TYPES_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct String {
    uint8_t *data;
    uintmax_t length;
};

struct i32__opt {
    int32_t variant;
    int32_t variant_1;
};

struct test_Person {
    struct String name;
    struct i32__opt age;
};

#endif // __TYPES_H__
