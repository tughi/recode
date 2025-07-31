#include "test.h"

#line 1 "tests/01__basics/011__i32_comparison/test.code"
int32_t test__main() {
#line 2 "tests/01__basics/011__i32_comparison/test.code"
    int32_t errors = 6;
#line 3 "tests/01__basics/011__i32_comparison/test.code"
    {
#line 3 "tests/01__basics/011__i32_comparison/test.code"
        int32_t __001__ = 42;
#line 3 "tests/01__basics/011__i32_comparison/test.code"
        if (test__echo(__001__) == 42) {
#line 4 "tests/01__basics/011__i32_comparison/test.code"
            errors = errors - 1;
        }
    }
#line 6 "tests/01__basics/011__i32_comparison/test.code"
    {
#line 6 "tests/01__basics/011__i32_comparison/test.code"
        int32_t __001__ = 42;
#line 6 "tests/01__basics/011__i32_comparison/test.code"
        if (test__echo(__001__) != 42) {
        } else {
#line 9 "tests/01__basics/011__i32_comparison/test.code"
            errors = errors - 1;
        }
    }
#line 11 "tests/01__basics/011__i32_comparison/test.code"
    {
#line 11 "tests/01__basics/011__i32_comparison/test.code"
        int32_t __001__ = 42;
#line 11 "tests/01__basics/011__i32_comparison/test.code"
        if (test__echo(__001__) < 13) {
        } else {
#line 14 "tests/01__basics/011__i32_comparison/test.code"
            errors = errors - 1;
        }
    }
#line 16 "tests/01__basics/011__i32_comparison/test.code"
    {
#line 16 "tests/01__basics/011__i32_comparison/test.code"
        int32_t __001__ = 42;
#line 16 "tests/01__basics/011__i32_comparison/test.code"
        if (test__echo(__001__) <= 42) {
#line 17 "tests/01__basics/011__i32_comparison/test.code"
            errors = errors - 1;
        }
    }
#line 19 "tests/01__basics/011__i32_comparison/test.code"
    {
#line 19 "tests/01__basics/011__i32_comparison/test.code"
        int32_t __001__ = 42;
#line 19 "tests/01__basics/011__i32_comparison/test.code"
        if (test__echo(__001__) > 13) {
#line 20 "tests/01__basics/011__i32_comparison/test.code"
            errors = errors - 1;
        }
    }
#line 22 "tests/01__basics/011__i32_comparison/test.code"
    {
#line 22 "tests/01__basics/011__i32_comparison/test.code"
        int32_t __001__ = 42;
#line 22 "tests/01__basics/011__i32_comparison/test.code"
        if (test__echo(__001__) >= 42) {
#line 23 "tests/01__basics/011__i32_comparison/test.code"
            errors = errors - 1;
        }
    }
#line 25 "tests/01__basics/011__i32_comparison/test.code"
    return errors;
}

#line 28 "tests/01__basics/011__i32_comparison/test.code"
int32_t test__echo(int32_t v) {
#line 29 "tests/01__basics/011__i32_comparison/test.code"
    return v;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

