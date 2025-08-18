#include "test.h"
#include "constants.h"

void *malloc(uintmax_t size);

#line 3 "tests/14__const/002__imported/test.code"
int32_t test__main() {
#line 4 "tests/14__const/002__imported/test.code"
    {
#line 4 "tests/14__const/002__imported/test.code"
        int32_t __001__ = ((41) + 1) - 42;
#line 4 "tests/14__const/002__imported/test.code"
        return __001__;
#line 4 "tests/14__const/002__imported/test.code"
    }
#line 5 "tests/14__const/002__imported/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

