#ifndef __calculator__source_H__
#define __calculator__source_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

#include "libc.h"

struct calculator__source_Span {
    int32_t start;
    int32_t end;
};

struct calculator__source_Span *__alloc__calculator__source_Span__(struct calculator__source_Span value);

#endif // __calculator__source_H__
