#ifndef __test_H__
#define __test_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>


struct test_Point;

struct test_Point {
    int32_t x;
    int32_t y;
};

int32_t test__main();

#endif // __test_H__
