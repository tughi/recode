#ifndef __calculator__source_H__
#define __calculator__source_H__

#include "builtin_types.h"

#include "libc.h"

struct calculator__source_Span {
    int32_t start;
    int32_t end;
};

struct calculator__source_Error {
    struct calculator__source_Span span;
    struct String message;
};

struct calculator__source_Span *__alloc__calculator__source_Span__(struct calculator__source_Span value);

struct calculator__source_Error *__alloc__calculator__source_Error__(struct calculator__source_Error value);

#endif // __calculator__source_H__
