#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t test__main();

int32_t test__cast(uint8_t value);

int32_t main(int argc, const char **argv) {
    return test__main();
}

#line 3 "tests/01__basics/026__convert_u8_to_i32/test.code"
int32_t test__main() {
#line 4 "tests/01__basics/026__convert_u8_to_i32/test.code"
    if (test__cast(255) != 255) {
#line 5 "tests/01__basics/026__convert_u8_to_i32/test.code"
        return 1;
    }
#line 7 "tests/01__basics/026__convert_u8_to_i32/test.code"
    if (test__cast(0) != 0) {
#line 8 "tests/01__basics/026__convert_u8_to_i32/test.code"
        return 2;
    }
#line 10 "tests/01__basics/026__convert_u8_to_i32/test.code"
    return 0;
}

#line 13 "tests/01__basics/026__convert_u8_to_i32/test.code"
int32_t test__cast(uint8_t value) {
#line 14 "tests/01__basics/026__convert_u8_to_i32/test.code"
    return ((int32_t) value);
}

