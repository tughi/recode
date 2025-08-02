#include "test.h"

#line 5 "tests/05__methods/002__struct_method/test.code"
int32_t ptest_Number__get_value(struct test_Number *self) {
#line 6 "tests/05__methods/002__struct_method/test.code"
    return self->value;
}

#line 9 "tests/05__methods/002__struct_method/test.code"
int32_t test__main() {
#line 10 "tests/05__methods/002__struct_method/test.code"
    struct test_Number number;
#line 10 "tests/05__methods/002__struct_method/test.code"
    {
#line 10 "tests/05__methods/002__struct_method/test.code"
        int32_t __001__ = 42;
#line 10 "tests/05__methods/002__struct_method/test.code"
        number = (struct test_Number){.value = __001__};
    }
#line 11 "tests/05__methods/002__struct_method/test.code"
    {
#line 11 "tests/05__methods/002__struct_method/test.code"
        struct test_Number *__001__ = &number;
#line 11 "tests/05__methods/002__struct_method/test.code"
        return ptest_Number__get_value(__001__) - 42;
    }
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

