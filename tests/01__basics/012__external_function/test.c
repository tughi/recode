#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

void exit(int32_t status);

int32_t test__main();

int32_t main(int argc, const char **argv) {
    return test__main();
}

#line 5 "tests/01__basics/012__external_function/test.code"
int32_t test__main() {
#line 6 "tests/01__basics/012__external_function/test.code"
    exit(0);
#line 7 "tests/01__basics/012__external_function/test.code"
    return 1;
}

