#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

#include "test.h"

#line 11 "tests/04__struct/007__access_struct_member_via_reference/test.code"
int32_t test__main() {
#line 12 "tests/04__struct/007__access_struct_member_via_reference/test.code"
    struct test_Line line = (struct test_Line){.p1 = (struct test_Point){.x = 16, .y = 32}, .p2 = (struct test_Point){.x = 48, .y = 64}};
#line 16 "tests/04__struct/007__access_struct_member_via_reference/test.code"
    struct test_Line *line_reference = &line;
#line 17 "tests/04__struct/007__access_struct_member_via_reference/test.code"
    return line_reference->p2.y - 64;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

