#include "test.h"

#line 1 "tests/02__fibonacci/test.code"
int32_t test__main() {
#line 2 "tests/02__fibonacci/test.code"
    return test__fibonacci(12) - 144;
}

#line 5 "tests/02__fibonacci/test.code"
int32_t test__fibonacci(int32_t n) {
#line 6 "tests/02__fibonacci/test.code"
    if (n <= 1) {
#line 7 "tests/02__fibonacci/test.code"
        return n;
    }
#line 9 "tests/02__fibonacci/test.code"
    return test__fibonacci(n - 1) + test__fibonacci(n - 2);
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

