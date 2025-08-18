#include "test.h"

void *malloc(uintmax_t size);

#line 11 "tests/04__struct/005__assign_struct_member/test.code"
int32_t test__main() {
#line 12 "tests/04__struct/005__assign_struct_member/test.code"
    struct test_Line line;
#line 13 "tests/04__struct/005__assign_struct_member/test.code"
    line.p2.y = 64;
#line 14 "tests/04__struct/005__assign_struct_member/test.code"
    {
#line 14 "tests/04__struct/005__assign_struct_member/test.code"
        int32_t __001__ = line.p2.y - 64;
#line 14 "tests/04__struct/005__assign_struct_member/test.code"
        return __001__;
#line 14 "tests/04__struct/005__assign_struct_member/test.code"
    }
#line 15 "tests/04__struct/005__assign_struct_member/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

