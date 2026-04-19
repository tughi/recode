#include "test.h"

void *malloc(uintmax_t size);

#line 6 "tests/16__optional/004__struct_field/test.code"
int32_t test__main() {
#line 7 "tests/16__optional/004__struct_field/test.code"
    struct test_Person p = (struct test_Person){.name = (struct String){.data = "Alice", .length = 5}, .age = (struct i32__opt){.variant = 1, .variant_1 = 30}};
#line 8 "tests/16__optional/004__struct_field/test.code"
    struct test_Person q = (struct test_Person){.name = (struct String){.data = "Bob", .length = 3}, .age = (struct i32__opt){.variant = 0}};
#line 10 "tests/16__optional/004__struct_field/test.code"
    struct i32__opt p_age = p.age;
#line 11 "tests/16__optional/004__struct_field/test.code"
    if (p_age.variant == 1) {
#line 12 "tests/16__optional/004__struct_field/test.code"
        if (p_age.variant_1 != 30) {
#line 13 "tests/16__optional/004__struct_field/test.code"
            {
#line 13 "tests/16__optional/004__struct_field/test.code"
                int32_t __001__ = 1;
#line 13 "tests/16__optional/004__struct_field/test.code"
                return __001__;
#line 13 "tests/16__optional/004__struct_field/test.code"
            }
#line 14 "tests/16__optional/004__struct_field/test.code"
        }
#line 15 "tests/16__optional/004__struct_field/test.code"
    } else {
#line 16 "tests/16__optional/004__struct_field/test.code"
        {
#line 16 "tests/16__optional/004__struct_field/test.code"
            int32_t __002__ = 2;
#line 16 "tests/16__optional/004__struct_field/test.code"
            return __002__;
#line 16 "tests/16__optional/004__struct_field/test.code"
        }
#line 17 "tests/16__optional/004__struct_field/test.code"
    }
#line 19 "tests/16__optional/004__struct_field/test.code"
    struct i32__opt q_age = q.age;
#line 20 "tests/16__optional/004__struct_field/test.code"
    if (q_age.variant == 0) {
#line 21 "tests/16__optional/004__struct_field/test.code"
    } else {
#line 22 "tests/16__optional/004__struct_field/test.code"
        {
#line 22 "tests/16__optional/004__struct_field/test.code"
            int32_t __003__ = 3;
#line 22 "tests/16__optional/004__struct_field/test.code"
            return __003__;
#line 22 "tests/16__optional/004__struct_field/test.code"
        }
#line 23 "tests/16__optional/004__struct_field/test.code"
    }
#line 25 "tests/16__optional/004__struct_field/test.code"
    {
#line 25 "tests/16__optional/004__struct_field/test.code"
        int32_t __004__ = 0;
#line 25 "tests/16__optional/004__struct_field/test.code"
        return __004__;
#line 25 "tests/16__optional/004__struct_field/test.code"
    }
#line 26 "tests/16__optional/004__struct_field/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

