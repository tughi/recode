#include "test.h"

void *malloc(uintmax_t size);

#line 11 "tests/09__variant/006__switch/test.code"
int32_t test__main() {
#line 12 "tests/09__variant/006__switch/test.code"
    struct test_Value value = (struct test_Value){.variant = 2, .variant_2 = (struct test_Integer){.variant = 2, .variant_2 = 42}};
#line 14 "tests/09__variant/006__switch/test.code"
    for (;;) {
#line 15 "tests/09__variant/006__switch/test.code"
        struct test_Value __switch_15_value__ = value;
#line 16 "tests/09__variant/006__switch/test.code"
        if (__switch_15_value__.variant == 1) {
#line 17 "tests/09__variant/006__switch/test.code"
            {
#line 17 "tests/09__variant/006__switch/test.code"
                int32_t __001__ = 1;
#line 17 "tests/09__variant/006__switch/test.code"
                return __001__;
#line 17 "tests/09__variant/006__switch/test.code"
            }
#line 18 "tests/09__variant/006__switch/test.code"
        }
#line 19 "tests/09__variant/006__switch/test.code"
        else if (__switch_15_value__.variant == 2) {
#line 20 "tests/09__variant/006__switch/test.code"
            struct test_Integer __switch_20_value__ = __switch_15_value__.variant_2;
#line 21 "tests/09__variant/006__switch/test.code"
            if (__switch_20_value__.variant == 1) {
#line 22 "tests/09__variant/006__switch/test.code"
                {
#line 22 "tests/09__variant/006__switch/test.code"
                    int32_t __002__ = 2;
#line 22 "tests/09__variant/006__switch/test.code"
                    return __002__;
#line 22 "tests/09__variant/006__switch/test.code"
                }
#line 23 "tests/09__variant/006__switch/test.code"
            }
#line 24 "tests/09__variant/006__switch/test.code"
            else if (__switch_20_value__.variant == 2) {
#line 25 "tests/09__variant/006__switch/test.code"
                if (__switch_20_value__.variant_2 != 42) {
#line 26 "tests/09__variant/006__switch/test.code"
                    {
#line 26 "tests/09__variant/006__switch/test.code"
                        int32_t __003__ = 3;
#line 26 "tests/09__variant/006__switch/test.code"
                        return __003__;
#line 26 "tests/09__variant/006__switch/test.code"
                    }
#line 27 "tests/09__variant/006__switch/test.code"
                }
#line 28 "tests/09__variant/006__switch/test.code"
                break;
#line 29 "tests/09__variant/006__switch/test.code"
            }
#line 30 "tests/09__variant/006__switch/test.code"
            else if (__switch_20_value__.variant == 0) {
#line 31 "tests/09__variant/006__switch/test.code"
                {
#line 31 "tests/09__variant/006__switch/test.code"
                    int32_t __004__ = 4;
#line 31 "tests/09__variant/006__switch/test.code"
                    return __004__;
#line 31 "tests/09__variant/006__switch/test.code"
                }
#line 32 "tests/09__variant/006__switch/test.code"
            }
#line 34 "tests/09__variant/006__switch/test.code"
        }
#line 35 "tests/09__variant/006__switch/test.code"
        else if (__switch_15_value__.variant == 0) {
#line 36 "tests/09__variant/006__switch/test.code"
            {
#line 36 "tests/09__variant/006__switch/test.code"
                int32_t __005__ = 5;
#line 36 "tests/09__variant/006__switch/test.code"
                return __005__;
#line 36 "tests/09__variant/006__switch/test.code"
            }
#line 37 "tests/09__variant/006__switch/test.code"
        }
#line 40 "tests/09__variant/006__switch/test.code"
        {
#line 40 "tests/09__variant/006__switch/test.code"
            int32_t __006__ = 6;
#line 40 "tests/09__variant/006__switch/test.code"
            return __006__;
#line 40 "tests/09__variant/006__switch/test.code"
        }
#line 41 "tests/09__variant/006__switch/test.code"
    }
#line 43 "tests/09__variant/006__switch/test.code"
    {
#line 43 "tests/09__variant/006__switch/test.code"
        int32_t __007__ = 0;
#line 43 "tests/09__variant/006__switch/test.code"
        return __007__;
#line 43 "tests/09__variant/006__switch/test.code"
    }
#line 44 "tests/09__variant/006__switch/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

