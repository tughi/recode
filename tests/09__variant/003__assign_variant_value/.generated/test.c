#include "test.h"

void *malloc(uintmax_t size);

#line 11 "tests/09__variant/003__assign_variant_value/test.code"
int32_t test__main() {
#line 12 "tests/09__variant/003__assign_variant_value/test.code"
    struct test_Value value;
#line 13 "tests/09__variant/003__assign_variant_value/test.code"
    value = (struct test_Value){.variant = 1, .variant_1 = true};
#line 14 "tests/09__variant/003__assign_variant_value/test.code"
    struct test_Value other_value;
#line 15 "tests/09__variant/003__assign_variant_value/test.code"
    other_value = value;
#line 16 "tests/09__variant/003__assign_variant_value/test.code"
    return 0;
#line 17 "tests/09__variant/003__assign_variant_value/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

