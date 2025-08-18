#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/13__defer/007__execute_before_raise/test.code"
int32_t test__main() {
#line 2 "tests/13__defer/007__execute_before_raise/test.code"
    {
#line 2 "tests/13__defer/007__execute_before_raise/test.code"
        struct test_Result__5 __001__ = test__raise_forty_two();
#line 2 "tests/13__defer/007__execute_before_raise/test.code"
        int32_t __002__;
#line 2 "tests/13__defer/007__execute_before_raise/test.code"
        if (__001__.success) {
#line 2 "tests/13__defer/007__execute_before_raise/test.code"
            __002__ = __001__.value;
#line 2 "tests/13__defer/007__execute_before_raise/test.code"
        } else {
#line 2 "tests/13__defer/007__execute_before_raise/test.code"
            __002__ = __001__.error - 42;
#line 2 "tests/13__defer/007__execute_before_raise/test.code"
        }
#line 2 "tests/13__defer/007__execute_before_raise/test.code"
        return __002__;
#line 2 "tests/13__defer/007__execute_before_raise/test.code"
    }
#line 3 "tests/13__defer/007__execute_before_raise/test.code"
}

#line 5 "tests/13__defer/007__execute_before_raise/test.code"
struct test_Result__5 test__raise_forty_two() {
#line 6 "tests/13__defer/007__execute_before_raise/test.code"
    int32_t value = 42;
#line 8 "tests/13__defer/007__execute_before_raise/test.code"
    {
#line 8 "tests/13__defer/007__execute_before_raise/test.code"
        int32_t __001__ = value;
#line 7 "tests/13__defer/007__execute_before_raise/test.code"
        value = 0;
#line 8 "tests/13__defer/007__execute_before_raise/test.code"
        return (struct test_Result__5){.success = false, .error = __001__};
#line 8 "tests/13__defer/007__execute_before_raise/test.code"
    }
#line 9 "tests/13__defer/007__execute_before_raise/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

