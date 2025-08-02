#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/01__basics/010__logic/test.code"
int32_t test__main() {
#line 2 "tests/01__basics/010__logic/test.code"
    bool t = test__echo(true);
#line 3 "tests/01__basics/010__logic/test.code"
    bool f = test__echo(false);
#line 4 "tests/01__basics/010__logic/test.code"
    if ((t && f || f && t) || !((t || f) && (f || t))) {
#line 5 "tests/01__basics/010__logic/test.code"
        return 1;
    }
#line 7 "tests/01__basics/010__logic/test.code"
    return 0;
}

#line 10 "tests/01__basics/010__logic/test.code"
bool test__echo(bool v) {
#line 11 "tests/01__basics/010__logic/test.code"
    return v;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

