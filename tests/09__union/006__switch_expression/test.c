#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct Value;

struct Literal;

struct Value {
    int32_t variant;
    union {
        bool variant_1;
        int8_t variant_2;
        int32_t variant_3;
    };
};

struct Literal {
    struct Value value;
};

int32_t test__main();

int32_t main(int argc, const char **argv) {
    return test__main();
}

#line 13 "tests/09__union/006__switch_expression/test.code"
int32_t test__main() {
#line 14 "tests/09__union/006__switch_expression/test.code"
    struct Literal literal = (struct Literal){.value = (struct Value){.variant = 3, .variant_3 = 42}};
#line 15 "tests/09__union/006__switch_expression/test.code"
    struct Value __switch_15_value__ = literal.value;
#line 16 "tests/09__union/006__switch_expression/test.code"
    if (__switch_15_value__.variant == 3) {
#line 17 "tests/09__union/006__switch_expression/test.code"
        return __switch_15_value__.variant_3 - 42;
    }
#line 19 "tests/09__union/006__switch_expression/test.code"
    else {
#line 20 "tests/09__union/006__switch_expression/test.code"
        return 1;
    }
}

