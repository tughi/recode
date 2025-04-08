#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct Number;

struct Boolean;

struct Number {
    int32_t value;
};

struct Boolean {
    bool value;
};

int32_t test__pNumber__get_value(struct Number *self);

void test__pNumber__set_value(struct Number *self, int32_t value);

bool test__pBoolean__get_value(struct Boolean *self);

int32_t test__main();

int32_t main(int argc, const char **argv) {
    return test__main();
}

#line 5 "tests/04__struct/011__struct_method_overriding/test.code"
int32_t test__pNumber__get_value(struct Number *self) {
#line 6 "tests/04__struct/011__struct_method_overriding/test.code"
    return self->value;
}

#line 9 "tests/04__struct/011__struct_method_overriding/test.code"
void test__pNumber__set_value(struct Number *self, int32_t value) {
#line 10 "tests/04__struct/011__struct_method_overriding/test.code"
    self->value = value;
}

#line 17 "tests/04__struct/011__struct_method_overriding/test.code"
bool test__pBoolean__get_value(struct Boolean *self) {
#line 18 "tests/04__struct/011__struct_method_overriding/test.code"
    return self->value;
}

#line 21 "tests/04__struct/011__struct_method_overriding/test.code"
int32_t test__main() {
#line 22 "tests/04__struct/011__struct_method_overriding/test.code"
    struct Number number = (struct Number){.value = 0};
#line 24 "tests/04__struct/011__struct_method_overriding/test.code"
    test__pNumber__set_value(&number, 42);
#line 26 "tests/04__struct/011__struct_method_overriding/test.code"
    return test__pNumber__get_value(&number) - 42;
}

