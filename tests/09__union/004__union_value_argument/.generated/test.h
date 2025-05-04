#ifndef __test_H__
#define __test_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>


struct test_Value;

struct test_Value {
    int32_t variant;
    union {
        bool variant_1;
        int32_t variant_2;
    };
};

int32_t test__main();

struct test_Value test__demo__0_value(struct test_Value value);

#endif // __test_H__
