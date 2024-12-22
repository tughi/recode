#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t test__main();

int32_t test__forty_two();

int32_t main(int argc, const char **argv) {
    return test__main();
}

#line 3 "tests/01__basics/004__i32_literal_division/test.code"
int32_t test__main() {
#line 4 "tests/01__basics/004__i32_literal_division/test.code"
    return test__forty_two() / 42 - 1;
}

#line 7 "tests/01__basics/004__i32_literal_division/test.code"
int32_t test__forty_two() {
#line 8 "tests/01__basics/004__i32_literal_division/test.code"
    return 42;
}

