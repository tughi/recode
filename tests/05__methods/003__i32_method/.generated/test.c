#include "test.h"

void *malloc(uintmax_t size);

#line 5 "tests/05__methods/003__i32_method/test.code"
int32_t ptest_Number__get_value(struct test_Number *self) {
#line 6 "tests/05__methods/003__i32_method/test.code"
    return self->value;
}

#line 9 "tests/05__methods/003__i32_method/test.code"
int32_t i32__get_value(int32_t self) {
#line 10 "tests/05__methods/003__i32_method/test.code"
    return self;
}

#line 13 "tests/05__methods/003__i32_method/test.code"
int32_t test__main() {
#line 14 "tests/05__methods/003__i32_method/test.code"
    struct test_Number number;
#line 14 "tests/05__methods/003__i32_method/test.code"
    {
#line 14 "tests/05__methods/003__i32_method/test.code"
        int32_t __001__ = 42;
#line 14 "tests/05__methods/003__i32_method/test.code"
        number = (struct test_Number){.value = __001__};
    }
#line 15 "tests/05__methods/003__i32_method/test.code"
    {
#line 15 "tests/05__methods/003__i32_method/test.code"
        struct test_Number *__001__ = &number;
#line 15 "tests/05__methods/003__i32_method/test.code"
        int32_t __002__ = 42;
#line 15 "tests/05__methods/003__i32_method/test.code"
        return ptest_Number__get_value(__001__) - i32__get_value(__002__);
    }
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

