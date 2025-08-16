#include "test.h"

void *malloc(uintmax_t size);

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
#line 11 "tests/01__basics/010__boolean_logic/test.code"
    } else {
#line 12 "tests/01__basics/010__boolean_logic/test.code"
        {
#line 12 "tests/01__basics/010__boolean_logic/test.code"
            int32_t __001__ = 1;
#line 12 "tests/01__basics/010__boolean_logic/test.code"
            return __001__;
#line 12 "tests/01__basics/010__boolean_logic/test.code"
        }
#line 13 "tests/01__basics/010__boolean_logic/test.code"
    }
#line 15 "tests/01__basics/010__boolean_logic/test.code"
    if (!check1) {
#line 16 "tests/01__basics/010__boolean_logic/test.code"
        {
#line 16 "tests/01__basics/010__boolean_logic/test.code"
            int32_t __002__ = 2;
#line 16 "tests/01__basics/010__boolean_logic/test.code"
            return __002__;
#line 16 "tests/01__basics/010__boolean_logic/test.code"
        }
#line 17 "tests/01__basics/010__boolean_logic/test.code"
    }
#line 19 "tests/01__basics/010__boolean_logic/test.code"
    if (check2) {
#line 20 "tests/01__basics/010__boolean_logic/test.code"
        {
#line 20 "tests/01__basics/010__boolean_logic/test.code"
            int32_t __003__ = 3;
#line 20 "tests/01__basics/010__boolean_logic/test.code"
            return __003__;
#line 20 "tests/01__basics/010__boolean_logic/test.code"
        }
#line 21 "tests/01__basics/010__boolean_logic/test.code"
    }
#line 23 "tests/01__basics/010__boolean_logic/test.code"
    if (!check2) {
#line 25 "tests/01__basics/010__boolean_logic/test.code"
    } else {
#line 26 "tests/01__basics/010__boolean_logic/test.code"
        {
#line 26 "tests/01__basics/010__boolean_logic/test.code"
            int32_t __004__ = 4;
#line 26 "tests/01__basics/010__boolean_logic/test.code"
            return __004__;
#line 26 "tests/01__basics/010__boolean_logic/test.code"
        }
#line 27 "tests/01__basics/010__boolean_logic/test.code"
    }
#line 29 "tests/01__basics/010__boolean_logic/test.code"
    if (check1 && check2) {
#line 30 "tests/01__basics/010__boolean_logic/test.code"
        {
#line 30 "tests/01__basics/010__boolean_logic/test.code"
            int32_t __005__ = 5;
#line 30 "tests/01__basics/010__boolean_logic/test.code"
            return __005__;
#line 30 "tests/01__basics/010__boolean_logic/test.code"
        }
#line 31 "tests/01__basics/010__boolean_logic/test.code"
    }
#line 33 "tests/01__basics/010__boolean_logic/test.code"
    if (!(check1 && check2)) {
#line 35 "tests/01__basics/010__boolean_logic/test.code"
    } else {
#line 36 "tests/01__basics/010__boolean_logic/test.code"
        {
#line 36 "tests/01__basics/010__boolean_logic/test.code"
            int32_t __006__ = 6;
#line 36 "tests/01__basics/010__boolean_logic/test.code"
            return __006__;
#line 36 "tests/01__basics/010__boolean_logic/test.code"
        }
#line 37 "tests/01__basics/010__boolean_logic/test.code"
    }
#line 39 "tests/01__basics/010__boolean_logic/test.code"
    if (!!(check1 && check2)) {
#line 40 "tests/01__basics/010__boolean_logic/test.code"
        {
#line 40 "tests/01__basics/010__boolean_logic/test.code"
            int32_t __007__ = 7;
#line 40 "tests/01__basics/010__boolean_logic/test.code"
            return __007__;
#line 40 "tests/01__basics/010__boolean_logic/test.code"
        }
#line 41 "tests/01__basics/010__boolean_logic/test.code"
    } else {
#line 43 "tests/01__basics/010__boolean_logic/test.code"
    }
