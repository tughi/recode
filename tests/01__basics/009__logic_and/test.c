#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t main();

bool echo(bool v);

#line 1 "tests/01__basics/009__logic_and/test.code"
int32_t main() {
#line 2 "tests/01__basics/009__logic_and/test.code"
    bool t = echo(true);
#line 3 "tests/01__basics/009__logic_and/test.code"
    bool f = echo(false);
#line 4 "tests/01__basics/009__logic_and/test.code"
    if (t && f) {
#line 5 "tests/01__basics/009__logic_and/test.code"
        return 1;
    }
#line 7 "tests/01__basics/009__logic_and/test.code"
    if (f && t) {
#line 8 "tests/01__basics/009__logic_and/test.code"
        return 2;
    }
#line 10 "tests/01__basics/009__logic_and/test.code"
    if (t && t) {
    } else {
#line 13 "tests/01__basics/009__logic_and/test.code"
        return 3;
    }
#line 15 "tests/01__basics/009__logic_and/test.code"
    if (f && f) {
#line 16 "tests/01__basics/009__logic_and/test.code"
        return 4;
    }
#line 18 "tests/01__basics/009__logic_and/test.code"
    if ((t && t) && (f && f)) {
#line 19 "tests/01__basics/009__logic_and/test.code"
        return 5;
    }
#line 21 "tests/01__basics/009__logic_and/test.code"
    return 0;
}

#line 24 "tests/01__basics/009__logic_and/test.code"
bool echo(bool v) {
#line 25 "tests/01__basics/009__logic_and/test.code"
    return v;
}

