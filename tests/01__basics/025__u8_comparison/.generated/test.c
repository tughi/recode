#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/01__basics/025__u8_comparison/test.code"
int32_t test__main() {
#line 2 "tests/01__basics/025__u8_comparison/test.code"
    uint8_t min = 0;
#line 3 "tests/01__basics/025__u8_comparison/test.code"
    uint8_t max = 255;
#line 5 "tests/01__basics/025__u8_comparison/test.code"
    int32_t errors = 8;
#line 6 "tests/01__basics/025__u8_comparison/test.code"
    if (test__forty_two() == 42) {
#line 7 "tests/01__basics/025__u8_comparison/test.code"
        errors = errors - 1;
#line 8 "tests/01__basics/025__u8_comparison/test.code"
    }
#line 9 "tests/01__basics/025__u8_comparison/test.code"
    if (test__forty_two() != 42) {
#line 11 "tests/01__basics/025__u8_comparison/test.code"
    } else {
#line 12 "tests/01__basics/025__u8_comparison/test.code"
        errors = errors - 1;
#line 13 "tests/01__basics/025__u8_comparison/test.code"
    }
#line 14 "tests/01__basics/025__u8_comparison/test.code"
    if (test__forty_two() < max) {
#line 15 "tests/01__basics/025__u8_comparison/test.code"
        errors = errors - 1;
#line 16 "tests/01__basics/025__u8_comparison/test.code"
    }
#line 17 "tests/01__basics/025__u8_comparison/test.code"
    if (test__forty_two() < min) {
#line 19 "tests/01__basics/025__u8_comparison/test.code"
    } else {
#line 20 "tests/01__basics/025__u8_comparison/test.code"
        errors = errors - 1;
#line 21 "tests/01__basics/025__u8_comparison/test.code"
    }
#line 22 "tests/01__basics/025__u8_comparison/test.code"
    if (test__forty_two() <= 42) {
#line 23 "tests/01__basics/025__u8_comparison/test.code"
        errors = errors - 1;
#line 24 "tests/01__basics/025__u8_comparison/test.code"
    }
#line 25 "tests/01__basics/025__u8_comparison/test.code"
    if (test__forty_two() < max) {
#line 26 "tests/01__basics/025__u8_comparison/test.code"
        errors = errors - 1;
#line 27 "tests/01__basics/025__u8_comparison/test.code"
    }
#line 28 "tests/01__basics/025__u8_comparison/test.code"
    if (test__forty_two() < min) {
#line 30 "tests/01__basics/025__u8_comparison/test.code"
    } else {
#line 31 "tests/01__basics/025__u8_comparison/test.code"
        errors = errors - 1;
#line 32 "tests/01__basics/025__u8_comparison/test.code"
    }
#line 33 "tests/01__basics/025__u8_comparison/test.code"
    if (test__forty_two() >= 42) {
#line 34 "tests/01__basics/025__u8_comparison/test.code"
        errors = errors - 1;
#line 35 "tests/01__basics/025__u8_comparison/test.code"
    }
#line 36 "tests/01__basics/025__u8_comparison/test.code"
    return errors;
#line 37 "tests/01__basics/025__u8_comparison/test.code"
}

#line 39 "tests/01__basics/025__u8_comparison/test.code"
uint8_t test__forty_two() {
#line 40 "tests/01__basics/025__u8_comparison/test.code"
    return 42;
#line 41 "tests/01__basics/025__u8_comparison/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

