#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

#include "test.h"

#line 5 "tests/04__struct/011__struct_method_overriding/test.code"
int32_t test__ptest__Number__get_value(struct test__Number *self) {
#line 6 "tests/04__struct/011__struct_method_overriding/test.code"
    return self->value;
}

#line 9 "tests/04__struct/011__struct_method_overriding/test.code"
void test__ptest__Number__set_value(struct test__Number *self, int32_t value) {
#line 10 "tests/04__struct/011__struct_method_overriding/test.code"
    self->value = value;
}

#line 17 "tests/04__struct/011__struct_method_overriding/test.code"
bool test__ptest__Boolean__get_value(struct test__Boolean *self) {
#line 18 "tests/04__struct/011__struct_method_overriding/test.code"
    return self->value;
}

#line 21 "tests/04__struct/011__struct_method_overriding/test.code"
int32_t test__main() {
#line 22 "tests/04__struct/011__struct_method_overriding/test.code"
    struct test__Number number = (struct test__Number){.value = 0};
#line 24 "tests/04__struct/011__struct_method_overriding/test.code"
    test__ptest__Number__set_value(&number, 42);
#line 26 "tests/04__struct/011__struct_method_overriding/test.code"
    return test__ptest__Number__get_value(&number) - 42;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

