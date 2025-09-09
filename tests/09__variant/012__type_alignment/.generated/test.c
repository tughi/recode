#include "test.h"

void *malloc(uintmax_t size);

#line 11 "tests/09__variant/012__type_alignment/test.code"
int32_t test__main() {
#line 12 "tests/09__variant/012__type_alignment/test.code"
    if (4 != 4) {
#line 13 "tests/09__variant/012__type_alignment/test.code"
        {
#line 13 "tests/09__variant/012__type_alignment/test.code"
            int32_t __001__ = 1;
#line 13 "tests/09__variant/012__type_alignment/test.code"
            return __001__;
#line 13 "tests/09__variant/012__type_alignment/test.code"
        }
#line 14 "tests/09__variant/012__type_alignment/test.code"
    }
#line 15 "tests/09__variant/012__type_alignment/test.code"
    if (8 != 8) {
#line 16 "tests/09__variant/012__type_alignment/test.code"
        {
#line 16 "tests/09__variant/012__type_alignment/test.code"
            int32_t __002__ = 2;
#line 16 "tests/09__variant/012__type_alignment/test.code"
            return __002__;
#line 16 "tests/09__variant/012__type_alignment/test.code"
        }
#line 17 "tests/09__variant/012__type_alignment/test.code"
    }
#line 18 "tests/09__variant/012__type_alignment/test.code"
    {
#line 18 "tests/09__variant/012__type_alignment/test.code"
        int32_t __003__ = 0;
#line 18 "tests/09__variant/012__type_alignment/test.code"
        return __003__;
#line 18 "tests/09__variant/012__type_alignment/test.code"
    }
#line 19 "tests/09__variant/012__type_alignment/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

