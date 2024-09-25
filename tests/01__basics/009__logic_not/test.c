#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t main();

bool test_not(bool v);

#line 1 "tests/01__basics/009__logic_not/test.code"
int32_t main() {
#line 2 "tests/01__basics/009__logic_not/test.code"
    if (test_not(true)) {
#line 3 "tests/01__basics/009__logic_not/test.code"
        return 1;
    }
#line 5 "tests/01__basics/009__logic_not/test.code"
    if (test_not(false)) {
    } else {
#line 8 "tests/01__basics/009__logic_not/test.code"
        return 2;
    }
#line 10 "tests/01__basics/009__logic_not/test.code"
    if (!test_not(false)) {
#line 11 "tests/01__basics/009__logic_not/test.code"
        return 3;
    }
#line 13 "tests/01__basics/009__logic_not/test.code"
    if (!!test_not(true)) {
#line 14 "tests/01__basics/009__logic_not/test.code"
        return 4;
    }
#line 16 "tests/01__basics/009__logic_not/test.code"
    return 0;
}

#line 19 "tests/01__basics/009__logic_not/test.code"
bool test_not(bool v) {
#line 20 "tests/01__basics/009__logic_not/test.code"
    return !v;
}

