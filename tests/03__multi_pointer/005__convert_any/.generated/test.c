#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/03__multi_pointer/005__convert_any/test.code"
int32_t test__main(int32_t argc, uint8_t **argv) {
#line 2 "tests/03__multi_pointer/005__convert_any/test.code"
    void *any = ((void *) argv[0]);
#line 3 "tests/03__multi_pointer/005__convert_any/test.code"
    uint8_t *name = ((uint8_t *) any);
#line 4 "tests/03__multi_pointer/005__convert_any/test.code"
    if (name[0] != 'b') {
#line 5 "tests/03__multi_pointer/005__convert_any/test.code"
        {
#line 5 "tests/03__multi_pointer/005__convert_any/test.code"
            int32_t __001__ = 1;
#line 5 "tests/03__multi_pointer/005__convert_any/test.code"
            return __001__;
#line 5 "tests/03__multi_pointer/005__convert_any/test.code"
        }
#line 6 "tests/03__multi_pointer/005__convert_any/test.code"
    }
#line 7 "tests/03__multi_pointer/005__convert_any/test.code"
    {
#line 7 "tests/03__multi_pointer/005__convert_any/test.code"
        int32_t __002__ = 0;
#line 7 "tests/03__multi_pointer/005__convert_any/test.code"
        return __002__;
#line 7 "tests/03__multi_pointer/005__convert_any/test.code"
    }
#line 8 "tests/03__multi_pointer/005__convert_any/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main(argc, (uint8_t **)argv);
}

