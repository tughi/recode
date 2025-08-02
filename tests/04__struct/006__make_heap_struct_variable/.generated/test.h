#ifndef __test_H__
#define __test_H__

#include "builtin_types.h"


struct test_Point {
    int32_t x;
    int32_t y;
};

struct test_Line {
    struct test_Point p1;
    struct test_Point p2;
};

int32_t test__main();

void *malloc(uintmax_t size);

#endif // __test_H__
