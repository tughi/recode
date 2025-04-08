#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t test__main();

int32_t test__fallback();

int32_t test__fallback__0_value(int32_t value);

int32_t main(int argc, const char **argv) {
    return test__main();
}

#line 1 "tests/01__basics/003__procedure_overloading/test.code"
int32_t test__main() {
#line 2 "tests/01__basics/003__procedure_overloading/test.code"
    return test__fallback() - test__fallback__0_value(42);
}

#line 5 "tests/01__basics/003__procedure_overloading/test.code"
int32_t test__fallback() {
#line 6 "tests/01__basics/003__procedure_overloading/test.code"
    return 42;
}

#line 9 "tests/01__basics/003__procedure_overloading/test.code"
int32_t test__fallback__0_value(int32_t value) {
#line 10 "tests/01__basics/003__procedure_overloading/test.code"
    return value;
}

