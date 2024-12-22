#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t test__main();

int32_t test__fibonacci__0_of(int32_t n);

int32_t main(int argc, const char **argv) {
    return test__main();
}

#line 3 "tests/01__basics/016__loop/test.code"
int32_t test__main() {
#line 4 "tests/01__basics/016__loop/test.code"
    return test__fibonacci__0_of(12) - 144;
}

#line 7 "tests/01__basics/016__loop/test.code"
int32_t test__fibonacci__0_of(int32_t n) {
#line 8 "tests/01__basics/016__loop/test.code"
    if (n <= 1) {
#line 9 "tests/01__basics/016__loop/test.code"
        return n;
    }
#line 12 "tests/01__basics/016__loop/test.code"
    int32_t v1 = 0;
#line 13 "tests/01__basics/016__loop/test.code"
    int32_t v2 = 1;
#line 14 "tests/01__basics/016__loop/test.code"
    int32_t i = 2;
#line 15 "tests/01__basics/016__loop/test.code"
    for (;;) {
#line 16 "tests/01__basics/016__loop/test.code"
        int32_t v3 = v1 + v2;
#line 17 "tests/01__basics/016__loop/test.code"
        v1 = v2;
#line 18 "tests/01__basics/016__loop/test.code"
        v2 = v3;
#line 19 "tests/01__basics/016__loop/test.code"
        if (i == n) {
#line 20 "tests/01__basics/016__loop/test.code"
            break;
        }
#line 22 "tests/01__basics/016__loop/test.code"
        i = i + 1;
    }
#line 24 "tests/01__basics/016__loop/test.code"
    return v2;
}

