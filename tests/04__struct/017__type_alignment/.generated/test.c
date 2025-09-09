#include "test.h"

void *malloc(uintmax_t size);

#line 6 "tests/04__struct/017__type_alignment/test.code"
int32_t test__main() {
#line 7 "tests/04__struct/017__type_alignment/test.code"
    {
#line 7 "tests/04__struct/017__type_alignment/test.code"
        int32_t __001__ = ((int32_t) (4 - 4));
#line 7 "tests/04__struct/017__type_alignment/test.code"
        return __001__;
#line 7 "tests/04__struct/017__type_alignment/test.code"
    }
#line 8 "tests/04__struct/017__type_alignment/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

