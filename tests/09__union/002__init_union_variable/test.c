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

#line 13 "tests/09__union/002__init_union_variable/test.code"
int32_t test__main() {
#line 14 "tests/09__union/002__init_union_variable/test.code"
    struct Value value = (struct Value){.variant = 1, .variant_1 = false};
#line 15 "tests/09__union/002__init_union_variable/test.code"
    struct Value other_value = value;
#line 16 "tests/09__union/002__init_union_variable/test.code"
    struct Value another_value = other_value;
#line 17 "tests/09__union/002__init_union_variable/test.code"
    return 0;
}

