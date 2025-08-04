#ifndef __test_H__
#define __test_H__

#include "builtin_types.h"


struct test_Value {
    int32_t variant;
    union {
        uintmax_t variant_1;
        int32_t *variant_2;
        int64_t *variant_3;
    };
};

int32_t test__main();

#endif // __test_H__
