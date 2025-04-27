#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

#include "test.h"

#line 11 "tests/09__union/006__switch_else_only/test.code"
int32_t test__main() {
#line 12 "tests/09__union/006__switch_else_only/test.code"
    struct test__Value value = (struct test__Value){.variant = 2, .variant_2 = (struct test__Integer){.variant = 2, .variant_2 = 42}};
#line 14 "tests/09__union/006__switch_else_only/test.code"
    struct test__Value __switch_14_value__ = value;
#line 15 "tests/09__union/006__switch_else_only/test.code"
    {
#line 16 "tests/09__union/006__switch_else_only/test.code"
        return 0;
    }
#line 20 "tests/09__union/006__switch_else_only/test.code"
    return 1;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

