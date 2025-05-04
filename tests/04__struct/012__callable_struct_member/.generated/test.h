#ifndef __test_H__
#define __test_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>


struct test_Function;

struct test_Function {
    int32_t (*run)();
};

int32_t test__forty_two();

int32_t test__main();

#endif // __test_H__
