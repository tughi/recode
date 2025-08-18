#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/02__fibonacci/test.code"
int32_t test__main() {
#line 2 "tests/02__fibonacci/test.code"
    {
#line 2 "tests/02__fibonacci/test.code"
        int32_t __001__ = test__fibonacci(12) - 144;
#line 2 "tests/02__fibonacci/test.code"
        return __001__;
#line 2 "tests/02__fibonacci/test.code"
    }
#line 3 "tests/02__fibonacci/test.code"
}

#line 5 "tests/02__fibonacci/test.code"
int32_t test__fibonacci(int32_t n) {
#line 6 "tests/02__fibonacci/test.code"
    if (n <= 1) {
#line 7 "tests/02__fibonacci/test.code"
        {
#line 7 "tests/02__fibonacci/test.code"
            int32_t __001__ = n;
#line 7 "tests/02__fibonacci/test.code"
            return __001__;
#line 7 "tests/02__fibonacci/test.code"
        }
#line 8 "tests/02__fibonacci/test.code"
    }
#line 9 "tests/02__fibonacci/test.code"
    {
#line 9 "tests/02__fibonacci/test.code"
        int32_t __002__ = test__fibonacci(n - 1) + test__fibonacci(n - 2);
#line 9 "tests/02__fibonacci/test.code"
        return __002__;
#line 9 "tests/02__fibonacci/test.code"
    }
#line 10 "tests/02__fibonacci/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

