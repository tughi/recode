#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t main();

#line 1 "tests/01__basics/008__if_true_else/test.code"
int32_t main() {
#line 2 "tests/01__basics/008__if_true_else/test.code"
    int32_t result = 2;
#line 3 "tests/01__basics/008__if_true_else/test.code"
    if (true) {
#line 4 "tests/01__basics/008__if_true_else/test.code"
        result = 0;
    } else {
#line 6 "tests/01__basics/008__if_true_else/test.code"
        result = 1;
    }
#line 8 "tests/01__basics/008__if_true_else/test.code"
    return result;
}

