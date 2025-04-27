#ifndef __test_H__
#define __test_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>


struct test__Number;

struct test__Boolean;

struct test__Number {
    int32_t value;
};

struct test__Boolean {
    bool value;
};

int32_t test__ptest__Number__get_value(struct test__Number *self);

void test__ptest__Number__set_value(struct test__Number *self, int32_t value);

bool test__ptest__Boolean__get_value(struct test__Boolean *self);

int32_t test__main();

#endif // __test_H__
