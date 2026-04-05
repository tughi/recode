#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/01__basics/026__convert_u8_to_i32/test.code"
int32_t test__main() {
#line 2 "tests/01__basics/026__convert_u8_to_i32/test.code"
    if (test__cast__anon(255) != 255) {
#line 3 "tests/01__basics/026__convert_u8_to_i32/test.code"
        {
#line 3 "tests/01__basics/026__convert_u8_to_i32/test.code"
            int32_t __001__ = 1;
#line 3 "tests/01__basics/026__convert_u8_to_i32/test.code"
            return __001__;
#line 3 "tests/01__basics/026__convert_u8_to_i32/test.code"
        }
#line 4 "tests/01__basics/026__convert_u8_to_i32/test.code"
    }
#line 5 "tests/01__basics/026__convert_u8_to_i32/test.code"
    if (test__cast__anon(0) != 0) {
#line 6 "tests/01__basics/026__convert_u8_to_i32/test.code"
        {
#line 6 "tests/01__basics/026__convert_u8_to_i32/test.code"
            int32_t __002__ = 2;
#line 6 "tests/01__basics/026__convert_u8_to_i32/test.code"
            return __002__;
#line 6 "tests/01__basics/026__convert_u8_to_i32/test.code"
        }
#line 7 "tests/01__basics/026__convert_u8_to_i32/test.code"
    }
#line 8 "tests/01__basics/026__convert_u8_to_i32/test.code"
    {
#line 8 "tests/01__basics/026__convert_u8_to_i32/test.code"
        int32_t __003__ = 0;
#line 8 "tests/01__basics/026__convert_u8_to_i32/test.code"
        return __003__;
#line 8 "tests/01__basics/026__convert_u8_to_i32/test.code"
    }
#line 9 "tests/01__basics/026__convert_u8_to_i32/test.code"
}

#line 11 "tests/01__basics/026__convert_u8_to_i32/test.code"
int32_t test__cast__anon(uint8_t value) {
#line 12 "tests/01__basics/026__convert_u8_to_i32/test.code"
    {
#line 12 "tests/01__basics/026__convert_u8_to_i32/test.code"
        int32_t __001__ = ((int32_t) value);
#line 12 "tests/01__basics/026__convert_u8_to_i32/test.code"
        return __001__;
#line 12 "tests/01__basics/026__convert_u8_to_i32/test.code"
    }
#line 13 "tests/01__basics/026__convert_u8_to_i32/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

