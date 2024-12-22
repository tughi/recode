#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t test__main();

uint64_t test__cast(int32_t value);

int32_t main(int argc, const char **argv) {
    return test__main();
}

#line 3 "tests/01__basics/027__convert_i32_to_u64/test.code"
int32_t test__main() {
#line 4 "tests/01__basics/027__convert_i32_to_u64/test.code"
    if (test__cast(255) != 255u) {
#line 5 "tests/01__basics/027__convert_i32_to_u64/test.code"
        return 1;
    }
#line 7 "tests/01__basics/027__convert_i32_to_u64/test.code"
    if (test__cast(-1) != 18446744073709551615u) {
#line 8 "tests/01__basics/027__convert_i32_to_u64/test.code"
        return 2;
    }
#line 10 "tests/01__basics/027__convert_i32_to_u64/test.code"
    if (test__cast(-255) != 18446744073709551361u) {
#line 11 "tests/01__basics/027__convert_i32_to_u64/test.code"
        return 3;
    }
#line 13 "tests/01__basics/027__convert_i32_to_u64/test.code"
    return 0;
}

#line 16 "tests/01__basics/027__convert_i32_to_u64/test.code"
uint64_t test__cast(int32_t value) {
#line 17 "tests/01__basics/027__convert_i32_to_u64/test.code"
    return ((uint64_t) value);
}

