#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/01__basics/027__convert_i32_to_u8/test.code"
int32_t test__main() {
#line 2 "tests/01__basics/027__convert_i32_to_u8/test.code"
    {
#line 2 "tests/01__basics/027__convert_i32_to_u8/test.code"
        int32_t __001__ = 255;
#line 2 "tests/01__basics/027__convert_i32_to_u8/test.code"
        if (test__cast(__001__) != 255) {
#line 3 "tests/01__basics/027__convert_i32_to_u8/test.code"
            return 1;
        }
    }
#line 5 "tests/01__basics/027__convert_i32_to_u8/test.code"
    {
#line 5 "tests/01__basics/027__convert_i32_to_u8/test.code"
        int32_t __001__ = -1;
#line 5 "tests/01__basics/027__convert_i32_to_u8/test.code"
        if (test__cast(__001__) != 255) {
#line 6 "tests/01__basics/027__convert_i32_to_u8/test.code"
            return 2;
        }
    }
#line 8 "tests/01__basics/027__convert_i32_to_u8/test.code"
    {
#line 8 "tests/01__basics/027__convert_i32_to_u8/test.code"
        int32_t __001__ = -255;
#line 8 "tests/01__basics/027__convert_i32_to_u8/test.code"
        if (test__cast(__001__) != 1) {
#line 9 "tests/01__basics/027__convert_i32_to_u8/test.code"
            return 3;
        }
    }
#line 11 "tests/01__basics/027__convert_i32_to_u8/test.code"
    return 0;
}

#line 14 "tests/01__basics/027__convert_i32_to_u8/test.code"
uint8_t test__cast(int32_t value) {
#line 15 "tests/01__basics/027__convert_i32_to_u8/test.code"
    return ((uint8_t) value);
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

