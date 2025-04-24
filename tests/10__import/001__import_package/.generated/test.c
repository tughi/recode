#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

#include "test.h"

#line 3 "tests/10__import/001__import_package/test.code"
int32_t test__main() {
#line 4 "tests/10__import/001__import_package/test.code"
    return foo__bar() - 42;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

