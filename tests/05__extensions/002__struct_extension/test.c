#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct Number;

struct Number {
    int32_t value;
};

int32_t pNumber__get_value(struct Number *self);

int32_t main();

#line 5 "tests/05__extensions/002__struct_extension/test.code"
int32_t pNumber__get_value(struct Number *self) {
#line 6 "tests/05__extensions/002__struct_extension/test.code"
    return self->value;
}

#line 9 "tests/05__extensions/002__struct_extension/test.code"
int32_t main() {
#line 10 "tests/05__extensions/002__struct_extension/test.code"
    struct Number number = (struct Number){.value = 42};
#line 11 "tests/05__extensions/002__struct_extension/test.code"
    return pNumber__get_value(&number) - 42;
}

