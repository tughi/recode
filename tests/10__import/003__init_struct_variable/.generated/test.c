#include "test.h"
#include "source.h"

void *malloc(uintmax_t size);

#line 3 "tests/10__import/003__init_struct_variable/test.code"
int32_t test__main() {
#line 4 "tests/10__import/003__init_struct_variable/test.code"
    struct source_Span span = (struct source_Span){.start = 0, .end = 42};
#line 5 "tests/10__import/003__init_struct_variable/test.code"
    {
#line 5 "tests/10__import/003__init_struct_variable/test.code"
        int32_t __001__ = span.end - 42;
#line 5 "tests/10__import/003__init_struct_variable/test.code"
        return __001__;
#line 5 "tests/10__import/003__init_struct_variable/test.code"
    }
#line 6 "tests/10__import/003__init_struct_variable/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

