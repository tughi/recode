#ifndef __test_H__
#define __test_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>


struct test_Span {
    int32_t start;
    int32_t end;
};

struct test_Number {
    struct test_Span span;
    int32_t value;
};

struct test_Plus {
    struct test_Span span;
};

struct test_Minus {
    struct test_Span span;
};

struct test_Multiply {
    struct test_Span span;
};

struct test_Divide {
    struct test_Span span;
};

struct test_Stop {
    struct test_Span span;
};

struct String {
    uint8_t *data;
    int32_t length;
};

struct test_Error {
    struct test_Span span;
    struct String message;
};

struct test_Token {
    int32_t variant;
    union {
        struct test_Number variant_1;
        struct test_Plus variant_2;
        struct test_Minus variant_3;
        struct test_Multiply variant_4;
        struct test_Divide variant_5;
        struct test_Stop variant_6;
        struct test_Error variant_7;
    };
};

struct test_Tokenizer {
    uint8_t *data;
    int32_t index;
    struct test_Token current_token;
};

struct test_Parser {
    struct test_Tokenizer tokenizer;
};

struct test_Addition {
    struct test_Span span;
    struct test_Expression *left;
    struct test_Expression *right;
};

struct test_Division {
    struct test_Span span;
    struct test_Expression *left;
    struct test_Expression *right;
};

struct test_Multiplication {
    struct test_Span span;
    struct test_Expression *left;
    struct test_Expression *right;
};

struct test_Subtraction {
    struct test_Span span;
    struct test_Expression *left;
    struct test_Expression *right;
};

struct test_Expression {
    int32_t variant;
    union {
        struct test_Number variant_1;
        struct test_Addition variant_2;
        struct test_Division variant_3;
        struct test_Multiplication variant_4;
        struct test_Subtraction variant_5;
        struct test_Error variant_6;
    };
};

struct test_Writer {
    void *self;
    void (*write_char)(void *self, uint8_t c);
};

struct test_String_Builder {
    uint8_t *data;
    int32_t data_size;
    int32_t length;
};

extern struct test_FILE *__stdinp;

extern struct test_FILE *__stdoutp;

extern struct test_FILE *__stderrp;

struct test_Parser *__alloc__test_Parser__(struct test_Parser value);

struct test_Tokenizer *__alloc__test_Tokenizer__(struct test_Tokenizer value);

struct test_Token *__alloc__test_Token__(struct test_Token value);

struct test_Number *__alloc__test_Number__(struct test_Number value);

struct test_Span *__alloc__test_Span__(struct test_Span value);

struct test_Plus *__alloc__test_Plus__(struct test_Plus value);

struct test_Minus *__alloc__test_Minus__(struct test_Minus value);

struct test_Multiply *__alloc__test_Multiply__(struct test_Multiply value);

struct test_Divide *__alloc__test_Divide__(struct test_Divide value);

struct test_Stop *__alloc__test_Stop__(struct test_Stop value);

struct test_Error *__alloc__test_Error__(struct test_Error value);

struct String *__alloc__String__(struct String value);

struct test_Expression *__alloc__test_Expression__(struct test_Expression value);

struct test_Addition *__alloc__test_Addition__(struct test_Addition value);

struct test_Division *__alloc__test_Division__(struct test_Division value);

struct test_Multiplication *__alloc__test_Multiplication__(struct test_Multiplication value);

struct test_Subtraction *__alloc__test_Subtraction__(struct test_Subtraction value);

struct test_Writer *__alloc__test_Writer__(struct test_Writer value);

struct test_String_Builder *__alloc__test_String_Builder__(struct test_String_Builder value);

int32_t test__main(int32_t argc, uint8_t **argv);

int32_t test__evaluate__0_expression(struct test_Expression *expression);

struct test_Expression ptest_Parser__parse_expression(struct test_Parser *self);

struct test_Expression ptest_Parser__parse_additive_expression(struct test_Parser *self);

struct test_Expression ptest_Parser__parse_multiplicative_expression(struct test_Parser *self);

struct test_Expression ptest_Parser__parse_primary_expression(struct test_Parser *self);

struct test_Span ptest_Expression__span(struct test_Expression *self);

struct test_Writer *ptest_Writer__write__1_expression(struct test_Writer *self, struct test_Expression *expression);

struct test_Token ptest_Tokenizer__peek_token(struct test_Tokenizer *self);

struct test_Token ptest_Tokenizer__next_token(struct test_Tokenizer *self);

struct test_Token ptest_Tokenizer__scan_token(struct test_Tokenizer *self);

struct test_Token ptest_Tokenizer__scan_number_token(struct test_Tokenizer *self);

struct test_Span ptest_Token__span(struct test_Token *self);

struct test_Writer *ptest_Writer__write__1_token(struct test_Writer *self, struct test_Token *token);

struct test_Writer *ptest_Writer__write__1_char(struct test_Writer *self, uint8_t c);

struct test_Writer *ptest_Writer__write__1_signed(struct test_Writer *self, int32_t value);

struct test_Writer *ptest_Writer__end_line(struct test_Writer *self);

struct test_String_Builder *ptest_String_Builder__write__1_char(struct test_String_Builder *self, uint8_t c);

struct String ptest_String_Builder__build(struct test_String_Builder *self);

struct test_String_Builder test__make_string_builder();

struct test_String_Builder test__make_string_builder__0_initial_data_size(int32_t initial_data_size);

void ptest_String_Builder__write_char(struct test_String_Builder *self, uint8_t c);

struct test_Writer *ptest_Writer__write(struct test_Writer *self, struct String string);

int32_t fputc(int32_t c, struct test_FILE *file);

void ptest_FILE__write_char(struct test_FILE *self, uint8_t c);

void *malloc(uint64_t size);

void *realloc(void *block, uint64_t size);

void exit(int32_t code);

#endif // __test_H__
