#ifndef __test_H__
#define __test_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>


struct test_Value {
    int32_t variant;
    union {
        bool variant_1;
        int8_t variant_2;
        int32_t variant_3;
    };
};

struct test_Literal {
    struct test_Value value;
};

int32_t test__main();

#endif // __test_H__
