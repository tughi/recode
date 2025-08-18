#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/12__error_handling/004__else_return/test.code"
int32_t test__main() {
#line 2 "tests/12__error_handling/004__else_return/test.code"
    int32_t result;
#line 2 "tests/12__error_handling/004__else_return/test.code"
    {
#line 2 "tests/12__error_handling/004__else_return/test.code"
        struct test_Result__12 __002__ = test__increment(13);
#line 2 "tests/12__error_handling/004__else_return/test.code"
        int32_t __003__;
#line 2 "tests/12__error_handling/004__else_return/test.code"
        if (__002__.success) {
#line 2 "tests/12__error_handling/004__else_return/test.code"
            __003__ = __002__.value;
#line 2 "tests/12__error_handling/004__else_return/test.code"
        } else {
#line 2 "tests/12__error_handling/004__else_return/test.code"
            int32_t __004__;
#line 2 "tests/12__error_handling/004__else_return/test.code"
            {
#line 3 "tests/12__error_handling/004__else_return/test.code"
                {
#line 3 "tests/12__error_handling/004__else_return/test.code"
                    int32_t __001__ = __002__.error.code - 42;
#line 3 "tests/12__error_handling/004__else_return/test.code"
                    return __001__;
#line 3 "tests/12__error_handling/004__else_return/test.code"
                }
#line 4 "tests/12__error_handling/004__else_return/test.code"
            }
#line 2 "tests/12__error_handling/004__else_return/test.code"
            __003__ = __004__;
#line 4 "tests/12__error_handling/004__else_return/test.code"
        }
#line 2 "tests/12__error_handling/004__else_return/test.code"
        result = __003__;
#line 4 "tests/12__error_handling/004__else_return/test.code"
    }
#line 5 "tests/12__error_handling/004__else_return/test.code"
    {
#line 5 "tests/12__error_handling/004__else_return/test.code"
        int32_t __005__ = result;
#line 5 "tests/12__error_handling/004__else_return/test.code"
        return __005__;
#line 5 "tests/12__error_handling/004__else_return/test.code"
    }
#line 6 "tests/12__error_handling/004__else_return/test.code"
}

#line 12 "tests/12__error_handling/004__else_return/test.code"
struct test_Result__12 test__increment(int32_t value) {
#line 13 "tests/12__error_handling/004__else_return/test.code"
    if (value > 10) {
#line 14 "tests/12__error_handling/004__else_return/test.code"
        {
#line 14 "tests/12__error_handling/004__else_return/test.code"
            struct test_Error __001__ = (struct test_Error){.code = 42};
#line 14 "tests/12__error_handling/004__else_return/test.code"
            return (struct test_Result__12){.success = false, .error = __001__};
#line 14 "tests/12__error_handling/004__else_return/test.code"
        }
#line 15 "tests/12__error_handling/004__else_return/test.code"
    }
#line 16 "tests/12__error_handling/004__else_return/test.code"
    {
#line 16 "tests/12__error_handling/004__else_return/test.code"
        struct test_Result__12 __002__ = (struct test_Result__12){.success = true, .value = value + 1};
#line 16 "tests/12__error_handling/004__else_return/test.code"
        return __002__;
#line 16 "tests/12__error_handling/004__else_return/test.code"
    }
#line 17 "tests/12__error_handling/004__else_return/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

