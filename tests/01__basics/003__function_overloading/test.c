#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t main();

int32_t fallback();

int32_t fallback__0_value(int32_t value);

#line 1 "tests/01__basics/003__function_overloading/test.code"
int32_t main() {
#line 2 "tests/01__basics/003__function_overloading/test.code"
    return fallback() - fallback__0_value(42);
}

#line 5 "tests/01__basics/003__function_overloading/test.code"
int32_t fallback() {
#line 6 "tests/01__basics/003__function_overloading/test.code"
    return 42;
}

#line 9 "tests/01__basics/003__function_overloading/test.code"
int32_t fallback__0_value(int32_t value) {
#line 10 "tests/01__basics/003__function_overloading/test.code"
    return value;
}

