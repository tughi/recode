#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t main();

#line 1 "tests/01__basics/008__if_true/test.code"
int32_t main() {
#line 2 "tests/01__basics/008__if_true/test.code"
    int32_t result = 1;
#line 3 "tests/01__basics/008__if_true/test.code"
    if (true) {
#line 4 "tests/01__basics/008__if_true/test.code"
        result = 0;
    }
#line 6 "tests/01__basics/008__if_true/test.code"
    return result;
}

