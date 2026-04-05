#include "test.h"

void *malloc(uintmax_t size);

#line 5 "tests/04__struct/011__struct_method_overriding/test.code"
int32_t ptest_Number__get_value(struct test_Number *self) {
#line 6 "tests/04__struct/011__struct_method_overriding/test.code"
    {
#line 6 "tests/04__struct/011__struct_method_overriding/test.code"
        int32_t __001__ = self->value;
#line 6 "tests/04__struct/011__struct_method_overriding/test.code"
        return __001__;
#line 6 "tests/04__struct/011__struct_method_overriding/test.code"
    }
#line 7 "tests/04__struct/011__struct_method_overriding/test.code"
}

#line 9 "tests/04__struct/011__struct_method_overriding/test.code"
void ptest_Number__set_value__anon(struct test_Number *self, int32_t value) {
#line 10 "tests/04__struct/011__struct_method_overriding/test.code"
    self->value = value;
#line 11 "tests/04__struct/011__struct_method_overriding/test.code"
}

#line 17 "tests/04__struct/011__struct_method_overriding/test.code"
bool ptest_Boolean__get_value(struct test_Boolean *self) {
#line 18 "tests/04__struct/011__struct_method_overriding/test.code"
    {
#line 18 "tests/04__struct/011__struct_method_overriding/test.code"
        bool __001__ = self->value;
#line 18 "tests/04__struct/011__struct_method_overriding/test.code"
        return __001__;
#line 18 "tests/04__struct/011__struct_method_overriding/test.code"
    }
#line 19 "tests/04__struct/011__struct_method_overriding/test.code"
}

#line 21 "tests/04__struct/011__struct_method_overriding/test.code"
int32_t test__main() {
#line 22 "tests/04__struct/011__struct_method_overriding/test.code"
    struct test_Number number = (struct test_Number){.value = 0};
#line 24 "tests/04__struct/011__struct_method_overriding/test.code"
    ptest_Number__set_value__anon(&number, 42);
#line 26 "tests/04__struct/011__struct_method_overriding/test.code"
    {
#line 26 "tests/04__struct/011__struct_method_overriding/test.code"
        int32_t __001__ = ptest_Number__get_value(&number) - 42;
#line 26 "tests/04__struct/011__struct_method_overriding/test.code"
        return __001__;
#line 26 "tests/04__struct/011__struct_method_overriding/test.code"
    }
#line 27 "tests/04__struct/011__struct_method_overriding/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

