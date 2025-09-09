#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/03__multi_pointer/009__type_alignment/test.code"
int32_t test__main() {
#line 2 "tests/03__multi_pointer/009__type_alignment/test.code"
    if (1 != 1u) {
#line 3 "tests/03__multi_pointer/009__type_alignment/test.code"
        {
#line 3 "tests/03__multi_pointer/009__type_alignment/test.code"
            int32_t __001__ = 1;
#line 3 "tests/03__multi_pointer/009__type_alignment/test.code"
            return __001__;
#line 3 "tests/03__multi_pointer/009__type_alignment/test.code"
        }
#line 4 "tests/03__multi_pointer/009__type_alignment/test.code"
    }
#line 5 "tests/03__multi_pointer/009__type_alignment/test.code"
    if (2 != 2u) {
#line 6 "tests/03__multi_pointer/009__type_alignment/test.code"
        {
#line 6 "tests/03__multi_pointer/009__type_alignment/test.code"
            int32_t __002__ = 2;
#line 6 "tests/03__multi_pointer/009__type_alignment/test.code"
            return __002__;
#line 6 "tests/03__multi_pointer/009__type_alignment/test.code"
        }
#line 7 "tests/03__multi_pointer/009__type_alignment/test.code"
    }
#line 8 "tests/03__multi_pointer/009__type_alignment/test.code"
    if (8 != 8u) {
#line 9 "tests/03__multi_pointer/009__type_alignment/test.code"
        {
#line 9 "tests/03__multi_pointer/009__type_alignment/test.code"
            int32_t __003__ = 3;
#line 9 "tests/03__multi_pointer/009__type_alignment/test.code"
            return __003__;
#line 9 "tests/03__multi_pointer/009__type_alignment/test.code"
        }
#line 10 "tests/03__multi_pointer/009__type_alignment/test.code"
    }
#line 11 "tests/03__multi_pointer/009__type_alignment/test.code"
    {
#line 11 "tests/03__multi_pointer/009__type_alignment/test.code"
        int32_t __004__ = 0;
#line 11 "tests/03__multi_pointer/009__type_alignment/test.code"
        return __004__;
#line 11 "tests/03__multi_pointer/009__type_alignment/test.code"
    }
#line 12 "tests/03__multi_pointer/009__type_alignment/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

