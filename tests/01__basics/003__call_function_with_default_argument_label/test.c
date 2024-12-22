#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t test__main();

int32_t test__echo__0_value(int32_t value);

int32_t main(int argc, const char **argv) {
    return test__main();
}

#line 3 "tests/01__basics/003__call_function_with_default_argument_label/test.code"
int32_t test__main() {
#line 4 "tests/01__basics/003__call_function_with_default_argument_label/test.code"
    return test__echo__0_value(0);
}

#line 7 "tests/01__basics/003__call_function_with_default_argument_label/test.code"
int32_t test__echo__0_value(int32_t value) {
#line 8 "tests/01__basics/003__call_function_with_default_argument_label/test.code"
    return value;
}

