#include "test.h"
#include "collections.h"

void *malloc(uintmax_t size);

#line 14 "tests/11__generics/005__method/test.code"
int32_t test__main() {
#line 15 "tests/11__generics/005__method/test.code"
    struct collections_List__i32 list;
#line 15 "tests/11__generics/005__method/test.code"
    {
#line 15 "tests/11__generics/005__method/test.code"
        struct collections_List_Item__i32 *__001__ = NULL;
#line 15 "tests/11__generics/005__method/test.code"
        struct collections_List_Item__i32 *__002__ = NULL;
#line 15 "tests/11__generics/005__method/test.code"
        uintmax_t __003__ = 0u;
#line 15 "tests/11__generics/005__method/test.code"
        list = (struct collections_List__i32){.first_item = __001__, .last_item = __002__, .length = __003__};
    }
#line 16 "tests/11__generics/005__method/test.code"
    {
#line 16 "tests/11__generics/005__method/test.code"
        struct collections_List__i32 *__001__ = &list;
#line 16 "tests/11__generics/005__method/test.code"
        int32_t __002__ = 42;
#line 16 "tests/11__generics/005__method/test.code"
        pcollections_List__i32__append(__001__, __002__);
    }
#line 17 "tests/11__generics/005__method/test.code"
    {
#line 17 "tests/11__generics/005__method/test.code"
        struct collections_List__i32 *__001__ = &list;
#line 17 "tests/11__generics/005__method/test.code"
        int32_t __002__ = 24;
#line 17 "tests/11__generics/005__method/test.code"
        pcollections_List__i32__prepend(__001__, __002__);
    }
#line 18 "tests/11__generics/005__method/test.code"
    return list.last_item->data - list.first_item->data - 18;
}

#line 3 "tests/11__generics/005__method/test.code"
void pcollections_List__i32__append(struct collections_List__i32 *self, int32_t data) {
#line 4 "tests/11__generics/005__method/test.code"
    struct collections_List_Item__i32 *new_item;
#line 4 "tests/11__generics/005__method/test.code"
    {
#line 4 "tests/11__generics/005__method/test.code"
        struct collections_List_Item__i32 *__001__ = (struct collections_List_Item__i32 *)malloc(sizeof(struct collections_List_Item__i32));
#line 4 "tests/11__generics/005__method/test.code"
        *__001__ = (struct collections_List_Item__i32){.data = data, .next = NULL};
#line 4 "tests/11__generics/005__method/test.code"
        new_item = __001__;
    }
#line 5 "tests/11__generics/005__method/test.code"
    if (self->first_item == NULL) {
#line 6 "tests/11__generics/005__method/test.code"
        self->first_item = new_item;
    } else {
#line 8 "tests/11__generics/005__method/test.code"
        self->last_item->next = new_item;
    }
#line 10 "tests/11__generics/005__method/test.code"
    self->last_item = new_item;
#line 11 "tests/11__generics/005__method/test.code"
    self->length = self->length + 1u;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

