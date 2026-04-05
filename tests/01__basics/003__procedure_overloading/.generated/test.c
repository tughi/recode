#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/01__basics/003__procedure_overloading/test.code"
int32_t test__main() {
#line 2 "tests/01__basics/003__procedure_overloading/test.code"
    {
#line 2 "tests/01__basics/003__procedure_overloading/test.code"
        int32_t __001__ = test__fallback() - test__fallback__value(42);
#line 2 "tests/01__basics/003__procedure_overloading/test.code"
        return __001__;
#line 2 "tests/01__basics/003__procedure_overloading/test.code"
    }
#line 3 "tests/01__basics/003__procedure_overloading/test.code"
}

#line 5 "tests/01__basics/003__procedure_overloading/test.code"
int32_t test__fallback() {
#line 6 "tests/01__basics/003__procedure_overloading/test.code"
    {
#line 6 "tests/01__basics/003__procedure_overloading/test.code"
        int32_t __001__ = 42;
#line 6 "tests/01__basics/003__procedure_overloading/test.code"
        return __001__;
#line 6 "tests/01__basics/003__procedure_overloading/test.code"
    }
#line 7 "tests/01__basics/003__procedure_overloading/test.code"
}

#line 9 "tests/01__basics/003__procedure_overloading/test.code"
int32_t test__fallback__value(int32_t value) {
#line 10 "tests/01__basics/003__procedure_overloading/test.code"
    {
#line 10 "tests/01__basics/003__procedure_overloading/test.code"
        int32_t __001__ = value;
#line 10 "tests/01__basics/003__procedure_overloading/test.code"
        return __001__;
#line 10 "tests/01__basics/003__procedure_overloading/test.code"
    }
#line 11 "tests/01__basics/003__procedure_overloading/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

