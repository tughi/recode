#ifndef __TYPES_H__
#define __TYPES_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct String {
    uint8_t *data;
    uintmax_t length;
};

struct collections_List_Item__i32;

struct collections_List__i32 {
    struct collections_List_Item__i32 *first_item;
    struct collections_List_Item__i32 *last_item;
    uintmax_t length;
};

struct collections_List_Item__i32 {
    int32_t data;
    struct collections_List_Item__i32 *next;
};

#endif // __TYPES_H__
