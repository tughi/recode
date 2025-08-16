#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/01__basics/016__loop/test.code"
int32_t test__main() {
#line 2 "tests/01__basics/016__loop/test.code"
    {
#line 2 "tests/01__basics/016__loop/test.code"
        int32_t __001__ = test__fibonacci(12) - 144;
#line 2 "tests/01__basics/016__loop/test.code"
        return __001__;
#line 2 "tests/01__basics/016__loop/test.code"
    }
#line 3 "tests/01__basics/016__loop/test.code"
}

#line 5 "tests/01__basics/016__loop/test.code"
int32_t test__fibonacci(int32_t n) {
#line 6 "tests/01__basics/016__loop/test.code"
    if (n <= 1) {
#line 7 "tests/01__basics/016__loop/test.code"
        {
#line 7 "tests/01__basics/016__loop/test.code"
            int32_t __001__ = n;
#line 7 "tests/01__basics/016__loop/test.code"
            return __001__;
#line 7 "tests/01__basics/016__loop/test.code"
        }
#line 8 "tests/01__basics/016__loop/test.code"
    }
#line 10 "tests/01__basics/016__loop/test.code"
    int32_t v1 = 0;
#line 11 "tests/01__basics/016__loop/test.code"
    int32_t v2 = 1;
#line 12 "tests/01__basics/016__loop/test.code"
    int32_t i = 2;
#line 13 "tests/01__basics/016__loop/test.code"
    for (;;) {
#line 14 "tests/01__basics/016__loop/test.code"
        int32_t v3 = v1 + v2;
#line 15 "tests/01__basics/016__loop/test.code"
        v1 = v2;
#line 16 "tests/01__basics/016__loop/test.code"
        v2 = v3;
#line 17 "tests/01__basics/016__loop/test.code"
        if (i == n) {
#line 18 "tests/01__basics/016__loop/test.code"
            break;
#line 19 "tests/01__basics/016__loop/test.code"
        }
#line 20 "tests/01__basics/016__loop/test.code"
        i = i + 1;
#line 21 "tests/01__basics/016__loop/test.code"
    }
#line 22 "tests/01__basics/016__loop/test.code"
    {
#line 22 "tests/01__basics/016__loop/test.code"
        int32_t __002__ = v2;
#line 22 "tests/01__basics/016__loop/test.code"
        return __002__;
#line 22 "tests/01__basics/016__loop/test.code"
    }
#line 23 "tests/01__basics/016__loop/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

