#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

#include "test.h"

struct test__Point *__alloc_test__Point_value(struct test__Point value) {
    struct test__Point *result = (struct test__Point *)malloc(sizeof(struct test__Point));
    *result = value;
    return result;
}

struct test__Line *__alloc_test__Line_value(struct test__Line value) {
    struct test__Line *result = (struct test__Line *)malloc(sizeof(struct test__Line));
    *result = value;
    return result;
}

#line 11 "tests/04__struct/006__make_heap_struct_variable/test.code"
int32_t test__main() {
#line 12 "tests/04__struct/006__make_heap_struct_variable/test.code"
    struct test__Line *line = __alloc_test__Line_value((struct test__Line){.p1 = (struct test__Point){.x = 16, .y = 32}, .p2 = (struct test__Point){.x = 48, .y = 64}});
#line 16 "tests/04__struct/006__make_heap_struct_variable/test.code"
    return line->p1.x + line->p1.y + line->p2.x + line->p2.y - 160;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

