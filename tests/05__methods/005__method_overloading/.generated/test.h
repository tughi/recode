#ifndef __test_H__
#define __test_H__

#include "types.h"


void ptest_Counter__add(struct test_Counter *self);

void ptest_Counter__add__amount(struct test_Counter *self, int32_t amount);

int32_t test__main();

#endif // __test_H__
