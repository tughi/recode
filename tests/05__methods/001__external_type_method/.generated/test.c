#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/05__methods/001__external_type_method/test.code"
int32_t test__main() {
#line 2 "tests/05__methods/001__external_type_method/test.code"
    {
#line 2 "tests/05__methods/001__external_type_method/test.code"
        struct test_FILE *__001__ = __stdoutp;
#line 2 "tests/05__methods/001__external_type_method/test.code"
        uint8_t __002__ = '4';
#line 2 "tests/05__methods/001__external_type_method/test.code"
        struct test_FILE *__003__ = ptest_FILE__write(__001__, __002__);
#line 2 "tests/05__methods/001__external_type_method/test.code"
        uint8_t __004__ = '2';
#line 2 "tests/05__methods/001__external_type_method/test.code"
        struct test_FILE *__005__ = ptest_FILE__write(__003__, __004__);
#line 2 "tests/05__methods/001__external_type_method/test.code"
        uint8_t __006__ = '\n';
#line 2 "tests/05__methods/001__external_type_method/test.code"
        ptest_FILE__write(__005__, __006__);
    }
#line 3 "tests/05__methods/001__external_type_method/test.code"
    return 0;
}

#line 6 "tests/05__methods/001__external_type_method/test.code"
struct test_FILE *ptest_FILE__write(struct test_FILE *self, uint8_t ch) {
#line 7 "tests/05__methods/001__external_type_method/test.code"
    {
#line 7 "tests/05__methods/001__external_type_method/test.code"
        int32_t __001__ = ((int32_t) ch);
#line 7 "tests/05__methods/001__external_type_method/test.code"
        struct test_FILE *__002__ = __stdoutp;
#line 7 "tests/05__methods/001__external_type_method/test.code"
        fputc(__001__, __002__);
    }
#line 8 "tests/05__methods/001__external_type_method/test.code"
    return self;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

