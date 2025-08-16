#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/01__basics/032__call_procedure_with_null_parameter/test.code"
int32_t test__main() {
#line 2 "tests/01__basics/032__call_procedure_with_null_parameter/test.code"
    return test__deref(NULL);
#line 3 "tests/01__basics/032__call_procedure_with_null_parameter/test.code"
}

#line 5 "tests/01__basics/032__call_procedure_with_null_parameter/test.code"
int32_t test__deref(int32_t *ptr) {
#line 6 "tests/01__basics/032__call_procedure_with_null_parameter/test.code"
    if (ptr == NULL) {
#line 7 "tests/01__basics/032__call_procedure_with_null_parameter/test.code"
        return 0;
#line 8 "tests/01__basics/032__call_procedure_with_null_parameter/test.code"
    }
#line 9 "tests/01__basics/032__call_procedure_with_null_parameter/test.code"
    return *ptr;
#line 10 "tests/01__basics/032__call_procedure_with_null_parameter/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

