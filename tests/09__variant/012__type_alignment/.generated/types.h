#ifndef __TYPES_H__
#define __TYPES_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct String {
    uint8_t *data;
    uintmax_t length;
};

struct test_Data {
    int32_t variant;
    union {
        bool variant_1;
        int8_t variant_2;
    };
};

struct test_More_Data {
    int32_t variant;
    union {
        struct test_Data variant_1;
        int64_t variant_2;
    };
};

#endif // __TYPES_H__
