#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/03__multi_pointer/008__item_reference/test.code"
int32_t test__main() {
#line 2 "tests/03__multi_pointer/008__item_reference/test.code"
    uint64_t number = 0u;
#line 3 "tests/03__multi_pointer/008__item_reference/test.code"
    uint8_t *bytes = ((uint8_t *) (&number));
#line 4 "tests/03__multi_pointer/008__item_reference/test.code"
    uint8_t *fourth_byte = &bytes[3];
#line 5 "tests/03__multi_pointer/008__item_reference/test.code"
    *fourth_byte = 42;
#line 6 "tests/03__multi_pointer/008__item_reference/test.code"
    if (bytes[3] != 42) {
#line 7 "tests/03__multi_pointer/008__item_reference/test.code"
        {
#line 7 "tests/03__multi_pointer/008__item_reference/test.code"
            int32_t __001__ = 1;
#line 7 "tests/03__multi_pointer/008__item_reference/test.code"
            return __001__;
#line 7 "tests/03__multi_pointer/008__item_reference/test.code"
        }
#line 8 "tests/03__multi_pointer/008__item_reference/test.code"
    }
#line 9 "tests/03__multi_pointer/008__item_reference/test.code"
    if (number != 0x2a00000000u && number != 0x2a000000u) {
#line 10 "tests/03__multi_pointer/008__item_reference/test.code"
        {
#line 10 "tests/03__multi_pointer/008__item_reference/test.code"
            int32_t __002__ = 2;
#line 10 "tests/03__multi_pointer/008__item_reference/test.code"
            return __002__;
#line 10 "tests/03__multi_pointer/008__item_reference/test.code"
        }
#line 11 "tests/03__multi_pointer/008__item_reference/test.code"
    }
#line 12 "tests/03__multi_pointer/008__item_reference/test.code"
    {
#line 12 "tests/03__multi_pointer/008__item_reference/test.code"
        int32_t __003__ = 0;
#line 12 "tests/03__multi_pointer/008__item_reference/test.code"
        return __003__;
#line 12 "tests/03__multi_pointer/008__item_reference/test.code"
    }
#line 13 "tests/03__multi_pointer/008__item_reference/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

