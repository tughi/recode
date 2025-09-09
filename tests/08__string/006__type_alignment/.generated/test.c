#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/08__string/006__type_alignment/test.code"
int32_t test__main() {
#line 2 "tests/08__string/006__type_alignment/test.code"
    if (8 != 8) {
#line 3 "tests/08__string/006__type_alignment/test.code"
        {
#line 3 "tests/08__string/006__type_alignment/test.code"
            int32_t __001__ = 1;
#line 3 "tests/08__string/006__type_alignment/test.code"
            return __001__;
#line 3 "tests/08__string/006__type_alignment/test.code"
        }
#line 4 "tests/08__string/006__type_alignment/test.code"
    }
#line 5 "tests/08__string/006__type_alignment/test.code"
    {
#line 5 "tests/08__string/006__type_alignment/test.code"
        int32_t __002__ = 0;
#line 5 "tests/08__string/006__type_alignment/test.code"
        return __002__;
#line 5 "tests/08__string/006__type_alignment/test.code"
    }
#line 6 "tests/08__string/006__type_alignment/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

