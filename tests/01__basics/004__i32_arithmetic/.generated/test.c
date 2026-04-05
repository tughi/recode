#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/01__basics/004__i32_arithmetic/test.code"
int32_t test__main() {
#line 2 "tests/01__basics/004__i32_arithmetic/test.code"
    {
#line 2 "tests/01__basics/004__i32_arithmetic/test.code"
        int32_t __001__ = test__sub__anon__anon(test__mul__anon__anon(test__add__anon__anon(test__div__anon__anon(42, 10), 2), test__add__anon__anon(test__mod__anon__anon(42, 10), 5)), 42);
#line 2 "tests/01__basics/004__i32_arithmetic/test.code"
        return __001__;
#line 14 "tests/01__basics/004__i32_arithmetic/test.code"
    }
#line 15 "tests/01__basics/004__i32_arithmetic/test.code"
}

#line 17 "tests/01__basics/004__i32_arithmetic/test.code"
int32_t test__add__anon__anon(int32_t v1, int32_t v2) {
#line 18 "tests/01__basics/004__i32_arithmetic/test.code"
    {
#line 18 "tests/01__basics/004__i32_arithmetic/test.code"
        int32_t __001__ = v1 + v2;
#line 18 "tests/01__basics/004__i32_arithmetic/test.code"
        return __001__;
#line 18 "tests/01__basics/004__i32_arithmetic/test.code"
    }
#line 19 "tests/01__basics/004__i32_arithmetic/test.code"
}

#line 21 "tests/01__basics/004__i32_arithmetic/test.code"
int32_t test__sub__anon__anon(int32_t v1, int32_t v2) {
#line 22 "tests/01__basics/004__i32_arithmetic/test.code"
    {
#line 22 "tests/01__basics/004__i32_arithmetic/test.code"
        int32_t __001__ = v1 - v2;
#line 22 "tests/01__basics/004__i32_arithmetic/test.code"
        return __001__;
#line 22 "tests/01__basics/004__i32_arithmetic/test.code"
    }
#line 23 "tests/01__basics/004__i32_arithmetic/test.code"
}

#line 25 "tests/01__basics/004__i32_arithmetic/test.code"
int32_t test__mul__anon__anon(int32_t v1, int32_t v2) {
#line 26 "tests/01__basics/004__i32_arithmetic/test.code"
    {
#line 26 "tests/01__basics/004__i32_arithmetic/test.code"
        int32_t __001__ = v1 * v2;
#line 26 "tests/01__basics/004__i32_arithmetic/test.code"
        return __001__;
#line 26 "tests/01__basics/004__i32_arithmetic/test.code"
    }
#line 27 "tests/01__basics/004__i32_arithmetic/test.code"
}

#line 29 "tests/01__basics/004__i32_arithmetic/test.code"
int32_t test__div__anon__anon(int32_t v1, int32_t v2) {
#line 30 "tests/01__basics/004__i32_arithmetic/test.code"
    {
#line 30 "tests/01__basics/004__i32_arithmetic/test.code"
        int32_t __001__ = v1 / v2;
#line 30 "tests/01__basics/004__i32_arithmetic/test.code"
        return __001__;
#line 30 "tests/01__basics/004__i32_arithmetic/test.code"
    }
#line 31 "tests/01__basics/004__i32_arithmetic/test.code"
}

#line 33 "tests/01__basics/004__i32_arithmetic/test.code"
int32_t test__mod__anon__anon(int32_t v1, int32_t v2) {
#line 34 "tests/01__basics/004__i32_arithmetic/test.code"
    {
#line 34 "tests/01__basics/004__i32_arithmetic/test.code"
        int32_t __001__ = v1 % v2;
#line 34 "tests/01__basics/004__i32_arithmetic/test.code"
        return __001__;
#line 34 "tests/01__basics/004__i32_arithmetic/test.code"
    }
#line 35 "tests/01__basics/004__i32_arithmetic/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

