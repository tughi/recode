#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/13__defer/005__execute_before_loop_break/test.code"
int32_t test__main() {
#line 2 "tests/13__defer/005__execute_before_loop_break/test.code"
    bool repeat = true;
#line 3 "tests/13__defer/005__execute_before_loop_break/test.code"
    while (repeat) {
#line 4 "tests/13__defer/005__execute_before_loop_break/test.code"
        for (;;) {
#line 6 "tests/13__defer/005__execute_before_loop_break/test.code"
            repeat = true;
#line 5 "tests/13__defer/005__execute_before_loop_break/test.code"
            repeat = false;
#line 7 "tests/13__defer/005__execute_before_loop_break/test.code"
            break;
#line 8 "tests/13__defer/005__execute_before_loop_break/test.code"
        }
#line 9 "tests/13__defer/005__execute_before_loop_break/test.code"
    }
#line 10 "tests/13__defer/005__execute_before_loop_break/test.code"
    {
#line 10 "tests/13__defer/005__execute_before_loop_break/test.code"
        int32_t __001__ = 0;
#line 10 "tests/13__defer/005__execute_before_loop_break/test.code"
        return __001__;
#line 10 "tests/13__defer/005__execute_before_loop_break/test.code"
    }
#line 11 "tests/13__defer/005__execute_before_loop_break/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

