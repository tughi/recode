#include "test.h"

#line 7 "tests/11__generics/003__struct_init/test.code"
int32_t test__main() {
#line 8 "tests/11__generics/003__struct_init/test.code"
    struct test_Array__i32 array;
#line 8 "tests/11__generics/003__struct_init/test.code"
    {
#line 9 "tests/11__generics/003__struct_init/test.code"
        int32_t *__001__ = NULL;
#line 10 "tests/11__generics/003__struct_init/test.code"
        uintmax_t __002__ = 0;
#line 11 "tests/11__generics/003__struct_init/test.code"
        uintmax_t __003__ = 0;
#line 8 "tests/11__generics/003__struct_init/test.code"
        array = (struct test_Array__i32){.items = __001__, .length = __002__, .capacity = __003__};
    }
#line 13 "tests/11__generics/003__struct_init/test.code"
    return ((int32_t) array.length);
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

