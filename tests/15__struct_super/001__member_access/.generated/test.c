#include "test.h"

void *malloc(uintmax_t size);

#line 13 "tests/15__struct_super/001__member_access/test.code"
int32_t test__main() {
#line 14 "tests/15__struct_super/001__member_access/test.code"
    struct test_Sports_Car my_car = (struct test_Sports_Car){.super = (struct test_Car){.super = (struct test_Vehicle){.wheels = 4}}};
#line 15 "tests/15__struct_super/001__member_access/test.code"
    {
#line 15 "tests/15__struct_super/001__member_access/test.code"
        int32_t __001__ = my_car.super.super.wheels - 4;
#line 15 "tests/15__struct_super/001__member_access/test.code"
        return __001__;
#line 15 "tests/15__struct_super/001__member_access/test.code"
    }
#line 16 "tests/15__struct_super/001__member_access/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

