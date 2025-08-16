#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/01__basics/002__call_procedure_without_arguments/test.code"
int32_t test__main() {
#line 2 "tests/01__basics/002__call_procedure_without_arguments/test.code"
    {
#line 2 "tests/01__basics/002__call_procedure_without_arguments/test.code"
        int32_t __001__ = test__zero();
#line 2 "tests/01__basics/002__call_procedure_without_arguments/test.code"
        return __001__;
#line 2 "tests/01__basics/002__call_procedure_without_arguments/test.code"
    }
#line 3 "tests/01__basics/002__call_procedure_without_arguments/test.code"
}

#line 5 "tests/01__basics/002__call_procedure_without_arguments/test.code"
int32_t test__zero() {
#line 6 "tests/01__basics/002__call_procedure_without_arguments/test.code"
    {
#line 6 "tests/01__basics/002__call_procedure_without_arguments/test.code"
        int32_t __001__ = 0;
#line 6 "tests/01__basics/002__call_procedure_without_arguments/test.code"
        return __001__;
#line 6 "tests/01__basics/002__call_procedure_without_arguments/test.code"
    }
#line 7 "tests/01__basics/002__call_procedure_without_arguments/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

