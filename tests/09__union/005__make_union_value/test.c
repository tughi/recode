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

#line 13 "tests/09__union/005__make_union_value/test.code"
int32_t test__main() {
#line 14 "tests/09__union/005__make_union_value/test.code"
    struct Value value = (struct Value){.variant = 2, .variant_2 = (struct Integer){.variant = 2, .variant_2 = 256}};
#line 15 "tests/09__union/005__make_union_value/test.code"
    value = (struct Value){.variant = 2, .variant_2 = (struct Integer){.variant = 2, .variant_2 = 42}};
#line 16 "tests/09__union/005__make_union_value/test.code"
    return 0;
}

