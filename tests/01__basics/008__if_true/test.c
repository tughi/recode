#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t test__main();

int32_t main(int argc, const char **argv) {
    return test__main();
}

#line 3 "tests/01__basics/008__if_true/test.code"
int32_t test__main() {
#line 4 "tests/01__basics/008__if_true/test.code"
    int32_t result = 1;
#line 5 "tests/01__basics/008__if_true/test.code"
    if (true) {
#line 6 "tests/01__basics/008__if_true/test.code"
        result = 0;
    }
#line 8 "tests/01__basics/008__if_true/test.code"
    return result;
}

