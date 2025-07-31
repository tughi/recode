#include "test.h"

#line 5 "tests/04__struct/010__struct_methods/test.code"
int32_t ptest_Number__get_value(struct test_Number *self) {
#line 6 "tests/04__struct/010__struct_methods/test.code"
    return self->value;
}

#line 9 "tests/04__struct/010__struct_methods/test.code"
void ptest_Number__set_value(struct test_Number *self, int32_t value) {
#line 10 "tests/04__struct/010__struct_methods/test.code"
    self->value = value;
}

#line 13 "tests/04__struct/010__struct_methods/test.code"
int32_t test__main() {
#line 14 "tests/04__struct/010__struct_methods/test.code"
    struct test_Number number = (struct test_Number){.value = 0};
#line 16 "tests/04__struct/010__struct_methods/test.code"
    {
#line 16 "tests/04__struct/010__struct_methods/test.code"
        struct test_Number *__001__ = &number;
#line 16 "tests/04__struct/010__struct_methods/test.code"
        int32_t __002__ = 42;
#line 16 "tests/04__struct/010__struct_methods/test.code"
        ptest_Number__set_value(__001__, __002__);
    }
#line 18 "tests/04__struct/010__struct_methods/test.code"
    {
#line 18 "tests/04__struct/010__struct_methods/test.code"
        struct test_Number *__001__ = &number;
#line 18 "tests/04__struct/010__struct_methods/test.code"
        return ptest_Number__get_value(__001__) - 42;
    }
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

