#include "test.h"

#line 1 "tests/01__basics/009__logic_not/test.code"
int32_t test__main() {
#line 2 "tests/01__basics/009__logic_not/test.code"
    {
#line 2 "tests/01__basics/009__logic_not/test.code"
        bool __001__ = true;
#line 2 "tests/01__basics/009__logic_not/test.code"
        if (test__test_not(__001__)) {
#line 3 "tests/01__basics/009__logic_not/test.code"
            return 1;
        }
    }
#line 5 "tests/01__basics/009__logic_not/test.code"
    {
#line 5 "tests/01__basics/009__logic_not/test.code"
        bool __001__ = false;
#line 5 "tests/01__basics/009__logic_not/test.code"
        if (test__test_not(__001__)) {
        } else {
#line 8 "tests/01__basics/009__logic_not/test.code"
            return 2;
        }
    }
#line 10 "tests/01__basics/009__logic_not/test.code"
    {
#line 10 "tests/01__basics/009__logic_not/test.code"
        bool __001__ = false;
#line 10 "tests/01__basics/009__logic_not/test.code"
        if (!test__test_not(__001__)) {
#line 11 "tests/01__basics/009__logic_not/test.code"
            return 3;
        }
    }
#line 13 "tests/01__basics/009__logic_not/test.code"
    {
#line 13 "tests/01__basics/009__logic_not/test.code"
        bool __001__ = true;
#line 13 "tests/01__basics/009__logic_not/test.code"
        if (!!test__test_not(__001__)) {
#line 14 "tests/01__basics/009__logic_not/test.code"
            return 4;
        }
    }
#line 16 "tests/01__basics/009__logic_not/test.code"
    return 0;
}

#line 19 "tests/01__basics/009__logic_not/test.code"
bool test__test_not(bool v) {
#line 20 "tests/01__basics/009__logic_not/test.code"
    return !v;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

