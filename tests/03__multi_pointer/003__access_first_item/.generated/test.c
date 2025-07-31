#include "test.h"

#line 1 "tests/03__multi_pointer/003__access_first_item/test.code"
int32_t test__main(int32_t argc, uint8_t **argv) {
#line 2 "tests/03__multi_pointer/003__access_first_item/test.code"
    uint8_t *arg;
#line 2 "tests/03__multi_pointer/003__access_first_item/test.code"
    {
#line 2 "tests/03__multi_pointer/003__access_first_item/test.code"
        int32_t __001__ = 0;
#line 2 "tests/03__multi_pointer/003__access_first_item/test.code"
        arg = argv[__001__];
    }
#line 3 "tests/03__multi_pointer/003__access_first_item/test.code"
    uint8_t ch;
#line 3 "tests/03__multi_pointer/003__access_first_item/test.code"
    {
#line 3 "tests/03__multi_pointer/003__access_first_item/test.code"
        int32_t __001__ = 0;
#line 3 "tests/03__multi_pointer/003__access_first_item/test.code"
        ch = arg[__001__];
    }
#line 4 "tests/03__multi_pointer/003__access_first_item/test.code"
    if (ch != 'b') {
#line 5 "tests/03__multi_pointer/003__access_first_item/test.code"
        return 1;
    }
#line 7 "tests/03__multi_pointer/003__access_first_item/test.code"
    return 0;
}

int32_t main(int argc, const char **argv) {
    return test__main(argc, (uint8_t **)argv);
}

