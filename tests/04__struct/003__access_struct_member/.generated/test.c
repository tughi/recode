#include "test.h"

void *malloc(uintmax_t size);

#line 6 "tests/04__struct/003__access_struct_member/test.code"
int32_t test__main() {
#line 7 "tests/04__struct/003__access_struct_member/test.code"
    struct test_Point point;
#line 7 "tests/04__struct/003__access_struct_member/test.code"
    {
#line 7 "tests/04__struct/003__access_struct_member/test.code"
        int32_t __001__ = 16;
#line 7 "tests/04__struct/003__access_struct_member/test.code"
        int32_t __002__ = 32;
#line 7 "tests/04__struct/003__access_struct_member/test.code"
        point = (struct test_Point){.x = __001__, .y = __002__};
    }
#line 8 "tests/04__struct/003__access_struct_member/test.code"
    return point.x - 16;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

