#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t main();

bool echo(bool v);

#line 1 "tests/01__basics/009__logic_or/test.code"
int32_t main() {
#line 2 "tests/01__basics/009__logic_or/test.code"
    bool t = echo(true);
#line 3 "tests/01__basics/009__logic_or/test.code"
    bool f = echo(false);
#line 4 "tests/01__basics/009__logic_or/test.code"
    if (t || f) {
    } else {
#line 7 "tests/01__basics/009__logic_or/test.code"
        return 1;
    }
#line 9 "tests/01__basics/009__logic_or/test.code"
    if (f || t) {
    } else {
#line 12 "tests/01__basics/009__logic_or/test.code"
        return 2;
    }
#line 14 "tests/01__basics/009__logic_or/test.code"
    if (t || t) {
    } else {
#line 17 "tests/01__basics/009__logic_or/test.code"
        return 3;
    }
#line 19 "tests/01__basics/009__logic_or/test.code"
    if (f || f) {
#line 20 "tests/01__basics/009__logic_or/test.code"
        return 4;
    }
#line 22 "tests/01__basics/009__logic_or/test.code"
    if ((f || f) || (f || f)) {
#line 23 "tests/01__basics/009__logic_or/test.code"
        return 5;
    }
#line 25 "tests/01__basics/009__logic_or/test.code"
    return 0;
}

#line 28 "tests/01__basics/009__logic_or/test.code"
bool echo(bool v) {
#line 29 "tests/01__basics/009__logic_or/test.code"
    return v;
}

