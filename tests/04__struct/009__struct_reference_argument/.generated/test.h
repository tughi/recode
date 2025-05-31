#ifndef __test_H__
#define __test_H__

#include "builtin_types.h"


struct test_Point {
    int32_t x;
    int32_t y;
};

int32_t test__main();

int32_t test__get_y(struct test_Point *point);

#endif // __test_H__
