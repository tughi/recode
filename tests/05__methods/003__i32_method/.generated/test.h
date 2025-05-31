#ifndef __test_H__
#define __test_H__

#include "builtin_types.h"


struct test_Number {
    int32_t value;
};

int32_t ptest_Number__get_value(struct test_Number *self);

int32_t i32__get_value(int32_t self);

int32_t test__main();

#endif // __test_H__
