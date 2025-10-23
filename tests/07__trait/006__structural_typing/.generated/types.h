#ifndef __TYPES_H__
#define __TYPES_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct String {
    uint8_t *data;
    uintmax_t length;
};

struct test_Writer {
    void *self;
    void (*write_char)(void *self, uint8_t c);
};

struct test_Writable {
    void *self;
    void (*write_to)(void *self, struct test_Writer *writer);
};

#endif // __TYPES_H__
