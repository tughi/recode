#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/01__basics/004__i32_literal_division/test.code"
int32_t test__main() {
#line 2 "tests/01__basics/004__i32_literal_division/test.code"
    {
#line 2 "tests/01__basics/004__i32_literal_division/test.code"
        int32_t __001__ = test__forty_two() / 42 - 1;
#line 2 "tests/01__basics/004__i32_literal_division/test.code"
        return __001__;
#line 2 "tests/01__basics/004__i32_literal_division/test.code"
    }
#line 3 "tests/01__basics/004__i32_literal_division/test.code"
}

#line 5 "tests/01__basics/004__i32_literal_division/test.code"
int32_t test__forty_two() {
#line 6 "tests/01__basics/004__i32_literal_division/test.code"
    {
#line 6 "tests/01__basics/004__i32_literal_division/test.code"
        int32_t __001__ = 42;
#line 6 "tests/01__basics/004__i32_literal_division/test.code"
        return __001__;
#line 6 "tests/01__basics/004__i32_literal_division/test.code"
    }
#line 7 "tests/01__basics/004__i32_literal_division/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

