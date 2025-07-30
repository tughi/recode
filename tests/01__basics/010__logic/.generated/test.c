#include "test.h"

#line 1 "tests/01__basics/010__logic/test.code"
int32_t test__main() {
#line 2 "tests/01__basics/010__logic/test.code"
    bool t = test__echo(true);
#line 3 "tests/01__basics/010__logic/test.code"
    bool f = test__echo(false);
#line 4 "tests/01__basics/010__logic/test.code"
    {
#line 4 "tests/01__basics/010__logic/test.code"
        bool __001__;
#line 4 "tests/01__basics/010__logic/test.code"
        bool __002__;
#line 4 "tests/01__basics/010__logic/test.code"
        bool __003__;
#line 4 "tests/01__basics/010__logic/test.code"
        bool __004__ = t;
#line 4 "tests/01__basics/010__logic/test.code"
        if (__004__) {
#line 4 "tests/01__basics/010__logic/test.code"
            bool __005__ = f;
#line 4 "tests/01__basics/010__logic/test.code"
            __003__ = __005__;
        } else {
#line 4 "tests/01__basics/010__logic/test.code"
            __003__ = __004__;
        }
#line 4 "tests/01__basics/010__logic/test.code"
        bool __006__ = __003__;
#line 4 "tests/01__basics/010__logic/test.code"
        if (__006__) {
#line 4 "tests/01__basics/010__logic/test.code"
            __002__ = __006__;
        } else {
#line 4 "tests/01__basics/010__logic/test.code"
            bool __007__;
#line 4 "tests/01__basics/010__logic/test.code"
            bool __008__ = f;
#line 4 "tests/01__basics/010__logic/test.code"
            if (__008__) {
#line 4 "tests/01__basics/010__logic/test.code"
                bool __009__ = t;
#line 4 "tests/01__basics/010__logic/test.code"
                __007__ = __009__;
            } else {
#line 4 "tests/01__basics/010__logic/test.code"
                __007__ = __008__;
            }
#line 4 "tests/01__basics/010__logic/test.code"
            bool __010__ = __007__;
#line 4 "tests/01__basics/010__logic/test.code"
            __002__ = __010__;
        }
#line 4 "tests/01__basics/010__logic/test.code"
        bool __011__ = (__002__);
#line 4 "tests/01__basics/010__logic/test.code"
        if (__011__) {
#line 4 "tests/01__basics/010__logic/test.code"
            __001__ = __011__;
        } else {
#line 4 "tests/01__basics/010__logic/test.code"
            bool __012__;
#line 4 "tests/01__basics/010__logic/test.code"
            bool __013__;
#line 4 "tests/01__basics/010__logic/test.code"
            bool __014__ = t;
#line 4 "tests/01__basics/010__logic/test.code"
            if (__014__) {
#line 4 "tests/01__basics/010__logic/test.code"
                __013__ = __014__;
            } else {
#line 4 "tests/01__basics/010__logic/test.code"
                bool __015__ = f;
#line 4 "tests/01__basics/010__logic/test.code"
                __013__ = __015__;
            }
#line 4 "tests/01__basics/010__logic/test.code"
            bool __016__ = (__013__);
#line 4 "tests/01__basics/010__logic/test.code"
            if (__016__) {
#line 4 "tests/01__basics/010__logic/test.code"
                bool __017__;
#line 4 "tests/01__basics/010__logic/test.code"
                bool __018__ = f;
#line 4 "tests/01__basics/010__logic/test.code"
                if (__018__) {
#line 4 "tests/01__basics/010__logic/test.code"
                    __017__ = __018__;
                } else {
#line 4 "tests/01__basics/010__logic/test.code"
                    bool __019__ = t;
#line 4 "tests/01__basics/010__logic/test.code"
                    __017__ = __019__;
                }
#line 4 "tests/01__basics/010__logic/test.code"
                bool __020__ = (__017__);
#line 4 "tests/01__basics/010__logic/test.code"
                __012__ = __020__;
            } else {
#line 4 "tests/01__basics/010__logic/test.code"
                __012__ = __016__;
            }
#line 4 "tests/01__basics/010__logic/test.code"
            bool __021__ = !(__012__);
#line 4 "tests/01__basics/010__logic/test.code"
            __001__ = __021__;
        }
#line 4 "tests/01__basics/010__logic/test.code"
        if (__001__) {
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

