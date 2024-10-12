#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct Number;

struct Number {
    int32_t value;
};

int32_t pNumber__get_value(struct Number *self);

int32_t i32__get_value(int32_t self);

int32_t main();

#line 5 "tests/05__extensions/003__i32_extension/test.code"
int32_t pNumber__get_value(struct Number *self) {
#line 6 "tests/05__extensions/003__i32_extension/test.code"
    return self->value;
}

#line 9 "tests/05__extensions/003__i32_extension/test.code"
int32_t i32__get_value(int32_t self) {
#line 10 "tests/05__extensions/003__i32_extension/test.code"
    return self;
}

#line 13 "tests/05__extensions/003__i32_extension/test.code"
int32_t main() {
#line 14 "tests/05__extensions/003__i32_extension/test.code"
    struct Number number = (struct Number){.value = 42};
#line 15 "tests/05__extensions/003__i32_extension/test.code"
    return pNumber__get_value(&number) - i32__get_value(42);
}

