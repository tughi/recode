#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t main();

int32_t fibonacci(int32_t n);

#line 1 "tests/02__fibonacci/test.code"
int32_t main() {
#line 2 "tests/02__fibonacci/test.code"
    return fibonacci(12) - 144;
}

#line 5 "tests/02__fibonacci/test.code"
int32_t fibonacci(int32_t n) {
#line 6 "tests/02__fibonacci/test.code"
    if (n <= 1) {
#line 7 "tests/02__fibonacci/test.code"
        return n;
    }
#line 9 "tests/02__fibonacci/test.code"
    return fibonacci(n - 1) + fibonacci(n - 2);
}

