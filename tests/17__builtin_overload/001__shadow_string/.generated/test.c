#include "test.h"

void *malloc(uintmax_t size);

#line 5 "tests/17__builtin_overload/001__shadow_string/test.code"
int32_t test__main() {
#line 6 "tests/17__builtin_overload/001__shadow_string/test.code"
    struct test_String s = (struct test_String){.value = 42};
#line 7 "tests/17__builtin_overload/001__shadow_string/test.code"
    {
#line 7 "tests/17__builtin_overload/001__shadow_string/test.code"
        int32_t __001__ = s.value - 42;
#line 7 "tests/17__builtin_overload/001__shadow_string/test.code"
        return __001__;
#line 7 "tests/17__builtin_overload/001__shadow_string/test.code"
    }
#line 8 "tests/17__builtin_overload/001__shadow_string/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

