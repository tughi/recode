#ifndef __test_H__
#define __test_H__

#include "builtin_types.h"


struct test_Number {
    int32_t value;
    struct test_Number *next;
};

int32_t test__main();

#endif // __test_H__
