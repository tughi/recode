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

#line 1 "tests/01__basics/004__i32_arithmetic/test.code"
int32_t test__main() {
#line 2 "tests/01__basics/004__i32_arithmetic/test.code"
    return test__sub(test__mul(test__add(test__div(42, 10), 2), test__add(test__mod(42, 10), 5)), 42);
}

#line 17 "tests/01__basics/004__i32_arithmetic/test.code"
int32_t test__add(int32_t v1, int32_t v2) {
#line 18 "tests/01__basics/004__i32_arithmetic/test.code"
    return v1 + v2;
}

#line 21 "tests/01__basics/004__i32_arithmetic/test.code"
int32_t test__sub(int32_t v1, int32_t v2) {
#line 22 "tests/01__basics/004__i32_arithmetic/test.code"
    return v1 - v2;
}

#line 25 "tests/01__basics/004__i32_arithmetic/test.code"
int32_t test__mul(int32_t v1, int32_t v2) {
#line 26 "tests/01__basics/004__i32_arithmetic/test.code"
    return v1 * v2;
}

#line 29 "tests/01__basics/004__i32_arithmetic/test.code"
int32_t test__div(int32_t v1, int32_t v2) {
#line 30 "tests/01__basics/004__i32_arithmetic/test.code"
    return v1 / v2;
}

#line 33 "tests/01__basics/004__i32_arithmetic/test.code"
int32_t test__mod(int32_t v1, int32_t v2) {
#line 34 "tests/01__basics/004__i32_arithmetic/test.code"
    return v1 % v2;
}

