#include "test.h"

void *malloc(uintmax_t size);

#line 6 "tests/09__union/009__nil/test.code"
int32_t test__main() {
#line 7 "tests/09__union/009__nil/test.code"
    struct test_Value value = (struct test_Value){.variant = 0};
#line 9 "tests/09__union/009__nil/test.code"
    if (value.variant != 0) {
#line 10 "tests/09__union/009__nil/test.code"
        return 1;
    }
#line 13 "tests/09__union/009__nil/test.code"
    value = (struct test_Value){.variant = 2, .variant_2 = 42};
#line 15 "tests/09__union/009__nil/test.code"
    if (value.variant == 0) {
#line 16 "tests/09__union/009__nil/test.code"
        return 2;
    }
#line 19 "tests/09__union/009__nil/test.code"
    return 0;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

