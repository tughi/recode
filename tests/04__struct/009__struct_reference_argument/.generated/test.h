#ifndef __test_H__
#define __test_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>


struct Point;

struct Point {
    int32_t x;
    int32_t y;
};

int32_t test__main();

int32_t test__get_y(struct Point *point);

#endif // __test_H__
