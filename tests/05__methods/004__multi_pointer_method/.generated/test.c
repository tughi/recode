#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/05__methods/004__multi_pointer_method/test.code"
int32_t d_u8_b__length(uint8_t *self) {
#line 2 "tests/05__methods/004__multi_pointer_method/test.code"
    int32_t length = 0;
#line 3 "tests/05__methods/004__multi_pointer_method/test.code"
    while (self[length] != 0) {
#line 4 "tests/05__methods/004__multi_pointer_method/test.code"
        length = length + 1;
#line 5 "tests/05__methods/004__multi_pointer_method/test.code"
    }
#line 6 "tests/05__methods/004__multi_pointer_method/test.code"
    {
#line 6 "tests/05__methods/004__multi_pointer_method/test.code"
        int32_t __001__ = length;
#line 6 "tests/05__methods/004__multi_pointer_method/test.code"
        return __001__;
#line 6 "tests/05__methods/004__multi_pointer_method/test.code"
    }
#line 7 "tests/05__methods/004__multi_pointer_method/test.code"
}

#line 9 "tests/05__methods/004__multi_pointer_method/test.code"
int32_t test__main(int32_t argc, uint8_t **argv) {
#line 10 "tests/05__methods/004__multi_pointer_method/test.code"
    if (argc != 2) {
#line 11 "tests/05__methods/004__multi_pointer_method/test.code"
        {
#line 11 "tests/05__methods/004__multi_pointer_method/test.code"
            int32_t __001__ = 1;
#line 11 "tests/05__methods/004__multi_pointer_method/test.code"
            return __001__;
#line 11 "tests/05__methods/004__multi_pointer_method/test.code"
        }
#line 12 "tests/05__methods/004__multi_pointer_method/test.code"
    }
#line 13 "tests/05__methods/004__multi_pointer_method/test.code"
    if (d_u8_b__length(argv[1]) != 4) {
#line 14 "tests/05__methods/004__multi_pointer_method/test.code"
        {
#line 14 "tests/05__methods/004__multi_pointer_method/test.code"
            int32_t __002__ = 2;
#line 14 "tests/05__methods/004__multi_pointer_method/test.code"
            return __002__;
#line 14 "tests/05__methods/004__multi_pointer_method/test.code"
        }
#line 15 "tests/05__methods/004__multi_pointer_method/test.code"
    }
#line 16 "tests/05__methods/004__multi_pointer_method/test.code"
    {
#line 16 "tests/05__methods/004__multi_pointer_method/test.code"
        int32_t __003__ = 0;
#line 16 "tests/05__methods/004__multi_pointer_method/test.code"
        return __003__;
#line 16 "tests/05__methods/004__multi_pointer_method/test.code"
    }
#line 17 "tests/05__methods/004__multi_pointer_method/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main(argc, (uint8_t **)argv);
}

