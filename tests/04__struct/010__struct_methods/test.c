#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct Number;

struct Number {
    int32_t value;
};

int32_t pNumber__get_value(struct Number *self);

void pNumber__set_value(struct Number *self, int32_t value);

int32_t main();

#line 4 "tests/04__struct/010__struct_methods/test.code"
int32_t pNumber__get_value(struct Number *self) {
#line 5 "tests/04__struct/010__struct_methods/test.code"
    return self->value;
}

#line 8 "tests/04__struct/010__struct_methods/test.code"
void pNumber__set_value(struct Number *self, int32_t value) {
#line 9 "tests/04__struct/010__struct_methods/test.code"
    self->value = value;
}

#line 13 "tests/04__struct/010__struct_methods/test.code"
int32_t main() {
#line 14 "tests/04__struct/010__struct_methods/test.code"
    struct Number number = (struct Number){.value = 0};
#line 16 "tests/04__struct/010__struct_methods/test.code"
    pNumber__set_value(&number, 42);
#line 18 "tests/04__struct/010__struct_methods/test.code"
    return pNumber__get_value(&number) - 42;
}

