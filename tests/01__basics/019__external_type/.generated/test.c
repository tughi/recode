#include "test.h"

#line 7 "tests/01__basics/019__external_type/test.code"
int32_t test__main() {
#line 8 "tests/01__basics/019__external_type/test.code"
    {
#line 8 "tests/01__basics/019__external_type/test.code"
        int32_t __001__ = 52;
#line 8 "tests/01__basics/019__external_type/test.code"
        struct test_FILE *__002__ = __stdoutp;
#line 8 "tests/01__basics/019__external_type/test.code"
        fputc(__001__, __002__);
    }
#line 9 "tests/01__basics/019__external_type/test.code"
    {
#line 9 "tests/01__basics/019__external_type/test.code"
        int32_t __001__ = 50;
#line 9 "tests/01__basics/019__external_type/test.code"
        struct test_FILE *__002__ = __stdoutp;
#line 9 "tests/01__basics/019__external_type/test.code"
        fputc(__001__, __002__);
    }
#line 10 "tests/01__basics/019__external_type/test.code"
    {
#line 10 "tests/01__basics/019__external_type/test.code"
        int32_t __001__ = 10;
#line 10 "tests/01__basics/019__external_type/test.code"
        struct test_FILE *__002__ = __stdoutp;
#line 10 "tests/01__basics/019__external_type/test.code"
        fputc(__001__, __002__);
    }
#line 11 "tests/01__basics/019__external_type/test.code"
    return 0;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

