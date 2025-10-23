#ifndef __TYPES_H__
#define __TYPES_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct String {
    uint8_t *data;
    uintmax_t length;
};

struct test_Array__i32 {
    int32_t *items;
    uintmax_t length;
    uintmax_t capacity;
};

struct test_Array__i64 {
    int64_t *items;
    uintmax_t length;
    uintmax_t capacity;
};

#endif // __TYPES_H__
