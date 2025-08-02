#include "test.h"

#line 1 "tests/01__basics/010__boolean_logic/test.code"
int32_t test__main() {
#line 2 "tests/01__basics/010__boolean_logic/test.code"
    bool check1 = true;
#line 3 "tests/01__basics/010__boolean_logic/test.code"
    bool check2 = false;
#line 4 "tests/01__basics/010__boolean_logic/test.code"
    bool check3 = true;
#line 5 "tests/01__basics/010__boolean_logic/test.code"
    bool check4 = false;
#line 6 "tests/01__basics/010__boolean_logic/test.code"
    bool check5 = true;
#line 7 "tests/01__basics/010__boolean_logic/test.code"
    bool check6 = false;
#line 9 "tests/01__basics/010__boolean_logic/test.code"
    if (check1) {
    } else {
#line 12 "tests/01__basics/010__boolean_logic/test.code"
        return 1;
    }
#line 15 "tests/01__basics/010__boolean_logic/test.code"
    if (!check1) {
#line 16 "tests/01__basics/010__boolean_logic/test.code"
        return 2;
    }
#line 19 "tests/01__basics/010__boolean_logic/test.code"
    if (check2) {
#line 20 "tests/01__basics/010__boolean_logic/test.code"
        return 3;
    }
#line 23 "tests/01__basics/010__boolean_logic/test.code"
    if (!check2) {
    } else {
#line 26 "tests/01__basics/010__boolean_logic/test.code"
        return 4;
    }
#line 29 "tests/01__basics/010__boolean_logic/test.code"
    {
#line 29 "tests/01__basics/010__boolean_logic/test.code"
        bool __001__ = check1;
#line 29 "tests/01__basics/010__boolean_logic/test.code"
        if (__001__) {
#line 29 "tests/01__basics/010__boolean_logic/test.code"
            __001__ = check2;
        }
#line 29 "tests/01__basics/010__boolean_logic/test.code"
        if (__001__) {
#line 30 "tests/01__basics/010__boolean_logic/test.code"
            return 5;
        }
    }
#line 33 "tests/01__basics/010__boolean_logic/test.code"
    {
#line 33 "tests/01__basics/010__boolean_logic/test.code"
        bool __001__ = check1;
#line 33 "tests/01__basics/010__boolean_logic/test.code"
        if (__001__) {
#line 33 "tests/01__basics/010__boolean_logic/test.code"
            __001__ = check2;
        }
#line 33 "tests/01__basics/010__boolean_logic/test.code"
        if (!(__001__)) {
        } else {
#line 36 "tests/01__basics/010__boolean_logic/test.code"
            return 6;
        }
    }
#line 39 "tests/01__basics/010__boolean_logic/test.code"
    {
#line 39 "tests/01__basics/010__boolean_logic/test.code"
        bool __001__ = check1;
#line 39 "tests/01__basics/010__boolean_logic/test.code"
        if (__001__) {
#line 39 "tests/01__basics/010__boolean_logic/test.code"
            __001__ = check2;
        }
#line 39 "tests/01__basics/010__boolean_logic/test.code"
        if (!!(__001__)) {
#line 40 "tests/01__basics/010__boolean_logic/test.code"
            return 7;
        } else {
        }
    }
#line 45 "tests/01__basics/010__boolean_logic/test.code"
    {
#line 45 "tests/01__basics/010__boolean_logic/test.code"
        bool __001__ = check1;
#line 45 "tests/01__basics/010__boolean_logic/test.code"
        if (__001__) {} else {
#line 45 "tests/01__basics/010__boolean_logic/test.code"
            __001__ = check2;
        }
#line 45 "tests/01__basics/010__boolean_logic/test.code"
        if (__001__) {
        } else {
#line 48 "tests/01__basics/010__boolean_logic/test.code"
            return 8;
        }
    }
#line 51 "tests/01__basics/010__boolean_logic/test.code"
    {
#line 51 "tests/01__basics/010__boolean_logic/test.code"
        bool __001__ = check1;
#line 51 "tests/01__basics/010__boolean_logic/test.code"
        if (__001__) {} else {
#line 51 "tests/01__basics/010__boolean_logic/test.code"
            __001__ = check2;
        }
#line 51 "tests/01__basics/010__boolean_logic/test.code"
        if (!(__001__)) {
#line 52 "tests/01__basics/010__boolean_logic/test.code"
            return 9;
        } else {
        }
    }
#line 57 "tests/01__basics/010__boolean_logic/test.code"
    {
#line 57 "tests/01__basics/010__boolean_logic/test.code"
        bool __001__ = check1;
#line 57 "tests/01__basics/010__boolean_logic/test.code"
        if (__001__) {
#line 57 "tests/01__basics/010__boolean_logic/test.code"
            __001__ = check2;
        }
#line 57 "tests/01__basics/010__boolean_logic/test.code"
        bool __002__ = (__001__);
#line 57 "tests/01__basics/010__boolean_logic/test.code"
        if (__002__) {} else {
#line 57 "tests/01__basics/010__boolean_logic/test.code"
            bool __003__ = check3;
#line 57 "tests/01__basics/010__boolean_logic/test.code"
            if (__003__) {
#line 57 "tests/01__basics/010__boolean_logic/test.code"
                __003__ = check4;
            }
#line 57 "tests/01__basics/010__boolean_logic/test.code"
            __002__ = (__003__);
        }
#line 57 "tests/01__basics/010__boolean_logic/test.code"
        if (__002__) {
#line 58 "tests/01__basics/010__boolean_logic/test.code"
            return 10;
        }
    }
#line 61 "tests/01__basics/010__boolean_logic/test.code"
    {
#line 61 "tests/01__basics/010__boolean_logic/test.code"
        bool __001__ = check2;
#line 61 "tests/01__basics/010__boolean_logic/test.code"
        if (__001__) {
#line 61 "tests/01__basics/010__boolean_logic/test.code"
            __001__ = check4;
        }
#line 61 "tests/01__basics/010__boolean_logic/test.code"
        bool __002__ = (__001__);
#line 61 "tests/01__basics/010__boolean_logic/test.code"
        if (__002__) {} else {
#line 61 "tests/01__basics/010__boolean_logic/test.code"
            bool __003__ = check1;
#line 61 "tests/01__basics/010__boolean_logic/test.code"
            if (__003__) {
#line 61 "tests/01__basics/010__boolean_logic/test.code"
                __003__ = check3;
            }
#line 61 "tests/01__basics/010__boolean_logic/test.code"
            __002__ = (__003__);
        }
#line 61 "tests/01__basics/010__boolean_logic/test.code"
        if (__002__) {
        } else {
#line 64 "tests/01__basics/010__boolean_logic/test.code"
            return 11;
        }
    }
#line 67 "tests/01__basics/010__boolean_logic/test.code"
    {
#line 67 "tests/01__basics/010__boolean_logic/test.code"
        bool __001__ = check1;
#line 67 "tests/01__basics/010__boolean_logic/test.code"
        if (__001__) {
#line 67 "tests/01__basics/010__boolean_logic/test.code"
            bool __002__ = check2;
#line 67 "tests/01__basics/010__boolean_logic/test.code"
            if (__002__) {} else {
#line 67 "tests/01__basics/010__boolean_logic/test.code"
                __002__ = check3;
            }
#line 67 "tests/01__basics/010__boolean_logic/test.code"
            __001__ = (__002__);
        }
#line 67 "tests/01__basics/010__boolean_logic/test.code"
        bool __003__ = __001__;
#line 67 "tests/01__basics/010__boolean_logic/test.code"
        if (__003__) {
#line 67 "tests/01__basics/010__boolean_logic/test.code"
            __003__ = check4;
        }
#line 67 "tests/01__basics/010__boolean_logic/test.code"
        if (__003__) {
#line 68 "tests/01__basics/010__boolean_logic/test.code"
            return 12;
        } else {
        }
    }
#line 73 "tests/01__basics/010__boolean_logic/test.code"
    {
#line 73 "tests/01__basics/010__boolean_logic/test.code"
        bool __001__ = check1;
#line 73 "tests/01__basics/010__boolean_logic/test.code"
        if (__001__) {} else {
#line 73 "tests/01__basics/010__boolean_logic/test.code"
            __001__ = check2;
        }
#line 73 "tests/01__basics/010__boolean_logic/test.code"
        bool __002__ = (__001__);
#line 73 "tests/01__basics/010__boolean_logic/test.code"
        if (__002__) {
#line 73 "tests/01__basics/010__boolean_logic/test.code"
            bool __003__ = check3;
#line 73 "tests/01__basics/010__boolean_logic/test.code"
            if (__003__) {} else {
#line 73 "tests/01__basics/010__boolean_logic/test.code"
                __003__ = check4;
            }
#line 73 "tests/01__basics/010__boolean_logic/test.code"
            __002__ = (__003__);
        }
#line 73 "tests/01__basics/010__boolean_logic/test.code"
        if (__002__) {
        } else {
#line 76 "tests/01__basics/010__boolean_logic/test.code"
            return 13;
        }
    }
#line 79 "tests/01__basics/010__boolean_logic/test.code"
    {
#line 79 "tests/01__basics/010__boolean_logic/test.code"
        bool __001__ = check1;
#line 79 "tests/01__basics/010__boolean_logic/test.code"
        if (__001__) {} else {
#line 79 "tests/01__basics/010__boolean_logic/test.code"
            __001__ = check4;
        }
#line 79 "tests/01__basics/010__boolean_logic/test.code"
        bool __002__ = (__001__);
#line 79 "tests/01__basics/010__boolean_logic/test.code"
        if (__002__) {
#line 79 "tests/01__basics/010__boolean_logic/test.code"
            bool __003__ = check2;
#line 79 "tests/01__basics/010__boolean_logic/test.code"
            if (__003__) {} else {
#line 79 "tests/01__basics/010__boolean_logic/test.code"
                __003__ = check3;
            }
#line 79 "tests/01__basics/010__boolean_logic/test.code"
            __002__ = (__003__);
        }
#line 79 "tests/01__basics/010__boolean_logic/test.code"
        if (__002__) {
        } else {
#line 82 "tests/01__basics/010__boolean_logic/test.code"
            return 14;
        }
    }
#line 85 "tests/01__basics/010__boolean_logic/test.code"
    {
#line 85 "tests/01__basics/010__boolean_logic/test.code"
        bool __001__ = check2;
#line 85 "tests/01__basics/010__boolean_logic/test.code"
        if (__001__) {} else {
#line 85 "tests/01__basics/010__boolean_logic/test.code"
            bool __002__ = check3;
#line 85 "tests/01__basics/010__boolean_logic/test.code"
            if (__002__) {
#line 85 "tests/01__basics/010__boolean_logic/test.code"
                __002__ = check4;
            }
#line 85 "tests/01__basics/010__boolean_logic/test.code"
            __001__ = (__002__);
        }
#line 85 "tests/01__basics/010__boolean_logic/test.code"
        bool __003__ = __001__;
#line 85 "tests/01__basics/010__boolean_logic/test.code"
        if (__003__) {} else {
#line 85 "tests/01__basics/010__boolean_logic/test.code"
            __003__ = check5;
        }
#line 85 "tests/01__basics/010__boolean_logic/test.code"
        if (__003__) {
        } else {
#line 88 "tests/01__basics/010__boolean_logic/test.code"
            return 15;
        }
    }
#line 91 "tests/01__basics/010__boolean_logic/test.code"
    {
#line 91 "tests/01__basics/010__boolean_logic/test.code"
        bool __001__ = check1;
#line 91 "tests/01__basics/010__boolean_logic/test.code"
        if (__001__) {
#line 91 "tests/01__basics/010__boolean_logic/test.code"
            __001__ = check2;
        }
#line 91 "tests/01__basics/010__boolean_logic/test.code"
        bool __002__ = (__001__);
#line 91 "tests/01__basics/010__boolean_logic/test.code"
        if (__002__) {} else {
#line 91 "tests/01__basics/010__boolean_logic/test.code"
            bool __003__ = check3;
#line 91 "tests/01__basics/010__boolean_logic/test.code"
            if (__003__) {
#line 91 "tests/01__basics/010__boolean_logic/test.code"
                __003__ = check4;
            }
#line 91 "tests/01__basics/010__boolean_logic/test.code"
            __002__ = (__003__);
        }
#line 91 "tests/01__basics/010__boolean_logic/test.code"
        bool __004__ = (__002__);
#line 91 "tests/01__basics/010__boolean_logic/test.code"
        if (__004__) {
#line 91 "tests/01__basics/010__boolean_logic/test.code"
            __004__ = check5;
        }
#line 91 "tests/01__basics/010__boolean_logic/test.code"
        bool __005__ = (__004__);
#line 91 "tests/01__basics/010__boolean_logic/test.code"
        if (__005__) {} else {
#line 91 "tests/01__basics/010__boolean_logic/test.code"
            __005__ = check6;
        }
#line 91 "tests/01__basics/010__boolean_logic/test.code"
        if (__005__) {
#line 92 "tests/01__basics/010__boolean_logic/test.code"
            return 16;
        } else {
        }
    }
#line 97 "tests/01__basics/010__boolean_logic/test.code"
    {
#line 97 "tests/01__basics/010__boolean_logic/test.code"
        bool __001__ = check1;
#line 97 "tests/01__basics/010__boolean_logic/test.code"
        if (__001__) {
#line 97 "tests/01__basics/010__boolean_logic/test.code"
            __001__ = check2;
        }
#line 97 "tests/01__basics/010__boolean_logic/test.code"
        bool __002__ = (__001__);
#line 97 "tests/01__basics/010__boolean_logic/test.code"
        if (__002__) {} else {
#line 97 "tests/01__basics/010__boolean_logic/test.code"
            bool __003__ = check3;
#line 97 "tests/01__basics/010__boolean_logic/test.code"
            if (__003__) {
#line 97 "tests/01__basics/010__boolean_logic/test.code"
                __003__ = check4;
            }
#line 97 "tests/01__basics/010__boolean_logic/test.code"
            bool __004__ = (__003__);
#line 97 "tests/01__basics/010__boolean_logic/test.code"
            if (__004__) {} else {
#line 97 "tests/01__basics/010__boolean_logic/test.code"
                __004__ = check6;
            }
#line 97 "tests/01__basics/010__boolean_logic/test.code"
            bool __005__ = (__004__);
#line 97 "tests/01__basics/010__boolean_logic/test.code"
            if (__005__) {
#line 97 "tests/01__basics/010__boolean_logic/test.code"
                __005__ = check5;
            }
#line 97 "tests/01__basics/010__boolean_logic/test.code"
            __002__ = (__005__);
        }
#line 97 "tests/01__basics/010__boolean_logic/test.code"
        if (__002__) {
#line 98 "tests/01__basics/010__boolean_logic/test.code"
            return 17;
        }
    }
#line 101 "tests/01__basics/010__boolean_logic/test.code"
    {
#line 101 "tests/01__basics/010__boolean_logic/test.code"
        bool __001__ = check1;
#line 101 "tests/01__basics/010__boolean_logic/test.code"
        if (__001__) {
#line 101 "tests/01__basics/010__boolean_logic/test.code"
            __001__ = !check2;
        }
#line 101 "tests/01__basics/010__boolean_logic/test.code"
        if (__001__) {
        } else {
#line 104 "tests/01__basics/010__boolean_logic/test.code"
            return 18;
        }
    }
#line 107 "tests/01__basics/010__boolean_logic/test.code"
    {
#line 107 "tests/01__basics/010__boolean_logic/test.code"
        bool __001__ = !check1;
#line 107 "tests/01__basics/010__boolean_logic/test.code"
        if (__001__) {} else {
#line 107 "tests/01__basics/010__boolean_logic/test.code"
            __001__ = check2;
        }
#line 107 "tests/01__basics/010__boolean_logic/test.code"
        if (__001__) {
#line 108 "tests/01__basics/010__boolean_logic/test.code"
            return 19;
        }
    }
#line 111 "tests/01__basics/010__boolean_logic/test.code"
    return 0;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

