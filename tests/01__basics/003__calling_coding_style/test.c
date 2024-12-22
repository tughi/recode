#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

void test__test(int32_t one, int32_t two, int32_t three, int32_t four, int32_t five);

int32_t test__main();

int32_t main(int argc, const char **argv) {
    return test__main();
}

#line 3 "tests/01__basics/003__calling_coding_style/test.code"
void test__test(int32_t one, int32_t two, int32_t three, int32_t four, int32_t five) {
}

#line 6 "tests/01__basics/003__calling_coding_style/test.code"
int32_t test__main() {
#line 7 "tests/01__basics/003__calling_coding_style/test.code"
    test__test(1, 2, 3, 4, 5);
#line 9 "tests/01__basics/003__calling_coding_style/test.code"
    test__test(1, 2, 3, 4, 5);
#line 21 "tests/01__basics/003__calling_coding_style/test.code"
    test__test(1, 2, 3, 4, 5);
#line 23 "tests/01__basics/003__calling_coding_style/test.code"
    test__test(1, 2, 3, 4, 5);
#line 27 "tests/01__basics/003__calling_coding_style/test.code"
    test__test(1, 2, 3, 4, 5);
#line 32 "tests/01__basics/003__calling_coding_style/test.code"
    return 0;
}

