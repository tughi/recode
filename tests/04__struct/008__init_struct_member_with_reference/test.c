#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct Number;

struct Number {
    int32_t value;
    struct Number *next;
};

int32_t test__main();

int32_t main(int argc, const char **argv) {
    return test__main();
}

#line 8 "tests/04__struct/008__init_struct_member_with_reference/test.code"
int32_t test__main() {
#line 9 "tests/04__struct/008__init_struct_member_with_reference/test.code"
    struct Number third = (struct Number){.value = 43};
#line 10 "tests/04__struct/008__init_struct_member_with_reference/test.code"
    struct Number second = (struct Number){.value = 42, .next = &third};
#line 11 "tests/04__struct/008__init_struct_member_with_reference/test.code"
    struct Number first = (struct Number){.value = 41, .next = &second};
#line 13 "tests/04__struct/008__init_struct_member_with_reference/test.code"
    int32_t second_value = first.next->value;
#line 14 "tests/04__struct/008__init_struct_member_with_reference/test.code"
    int32_t *second_value_ref = &first.next->value;
#line 16 "tests/04__struct/008__init_struct_member_with_reference/test.code"
    if (second_value != 42) {
#line 17 "tests/04__struct/008__init_struct_member_with_reference/test.code"
        return 1;
    }
#line 20 "tests/04__struct/008__init_struct_member_with_reference/test.code"
    if (*second_value_ref != 42) {
#line 21 "tests/04__struct/008__init_struct_member_with_reference/test.code"
        return 2;
    }
#line 24 "tests/04__struct/008__init_struct_member_with_reference/test.code"
    return 0;
}

