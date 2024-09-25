#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t main();

int32_t forty_two();

#line 1 "tests/01__basics/004__i32_literal_division/test.code"
int32_t main() {
#line 2 "tests/01__basics/004__i32_literal_division/test.code"
    return forty_two() / 42 - 1;
}

#line 5 "tests/01__basics/004__i32_literal_division/test.code"
int32_t forty_two() {
#line 6 "tests/01__basics/004__i32_literal_division/test.code"
    return 42;
}

