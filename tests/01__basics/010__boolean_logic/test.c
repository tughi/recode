#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t test__main();

int32_t main(int argc, const char **argv) {
    return test__main();
}

#line 3 "tests/01__basics/010__boolean_logic/test.code"
int32_t test__main() {
#line 4 "tests/01__basics/010__boolean_logic/test.code"
    bool check1 = true;
#line 5 "tests/01__basics/010__boolean_logic/test.code"
    bool check2 = false;
#line 6 "tests/01__basics/010__boolean_logic/test.code"
    bool check3 = true;
#line 7 "tests/01__basics/010__boolean_logic/test.code"
    bool check4 = false;
#line 8 "tests/01__basics/010__boolean_logic/test.code"
    bool check5 = true;
#line 9 "tests/01__basics/010__boolean_logic/test.code"
    bool check6 = false;
#line 11 "tests/01__basics/010__boolean_logic/test.code"
    if (check1) {
    } else {
#line 14 "tests/01__basics/010__boolean_logic/test.code"
        return 1;
    }
#line 17 "tests/01__basics/010__boolean_logic/test.code"
    if (!check1) {
#line 18 "tests/01__basics/010__boolean_logic/test.code"
        return 2;
    }
#line 21 "tests/01__basics/010__boolean_logic/test.code"
    if (check2) {
#line 22 "tests/01__basics/010__boolean_logic/test.code"
        return 3;
    }
#line 25 "tests/01__basics/010__boolean_logic/test.code"
    if (!check2) {
    } else {
#line 28 "tests/01__basics/010__boolean_logic/test.code"
        return 4;
    }
#line 31 "tests/01__basics/010__boolean_logic/test.code"
    if (check1 && check2) {
#line 32 "tests/01__basics/010__boolean_logic/test.code"
        return 5;
    }
#line 35 "tests/01__basics/010__boolean_logic/test.code"
    if (!(check1 && check2)) {
    } else {
#line 38 "tests/01__basics/010__boolean_logic/test.code"
        return 6;
    }
#line 41 "tests/01__basics/010__boolean_logic/test.code"
    if (!!(check1 && check2)) {
#line 42 "tests/01__basics/010__boolean_logic/test.code"
        return 7;
    } else {
    }
#line 47 "tests/01__basics/010__boolean_logic/test.code"
    if (check1 || check2) {
    } else {
#line 50 "tests/01__basics/010__boolean_logic/test.code"
        return 8;
    }
#line 53 "tests/01__basics/010__boolean_logic/test.code"
    if (!(check1 || check2)) {
#line 54 "tests/01__basics/010__boolean_logic/test.code"
        return 9;
    } else {
    }
#line 59 "tests/01__basics/010__boolean_logic/test.code"
    if ((check1 && check2) || (check3 && check4)) {
#line 60 "tests/01__basics/010__boolean_logic/test.code"
        return 10;
    }
#line 63 "tests/01__basics/010__boolean_logic/test.code"
    if ((check2 && check4) || (check1 && check3)) {
    } else {
#line 66 "tests/01__basics/010__boolean_logic/test.code"
        return 11;
    }
#line 69 "tests/01__basics/010__boolean_logic/test.code"
    if (check1 && (check2 || check3) && check4) {
#line 70 "tests/01__basics/010__boolean_logic/test.code"
        return 12;
    } else {
    }
#line 75 "tests/01__basics/010__boolean_logic/test.code"
    if ((check1 || check2) && (check3 || check4)) {
    } else {
#line 78 "tests/01__basics/010__boolean_logic/test.code"
        return 13;
    }
#line 81 "tests/01__basics/010__boolean_logic/test.code"
    if ((check1 || check4) && (check2 || check3)) {
    } else {
#line 84 "tests/01__basics/010__boolean_logic/test.code"
        return 14;
    }
#line 87 "tests/01__basics/010__boolean_logic/test.code"
    if (check2 || (check3 && check4) || check5) {
    } else {
#line 90 "tests/01__basics/010__boolean_logic/test.code"
        return 15;
    }
#line 93 "tests/01__basics/010__boolean_logic/test.code"
    if ((((check1 && check2) || (check3 && check4)) && check5) || check6) {
#line 94 "tests/01__basics/010__boolean_logic/test.code"
        return 16;
    } else {
    }
#line 99 "tests/01__basics/010__boolean_logic/test.code"
    if ((check1 && check2) || (((check3 && check4) || check6) && check5)) {
#line 100 "tests/01__basics/010__boolean_logic/test.code"
        return 17;
    }
#line 103 "tests/01__basics/010__boolean_logic/test.code"
    if (check1 && !check2) {
    } else {
#line 106 "tests/01__basics/010__boolean_logic/test.code"
        return 18;
    }
#line 109 "tests/01__basics/010__boolean_logic/test.code"
    if (!check1 || check2) {
#line 110 "tests/01__basics/010__boolean_logic/test.code"
        return 19;
    }
#line 113 "tests/01__basics/010__boolean_logic/test.code"
    return 0;
}

