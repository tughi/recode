#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

#include "test.h"

#line 6 "tests/09__union/008__is/test.code"
int32_t test__main() {
#line 7 "tests/09__union/008__is/test.code"
    struct Value value = (struct Value){.variant = 2, .variant_2 = 42};
#line 9 "tests/09__union/008__is/test.code"
    if (value.variant == 2) {
#line 10 "tests/09__union/008__is/test.code"
        return 0;
    }
#line 13 "tests/09__union/008__is/test.code"
    return 1;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

