#ifndef __test_H__
#define __test_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>


struct Number;

struct Boolean;

struct Number {
    int32_t value;
};

struct Boolean {
    bool value;
};

int32_t test__pNumber__get_value(struct Number *self);

void test__pNumber__set_value(struct Number *self, int32_t value);

bool test__pBoolean__get_value(struct Boolean *self);

int32_t test__main();

#endif // __test_H__
