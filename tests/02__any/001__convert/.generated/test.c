#include "test.h"

#line 1 "tests/02__any/001__convert/test.code"
int32_t test__main() {
#line 2 "tests/02__any/001__convert/test.code"
    int32_t value = 42;
#line 3 "tests/02__any/001__convert/test.code"
    void *any = ((void *) (&value));
#line 4 "tests/02__any/001__convert/test.code"
    return *((int32_t *) any) - 42;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

