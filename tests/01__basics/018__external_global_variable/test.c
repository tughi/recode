#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

extern int32_t optind;
int32_t main();

#line 3 "tests/01__basics/018__external_global_variable/test.code"
int32_t main() {
#line 4 "tests/01__basics/018__external_global_variable/test.code"
    return optind - 1;
}

