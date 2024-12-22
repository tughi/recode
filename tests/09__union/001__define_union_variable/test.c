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

int32_t test__main();

int32_t main(int argc, const char **argv) {
    return test__main();
}

#line 8 "tests/09__union/001__define_union_variable/test.code"
int32_t test__main() {
#line 9 "tests/09__union/001__define_union_variable/test.code"
    struct Integer integer;
#line 10 "tests/09__union/001__define_union_variable/test.code"
    return 0;
}

