#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t main();

#line 1 "tests/01__basics/007__assign_local_variable/test.code"
int32_t main() {
#line 2 "tests/01__basics/007__assign_local_variable/test.code"
    int32_t x = 0;
#line 3 "tests/01__basics/007__assign_local_variable/test.code"
    x = x + 1;
#line 4 "tests/01__basics/007__assign_local_variable/test.code"
    return x - 1;
}

