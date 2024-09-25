#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t main();

int32_t echo(int32_t value);

#line 1 "tests/01__basics/003__call_function_with_default_argument_label/test.code"
int32_t main() {
#line 2 "tests/01__basics/003__call_function_with_default_argument_label/test.code"
    return echo(0);
}

#line 5 "tests/01__basics/003__call_function_with_default_argument_label/test.code"
int32_t echo(int32_t value) {
#line 6 "tests/01__basics/003__call_function_with_default_argument_label/test.code"
    return value;
}

