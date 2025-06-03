#include "test.h"

#line 1 "tests/01__basics/023__init_procedure_pointer_variable/test.code"
int32_t test__main() {
#line 2 "tests/01__basics/023__init_procedure_pointer_variable/test.code"
    int32_t (*procedure_pointer)(int32_t value) = test__echo;
#line 4 "tests/01__basics/023__init_procedure_pointer_variable/test.code"
    return 0;
}

#line 7 "tests/01__basics/023__init_procedure_pointer_variable/test.code"
int32_t test__echo(int32_t value) {
#line 8 "tests/01__basics/023__init_procedure_pointer_variable/test.code"
    return value;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

