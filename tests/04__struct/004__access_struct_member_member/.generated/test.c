#include "test.h"

#line 11 "tests/04__struct/004__access_struct_member_member/test.code"
int32_t test__main() {
#line 12 "tests/04__struct/004__access_struct_member_member/test.code"
    struct test_Line line;
#line 12 "tests/04__struct/004__access_struct_member_member/test.code"
    {
#line 13 "tests/04__struct/004__access_struct_member_member/test.code"
        int32_t __001__ = 16;
#line 13 "tests/04__struct/004__access_struct_member_member/test.code"
        int32_t __002__ = 32;
#line 13 "tests/04__struct/004__access_struct_member_member/test.code"
        struct test_Point __003__ = (struct test_Point){.x = __001__, .y = __002__};
#line 14 "tests/04__struct/004__access_struct_member_member/test.code"
        int32_t __004__ = 48;
#line 14 "tests/04__struct/004__access_struct_member_member/test.code"
        int32_t __005__ = 64;
#line 14 "tests/04__struct/004__access_struct_member_member/test.code"
        struct test_Point __006__ = (struct test_Point){.x = __004__, .y = __005__};
#line 12 "tests/04__struct/004__access_struct_member_member/test.code"
        line = (struct test_Line){.p1 = __003__, .p2 = __006__};
    }
#line 16 "tests/04__struct/004__access_struct_member_member/test.code"
    return line.p2.y - 64;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

