#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/12__error_handling/003__auto_propagation/test.code"
int32_t test__main() {
#line 2 "tests/12__error_handling/003__auto_propagation/test.code"
    {
#line 2 "tests/12__error_handling/003__auto_propagation/test.code"
        struct test_Result__9_36 __001__ = test__count_from(0);
#line 2 "tests/12__error_handling/003__auto_propagation/test.code"
        int32_t __002__;
#line 2 "tests/12__error_handling/003__auto_propagation/test.code"
        if (__001__.success) {
#line 2 "tests/12__error_handling/003__auto_propagation/test.code"
            __002__ = __001__.value;
#line 2 "tests/12__error_handling/003__auto_propagation/test.code"
        } else {
#line 2 "tests/12__error_handling/003__auto_propagation/test.code"
            __002__ = __001__.error.code - 42;
#line 2 "tests/12__error_handling/003__auto_propagation/test.code"
        }
#line 2 "tests/12__error_handling/003__auto_propagation/test.code"
        return __002__;
#line 2 "tests/12__error_handling/003__auto_propagation/test.code"
    }
#line 3 "tests/12__error_handling/003__auto_propagation/test.code"
}

#line 9 "tests/12__error_handling/003__auto_propagation/test.code"
struct test_Result__9_36 test__increment(int32_t value) {
#line 10 "tests/12__error_handling/003__auto_propagation/test.code"
    if (value > 10) {
#line 11 "tests/12__error_handling/003__auto_propagation/test.code"
        {
#line 11 "tests/12__error_handling/003__auto_propagation/test.code"
            struct test_Error __001__ = (struct test_Error){.code = 42};
#line 11 "tests/12__error_handling/003__auto_propagation/test.code"
            return (struct test_Result__9_36){.success = false, .error = __001__};
#line 11 "tests/12__error_handling/003__auto_propagation/test.code"
        }
#line 12 "tests/12__error_handling/003__auto_propagation/test.code"
    }
#line 13 "tests/12__error_handling/003__auto_propagation/test.code"
    {
#line 13 "tests/12__error_handling/003__auto_propagation/test.code"
        struct test_Result__9_36 __002__ = (struct test_Result__9_36){.success = true, .value = value + 1};
#line 13 "tests/12__error_handling/003__auto_propagation/test.code"
        return __002__;
#line 13 "tests/12__error_handling/003__auto_propagation/test.code"
    }
#line 14 "tests/12__error_handling/003__auto_propagation/test.code"
}

#line 16 "tests/12__error_handling/003__auto_propagation/test.code"
struct test_Result__9_36 test__count_from(int32_t value) {
#line 17 "tests/12__error_handling/003__auto_propagation/test.code"
    int32_t new_value = value;
#line 18 "tests/12__error_handling/003__auto_propagation/test.code"
    while (new_value < 100) {
#line 19 "tests/12__error_handling/003__auto_propagation/test.code"
        {
#line 19 "tests/12__error_handling/003__auto_propagation/test.code"
            struct test_Result__9_36 __001__ = test__increment(new_value);
#line 19 "tests/12__error_handling/003__auto_propagation/test.code"
            if (__001__.success) {} else {
#line 19 "tests/12__error_handling/003__auto_propagation/test.code"
                return (struct test_Result__9_36){.success = false, .error = __001__.error};
#line 19 "tests/12__error_handling/003__auto_propagation/test.code"
            }
#line 19 "tests/12__error_handling/003__auto_propagation/test.code"
            new_value = __001__.value;
#line 19 "tests/12__error_handling/003__auto_propagation/test.code"
        }
#line 20 "tests/12__error_handling/003__auto_propagation/test.code"
    }
#line 21 "tests/12__error_handling/003__auto_propagation/test.code"
    {
#line 21 "tests/12__error_handling/003__auto_propagation/test.code"
        struct test_Result__9_36 __002__ = (struct test_Result__9_36){.success = true, .value = new_value};
#line 21 "tests/12__error_handling/003__auto_propagation/test.code"
        return __002__;
#line 21 "tests/12__error_handling/003__auto_propagation/test.code"
    }
#line 22 "tests/12__error_handling/003__auto_propagation/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

