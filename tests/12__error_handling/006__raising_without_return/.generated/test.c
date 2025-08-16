#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/12__error_handling/006__raising_without_return/test.code"
int32_t test__main() {
#line 2 "tests/12__error_handling/006__raising_without_return/test.code"
    {
#line 2 "tests/12__error_handling/006__raising_without_return/test.code"
        struct test_Result__8 __001__ = test__auto_raise_error(false);
#line 2 "tests/12__error_handling/006__raising_without_return/test.code"
        if (__001__.success) {} else {
#line 2 "tests/12__error_handling/006__raising_without_return/test.code"
            {
#line 3 "tests/12__error_handling/006__raising_without_return/test.code"
                return __001__.error.code;
#line 4 "tests/12__error_handling/006__raising_without_return/test.code"
            }
#line 4 "tests/12__error_handling/006__raising_without_return/test.code"
        }
#line 2 "tests/12__error_handling/006__raising_without_return/test.code"
        ;
#line 4 "tests/12__error_handling/006__raising_without_return/test.code"
    }
#line 5 "tests/12__error_handling/006__raising_without_return/test.code"
    return 0;
#line 6 "tests/12__error_handling/006__raising_without_return/test.code"
}

#line 8 "tests/12__error_handling/006__raising_without_return/test.code"
struct test_Result__8 test__auto_raise_error(bool condition) {
#line 9 "tests/12__error_handling/006__raising_without_return/test.code"
    {
#line 9 "tests/12__error_handling/006__raising_without_return/test.code"
        struct test_Result__13 __001__ = test__raise_error(condition);
#line 9 "tests/12__error_handling/006__raising_without_return/test.code"
        if (__001__.success) {} else return (struct test_Result__8){.success = false, .error = __001__.error};
#line 9 "tests/12__error_handling/006__raising_without_return/test.code"
        ;
#line 9 "tests/12__error_handling/006__raising_without_return/test.code"
    }
#line 10 "tests/12__error_handling/006__raising_without_return/test.code"
    return (struct test_Result__8){.success = true};
#line 11 "tests/12__error_handling/006__raising_without_return/test.code"
}

#line 13 "tests/12__error_handling/006__raising_without_return/test.code"
struct test_Result__13 test__raise_error(bool condition) {
#line 14 "tests/12__error_handling/006__raising_without_return/test.code"
    if (condition) {
#line 15 "tests/12__error_handling/006__raising_without_return/test.code"
        return (struct test_Result__13){.success = false, .error = (struct test_Error){.code = 42}};
#line 16 "tests/12__error_handling/006__raising_without_return/test.code"
    }
#line 17 "tests/12__error_handling/006__raising_without_return/test.code"
    return (struct test_Result__13){.success = true};
#line 18 "tests/12__error_handling/006__raising_without_return/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

