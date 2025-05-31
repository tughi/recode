#ifndef __test_H__
#define __test_H__

#include "builtin_types.h"


struct test_Integer {
    int32_t variant;
    union {
        int8_t variant_1;
        int32_t variant_2;
    };
};

int32_t test__main();

#endif // __test_H__
