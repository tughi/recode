#ifndef __TYPES_H__
#define __TYPES_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct String {
    uint8_t *data;
    uintmax_t length;
};

struct io_Writer {
    void *self;
    int32_t (*write_char)(void *self, int32_t c);
};

#endif // __TYPES_H__
