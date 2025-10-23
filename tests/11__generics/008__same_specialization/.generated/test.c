#include "test.h"
#include "foo.h"
#include "bar.h"
#include "collections.h"
#include "tokens.h"

void *malloc(uintmax_t size);

#line 4 "tests/11__generics/008__same_specialization/test.code"
int32_t test__main() {
#line 5 "tests/11__generics/008__same_specialization/test.code"
    struct foo_Foo_Demo foo_demo;
#line 6 "tests/11__generics/008__same_specialization/test.code"
    struct bar_Bar_Demo bar_demo;
#line 7 "tests/11__generics/008__same_specialization/test.code"
    {
#line 7 "tests/11__generics/008__same_specialization/test.code"
        int32_t __001__ = 0;
#line 7 "tests/11__generics/008__same_specialization/test.code"
        return __001__;
#line 7 "tests/11__generics/008__same_specialization/test.code"
    }
#line 8 "tests/11__generics/008__same_specialization/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

