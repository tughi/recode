#include "test.h"

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
    struct test_Number number = (struct test_Number){.value = 42};
#line 15 "tests/05__methods/003__i32_method/test.code"
    return ptest_Number__get_value(&number) - i32__get_value(42);
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

