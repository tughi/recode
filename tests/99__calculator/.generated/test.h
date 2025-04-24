#ifndef __test_H__
#define __test_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>


struct Parser;

struct Tokenizer;

struct Token;

struct Number;

struct Span;

struct Plus;

struct Minus;

struct Multiply;

struct Divide;

struct Stop;

struct Error;

struct String;

struct Expression;

struct Addition;

struct Division;

struct Multiplication;

struct Subtraction;

struct Writer;

struct String_Builder;

typedef struct FILE FILE;

struct Span {
    int32_t start;
    int32_t end;
};

struct Number {
    struct Span span;
    int32_t value;
};

struct Plus {
    struct Span span;
};

struct Minus {
    struct Span span;
};

struct Multiply {
    struct Span span;
};

struct Divide {
    struct Span span;
};

struct Stop {
    struct Span span;
};

struct String {
    uint8_t *data;
    int32_t length;
};

struct Error {
    struct Span span;
    struct String message;
};

struct Token {
    int32_t variant;
    union {
        struct Number variant_1;
        struct Plus variant_2;
        struct Minus variant_3;
        struct Multiply variant_4;
        struct Divide variant_5;
        struct Stop variant_6;
        struct Error variant_7;
    };
};

struct Tokenizer {
    uint8_t *data;
    int32_t index;
    struct Token current_token;
};

struct Parser {
    struct Tokenizer tokenizer;
};

struct Addition {
    struct Span span;
    struct Expression *left;
    struct Expression *right;
};

struct Division {
    struct Span span;
    struct Expression *left;
    struct Expression *right;
};

struct Multiplication {
    struct Span span;
    struct Expression *left;
    struct Expression *right;
};

struct Subtraction {
    struct Span span;
    struct Expression *left;
    struct Expression *right;
};

struct Expression {
    int32_t variant;
    union {
        struct Number variant_1;
        struct Addition variant_2;
        struct Division variant_3;
        struct Multiplication variant_4;
        struct Subtraction variant_5;
        struct Error variant_6;
    };
};

struct Writer {
    void *self;
    void (*write_char)(void *self, uint8_t c);
};

struct String_Builder {
    uint8_t *data;
    int32_t data_size;
    int32_t length;
};

extern FILE *__stdinp;
extern FILE *__stdoutp;
extern FILE *__stderrp;
struct Parser *__alloc_Parser_value(struct Parser value);

struct Tokenizer *__alloc_Tokenizer_value(struct Tokenizer value);

struct Token *__alloc_Token_value(struct Token value);

struct Number *__alloc_Number_value(struct Number value);

struct Span *__alloc_Span_value(struct Span value);

struct Plus *__alloc_Plus_value(struct Plus value);

struct Minus *__alloc_Minus_value(struct Minus value);

struct Multiply *__alloc_Multiply_value(struct Multiply value);

struct Divide *__alloc_Divide_value(struct Divide value);

struct Stop *__alloc_Stop_value(struct Stop value);

struct Error *__alloc_Error_value(struct Error value);

struct String *__alloc_String_value(struct String value);

struct Expression *__alloc_Expression_value(struct Expression value);

struct Addition *__alloc_Addition_value(struct Addition value);

struct Division *__alloc_Division_value(struct Division value);

struct Multiplication *__alloc_Multiplication_value(struct Multiplication value);

struct Subtraction *__alloc_Subtraction_value(struct Subtraction value);

struct Writer *__alloc_Writer_value(struct Writer value);

struct String_Builder *__alloc_String_Builder_value(struct String_Builder value);

int32_t test__main(int32_t argc, uint8_t **argv);

int32_t test__evaluate__0_expression(struct Expression *expression);

struct Expression test__pParser__parse_expression(struct Parser *self);

struct Expression test__pParser__parse_additive_expression(struct Parser *self);

struct Expression test__pParser__parse_multiplicative_expression(struct Parser *self);

struct Expression test__pParser__parse_primary_expression(struct Parser *self);

struct Span test__pExpression__span(struct Expression *self);

struct Writer *test__pWriter__write__1_expression(struct Writer *self, struct Expression *expression);

struct Token test__pTokenizer__peek_token(struct Tokenizer *self);

struct Token test__pTokenizer__next_token(struct Tokenizer *self);

struct Token test__pTokenizer__scan_token(struct Tokenizer *self);

struct Token test__pTokenizer__scan_number_token(struct Tokenizer *self);

struct Span test__pToken__span(struct Token *self);

struct Writer *test__pWriter__write__1_token(struct Writer *self, struct Token *token);

struct Writer *test__pWriter__write__1_char(struct Writer *self, uint8_t c);

struct Writer *test__pWriter__write__1_signed(struct Writer *self, int32_t value);

struct Writer *test__pWriter__end_line(struct Writer *self);

struct String_Builder *test__pString_Builder__write__1_char(struct String_Builder *self, uint8_t c);

struct String test__pString_Builder__build(struct String_Builder *self);

struct String_Builder test__make_string_builder();

struct String_Builder test__make_string_builder__0_initial_data_size(int32_t initial_data_size);

void test__pString_Builder__write_char(struct String_Builder *self, uint8_t c);

struct Writer *test__pWriter__write(struct Writer *self, struct String string);

int32_t fputc(int32_t c, FILE *file);

void test__pFILE__write_char(FILE *self, uint8_t c);

void *malloc(uint64_t size);

void *realloc(void *block, uint64_t size);

void exit(int32_t code);

#endif // __test_H__
