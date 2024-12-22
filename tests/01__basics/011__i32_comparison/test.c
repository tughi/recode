#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t test__main();

int32_t test__echo(int32_t v);

int32_t main(int argc, const char **argv) {
    return test__main();
}

#line 3 "tests/01__basics/011__i32_comparison/test.code"
int32_t test__main() {
#line 4 "tests/01__basics/011__i32_comparison/test.code"
    int32_t errors = 6;
#line 5 "tests/01__basics/011__i32_comparison/test.code"
    if (test__echo(42) == 42) {
#line 6 "tests/01__basics/011__i32_comparison/test.code"
        errors = errors - 1;
    }
#line 8 "tests/01__basics/011__i32_comparison/test.code"
    if (test__echo(42) != 42) {
    } else {
#line 11 "tests/01__basics/011__i32_comparison/test.code"
        errors = errors - 1;
    }
#line 13 "tests/01__basics/011__i32_comparison/test.code"
    if (test__echo(42) < 13) {
    } else {
#line 16 "tests/01__basics/011__i32_comparison/test.code"
        errors = errors - 1;
    }
#line 18 "tests/01__basics/011__i32_comparison/test.code"
    if (test__echo(42) <= 42) {
#line 19 "tests/01__basics/011__i32_comparison/test.code"
        errors = errors - 1;
    }
#line 21 "tests/01__basics/011__i32_comparison/test.code"
    if (test__echo(42) > 13) {
#line 22 "tests/01__basics/011__i32_comparison/test.code"
        errors = errors - 1;
    }
#line 24 "tests/01__basics/011__i32_comparison/test.code"
    if (test__echo(42) >= 42) {
#line 25 "tests/01__basics/011__i32_comparison/test.code"
        errors = errors - 1;
    }
#line 27 "tests/01__basics/011__i32_comparison/test.code"
    return errors;
}

#line 30 "tests/01__basics/011__i32_comparison/test.code"
int32_t test__echo(int32_t v) {
#line 31 "tests/01__basics/011__i32_comparison/test.code"
    return v;
}

