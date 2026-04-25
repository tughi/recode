#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/13__defer/010__defer_with_auto_propagation_raise/test.code"
int32_t test__main() {
#line 2 "tests/13__defer/010__defer_with_auto_propagation_raise/test.code"
    {
#line 2 "tests/13__defer/010__defer_with_auto_propagation_raise/test.code"
        struct test_Result__5_21 __001__ = test__test();
#line 2 "tests/13__defer/010__defer_with_auto_propagation_raise/test.code"
        int32_t __002__;
#line 2 "tests/13__defer/010__defer_with_auto_propagation_raise/test.code"
        if (__001__.success) {
#line 2 "tests/13__defer/010__defer_with_auto_propagation_raise/test.code"
            __002__ = __001__.value;
#line 2 "tests/13__defer/010__defer_with_auto_propagation_raise/test.code"
        } else {
#line 2 "tests/13__defer/010__defer_with_auto_propagation_raise/test.code"
            __002__ = __001__.error - 42;
#line 2 "tests/13__defer/010__defer_with_auto_propagation_raise/test.code"
        }
#line 2 "tests/13__defer/010__defer_with_auto_propagation_raise/test.code"
        return __002__;
#line 2 "tests/13__defer/010__defer_with_auto_propagation_raise/test.code"
    }
#line 3 "tests/13__defer/010__defer_with_auto_propagation_raise/test.code"
}

#line 5 "tests/13__defer/010__defer_with_auto_propagation_raise/test.code"
struct test_Result__5_21 test__raises_42() {
#line 6 "tests/13__defer/010__defer_with_auto_propagation_raise/test.code"
    {
#line 6 "tests/13__defer/010__defer_with_auto_propagation_raise/test.code"
        int32_t __001__ = 42;
#line 6 "tests/13__defer/010__defer_with_auto_propagation_raise/test.code"
        return (struct test_Result__5_21){.success = false, .error = __001__};
#line 6 "tests/13__defer/010__defer_with_auto_propagation_raise/test.code"
    }
#line 7 "tests/13__defer/010__defer_with_auto_propagation_raise/test.code"
}

#line 9 "tests/13__defer/010__defer_with_auto_propagation_raise/test.code"
struct test_Result__5_21 test__test() {
#line 10 "tests/13__defer/010__defer_with_auto_propagation_raise/test.code"
    int32_t cleanup = 0;
#line 12 "tests/13__defer/010__defer_with_auto_propagation_raise/test.code"
    int32_t value;
#line 12 "tests/13__defer/010__defer_with_auto_propagation_raise/test.code"
    {
#line 12 "tests/13__defer/010__defer_with_auto_propagation_raise/test.code"
        struct test_Result__5_21 __001__ = test__raises_42();
#line 12 "tests/13__defer/010__defer_with_auto_propagation_raise/test.code"
        if (__001__.success) {} else {
#line 11 "tests/13__defer/010__defer_with_auto_propagation_raise/test.code"
            cleanup = 1;
#line 12 "tests/13__defer/010__defer_with_auto_propagation_raise/test.code"
            return (struct test_Result__5_21){.success = false, .error = __001__.error};
#line 12 "tests/13__defer/010__defer_with_auto_propagation_raise/test.code"
        }
#line 12 "tests/13__defer/010__defer_with_auto_propagation_raise/test.code"
        value = __001__.value;
#line 12 "tests/13__defer/010__defer_with_auto_propagation_raise/test.code"
    }
#line 13 "tests/13__defer/010__defer_with_auto_propagation_raise/test.code"
    {
#line 13 "tests/13__defer/010__defer_with_auto_propagation_raise/test.code"
        struct test_Result__5_21 __002__ = (struct test_Result__5_21){.success = true, .value = value};
#line 11 "tests/13__defer/010__defer_with_auto_propagation_raise/test.code"
        cleanup = 1;
#line 13 "tests/13__defer/010__defer_with_auto_propagation_raise/test.code"
        return __002__;
#line 13 "tests/13__defer/010__defer_with_auto_propagation_raise/test.code"
    }
#line 14 "tests/13__defer/010__defer_with_auto_propagation_raise/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

