#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/01__basics/027__convert_i32_to_u8/test.code"
int32_t test__main() {
#line 2 "tests/01__basics/027__convert_i32_to_u8/test.code"
    if (test__cast__anon(255) != 255) {
#line 3 "tests/01__basics/027__convert_i32_to_u8/test.code"
        {
#line 3 "tests/01__basics/027__convert_i32_to_u8/test.code"
            int32_t __001__ = 1;
#line 3 "tests/01__basics/027__convert_i32_to_u8/test.code"
            return __001__;
#line 3 "tests/01__basics/027__convert_i32_to_u8/test.code"
        }
#line 4 "tests/01__basics/027__convert_i32_to_u8/test.code"
    }
#line 5 "tests/01__basics/027__convert_i32_to_u8/test.code"
    if (test__cast__anon(-1) != 255) {
#line 6 "tests/01__basics/027__convert_i32_to_u8/test.code"
        {
#line 6 "tests/01__basics/027__convert_i32_to_u8/test.code"
            int32_t __002__ = 2;
#line 6 "tests/01__basics/027__convert_i32_to_u8/test.code"
            return __002__;
#line 6 "tests/01__basics/027__convert_i32_to_u8/test.code"
        }
#line 7 "tests/01__basics/027__convert_i32_to_u8/test.code"
    }
#line 8 "tests/01__basics/027__convert_i32_to_u8/test.code"
    if (test__cast__anon(-255) != 1) {
#line 9 "tests/01__basics/027__convert_i32_to_u8/test.code"
        {
#line 9 "tests/01__basics/027__convert_i32_to_u8/test.code"
            int32_t __003__ = 3;
#line 9 "tests/01__basics/027__convert_i32_to_u8/test.code"
            return __003__;
#line 9 "tests/01__basics/027__convert_i32_to_u8/test.code"
        }
#line 10 "tests/01__basics/027__convert_i32_to_u8/test.code"
    }
#line 11 "tests/01__basics/027__convert_i32_to_u8/test.code"
    {
#line 11 "tests/01__basics/027__convert_i32_to_u8/test.code"
        int32_t __004__ = 0;
#line 11 "tests/01__basics/027__convert_i32_to_u8/test.code"
        return __004__;
#line 11 "tests/01__basics/027__convert_i32_to_u8/test.code"
    }
#line 12 "tests/01__basics/027__convert_i32_to_u8/test.code"
}

#line 14 "tests/01__basics/027__convert_i32_to_u8/test.code"
uint8_t test__cast__anon(int32_t value) {
#line 15 "tests/01__basics/027__convert_i32_to_u8/test.code"
    {
#line 15 "tests/01__basics/027__convert_i32_to_u8/test.code"
        uint8_t __001__ = ((uint8_t) value);
#line 15 "tests/01__basics/027__convert_i32_to_u8/test.code"
        return __001__;
#line 15 "tests/01__basics/027__convert_i32_to_u8/test.code"
    }
#line 16 "tests/01__basics/027__convert_i32_to_u8/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

