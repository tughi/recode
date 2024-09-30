#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct Number;

struct Number {
    int32_t value;
    struct Number *next;
};

int32_t main();

#line 6 "tests/04__struct/008__init_struct_member_with_reference/test.code"
int32_t main() {
#line 7 "tests/04__struct/008__init_struct_member_with_reference/test.code"
    struct Number third = (struct Number){.value = 43};
#line 8 "tests/04__struct/008__init_struct_member_with_reference/test.code"
    struct Number second = (struct Number){.value = 42, .next = &third};
#line 9 "tests/04__struct/008__init_struct_member_with_reference/test.code"
    struct Number first = (struct Number){.value = 41, .next = &second};
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

