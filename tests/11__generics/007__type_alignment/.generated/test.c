#include "test.h"

void *malloc(uintmax_t size);

#line 5 "tests/11__generics/007__type_alignment/test.code"
int32_t test__main() {
#line 6 "tests/11__generics/007__type_alignment/test.code"
    if (1 != 1) {
#line 7 "tests/11__generics/007__type_alignment/test.code"
        {
#line 7 "tests/11__generics/007__type_alignment/test.code"
            int32_t __001__ = 1;
#line 7 "tests/11__generics/007__type_alignment/test.code"
            return __001__;
#line 7 "tests/11__generics/007__type_alignment/test.code"
        }
#line 8 "tests/11__generics/007__type_alignment/test.code"
    }
#line 9 "tests/11__generics/007__type_alignment/test.code"
    if (8 != 8) {
#line 10 "tests/11__generics/007__type_alignment/test.code"
        {
#line 10 "tests/11__generics/007__type_alignment/test.code"
            int32_t __002__ = 1;
#line 10 "tests/11__generics/007__type_alignment/test.code"
            return __002__;
#line 10 "tests/11__generics/007__type_alignment/test.code"
        }
#line 11 "tests/11__generics/007__type_alignment/test.code"
    }
#line 12 "tests/11__generics/007__type_alignment/test.code"
    {
#line 12 "tests/11__generics/007__type_alignment/test.code"
        int32_t __003__ = 0;
#line 12 "tests/11__generics/007__type_alignment/test.code"
        return __003__;
#line 12 "tests/11__generics/007__type_alignment/test.code"
    }
#line 13 "tests/11__generics/007__type_alignment/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

