#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t main();

int32_t fibonacci(int32_t n);

#line 1 "tests/01__basics/014__while/test.code"
int32_t main() {
#line 2 "tests/01__basics/014__while/test.code"
    return fibonacci(12) - 144;
}

#line 5 "tests/01__basics/014__while/test.code"
int32_t fibonacci(int32_t n) {
#line 6 "tests/01__basics/014__while/test.code"
    if (n <= 1) {
#line 7 "tests/01__basics/014__while/test.code"
        return n;
    }
#line 10 "tests/01__basics/014__while/test.code"
    int32_t v1 = 0;
#line 11 "tests/01__basics/014__while/test.code"
    int32_t v2 = 1;
#line 12 "tests/01__basics/014__while/test.code"
    int32_t i = 2;
#line 13 "tests/01__basics/014__while/test.code"
    while (i <= n) {
#line 14 "tests/01__basics/014__while/test.code"
        int32_t v3 = v1 + v2;
#line 15 "tests/01__basics/014__while/test.code"
        v1 = v2;
#line 16 "tests/01__basics/014__while/test.code"
        v2 = v3;
#line 17 "tests/01__basics/014__while/test.code"
        i = i + 1;
    }
#line 19 "tests/01__basics/014__while/test.code"
    return v2;
}

