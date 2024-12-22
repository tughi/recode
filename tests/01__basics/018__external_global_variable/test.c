#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

extern int32_t optind;
int32_t test__main();

int32_t main(int argc, const char **argv) {
    return test__main();
}

#line 5 "tests/01__basics/018__external_global_variable/test.code"
int32_t test__main() {
#line 6 "tests/01__basics/018__external_global_variable/test.code"
    return optind - 1;
}

