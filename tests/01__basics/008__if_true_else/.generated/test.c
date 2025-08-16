#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/01__basics/008__if_true_else/test.code"
int32_t test__main() {
#line 2 "tests/01__basics/008__if_true_else/test.code"
    int32_t result = 2;
#line 3 "tests/01__basics/008__if_true_else/test.code"
    if (true) {
#line 4 "tests/01__basics/008__if_true_else/test.code"
        result = 0;
#line 5 "tests/01__basics/008__if_true_else/test.code"
    } else {
#line 6 "tests/01__basics/008__if_true_else/test.code"
        result = 1;
#line 7 "tests/01__basics/008__if_true_else/test.code"
    }
#line 8 "tests/01__basics/008__if_true_else/test.code"
    return result;
#line 9 "tests/01__basics/008__if_true_else/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

