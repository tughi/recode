#include "test.h"

#line 1 "tests/03__multi_pointer/004__access_second_item/test.code"
int32_t test__main(int32_t argc, uint8_t **argv) {
#line 2 "tests/03__multi_pointer/004__access_second_item/test.code"
    if (argc < 2) {
#line 3 "tests/03__multi_pointer/004__access_second_item/test.code"
        return 1;
    }
#line 5 "tests/03__multi_pointer/004__access_second_item/test.code"
    {
#line 5 "tests/03__multi_pointer/004__access_second_item/test.code"
        int32_t __001__ = 1;
#line 5 "tests/03__multi_pointer/004__access_second_item/test.code"
        int32_t __002__ = 1;
#line 5 "tests/03__multi_pointer/004__access_second_item/test.code"
        uint8_t *__003__ = argv[__001__];
#line 5 "tests/03__multi_pointer/004__access_second_item/test.code"
        if (__003__[__002__] != '0') {
#line 6 "tests/03__multi_pointer/004__access_second_item/test.code"
            return 2;
        }
    }
#line 8 "tests/03__multi_pointer/004__access_second_item/test.code"
    return 0;
}

int32_t main(int argc, const char **argv) {
    return test__main(argc, (uint8_t **)argv);
}

