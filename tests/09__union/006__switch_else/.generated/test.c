#include "test.h"

void *malloc(uintmax_t size);

#line 11 "tests/09__union/006__switch_else/test.code"
int32_t test__main() {
#line 12 "tests/09__union/006__switch_else/test.code"
    struct test_Value value = (struct test_Value){.variant = 2, .variant_2 = (struct test_Integer){.variant = 2, .variant_2 = 42}};
#line 14 "tests/09__union/006__switch_else/test.code"
    struct test_Value __switch_14_value__ = value;
#line 15 "tests/09__union/006__switch_else/test.code"
    if (__switch_14_value__.variant == 2) {
#line 16 "tests/09__union/006__switch_else/test.code"
        return 0;
    }
#line 18 "tests/09__union/006__switch_else/test.code"
    else {
#line 19 "tests/09__union/006__switch_else/test.code"
        return 1;
    }
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

