#include "test.h"

void *malloc(uintmax_t size);

#line 17 "tests/09__variant/011__make_variant_decomposition/test.code"
int32_t test__evaluate(struct test_Expression expression) {
#line 18 "tests/09__variant/011__make_variant_decomposition/test.code"
    struct test_Expression __switch_18_value__ = expression;
#line 19 "tests/09__variant/011__make_variant_decomposition/test.code"
    if (__switch_18_value__.variant == 1) {
#line 20 "tests/09__variant/011__make_variant_decomposition/test.code"
        {
#line 20 "tests/09__variant/011__make_variant_decomposition/test.code"
            int32_t __001__ = __switch_18_value__.variant_1;
#line 20 "tests/09__variant/011__make_variant_decomposition/test.code"
            return __001__;
#line 20 "tests/09__variant/011__make_variant_decomposition/test.code"
        }
#line 21 "tests/09__variant/011__make_variant_decomposition/test.code"
    }
#line 22 "tests/09__variant/011__make_variant_decomposition/test.code"
    else if (__switch_18_value__.variant == 2) {
#line 23 "tests/09__variant/011__make_variant_decomposition/test.code"
        {
#line 23 "tests/09__variant/011__make_variant_decomposition/test.code"
            int32_t __002__ = test__evaluate(__switch_18_value__.variant_2->left) + test__evaluate(__switch_18_value__.variant_2->right);
#line 23 "tests/09__variant/011__make_variant_decomposition/test.code"
            return __002__;
#line 23 "tests/09__variant/011__make_variant_decomposition/test.code"
        }
#line 24 "tests/09__variant/011__make_variant_decomposition/test.code"
    }
#line 25 "tests/09__variant/011__make_variant_decomposition/test.code"
    else if (__switch_18_value__.variant == 3) {
#line 26 "tests/09__variant/011__make_variant_decomposition/test.code"
        {
#line 26 "tests/09__variant/011__make_variant_decomposition/test.code"
            int32_t __003__ = test__evaluate(__switch_18_value__.variant_3->left) - test__evaluate(__switch_18_value__.variant_3->right);
#line 26 "tests/09__variant/011__make_variant_decomposition/test.code"
            return __003__;
#line 26 "tests/09__variant/011__make_variant_decomposition/test.code"
        }
#line 27 "tests/09__variant/011__make_variant_decomposition/test.code"
    }
#line 28 "tests/09__variant/011__make_variant_decomposition/test.code"
    else {
#line 30 "tests/09__variant/011__make_variant_decomposition/test.code"
    }
#line 32 "tests/09__variant/011__make_variant_decomposition/test.code"
    exit(1);
#line 33 "tests/09__variant/011__make_variant_decomposition/test.code"
}

#line 37 "tests/09__variant/011__make_variant_decomposition/test.code"
int32_t test__main() {
#line 38 "tests/09__variant/011__make_variant_decomposition/test.code"
    {
#line 38 "tests/09__variant/011__make_variant_decomposition/test.code"
        struct test_Subtraction *__001__ = (struct test_Subtraction *)malloc(sizeof(struct test_Subtraction));
#line 39 "tests/09__variant/011__make_variant_decomposition/test.code"
        struct test_Expression __002__ = (struct test_Expression){.variant = 1, .variant_1 = 42};
#line 40 "tests/09__variant/011__make_variant_decomposition/test.code"
        struct test_Addition *__003__ = (struct test_Addition *)malloc(sizeof(struct test_Addition));
#line 40 "tests/09__variant/011__make_variant_decomposition/test.code"
        *__003__ = (struct test_Addition){.left = (struct test_Expression){.variant = 1, .variant_1 = 21}, .right = (struct test_Expression){.variant = 1, .variant_1 = 21}};
#line 40 "tests/09__variant/011__make_variant_decomposition/test.code"
        struct test_Expression __004__ = (struct test_Expression){.variant = 2, .variant_2 = __003__};
#line 38 "tests/09__variant/011__make_variant_decomposition/test.code"
        *__001__ = (struct test_Subtraction){.left = __002__, .right = __004__};
#line 38 "tests/09__variant/011__make_variant_decomposition/test.code"
        struct test_Expression __005__ = (struct test_Expression){.variant = 3, .variant_3 = __001__};
#line 38 "tests/09__variant/011__make_variant_decomposition/test.code"
        int32_t __006__ = test__evaluate(__005__);
#line 38 "tests/09__variant/011__make_variant_decomposition/test.code"
        return __006__;
#line 44 "tests/09__variant/011__make_variant_decomposition/test.code"
    }
#line 45 "tests/09__variant/011__make_variant_decomposition/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

