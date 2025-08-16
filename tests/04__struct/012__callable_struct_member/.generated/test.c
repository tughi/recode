#include "test.h"

void *malloc(uintmax_t size);

#line 5 "tests/04__struct/012__callable_struct_member/test.code"
int32_t test__forty_two() {
#line 6 "tests/04__struct/012__callable_struct_member/test.code"
    {
#line 6 "tests/04__struct/012__callable_struct_member/test.code"
        int32_t __001__ = 42;
#line 6 "tests/04__struct/012__callable_struct_member/test.code"
        return __001__;
#line 6 "tests/04__struct/012__callable_struct_member/test.code"
    }
#line 7 "tests/04__struct/012__callable_struct_member/test.code"
}

#line 9 "tests/04__struct/012__callable_struct_member/test.code"
int32_t test__main() {
#line 10 "tests/04__struct/012__callable_struct_member/test.code"
    struct test_Function procedure = (struct test_Function){.run = test__forty_two};
#line 12 "tests/04__struct/012__callable_struct_member/test.code"
    {
#line 12 "tests/04__struct/012__callable_struct_member/test.code"
        int32_t __001__ = procedure.run() - 42;
#line 12 "tests/04__struct/012__callable_struct_member/test.code"
        return __001__;
#line 12 "tests/04__struct/012__callable_struct_member/test.code"
    }
#line 13 "tests/04__struct/012__callable_struct_member/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

