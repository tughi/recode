#ifndef __TYPES_H__
#define __TYPES_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct String {
    uint8_t *data;
    uintmax_t length;
};

struct collections_List_item__tokens_Token;

struct collections_List__tokens_Token {
    struct collections_List_item__tokens_Token *first;
};

struct foo_Foo_Demo {
    struct collections_List__tokens_Token tokens;
};

struct bar_Bar_Demo {
    struct collections_List__tokens_Token tokens;
};

struct tokens_Identifier {
    struct String name;
};

struct tokens_Number {
    int32_t value;
};

struct tokens_Token {
    int32_t variant;
    union {
        struct tokens_Identifier variant_1;
        struct tokens_Number variant_2;
    };
};

struct collections_List_item__tokens_Token {
    struct tokens_Token data;
    struct collections_List_item__tokens_Token *next;
};

#endif // __TYPES_H__
