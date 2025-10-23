#ifndef __TYPES_H__
#define __TYPES_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct String {
    uint8_t *data;
    uintmax_t length;
};

struct test_Data__i8 {
    int8_t value;
};

struct test_Data__isize {
    intmax_t value;
};

#endif // __TYPES_H__
