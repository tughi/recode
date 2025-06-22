#ifndef __collections_H__
#define __collections_H__

#include "builtin_types.h"


struct collections_List__i32 {
    struct collections_List_Item__i32 *first_item;
    struct collections_List_Item__i32 *last_item;
    uintmax_t length;
};

struct collections_List_Item__i32 {
    int32_t data;
    struct collections_List_Item__i32 *next;
};

void *malloc(uintmax_t size);

struct collections_List__i32 *__alloc__collections_List__i32__(struct collections_List__i32 value);

struct collections_List_Item__i32 *__alloc__collections_List_Item__i32__(struct collections_List_Item__i32 value);

void pcollections_List__i32__prepend(struct collections_List__i32 *self, int32_t data);

#endif // __collections_H__
