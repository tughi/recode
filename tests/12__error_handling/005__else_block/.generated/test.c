#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/12__error_handling/005__else_block/test.code"
int32_t test__main() {
#line 2 "tests/12__error_handling/005__else_block/test.code"
    {
#line 2 "tests/12__error_handling/005__else_block/test.code"
        struct test_Result__11_36 __001__ = test__increment(13);
#line 2 "tests/12__error_handling/005__else_block/test.code"
        int32_t __002__;
#line 2 "tests/12__error_handling/005__else_block/test.code"
        if (__001__.success) {
#line 2 "tests/12__error_handling/005__else_block/test.code"
            __002__ = __001__.value;
#line 2 "tests/12__error_handling/005__else_block/test.code"
        } else {
#line 2 "tests/12__error_handling/005__else_block/test.code"
            int32_t __003__;
#line 2 "tests/12__error_handling/005__else_block/test.code"
            {
#line 3 "tests/12__error_handling/005__else_block/test.code"
                __003__ = __001__.error.code - 42;
#line 4 "tests/12__error_handling/005__else_block/test.code"
            }
#line 2 "tests/12__error_handling/005__else_block/test.code"
            __002__ = __003__;
#line 4 "tests/12__error_handling/005__else_block/test.code"
        }
#line 2 "tests/12__error_handling/005__else_block/test.code"
        return __002__;
#line 4 "tests/12__error_handling/005__else_block/test.code"
    }
#line 5 "tests/12__error_handling/005__else_block/test.code"
}

#line 11 "tests/12__error_handling/005__else_block/test.code"
struct test_Result__11_36 test__increment(int32_t value) {
#line 12 "tests/12__error_handling/005__else_block/test.code"
    if (value > 10) {
#line 13 "tests/12__error_handling/005__else_block/test.code"
        {
#line 13 "tests/12__error_handling/005__else_block/test.code"
            struct test_Error __001__ = (struct test_Error){.code = 42};
#line 13 "tests/12__error_handling/005__else_block/test.code"
            return (struct test_Result__11_36){.success = false, .error = __001__};
#line 13 "tests/12__error_handling/005__else_block/test.code"
        }
#line 14 "tests/12__error_handling/005__else_block/test.code"
    }
#line 15 "tests/12__error_handling/005__else_block/test.code"
    {
#line 15 "tests/12__error_handling/005__else_block/test.code"
        struct test_Result__11_36 __002__ = (struct test_Result__11_36){.success = true, .value = value + 1};
#line 15 "tests/12__error_handling/005__else_block/test.code"
        return __002__;
#line 15 "tests/12__error_handling/005__else_block/test.code"
    }
#line 16 "tests/12__error_handling/005__else_block/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

