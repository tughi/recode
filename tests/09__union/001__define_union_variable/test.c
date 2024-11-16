#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct Integer;

struct Integer {
    int32_t variant;
    union {
        int8_t variant_1;
        int32_t variant_2;
    };
};

int32_t main();

#line 6 "tests/09__union/001__define_union_variable/test.code"
int32_t main() {
#line 7 "tests/09__union/001__define_union_variable/test.code"
    struct Integer integer;
#line 8 "tests/09__union/001__define_union_variable/test.code"
    return 0;
}

