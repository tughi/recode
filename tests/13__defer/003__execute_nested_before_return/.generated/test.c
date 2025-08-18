#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/13__defer/003__execute_nested_before_return/test.code"
int32_t test__main() {
#line 2 "tests/13__defer/003__execute_nested_before_return/test.code"
    int32_t result = 42;
#line 4 "tests/13__defer/003__execute_nested_before_return/test.code"
    {
#line 6 "tests/13__defer/003__execute_nested_before_return/test.code"
        {
#line 7 "tests/13__defer/003__execute_nested_before_return/test.code"
            {
#line 7 "tests/13__defer/003__execute_nested_before_return/test.code"
                int32_t __001__ = result - 42;
#line 5 "tests/13__defer/003__execute_nested_before_return/test.code"
                result = 10;
#line 3 "tests/13__defer/003__execute_nested_before_return/test.code"
                result = 13;
#line 7 "tests/13__defer/003__execute_nested_before_return/test.code"
                return __001__;
#line 7 "tests/13__defer/003__execute_nested_before_return/test.code"
            }
#line 8 "tests/13__defer/003__execute_nested_before_return/test.code"
        }
#line 9 "tests/13__defer/003__execute_nested_before_return/test.code"
    }
#line 10 "tests/13__defer/003__execute_nested_before_return/test.code"
    {
#line 10 "tests/13__defer/003__execute_nested_before_return/test.code"
        int32_t __002__ = 1;
#line 3 "tests/13__defer/003__execute_nested_before_return/test.code"
        result = 13;
#line 10 "tests/13__defer/003__execute_nested_before_return/test.code"
        return __002__;
#line 10 "tests/13__defer/003__execute_nested_before_return/test.code"
    }
#line 11 "tests/13__defer/003__execute_nested_before_return/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