#line 45 "tests/01__basics/010__boolean_logic/test.code"
    if (check1 || check2) {
#line 47 "tests/01__basics/010__boolean_logic/test.code"
    } else {
#line 48 "tests/01__basics/010__boolean_logic/test.code"
        {
#line 48 "tests/01__basics/010__boolean_logic/test.code"
            int32_t __008__ = 8;
#line 48 "tests/01__basics/010__boolean_logic/test.code"
            return __008__;
#line 48 "tests/01__basics/010__boolean_logic/test.code"
        }
#line 49 "tests/01__basics/010__boolean_logic/test.code"
    }
#line 51 "tests/01__basics/010__boolean_logic/test.code"
    if (!(check1 || check2)) {
#line 52 "tests/01__basics/010__boolean_logic/test.code"
        {
#line 52 "tests/01__basics/010__boolean_logic/test.code"
            int32_t __009__ = 9;
#line 52 "tests/01__basics/010__boolean_logic/test.code"
            return __009__;
#line 52 "tests/01__basics/010__boolean_logic/test.code"
        }
#line 53 "tests/01__basics/010__boolean_logic/test.code"
    } else {
#line 55 "tests/01__basics/010__boolean_logic/test.code"
    }
#line 57 "tests/01__basics/010__boolean_logic/test.code"
    if ((check1 && check2) || (check3 && check4)) {
#line 58 "tests/01__basics/010__boolean_logic/test.code"
        {
#line 58 "tests/01__basics/010__boolean_logic/test.code"
            int32_t __010__ = 10;
#line 58 "tests/01__basics/010__boolean_logic/test.code"
            return __010__;
#line 58 "tests/01__basics/010__boolean_logic/test.code"
        }
#line 59 "tests/01__basics/010__boolean_logic/test.code"
    }
#line 61 "tests/01__basics/010__boolean_logic/test.code"
    if ((check2 && check4) || (check1 && check3)) {
#line 63 "tests/01__basics/010__boolean_logic/test.code"
    } else {
#line 64 "tests/01__basics/010__boolean_logic/test.code"
        {
#line 64 "tests/01__basics/010__boolean_logic/test.code"
            int32_t __011__ = 11;
#line 64 "tests/01__basics/010__boolean_logic/test.code"
            return __011__;
#line 64 "tests/01__basics/010__boolean_logic/test.code"
        }
#line 65 "tests/01__basics/010__boolean_logic/test.code"
    }
#line 67 "tests/01__basics/010__boolean_logic/test.code"
    if (check1 && (check2 || check3) && check4) {
#line 68 "tests/01__basics/010__boolean_logic/test.code"
        {
#line 68 "tests/01__basics/010__boolean_logic/test.code"
            int32_t __012__ = 12;
#line 68 "tests/01__basics/010__boolean_logic/test.code"
            return __012__;
#line 68 "tests/01__basics/010__boolean_logic/test.code"
        }
#line 69 "tests/01__basics/010__boolean_logic/test.code"
    } else {
#line 71 "tests/01__basics/010__boolean_logic/test.code"
    }
#line 73 "tests/01__basics/010__boolean_logic/test.code"
    if ((check1 || check2) && (check3 || check4)) {
#line 75 "tests/01__basics/010__boolean_logic/test.code"
    } else {
#line 76 "tests/01__basics/010__boolean_logic/test.code"
        {
#line 76 "tests/01__basics/010__boolean_logic/test.code"
            int32_t __013__ = 13;
#line 76 "tests/01__basics/010__boolean_logic/test.code"
            return __013__;
#line 76 "tests/01__basics/010__boolean_logic/test.code"
        }
#line 77 "tests/01__basics/010__boolean_logic/test.code"
    }
