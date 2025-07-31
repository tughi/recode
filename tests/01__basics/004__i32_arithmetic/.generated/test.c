#include "test.h"

#line 1 "tests/01__basics/004__i32_arithmetic/test.code"
int32_t test__main() {
#line 2 "tests/01__basics/004__i32_arithmetic/test.code"
    {
#line 5 "tests/01__basics/004__i32_arithmetic/test.code"
        int32_t __001__ = 42;
#line 5 "tests/01__basics/004__i32_arithmetic/test.code"
        int32_t __002__ = 10;
#line 5 "tests/01__basics/004__i32_arithmetic/test.code"
        int32_t __003__ = test__div(__001__, __002__);
#line 6 "tests/01__basics/004__i32_arithmetic/test.code"
        int32_t __004__ = 2;
#line 4 "tests/01__basics/004__i32_arithmetic/test.code"
        int32_t __005__ = test__add(__003__, __004__);
#line 9 "tests/01__basics/004__i32_arithmetic/test.code"
        int32_t __006__ = 42;
#line 9 "tests/01__basics/004__i32_arithmetic/test.code"
        int32_t __007__ = 10;
#line 9 "tests/01__basics/004__i32_arithmetic/test.code"
        int32_t __008__ = test__mod(__006__, __007__);
#line 10 "tests/01__basics/004__i32_arithmetic/test.code"
        int32_t __009__ = 5;
#line 8 "tests/01__basics/004__i32_arithmetic/test.code"
        int32_t __010__ = test__add(__008__, __009__);
#line 3 "tests/01__basics/004__i32_arithmetic/test.code"
        int32_t __011__ = test__mul(__005__, __010__);
#line 13 "tests/01__basics/004__i32_arithmetic/test.code"
        int32_t __012__ = 42;
#line 2 "tests/01__basics/004__i32_arithmetic/test.code"
        return test__sub(__011__, __012__);
    }
}

#line 17 "tests/01__basics/004__i32_arithmetic/test.code"
int32_t test__add(int32_t v1, int32_t v2) {
#line 18 "tests/01__basics/004__i32_arithmetic/test.code"
    return v1 + v2;
}

#line 21 "tests/01__basics/004__i32_arithmetic/test.code"
int32_t test__sub(int32_t v1, int32_t v2) {
#line 22 "tests/01__basics/004__i32_arithmetic/test.code"
    return v1 - v2;
}

#line 25 "tests/01__basics/004__i32_arithmetic/test.code"
int32_t test__mul(int32_t v1, int32_t v2) {
#line 26 "tests/01__basics/004__i32_arithmetic/test.code"
    return v1 * v2;
}

#line 29 "tests/01__basics/004__i32_arithmetic/test.code"
int32_t test__div(int32_t v1, int32_t v2) {
#line 30 "tests/01__basics/004__i32_arithmetic/test.code"
    return v1 / v2;
}

#line 33 "tests/01__basics/004__i32_arithmetic/test.code"
int32_t test__mod(int32_t v1, int32_t v2) {
#line 34 "tests/01__basics/004__i32_arithmetic/test.code"
    return v1 % v2;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

