#ifndef __TYPES_H__
#define __TYPES_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct String {
    uint8_t *data;
    uintmax_t length;
};

struct calculator__source_Span {
    int32_t start;
    int32_t end;
};

struct calculator__expression_Number {
    struct calculator__source_Span span;
    int32_t value;
};

struct calculator__expression_Expression;

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

struct calculator__source_Error {
    struct calculator__source_Span span;
    struct String message;
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

struct calculator__parser_Parser {
    struct calculator__tokenizer_Tokenizer tokenizer;
};

struct io_Writer {
    void *self;
    void (*write_char)(void *self, uint8_t c);
};

struct string_Builder {
    uint8_t *data;
    uintmax_t data_size;
    uintmax_t length;
};

#endif // __TYPES_H__
