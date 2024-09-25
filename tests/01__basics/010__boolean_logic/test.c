#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t main();

#line 1 "tests/01__basics/010__boolean_logic/test.code"
int32_t main() {
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
    if (check1 && check2) {
#line 30 "tests/01__basics/010__boolean_logic/test.code"
        return 5;
    }
#line 33 "tests/01__basics/010__boolean_logic/test.code"
    if (!(check1 && check2)) {
    } else {
#line 36 "tests/01__basics/010__boolean_logic/test.code"
        return 6;
    }
#line 39 "tests/01__basics/010__boolean_logic/test.code"
    if (!!(check1 && check2)) {
#line 40 "tests/01__basics/010__boolean_logic/test.code"
        return 7;
    } else {
    }
#line 45 "tests/01__basics/010__boolean_logic/test.code"
    if (check1 || check2) {
    } else {
#line 48 "tests/01__basics/010__boolean_logic/test.code"
        return 8;
    }
#line 51 "tests/01__basics/010__boolean_logic/test.code"
    if (!(check1 || check2)) {
#line 52 "tests/01__basics/010__boolean_logic/test.code"
        return 9;
    } else {
    }
#line 57 "tests/01__basics/010__boolean_logic/test.code"
    if ((check1 && check2) || (check3 && check4)) {
#line 58 "tests/01__basics/010__boolean_logic/test.code"
        return 10;
    }
#line 61 "tests/01__basics/010__boolean_logic/test.code"
    if ((check2 && check4) || (check1 && check3)) {
    } else {
#line 64 "tests/01__basics/010__boolean_logic/test.code"
        return 11;
    }
#line 67 "tests/01__basics/010__boolean_logic/test.code"
    if (check1 && (check2 || check3) && check4) {
#line 68 "tests/01__basics/010__boolean_logic/test.code"
        return 12;
    } else {
    }
#line 73 "tests/01__basics/010__boolean_logic/test.code"
    if ((check1 || check2) && (check3 || check4)) {
    } else {
#line 76 "tests/01__basics/010__boolean_logic/test.code"
        return 13;
    }
#line 79 "tests/01__basics/010__boolean_logic/test.code"
    if ((check1 || check4) && (check2 || check3)) {
    } else {
#line 82 "tests/01__basics/010__boolean_logic/test.code"
        return 14;
    }
#line 85 "tests/01__basics/010__boolean_logic/test.code"
    if (check2 || (check3 && check4) || check5) {
    } else {
#line 88 "tests/01__basics/010__boolean_logic/test.code"
        return 15;
    }
#line 91 "tests/01__basics/010__boolean_logic/test.code"
    if ((((check1 && check2) || (check3 && check4)) && check5) || check6) {
#line 92 "tests/01__basics/010__boolean_logic/test.code"
        return 16;
    } else {
    }
#line 97 "tests/01__basics/010__boolean_logic/test.code"
    if ((check1 && check2) || (((check3 && check4) || check6) && check5)) {
#line 98 "tests/01__basics/010__boolean_logic/test.code"
        return 17;
    }
#line 101 "tests/01__basics/010__boolean_logic/test.code"
    if (check1 && !check2) {
    } else {
#line 104 "tests/01__basics/010__boolean_logic/test.code"
        return 18;
    }
#line 107 "tests/01__basics/010__boolean_logic/test.code"
    if (!check1 || check2) {
#line 108 "tests/01__basics/010__boolean_logic/test.code"
        return 19;
    }
#line 111 "tests/01__basics/010__boolean_logic/test.code"
    return 0;
}

