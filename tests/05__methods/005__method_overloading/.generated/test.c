#include "test.h"

void *malloc(uintmax_t size);

#line 5 "tests/05__methods/005__method_overloading/test.code"
void ptest_Counter__add(struct test_Counter *self) {
#line 6 "tests/05__methods/005__method_overloading/test.code"
    self->value = self->value + 1;
#line 7 "tests/05__methods/005__method_overloading/test.code"
}

#line 9 "tests/05__methods/005__method_overloading/test.code"
void ptest_Counter__add__amount(struct test_Counter *self, int32_t amount) {
#line 10 "tests/05__methods/005__method_overloading/test.code"
    self->value = self->value + amount;
#line 11 "tests/05__methods/005__method_overloading/test.code"
}

#line 13 "tests/05__methods/005__method_overloading/test.code"
int32_t test__main() {
#line 14 "tests/05__methods/005__method_overloading/test.code"
    struct test_Counter counter = (struct test_Counter){.value = 0};
#line 15 "tests/05__methods/005__method_overloading/test.code"
    ptest_Counter__add(&counter);
#line 16 "tests/05__methods/005__method_overloading/test.code"
    ptest_Counter__add__amount(&counter, 4);
#line 17 "tests/05__methods/005__method_overloading/test.code"
    {
#line 17 "tests/05__methods/005__method_overloading/test.code"
        int32_t __001__ = counter.value - 5;
#line 17 "tests/05__methods/005__method_overloading/test.code"
        return __001__;
#line 17 "tests/05__methods/005__method_overloading/test.code"
    }
#line 18 "tests/05__methods/005__method_overloading/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

