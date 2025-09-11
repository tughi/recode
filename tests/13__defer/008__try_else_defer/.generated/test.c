#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/13__defer/008__try_else_defer/test.code"
int32_t test__main() {
#line 2 "tests/13__defer/008__try_else_defer/test.code"
    bool executed = false;
#line 4 "tests/13__defer/008__try_else_defer/test.code"
    {
#line 4 "tests/13__defer/008__try_else_defer/test.code"
        struct test_Result__11_27 __001__ = test__raise_forty_two();
#line 4 "tests/13__defer/008__try_else_defer/test.code"
        int32_t __002__;
#line 4 "tests/13__defer/008__try_else_defer/test.code"
        if (__001__.success) {
#line 4 "tests/13__defer/008__try_else_defer/test.code"
            __002__ = __001__.value;
#line 4 "tests/13__defer/008__try_else_defer/test.code"
        } else {
#line 4 "tests/13__defer/008__try_else_defer/test.code"
            int32_t __003__;
#line 4 "tests/13__defer/008__try_else_defer/test.code"
            {
#line 5 "tests/13__defer/008__try_else_defer/test.code"
                int32_t value = __001__.error - 42;
#line 7 "tests/13__defer/008__try_else_defer/test.code"
                __003__ = value;
#line 6 "tests/13__defer/008__try_else_defer/test.code"
                value = 13;
#line 8 "tests/13__defer/008__try_else_defer/test.code"
            }
#line 4 "tests/13__defer/008__try_else_defer/test.code"
            __002__ = __003__;
#line 8 "tests/13__defer/008__try_else_defer/test.code"
        }
#line 3 "tests/13__defer/008__try_else_defer/test.code"
        executed = true;
#line 4 "tests/13__defer/008__try_else_defer/test.code"
        return __002__;
#line 8 "tests/13__defer/008__try_else_defer/test.code"
    }
#line 9 "tests/13__defer/008__try_else_defer/test.code"
}

#line 11 "tests/13__defer/008__try_else_defer/test.code"
struct test_Result__11_27 test__raise_forty_two() {
#line 12 "tests/13__defer/008__try_else_defer/test.code"
    int32_t value = 42;
#line 14 "tests/13__defer/008__try_else_defer/test.code"
    {
#line 14 "tests/13__defer/008__try_else_defer/test.code"
        int32_t __001__ = value;
#line 13 "tests/13__defer/008__try_else_defer/test.code"
        value = 0;
#line 14 "tests/13__defer/008__try_else_defer/test.code"
        return (struct test_Result__11_27){.success = false, .error = __001__};
#line 14 "tests/13__defer/008__try_else_defer/test.code"
    }
#line 15 "tests/13__defer/008__try_else_defer/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

