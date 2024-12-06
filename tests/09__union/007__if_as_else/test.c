#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct Value;

struct Value {
    int32_t variant;
    union {
        bool variant_1;
        int32_t variant_2;
    };
};

int32_t main();

#line 6 "tests/09__union/007__if_as_else/test.code"
int32_t main() {
#line 7 "tests/09__union/007__if_as_else/test.code"
    struct Value value = (struct Value){.variant = 2, .variant_2 = 42};
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

