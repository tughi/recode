#ifndef __test_H__
#define __test_H__

#include "builtin_types.h"


struct test_Input_Stream {
    void *self;
    uint8_t (*read)(void *self);
};

int32_t test__main();

#endif // __test_H__
