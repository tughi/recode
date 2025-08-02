#include "test.h"
#include "source.h"

#line 3 "tests/10__import/003__init_struct_variable/test.code"
int32_t test__main() {
#line 4 "tests/10__import/003__init_struct_variable/test.code"
    struct source_Span span;
#line 4 "tests/10__import/003__init_struct_variable/test.code"
    {
#line 4 "tests/10__import/003__init_struct_variable/test.code"
        int32_t __001__ = 0;
#line 4 "tests/10__import/003__init_struct_variable/test.code"
        int32_t __002__ = 42;
#line 4 "tests/10__import/003__init_struct_variable/test.code"
        span = (struct source_Span){.start = __001__, .end = __002__};
    }
#line 5 "tests/10__import/003__init_struct_variable/test.code"
    return span.end - 42;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

