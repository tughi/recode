#include "test.h"

void *malloc(uintmax_t size);

#line 11 "tests/04__struct/006__make_heap_struct_variable/test.code"
int32_t test__main() {
#line 12 "tests/04__struct/006__make_heap_struct_variable/test.code"
    struct test_Line *line;
#line 12 "tests/04__struct/006__make_heap_struct_variable/test.code"
    {
#line 12 "tests/04__struct/006__make_heap_struct_variable/test.code"
        struct test_Line *__001__ = (struct test_Line *)malloc(sizeof(struct test_Line));
#line 12 "tests/04__struct/006__make_heap_struct_variable/test.code"
        *__001__ = (struct test_Line){.p1 = (struct test_Point){.x = 16, .y = 32}, .p2 = (struct test_Point){.x = 48, .y = 64}};
#line 12 "tests/04__struct/006__make_heap_struct_variable/test.code"
        line = __001__;
    }
#line 16 "tests/04__struct/006__make_heap_struct_variable/test.code"
    return line->p1.x + line->p1.y + line->p2.x + line->p2.y - 160;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

