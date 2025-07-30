#include "test.h"

#line 1 "tests/01__basics/009__logic_or/test.code"
int32_t test__main() {
#line 2 "tests/01__basics/009__logic_or/test.code"
    bool t = test__echo(true);
#line 3 "tests/01__basics/009__logic_or/test.code"
    bool f = test__echo(false);
#line 4 "tests/01__basics/009__logic_or/test.code"
    {
#line 4 "tests/01__basics/009__logic_or/test.code"
        bool __001__;
#line 4 "tests/01__basics/009__logic_or/test.code"
        bool __002__ = t;
#line 4 "tests/01__basics/009__logic_or/test.code"
        if (__002__) {
#line 4 "tests/01__basics/009__logic_or/test.code"
            __001__ = __002__;
        } else {
#line 4 "tests/01__basics/009__logic_or/test.code"
            bool __003__ = f;
#line 4 "tests/01__basics/009__logic_or/test.code"
            __001__ = __003__;
        }
#line 4 "tests/01__basics/009__logic_or/test.code"
        if (__001__) {
        } else {
#line 7 "tests/01__basics/009__logic_or/test.code"
            return 1;
        }
    }
#line 9 "tests/01__basics/009__logic_or/test.code"
    {
#line 9 "tests/01__basics/009__logic_or/test.code"
        bool __001__;
#line 9 "tests/01__basics/009__logic_or/test.code"
        bool __002__ = f;
#line 9 "tests/01__basics/009__logic_or/test.code"
        if (__002__) {
#line 9 "tests/01__basics/009__logic_or/test.code"
            __001__ = __002__;
        } else {
#line 9 "tests/01__basics/009__logic_or/test.code"
            bool __003__ = t;
#line 9 "tests/01__basics/009__logic_or/test.code"
            __001__ = __003__;
        }
#line 9 "tests/01__basics/009__logic_or/test.code"
        if (__001__) {
        } else {
#line 12 "tests/01__basics/009__logic_or/test.code"
            return 2;
        }
    }
#line 14 "tests/01__basics/009__logic_or/test.code"
    {
#line 14 "tests/01__basics/009__logic_or/test.code"
        bool __001__;
#line 14 "tests/01__basics/009__logic_or/test.code"
        bool __002__ = t;
#line 14 "tests/01__basics/009__logic_or/test.code"
        if (__002__) {
#line 14 "tests/01__basics/009__logic_or/test.code"
            __001__ = __002__;
        } else {
#line 14 "tests/01__basics/009__logic_or/test.code"
            bool __003__ = t;
#line 14 "tests/01__basics/009__logic_or/test.code"
            __001__ = __003__;
        }
#line 14 "tests/01__basics/009__logic_or/test.code"
        if (__001__) {
        } else {
#line 17 "tests/01__basics/009__logic_or/test.code"
            return 3;
        }
    }
#line 19 "tests/01__basics/009__logic_or/test.code"
    {
#line 19 "tests/01__basics/009__logic_or/test.code"
        bool __001__;
#line 19 "tests/01__basics/009__logic_or/test.code"
        bool __002__ = f;
#line 19 "tests/01__basics/009__logic_or/test.code"
        if (__002__) {
#line 19 "tests/01__basics/009__logic_or/test.code"
            __001__ = __002__;
        } else {
#line 19 "tests/01__basics/009__logic_or/test.code"
            bool __003__ = f;
#line 19 "tests/01__basics/009__logic_or/test.code"
            __001__ = __003__;
        }
#line 19 "tests/01__basics/009__logic_or/test.code"
        if (__001__) {
#line 20 "tests/01__basics/009__logic_or/test.code"
            return 4;
        }
    }
#line 22 "tests/01__basics/009__logic_or/test.code"
    {
#line 22 "tests/01__basics/009__logic_or/test.code"
        bool __001__;
#line 22 "tests/01__basics/009__logic_or/test.code"
        bool __002__;
#line 22 "tests/01__basics/009__logic_or/test.code"
        bool __003__ = f;
#line 22 "tests/01__basics/009__logic_or/test.code"
        if (__003__) {
#line 22 "tests/01__basics/009__logic_or/test.code"
            __002__ = __003__;
        } else {
#line 22 "tests/01__basics/009__logic_or/test.code"
            bool __004__ = f;
#line 22 "tests/01__basics/009__logic_or/test.code"
            __002__ = __004__;
        }
#line 22 "tests/01__basics/009__logic_or/test.code"
        bool __005__ = (__002__);
#line 22 "tests/01__basics/009__logic_or/test.code"
        if (__005__) {
#line 22 "tests/01__basics/009__logic_or/test.code"
            __001__ = __005__;
        } else {
#line 22 "tests/01__basics/009__logic_or/test.code"
            bool __006__;
#line 22 "tests/01__basics/009__logic_or/test.code"
            bool __007__ = f;
#line 22 "tests/01__basics/009__logic_or/test.code"
            if (__007__) {
#line 22 "tests/01__basics/009__logic_or/test.code"
                __006__ = __007__;
            } else {
#line 22 "tests/01__basics/009__logic_or/test.code"
                bool __008__ = f;
#line 22 "tests/01__basics/009__logic_or/test.code"
                __006__ = __008__;
            }
#line 22 "tests/01__basics/009__logic_or/test.code"
            bool __009__ = (__006__);
#line 22 "tests/01__basics/009__logic_or/test.code"
            __001__ = __009__;
        }
#line 22 "tests/01__basics/009__logic_or/test.code"
        if (__001__) {
#line 23 "tests/01__basics/009__logic_or/test.code"
            return 5;
        }
    }
#line 25 "tests/01__basics/009__logic_or/test.code"
    return 0;
}

#line 28 "tests/01__basics/009__logic_or/test.code"
bool test__echo(bool v) {
#line 29 "tests/01__basics/009__logic_or/test.code"
    return v;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

