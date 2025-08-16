#include "test.h"

void *malloc(uintmax_t size);

#line 3 "tests/01__basics/018__external_global_variable/test.code"
int32_t test__main() {
#line 4 "tests/01__basics/018__external_global_variable/test.code"
    return optind - 1;
#line 5 "tests/01__basics/018__external_global_variable/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

