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

struct Value test__demo__0_value(struct Value value);

int32_t main(int argc, const char **argv) {
    return test__main();
}

#line 8 "tests/09__union/004__union_value_argument/test.code"
int32_t test__main() {
#line 9 "tests/09__union/004__union_value_argument/test.code"
    struct Value value;
#line 10 "tests/09__union/004__union_value_argument/test.code"
    value = (struct Value){.variant = 2, .variant_2 = 42};
#line 11 "tests/09__union/004__union_value_argument/test.code"
    struct Value other_value;
#line 12 "tests/09__union/004__union_value_argument/test.code"
    other_value = value;
#line 13 "tests/09__union/004__union_value_argument/test.code"
    struct Value another_value = test__demo__0_value((struct Value){.variant = 1, .variant_1 = true});
#line 14 "tests/09__union/004__union_value_argument/test.code"
    return 0;
}

#line 17 "tests/09__union/004__union_value_argument/test.code"
struct Value test__demo__0_value(struct Value value) {
#line 18 "tests/09__union/004__union_value_argument/test.code"
    return value;
}

