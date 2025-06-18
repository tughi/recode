#include "test.h"

#line 7 "tests/11__generics/003__struct_init/test.code"
int32_t test__main() {
#line 8 "tests/11__generics/003__struct_init/test.code"
    struct test_Array__i32 array = (struct test_Array__i32){.items = NULL, .length = 0, .capacity = 0};
#line 13 "tests/11__generics/003__struct_init/test.code"
    return ((int32_t) array.length);
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

