#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct Integer;

struct Value;

struct Integer {
    int32_t variant;
    union {
        int8_t variant_1;
        int32_t variant_2;
    };
};

struct Value {
    int32_t variant;
    union {
        bool variant_1;
        struct Integer variant_2;
    };
};

int32_t main();

#line 11 "tests/09__union/006__switch_else/test.code"
int32_t main() {
#line 12 "tests/09__union/006__switch_else/test.code"
    struct Value value = (struct Value){.variant = 2, .variant_2 = (struct Integer){.variant = 2, .variant_2 = 42}};
#line 14 "tests/09__union/006__switch_else/test.code"
    while (false) {
    }
#line 15 "tests/09__union/006__switch_else/test.code"
    if (value.variant == 2) {
#line 16 "tests/09__union/006__switch_else/test.code"
        return 0;
    }
#line 18 "tests/09__union/006__switch_else/test.code"
     else {
#line 19 "tests/09__union/006__switch_else/test.code"
        return 1;
    }
}

