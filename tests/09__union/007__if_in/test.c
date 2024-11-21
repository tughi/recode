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

#line 6 "tests/09__union/007__if_in/test.code"
int32_t main() {
#line 7 "tests/09__union/007__if_in/test.code"
    struct Value value = (struct Value){.variant = 2, .variant_2 = 42};
#line 9 "tests/09__union/007__if_in/test.code"
    if (value.variant == 2) {
#line 10 "tests/09__union/007__if_in/test.code"
        return value.variant_2 - 42;
    }
#line 13 "tests/09__union/007__if_in/test.code"
    return 1;
}

