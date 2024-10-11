#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t main();

int32_t echo__0_value(int32_t value);

#line 1 "tests/01__basics/024__call_function_pointer_variable/test.code"
int32_t main() {
#line 2 "tests/01__basics/024__call_function_pointer_variable/test.code"
    int32_t (*echo_pointer)(int32_t value) = echo__0_value;
#line 4 "tests/01__basics/024__call_function_pointer_variable/test.code"
    return echo_pointer(42) - 42;
}

#line 7 "tests/01__basics/024__call_function_pointer_variable/test.code"
int32_t echo__0_value(int32_t value) {
#line 8 "tests/01__basics/024__call_function_pointer_variable/test.code"
    return value;
}

