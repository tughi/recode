#ifndef __test_H__
#define __test_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>


struct test__Number;

struct test__Number {
    int32_t value;
    struct test__Number *next;
};

int32_t test__main();

#endif // __test_H__
