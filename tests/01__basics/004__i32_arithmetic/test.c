#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t test__main();

int32_t test__add(int32_t v1, int32_t v2);

int32_t test__sub(int32_t v1, int32_t v2);

int32_t test__mul(int32_t v1, int32_t v2);

int32_t test__div(int32_t v1, int32_t v2);

int32_t test__mod(int32_t v1, int32_t v2);

int32_t main(int argc, const char **argv) {
    return test__main();
}

#line 3 "tests/01__basics/004__i32_arithmetic/test.code"
int32_t test__main() {
#line 4 "tests/01__basics/004__i32_arithmetic/test.code"
    return test__sub(test__mul(test__add(test__div(42, 10), 2), test__add(test__mod(42, 10), 5)), 42);
}

#line 19 "tests/01__basics/004__i32_arithmetic/test.code"
int32_t test__add(int32_t v1, int32_t v2) {
#line 20 "tests/01__basics/004__i32_arithmetic/test.code"
    return v1 + v2;
}

#line 23 "tests/01__basics/004__i32_arithmetic/test.code"
int32_t test__sub(int32_t v1, int32_t v2) {
#line 24 "tests/01__basics/004__i32_arithmetic/test.code"
    return v1 - v2;
}

#line 27 "tests/01__basics/004__i32_arithmetic/test.code"
int32_t test__mul(int32_t v1, int32_t v2) {
#line 28 "tests/01__basics/004__i32_arithmetic/test.code"
    return v1 * v2;
}

#line 31 "tests/01__basics/004__i32_arithmetic/test.code"
int32_t test__div(int32_t v1, int32_t v2) {
#line 32 "tests/01__basics/004__i32_arithmetic/test.code"
    return v1 / v2;
}

#line 35 "tests/01__basics/004__i32_arithmetic/test.code"
int32_t test__mod(int32_t v1, int32_t v2) {
#line 36 "tests/01__basics/004__i32_arithmetic/test.code"
    return v1 % v2;
}

