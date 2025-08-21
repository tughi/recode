#ifndef __calculator__source_H__
#define __calculator__source_H__

#include "builtin_types.h"


struct calculator__source_Span {
    int32_t start;
    int32_t end;
};

struct calculator__source_Error {
    struct calculator__source_Span span;
    struct String message;
};

#endif // __calculator__source_H__
