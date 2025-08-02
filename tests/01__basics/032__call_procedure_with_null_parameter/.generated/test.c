#include "test.h"

#line 1 "tests/01__basics/032__call_procedure_with_null_parameter/test.code"
int32_t test__main() {
#line 2 "tests/01__basics/032__call_procedure_with_null_parameter/test.code"
    {
#line 2 "tests/01__basics/032__call_procedure_with_null_parameter/test.code"
        int32_t *__001__ = NULL;
#line 2 "tests/01__basics/032__call_procedure_with_null_parameter/test.code"
        return test__deref(__001__);
    }
}

#line 5 "tests/01__basics/032__call_procedure_with_null_parameter/test.code"
int32_t test__deref(int32_t *ptr) {
#line 6 "tests/01__basics/032__call_procedure_with_null_parameter/test.code"
    if (ptr == NULL) {
#line 7 "tests/01__basics/032__call_procedure_with_null_parameter/test.code"
        return 0;
    }
#line 9 "tests/01__basics/032__call_procedure_with_null_parameter/test.code"
    return *ptr;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

