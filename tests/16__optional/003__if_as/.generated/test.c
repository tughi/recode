#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/16__optional/003__if_as/test.code"
int32_t test__main() {
#line 2 "tests/16__optional/003__if_as/test.code"
    struct i32__opt value = (struct i32__opt){.variant = 1, .variant_1 = 99};
#line 4 "tests/16__optional/003__if_as/test.code"
    if (value.variant == 1) {
#line 5 "tests/16__optional/003__if_as/test.code"
        if (value.variant_1 != 99) {
#line 6 "tests/16__optional/003__if_as/test.code"
            {
#line 6 "tests/16__optional/003__if_as/test.code"
                int32_t __001__ = 1;
#line 6 "tests/16__optional/003__if_as/test.code"
                return __001__;
#line 6 "tests/16__optional/003__if_as/test.code"
            }
#line 7 "tests/16__optional/003__if_as/test.code"
        }
#line 8 "tests/16__optional/003__if_as/test.code"
    } else {
#line 9 "tests/16__optional/003__if_as/test.code"
        {
#line 9 "tests/16__optional/003__if_as/test.code"
            int32_t __002__ = 2;
#line 9 "tests/16__optional/003__if_as/test.code"
            return __002__;
#line 9 "tests/16__optional/003__if_as/test.code"
        }
#line 10 "tests/16__optional/003__if_as/test.code"
    }
#line 12 "tests/16__optional/003__if_as/test.code"
    struct i32__opt empty = (struct i32__opt){.variant = 0};
#line 14 "tests/16__optional/003__if_as/test.code"
    if (empty.variant == 1) {
#line 15 "tests/16__optional/003__if_as/test.code"
        {
#line 15 "tests/16__optional/003__if_as/test.code"
            int32_t __003__ = 3;
#line 15 "tests/16__optional/003__if_as/test.code"
            return __003__;
#line 15 "tests/16__optional/003__if_as/test.code"
        }
#line 16 "tests/16__optional/003__if_as/test.code"
    }
#line 18 "tests/16__optional/003__if_as/test.code"
    if (empty.variant == 0) {
#line 19 "tests/16__optional/003__if_as/test.code"
    } else {
#line 20 "tests/16__optional/003__if_as/test.code"
        {
#line 20 "tests/16__optional/003__if_as/test.code"
            int32_t __004__ = 4;
#line 20 "tests/16__optional/003__if_as/test.code"
            return __004__;
#line 20 "tests/16__optional/003__if_as/test.code"
        }
#line 21 "tests/16__optional/003__if_as/test.code"
    }
#line 23 "tests/16__optional/003__if_as/test.code"
    {
#line 23 "tests/16__optional/003__if_as/test.code"
        int32_t __005__ = 0;
#line 23 "tests/16__optional/003__if_as/test.code"
        return __005__;
#line 23 "tests/16__optional/003__if_as/test.code"
    }
#line 24 "tests/16__optional/003__if_as/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

