#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/03__multi_pointer/002__main_parameters/test.code"
int32_t test__main(int32_t argc, uint8_t **argv) {
#line 2 "tests/03__multi_pointer/002__main_parameters/test.code"
    {
#line 2 "tests/03__multi_pointer/002__main_parameters/test.code"
        int32_t __001__ = 0;
#line 2 "tests/03__multi_pointer/002__main_parameters/test.code"
        return __001__;
#line 2 "tests/03__multi_pointer/002__main_parameters/test.code"
    }
#line 3 "tests/03__multi_pointer/002__main_parameters/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main(argc, (uint8_t **)argv);
}

