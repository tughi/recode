#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/01__basics/022__assign_procedure_pointer_variable/test.code"
int32_t test__main() {
#line 2 "tests/01__basics/022__assign_procedure_pointer_variable/test.code"
    int32_t (*procedure_pointer)(int32_t value);
#line 4 "tests/01__basics/022__assign_procedure_pointer_variable/test.code"
    procedure_pointer = test__echo__value;
#line 6 "tests/01__basics/022__assign_procedure_pointer_variable/test.code"
    {
#line 6 "tests/01__basics/022__assign_procedure_pointer_variable/test.code"
        int32_t __001__ = 0;
#line 6 "tests/01__basics/022__assign_procedure_pointer_variable/test.code"
        return __001__;
#line 6 "tests/01__basics/022__assign_procedure_pointer_variable/test.code"
    }
#line 7 "tests/01__basics/022__assign_procedure_pointer_variable/test.code"
}

#line 9 "tests/01__basics/022__assign_procedure_pointer_variable/test.code"
int32_t test__echo__value(int32_t value) {
#line 10 "tests/01__basics/022__assign_procedure_pointer_variable/test.code"
    {
#line 10 "tests/01__basics/022__assign_procedure_pointer_variable/test.code"
        int32_t __001__ = value;
#line 10 "tests/01__basics/022__assign_procedure_pointer_variable/test.code"
        return __001__;
#line 10 "tests/01__basics/022__assign_procedure_pointer_variable/test.code"
    }
#line 11 "tests/01__basics/022__assign_procedure_pointer_variable/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

