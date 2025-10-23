#ifndef __TYPES_H__
#define __TYPES_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct String {
    uint8_t *data;
    uintmax_t length;
};

struct test_Input_Stream {
    void *self;
    uint8_t (*read)(void *self);
};

#endif // __TYPES_H__
