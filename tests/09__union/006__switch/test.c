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

int32_t test__main();

int32_t main(int argc, const char **argv) {
    return test__main();
}

#line 13 "tests/09__union/006__switch/test.code"
int32_t test__main() {
#line 14 "tests/09__union/006__switch/test.code"
    struct Value value = (struct Value){.variant = 2, .variant_2 = (struct Integer){.variant = 2, .variant_2 = 42}};
#line 16 "tests/09__union/006__switch/test.code"
    for (;;) {
#line 17 "tests/09__union/006__switch/test.code"
        struct Value __switch_17_value__ = value;
#line 18 "tests/09__union/006__switch/test.code"
        if (__switch_17_value__.variant == 1) {
#line 19 "tests/09__union/006__switch/test.code"
            return 1;
        }
#line 21 "tests/09__union/006__switch/test.code"
        else if (__switch_17_value__.variant == 2) {
#line 22 "tests/09__union/006__switch/test.code"
            struct Integer __switch_22_value__ = __switch_17_value__.variant_2;
#line 23 "tests/09__union/006__switch/test.code"
            if (__switch_22_value__.variant == 1) {
#line 24 "tests/09__union/006__switch/test.code"
                return 2;
            }
#line 26 "tests/09__union/006__switch/test.code"
            else if (__switch_22_value__.variant == 2) {
#line 27 "tests/09__union/006__switch/test.code"
                if (__switch_22_value__.variant_2 != 42) {
#line 28 "tests/09__union/006__switch/test.code"
                    return 3;
                }
#line 30 "tests/09__union/006__switch/test.code"
                break;
            }
#line 32 "tests/09__union/006__switch/test.code"
            else if (__switch_22_value__.variant == 0) {
#line 33 "tests/09__union/006__switch/test.code"
                return 4;
            }
        }
#line 37 "tests/09__union/006__switch/test.code"
        else if (__switch_17_value__.variant == 0) {
#line 38 "tests/09__union/006__switch/test.code"
            return 5;
        }
#line 42 "tests/09__union/006__switch/test.code"
        return 6;
    }
#line 45 "tests/09__union/006__switch/test.code"
    return 0;
}

