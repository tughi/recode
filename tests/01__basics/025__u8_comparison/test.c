#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t test__main();

uint8_t test__forty_two();

int32_t main(int argc, const char **argv) {
    return test__main();
}

#line 3 "tests/01__basics/025__u8_comparison/test.code"
int32_t test__main() {
#line 4 "tests/01__basics/025__u8_comparison/test.code"
    uint8_t min = 0;
#line 5 "tests/01__basics/025__u8_comparison/test.code"
    uint8_t max = 255;
#line 7 "tests/01__basics/025__u8_comparison/test.code"
    int32_t errors = 8;
#line 8 "tests/01__basics/025__u8_comparison/test.code"
    if (test__forty_two() == 42) {
#line 9 "tests/01__basics/025__u8_comparison/test.code"
        errors = errors - 1;
    }
#line 11 "tests/01__basics/025__u8_comparison/test.code"
    if (test__forty_two() != 42) {
    } else {
#line 14 "tests/01__basics/025__u8_comparison/test.code"
        errors = errors - 1;
    }
#line 16 "tests/01__basics/025__u8_comparison/test.code"
    if (test__forty_two() < max) {
#line 17 "tests/01__basics/025__u8_comparison/test.code"
        errors = errors - 1;
    }
#line 19 "tests/01__basics/025__u8_comparison/test.code"
    if (test__forty_two() < min) {
    } else {
#line 22 "tests/01__basics/025__u8_comparison/test.code"
        errors = errors - 1;
    }
#line 24 "tests/01__basics/025__u8_comparison/test.code"
    if (test__forty_two() <= 42) {
#line 25 "tests/01__basics/025__u8_comparison/test.code"
        errors = errors - 1;
    }
#line 27 "tests/01__basics/025__u8_comparison/test.code"
    if (test__forty_two() < max) {
#line 28 "tests/01__basics/025__u8_comparison/test.code"
        errors = errors - 1;
    }
#line 30 "tests/01__basics/025__u8_comparison/test.code"
    if (test__forty_two() < min) {
    } else {
#line 33 "tests/01__basics/025__u8_comparison/test.code"
        errors = errors - 1;
    }
#line 35 "tests/01__basics/025__u8_comparison/test.code"
    if (test__forty_two() >= 42) {
#line 36 "tests/01__basics/025__u8_comparison/test.code"
        errors = errors - 1;
    }
#line 38 "tests/01__basics/025__u8_comparison/test.code"
    return errors;
}

#line 41 "tests/01__basics/025__u8_comparison/test.code"
uint8_t test__forty_two() {
#line 42 "tests/01__basics/025__u8_comparison/test.code"
    return 42;
}

