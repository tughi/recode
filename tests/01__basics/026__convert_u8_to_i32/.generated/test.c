#include "test.h"

#line 1 "tests/01__basics/026__convert_u8_to_i32/test.code"
int32_t test__main() {
#line 2 "tests/01__basics/026__convert_u8_to_i32/test.code"
    {
#line 2 "tests/01__basics/026__convert_u8_to_i32/test.code"
        uint8_t __001__ = 255;
#line 2 "tests/01__basics/026__convert_u8_to_i32/test.code"
        if (test__cast(__001__) != 255) {
#line 3 "tests/01__basics/026__convert_u8_to_i32/test.code"
            return 1;
        }
    }
#line 5 "tests/01__basics/026__convert_u8_to_i32/test.code"
    {
#line 5 "tests/01__basics/026__convert_u8_to_i32/test.code"
        uint8_t __001__ = 0;
#line 5 "tests/01__basics/026__convert_u8_to_i32/test.code"
        if (test__cast(__001__) != 0) {
#line 6 "tests/01__basics/026__convert_u8_to_i32/test.code"
            return 2;
        }
    }
#line 8 "tests/01__basics/026__convert_u8_to_i32/test.code"
    return 0;
}

#line 11 "tests/01__basics/026__convert_u8_to_i32/test.code"
int32_t test__cast(uint8_t value) {
#line 12 "tests/01__basics/026__convert_u8_to_i32/test.code"
    return ((int32_t) value);
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

