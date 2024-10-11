#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t main();

int32_t echo__0_value(int32_t value);

#line 1 "tests/01__basics/022__assign_function_pointer_variable/test.code"
int32_t main() {
#line 2 "tests/01__basics/022__assign_function_pointer_variable/test.code"
    int32_t (*function_pointer)(int32_t value);
#line 4 "tests/01__basics/022__assign_function_pointer_variable/test.code"
    function_pointer = echo__0_value;
#line 6 "tests/01__basics/022__assign_function_pointer_variable/test.code"
    return 0;
}

#line 9 "tests/01__basics/022__assign_function_pointer_variable/test.code"
int32_t echo__0_value(int32_t value) {
#line 10 "tests/01__basics/022__assign_function_pointer_variable/test.code"
    return value;
}

