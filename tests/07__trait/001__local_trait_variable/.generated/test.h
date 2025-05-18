#ifndef __test_H__
#define __test_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>


struct test_Animal {
    void *self;
    int32_t (*legs)(void *self);
};

int32_t test__main();

#endif // __test_H__
