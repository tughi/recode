#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

#include "test.h"

#line 1 "tests/05__extensions/001__external_type_extension/test.code"
int32_t test__main() {
#line 2 "tests/05__extensions/001__external_type_extension/test.code"
    ptest_FILE__write__1_char(ptest_FILE__write__1_char(ptest_FILE__write__1_char(__stdoutp, '4'), '2'), '\n');
#line 3 "tests/05__extensions/001__external_type_extension/test.code"
    return 0;
}

#line 6 "tests/05__extensions/001__external_type_extension/test.code"
struct test_FILE *ptest_FILE__write__1_char(struct test_FILE *self, uint8_t ch) {
#line 7 "tests/05__extensions/001__external_type_extension/test.code"
    fputc(((int32_t) ch), __stdoutp);
#line 8 "tests/05__extensions/001__external_type_extension/test.code"
    return self;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

