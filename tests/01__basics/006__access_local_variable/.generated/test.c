#include "test.h"

#line 1 "tests/01__basics/006__access_local_variable/test.code"
int32_t test__main() {
#line 2 "tests/01__basics/006__access_local_variable/test.code"
    int32_t result = 42;
#line 3 "tests/01__basics/006__access_local_variable/test.code"
    return result - 42;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

