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
        return 1;
#line 13 "tests/01__basics/010__boolean_logic/test.code"
    }
#line 15 "tests/01__basics/010__boolean_logic/test.code"
    if (!check1) {
#line 16 "tests/01__basics/010__boolean_logic/test.code"
        return 2;
#line 17 "tests/01__basics/010__boolean_logic/test.code"
    }
#line 19 "tests/01__basics/010__boolean_logic/test.code"
    if (check2) {
#line 20 "tests/01__basics/010__boolean_logic/test.code"
        return 3;
#line 21 "tests/01__basics/010__boolean_logic/test.code"
    }
#line 23 "tests/01__basics/010__boolean_logic/test.code"
    if (!check2) {
#line 25 "tests/01__basics/010__boolean_logic/test.code"
    } else {
#line 26 "tests/01__basics/010__boolean_logic/test.code"
        return 4;
#line 27 "tests/01__basics/010__boolean_logic/test.code"
    }
#line 29 "tests/01__basics/010__boolean_logic/test.code"
    if (check1 && check2) {
#line 30 "tests/01__basics/010__boolean_logic/test.code"
        return 5;
#line 31 "tests/01__basics/010__boolean_logic/test.code"
    }
#line 33 "tests/01__basics/010__boolean_logic/test.code"
    if (!(check1 && check2)) {
#line 35 "tests/01__basics/010__boolean_logic/test.code"
    } else {
#line 36 "tests/01__basics/010__boolean_logic/test.code"
        return 6;
#line 37 "tests/01__basics/010__boolean_logic/test.code"
    }
#line 39 "tests/01__basics/010__boolean_logic/test.code"
    if (!!(check1 && check2)) {
#line 40 "tests/01__basics/010__boolean_logic/test.code"
        return 7;
#line 41 "tests/01__basics/010__boolean_logic/test.code"
    } else {
#line 43 "tests/01__basics/010__boolean_logic/test.code"
    }
#line 45 "tests/01__basics/010__boolean_logic/test.code"
    if (check1 || check2) {
#line 47 "tests/01__basics/010__boolean_logic/test.code"
    } else {
#line 48 "tests/01__basics/010__boolean_logic/test.code"
        return 8;
#line 49 "tests/01__basics/010__boolean_logic/test.code"
    }
#line 51 "tests/01__basics/010__boolean_logic/test.code"
    if (!(check1 || check2)) {
#line 52 "tests/01__basics/010__boolean_logic/test.code"
        return 9;
#line 53 "tests/01__basics/010__boolean_logic/test.code"
    } else {
#line 55 "tests/01__basics/010__boolean_logic/test.code"
    }
#line 57 "tests/01__basics/010__boolean_logic/test.code"
    if ((check1 && check2) || (check3 && check4)) {
#line 58 "tests/01__basics/010__boolean_logic/test.code"
        return 10;
#line 59 "tests/01__basics/010__boolean_logic/test.code"
    }
#line 61 "tests/01__basics/010__boolean_logic/test.code"
    if ((check2 && check4) || (check1 && check3)) {
#line 63 "tests/01__basics/010__boolean_logic/test.code"
    } else {
#line 64 "tests/01__basics/010__boolean_logic/test.code"
        return 11;
#line 65 "tests/01__basics/010__boolean_logic/test.code"
    }
#line 67 "tests/01__basics/010__boolean_logic/test.code"
    if (check1 && (check2 || check3) && check4) {
#line 68 "tests/01__basics/010__boolean_logic/test.code"
        return 12;
#line 69 "tests/01__basics/010__boolean_logic/test.code"
    } else {
#line 71 "tests/01__basics/010__boolean_logic/test.code"
    }
#line 73 "tests/01__basics/010__boolean_logic/test.code"
    if ((check1 || check2) && (check3 || check4)) {
#line 75 "tests/01__basics/010__boolean_logic/test.code"
    } else {
#line 76 "tests/01__basics/010__boolean_logic/test.code"
        return 13;
#line 77 "tests/01__basics/010__boolean_logic/test.code"
    }
#line 79 "tests/01__basics/010__boolean_logic/test.code"
    if ((check1 || check4) && (check2 || check3)) {
#line 81 "tests/01__basics/010__boolean_logic/test.code"
    } else {
#line 82 "tests/01__basics/010__boolean_logic/test.code"
        return 14;
#line 83 "tests/01__basics/010__boolean_logic/test.code"
    }
#line 85 "tests/01__basics/010__boolean_logic/test.code"
    if (check2 || (check3 && check4) || check5) {
#line 87 "tests/01__basics/010__boolean_logic/test.code"
    } else {
#line 88 "tests/01__basics/010__boolean_logic/test.code"
        return 15;
#line 89 "tests/01__basics/010__boolean_logic/test.code"
    }
#line 91 "tests/01__basics/010__boolean_logic/test.code"
    if ((((check1 && check2) || (check3 && check4)) && check5) || check6) {
#line 92 "tests/01__basics/010__boolean_logic/test.code"
        return 16;
#line 93 "tests/01__basics/010__boolean_logic/test.code"
    } else {
#line 95 "tests/01__basics/010__boolean_logic/test.code"
    }
#line 97 "tests/01__basics/010__boolean_logic/test.code"
    if ((check1 && check2) || (((check3 && check4) || check6) && check5)) {
#line 98 "tests/01__basics/010__boolean_logic/test.code"
        return 17;
#line 99 "tests/01__basics/010__boolean_logic/test.code"
    }
#line 101 "tests/01__basics/010__boolean_logic/test.code"
    if (check1 && !check2) {
#line 103 "tests/01__basics/010__boolean_logic/test.code"
    } else {
#line 104 "tests/01__basics/010__boolean_logic/test.code"
        return 18;
#line 105 "tests/01__basics/010__boolean_logic/test.code"
    }
#line 107 "tests/01__basics/010__boolean_logic/test.code"
    if (!check1 || check2) {
#line 108 "tests/01__basics/010__boolean_logic/test.code"
        return 19;
#line 109 "tests/01__basics/010__boolean_logic/test.code"
    }
#line 111 "tests/01__basics/010__boolean_logic/test.code"
    return 0;
#line 112 "tests/01__basics/010__boolean_logic/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

