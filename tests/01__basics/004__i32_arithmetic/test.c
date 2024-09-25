#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t main();

int32_t add(int32_t v1, int32_t v2);

int32_t sub(int32_t v1, int32_t v2);

int32_t mul(int32_t v1, int32_t v2);

int32_t div(int32_t v1, int32_t v2);

int32_t mod(int32_t v1, int32_t v2);

#line 1 "tests/01__basics/004__i32_arithmetic/test.code"
int32_t main() {
#line 2 "tests/01__basics/004__i32_arithmetic/test.code"
    return sub(mul(add(div(42, 10), 2), add(mod(42, 10), 5)), 42);
}

#line 17 "tests/01__basics/004__i32_arithmetic/test.code"
int32_t add(int32_t v1, int32_t v2) {
#line 18 "tests/01__basics/004__i32_arithmetic/test.code"
    return v1 + v2;
}

#line 21 "tests/01__basics/004__i32_arithmetic/test.code"
int32_t sub(int32_t v1, int32_t v2) {
#line 22 "tests/01__basics/004__i32_arithmetic/test.code"
    return v1 - v2;
}

#line 25 "tests/01__basics/004__i32_arithmetic/test.code"
int32_t mul(int32_t v1, int32_t v2) {
#line 26 "tests/01__basics/004__i32_arithmetic/test.code"
    return v1 * v2;
}

#line 29 "tests/01__basics/004__i32_arithmetic/test.code"
int32_t div(int32_t v1, int32_t v2) {
#line 30 "tests/01__basics/004__i32_arithmetic/test.code"
    return v1 / v2;
}

#line 33 "tests/01__basics/004__i32_arithmetic/test.code"
int32_t mod(int32_t v1, int32_t v2) {
#line 34 "tests/01__basics/004__i32_arithmetic/test.code"
    return v1 % v2;
}

