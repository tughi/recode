#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/01__basics/034__type_size/test.code"
int32_t test__main() {
#line 2 "tests/01__basics/034__type_size/test.code"
    uintmax_t size = sizeof(int32_t);
#line 3 "tests/01__basics/034__type_size/test.code"
    if (size != 4u) {
#line 4 "tests/01__basics/034__type_size/test.code"
        {
#line 4 "tests/01__basics/034__type_size/test.code"
            int32_t __001__ = 1;
#line 4 "tests/01__basics/034__type_size/test.code"
            return __001__;
#line 4 "tests/01__basics/034__type_size/test.code"
        }
#line 5 "tests/01__basics/034__type_size/test.code"
    }
#line 6 "tests/01__basics/034__type_size/test.code"
    {
#line 6 "tests/01__basics/034__type_size/test.code"
        int32_t __002__ = 0;
#line 6 "tests/01__basics/034__type_size/test.code"
        return __002__;
#line 6 "tests/01__basics/034__type_size/test.code"
    }
#line 7 "tests/01__basics/034__type_size/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

