#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t main();

int32_t cast(uint8_t value);

#line 1 "tests/01__basics/026__convert_u8_to_i32/test.code"
int32_t main() {
#line 2 "tests/01__basics/026__convert_u8_to_i32/test.code"
    if (cast(255) != 255) {
#line 3 "tests/01__basics/026__convert_u8_to_i32/test.code"
        return 1;
    }
#line 5 "tests/01__basics/026__convert_u8_to_i32/test.code"
    if (cast(0) != 0) {
#line 6 "tests/01__basics/026__convert_u8_to_i32/test.code"
        return 2;
    }
#line 8 "tests/01__basics/026__convert_u8_to_i32/test.code"
    return 0;
}

#line 11 "tests/01__basics/026__convert_u8_to_i32/test.code"
int32_t cast(uint8_t value) {
#line 12 "tests/01__basics/026__convert_u8_to_i32/test.code"
    return (int32_t) value;
}

