#ifndef __TYPES_H__
#define __TYPES_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct String {
    uint8_t *data;
    uintmax_t length;
};

struct source_Span {
    int32_t start;
    int32_t end;
};

struct test_Token {
    struct source_Span span;
};

#endif // __TYPES_H__
