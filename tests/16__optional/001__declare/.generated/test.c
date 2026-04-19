#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/16__optional/001__declare/test.code"
int32_t test__main() {
#line 2 "tests/16__optional/001__declare/test.code"
    struct i32__opt has_value = (struct i32__opt){.variant = 1, .variant_1 = 42};
#line 3 "tests/16__optional/001__declare/test.code"
    struct i32__opt no_value = (struct i32__opt){.variant = 0};
#line 5 "tests/16__optional/001__declare/test.code"
    if (has_value.variant == 1) {
#line 6 "tests/16__optional/001__declare/test.code"
        if (no_value.variant == 0) {
#line 7 "tests/16__optional/001__declare/test.code"
            {
#line 7 "tests/16__optional/001__declare/test.code"
                int32_t __001__ = has_value.variant_1 - 42;
#line 7 "tests/16__optional/001__declare/test.code"
                return __001__;
#line 7 "tests/16__optional/001__declare/test.code"
            }
#line 8 "tests/16__optional/001__declare/test.code"
        }
#line 9 "tests/16__optional/001__declare/test.code"
    }
#line 11 "tests/16__optional/001__declare/test.code"
    {
#line 11 "tests/16__optional/001__declare/test.code"
        int32_t __002__ = 1;
#line 11 "tests/16__optional/001__declare/test.code"
        return __002__;
#line 11 "tests/16__optional/001__declare/test.code"
    }
#line 12 "tests/16__optional/001__declare/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

