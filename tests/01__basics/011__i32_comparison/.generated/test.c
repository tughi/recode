#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/01__basics/011__i32_comparison/test.code"
int32_t test__main() {
#line 2 "tests/01__basics/011__i32_comparison/test.code"
    int32_t errors = 6;
#line 3 "tests/01__basics/011__i32_comparison/test.code"
    if (test__echo(42) == 42) {
#line 4 "tests/01__basics/011__i32_comparison/test.code"
        errors = errors - 1;
#line 5 "tests/01__basics/011__i32_comparison/test.code"
    }
#line 6 "tests/01__basics/011__i32_comparison/test.code"
    if (test__echo(42) != 42) {
#line 8 "tests/01__basics/011__i32_comparison/test.code"
    } else {
#line 9 "tests/01__basics/011__i32_comparison/test.code"
        errors = errors - 1;
#line 10 "tests/01__basics/011__i32_comparison/test.code"
    }
#line 11 "tests/01__basics/011__i32_comparison/test.code"
    if (test__echo(42) < 13) {
#line 13 "tests/01__basics/011__i32_comparison/test.code"
    } else {
#line 14 "tests/01__basics/011__i32_comparison/test.code"
        errors = errors - 1;
#line 15 "tests/01__basics/011__i32_comparison/test.code"
    }
#line 16 "tests/01__basics/011__i32_comparison/test.code"
    if (test__echo(42) <= 42) {
#line 17 "tests/01__basics/011__i32_comparison/test.code"
        errors = errors - 1;
#line 18 "tests/01__basics/011__i32_comparison/test.code"
    }
#line 19 "tests/01__basics/011__i32_comparison/test.code"
    if (test__echo(42) > 13) {
#line 20 "tests/01__basics/011__i32_comparison/test.code"
        errors = errors - 1;
#line 21 "tests/01__basics/011__i32_comparison/test.code"
    }
#line 22 "tests/01__basics/011__i32_comparison/test.code"
    if (test__echo(42) >= 42) {
#line 23 "tests/01__basics/011__i32_comparison/test.code"
        errors = errors - 1;
#line 24 "tests/01__basics/011__i32_comparison/test.code"
    }
#line 25 "tests/01__basics/011__i32_comparison/test.code"
    {
#line 25 "tests/01__basics/011__i32_comparison/test.code"
        int32_t __001__ = errors;
#line 25 "tests/01__basics/011__i32_comparison/test.code"
        return __001__;
#line 25 "tests/01__basics/011__i32_comparison/test.code"
    }
#line 26 "tests/01__basics/011__i32_comparison/test.code"
}

#line 28 "tests/01__basics/011__i32_comparison/test.code"
int32_t test__echo(int32_t v) {
#line 29 "tests/01__basics/011__i32_comparison/test.code"
    {
#line 29 "tests/01__basics/011__i32_comparison/test.code"
        int32_t __001__ = v;
#line 29 "tests/01__basics/011__i32_comparison/test.code"
        return __001__;
#line 29 "tests/01__basics/011__i32_comparison/test.code"
    }
#line 30 "tests/01__basics/011__i32_comparison/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

