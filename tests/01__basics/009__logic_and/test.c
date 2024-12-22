#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t test__main();

bool test__echo(bool v);

int32_t main(int argc, const char **argv) {
    return test__main();
}

#line 3 "tests/01__basics/009__logic_and/test.code"
int32_t test__main() {
#line 4 "tests/01__basics/009__logic_and/test.code"
    bool t = test__echo(true);
#line 5 "tests/01__basics/009__logic_and/test.code"
    bool f = test__echo(false);
#line 6 "tests/01__basics/009__logic_and/test.code"
    if (t && f) {
#line 7 "tests/01__basics/009__logic_and/test.code"
        return 1;
    }
#line 9 "tests/01__basics/009__logic_and/test.code"
    if (f && t) {
#line 10 "tests/01__basics/009__logic_and/test.code"
        return 2;
    }
#line 12 "tests/01__basics/009__logic_and/test.code"
    if (t && t) {
    } else {
#line 15 "tests/01__basics/009__logic_and/test.code"
        return 3;
    }
#line 17 "tests/01__basics/009__logic_and/test.code"
    if (f && f) {
#line 18 "tests/01__basics/009__logic_and/test.code"
        return 4;
    }
#line 20 "tests/01__basics/009__logic_and/test.code"
    if ((t && t) && (f && f)) {
#line 21 "tests/01__basics/009__logic_and/test.code"
        return 5;
    }
#line 23 "tests/01__basics/009__logic_and/test.code"
    return 0;
}

#line 26 "tests/01__basics/009__logic_and/test.code"
bool test__echo(bool v) {
#line 27 "tests/01__basics/009__logic_and/test.code"
    return v;
}

