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

int32_t test__main();

int32_t main(int argc, const char **argv) {
    return test__main();
}

#line 8 "tests/09__union/009__nil/test.code"
int32_t test__main() {
#line 9 "tests/09__union/009__nil/test.code"
    struct Value value = (struct Value){.variant = 0};
#line 11 "tests/09__union/009__nil/test.code"
    if (value.variant != 0) {
#line 12 "tests/09__union/009__nil/test.code"
        return 1;
    }
#line 15 "tests/09__union/009__nil/test.code"
    value = (struct Value){.variant = 2, .variant_2 = 42};
#line 17 "tests/09__union/009__nil/test.code"
    if (value.variant == 0) {
#line 18 "tests/09__union/009__nil/test.code"
        return 2;
    }
#line 21 "tests/09__union/009__nil/test.code"
    return 0;
}

