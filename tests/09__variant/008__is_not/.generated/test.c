#include "test.h"

void *malloc(uintmax_t size);

#line 6 "tests/09__variant/008__is_not/test.code"
int32_t test__main() {
#line 7 "tests/09__variant/008__is_not/test.code"
    struct test_Value value = (struct test_Value){.variant = 2, .variant_2 = 42};
#line 9 "tests/09__variant/008__is_not/test.code"
    if (value.variant != 1) {
#line 10 "tests/09__variant/008__is_not/test.code"
        return 0;
    }
#line 13 "tests/09__variant/008__is_not/test.code"
    return 1;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

