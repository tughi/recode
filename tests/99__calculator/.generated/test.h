#ifndef __test_H__
#define __test_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>


struct test__Parser;

struct test__Tokenizer;

struct test__Token;

struct test__Number;

struct test__Span;

struct test__Plus;

struct test__Minus;

struct test__Multiply;

struct test__Divide;

struct test__Stop;

struct test__Error;

struct String;

struct test__Expression;

struct test__Addition;

struct test__Division;

struct test__Multiplication;

struct test__Subtraction;

struct test__Writer;

struct test__String_Builder;

typedef struct test__FILE test__FILE;

struct test__Span {
    int32_t start;
    int32_t end;
};

struct test__Number {
    struct test__Span span;
    int32_t value;
};

struct test__Plus {
    struct test__Span span;
};

struct test__Minus {
    struct test__Span span;
};

struct test__Multiply {
    struct test__Span span;
};

struct test__Divide {
    struct test__Span span;
};

struct test__Stop {
    struct test__Span span;
};

struct String {
    uint8_t *data;
    int32_t length;
};

struct test__Error {
    struct test__Span span;
    struct String message;
};

struct test__Token {
    int32_t variant;
    union {
        struct test__Number variant_1;
        struct test__Plus variant_2;
        struct test__Minus variant_3;
        struct test__Multiply variant_4;
        struct test__Divide variant_5;
        struct test__Stop variant_6;
        struct test__Error variant_7;
    };
};

struct test__Tokenizer {
    uint8_t *data;
    int32_t index;
    struct test__Token current_token;
};

struct test__Parser {
    struct test__Tokenizer tokenizer;
};

struct test__Addition {
    struct test__Span span;
    struct test__Expression *left;
    struct test__Expression *right;
};

struct test__Division {
    struct test__Span span;
    struct test__Expression *left;
    struct test__Expression *right;
};

struct test__Multiplication {
    struct test__Span span;
    struct test__Expression *left;
    struct test__Expression *right;
};

struct test__Subtraction {
    struct test__Span span;
    struct test__Expression *left;
    struct test__Expression *right;
};

struct test__Expression {
    int32_t variant;
    union {
        struct test__Number variant_1;
        struct test__Addition variant_2;
        struct test__Division variant_3;
        struct test__Multiplication variant_4;
        struct test__Subtraction variant_5;
        struct test__Error variant_6;
    };
};

struct test__Writer {
    void *self;
    void (*write_char)(void *self, uint8_t c);
};

struct test__String_Builder {
    uint8_t *data;
    int32_t data_size;
    int32_t length;
};

extern test__FILE *__stdinp;
extern test__FILE *__stdoutp;
extern test__FILE *__stderrp;
struct test__Parser *__alloc_test__Parser_value(struct test__Parser value);

struct test__Tokenizer *__alloc_test__Tokenizer_value(struct test__Tokenizer value);

struct test__Token *__alloc_test__Token_value(struct test__Token value);

struct test__Number *__alloc_test__Number_value(struct test__Number value);

struct test__Span *__alloc_test__Span_value(struct test__Span value);

struct test__Plus *__alloc_test__Plus_value(struct test__Plus value);

struct test__Minus *__alloc_test__Minus_value(struct test__Minus value);

struct test__Multiply *__alloc_test__Multiply_value(struct test__Multiply value);

struct test__Divide *__alloc_test__Divide_value(struct test__Divide value);

struct test__Stop *__alloc_test__Stop_value(struct test__Stop value);

struct test__Error *__alloc_test__Error_value(struct test__Error value);

struct String *__alloc_String_value(struct String value);

struct test__Expression *__alloc_test__Expression_value(struct test__Expression value);

struct test__Addition *__alloc_test__Addition_value(struct test__Addition value);

struct test__Division *__alloc_test__Division_value(struct test__Division value);

struct test__Multiplication *__alloc_test__Multiplication_value(struct test__Multiplication value);

struct test__Subtraction *__alloc_test__Subtraction_value(struct test__Subtraction value);

struct test__Writer *__alloc_test__Writer_value(struct test__Writer value);

struct test__String_Builder *__alloc_test__String_Builder_value(struct test__String_Builder value);

int32_t test__main(int32_t argc, uint8_t **argv);

int32_t test__evaluate__0_expression(struct test__Expression *expression);

struct test__Expression test__ptest__Parser__parse_expression(struct test__Parser *self);

struct test__Expression test__ptest__Parser__parse_additive_expression(struct test__Parser *self);

struct test__Expression test__ptest__Parser__parse_multiplicative_expression(struct test__Parser *self);

struct test__Expression test__ptest__Parser__parse_primary_expression(struct test__Parser *self);

struct test__Span test__ptest__Expression__span(struct test__Expression *self);

struct test__Writer *test__ptest__Writer__write__1_expression(struct test__Writer *self, struct test__Expression *expression);

struct test__Token test__ptest__Tokenizer__peek_token(struct test__Tokenizer *self);

struct test__Token test__ptest__Tokenizer__next_token(struct test__Tokenizer *self);

struct test__Token test__ptest__Tokenizer__scan_token(struct test__Tokenizer *self);

struct test__Token test__ptest__Tokenizer__scan_number_token(struct test__Tokenizer *self);

struct test__Span test__ptest__Token__span(struct test__Token *self);

struct test__Writer *test__ptest__Writer__write__1_token(struct test__Writer *self, struct test__Token *token);

struct test__Writer *test__ptest__Writer__write__1_char(struct test__Writer *self, uint8_t c);

struct test__Writer *test__ptest__Writer__write__1_signed(struct test__Writer *self, int32_t value);

struct test__Writer *test__ptest__Writer__end_line(struct test__Writer *self);

struct test__String_Builder *test__ptest__String_Builder__write__1_char(struct test__String_Builder *self, uint8_t c);

struct String test__ptest__String_Builder__build(struct test__String_Builder *self);

struct test__String_Builder test__make_string_builder();

struct test__String_Builder test__make_string_builder__0_initial_data_size(int32_t initial_data_size);

void test__ptest__String_Builder__write_char(struct test__String_Builder *self, uint8_t c);

struct test__Writer *test__ptest__Writer__write(struct test__Writer *self, struct String string);

int32_t fputc(int32_t c, test__FILE *file);

void test__ptest__FILE__write_char(test__FILE *self, uint8_t c);

void *malloc(uint64_t size);

void *realloc(void *block, uint64_t size);

void exit(int32_t code);

#endif // __test_H__
