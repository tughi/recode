#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/03__multi_pointer/004__access_second_item/test.code"
int32_t test__main__anon__anon(int32_t argc, uint8_t **argv) {
#line 2 "tests/03__multi_pointer/004__access_second_item/test.code"
    if (argc < 2) {
#line 3 "tests/03__multi_pointer/004__access_second_item/test.code"
        {
#line 3 "tests/03__multi_pointer/004__access_second_item/test.code"
            int32_t __001__ = 1;
#line 3 "tests/03__multi_pointer/004__access_second_item/test.code"
            return __001__;
#line 3 "tests/03__multi_pointer/004__access_second_item/test.code"
        }
#line 4 "tests/03__multi_pointer/004__access_second_item/test.code"
    }
#line 5 "tests/03__multi_pointer/004__access_second_item/test.code"
    if (argv[1][1] != '0') {
#line 6 "tests/03__multi_pointer/004__access_second_item/test.code"
        {
#line 6 "tests/03__multi_pointer/004__access_second_item/test.code"
            int32_t __002__ = 2;
#line 6 "tests/03__multi_pointer/004__access_second_item/test.code"
            return __002__;
#line 6 "tests/03__multi_pointer/004__access_second_item/test.code"
        }
#line 7 "tests/03__multi_pointer/004__access_second_item/test.code"
    }
#line 8 "tests/03__multi_pointer/004__access_second_item/test.code"
    {
#line 8 "tests/03__multi_pointer/004__access_second_item/test.code"
        int32_t __003__ = 0;
#line 8 "tests/03__multi_pointer/004__access_second_item/test.code"
        return __003__;
#line 8 "tests/03__multi_pointer/004__access_second_item/test.code"
    }
#line 9 "tests/03__multi_pointer/004__access_second_item/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main__anon__anon(argc, (uint8_t **)argv);
}

