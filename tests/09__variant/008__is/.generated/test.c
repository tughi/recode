#include "test.h"

void *malloc(uintmax_t size);

#line 6 "tests/09__variant/008__is/test.code"
int32_t test__main() {
#line 7 "tests/09__variant/008__is/test.code"
    struct test_Value value = (struct test_Value){.variant = 2, .variant_2 = 42};
#line 9 "tests/09__variant/008__is/test.code"
    if (value.variant == 2) {
#line 10 "tests/09__variant/008__is/test.code"
        {
#line 10 "tests/09__variant/008__is/test.code"
            int32_t __001__ = 0;
#line 10 "tests/09__variant/008__is/test.code"
            return __001__;
#line 10 "tests/09__variant/008__is/test.code"
        }
#line 11 "tests/09__variant/008__is/test.code"
    }
#line 13 "tests/09__variant/008__is/test.code"
    {
#line 13 "tests/09__variant/008__is/test.code"
        int32_t __002__ = 1;
#line 13 "tests/09__variant/008__is/test.code"
        return __002__;
#line 13 "tests/09__variant/008__is/test.code"
    }
#line 14 "tests/09__variant/008__is/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

