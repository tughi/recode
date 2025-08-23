#ifndef __test_H__
#define __test_H__

#include "builtin_types.h"


struct test_Error {
    int32_t code;
};

struct test_Result__8 {
    bool success;
    union {
        struct test_Error error;
    };
};

int32_t test__main();

struct test_Result__8 test__auto_raise_error(bool condition);

struct test_Result__8 test__raise_error(bool condition);

#endif // __test_H__
