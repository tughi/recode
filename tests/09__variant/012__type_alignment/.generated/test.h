#ifndef __test_H__
#define __test_H__

#include "builtin_types.h"


struct test_Data {
    int32_t variant;
    union {
        bool variant_1;
        int8_t variant_2;
    };
};

struct test_More_Data {
    int32_t variant;
    union {
        struct test_Data variant_1;
        int64_t variant_2;
    };
};

int32_t test__main();

#endif // __test_H__
