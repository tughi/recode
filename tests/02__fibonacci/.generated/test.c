#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t test__main();

int32_t test__fibonacci__0_of(int32_t n);

int32_t main(int argc, const char **argv) {
    return test__main();
}

#line 1 "tests/02__fibonacci/test.code"
int32_t test__main() {
#line 2 "tests/02__fibonacci/test.code"
    return test__fibonacci__0_of(12) - 144;
}

#line 5 "tests/02__fibonacci/test.code"
int32_t test__fibonacci__0_of(int32_t n) {
#line 6 "tests/02__fibonacci/test.code"
    if (n <= 1) {
#line 7 "tests/02__fibonacci/test.code"
        return n;
    }
#line 9 "tests/02__fibonacci/test.code"
    return test__fibonacci__0_of(n - 1) + test__fibonacci__0_of(n - 2);
}

