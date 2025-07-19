#include "test.h"
#include "collections.h"

#line 14 "tests/11__generics/005__method/test.code"
int32_t test__main() {
#line 15 "tests/11__generics/005__method/test.code"
    struct collections_List__i32 list = (struct collections_List__i32){.first_item = NULL, .last_item = NULL, .length = 0};
#line 16 "tests/11__generics/005__method/test.code"
    pcollections_List__i32__append(&list, 42);
#line 17 "tests/11__generics/005__method/test.code"
    pcollections_List__i32__prepend(&list, 24);
#line 18 "tests/11__generics/005__method/test.code"
    return list.last_item->data - list.first_item->data - 18;
}

#line 3 "tests/11__generics/005__method/test.code"
void pcollections_List__i32__append(struct collections_List__i32 *self, int32_t data) {
#line 4 "tests/11__generics/005__method/test.code"
    struct collections_List_Item__i32 *new_item = __alloc__collections_List_Item__i32__((struct collections_List_Item__i32){.data = data, .next = NULL});
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
    self->length = self->length + 1;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

