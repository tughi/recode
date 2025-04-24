#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

#include "test.h"

#line 3 "tests/01__basics/018__external_global_variable/test.code"
int32_t test__main() {
#line 4 "tests/01__basics/018__external_global_variable/test.code"
    return optind - 1;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

