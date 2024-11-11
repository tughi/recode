#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t main();

void set__0_pointer__1_value(int32_t *pointer, int32_t value);

#line 1 "tests/01__basics/030__assign_through_function_parameter_pointer/test.code"
int32_t main() {
#line 2 "tests/01__basics/030__assign_through_function_parameter_pointer/test.code"
    int32_t x = 0;
#line 3 "tests/01__basics/030__assign_through_function_parameter_pointer/test.code"
    set__0_pointer__1_value(&x, 42);
#line 4 "tests/01__basics/030__assign_through_function_parameter_pointer/test.code"
    return x - 42;
}

#line 7 "tests/01__basics/030__assign_through_function_parameter_pointer/test.code"
void set__0_pointer__1_value(int32_t *pointer, int32_t value) {
#line 8 "tests/01__basics/030__assign_through_function_parameter_pointer/test.code"
    *pointer = value;
}

