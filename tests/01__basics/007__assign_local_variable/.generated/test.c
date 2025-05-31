#include "test.h"

#line 1 "tests/01__basics/007__assign_local_variable/test.code"
int32_t test__main() {
#line 2 "tests/01__basics/007__assign_local_variable/test.code"
    int32_t x = 0;
#line 3 "tests/01__basics/007__assign_local_variable/test.code"
    x = x + 1;
#line 4 "tests/01__basics/007__assign_local_variable/test.code"
    return x - 1;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

