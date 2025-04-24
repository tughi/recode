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

int32_t test__main();

#endif // __test_H__
