#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t test__main();

uint8_t test__cast(int32_t value);

int32_t main(int argc, const char **argv) {
    return test__main();
}

#line 3 "tests/01__basics/027__convert_i32_to_u8/test.code"
int32_t test__main() {
#line 4 "tests/01__basics/027__convert_i32_to_u8/test.code"
    if (test__cast(255) != 255) {
#line 5 "tests/01__basics/027__convert_i32_to_u8/test.code"
        return 1;
    }
#line 7 "tests/01__basics/027__convert_i32_to_u8/test.code"
    if (test__cast(-1) != 255) {
#line 8 "tests/01__basics/027__convert_i32_to_u8/test.code"
        return 2;
    }
#line 10 "tests/01__basics/027__convert_i32_to_u8/test.code"
    if (test__cast(-255) != 1) {
#line 11 "tests/01__basics/027__convert_i32_to_u8/test.code"
        return 3;
    }
#line 13 "tests/01__basics/027__convert_i32_to_u8/test.code"
    return 0;
}

#line 16 "tests/01__basics/027__convert_i32_to_u8/test.code"
uint8_t test__cast(int32_t value) {
#line 17 "tests/01__basics/027__convert_i32_to_u8/test.code"
    return ((uint8_t) value);
}

