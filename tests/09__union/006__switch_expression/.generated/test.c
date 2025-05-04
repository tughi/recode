#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

#include "test.h"

#line 11 "tests/09__union/006__switch_expression/test.code"
int32_t test__main() {
#line 12 "tests/09__union/006__switch_expression/test.code"
    struct test_Literal literal = (struct test_Literal){.value = (struct test_Value){.variant = 3, .variant_3 = 42}};
#line 13 "tests/09__union/006__switch_expression/test.code"
    struct test_Value __switch_13_value__ = literal.value;
#line 14 "tests/09__union/006__switch_expression/test.code"
    if (__switch_13_value__.variant == 3) {
#line 15 "tests/09__union/006__switch_expression/test.code"
        return __switch_13_value__.variant_3 - 42;
    }
#line 17 "tests/09__union/006__switch_expression/test.code"
    else {
#line 18 "tests/09__union/006__switch_expression/test.code"
        return 1;
    }
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

