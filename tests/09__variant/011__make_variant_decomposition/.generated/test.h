#ifndef __test_H__
#define __test_H__

#include "builtin_types.h"


struct test_Expression {
    int32_t variant;
    union {
        int32_t variant_1;
        struct test_Addition *variant_2;
        struct test_Subtraction *variant_3;
    };
};

struct test_Addition {
    struct test_Expression left;
    struct test_Expression right;
};

struct test_Subtraction {
    struct test_Expression left;
    struct test_Expression right;
};

int32_t test__evaluate(struct test_Expression expression);

void exit(int32_t status);

int32_t test__main();

#endif // __test_H__
