#include "test.h"

void *malloc(uintmax_t size);

#line 5 "tests/07__trait/001__local_trait_variable/test.code"
int32_t test__main() {
#line 6 "tests/07__trait/001__local_trait_variable/test.code"
    struct test_Animal animal;
#line 7 "tests/07__trait/001__local_trait_variable/test.code"
    {
#line 7 "tests/07__trait/001__local_trait_variable/test.code"
        int32_t __001__ = 0;
#line 7 "tests/07__trait/001__local_trait_variable/test.code"
        return __001__;
#line 7 "tests/07__trait/001__local_trait_variable/test.code"
    }
#line 8 "tests/07__trait/001__local_trait_variable/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

