#ifndef __test_H__
#define __test_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>


struct test_Number {
    int32_t value;
};

struct test_Boolean {
    bool value;
};

int32_t ptest_Number__get_value(struct test_Number *self);

void ptest_Number__set_value(struct test_Number *self, int32_t value);

bool ptest_Boolean__get_value(struct test_Boolean *self);

int32_t test__main();

#endif // __test_H__
