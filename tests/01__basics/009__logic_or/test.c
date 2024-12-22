#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t test__main();

bool test__echo(bool v);

int32_t main(int argc, const char **argv) {
    return test__main();
}

#line 3 "tests/01__basics/009__logic_or/test.code"
int32_t test__main() {
#line 4 "tests/01__basics/009__logic_or/test.code"
    bool t = test__echo(true);
#line 5 "tests/01__basics/009__logic_or/test.code"
    bool f = test__echo(false);
#line 6 "tests/01__basics/009__logic_or/test.code"
    if (t || f) {
    } else {
#line 9 "tests/01__basics/009__logic_or/test.code"
        return 1;
    }
#line 11 "tests/01__basics/009__logic_or/test.code"
    if (f || t) {
    } else {
#line 14 "tests/01__basics/009__logic_or/test.code"
        return 2;
    }
#line 16 "tests/01__basics/009__logic_or/test.code"
    if (t || t) {
    } else {
#line 19 "tests/01__basics/009__logic_or/test.code"
        return 3;
    }
#line 21 "tests/01__basics/009__logic_or/test.code"
    if (f || f) {
#line 22 "tests/01__basics/009__logic_or/test.code"
        return 4;
    }
#line 24 "tests/01__basics/009__logic_or/test.code"
    if ((f || f) || (f || f)) {
#line 25 "tests/01__basics/009__logic_or/test.code"
        return 5;
    }
#line 27 "tests/01__basics/009__logic_or/test.code"
    return 0;
}

#line 30 "tests/01__basics/009__logic_or/test.code"
bool test__echo(bool v) {
#line 31 "tests/01__basics/009__logic_or/test.code"
    return v;
}

