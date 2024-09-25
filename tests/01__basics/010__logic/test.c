#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t main();

bool echo(bool v);

#line 1 "tests/01__basics/010__logic/test.code"
int32_t main() {
#line 2 "tests/01__basics/010__logic/test.code"
    bool t = echo(true);
#line 3 "tests/01__basics/010__logic/test.code"
    bool f = echo(false);
#line 4 "tests/01__basics/010__logic/test.code"
    if ((t && f || f && t) || !((t || f) && (f || t))) {
#line 5 "tests/01__basics/010__logic/test.code"
        return 1;
    }
#line 7 "tests/01__basics/010__logic/test.code"
    return 0;
}

#line 10 "tests/01__basics/010__logic/test.code"
bool echo(bool v) {
#line 11 "tests/01__basics/010__logic/test.code"
    return v;
}

