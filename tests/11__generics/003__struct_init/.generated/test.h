#ifndef __test_H__
#define __test_H__

#include "builtin_types.h"


struct test_Array__i32 {
    int32_t *items;
    uintmax_t length;
    uintmax_t capacity;
};

int32_t test__main();

#endif // __test_H__
