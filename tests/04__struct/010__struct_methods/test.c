#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct Number;

struct Number {
    int32_t value;
};

int32_t test__pNumber__get_value(struct Number *self);

void test__pNumber__set_value(struct Number *self, int32_t value);

int32_t test__main();

int32_t main(int argc, const char **argv) {
    return test__main();
}

#line 7 "tests/04__struct/010__struct_methods/test.code"
int32_t test__pNumber__get_value(struct Number *self) {
#line 8 "tests/04__struct/010__struct_methods/test.code"
    return self->value;
}

#line 11 "tests/04__struct/010__struct_methods/test.code"
void test__pNumber__set_value(struct Number *self, int32_t value) {
#line 12 "tests/04__struct/010__struct_methods/test.code"
    self->value = value;
}

#line 15 "tests/04__struct/010__struct_methods/test.code"
int32_t test__main() {
#line 16 "tests/04__struct/010__struct_methods/test.code"
    struct Number number = (struct Number){.value = 0};
#line 18 "tests/04__struct/010__struct_methods/test.code"
    test__pNumber__set_value(&number, 42);
#line 20 "tests/04__struct/010__struct_methods/test.code"
    return test__pNumber__get_value(&number) - 42;
}

