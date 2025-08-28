#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/12__error_handling/006__raising_without_return/test.code"
int32_t test__main() {
#line 2 "tests/12__error_handling/006__raising_without_return/test.code"
    {
#line 2 "tests/12__error_handling/006__raising_without_return/test.code"
        struct test_Result__8 __002__ = test__auto_raise_error(false);
#line 2 "tests/12__error_handling/006__raising_without_return/test.code"
        if (__002__.success) {} else {
#line 2 "tests/12__error_handling/006__raising_without_return/test.code"
            {
#line 3 "tests/12__error_handling/006__raising_without_return/test.code"
                {
#line 3 "tests/12__error_handling/006__raising_without_return/test.code"
                    int32_t __001__ = __002__.error.code;
#line 3 "tests/12__error_handling/006__raising_without_return/test.code"
                    return __001__;
#line 3 "tests/12__error_handling/006__raising_without_return/test.code"
                }
#line 4 "tests/12__error_handling/006__raising_without_return/test.code"
            }
#line 4 "tests/12__error_handling/006__raising_without_return/test.code"
        }
#line 2 "tests/12__error_handling/006__raising_without_return/test.code"
        ;
#line 4 "tests/12__error_handling/006__raising_without_return/test.code"
    }
#line 5 "tests/12__error_handling/006__raising_without_return/test.code"
    {
#line 5 "tests/12__error_handling/006__raising_without_return/test.code"
        int32_t __003__ = 0;
#line 5 "tests/12__error_handling/006__raising_without_return/test.code"
        return __003__;
#line 5 "tests/12__error_handling/006__raising_without_return/test.code"
    }
#line 6 "tests/12__error_handling/006__raising_without_return/test.code"
}

#line 8 "tests/12__error_handling/006__raising_without_return/test.code"
struct test_Result__8 test__auto_raise_error(bool condition) {
#line 9 "tests/12__error_handling/006__raising_without_return/test.code"
    {
#line 9 "tests/12__error_handling/006__raising_without_return/test.code"
        struct test_Result__8 __001__ = test__raise_error(condition);
#line 9 "tests/12__error_handling/006__raising_without_return/test.code"
        if (__001__.success) {} else return (struct test_Result__8){.success = false, .error = __001__.error};
#line 9 "tests/12__error_handling/006__raising_without_return/test.code"
        ;
#line 9 "tests/12__error_handling/006__raising_without_return/test.code"
    }
#line 10 "tests/12__error_handling/006__raising_without_return/test.code"
    {
#line 10 "tests/12__error_handling/006__raising_without_return/test.code"
        struct test_Result__8 __002__ = (struct test_Result__8){.success = true};
#line 10 "tests/12__error_handling/006__raising_without_return/test.code"
        return __002__;
#line 10 "tests/12__error_handling/006__raising_without_return/test.code"
    }
#line 11 "tests/12__error_handling/006__raising_without_return/test.code"
}

#line 13 "tests/12__error_handling/006__raising_without_return/test.code"
struct test_Result__8 test__raise_error(bool condition) {
#line 14 "tests/12__error_handling/006__raising_without_return/test.code"
    if (condition) {
#line 15 "tests/12__error_handling/006__raising_without_return/test.code"
        {
#line 15 "tests/12__error_handling/006__raising_without_return/test.code"
            struct test_Error __001__ = (struct test_Error){.code = 42};
#line 15 "tests/12__error_handling/006__raising_without_return/test.code"
            return (struct test_Result__8){.success = false, .error = __001__};
#line 15 "tests/12__error_handling/006__raising_without_return/test.code"
        }
#line 16 "tests/12__error_handling/006__raising_without_return/test.code"
    }
#line 17 "tests/12__error_handling/006__raising_without_return/test.code"
    {
#line 17 "tests/12__error_handling/006__raising_without_return/test.code"
        struct test_Result__8 __002__ = (struct test_Result__8){.success = true};
#line 17 "tests/12__error_handling/006__raising_without_return/test.code"
        return __002__;
#line 17 "tests/12__error_handling/006__raising_without_return/test.code"
    }
#line 18 "tests/12__error_handling/006__raising_without_return/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

