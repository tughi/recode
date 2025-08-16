#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/03__multi_pointer/003__access_first_item/test.code"
int32_t test__main(int32_t argc, uint8_t **argv) {
#line 2 "tests/03__multi_pointer/003__access_first_item/test.code"
    uint8_t *arg = argv[0];
#line 3 "tests/03__multi_pointer/003__access_first_item/test.code"
    uint8_t ch = arg[0];
#line 4 "tests/03__multi_pointer/003__access_first_item/test.code"
    if (ch != 'b') {
#line 5 "tests/03__multi_pointer/003__access_first_item/test.code"
        return 1;
#line 6 "tests/03__multi_pointer/003__access_first_item/test.code"
    }
#line 7 "tests/03__multi_pointer/003__access_first_item/test.code"
    return 0;
#line 8 "tests/03__multi_pointer/003__access_first_item/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main(argc, (uint8_t **)argv);
}

