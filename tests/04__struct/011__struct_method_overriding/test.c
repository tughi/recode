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

int32_t pNumber__get_value(struct Number *self);

void pNumber__set_value(struct Number *self, int32_t value);

bool pBoolean__get_value(struct Boolean *self);

int32_t main();

#line 4 "tests/04__struct/011__struct_method_overriding/test.code"
int32_t pNumber__get_value(struct Number *self) {
#line 5 "tests/04__struct/011__struct_method_overriding/test.code"
    return self->value;
}

#line 8 "tests/04__struct/011__struct_method_overriding/test.code"
void pNumber__set_value(struct Number *self, int32_t value) {
#line 9 "tests/04__struct/011__struct_method_overriding/test.code"
    self->value = value;
}

#line 16 "tests/04__struct/011__struct_method_overriding/test.code"
bool pBoolean__get_value(struct Boolean *self) {
#line 17 "tests/04__struct/011__struct_method_overriding/test.code"
    return self->value;
}

#line 21 "tests/04__struct/011__struct_method_overriding/test.code"
int32_t main() {
#line 22 "tests/04__struct/011__struct_method_overriding/test.code"
    struct Number number = (struct Number){.value = 0};
#line 24 "tests/04__struct/011__struct_method_overriding/test.code"
    pNumber__set_value(&number, 42);
#line 26 "tests/04__struct/011__struct_method_overriding/test.code"
    return pNumber__get_value(&number) - 42;
}

