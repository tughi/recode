#include "test.h"

void *malloc(uintmax_t size);

#line 5 "tests/17__builtin_overload/002__builtin_qualified/test.code"
int32_t test__main() {
#line 6 "tests/17__builtin_overload/002__builtin_qualified/test.code"
    struct test_i32 wrapped = (struct test_i32){.value = 0};
#line 7 "tests/17__builtin_overload/002__builtin_qualified/test.code"
    {
#line 7 "tests/17__builtin_overload/002__builtin_qualified/test.code"
        int32_t __001__ = wrapped.value;
#line 7 "tests/17__builtin_overload/002__builtin_qualified/test.code"
        return __001__;
#line 7 "tests/17__builtin_overload/002__builtin_qualified/test.code"
    }
#line 8 "tests/17__builtin_overload/002__builtin_qualified/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

