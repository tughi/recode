#include "test.h"

#line 6 "tests/04__struct/008__init_struct_member_with_reference/test.code"
int32_t test__main() {
#line 7 "tests/04__struct/008__init_struct_member_with_reference/test.code"
    struct test_Number third;
#line 7 "tests/04__struct/008__init_struct_member_with_reference/test.code"
    {
#line 7 "tests/04__struct/008__init_struct_member_with_reference/test.code"
        int32_t __001__ = 43;
#line 7 "tests/04__struct/008__init_struct_member_with_reference/test.code"
        third = (struct test_Number){.value = __001__};
    }
#line 8 "tests/04__struct/008__init_struct_member_with_reference/test.code"
    struct test_Number second;
#line 8 "tests/04__struct/008__init_struct_member_with_reference/test.code"
    {
#line 8 "tests/04__struct/008__init_struct_member_with_reference/test.code"
        int32_t __001__ = 42;
#line 8 "tests/04__struct/008__init_struct_member_with_reference/test.code"
        struct test_Number *__002__ = &third;
#line 8 "tests/04__struct/008__init_struct_member_with_reference/test.code"
        second = (struct test_Number){.value = __001__, .next = __002__};
    }
#line 9 "tests/04__struct/008__init_struct_member_with_reference/test.code"
    struct test_Number first;
#line 9 "tests/04__struct/008__init_struct_member_with_reference/test.code"
    {
#line 9 "tests/04__struct/008__init_struct_member_with_reference/test.code"
        int32_t __001__ = 41;
#line 9 "tests/04__struct/008__init_struct_member_with_reference/test.code"
        struct test_Number *__002__ = &second;
#line 9 "tests/04__struct/008__init_struct_member_with_reference/test.code"
        first = (struct test_Number){.value = __001__, .next = __002__};
    }
#line 11 "tests/04__struct/008__init_struct_member_with_reference/test.code"
    int32_t second_value = first.next->value;
#line 12 "tests/04__struct/008__init_struct_member_with_reference/test.code"
    int32_t *second_value_ref = &first.next->value;
#line 14 "tests/04__struct/008__init_struct_member_with_reference/test.code"
    if (second_value != 42) {
#line 15 "tests/04__struct/008__init_struct_member_with_reference/test.code"
        return 1;
    }
#line 18 "tests/04__struct/008__init_struct_member_with_reference/test.code"
    if (*second_value_ref != 42) {
#line 19 "tests/04__struct/008__init_struct_member_with_reference/test.code"
        return 2;
    }
#line 22 "tests/04__struct/008__init_struct_member_with_reference/test.code"
    return 0;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

