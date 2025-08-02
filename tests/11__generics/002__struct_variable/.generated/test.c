#include "test.h"

void *malloc(uintmax_t size);

#line 7 "tests/11__generics/002__struct_variable/test.code"
int32_t test__main() {
#line 8 "tests/11__generics/002__struct_variable/test.code"
    struct test_Array__i32 array_of_i32;
#line 9 "tests/11__generics/002__struct_variable/test.code"
    struct test_Array__i64 array_of_i64;
#line 10 "tests/11__generics/002__struct_variable/test.code"
    return 0;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

