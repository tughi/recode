#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

#include "test.h"

#line 5 "tests/05__extensions/002__struct_extension/test.code"
int32_t test__ptest__Number__get_value(struct test__Number *self) {
#line 6 "tests/05__extensions/002__struct_extension/test.code"
    return self->value;
}

#line 9 "tests/05__extensions/002__struct_extension/test.code"
int32_t test__main() {
#line 10 "tests/05__extensions/002__struct_extension/test.code"
    struct test__Number number = (struct test__Number){.value = 42};
#line 11 "tests/05__extensions/002__struct_extension/test.code"
    return test__ptest__Number__get_value(&number) - 42;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

