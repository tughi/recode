#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

#include "test.h"

#line 1 "tests/01__basics/017__i32_negation/test.code"
int32_t test__main() {
#line 2 "tests/01__basics/017__i32_negation/test.code"
    int32_t value = 42;
#line 3 "tests/01__basics/017__i32_negation/test.code"
    if (value * -1 != -value) {
#line 4 "tests/01__basics/017__i32_negation/test.code"
        return 1;
    }
#line 6 "tests/01__basics/017__i32_negation/test.code"
    return 0;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

