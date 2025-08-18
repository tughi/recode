#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/13__defer/002__execute_before_return/test.code"
int32_t test__main() {
#line 2 "tests/13__defer/002__execute_before_return/test.code"
    if (test__return_forty_two() != 42) {
#line 3 "tests/13__defer/002__execute_before_return/test.code"
        {
#line 3 "tests/13__defer/002__execute_before_return/test.code"
            int32_t __001__ = 2;
#line 3 "tests/13__defer/002__execute_before_return/test.code"
            return __001__;
#line 3 "tests/13__defer/002__execute_before_return/test.code"
        }
#line 4 "tests/13__defer/002__execute_before_return/test.code"
    }
#line 5 "tests/13__defer/002__execute_before_return/test.code"
    {
#line 5 "tests/13__defer/002__execute_before_return/test.code"
        int32_t __002__ = 0;
#line 5 "tests/13__defer/002__execute_before_return/test.code"
        return __002__;
#line 5 "tests/13__defer/002__execute_before_return/test.code"
    }
#line 6 "tests/13__defer/002__execute_before_return/test.code"
}

#line 8 "tests/13__defer/002__execute_before_return/test.code"
int32_t test__return_forty_two() {
#line 9 "tests/13__defer/002__execute_before_return/test.code"
    int32_t value = 42;
#line 12 "tests/13__defer/002__execute_before_return/test.code"
    {
#line 12 "tests/13__defer/002__execute_before_return/test.code"
        int32_t __001__ = value;
#line 11 "tests/13__defer/002__execute_before_return/test.code"
        value = 0;
#line 10 "tests/13__defer/002__execute_before_return/test.code"
        value = 13;
#line 12 "tests/13__defer/002__execute_before_return/test.code"
        return __001__;
#line 12 "tests/13__defer/002__execute_before_return/test.code"
    }
#line 13 "tests/13__defer/002__execute_before_return/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

