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
        bool __001__;
#line 29 "tests/01__basics/010__boolean_logic/test.code"
        bool __002__ = check1;
#line 29 "tests/01__basics/010__boolean_logic/test.code"
        if (__002__) {
#line 29 "tests/01__basics/010__boolean_logic/test.code"
            bool __003__ = check2;
#line 29 "tests/01__basics/010__boolean_logic/test.code"
            __001__ = __003__;
        } else {
#line 29 "tests/01__basics/010__boolean_logic/test.code"
            __001__ = __002__;
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
        bool __001__;
#line 33 "tests/01__basics/010__boolean_logic/test.code"
        bool __002__ = check1;
#line 33 "tests/01__basics/010__boolean_logic/test.code"
        if (__002__) {
#line 33 "tests/01__basics/010__boolean_logic/test.code"
            bool __003__ = check2;
#line 33 "tests/01__basics/010__boolean_logic/test.code"
            __001__ = __003__;
        } else {
#line 33 "tests/01__basics/010__boolean_logic/test.code"
            __001__ = __002__;
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
        bool __001__;
#line 39 "tests/01__basics/010__boolean_logic/test.code"
        bool __002__ = check1;
#line 39 "tests/01__basics/010__boolean_logic/test.code"
        if (__002__) {
#line 39 "tests/01__basics/010__boolean_logic/test.code"
            bool __003__ = check2;
#line 39 "tests/01__basics/010__boolean_logic/test.code"
            __001__ = __003__;
        } else {
#line 39 "tests/01__basics/010__boolean_logic/test.code"
            __001__ = __002__;
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
        bool __001__;
#line 45 "tests/01__basics/010__boolean_logic/test.code"
        bool __002__ = check1;
#line 45 "tests/01__basics/010__boolean_logic/test.code"
        if (__002__) {
#line 45 "tests/01__basics/010__boolean_logic/test.code"
            __001__ = __002__;
        } else {
#line 45 "tests/01__basics/010__boolean_logic/test.code"
            bool __003__ = check2;
#line 45 "tests/01__basics/010__boolean_logic/test.code"
            __001__ = __003__;
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
        bool __001__;
#line 51 "tests/01__basics/010__boolean_logic/test.code"
        bool __002__ = check1;
#line 51 "tests/01__basics/010__boolean_logic/test.code"
        if (__002__) {
#line 51 "tests/01__basics/010__boolean_logic/test.code"
            __001__ = __002__;
        } else {
#line 51 "tests/01__basics/010__boolean_logic/test.code"
            bool __003__ = check2;
#line 51 "tests/01__basics/010__boolean_logic/test.code"
            __001__ = __003__;
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
        bool __001__;
#line 57 "tests/01__basics/010__boolean_logic/test.code"
        bool __002__;
#line 57 "tests/01__basics/010__boolean_logic/test.code"
        bool __003__ = check1;
#line 57 "tests/01__basics/010__boolean_logic/test.code"
        if (__003__) {
#line 57 "tests/01__basics/010__boolean_logic/test.code"
            bool __004__ = check2;
#line 57 "tests/01__basics/010__boolean_logic/test.code"
            __002__ = __004__;
        } else {
#line 57 "tests/01__basics/010__boolean_logic/test.code"
            __002__ = __003__;
        }
#line 57 "tests/01__basics/010__boolean_logic/test.code"
        bool __005__ = (__002__);
#line 57 "tests/01__basics/010__boolean_logic/test.code"
        if (__005__) {
#line 57 "tests/01__basics/010__boolean_logic/test.code"
            __001__ = __005__;
        } else {
#line 57 "tests/01__basics/010__boolean_logic/test.code"
            bool __006__;
#line 57 "tests/01__basics/010__boolean_logic/test.code"
            bool __007__ = check3;
#line 57 "tests/01__basics/010__boolean_logic/test.code"
            if (__007__) {
#line 57 "tests/01__basics/010__boolean_logic/test.code"
                bool __008__ = check4;
#line 57 "tests/01__basics/010__boolean_logic/test.code"
                __006__ = __008__;
            } else {
#line 57 "tests/01__basics/010__boolean_logic/test.code"
                __006__ = __007__;
            }
#line 57 "tests/01__basics/010__boolean_logic/test.code"
            bool __009__ = (__006__);
#line 57 "tests/01__basics/010__boolean_logic/test.code"
            __001__ = __009__;
        }
#line 57 "tests/01__basics/010__boolean_logic/test.code"
        if (__001__) {
#line 58 "tests/01__basics/010__boolean_logic/test.code"
            return 10;
        }
    }
#line 61 "tests/01__basics/010__boolean_logic/test.code"
    {
#line 61 "tests/01__basics/010__boolean_logic/test.code"
        bool __001__;
#line 61 "tests/01__basics/010__boolean_logic/test.code"
        bool __002__;
#line 61 "tests/01__basics/010__boolean_logic/test.code"
        bool __003__ = check2;
#line 61 "tests/01__basics/010__boolean_logic/test.code"
        if (__003__) {
#line 61 "tests/01__basics/010__boolean_logic/test.code"
            bool __004__ = check4;
#line 61 "tests/01__basics/010__boolean_logic/test.code"
            __002__ = __004__;
        } else {
#line 61 "tests/01__basics/010__boolean_logic/test.code"
            __002__ = __003__;
        }
#line 61 "tests/01__basics/010__boolean_logic/test.code"
        bool __005__ = (__002__);
#line 61 "tests/01__basics/010__boolean_logic/test.code"
        if (__005__) {
#line 61 "tests/01__basics/010__boolean_logic/test.code"
            __001__ = __005__;
        } else {
#line 61 "tests/01__basics/010__boolean_logic/test.code"
            bool __006__;
#line 61 "tests/01__basics/010__boolean_logic/test.code"
            bool __007__ = check1;
#line 61 "tests/01__basics/010__boolean_logic/test.code"
            if (__007__) {
#line 61 "tests/01__basics/010__boolean_logic/test.code"
                bool __008__ = check3;
#line 61 "tests/01__basics/010__boolean_logic/test.code"
                __006__ = __008__;
            } else {
#line 61 "tests/01__basics/010__boolean_logic/test.code"
                __006__ = __007__;
            }
#line 61 "tests/01__basics/010__boolean_logic/test.code"
            bool __009__ = (__006__);
#line 61 "tests/01__basics/010__boolean_logic/test.code"
            __001__ = __009__;
        }
#line 61 "tests/01__basics/010__boolean_logic/test.code"
        if (__001__) {
        } else {
#line 64 "tests/01__basics/010__boolean_logic/test.code"
            return 11;
        }
    }
#line 67 "tests/01__basics/010__boolean_logic/test.code"
    {
#line 67 "tests/01__basics/010__boolean_logic/test.code"
        bool __001__;
#line 67 "tests/01__basics/010__boolean_logic/test.code"
        bool __002__;
#line 67 "tests/01__basics/010__boolean_logic/test.code"
        bool __003__ = check1;
#line 67 "tests/01__basics/010__boolean_logic/test.code"
        if (__003__) {
#line 67 "tests/01__basics/010__boolean_logic/test.code"
            bool __004__;
#line 67 "tests/01__basics/010__boolean_logic/test.code"
            bool __005__ = check2;
#line 67 "tests/01__basics/010__boolean_logic/test.code"
            if (__005__) {
#line 67 "tests/01__basics/010__boolean_logic/test.code"
                __004__ = __005__;
            } else {
#line 67 "tests/01__basics/010__boolean_logic/test.code"
                bool __006__ = check3;
#line 67 "tests/01__basics/010__boolean_logic/test.code"
                __004__ = __006__;
            }
#line 67 "tests/01__basics/010__boolean_logic/test.code"
            bool __007__ = (__004__);
#line 67 "tests/01__basics/010__boolean_logic/test.code"
            __002__ = __007__;
        } else {
#line 67 "tests/01__basics/010__boolean_logic/test.code"
            __002__ = __003__;
        }
#line 67 "tests/01__basics/010__boolean_logic/test.code"
        bool __008__ = __002__;
#line 67 "tests/01__basics/010__boolean_logic/test.code"
        if (__008__) {
#line 67 "tests/01__basics/010__boolean_logic/test.code"
            bool __009__ = check4;
#line 67 "tests/01__basics/010__boolean_logic/test.code"
            __001__ = __009__;
        } else {
#line 67 "tests/01__basics/010__boolean_logic/test.code"
            __001__ = __008__;
        }
#line 67 "tests/01__basics/010__boolean_logic/test.code"
        if (__001__) {
#line 68 "tests/01__basics/010__boolean_logic/test.code"
            return 12;
        } else {
        }
    }
#line 73 "tests/01__basics/010__boolean_logic/test.code"
    {
#line 73 "tests/01__basics/010__boolean_logic/test.code"
        bool __001__;
#line 73 "tests/01__basics/010__boolean_logic/test.code"
        bool __002__;
#line 73 "tests/01__basics/010__boolean_logic/test.code"
        bool __003__ = check1;
#line 73 "tests/01__basics/010__boolean_logic/test.code"
        if (__003__) {
#line 73 "tests/01__basics/010__boolean_logic/test.code"
            __002__ = __003__;
        } else {
#line 73 "tests/01__basics/010__boolean_logic/test.code"
            bool __004__ = check2;
#line 73 "tests/01__basics/010__boolean_logic/test.code"
            __002__ = __004__;
        }
#line 73 "tests/01__basics/010__boolean_logic/test.code"
        bool __005__ = (__002__);
#line 73 "tests/01__basics/010__boolean_logic/test.code"
        if (__005__) {
#line 73 "tests/01__basics/010__boolean_logic/test.code"
            bool __006__;
#line 73 "tests/01__basics/010__boolean_logic/test.code"
            bool __007__ = check3;
#line 73 "tests/01__basics/010__boolean_logic/test.code"
            if (__007__) {
#line 73 "tests/01__basics/010__boolean_logic/test.code"
                __006__ = __007__;
            } else {
#line 73 "tests/01__basics/010__boolean_logic/test.code"
                bool __008__ = check4;
#line 73 "tests/01__basics/010__boolean_logic/test.code"
                __006__ = __008__;
            }
#line 73 "tests/01__basics/010__boolean_logic/test.code"
            bool __009__ = (__006__);
#line 73 "tests/01__basics/010__boolean_logic/test.code"
            __001__ = __009__;
        } else {
#line 73 "tests/01__basics/010__boolean_logic/test.code"
            __001__ = __005__;
        }
#line 73 "tests/01__basics/010__boolean_logic/test.code"
        if (__001__) {
        } else {
#line 76 "tests/01__basics/010__boolean_logic/test.code"
            return 13;
        }
    }
#line 79 "tests/01__basics/010__boolean_logic/test.code"
    {
#line 79 "tests/01__basics/010__boolean_logic/test.code"
        bool __001__;
#line 79 "tests/01__basics/010__boolean_logic/test.code"
        bool __002__;
#line 79 "tests/01__basics/010__boolean_logic/test.code"
        bool __003__ = check1;
#line 79 "tests/01__basics/010__boolean_logic/test.code"
        if (__003__) {
#line 79 "tests/01__basics/010__boolean_logic/test.code"
            __002__ = __003__;
        } else {
#line 79 "tests/01__basics/010__boolean_logic/test.code"
            bool __004__ = check4;
#line 79 "tests/01__basics/010__boolean_logic/test.code"
            __002__ = __004__;
        }
#line 79 "tests/01__basics/010__boolean_logic/test.code"
        bool __005__ = (__002__);
#line 79 "tests/01__basics/010__boolean_logic/test.code"
        if (__005__) {
#line 79 "tests/01__basics/010__boolean_logic/test.code"
            bool __006__;
#line 79 "tests/01__basics/010__boolean_logic/test.code"
            bool __007__ = check2;
#line 79 "tests/01__basics/010__boolean_logic/test.code"
            if (__007__) {
#line 79 "tests/01__basics/010__boolean_logic/test.code"
                __006__ = __007__;
            } else {
#line 79 "tests/01__basics/010__boolean_logic/test.code"
                bool __008__ = check3;
#line 79 "tests/01__basics/010__boolean_logic/test.code"
                __006__ = __008__;
            }
#line 79 "tests/01__basics/010__boolean_logic/test.code"
            bool __009__ = (__006__);
#line 79 "tests/01__basics/010__boolean_logic/test.code"
            __001__ = __009__;
        } else {
#line 79 "tests/01__basics/010__boolean_logic/test.code"
            __001__ = __005__;
        }
#line 79 "tests/01__basics/010__boolean_logic/test.code"
        if (__001__) {
        } else {
#line 82 "tests/01__basics/010__boolean_logic/test.code"
            return 14;
        }
    }
#line 85 "tests/01__basics/010__boolean_logic/test.code"
    {
#line 85 "tests/01__basics/010__boolean_logic/test.code"
        bool __001__;
#line 85 "tests/01__basics/010__boolean_logic/test.code"
        bool __002__;
#line 85 "tests/01__basics/010__boolean_logic/test.code"
        bool __003__ = check2;
#line 85 "tests/01__basics/010__boolean_logic/test.code"
        if (__003__) {
#line 85 "tests/01__basics/010__boolean_logic/test.code"
            __002__ = __003__;
        } else {
#line 85 "tests/01__basics/010__boolean_logic/test.code"
            bool __004__;
#line 85 "tests/01__basics/010__boolean_logic/test.code"
            bool __005__ = check3;
#line 85 "tests/01__basics/010__boolean_logic/test.code"
            if (__005__) {
#line 85 "tests/01__basics/010__boolean_logic/test.code"
                bool __006__ = check4;
#line 85 "tests/01__basics/010__boolean_logic/test.code"
                __004__ = __006__;
            } else {
#line 85 "tests/01__basics/010__boolean_logic/test.code"
                __004__ = __005__;
            }
#line 85 "tests/01__basics/010__boolean_logic/test.code"
            bool __007__ = (__004__);
#line 85 "tests/01__basics/010__boolean_logic/test.code"
            __002__ = __007__;
        }
#line 85 "tests/01__basics/010__boolean_logic/test.code"
        bool __008__ = __002__;
#line 85 "tests/01__basics/010__boolean_logic/test.code"
        if (__008__) {
#line 85 "tests/01__basics/010__boolean_logic/test.code"
            __001__ = __008__;
        } else {
#line 85 "tests/01__basics/010__boolean_logic/test.code"
            bool __009__ = check5;
#line 85 "tests/01__basics/010__boolean_logic/test.code"
            __001__ = __009__;
        }
#line 85 "tests/01__basics/010__boolean_logic/test.code"
        if (__001__) {
        } else {
#line 88 "tests/01__basics/010__boolean_logic/test.code"
            return 15;
        }
    }
#line 91 "tests/01__basics/010__boolean_logic/test.code"
    {
#line 91 "tests/01__basics/010__boolean_logic/test.code"
        bool __001__;
#line 91 "tests/01__basics/010__boolean_logic/test.code"
        bool __002__;
#line 91 "tests/01__basics/010__boolean_logic/test.code"
        bool __003__;
#line 91 "tests/01__basics/010__boolean_logic/test.code"
        bool __004__;
#line 91 "tests/01__basics/010__boolean_logic/test.code"
        bool __005__ = check1;
#line 91 "tests/01__basics/010__boolean_logic/test.code"
        if (__005__) {
#line 91 "tests/01__basics/010__boolean_logic/test.code"
            bool __006__ = check2;
#line 91 "tests/01__basics/010__boolean_logic/test.code"
            __004__ = __006__;
        } else {
#line 91 "tests/01__basics/010__boolean_logic/test.code"
            __004__ = __005__;
        }
#line 91 "tests/01__basics/010__boolean_logic/test.code"
        bool __007__ = (__004__);
#line 91 "tests/01__basics/010__boolean_logic/test.code"
        if (__007__) {
#line 91 "tests/01__basics/010__boolean_logic/test.code"
            __003__ = __007__;
        } else {
#line 91 "tests/01__basics/010__boolean_logic/test.code"
            bool __008__;
#line 91 "tests/01__basics/010__boolean_logic/test.code"
            bool __009__ = check3;
#line 91 "tests/01__basics/010__boolean_logic/test.code"
            if (__009__) {
#line 91 "tests/01__basics/010__boolean_logic/test.code"
                bool __010__ = check4;
#line 91 "tests/01__basics/010__boolean_logic/test.code"
                __008__ = __010__;
            } else {
#line 91 "tests/01__basics/010__boolean_logic/test.code"
                __008__ = __009__;
            }
#line 91 "tests/01__basics/010__boolean_logic/test.code"
            bool __011__ = (__008__);
#line 91 "tests/01__basics/010__boolean_logic/test.code"
            __003__ = __011__;
        }
#line 91 "tests/01__basics/010__boolean_logic/test.code"
        bool __012__ = (__003__);
#line 91 "tests/01__basics/010__boolean_logic/test.code"
        if (__012__) {
#line 91 "tests/01__basics/010__boolean_logic/test.code"
            bool __013__ = check5;
#line 91 "tests/01__basics/010__boolean_logic/test.code"
            __002__ = __013__;
        } else {
#line 91 "tests/01__basics/010__boolean_logic/test.code"
            __002__ = __012__;
        }
#line 91 "tests/01__basics/010__boolean_logic/test.code"
        bool __014__ = (__002__);
#line 91 "tests/01__basics/010__boolean_logic/test.code"
        if (__014__) {
#line 91 "tests/01__basics/010__boolean_logic/test.code"
            __001__ = __014__;
        } else {
#line 91 "tests/01__basics/010__boolean_logic/test.code"
            bool __015__ = check6;
#line 91 "tests/01__basics/010__boolean_logic/test.code"
            __001__ = __015__;
        }
#line 91 "tests/01__basics/010__boolean_logic/test.code"
        if (__001__) {
#line 92 "tests/01__basics/010__boolean_logic/test.code"
            return 16;
        } else {
        }
    }
#line 97 "tests/01__basics/010__boolean_logic/test.code"
    {
#line 97 "tests/01__basics/010__boolean_logic/test.code"
        bool __001__;
#line 97 "tests/01__basics/010__boolean_logic/test.code"
        bool __002__;
#line 97 "tests/01__basics/010__boolean_logic/test.code"
        bool __003__ = check1;
#line 97 "tests/01__basics/010__boolean_logic/test.code"
        if (__003__) {
#line 97 "tests/01__basics/010__boolean_logic/test.code"
            bool __004__ = check2;
#line 97 "tests/01__basics/010__boolean_logic/test.code"
            __002__ = __004__;
        } else {
#line 97 "tests/01__basics/010__boolean_logic/test.code"
            __002__ = __003__;
        }
#line 97 "tests/01__basics/010__boolean_logic/test.code"
        bool __005__ = (__002__);
#line 97 "tests/01__basics/010__boolean_logic/test.code"
        if (__005__) {
#line 97 "tests/01__basics/010__boolean_logic/test.code"
            __001__ = __005__;
        } else {
#line 97 "tests/01__basics/010__boolean_logic/test.code"
            bool __006__;
#line 97 "tests/01__basics/010__boolean_logic/test.code"
            bool __007__;
#line 97 "tests/01__basics/010__boolean_logic/test.code"
            bool __008__;
#line 97 "tests/01__basics/010__boolean_logic/test.code"
            bool __009__ = check3;
#line 97 "tests/01__basics/010__boolean_logic/test.code"
            if (__009__) {
#line 97 "tests/01__basics/010__boolean_logic/test.code"
                bool __010__ = check4;
#line 97 "tests/01__basics/010__boolean_logic/test.code"
                __008__ = __010__;
            } else {
#line 97 "tests/01__basics/010__boolean_logic/test.code"
                __008__ = __009__;
            }
#line 97 "tests/01__basics/010__boolean_logic/test.code"
            bool __011__ = (__008__);
#line 97 "tests/01__basics/010__boolean_logic/test.code"
            if (__011__) {
#line 97 "tests/01__basics/010__boolean_logic/test.code"
                __007__ = __011__;
            } else {
#line 97 "tests/01__basics/010__boolean_logic/test.code"
                bool __012__ = check6;
#line 97 "tests/01__basics/010__boolean_logic/test.code"
                __007__ = __012__;
            }
#line 97 "tests/01__basics/010__boolean_logic/test.code"
            bool __013__ = (__007__);
#line 97 "tests/01__basics/010__boolean_logic/test.code"
            if (__013__) {
#line 97 "tests/01__basics/010__boolean_logic/test.code"
                bool __014__ = check5;
#line 97 "tests/01__basics/010__boolean_logic/test.code"
                __006__ = __014__;
            } else {
#line 97 "tests/01__basics/010__boolean_logic/test.code"
                __006__ = __013__;
            }
#line 97 "tests/01__basics/010__boolean_logic/test.code"
            bool __015__ = (__006__);
#line 97 "tests/01__basics/010__boolean_logic/test.code"
            __001__ = __015__;
        }
#line 97 "tests/01__basics/010__boolean_logic/test.code"
        if (__001__) {
#line 98 "tests/01__basics/010__boolean_logic/test.code"
            return 17;
        }
    }
#line 101 "tests/01__basics/010__boolean_logic/test.code"
    {
#line 101 "tests/01__basics/010__boolean_logic/test.code"
        bool __001__;
#line 101 "tests/01__basics/010__boolean_logic/test.code"
        bool __002__ = check1;
#line 101 "tests/01__basics/010__boolean_logic/test.code"
        if (__002__) {
#line 101 "tests/01__basics/010__boolean_logic/test.code"
            bool __003__ = !check2;
#line 101 "tests/01__basics/010__boolean_logic/test.code"
            __001__ = __003__;
        } else {
#line 101 "tests/01__basics/010__boolean_logic/test.code"
            __001__ = __002__;
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
        bool __001__;
#line 107 "tests/01__basics/010__boolean_logic/test.code"
        bool __002__ = !check1;
#line 107 "tests/01__basics/010__boolean_logic/test.code"
        if (__002__) {
#line 107 "tests/01__basics/010__boolean_logic/test.code"
            __001__ = __002__;
        } else {
#line 107 "tests/01__basics/010__boolean_logic/test.code"
            bool __003__ = check2;
#line 107 "tests/01__basics/010__boolean_logic/test.code"
            __001__ = __003__;
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

