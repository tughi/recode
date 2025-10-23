#ifndef __TYPES_H__
#define __TYPES_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct String {
    uint8_t *data;
    uintmax_t length;
};

struct test_Error {
    int32_t code;
};

struct test_Result__12_36 {
    bool success;
    union {
        int32_t value;
        struct test_Error error;
    };
};

#endif // __TYPES_H__
