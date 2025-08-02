#include "test.h"

void *malloc(uintmax_t size);

#line 6 "tests/09__union/007__if_as_else/test.code"
int32_t test__main() {
#line 7 "tests/09__union/007__if_as_else/test.code"
    struct test_Value value = (struct test_Value){.variant = 2, .variant_2 = 42};
#line 9 "tests/09__union/007__if_as_else/test.code"
    if (value.variant == 2) {
#line 10 "tests/09__union/007__if_as_else/test.code"
        return value.variant_2 - 42;
    } else {
#line 12 "tests/09__union/007__if_as_else/test.code"
        return 1;
    }
#line 15 "tests/09__union/007__if_as_else/test.code"
    return 2;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

