#include "test.h"

struct test_Point *__alloc__test_Point__(struct test_Point value) {
    struct test_Point *result = (struct test_Point *)malloc(sizeof(struct test_Point));
    *result = value;
    return result;
}

struct test_Line *__alloc__test_Line__(struct test_Line value) {
    struct test_Line *result = (struct test_Line *)malloc(sizeof(struct test_Line));
    *result = value;
    return result;
}

#line 11 "tests/04__struct/006__make_heap_struct_variable/test.code"
int32_t test__main() {
#line 12 "tests/04__struct/006__make_heap_struct_variable/test.code"
    struct test_Line *line = __alloc__test_Line__((struct test_Line){.p1 = (struct test_Point){.x = 16, .y = 32}, .p2 = (struct test_Point){.x = 48, .y = 64}});
#line 16 "tests/04__struct/006__make_heap_struct_variable/test.code"
    return line->p1.x + line->p1.y + line->p2.x + line->p2.y - 160;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

