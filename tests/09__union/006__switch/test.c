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

#line 11 "tests/09__union/006__switch/test.code"
int32_t main() {
#line 12 "tests/09__union/006__switch/test.code"
    struct Value value = (struct Value){.variant = 2, .variant_2 = (struct Integer){.variant = 2, .variant_2 = 42}};
#line 14 "tests/09__union/006__switch/test.code"
    for (;;) {
#line 15 "tests/09__union/006__switch/test.code"
        while (false) {
        }
#line 16 "tests/09__union/006__switch/test.code"
        if (value.variant == 1) {
#line 17 "tests/09__union/006__switch/test.code"
            return 1;
        }
#line 19 "tests/09__union/006__switch/test.code"
        else if (value.variant == 2) {
#line 20 "tests/09__union/006__switch/test.code"
            while (false) {
            }
#line 21 "tests/09__union/006__switch/test.code"
            if (value.variant_2.variant == 1) {
#line 22 "tests/09__union/006__switch/test.code"
                return 2;
            }
#line 24 "tests/09__union/006__switch/test.code"
            else if (value.variant_2.variant == 2) {
#line 25 "tests/09__union/006__switch/test.code"
                if (value.variant_2.variant_2 != 42) {
#line 26 "tests/09__union/006__switch/test.code"
                    return 3;
                }
#line 28 "tests/09__union/006__switch/test.code"
                break;
            }
        }
#line 34 "tests/09__union/006__switch/test.code"
        return 4;
    }
#line 37 "tests/09__union/006__switch/test.code"
    return 0;
}

