#include "test.h"

#line 1 "tests/01__basics/010__logic/test.code"
int32_t test__main() {
#line 2 "tests/01__basics/010__logic/test.code"
    bool t;
#line 2 "tests/01__basics/010__logic/test.code"
    {
#line 2 "tests/01__basics/010__logic/test.code"
        bool __001__ = true;
#line 2 "tests/01__basics/010__logic/test.code"
        t = test__echo(__001__);
    }
#line 3 "tests/01__basics/010__logic/test.code"
    bool f;
#line 3 "tests/01__basics/010__logic/test.code"
    {
#line 3 "tests/01__basics/010__logic/test.code"
        bool __001__ = false;
#line 3 "tests/01__basics/010__logic/test.code"
        f = test__echo(__001__);
    }
#line 4 "tests/01__basics/010__logic/test.code"
    {
#line 4 "tests/01__basics/010__logic/test.code"
        bool __001__ = t;
#line 4 "tests/01__basics/010__logic/test.code"
        if (__001__) {
#line 4 "tests/01__basics/010__logic/test.code"
            __001__ = f;
        }
#line 4 "tests/01__basics/010__logic/test.code"
        bool __002__ = __001__;
#line 4 "tests/01__basics/010__logic/test.code"
        if (__002__) {} else {
#line 4 "tests/01__basics/010__logic/test.code"
            bool __003__ = f;
#line 4 "tests/01__basics/010__logic/test.code"
            if (__003__) {
#line 4 "tests/01__basics/010__logic/test.code"
                __003__ = t;
            }
#line 4 "tests/01__basics/010__logic/test.code"
            __002__ = __003__;
        }
#line 4 "tests/01__basics/010__logic/test.code"
        bool __004__ = (__002__);
#line 4 "tests/01__basics/010__logic/test.code"
        if (__004__) {} else {
#line 4 "tests/01__basics/010__logic/test.code"
            bool __005__ = t;
#line 4 "tests/01__basics/010__logic/test.code"
            if (__005__) {} else {
#line 4 "tests/01__basics/010__logic/test.code"
                __005__ = f;
            }
#line 4 "tests/01__basics/010__logic/test.code"
            bool __006__ = (__005__);
#line 4 "tests/01__basics/010__logic/test.code"
            if (__006__) {
#line 4 "tests/01__basics/010__logic/test.code"
                bool __007__ = f;
#line 4 "tests/01__basics/010__logic/test.code"
                if (__007__) {} else {
#line 4 "tests/01__basics/010__logic/test.code"
                    __007__ = t;
                }
#line 4 "tests/01__basics/010__logic/test.code"
                __006__ = (__007__);
            }
#line 4 "tests/01__basics/010__logic/test.code"
            __004__ = !(__006__);
        }
#line 4 "tests/01__basics/010__logic/test.code"
        if (__004__) {
#line 5 "tests/01__basics/010__logic/test.code"
            return 1;
        }
    }
#line 7 "tests/01__basics/010__logic/test.code"
    return 0;
}

#line 10 "tests/01__basics/010__logic/test.code"
bool test__echo(bool v) {
#line 11 "tests/01__basics/010__logic/test.code"
    return v;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

