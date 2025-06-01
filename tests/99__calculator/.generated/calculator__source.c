#include "calculator__source.h"

struct calculator__source_Span *__alloc__calculator__source_Span__(struct calculator__source_Span value) {
    struct calculator__source_Span *result = (struct calculator__source_Span *)malloc(sizeof(struct calculator__source_Span));
    *result = value;
    return result;
}

struct calculator__source_Error *__alloc__calculator__source_Error__(struct calculator__source_Error value) {
    struct calculator__source_Error *result = (struct calculator__source_Error *)malloc(sizeof(struct calculator__source_Error));
    *result = value;
    return result;
}

