#ifndef __test_H__
#define __test_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>


struct String;

struct String {
    uint8_t *data;
    uintmax_t length;
};

struct String *__alloc_String_value(struct String value);

void *malloc(uintmax_t size);

struct String test__str__concat(struct String self, struct String other);

bool test__str__equals(struct String self, struct String other);

int32_t test__main();

#endif // __test_H__
