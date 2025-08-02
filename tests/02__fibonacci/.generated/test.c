#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/02__fibonacci/test.code"
int32_t test__main() {
#line 2 "tests/02__fibonacci/test.code"
    {
#line 2 "tests/02__fibonacci/test.code"
        int32_t __001__ = 12;
#line 2 "tests/02__fibonacci/test.code"
        return test__fibonacci(__001__) - 144;
    }
}

#line 5 "tests/02__fibonacci/test.code"
int32_t test__fibonacci(int32_t n) {
#line 6 "tests/02__fibonacci/test.code"
    if (n <= 1) {
#line 7 "tests/02__fibonacci/test.code"
        return n;
    }
#line 9 "tests/02__fibonacci/test.code"
    {
#line 9 "tests/02__fibonacci/test.code"
        int32_t __001__ = n - 1;
#line 9 "tests/02__fibonacci/test.code"
        int32_t __002__ = n - 2;
#line 9 "tests/02__fibonacci/test.code"
        return test__fibonacci(__001__) + test__fibonacci(__002__);
    }
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

