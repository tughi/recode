#include "test.h"

void *malloc(uintmax_t size);

#line 6 "tests/04__struct/003__access_struct_member/test.code"
int32_t test__main() {
#line 7 "tests/04__struct/003__access_struct_member/test.code"
    struct test_Point point = (struct test_Point){.x = 16, .y = 32};
#line 8 "tests/04__struct/003__access_struct_member/test.code"
    return point.x - 16;
#line 9 "tests/04__struct/003__access_struct_member/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

