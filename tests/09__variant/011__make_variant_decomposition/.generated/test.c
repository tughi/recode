#include "test.h"

void *malloc(uintmax_t size);

#line 17 "tests/09__variant/011__make_variant_decomposition/test.code"
int32_t test__evaluate(struct test_Expression expression) {
#line 18 "tests/09__variant/011__make_variant_decomposition/test.code"
    struct test_Expression __switch_18_value__ = expression;
#line 19 "tests/09__variant/011__make_variant_decomposition/test.code"
    if (__switch_18_value__.variant == 0) {
#line 20 "tests/09__variant/011__make_variant_decomposition/test.code"
        return 0;
    }
#line 22 "tests/09__variant/011__make_variant_decomposition/test.code"
    else if (__switch_18_value__.variant == 1) {
#line 23 "tests/09__variant/011__make_variant_decomposition/test.code"
        return __switch_18_value__.variant_1;
    }
#line 25 "tests/09__variant/011__make_variant_decomposition/test.code"
    else if (__switch_18_value__.variant == 2) {
#line 26 "tests/09__variant/011__make_variant_decomposition/test.code"
        return test__evaluate(__switch_18_value__.variant_2->left) + test__evaluate(__switch_18_value__.variant_2->right);
    }
#line 28 "tests/09__variant/011__make_variant_decomposition/test.code"
    else if (__switch_18_value__.variant == 3) {
#line 29 "tests/09__variant/011__make_variant_decomposition/test.code"
        return test__evaluate(__switch_18_value__.variant_3->left) - test__evaluate(__switch_18_value__.variant_3->right);
    }
}

#line 34 "tests/09__variant/011__make_variant_decomposition/test.code"
int32_t test__main() {
#line 35 "tests/09__variant/011__make_variant_decomposition/test.code"
    {
#line 35 "tests/09__variant/011__make_variant_decomposition/test.code"
        struct test_Subtraction *__001__ = (struct test_Subtraction *)malloc(sizeof(struct test_Subtraction));
#line 36 "tests/09__variant/011__make_variant_decomposition/test.code"
        struct test_Expression __002__ = (struct test_Expression){.variant = 1, .variant_1 = 42};
#line 37 "tests/09__variant/011__make_variant_decomposition/test.code"
        struct test_Addition *__003__ = (struct test_Addition *)malloc(sizeof(struct test_Addition));
#line 37 "tests/09__variant/011__make_variant_decomposition/test.code"
        *__003__ = (struct test_Addition){.left = (struct test_Expression){.variant = 1, .variant_1 = 21}, .right = (struct test_Expression){.variant = 1, .variant_1 = 21}};
#line 37 "tests/09__variant/011__make_variant_decomposition/test.code"
        struct test_Expression __004__ = (struct test_Expression){.variant = 2, .variant_2 = __003__};
#line 35 "tests/09__variant/011__make_variant_decomposition/test.code"
        *__001__ = (struct test_Subtraction){.left = __002__, .right = __004__};
#line 35 "tests/09__variant/011__make_variant_decomposition/test.code"
        struct test_Expression __005__ = (struct test_Expression){.variant = 3, .variant_3 = __001__};
#line 35 "tests/09__variant/011__make_variant_decomposition/test.code"
        return test__evaluate(__005__);
    }
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

