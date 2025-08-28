#include "test.h"

void *malloc(uintmax_t size);

#line 5 "tests/15__struct_super/005__resolve_super_method_for_trait/test.code"
int32_t ptest_Vehicle__get_wheels(struct test_Vehicle *self) {
#line 6 "tests/15__struct_super/005__resolve_super_method_for_trait/test.code"
    {
#line 6 "tests/15__struct_super/005__resolve_super_method_for_trait/test.code"
        int32_t __001__ = self->wheels;
#line 6 "tests/15__struct_super/005__resolve_super_method_for_trait/test.code"
        return __001__;
#line 6 "tests/15__struct_super/005__resolve_super_method_for_trait/test.code"
    }
#line 7 "tests/15__struct_super/005__resolve_super_method_for_trait/test.code"
}

#line 17 "tests/15__struct_super/005__resolve_super_method_for_trait/test.code"
int32_t test__main() {
#line 18 "tests/15__struct_super/005__resolve_super_method_for_trait/test.code"
    struct test_Car *my_vehicle;
#line 18 "tests/15__struct_super/005__resolve_super_method_for_trait/test.code"
    {
#line 18 "tests/15__struct_super/005__resolve_super_method_for_trait/test.code"
        struct test_Car *__001__ = (struct test_Car *)malloc(sizeof(struct test_Car));
#line 18 "tests/15__struct_super/005__resolve_super_method_for_trait/test.code"
        *__001__ = (struct test_Car){.super = (struct test_Vehicle){.wheels = 4}};
#line 18 "tests/15__struct_super/005__resolve_super_method_for_trait/test.code"
        my_vehicle = __001__;
#line 18 "tests/15__struct_super/005__resolve_super_method_for_trait/test.code"
    }
#line 19 "tests/15__struct_super/005__resolve_super_method_for_trait/test.code"
    {
#line 19 "tests/15__struct_super/005__resolve_super_method_for_trait/test.code"
        int32_t __002__ = ptest_Vehicle__get_wheels(((struct test_Vehicle *) my_vehicle)) - 4;
#line 19 "tests/15__struct_super/005__resolve_super_method_for_trait/test.code"
        return __002__;
#line 19 "tests/15__struct_super/005__resolve_super_method_for_trait/test.code"
    }
#line 20 "tests/15__struct_super/005__resolve_super_method_for_trait/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

