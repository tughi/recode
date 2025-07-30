#include "test.h"

#line 1 "tests/01__basics/009__logic_and/test.code"
int32_t test__main() {
#line 2 "tests/01__basics/009__logic_and/test.code"
    bool t = test__echo(true);
#line 3 "tests/01__basics/009__logic_and/test.code"
    bool f = test__echo(false);
#line 4 "tests/01__basics/009__logic_and/test.code"
    {
#line 4 "tests/01__basics/009__logic_and/test.code"
        bool __001__;
#line 4 "tests/01__basics/009__logic_and/test.code"
        bool __002__ = t;
#line 4 "tests/01__basics/009__logic_and/test.code"
        if (__002__) {
#line 4 "tests/01__basics/009__logic_and/test.code"
            bool __003__ = f;
#line 4 "tests/01__basics/009__logic_and/test.code"
            __001__ = __003__;
        } else {
#line 4 "tests/01__basics/009__logic_and/test.code"
            __001__ = __002__;
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
        bool __001__;
#line 7 "tests/01__basics/009__logic_and/test.code"
        bool __002__ = f;
#line 7 "tests/01__basics/009__logic_and/test.code"
        if (__002__) {
#line 7 "tests/01__basics/009__logic_and/test.code"
            bool __003__ = t;
#line 7 "tests/01__basics/009__logic_and/test.code"
            __001__ = __003__;
        } else {
#line 7 "tests/01__basics/009__logic_and/test.code"
            __001__ = __002__;
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
        bool __001__;
#line 10 "tests/01__basics/009__logic_and/test.code"
        bool __002__ = t;
#line 10 "tests/01__basics/009__logic_and/test.code"
        if (__002__) {
#line 10 "tests/01__basics/009__logic_and/test.code"
            bool __003__ = t;
#line 10 "tests/01__basics/009__logic_and/test.code"
            __001__ = __003__;
        } else {
#line 10 "tests/01__basics/009__logic_and/test.code"
            __001__ = __002__;
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
        bool __001__;
#line 15 "tests/01__basics/009__logic_and/test.code"
        bool __002__ = f;
#line 15 "tests/01__basics/009__logic_and/test.code"
        if (__002__) {
#line 15 "tests/01__basics/009__logic_and/test.code"
            bool __003__ = f;
#line 15 "tests/01__basics/009__logic_and/test.code"
            __001__ = __003__;
        } else {
#line 15 "tests/01__basics/009__logic_and/test.code"
            __001__ = __002__;
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
        bool __001__;
#line 18 "tests/01__basics/009__logic_and/test.code"
        bool __002__;
#line 18 "tests/01__basics/009__logic_and/test.code"
        bool __003__ = t;
#line 18 "tests/01__basics/009__logic_and/test.code"
        if (__003__) {
#line 18 "tests/01__basics/009__logic_and/test.code"
            bool __004__ = t;
#line 18 "tests/01__basics/009__logic_and/test.code"
            __002__ = __004__;
        } else {
#line 18 "tests/01__basics/009__logic_and/test.code"
            __002__ = __003__;
        }
#line 18 "tests/01__basics/009__logic_and/test.code"
        bool __005__ = (__002__);
#line 18 "tests/01__basics/009__logic_and/test.code"
        if (__005__) {
#line 18 "tests/01__basics/009__logic_and/test.code"
            bool __006__;
#line 18 "tests/01__basics/009__logic_and/test.code"
            bool __007__ = f;
#line 18 "tests/01__basics/009__logic_and/test.code"
            if (__007__) {
#line 18 "tests/01__basics/009__logic_and/test.code"
                bool __008__ = f;
#line 18 "tests/01__basics/009__logic_and/test.code"
                __006__ = __008__;
            } else {
#line 18 "tests/01__basics/009__logic_and/test.code"
                __006__ = __007__;
            }
#line 18 "tests/01__basics/009__logic_and/test.code"
            bool __009__ = (__006__);
#line 18 "tests/01__basics/009__logic_and/test.code"
            __001__ = __009__;
        } else {
#line 18 "tests/01__basics/009__logic_and/test.code"
            __001__ = __005__;
        }
#line 18 "tests/01__basics/009__logic_and/test.code"
        if (__001__) {
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

