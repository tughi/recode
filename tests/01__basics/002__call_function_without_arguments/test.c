#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t main();

int32_t zero();

#line 1 "tests/01__basics/002__call_function_without_arguments/test.code"
int32_t main() {
#line 2 "tests/01__basics/002__call_function_without_arguments/test.code"
    return zero();
}

#line 5 "tests/01__basics/002__call_function_without_arguments/test.code"
int32_t zero() {
#line 6 "tests/01__basics/002__call_function_without_arguments/test.code"
    return 0;
}

