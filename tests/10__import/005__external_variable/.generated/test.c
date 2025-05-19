#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

#include "test.h"

#line 3 "tests/10__import/005__external_variable/test.code"
int32_t test__main() {
#line 4 "tests/10__import/005__external_variable/test.code"
    fputc(52, __stdoutp);
#line 5 "tests/10__import/005__external_variable/test.code"
    fputc(50, __stdoutp);
#line 6 "tests/10__import/005__external_variable/test.code"
    fputc(10, __stdoutp);
#line 8 "tests/10__import/005__external_variable/test.code"
    return 0;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

