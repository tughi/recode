#include "test.h"

void *malloc(uintmax_t size);

#line 11 "tests/09__variant/005__make_variant_value/test.code"
int32_t test__main() {
#line 12 "tests/09__variant/005__make_variant_value/test.code"
    struct test_Value value = (struct test_Value){.variant = 2, .variant_2 = (struct test_Integer){.variant = 2, .variant_2 = 256}};
#line 13 "tests/09__variant/005__make_variant_value/test.code"
    value = (struct test_Value){.variant = 2, .variant_2 = (struct test_Integer){.variant = 2, .variant_2 = 42}};
#line 14 "tests/09__variant/005__make_variant_value/test.code"
    return 0;
#line 15 "tests/09__variant/005__make_variant_value/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

