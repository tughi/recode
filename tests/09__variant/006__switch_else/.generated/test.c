#include "test.h"

void *malloc(uintmax_t size);

#line 11 "tests/09__variant/006__switch_else/test.code"
int32_t test__main() {
#line 12 "tests/09__variant/006__switch_else/test.code"
    struct test_Value value = (struct test_Value){.variant = 2, .variant_2 = (struct test_Integer){.variant = 2, .variant_2 = 42}};
#line 14 "tests/09__variant/006__switch_else/test.code"
    struct test_Value __switch_14_value__ = value;
#line 15 "tests/09__variant/006__switch_else/test.code"
    if (__switch_14_value__.variant == 2) {
#line 16 "tests/09__variant/006__switch_else/test.code"
        {
#line 16 "tests/09__variant/006__switch_else/test.code"
            int32_t __001__ = 0;
#line 16 "tests/09__variant/006__switch_else/test.code"
            return __001__;
#line 16 "tests/09__variant/006__switch_else/test.code"
        }
#line 17 "tests/09__variant/006__switch_else/test.code"
    }
#line 18 "tests/09__variant/006__switch_else/test.code"
    else {
#line 19 "tests/09__variant/006__switch_else/test.code"
        {
#line 19 "tests/09__variant/006__switch_else/test.code"
            int32_t __002__ = 1;
#line 19 "tests/09__variant/006__switch_else/test.code"
            return __002__;
#line 19 "tests/09__variant/006__switch_else/test.code"
        }
#line 20 "tests/09__variant/006__switch_else/test.code"
    }
#line 23 "tests/09__variant/006__switch_else/test.code"
    {
#line 23 "tests/09__variant/006__switch_else/test.code"
        int32_t __003__ = 2;
#line 23 "tests/09__variant/006__switch_else/test.code"
        return __003__;
#line 23 "tests/09__variant/006__switch_else/test.code"
    }
#line 24 "tests/09__variant/006__switch_else/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

