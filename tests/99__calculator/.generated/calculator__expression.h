#ifndef __calculator__expression_H__
#define __calculator__expression_H__

#include "builtin_types.h"

#include "calculator__source.h"
#include "io.h"

struct calculator__expression_Number {
    struct calculator__source_Span span;
    int32_t value;
};

struct calculator__expression_Addition {
    struct calculator__source_Span span;
    struct calculator__expression_Expression *left;
    struct calculator__expression_Expression *right;
};

struct calculator__expression_Division {
    struct calculator__source_Span span;
    struct calculator__expression_Expression *left;
    struct calculator__expression_Expression *right;
};

struct calculator__expression_Multiplication {
    struct calculator__source_Span span;
    struct calculator__expression_Expression *left;
    struct calculator__expression_Expression *right;
};

struct calculator__expression_Subtraction {
    struct calculator__source_Span span;
    struct calculator__expression_Expression *left;
    struct calculator__expression_Expression *right;
};

struct calculator__expression_Expression {
    int32_t variant;
    union {
        struct calculator__expression_Number variant_1;
        struct calculator__expression_Addition variant_2;
        struct calculator__expression_Division variant_3;
        struct calculator__expression_Multiplication variant_4;
        struct calculator__expression_Subtraction variant_5;
        struct calculator__source_Error variant_6;
    };
};

struct calculator__expression_Expression *__alloc__calculator__expression_Expression__(struct calculator__expression_Expression value);

struct calculator__expression_Number *__alloc__calculator__expression_Number__(struct calculator__expression_Number value);

struct calculator__expression_Addition *__alloc__calculator__expression_Addition__(struct calculator__expression_Addition value);

struct calculator__expression_Division *__alloc__calculator__expression_Division__(struct calculator__expression_Division value);

struct calculator__expression_Multiplication *__alloc__calculator__expression_Multiplication__(struct calculator__expression_Multiplication value);

struct calculator__expression_Subtraction *__alloc__calculator__expression_Subtraction__(struct calculator__expression_Subtraction value);

struct calculator__source_Span pcalculator__expression_Expression__span(struct calculator__expression_Expression *self);

struct io_Writer *pio_Writer__write_expression(struct io_Writer *self, struct calculator__expression_Expression *expression);

#endif // __calculator__expression_H__
