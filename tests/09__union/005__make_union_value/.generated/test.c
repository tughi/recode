#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

#include "test.h"

#line 11 "tests/09__union/005__make_union_value/test.code"
int32_t test__main() {
#line 12 "tests/09__union/005__make_union_value/test.code"
    struct Value value = (struct Value){.variant = 2, .variant_2 = (struct Integer){.variant = 2, .variant_2 = 256}};
#line 13 "tests/09__union/005__make_union_value/test.code"
    value = (struct Value){.variant = 2, .variant_2 = (struct Integer){.variant = 2, .variant_2 = 42}};
#line 14 "tests/09__union/005__make_union_value/test.code"
    return 0;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

