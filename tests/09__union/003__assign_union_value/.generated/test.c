#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

#include "test.h"

#line 11 "tests/09__union/003__assign_union_value/test.code"
int32_t test__main() {
#line 12 "tests/09__union/003__assign_union_value/test.code"
    struct test__Value value;
#line 13 "tests/09__union/003__assign_union_value/test.code"
    value = (struct test__Value){.variant = 1, .variant_1 = true};
#line 14 "tests/09__union/003__assign_union_value/test.code"
    struct test__Value other_value;
#line 15 "tests/09__union/003__assign_union_value/test.code"
    other_value = value;
#line 16 "tests/09__union/003__assign_union_value/test.code"
    return 0;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

