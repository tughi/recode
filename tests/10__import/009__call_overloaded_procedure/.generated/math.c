#include "test.h"
#include "math.h"

void *malloc(uintmax_t size);

#line 1 "tests/10__import/009__call_overloaded_procedure/math/add.code"
int32_t math__add__left__right(int32_t left, int32_t right) {
#line 2 "tests/10__import/009__call_overloaded_procedure/math/add.code"
    {
#line 2 "tests/10__import/009__call_overloaded_procedure/math/add.code"
        int32_t __001__ = left + right;
#line 2 "tests/10__import/009__call_overloaded_procedure/math/add.code"
        return __001__;
#line 2 "tests/10__import/009__call_overloaded_procedure/math/add.code"
    }
#line 3 "tests/10__import/009__call_overloaded_procedure/math/add.code"
}

#line 5 "tests/10__import/009__call_overloaded_procedure/math/add.code"
int32_t math__add__value(int32_t value) {
#line 6 "tests/10__import/009__call_overloaded_procedure/math/add.code"
    {
#line 6 "tests/10__import/009__call_overloaded_procedure/math/add.code"
        int32_t __001__ = value + value;
#line 6 "tests/10__import/009__call_overloaded_procedure/math/add.code"
        return __001__;
#line 6 "tests/10__import/009__call_overloaded_procedure/math/add.code"
    }
#line 7 "tests/10__import/009__call_overloaded_procedure/math/add.code"
}

