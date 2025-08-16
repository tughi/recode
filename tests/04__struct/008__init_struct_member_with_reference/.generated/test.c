#include "test.h"

void *malloc(uintmax_t size);

#line 6 "tests/04__struct/008__init_struct_member_with_reference/test.code"
int32_t test__main() {
#line 7 "tests/04__struct/008__init_struct_member_with_reference/test.code"
    struct test_Number third = (struct test_Number){.value = 43};
#line 8 "tests/04__struct/008__init_struct_member_with_reference/test.code"
    struct test_Number second = (struct test_Number){.value = 42, .next = &third};
#line 9 "tests/04__struct/008__init_struct_member_with_reference/test.code"
    struct test_Number first = (struct test_Number){.value = 41, .next = &second};
#line 11 "tests/04__struct/008__init_struct_member_with_reference/test.code"
    int32_t second_value = first.next->value;
#line 12 "tests/04__struct/008__init_struct_member_with_reference/test.code"
    int32_t *second_value_ref = &first.next->value;
#line 14 "tests/04__struct/008__init_struct_member_with_reference/test.code"
    if (second_value != 42) {
#line 15 "tests/04__struct/008__init_struct_member_with_reference/test.code"
        {
#line 15 "tests/04__struct/008__init_struct_member_with_reference/test.code"
            int32_t __001__ = 1;
#line 15 "tests/04__struct/008__init_struct_member_with_reference/test.code"
            return __001__;
#line 15 "tests/04__struct/008__init_struct_member_with_reference/test.code"
        }
#line 16 "tests/04__struct/008__init_struct_member_with_reference/test.code"
    }
#line 18 "tests/04__struct/008__init_struct_member_with_reference/test.code"
    if (*second_value_ref != 42) {
#line 19 "tests/04__struct/008__init_struct_member_with_reference/test.code"
        {
#line 19 "tests/04__struct/008__init_struct_member_with_reference/test.code"
            int32_t __002__ = 2;
#line 19 "tests/04__struct/008__init_struct_member_with_reference/test.code"
            return __002__;
#line 19 "tests/04__struct/008__init_struct_member_with_reference/test.code"
        }
#line 20 "tests/04__struct/008__init_struct_member_with_reference/test.code"
    }
#line 22 "tests/04__struct/008__init_struct_member_with_reference/test.code"
    {
#line 22 "tests/04__struct/008__init_struct_member_with_reference/test.code"
        int32_t __003__ = 0;
#line 22 "tests/04__struct/008__init_struct_member_with_reference/test.code"
        return __003__;
#line 22 "tests/04__struct/008__init_struct_member_with_reference/test.code"
    }
#line 23 "tests/04__struct/008__init_struct_member_with_reference/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

