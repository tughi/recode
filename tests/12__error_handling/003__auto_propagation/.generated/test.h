#ifndef __test_H__
#define __test_H__

#include "builtin_types.h"


struct test_Error {
    int32_t code;
};

struct test_Result__9 {
    bool success;
    union {
        int32_t value;
        struct test_Error error;
    };
};

int32_t test__main();

struct test_Result__9 test__increment(int32_t value);

struct test_Result__9 test__count_from(int32_t value);

#endif // __test_H__
