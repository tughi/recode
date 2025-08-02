#include "test.h"
#include "libc.h"

void *malloc(uintmax_t size);

#line 3 "tests/10__import/005__external_variable/test.code"
int32_t test__main() {
#line 4 "tests/10__import/005__external_variable/test.code"
    {
#line 4 "tests/10__import/005__external_variable/test.code"
        int32_t __001__ = ((int32_t) '4');
#line 4 "tests/10__import/005__external_variable/test.code"
        struct libc_FILE *__002__ = __stdoutp;
#line 4 "tests/10__import/005__external_variable/test.code"
        fputc(__001__, __002__);
    }
#line 5 "tests/10__import/005__external_variable/test.code"
    {
#line 5 "tests/10__import/005__external_variable/test.code"
        int32_t __001__ = ((int32_t) '2');
#line 5 "tests/10__import/005__external_variable/test.code"
        struct libc_FILE *__002__ = __stdoutp;
#line 5 "tests/10__import/005__external_variable/test.code"
        fputc(__001__, __002__);
    }
#line 6 "tests/10__import/005__external_variable/test.code"
    {
#line 6 "tests/10__import/005__external_variable/test.code"
        int32_t __001__ = ((int32_t) '\n');
#line 6 "tests/10__import/005__external_variable/test.code"
        struct libc_FILE *__002__ = __stdoutp;
#line 6 "tests/10__import/005__external_variable/test.code"
        fputc(__001__, __002__);
    }
#line 8 "tests/10__import/005__external_variable/test.code"
    return 0;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

