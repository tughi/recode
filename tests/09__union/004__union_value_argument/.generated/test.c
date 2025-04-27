#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

#include "test.h"

#line 6 "tests/09__union/004__union_value_argument/test.code"
int32_t test__main() {
#line 7 "tests/09__union/004__union_value_argument/test.code"
    struct test__Value value;
#line 8 "tests/09__union/004__union_value_argument/test.code"
    value = (struct test__Value){.variant = 2, .variant_2 = 42};
#line 9 "tests/09__union/004__union_value_argument/test.code"
    struct test__Value other_value;
#line 10 "tests/09__union/004__union_value_argument/test.code"
    other_value = value;
#line 11 "tests/09__union/004__union_value_argument/test.code"
    struct test__Value another_value = test__demo__0_value((struct test__Value){.variant = 1, .variant_1 = true});
#line 12 "tests/09__union/004__union_value_argument/test.code"
    return 0;
}

#line 15 "tests/09__union/004__union_value_argument/test.code"
struct test__Value test__demo__0_value(struct test__Value value) {
#line 16 "tests/09__union/004__union_value_argument/test.code"
    return value;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

