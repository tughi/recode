#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t test__main();

bool test__echo(bool v);

int32_t main(int argc, const char **argv) {
    return test__main();
}

#line 3 "tests/01__basics/010__logic/test.code"
int32_t test__main() {
#line 4 "tests/01__basics/010__logic/test.code"
    bool t = test__echo(true);
#line 5 "tests/01__basics/010__logic/test.code"
    bool f = test__echo(false);
#line 6 "tests/01__basics/010__logic/test.code"
    if ((t && f || f && t) || !((t || f) && (f || t))) {
#line 7 "tests/01__basics/010__logic/test.code"
        return 1;
    }
#line 9 "tests/01__basics/010__logic/test.code"
    return 0;
}

#line 12 "tests/01__basics/010__logic/test.code"
bool test__echo(bool v) {
#line 13 "tests/01__basics/010__logic/test.code"
    return v;
}

