#include "test.h"

#line 11 "tests/09__union/002__init_union_variable/test.code"
int32_t test__main() {
#line 12 "tests/09__union/002__init_union_variable/test.code"
    struct test_Value value = (struct test_Value){.variant = 1, .variant_1 = false};
#line 13 "tests/09__union/002__init_union_variable/test.code"
    struct test_Value other_value = value;
#line 14 "tests/09__union/002__init_union_variable/test.code"
    struct test_Value another_value = other_value;
#line 15 "tests/09__union/002__init_union_variable/test.code"
    return 0;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

