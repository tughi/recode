#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/16__optional/005__return_type/test.code"
struct i32__opt test__find__anon__anon(int32_t value, int32_t target) {
#line 2 "tests/16__optional/005__return_type/test.code"
    if (value == target) {
#line 3 "tests/16__optional/005__return_type/test.code"
        {
#line 3 "tests/16__optional/005__return_type/test.code"
            struct i32__opt __001__ = (struct i32__opt){.variant = 1, .variant_1 = value};
#line 3 "tests/16__optional/005__return_type/test.code"
            return __001__;
#line 3 "tests/16__optional/005__return_type/test.code"
        }
#line 4 "tests/16__optional/005__return_type/test.code"
    }
#line 5 "tests/16__optional/005__return_type/test.code"
    {
#line 5 "tests/16__optional/005__return_type/test.code"
        struct i32__opt __002__ = (struct i32__opt){.variant = 0};
#line 5 "tests/16__optional/005__return_type/test.code"
        return __002__;
#line 5 "tests/16__optional/005__return_type/test.code"
    }
#line 6 "tests/16__optional/005__return_type/test.code"
}

#line 8 "tests/16__optional/005__return_type/test.code"
int32_t test__main() {
#line 9 "tests/16__optional/005__return_type/test.code"
    struct i32__opt found = test__find__anon__anon(42, 42);
#line 10 "tests/16__optional/005__return_type/test.code"
    struct i32__opt not_found = test__find__anon__anon(1, 2);
#line 12 "tests/16__optional/005__return_type/test.code"
    if (found.variant == 1) {
#line 13 "tests/16__optional/005__return_type/test.code"
        if (found.variant_1 != 42) {
#line 14 "tests/16__optional/005__return_type/test.code"
            {
#line 14 "tests/16__optional/005__return_type/test.code"
                int32_t __001__ = 1;
#line 14 "tests/16__optional/005__return_type/test.code"
                return __001__;
#line 14 "tests/16__optional/005__return_type/test.code"
            }
#line 15 "tests/16__optional/005__return_type/test.code"
        }
#line 16 "tests/16__optional/005__return_type/test.code"
    } else {
#line 17 "tests/16__optional/005__return_type/test.code"
        {
#line 17 "tests/16__optional/005__return_type/test.code"
            int32_t __002__ = 2;
#line 17 "tests/16__optional/005__return_type/test.code"
            return __002__;
#line 17 "tests/16__optional/005__return_type/test.code"
        }
#line 18 "tests/16__optional/005__return_type/test.code"
    }
#line 20 "tests/16__optional/005__return_type/test.code"
    if (not_found.variant == 0) {
#line 21 "tests/16__optional/005__return_type/test.code"
    } else {
#line 22 "tests/16__optional/005__return_type/test.code"
        {
#line 22 "tests/16__optional/005__return_type/test.code"
            int32_t __003__ = 3;
#line 22 "tests/16__optional/005__return_type/test.code"
            return __003__;
#line 22 "tests/16__optional/005__return_type/test.code"
        }
#line 23 "tests/16__optional/005__return_type/test.code"
    }
#line 25 "tests/16__optional/005__return_type/test.code"
    {
#line 25 "tests/16__optional/005__return_type/test.code"
        int32_t __004__ = 0;
#line 25 "tests/16__optional/005__return_type/test.code"
        return __004__;
#line 25 "tests/16__optional/005__return_type/test.code"
    }
#line 26 "tests/16__optional/005__return_type/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

