#ifndef __test_H__
#define __test_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>


struct test_Integer;

struct test_Value;

struct test_Integer {
    int32_t variant;
    union {
        int8_t variant_1;
        int32_t variant_2;
    };
};

struct test_Value {
    int32_t variant;
    union {
        bool variant_1;
        struct test_Integer variant_2;
    };
};

int32_t test__main();

#endif // __test_H__
