#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/13__defer/006__nested_loop_returns/test.code"
int32_t test__main() {
#line 2 "tests/13__defer/006__nested_loop_returns/test.code"
    int32_t result = 42;
#line 4 "tests/13__defer/006__nested_loop_returns/test.code"
    for (;;) {
#line 6 "tests/13__defer/006__nested_loop_returns/test.code"
        for (;;) {
#line 8 "tests/13__defer/006__nested_loop_returns/test.code"
            {
#line 8 "tests/13__defer/006__nested_loop_returns/test.code"
                int32_t __001__ = result - 42;
#line 7 "tests/13__defer/006__nested_loop_returns/test.code"
                result = 12;
#line 5 "tests/13__defer/006__nested_loop_returns/test.code"
                result = 22;
#line 3 "tests/13__defer/006__nested_loop_returns/test.code"
                result = 32;
#line 8 "tests/13__defer/006__nested_loop_returns/test.code"
                return __001__;
#line 8 "tests/13__defer/006__nested_loop_returns/test.code"
            }
#line 9 "tests/13__defer/006__nested_loop_returns/test.code"
        }
#line 10 "tests/13__defer/006__nested_loop_returns/test.code"
    }
#line 11 "tests/13__defer/006__nested_loop_returns/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

