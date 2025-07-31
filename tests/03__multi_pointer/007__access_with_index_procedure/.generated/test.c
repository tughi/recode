#include "test.h"

#line 1 "tests/03__multi_pointer/007__access_with_index_procedure/test.code"
int32_t test__main(int32_t argc, uint8_t **argv) {
#line 2 "tests/03__multi_pointer/007__access_with_index_procedure/test.code"
    if (argc < 2) {
#line 3 "tests/03__multi_pointer/007__access_with_index_procedure/test.code"
        return 1;
    }
#line 5 "tests/03__multi_pointer/007__access_with_index_procedure/test.code"
    int32_t i = 1;
#line 6 "tests/03__multi_pointer/007__access_with_index_procedure/test.code"
    {
#line 6 "tests/03__multi_pointer/007__access_with_index_procedure/test.code"
        int32_t __001__ = i;
#line 6 "tests/03__multi_pointer/007__access_with_index_procedure/test.code"
        int32_t __002__ = test__index(__001__);
#line 6 "tests/03__multi_pointer/007__access_with_index_procedure/test.code"
        int32_t __003__ = i;
#line 6 "tests/03__multi_pointer/007__access_with_index_procedure/test.code"
        int32_t __004__ = test__index(__003__);
#line 6 "tests/03__multi_pointer/007__access_with_index_procedure/test.code"
        uint8_t *__005__ = argv[__002__];
#line 6 "tests/03__multi_pointer/007__access_with_index_procedure/test.code"
        if (__005__[__004__] != '0') {
#line 7 "tests/03__multi_pointer/007__access_with_index_procedure/test.code"
            return 2;
        }
    }
#line 9 "tests/03__multi_pointer/007__access_with_index_procedure/test.code"
    return 0;
}

#line 12 "tests/03__multi_pointer/007__access_with_index_procedure/test.code"
int32_t test__index(int32_t value) {
#line 13 "tests/03__multi_pointer/007__access_with_index_procedure/test.code"
    return value;
}

int32_t main(int argc, const char **argv) {
    return test__main(argc, (uint8_t **)argv);
}

