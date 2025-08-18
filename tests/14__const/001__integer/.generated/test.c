#include "test.h"

void *malloc(uintmax_t size);

#line 3 "tests/14__const/001__integer/test.code"
int32_t test__main() {
#line 4 "tests/14__const/001__integer/test.code"
    {
#line 4 "tests/14__const/001__integer/test.code"
        int32_t __001__ = (50 - 8) / 7 - 6;
#line 4 "tests/14__const/001__integer/test.code"
        return __001__;
#line 4 "tests/14__const/001__integer/test.code"
    }
#line 5 "tests/14__const/001__integer/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

