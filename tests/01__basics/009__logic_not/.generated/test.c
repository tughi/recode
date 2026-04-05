#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/01__basics/009__logic_not/test.code"
int32_t test__main() {
#line 2 "tests/01__basics/009__logic_not/test.code"
    if (test__test_not__anon(true)) {
#line 3 "tests/01__basics/009__logic_not/test.code"
        {
#line 3 "tests/01__basics/009__logic_not/test.code"
            int32_t __001__ = 1;
#line 3 "tests/01__basics/009__logic_not/test.code"
            return __001__;
#line 3 "tests/01__basics/009__logic_not/test.code"
        }
#line 4 "tests/01__basics/009__logic_not/test.code"
    }
#line 5 "tests/01__basics/009__logic_not/test.code"
    if (test__test_not__anon(false)) {
#line 7 "tests/01__basics/009__logic_not/test.code"
    } else {
#line 8 "tests/01__basics/009__logic_not/test.code"
        {
#line 8 "tests/01__basics/009__logic_not/test.code"
            int32_t __002__ = 2;
#line 8 "tests/01__basics/009__logic_not/test.code"
            return __002__;
#line 8 "tests/01__basics/009__logic_not/test.code"
        }
#line 9 "tests/01__basics/009__logic_not/test.code"
    }
#line 10 "tests/01__basics/009__logic_not/test.code"
    if (!test__test_not__anon(false)) {
#line 11 "tests/01__basics/009__logic_not/test.code"
        {
#line 11 "tests/01__basics/009__logic_not/test.code"
            int32_t __003__ = 3;
#line 11 "tests/01__basics/009__logic_not/test.code"
            return __003__;
#line 11 "tests/01__basics/009__logic_not/test.code"
        }
#line 12 "tests/01__basics/009__logic_not/test.code"
    }
#line 13 "tests/01__basics/009__logic_not/test.code"
    if (!!test__test_not__anon(true)) {
#line 14 "tests/01__basics/009__logic_not/test.code"
        {
#line 14 "tests/01__basics/009__logic_not/test.code"
            int32_t __004__ = 4;
#line 14 "tests/01__basics/009__logic_not/test.code"
            return __004__;
#line 14 "tests/01__basics/009__logic_not/test.code"
        }
#line 15 "tests/01__basics/009__logic_not/test.code"
    }
#line 16 "tests/01__basics/009__logic_not/test.code"
    {
#line 16 "tests/01__basics/009__logic_not/test.code"
        int32_t __005__ = 0;
#line 16 "tests/01__basics/009__logic_not/test.code"
        return __005__;
#line 16 "tests/01__basics/009__logic_not/test.code"
    }
#line 17 "tests/01__basics/009__logic_not/test.code"
}

#line 19 "tests/01__basics/009__logic_not/test.code"
bool test__test_not__anon(bool v) {
#line 20 "tests/01__basics/009__logic_not/test.code"
    {
#line 20 "tests/01__basics/009__logic_not/test.code"
        bool __001__ = !v;
#line 20 "tests/01__basics/009__logic_not/test.code"
        return __001__;
#line 20 "tests/01__basics/009__logic_not/test.code"
    }
#line 21 "tests/01__basics/009__logic_not/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

