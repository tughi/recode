#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/12__error_handling/004__else_return/test.code"
int32_t test__main() {
#line 2 "tests/12__error_handling/004__else_return/test.code"
    int32_t result;
#line 2 "tests/12__error_handling/004__else_return/test.code"
    {
#line 2 "tests/12__error_handling/004__else_return/test.code"
        struct test_Result__12 __001__ = test__increment(13);
#line 2 "tests/12__error_handling/004__else_return/test.code"
        int32_t __002__;
#line 2 "tests/12__error_handling/004__else_return/test.code"
        if (__001__.success) {
#line 2 "tests/12__error_handling/004__else_return/test.code"
            __002__ = __001__.value;
#line 2 "tests/12__error_handling/004__else_return/test.code"
        } else {
#line 2 "tests/12__error_handling/004__else_return/test.code"
            int32_t __003__;
#line 2 "tests/12__error_handling/004__else_return/test.code"
            {
#line 3 "tests/12__error_handling/004__else_return/test.code"
                return __001__.error.code - 42;
#line 4 "tests/12__error_handling/004__else_return/test.code"
            }
#line 2 "tests/12__error_handling/004__else_return/test.code"
            __002__ = __003__;
#line 4 "tests/12__error_handling/004__else_return/test.code"
        }
#line 2 "tests/12__error_handling/004__else_return/test.code"
        result = __002__;
#line 4 "tests/12__error_handling/004__else_return/test.code"
    }
#line 5 "tests/12__error_handling/004__else_return/test.code"
    return result;
#line 6 "tests/12__error_handling/004__else_return/test.code"
}

#line 12 "tests/12__error_handling/004__else_return/test.code"
struct test_Result__12 test__increment(int32_t value) {
#line 13 "tests/12__error_handling/004__else_return/test.code"
    if (value > 10) {
#line 14 "tests/12__error_handling/004__else_return/test.code"
        return (struct test_Result__12){.success = false, .error = (struct test_Error){.code = 42}};
#line 15 "tests/12__error_handling/004__else_return/test.code"
    }
#line 16 "tests/12__error_handling/004__else_return/test.code"
    return (struct test_Result__12){.success = true, .value = value + 1};
#line 17 "tests/12__error_handling/004__else_return/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