#line 79 "tests/01__basics/010__boolean_logic/test.code"
    if ((check1 || check4) && (check2 || check3)) {
#line 81 "tests/01__basics/010__boolean_logic/test.code"
    } else {
#line 82 "tests/01__basics/010__boolean_logic/test.code"
        {
#line 82 "tests/01__basics/010__boolean_logic/test.code"
            int32_t __014__ = 14;
#line 82 "tests/01__basics/010__boolean_logic/test.code"
            return __014__;
#line 82 "tests/01__basics/010__boolean_logic/test.code"
        }
#line 83 "tests/01__basics/010__boolean_logic/test.code"
    }
#line 85 "tests/01__basics/010__boolean_logic/test.code"
    if (check2 || (check3 && check4) || check5) {
#line 87 "tests/01__basics/010__boolean_logic/test.code"
    } else {
#line 88 "tests/01__basics/010__boolean_logic/test.code"
        {
#line 88 "tests/01__basics/010__boolean_logic/test.code"
            int32_t __015__ = 15;
#line 88 "tests/01__basics/010__boolean_logic/test.code"
            return __015__;
#line 88 "tests/01__basics/010__boolean_logic/test.code"
        }
#line 89 "tests/01__basics/010__boolean_logic/test.code"
    }
#line 91 "tests/01__basics/010__boolean_logic/test.code"
    if ((((check1 && check2) || (check3 && check4)) && check5) || check6) {
#line 92 "tests/01__basics/010__boolean_logic/test.code"
        {
#line 92 "tests/01__basics/010__boolean_logic/test.code"
            int32_t __016__ = 16;
#line 92 "tests/01__basics/010__boolean_logic/test.code"
            return __016__;
#line 92 "tests/01__basics/010__boolean_logic/test.code"
        }
#line 93 "tests/01__basics/010__boolean_logic/test.code"
    } else {
#line 95 "tests/01__basics/010__boolean_logic/test.code"
    }
#line 97 "tests/01__basics/010__boolean_logic/test.code"
    if ((check1 && check2) || (((check3 && check4) || check6) && check5)) {
#line 98 "tests/01__basics/010__boolean_logic/test.code"
        {
#line 98 "tests/01__basics/010__boolean_logic/test.code"
            int32_t __017__ = 17;
#line 98 "tests/01__basics/010__boolean_logic/test.code"
            return __017__;
#line 98 "tests/01__basics/010__boolean_logic/test.code"
        }
#line 99 "tests/01__basics/010__boolean_logic/test.code"
    }
#line 101 "tests/01__basics/010__boolean_logic/test.code"
    if (check1 && !check2) {
#line 103 "tests/01__basics/010__boolean_logic/test.code"
    } else {
#line 104 "tests/01__basics/010__boolean_logic/test.code"
        {
#line 104 "tests/01__basics/010__boolean_logic/test.code"
            int32_t __018__ = 18;
#line 104 "tests/01__basics/010__boolean_logic/test.code"
            return __018__;
#line 104 "tests/01__basics/010__boolean_logic/test.code"
        }
#line 105 "tests/01__basics/010__boolean_logic/test.code"
    }
#line 107 "tests/01__basics/010__boolean_logic/test.code"
    if (!check1 || check2) {
#line 108 "tests/01__basics/010__boolean_logic/test.code"
        {
#line 108 "tests/01__basics/010__boolean_logic/test.code"
            int32_t __019__ = 19;
#line 108 "tests/01__basics/010__boolean_logic/test.code"
            return __019__;
#line 108 "tests/01__basics/010__boolean_logic/test.code"
        }
#line 109 "tests/01__basics/010__boolean_logic/test.code"
    }
#line 111 "tests/01__basics/010__boolean_logic/test.code"
    {
#line 111 "tests/01__basics/010__boolean_logic/test.code"
        int32_t __020__ = 0;
#line 111 "tests/01__basics/010__boolean_logic/test.code"
        return __020__;
#line 111 "tests/01__basics/010__boolean_logic/test.code"
    }
#line 112 "tests/01__basics/010__boolean_logic/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

