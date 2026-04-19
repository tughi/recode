#ifndef __TYPES_H__
#define __TYPES_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct String {
    uint8_t *data;
    uintmax_t length;
};

struct source_Item {
    int32_t value;
};

struct source_Item__opt {
    int32_t variant;
    struct source_Item variant_1;
};

#endif // __TYPES_H__
