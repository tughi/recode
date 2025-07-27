#ifndef __collections_H__
#define __collections_H__

#include "builtin_types.h"


struct collections_List__i32__u32 {
    struct collections_List_Item__i32 *first_item;
    struct collections_List_Item__i32 *last_item;
    uint32_t length;
};

struct collections_List_Item__i32 {
    int32_t data;
    struct collections_List_Item__i32 *next;
};

#endif // __collections_H__
