#ifndef __test_H__
#define __test_H__

#include "builtin_types.h"

#include "source.h"

struct test_Token {
    struct source_Span span;
};

int32_t test__main();

#endif // __test_H__
