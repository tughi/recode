#ifndef __test_H__
#define __test_H__

#include "builtin_types.h"


struct test_Result__5 {
    bool success;
    union {
        int32_t value;
        int32_t error;
    };
};

int32_t test__main();

struct test_Result__5 test__raise_forty_two();

#endif // __test_H__
