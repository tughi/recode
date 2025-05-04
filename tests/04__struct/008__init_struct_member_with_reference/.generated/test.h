#ifndef __test_H__
#define __test_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>


struct test_Number;

struct test_Number {
    int32_t value;
    struct test_Number *next;
};

int32_t test__main();

#endif // __test_H__
