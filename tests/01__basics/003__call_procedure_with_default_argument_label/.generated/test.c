#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/01__basics/003__call_procedure_with_default_argument_label/test.code"
int32_t test__main() {
#line 2 "tests/01__basics/003__call_procedure_with_default_argument_label/test.code"
    {
#line 2 "tests/01__basics/003__call_procedure_with_default_argument_label/test.code"
        int32_t __001__ = test__echo__value(0);
#line 2 "tests/01__basics/003__call_procedure_with_default_argument_label/test.code"
        return __001__;
#line 2 "tests/01__basics/003__call_procedure_with_default_argument_label/test.code"
    }
#line 3 "tests/01__basics/003__call_procedure_with_default_argument_label/test.code"
}

#line 5 "tests/01__basics/003__call_procedure_with_default_argument_label/test.code"
int32_t test__echo__value(int32_t value) {
#line 6 "tests/01__basics/003__call_procedure_with_default_argument_label/test.code"
    {
#line 6 "tests/01__basics/003__call_procedure_with_default_argument_label/test.code"
        int32_t __001__ = value;
#line 6 "tests/01__basics/003__call_procedure_with_default_argument_label/test.code"
        return __001__;
#line 6 "tests/01__basics/003__call_procedure_with_default_argument_label/test.code"
    }
#line 7 "tests/01__basics/003__call_procedure_with_default_argument_label/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

