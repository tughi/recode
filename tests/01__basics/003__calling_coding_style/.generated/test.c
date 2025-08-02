#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/01__basics/003__calling_coding_style/test.code"
void test__test(int32_t one, int32_t two, int32_t three, int32_t four, int32_t five) {
}

#line 4 "tests/01__basics/003__calling_coding_style/test.code"
int32_t test__main() {
#line 5 "tests/01__basics/003__calling_coding_style/test.code"
    test__test(1, 2, 3, 4, 5);
#line 7 "tests/01__basics/003__calling_coding_style/test.code"
    test__test(1, 2, 3, 4, 5);
#line 19 "tests/01__basics/003__calling_coding_style/test.code"
    test__test(1, 2, 3, 4, 5);
#line 21 "tests/01__basics/003__calling_coding_style/test.code"
    test__test(1, 2, 3, 4, 5);
#line 25 "tests/01__basics/003__calling_coding_style/test.code"
    test__test(1, 2, 3, 4, 5);
#line 30 "tests/01__basics/003__calling_coding_style/test.code"
    return 0;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

