#include "test.h"

void *malloc(uintmax_t size);

#line 7 "tests/11__generics/003__struct_init/test.code"
int32_t test__main() {
#line 8 "tests/11__generics/003__struct_init/test.code"
    struct test_Array__i32 array = (struct test_Array__i32){.items = NULL, .length = 0u, .capacity = 0u};
#line 13 "tests/11__generics/003__struct_init/test.code"
    return ((int32_t) array.length);
#line 14 "tests/11__generics/003__struct_init/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

