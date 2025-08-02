#include "test.h"
#include "collections.h"

void *malloc(uintmax_t size);

#line 12 "tests/11__generics/005__method/collections.code"
void pcollections_List__i32__prepend(struct collections_List__i32 *self, int32_t data) {
#line 13 "tests/11__generics/005__method/collections.code"
    struct collections_List_Item__i32 *new_item;
#line 13 "tests/11__generics/005__method/collections.code"
    {
#line 13 "tests/11__generics/005__method/collections.code"
        struct collections_List_Item__i32 *__001__ = (struct collections_List_Item__i32 *)malloc(sizeof(struct collections_List_Item__i32));
#line 13 "tests/11__generics/005__method/collections.code"
        *__001__ = (struct collections_List_Item__i32){.data = data, .next = self->first_item};
#line 13 "tests/11__generics/005__method/collections.code"
        new_item = __001__;
    }
#line 14 "tests/11__generics/005__method/collections.code"
    if (self->first_item == NULL) {
#line 15 "tests/11__generics/005__method/collections.code"
        self->last_item = new_item;
    }
#line 17 "tests/11__generics/005__method/collections.code"
    self->first_item = new_item;
#line 18 "tests/11__generics/005__method/collections.code"
    self->length = self->length + 1u;
}

