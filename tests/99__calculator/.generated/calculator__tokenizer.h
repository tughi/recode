#ifndef __calculator__tokenizer_H__
#define __calculator__tokenizer_H__

#include "builtin_types.h"

#include "calculator__expression.h"
#include "calculator__source.h"
#include "io.h"

struct calculator__tokenizer_Plus {
    struct calculator__source_Span span;
};

struct calculator__tokenizer_Minus {
    struct calculator__source_Span span;
};

struct calculator__tokenizer_Multiply {
    struct calculator__source_Span span;
};

struct calculator__tokenizer_Divide {
    struct calculator__source_Span span;
};

struct calculator__tokenizer_Stop {
    struct calculator__source_Span span;
};

struct calculator__tokenizer_Token {
    int32_t variant;
    union {
        struct calculator__expression_Number variant_1;
        struct calculator__tokenizer_Plus variant_2;
        struct calculator__tokenizer_Minus variant_3;
        struct calculator__tokenizer_Multiply variant_4;
        struct calculator__tokenizer_Divide variant_5;
        struct calculator__tokenizer_Stop variant_6;
        struct calculator__source_Error variant_7;
    };
};

struct calculator__tokenizer_Tokenizer {
    uint8_t *data;
    int32_t index;
    struct calculator__tokenizer_Token current_token;
};

struct calculator__tokenizer_Tokenizer *__alloc__calculator__tokenizer_Tokenizer__(struct calculator__tokenizer_Tokenizer value);

struct calculator__tokenizer_Token *__alloc__calculator__tokenizer_Token__(struct calculator__tokenizer_Token value);

struct calculator__tokenizer_Plus *__alloc__calculator__tokenizer_Plus__(struct calculator__tokenizer_Plus value);

struct calculator__tokenizer_Minus *__alloc__calculator__tokenizer_Minus__(struct calculator__tokenizer_Minus value);

struct calculator__tokenizer_Multiply *__alloc__calculator__tokenizer_Multiply__(struct calculator__tokenizer_Multiply value);

struct calculator__tokenizer_Divide *__alloc__calculator__tokenizer_Divide__(struct calculator__tokenizer_Divide value);

struct calculator__tokenizer_Stop *__alloc__calculator__tokenizer_Stop__(struct calculator__tokenizer_Stop value);

struct calculator__tokenizer_Token pcalculator__tokenizer_Tokenizer__peek_token(struct calculator__tokenizer_Tokenizer *self);

struct calculator__tokenizer_Token pcalculator__tokenizer_Tokenizer__next_token(struct calculator__tokenizer_Tokenizer *self);

struct calculator__tokenizer_Token pcalculator__tokenizer_Tokenizer__scan_token(struct calculator__tokenizer_Tokenizer *self);

struct calculator__tokenizer_Token pcalculator__tokenizer_Tokenizer__scan_number_token(struct calculator__tokenizer_Tokenizer *self);

struct calculator__source_Span pcalculator__tokenizer_Token__span(struct calculator__tokenizer_Token *self);

struct io_Writer *pio_Writer__write_token(struct io_Writer *self, struct calculator__tokenizer_Token *token);

#endif // __calculator__tokenizer_H__
