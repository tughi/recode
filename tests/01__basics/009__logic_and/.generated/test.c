#include "test.h"

#line 1 "tests/01__basics/009__logic_and/test.code"
int32_t test__main() {
#line 2 "tests/01__basics/009__logic_and/test.code"
    bool t;
#line 2 "tests/01__basics/009__logic_and/test.code"
    {
#line 2 "tests/01__basics/009__logic_and/test.code"
        bool __001__ = true;
#line 2 "tests/01__basics/009__logic_and/test.code"
        t = test__echo(__001__);
    }
#line 3 "tests/01__basics/009__logic_and/test.code"
    bool f;
#line 3 "tests/01__basics/009__logic_and/test.code"
    {
#line 3 "tests/01__basics/009__logic_and/test.code"
        bool __001__ = false;
#line 3 "tests/01__basics/009__logic_and/test.code"
        f = test__echo(__001__);
    }
#line 4 "tests/01__basics/009__logic_and/test.code"
    {
#line 4 "tests/01__basics/009__logic_and/test.code"
        bool __001__ = t;
#line 4 "tests/01__basics/009__logic_and/test.code"
        if (__001__) {
#line 4 "tests/01__basics/009__logic_and/test.code"
            __001__ = f;
        }
#line 4 "tests/01__basics/009__logic_and/test.code"
        if (__001__) {
#line 5 "tests/01__basics/009__logic_and/test.code"
            return 1;
        }
    }
#line 7 "tests/01__basics/009__logic_and/test.code"
    {
#line 7 "tests/01__basics/009__logic_and/test.code"
        bool __001__ = f;
#line 7 "tests/01__basics/009__logic_and/test.code"
        if (__001__) {
#line 7 "tests/01__basics/009__logic_and/test.code"
            __001__ = t;
        }
#line 7 "tests/01__basics/009__logic_and/test.code"
        if (__001__) {
#line 8 "tests/01__basics/009__logic_and/test.code"
            return 2;
        }
    }
#line 10 "tests/01__basics/009__logic_and/test.code"
    {
#line 10 "tests/01__basics/009__logic_and/test.code"
        bool __001__ = t;
#line 10 "tests/01__basics/009__logic_and/test.code"
        if (__001__) {
#line 10 "tests/01__basics/009__logic_and/test.code"
            __001__ = t;
        }
#line 10 "tests/01__basics/009__logic_and/test.code"
        if (__001__) {
        } else {
#line 13 "tests/01__basics/009__logic_and/test.code"
            return 3;
        }
    }
#line 15 "tests/01__basics/009__logic_and/test.code"
    {
#line 15 "tests/01__basics/009__logic_and/test.code"
        bool __001__ = f;
#line 15 "tests/01__basics/009__logic_and/test.code"
        if (__001__) {
#line 15 "tests/01__basics/009__logic_and/test.code"
            __001__ = f;
        }
#line 15 "tests/01__basics/009__logic_and/test.code"
        if (__001__) {
#line 16 "tests/01__basics/009__logic_and/test.code"
            return 4;
        }
    }
#line 18 "tests/01__basics/009__logic_and/test.code"
    {
#line 18 "tests/01__basics/009__logic_and/test.code"
        bool __001__ = t;
#line 18 "tests/01__basics/009__logic_and/test.code"
        if (__001__) {
#line 18 "tests/01__basics/009__logic_and/test.code"
            __001__ = t;
        }
#line 18 "tests/01__basics/009__logic_and/test.code"
        bool __002__ = (__001__);
#line 18 "tests/01__basics/009__logic_and/test.code"
        if (__002__) {
#line 18 "tests/01__basics/009__logic_and/test.code"
            bool __003__ = f;
#line 18 "tests/01__basics/009__logic_and/test.code"
            if (__003__) {
#line 18 "tests/01__basics/009__logic_and/test.code"
                __003__ = f;
            }
#line 18 "tests/01__basics/009__logic_and/test.code"
            __002__ = (__003__);
        }
#line 18 "tests/01__basics/009__logic_and/test.code"
        if (__002__) {
#line 19 "tests/01__basics/009__logic_and/test.code"
            return 5;
        }
    }
#line 21 "tests/01__basics/009__logic_and/test.code"
    return 0;
}

#line 24 "tests/01__basics/009__logic_and/test.code"
bool test__echo(bool v) {
#line 25 "tests/01__basics/009__logic_and/test.code"
    return v;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

