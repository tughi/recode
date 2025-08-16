#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/01__basics/005__declare_local_variables/test.code"
int32_t test__main() {
#line 2 "tests/01__basics/005__declare_local_variables/test.code"
    int32_t value = 42;
#line 3 "tests/01__basics/005__declare_local_variables/test.code"
    {
#line 3 "tests/01__basics/005__declare_local_variables/test.code"
        int32_t __001__ = 0;
#line 3 "tests/01__basics/005__declare_local_variables/test.code"
        return __001__;
#line 3 "tests/01__basics/005__declare_local_variables/test.code"
    }
#line 4 "tests/01__basics/005__declare_local_variables/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

