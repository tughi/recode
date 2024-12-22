#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t test__main();

int32_t test__fibonacci__0_of(int32_t n);

int32_t main(int argc, const char **argv) {
    return test__main();
}

#line 3 "tests/02__fibonacci/test.code"
int32_t test__main() {
#line 4 "tests/02__fibonacci/test.code"
    return test__fibonacci__0_of(12) - 144;
}

#line 7 "tests/02__fibonacci/test.code"
int32_t test__fibonacci__0_of(int32_t n) {
#line 8 "tests/02__fibonacci/test.code"
    if (n <= 1) {
#line 9 "tests/02__fibonacci/test.code"
        return n;
    }
#line 11 "tests/02__fibonacci/test.code"
    return test__fibonacci__0_of(n - 1) + test__fibonacci__0_of(n - 2);
}

