#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t test__main();

int32_t main(int argc, const char **argv) {
    return test__main();
}

#line 3 "tests/02__any/001__convert/test.code"
int32_t test__main() {
#line 4 "tests/02__any/001__convert/test.code"
    int32_t value = 42;
#line 5 "tests/02__any/001__convert/test.code"
    void *any = ((void *) (&value));
#line 6 "tests/02__any/001__convert/test.code"
    return *((int32_t *) any) - 42;
}

