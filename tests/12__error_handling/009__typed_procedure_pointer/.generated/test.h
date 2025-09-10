#ifndef __test_H__
#define __test_H__

#include "builtin_types.h"


struct test_Result__6 {
    bool success;
    union {
        int32_t value;
        int32_t error;
    };
};

struct test_Result__2 {
    bool success;
    union {
        int32_t value;
        int32_t error;
    };
};

int32_t test__main();

struct test_Result__6 test__demo();

#endif // __test_H__
