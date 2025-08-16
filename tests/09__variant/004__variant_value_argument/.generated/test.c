#include "test.h"

void *malloc(uintmax_t size);

#line 6 "tests/09__variant/004__variant_value_argument/test.code"
int32_t test__main() {
#line 7 "tests/09__variant/004__variant_value_argument/test.code"
    struct test_Value value;
#line 8 "tests/09__variant/004__variant_value_argument/test.code"
    value = (struct test_Value){.variant = 2, .variant_2 = 42};
#line 9 "tests/09__variant/004__variant_value_argument/test.code"
    struct test_Value other_value;
#line 10 "tests/09__variant/004__variant_value_argument/test.code"
    other_value = value;
#line 11 "tests/09__variant/004__variant_value_argument/test.code"
    struct test_Value another_value = test__demo((struct test_Value){.variant = 1, .variant_1 = true});
#line 12 "tests/09__variant/004__variant_value_argument/test.code"
    return 0;
#line 13 "tests/09__variant/004__variant_value_argument/test.code"
}

#line 15 "tests/09__variant/004__variant_value_argument/test.code"
struct test_Value test__demo(struct test_Value value) {
#line 16 "tests/09__variant/004__variant_value_argument/test.code"
    return value;
#line 17 "tests/09__variant/004__variant_value_argument/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

