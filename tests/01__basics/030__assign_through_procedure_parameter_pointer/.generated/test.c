#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/01__basics/030__assign_through_procedure_parameter_pointer/test.code"
int32_t test__main() {
#line 2 "tests/01__basics/030__assign_through_procedure_parameter_pointer/test.code"
    int32_t x = 0;
#line 3 "tests/01__basics/030__assign_through_procedure_parameter_pointer/test.code"
    test__set(&x, 42);
#line 4 "tests/01__basics/030__assign_through_procedure_parameter_pointer/test.code"
    return x - 42;
}

#line 7 "tests/01__basics/030__assign_through_procedure_parameter_pointer/test.code"
void test__set(int32_t *pointer, int32_t value) {
#line 8 "tests/01__basics/030__assign_through_procedure_parameter_pointer/test.code"
    *pointer = value;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

