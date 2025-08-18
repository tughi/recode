#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/03__multi_pointer/001__local_variable/test.code"
int32_t test__main() {
#line 2 "tests/03__multi_pointer/001__local_variable/test.code"
    int32_t *array;
#line 3 "tests/03__multi_pointer/001__local_variable/test.code"
    {
#line 3 "tests/03__multi_pointer/001__local_variable/test.code"
        int32_t __001__ = 0;
#line 3 "tests/03__multi_pointer/001__local_variable/test.code"
        return __001__;
#line 3 "tests/03__multi_pointer/001__local_variable/test.code"
    }
#line 4 "tests/03__multi_pointer/001__local_variable/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

