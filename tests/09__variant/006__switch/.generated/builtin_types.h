#ifndef __BUILTIN_TYPES_H__
#define __BUILTIN_TYPES_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct String {
    uint8_t *data;
    uintmax_t length;
};

#endif // __BUILTIN_TYPES_H__
