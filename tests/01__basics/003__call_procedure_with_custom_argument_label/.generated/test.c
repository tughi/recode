#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/01__basics/003__call_procedure_with_custom_argument_label/test.code"
int32_t test__main() {
#line 2 "tests/01__basics/003__call_procedure_with_custom_argument_label/test.code"
    {
#line 2 "tests/01__basics/003__call_procedure_with_custom_argument_label/test.code"
        int32_t __001__ = 0;
#line 2 "tests/01__basics/003__call_procedure_with_custom_argument_label/test.code"
        return test__echo(__001__);
    }
}

#line 5 "tests/01__basics/003__call_procedure_with_custom_argument_label/test.code"
int32_t test__echo(int32_t value) {
#line 6 "tests/01__basics/003__call_procedure_with_custom_argument_label/test.code"
    return value;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

