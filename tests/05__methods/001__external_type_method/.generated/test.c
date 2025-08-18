#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/05__methods/001__external_type_method/test.code"
int32_t test__main() {
#line 2 "tests/05__methods/001__external_type_method/test.code"
    ptest_FILE__write(ptest_FILE__write(ptest_FILE__write(__stdoutp, '4'), '2'), '\n');
#line 3 "tests/05__methods/001__external_type_method/test.code"
    {
#line 3 "tests/05__methods/001__external_type_method/test.code"
        int32_t __001__ = 0;
#line 3 "tests/05__methods/001__external_type_method/test.code"
        return __001__;
#line 3 "tests/05__methods/001__external_type_method/test.code"
    }
#line 4 "tests/05__methods/001__external_type_method/test.code"
}

#line 6 "tests/05__methods/001__external_type_method/test.code"
struct test_FILE *ptest_FILE__write(struct test_FILE *self, uint8_t ch) {
#line 7 "tests/05__methods/001__external_type_method/test.code"
    fputc(((int32_t) ch), __stdoutp);
#line 8 "tests/05__methods/001__external_type_method/test.code"
    {
#line 8 "tests/05__methods/001__external_type_method/test.code"
        struct test_FILE *__001__ = self;
#line 8 "tests/05__methods/001__external_type_method/test.code"
        return __001__;
#line 8 "tests/05__methods/001__external_type_method/test.code"
    }
#line 9 "tests/05__methods/001__external_type_method/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

