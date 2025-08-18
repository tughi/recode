#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/01__basics/017__i32_negation/test.code"
int32_t test__main() {
#line 2 "tests/01__basics/017__i32_negation/test.code"
    int32_t value = 42;
#line 3 "tests/01__basics/017__i32_negation/test.code"
    if (value * -1 != -value) {
#line 4 "tests/01__basics/017__i32_negation/test.code"
        {
#line 4 "tests/01__basics/017__i32_negation/test.code"
            int32_t __001__ = 1;
#line 4 "tests/01__basics/017__i32_negation/test.code"
            return __001__;
#line 4 "tests/01__basics/017__i32_negation/test.code"
        }
#line 5 "tests/01__basics/017__i32_negation/test.code"
    }
#line 6 "tests/01__basics/017__i32_negation/test.code"
    {
#line 6 "tests/01__basics/017__i32_negation/test.code"
        int32_t __002__ = 0;
#line 6 "tests/01__basics/017__i32_negation/test.code"
        return __002__;
#line 6 "tests/01__basics/017__i32_negation/test.code"
    }
#line 7 "tests/01__basics/017__i32_negation/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

