#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t test__main();

bool test__test_not(bool v);

int32_t main(int argc, const char **argv) {
    return test__main();
}

#line 3 "tests/01__basics/009__logic_not/test.code"
int32_t test__main() {
#line 4 "tests/01__basics/009__logic_not/test.code"
    if (test__test_not(true)) {
#line 5 "tests/01__basics/009__logic_not/test.code"
        return 1;
    }
#line 7 "tests/01__basics/009__logic_not/test.code"
    if (test__test_not(false)) {
    } else {
#line 10 "tests/01__basics/009__logic_not/test.code"
        return 2;
    }
#line 12 "tests/01__basics/009__logic_not/test.code"
    if (!test__test_not(false)) {
#line 13 "tests/01__basics/009__logic_not/test.code"
        return 3;
    }
#line 15 "tests/01__basics/009__logic_not/test.code"
    if (!!test__test_not(true)) {
#line 16 "tests/01__basics/009__logic_not/test.code"
        return 4;
    }
#line 18 "tests/01__basics/009__logic_not/test.code"
    return 0;
}

#line 21 "tests/01__basics/009__logic_not/test.code"
bool test__test_not(bool v) {
#line 22 "tests/01__basics/009__logic_not/test.code"
    return !v;
}

