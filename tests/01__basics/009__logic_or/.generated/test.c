#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/01__basics/009__logic_or/test.code"
int32_t test__main() {
#line 2 "tests/01__basics/009__logic_or/test.code"
    bool t = test__echo__anon(true);
#line 3 "tests/01__basics/009__logic_or/test.code"
    bool f = test__echo__anon(false);
#line 4 "tests/01__basics/009__logic_or/test.code"
    if (t || f) {
#line 6 "tests/01__basics/009__logic_or/test.code"
    } else {
#line 7 "tests/01__basics/009__logic_or/test.code"
        {
#line 7 "tests/01__basics/009__logic_or/test.code"
            int32_t __001__ = 1;
#line 7 "tests/01__basics/009__logic_or/test.code"
            return __001__;
#line 7 "tests/01__basics/009__logic_or/test.code"
        }
#line 8 "tests/01__basics/009__logic_or/test.code"
    }
#line 9 "tests/01__basics/009__logic_or/test.code"
    if (f || t) {
#line 11 "tests/01__basics/009__logic_or/test.code"
    } else {
#line 12 "tests/01__basics/009__logic_or/test.code"
        {
#line 12 "tests/01__basics/009__logic_or/test.code"
            int32_t __002__ = 2;
#line 12 "tests/01__basics/009__logic_or/test.code"
            return __002__;
#line 12 "tests/01__basics/009__logic_or/test.code"
        }
#line 13 "tests/01__basics/009__logic_or/test.code"
    }
#line 14 "tests/01__basics/009__logic_or/test.code"
    if (t || t) {
#line 16 "tests/01__basics/009__logic_or/test.code"
    } else {
#line 17 "tests/01__basics/009__logic_or/test.code"
        {
#line 17 "tests/01__basics/009__logic_or/test.code"
            int32_t __003__ = 3;
#line 17 "tests/01__basics/009__logic_or/test.code"
            return __003__;
#line 17 "tests/01__basics/009__logic_or/test.code"
        }
#line 18 "tests/01__basics/009__logic_or/test.code"
    }
#line 19 "tests/01__basics/009__logic_or/test.code"
    if (f || f) {
#line 20 "tests/01__basics/009__logic_or/test.code"
        {
#line 20 "tests/01__basics/009__logic_or/test.code"
            int32_t __004__ = 4;
#line 20 "tests/01__basics/009__logic_or/test.code"
            return __004__;
#line 20 "tests/01__basics/009__logic_or/test.code"
        }
#line 21 "tests/01__basics/009__logic_or/test.code"
    }
#line 22 "tests/01__basics/009__logic_or/test.code"
    if ((f || f) || (f || f)) {
#line 23 "tests/01__basics/009__logic_or/test.code"
        {
#line 23 "tests/01__basics/009__logic_or/test.code"
            int32_t __005__ = 5;
#line 23 "tests/01__basics/009__logic_or/test.code"
            return __005__;
#line 23 "tests/01__basics/009__logic_or/test.code"
        }
#line 24 "tests/01__basics/009__logic_or/test.code"
    }
#line 25 "tests/01__basics/009__logic_or/test.code"
    {
#line 25 "tests/01__basics/009__logic_or/test.code"
        int32_t __006__ = 0;
#line 25 "tests/01__basics/009__logic_or/test.code"
        return __006__;
#line 25 "tests/01__basics/009__logic_or/test.code"
    }
#line 26 "tests/01__basics/009__logic_or/test.code"
}

#line 28 "tests/01__basics/009__logic_or/test.code"
bool test__echo__anon(bool v) {
#line 29 "tests/01__basics/009__logic_or/test.code"
    {
#line 29 "tests/01__basics/009__logic_or/test.code"
        bool __001__ = v;
#line 29 "tests/01__basics/009__logic_or/test.code"
        return __001__;
#line 29 "tests/01__basics/009__logic_or/test.code"
    }
#line 30 "tests/01__basics/009__logic_or/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

