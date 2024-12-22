#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t test__main();

int32_t test__zero();

int32_t main(int argc, const char **argv) {
    return test__main();
}

#line 3 "tests/01__basics/002__call_function_without_arguments/test.code"
int32_t test__main() {
#line 4 "tests/01__basics/002__call_function_without_arguments/test.code"
    return test__zero();
}

#line 7 "tests/01__basics/002__call_function_without_arguments/test.code"
int32_t test__zero() {
#line 8 "tests/01__basics/002__call_function_without_arguments/test.code"
    return 0;
}

