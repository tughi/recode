#include "test.h"

void *malloc(uintmax_t size);

#line 7 "tests/09__variant/010__make_variant_from_typed_null/test.code"
int32_t test__main() {
#line 8 "tests/09__variant/010__make_variant_from_typed_null/test.code"
    struct test_Value vale = (struct test_Value){.variant = 2, .variant_2 = ((int32_t *) NULL)};
#line 9 "tests/09__variant/010__make_variant_from_typed_null/test.code"
    {
#line 9 "tests/09__variant/010__make_variant_from_typed_null/test.code"
        int32_t __001__ = 0;
#line 9 "tests/09__variant/010__make_variant_from_typed_null/test.code"
        return __001__;
#line 9 "tests/09__variant/010__make_variant_from_typed_null/test.code"
    }
#line 10 "tests/09__variant/010__make_variant_from_typed_null/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

