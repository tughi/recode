#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/12__error_handling/009__typed_procedure_pointer/test.code"
int32_t test__main() {
#line 2 "tests/12__error_handling/009__typed_procedure_pointer/test.code"
    struct test_Result__6_16 (*procedure)() = test__demo;
#line 3 "tests/12__error_handling/009__typed_procedure_pointer/test.code"
    {
#line 3 "tests/12__error_handling/009__typed_procedure_pointer/test.code"
        struct test_Result__6_16 __001__ = procedure();
#line 3 "tests/12__error_handling/009__typed_procedure_pointer/test.code"
        int32_t __002__;
#line 3 "tests/12__error_handling/009__typed_procedure_pointer/test.code"
        if (__001__.success) {
#line 3 "tests/12__error_handling/009__typed_procedure_pointer/test.code"
            __002__ = __001__.value;
#line 3 "tests/12__error_handling/009__typed_procedure_pointer/test.code"
        } else {
#line 3 "tests/12__error_handling/009__typed_procedure_pointer/test.code"
            __002__ = __001__.error;
#line 3 "tests/12__error_handling/009__typed_procedure_pointer/test.code"
        }
#line 3 "tests/12__error_handling/009__typed_procedure_pointer/test.code"
        int32_t __003__ = (__002__);
#line 3 "tests/12__error_handling/009__typed_procedure_pointer/test.code"
        int32_t __004__ = __003__ - 42;
#line 3 "tests/12__error_handling/009__typed_procedure_pointer/test.code"
        return __004__;
#line 3 "tests/12__error_handling/009__typed_procedure_pointer/test.code"
    }
#line 4 "tests/12__error_handling/009__typed_procedure_pointer/test.code"
}

#line 6 "tests/12__error_handling/009__typed_procedure_pointer/test.code"
struct test_Result__6_16 test__demo() {
#line 7 "tests/12__error_handling/009__typed_procedure_pointer/test.code"
    {
#line 7 "tests/12__error_handling/009__typed_procedure_pointer/test.code"
        int32_t __001__ = 42;
#line 7 "tests/12__error_handling/009__typed_procedure_pointer/test.code"
        return (struct test_Result__6_16){.success = false, .error = __001__};
#line 7 "tests/12__error_handling/009__typed_procedure_pointer/test.code"
    }
#line 8 "tests/12__error_handling/009__typed_procedure_pointer/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

