#include "test.h"

void *malloc(uintmax_t size);

#line 6 "tests/04__struct/001__local_struct_variable/test.code"
int32_t test__main() {
#line 7 "tests/04__struct/001__local_struct_variable/test.code"
    struct test_Point point;
#line 8 "tests/04__struct/001__local_struct_variable/test.code"
    return 0;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

