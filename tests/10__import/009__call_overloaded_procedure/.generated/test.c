#include "test.h"
#include "math.h"

void *malloc(uintmax_t size);

#line 3 "tests/10__import/009__call_overloaded_procedure/test.code"
int32_t test__main() {
#line 4 "tests/10__import/009__call_overloaded_procedure/test.code"
    {
#line 4 "tests/10__import/009__call_overloaded_procedure/test.code"
        int32_t __001__ = math__add__left__right(3, 7) - math__add__value(5);
#line 4 "tests/10__import/009__call_overloaded_procedure/test.code"
        return __001__;
#line 4 "tests/10__import/009__call_overloaded_procedure/test.code"
    }
#line 5 "tests/10__import/009__call_overloaded_procedure/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

