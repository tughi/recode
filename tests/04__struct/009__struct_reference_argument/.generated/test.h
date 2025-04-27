#ifndef __test_H__
#define __test_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>


struct test__Point;

struct test__Point {
    int32_t x;
    int32_t y;
};

int32_t test__main();

int32_t test__get_y(struct test__Point *point);

#endif // __test_H__
