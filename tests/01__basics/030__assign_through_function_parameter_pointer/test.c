#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t test__main();

void test__set__0_pointer__1_value(int32_t *pointer, int32_t value);

int32_t main(int argc, const char **argv) {
    return test__main();
}

#line 3 "tests/01__basics/030__assign_through_function_parameter_pointer/test.code"
int32_t test__main() {
#line 4 "tests/01__basics/030__assign_through_function_parameter_pointer/test.code"
    int32_t x = 0;
#line 5 "tests/01__basics/030__assign_through_function_parameter_pointer/test.code"
    test__set__0_pointer__1_value(&x, 42);
#line 6 "tests/01__basics/030__assign_through_function_parameter_pointer/test.code"
    return x - 42;
}

#line 9 "tests/01__basics/030__assign_through_function_parameter_pointer/test.code"
void test__set__0_pointer__1_value(int32_t *pointer, int32_t value) {
#line 10 "tests/01__basics/030__assign_through_function_parameter_pointer/test.code"
    *pointer = value;
}

