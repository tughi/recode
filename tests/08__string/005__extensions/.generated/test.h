#ifndef __test_H__
#define __test_H__

#include "types.h"


void *malloc(uintmax_t size);

struct String str__concat(struct String self, struct String other);

bool str__equals(struct String self, struct String other);

int32_t test__main();

#endif // __test_H__
