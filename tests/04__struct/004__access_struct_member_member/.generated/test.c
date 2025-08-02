#include "test.h"

void *malloc(uintmax_t size);

#line 11 "tests/04__struct/004__access_struct_member_member/test.code"
int32_t test__main() {
#line 12 "tests/04__struct/004__access_struct_member_member/test.code"
    struct test_Line line = (struct test_Line){.p1 = (struct test_Point){.x = 16, .y = 32}, .p2 = (struct test_Point){.x = 48, .y = 64}};
#line 16 "tests/04__struct/004__access_struct_member_member/test.code"
    return line.p2.y - 64;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

