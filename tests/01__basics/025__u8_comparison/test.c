#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t main();

uint8_t forty_two();

#line 1 "tests/01__basics/025__u8_comparison/test.code"
int32_t main() {
#line 2 "tests/01__basics/025__u8_comparison/test.code"
    uint8_t min = 0;
#line 3 "tests/01__basics/025__u8_comparison/test.code"
    uint8_t max = 255;
#line 5 "tests/01__basics/025__u8_comparison/test.code"
    int32_t errors = 8;
#line 6 "tests/01__basics/025__u8_comparison/test.code"
    if (forty_two() == 42) {
#line 7 "tests/01__basics/025__u8_comparison/test.code"
        errors = errors - 1;
    }
#line 9 "tests/01__basics/025__u8_comparison/test.code"
    if (forty_two() != 42) {
    } else {
#line 12 "tests/01__basics/025__u8_comparison/test.code"
        errors = errors - 1;
    }
#line 14 "tests/01__basics/025__u8_comparison/test.code"
    if (forty_two() < max) {
#line 15 "tests/01__basics/025__u8_comparison/test.code"
        errors = errors - 1;
    }
#line 17 "tests/01__basics/025__u8_comparison/test.code"
    if (forty_two() < min) {
    } else {
#line 20 "tests/01__basics/025__u8_comparison/test.code"
        errors = errors - 1;
    }
#line 22 "tests/01__basics/025__u8_comparison/test.code"
    if (forty_two() <= 42) {
#line 23 "tests/01__basics/025__u8_comparison/test.code"
        errors = errors - 1;
    }
#line 25 "tests/01__basics/025__u8_comparison/test.code"
    if (forty_two() < max) {
#line 26 "tests/01__basics/025__u8_comparison/test.code"
        errors = errors - 1;
    }
#line 28 "tests/01__basics/025__u8_comparison/test.code"
    if (forty_two() < min) {
    } else {
#line 31 "tests/01__basics/025__u8_comparison/test.code"
        errors = errors - 1;
    }
#line 33 "tests/01__basics/025__u8_comparison/test.code"
    if (forty_two() >= 42) {
#line 34 "tests/01__basics/025__u8_comparison/test.code"
        errors = errors - 1;
    }
#line 36 "tests/01__basics/025__u8_comparison/test.code"
    return errors;
}

#line 39 "tests/01__basics/025__u8_comparison/test.code"
uint8_t forty_two() {
#line 40 "tests/01__basics/025__u8_comparison/test.code"
    return 42;
}

