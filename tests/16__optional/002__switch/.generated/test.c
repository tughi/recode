#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/16__optional/002__switch/test.code"
int32_t test__main() {
#line 2 "tests/16__optional/002__switch/test.code"
    struct i32__opt value = (struct i32__opt){.variant = 1, .variant_1 = 42};
#line 4 "tests/16__optional/002__switch/test.code"
    struct i32__opt __switch_4_value__ = value;
#line 5 "tests/16__optional/002__switch/test.code"
    if (__switch_4_value__.variant == 1) {
#line 6 "tests/16__optional/002__switch/test.code"
        if (__switch_4_value__.variant_1 != 42) {
#line 7 "tests/16__optional/002__switch/test.code"
            {
#line 7 "tests/16__optional/002__switch/test.code"
                int32_t __001__ = 1;
#line 7 "tests/16__optional/002__switch/test.code"
                return __001__;
#line 7 "tests/16__optional/002__switch/test.code"
            }
#line 8 "tests/16__optional/002__switch/test.code"
        }
#line 9 "tests/16__optional/002__switch/test.code"
    }
#line 10 "tests/16__optional/002__switch/test.code"
    else if (__switch_4_value__.variant == 0) {
#line 11 "tests/16__optional/002__switch/test.code"
        {
#line 11 "tests/16__optional/002__switch/test.code"
            int32_t __002__ = 2;
#line 11 "tests/16__optional/002__switch/test.code"
            return __002__;
#line 11 "tests/16__optional/002__switch/test.code"
        }
#line 12 "tests/16__optional/002__switch/test.code"
    }
#line 15 "tests/16__optional/002__switch/test.code"
    struct i32__opt empty = (struct i32__opt){.variant = 0};
#line 17 "tests/16__optional/002__switch/test.code"
    struct i32__opt __switch_17_value__ = empty;
#line 18 "tests/16__optional/002__switch/test.code"
    if (__switch_17_value__.variant == 1) {
#line 19 "tests/16__optional/002__switch/test.code"
        {
#line 19 "tests/16__optional/002__switch/test.code"
            int32_t __003__ = 3;
#line 19 "tests/16__optional/002__switch/test.code"
            return __003__;
#line 19 "tests/16__optional/002__switch/test.code"
        }
#line 20 "tests/16__optional/002__switch/test.code"
    }
#line 21 "tests/16__optional/002__switch/test.code"
    else if (__switch_17_value__.variant == 0) {
#line 22 "tests/16__optional/002__switch/test.code"
    }
#line 25 "tests/16__optional/002__switch/test.code"
    {
#line 25 "tests/16__optional/002__switch/test.code"
        int32_t __004__ = 0;
#line 25 "tests/16__optional/002__switch/test.code"
        return __004__;
#line 25 "tests/16__optional/002__switch/test.code"
    }
#line 26 "tests/16__optional/002__switch/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

