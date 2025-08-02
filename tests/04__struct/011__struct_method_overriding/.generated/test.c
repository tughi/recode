#include "test.h"

void *malloc(uintmax_t size);

#line 5 "tests/04__struct/011__struct_method_overriding/test.code"
int32_t ptest_Number__get_value(struct test_Number *self) {
#line 6 "tests/04__struct/011__struct_method_overriding/test.code"
    return self->value;
}

#line 9 "tests/04__struct/011__struct_method_overriding/test.code"
void ptest_Number__set_value(struct test_Number *self, int32_t value) {
#line 10 "tests/04__struct/011__struct_method_overriding/test.code"
    self->value = value;
}

#line 17 "tests/04__struct/011__struct_method_overriding/test.code"
bool ptest_Boolean__get_value(struct test_Boolean *self) {
#line 18 "tests/04__struct/011__struct_method_overriding/test.code"
    return self->value;
}

#line 21 "tests/04__struct/011__struct_method_overriding/test.code"
int32_t test__main() {
#line 22 "tests/04__struct/011__struct_method_overriding/test.code"
    struct test_Number number;
#line 22 "tests/04__struct/011__struct_method_overriding/test.code"
    {
#line 22 "tests/04__struct/011__struct_method_overriding/test.code"
        int32_t __001__ = 0;
#line 22 "tests/04__struct/011__struct_method_overriding/test.code"
        number = (struct test_Number){.value = __001__};
    }
#line 24 "tests/04__struct/011__struct_method_overriding/test.code"
    {
#line 24 "tests/04__struct/011__struct_method_overriding/test.code"
        struct test_Number *__001__ = &number;
#line 24 "tests/04__struct/011__struct_method_overriding/test.code"
        int32_t __002__ = 42;
#line 24 "tests/04__struct/011__struct_method_overriding/test.code"
        ptest_Number__set_value(__001__, __002__);
    }
#line 26 "tests/04__struct/011__struct_method_overriding/test.code"
    {
#line 26 "tests/04__struct/011__struct_method_overriding/test.code"
        struct test_Number *__001__ = &number;
#line 26 "tests/04__struct/011__struct_method_overriding/test.code"
        return ptest_Number__get_value(__001__) - 42;
    }
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

