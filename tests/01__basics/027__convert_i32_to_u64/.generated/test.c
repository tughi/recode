#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/01__basics/027__convert_i32_to_u64/test.code"
int32_t test__main() {
#line 2 "tests/01__basics/027__convert_i32_to_u64/test.code"
    if (test__cast(255) != 0xffu) {
#line 3 "tests/01__basics/027__convert_i32_to_u64/test.code"
        return 1;
#line 4 "tests/01__basics/027__convert_i32_to_u64/test.code"
    }
#line 5 "tests/01__basics/027__convert_i32_to_u64/test.code"
    if (test__cast(-1) != 0xffffffffffffffffu) {
#line 6 "tests/01__basics/027__convert_i32_to_u64/test.code"
        return 2;
#line 7 "tests/01__basics/027__convert_i32_to_u64/test.code"
    }
#line 8 "tests/01__basics/027__convert_i32_to_u64/test.code"
    if (test__cast(-255) != 0xffffffffffffff01u) {
#line 9 "tests/01__basics/027__convert_i32_to_u64/test.code"
        return 3;
#line 10 "tests/01__basics/027__convert_i32_to_u64/test.code"
    }
#line 11 "tests/01__basics/027__convert_i32_to_u64/test.code"
    return 0;
#line 12 "tests/01__basics/027__convert_i32_to_u64/test.code"
}

#line 14 "tests/01__basics/027__convert_i32_to_u64/test.code"
uint64_t test__cast(int32_t value) {
#line 15 "tests/01__basics/027__convert_i32_to_u64/test.code"
    return ((uint64_t) value);
#line 16 "tests/01__basics/027__convert_i32_to_u64/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

