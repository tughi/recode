#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/01__basics/024__call_procedure_pointer_variable/test.code"
int32_t test__main() {
#line 2 "tests/01__basics/024__call_procedure_pointer_variable/test.code"
    int32_t (*echo_pointer)(int32_t value) = test__echo;
#line 4 "tests/01__basics/024__call_procedure_pointer_variable/test.code"
    return echo_pointer(42) - 42;
#line 5 "tests/01__basics/024__call_procedure_pointer_variable/test.code"
}

#line 7 "tests/01__basics/024__call_procedure_pointer_variable/test.code"
int32_t test__echo(int32_t value) {
#line 8 "tests/01__basics/024__call_procedure_pointer_variable/test.code"
    return value;
#line 9 "tests/01__basics/024__call_procedure_pointer_variable/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

