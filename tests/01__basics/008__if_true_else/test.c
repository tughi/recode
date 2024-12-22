#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t test__main();

int32_t main(int argc, const char **argv) {
    return test__main();
}

#line 3 "tests/01__basics/008__if_true_else/test.code"
int32_t test__main() {
#line 4 "tests/01__basics/008__if_true_else/test.code"
    int32_t result = 2;
#line 5 "tests/01__basics/008__if_true_else/test.code"
    if (true) {
#line 6 "tests/01__basics/008__if_true_else/test.code"
        result = 0;
    } else {
#line 8 "tests/01__basics/008__if_true_else/test.code"
        result = 1;
    }
#line 10 "tests/01__basics/008__if_true_else/test.code"
    return result;
}

