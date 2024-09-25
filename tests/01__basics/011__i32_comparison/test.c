#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t main();

int32_t echo(int32_t v);

#line 1 "tests/01__basics/011__i32_comparison/test.code"
int32_t main() {
#line 2 "tests/01__basics/011__i32_comparison/test.code"
    int32_t errors = 6;
#line 3 "tests/01__basics/011__i32_comparison/test.code"
    if (echo(42) == 42) {
#line 4 "tests/01__basics/011__i32_comparison/test.code"
        errors = errors - 1;
    }
#line 6 "tests/01__basics/011__i32_comparison/test.code"
    if (echo(42) != 42) {
    } else {
#line 9 "tests/01__basics/011__i32_comparison/test.code"
        errors = errors - 1;
    }
#line 11 "tests/01__basics/011__i32_comparison/test.code"
    if (echo(42) < 13) {
    } else {
#line 14 "tests/01__basics/011__i32_comparison/test.code"
        errors = errors - 1;
    }
#line 16 "tests/01__basics/011__i32_comparison/test.code"
    if (echo(42) <= 42) {
#line 17 "tests/01__basics/011__i32_comparison/test.code"
        errors = errors - 1;
    }
#line 19 "tests/01__basics/011__i32_comparison/test.code"
    if (echo(42) > 13) {
#line 20 "tests/01__basics/011__i32_comparison/test.code"
        errors = errors - 1;
    }
#line 22 "tests/01__basics/011__i32_comparison/test.code"
    if (echo(42) >= 42) {
#line 23 "tests/01__basics/011__i32_comparison/test.code"
        errors = errors - 1;
    }
#line 25 "tests/01__basics/011__i32_comparison/test.code"
    return errors;
}

#line 28 "tests/01__basics/011__i32_comparison/test.code"
int32_t echo(int32_t v) {
#line 29 "tests/01__basics/011__i32_comparison/test.code"
    return v;
}

