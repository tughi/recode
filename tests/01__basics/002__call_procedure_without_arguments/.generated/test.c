#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

#include "test.h"

#line 1 "tests/01__basics/002__call_procedure_without_arguments/test.code"
int32_t test__main() {
#line 2 "tests/01__basics/002__call_procedure_without_arguments/test.code"
    return test__zero();
}

#line 5 "tests/01__basics/002__call_procedure_without_arguments/test.code"
int32_t test__zero() {
#line 6 "tests/01__basics/002__call_procedure_without_arguments/test.code"
    return 0;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

