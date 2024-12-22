#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t test__main();

int32_t main(int argc, const char **argv) {
    return test__main();
}

#line 3 "tests/01__basics/006__access_local_variable/test.code"
int32_t test__main() {
#line 4 "tests/01__basics/006__access_local_variable/test.code"
    int32_t result = 42;
#line 5 "tests/01__basics/006__access_local_variable/test.code"
    return result - 42;
}

