#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/05__methods/004__multi_pointer_method/test.code"
int32_t d_u8_b__length(uint8_t *self) {
#line 2 "tests/05__methods/004__multi_pointer_method/test.code"
    int32_t length = 0;
#line 3 "tests/05__methods/004__multi_pointer_method/test.code"
    for (;;) {
#line 3 "tests/05__methods/004__multi_pointer_method/test.code"
        {
#line 3 "tests/05__methods/004__multi_pointer_method/test.code"
            int32_t __001__ = length;
#line 3 "tests/05__methods/004__multi_pointer_method/test.code"
            if (self[__001__] != 0) {} else break;
        }
#line 4 "tests/05__methods/004__multi_pointer_method/test.code"
        length = length + 1;
    }
#line 6 "tests/05__methods/004__multi_pointer_method/test.code"
    return length;
}

#line 9 "tests/05__methods/004__multi_pointer_method/test.code"
int32_t test__main(int32_t argc, uint8_t **argv) {
#line 10 "tests/05__methods/004__multi_pointer_method/test.code"
    if (argc != 2) {
#line 11 "tests/05__methods/004__multi_pointer_method/test.code"
        return 1;
    }
#line 13 "tests/05__methods/004__multi_pointer_method/test.code"
    {
#line 13 "tests/05__methods/004__multi_pointer_method/test.code"
        int32_t __001__ = 1;
#line 13 "tests/05__methods/004__multi_pointer_method/test.code"
        uint8_t *__002__ = argv[__001__];
#line 13 "tests/05__methods/004__multi_pointer_method/test.code"
        if (d_u8_b__length(__002__) != 4) {
#line 14 "tests/05__methods/004__multi_pointer_method/test.code"
            return 2;
        }
    }
#line 16 "tests/05__methods/004__multi_pointer_method/test.code"
    return 0;
}

int32_t main(int argc, const char **argv) {
    return test__main(argc, (uint8_t **)argv);
}

