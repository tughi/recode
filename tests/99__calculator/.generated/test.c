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

int32_t main(int argc, const char **argv) {
    return test__main(argc, (uint8_t **)argv);
}

struct Parser *__alloc_Parser_value(struct Parser value) {
    struct Parser *result = (struct Parser *)malloc(sizeof(struct Parser));
    *result = value;
    return result;
}

struct Tokenizer *__alloc_Tokenizer_value(struct Tokenizer value) {
    struct Tokenizer *result = (struct Tokenizer *)malloc(sizeof(struct Tokenizer));
    *result = value;
    return result;
}

struct Token *__alloc_Token_value(struct Token value) {
struct Token *result = (struct Token *)malloc(sizeof(struct Token));
    *result = value;
    return result;
}

struct Number *__alloc_Number_value(struct Number value) {
    struct Number *result = (struct Number *)malloc(sizeof(struct Number));
    *result = value;
    return result;
}

struct Span *__alloc_Span_value(struct Span value) {
    struct Span *result = (struct Span *)malloc(sizeof(struct Span));
    *result = value;
    return result;
}

struct Plus *__alloc_Plus_value(struct Plus value) {
    struct Plus *result = (struct Plus *)malloc(sizeof(struct Plus));
    *result = value;
    return result;
}

struct Minus *__alloc_Minus_value(struct Minus value) {
    struct Minus *result = (struct Minus *)malloc(sizeof(struct Minus));
    *result = value;
    return result;
}

struct Multiply *__alloc_Multiply_value(struct Multiply value) {
    struct Multiply *result = (struct Multiply *)malloc(sizeof(struct Multiply));
    *result = value;
    return result;
}

struct Divide *__alloc_Divide_value(struct Divide value) {
    struct Divide *result = (struct Divide *)malloc(sizeof(struct Divide));
    *result = value;
    return result;
}

struct Stop *__alloc_Stop_value(struct Stop value) {
    struct Stop *result = (struct Stop *)malloc(sizeof(struct Stop));
    *result = value;
    return result;
}

struct Error *__alloc_Error_value(struct Error value) {
    struct Error *result = (struct Error *)malloc(sizeof(struct Error));
    *result = value;
    return result;
}

struct String *__alloc_String_value(struct String value) {
    struct String *result = (struct String *)malloc(sizeof(struct String));
    *result = value;
    return result;
}

struct Expression *__alloc_Expression_value(struct Expression value) {
struct Expression *result = (struct Expression *)malloc(sizeof(struct Expression));
    *result = value;
    return result;
}

struct Addition *__alloc_Addition_value(struct Addition value) {
    struct Addition *result = (struct Addition *)malloc(sizeof(struct Addition));
    *result = value;
    return result;
}

struct Division *__alloc_Division_value(struct Division value) {
    struct Division *result = (struct Division *)malloc(sizeof(struct Division));
    *result = value;
    return result;
}

struct Multiplication *__alloc_Multiplication_value(struct Multiplication value) {
    struct Multiplication *result = (struct Multiplication *)malloc(sizeof(struct Multiplication));
    *result = value;
    return result;
}

struct Subtraction *__alloc_Subtraction_value(struct Subtraction value) {
    struct Subtraction *result = (struct Subtraction *)malloc(sizeof(struct Subtraction));
    *result = value;
    return result;
}

struct Writer *__alloc_Writer_value(struct Writer value) {
    struct Writer *result = (struct Writer *)malloc(sizeof(struct Writer));
    *result = value;
    return result;
}

struct String_Builder *__alloc_String_Builder_value(struct String_Builder value) {
    struct String_Builder *result = (struct String_Builder *)malloc(sizeof(struct String_Builder));
    *result = value;
    return result;
}

#line 1 "tests/99__calculator/test.code"
int32_t test__main(int32_t argc, uint8_t **argv) {
#line 2 "tests/99__calculator/test.code"
    if (argc != 2) {
#line 3 "tests/99__calculator/test.code"
        exit(1);
    }
#line 6 "tests/99__calculator/test.code"
    struct Tokenizer tokenizer = (struct Tokenizer){.data = argv[1], .index = 0};
#line 11 "tests/99__calculator/test.code"
    struct Writer stdout_writer = (struct Writer){.self = __stdoutp, .write_char = ((void (*)(void *self, uint8_t c)) test__pFILE__write_char)};
#line 13 "tests/99__calculator/test.code"
    while (test__pTokenizer__peek_token(&tokenizer).variant != 6) {
#line 14 "tests/99__calculator/test.code"
        struct Token token = test__pTokenizer__next_token(&tokenizer);
#line 15 "tests/99__calculator/test.code"
        test__pWriter__end_line(test__pWriter__write__1_token(&stdout_writer, &token));
    }
#line 18 "tests/99__calculator/test.code"
    struct Parser parser = (struct Parser){.tokenizer = (struct Tokenizer){.data = argv[1], .index = 0}};
#line 22 "tests/99__calculator/test.code"
    struct Expression expression = test__pParser__parse_expression(&parser);
#line 23 "tests/99__calculator/test.code"
    test__pWriter__end_line(test__pWriter__write__1_expression(test__pWriter__write(&stdout_writer, (struct String){.data = "Expression: ", .length = 12}), &expression));
#line 25 "tests/99__calculator/test.code"
    int32_t result = test__evaluate__0_expression(&expression);
#line 26 "tests/99__calculator/test.code"
    test__pWriter__end_line(test__pWriter__write__1_signed(test__pWriter__write(&stdout_writer, (struct String){.data = "Result: ", .length = 8}), result));
#line 28 "tests/99__calculator/test.code"
    return 0;
}

#line 33 "tests/99__calculator/test.code"
int32_t test__evaluate__0_expression(struct Expression *expression) {
#line 34 "tests/99__calculator/test.code"
    struct Expression *__switch_34_value__ = expression;
#line 35 "tests/99__calculator/test.code"
    if (__switch_34_value__->variant == 1) {
#line 36 "tests/99__calculator/test.code"
        return __switch_34_value__->variant_1.value;
    }
#line 38 "tests/99__calculator/test.code"
    else if (__switch_34_value__->variant == 2) {
#line 39 "tests/99__calculator/test.code"
        return test__evaluate__0_expression(__switch_34_value__->variant_2.left) + test__evaluate__0_expression(__switch_34_value__->variant_2.right);
    }
#line 41 "tests/99__calculator/test.code"
    else if (__switch_34_value__->variant == 3) {
#line 42 "tests/99__calculator/test.code"
        return test__evaluate__0_expression(__switch_34_value__->variant_3.left) / test__evaluate__0_expression(__switch_34_value__->variant_3.right);
    }
#line 44 "tests/99__calculator/test.code"
    else if (__switch_34_value__->variant == 4) {
#line 45 "tests/99__calculator/test.code"
        return test__evaluate__0_expression(__switch_34_value__->variant_4.left) * test__evaluate__0_expression(__switch_34_value__->variant_4.right);
    }
#line 47 "tests/99__calculator/test.code"
    else if (__switch_34_value__->variant == 5) {
#line 48 "tests/99__calculator/test.code"
        return test__evaluate__0_expression(__switch_34_value__->variant_5.left) - test__evaluate__0_expression(__switch_34_value__->variant_5.right);
    }
#line 50 "tests/99__calculator/test.code"
    else {
#line 51 "tests/99__calculator/test.code"
        exit(1);
    }
}

#line 62 "tests/99__calculator/test.code"
struct Expression test__pParser__parse_expression(struct Parser *self) {
#line 63 "tests/99__calculator/test.code"
    return test__pParser__parse_additive_expression(self);
}

#line 66 "tests/99__calculator/test.code"
struct Expression test__pParser__parse_additive_expression(struct Parser *self) {
#line 67 "tests/99__calculator/test.code"
    struct Expression expression = test__pParser__parse_multiplicative_expression(self);
#line 68 "tests/99__calculator/test.code"
    for (;;) {
#line 69 "tests/99__calculator/test.code"
        struct Token __switch_69_value__ = test__pTokenizer__peek_token(&self->tokenizer);
#line 70 "tests/99__calculator/test.code"
        if (__switch_69_value__.variant == 2) {
#line 71 "tests/99__calculator/test.code"
            test__pTokenizer__next_token(&self->tokenizer);
#line 72 "tests/99__calculator/test.code"
            struct Expression other_expression = test__pParser__parse_multiplicative_expression(self);
#line 73 "tests/99__calculator/test.code"
            expression = (struct Expression){.variant = 2, .variant_2 = (struct Addition){.span = (struct Span){.start = test__pExpression__span(&expression).start, .end = test__pExpression__span(&other_expression).end}, .left = __alloc_Expression_value(expression), .right = __alloc_Expression_value(other_expression)}};
        }
#line 79 "tests/99__calculator/test.code"
        else if (__switch_69_value__.variant == 3) {
#line 80 "tests/99__calculator/test.code"
            test__pTokenizer__next_token(&self->tokenizer);
#line 81 "tests/99__calculator/test.code"
            struct Expression other_expression = test__pParser__parse_multiplicative_expression(self);
#line 82 "tests/99__calculator/test.code"
            expression = (struct Expression){.variant = 5, .variant_5 = (struct Subtraction){.span = (struct Span){.start = test__pExpression__span(&expression).start, .end = test__pExpression__span(&other_expression).end}, .left = __alloc_Expression_value(expression), .right = __alloc_Expression_value(other_expression)}};
        }
#line 88 "tests/99__calculator/test.code"
        else {
#line 89 "tests/99__calculator/test.code"
            break;
        }
    }
#line 93 "tests/99__calculator/test.code"
    return expression;
}

#line 96 "tests/99__calculator/test.code"
struct Expression test__pParser__parse_multiplicative_expression(struct Parser *self) {
#line 97 "tests/99__calculator/test.code"
    struct Expression expression = test__pParser__parse_primary_expression(self);
#line 98 "tests/99__calculator/test.code"
    for (;;) {
#line 99 "tests/99__calculator/test.code"
        struct Token token = test__pTokenizer__peek_token(&self->tokenizer);
#line 100 "tests/99__calculator/test.code"
        if (token.variant == 4) {
#line 101 "tests/99__calculator/test.code"
            test__pTokenizer__next_token(&self->tokenizer);
#line 102 "tests/99__calculator/test.code"
            struct Expression other_expression = test__pParser__parse_primary_expression(self);
#line 103 "tests/99__calculator/test.code"
            expression = (struct Expression){.variant = 4, .variant_4 = (struct Multiplication){.span = (struct Span){.start = test__pExpression__span(&expression).start, .end = test__pExpression__span(&other_expression).end}, .left = __alloc_Expression_value(expression), .right = __alloc_Expression_value(other_expression)}};
        } else if (token.variant == 5) {
#line 109 "tests/99__calculator/test.code"
            test__pTokenizer__next_token(&self->tokenizer);
#line 110 "tests/99__calculator/test.code"
            struct Expression other_expression = test__pParser__parse_primary_expression(self);
#line 111 "tests/99__calculator/test.code"
            expression = (struct Expression){.variant = 3, .variant_3 = (struct Division){.span = (struct Span){.start = test__pExpression__span(&expression).start, .end = test__pExpression__span(&other_expression).end}, .left = __alloc_Expression_value(expression), .right = __alloc_Expression_value(other_expression)}};
        } else {
#line 117 "tests/99__calculator/test.code"
            break;
        }
    }
#line 120 "tests/99__calculator/test.code"
    return expression;
}

#line 123 "tests/99__calculator/test.code"
struct Expression test__pParser__parse_primary_expression(struct Parser *self) {
#line 124 "tests/99__calculator/test.code"
    struct Token token = test__pTokenizer__next_token(&self->tokenizer);
#line 125 "tests/99__calculator/test.code"
    if (token.variant == 1) {
#line 126 "tests/99__calculator/test.code"
        return (struct Expression){.variant = 1, .variant_1 = token.variant_1};
    }
#line 128 "tests/99__calculator/test.code"
    return (struct Expression){.variant = 6, .variant_6 = (struct Error){.span = test__pToken__span(&token), .message = (struct String){.data = "Expected number", .length = 15}}};
}

#line 169 "tests/99__calculator/test.code"
struct Span test__pExpression__span(struct Expression *self) {
#line 170 "tests/99__calculator/test.code"
    struct Expression *__switch_170_value__ = self;
#line 171 "tests/99__calculator/test.code"
    if (__switch_170_value__->variant == 1) {
#line 172 "tests/99__calculator/test.code"
        return __switch_170_value__->variant_1.span;
    }
#line 174 "tests/99__calculator/test.code"
    else if (__switch_170_value__->variant == 2) {
#line 175 "tests/99__calculator/test.code"
        return __switch_170_value__->variant_2.span;
    }
#line 177 "tests/99__calculator/test.code"
    else if (__switch_170_value__->variant == 3) {
#line 178 "tests/99__calculator/test.code"
        return __switch_170_value__->variant_3.span;
    }
#line 180 "tests/99__calculator/test.code"
    else if (__switch_170_value__->variant == 4) {
#line 181 "tests/99__calculator/test.code"
        return __switch_170_value__->variant_4.span;
    }
#line 183 "tests/99__calculator/test.code"
    else if (__switch_170_value__->variant == 5) {
#line 184 "tests/99__calculator/test.code"
        return __switch_170_value__->variant_5.span;
    }
#line 186 "tests/99__calculator/test.code"
    else if (__switch_170_value__->variant == 6) {
#line 187 "tests/99__calculator/test.code"
        return __switch_170_value__->variant_6.span;
    }
#line 189 "tests/99__calculator/test.code"
    else if (__switch_170_value__->variant == 0) {
#line 190 "tests/99__calculator/test.code"
        return (struct Span){.start = 0, .end = 0};
    }
}

#line 195 "tests/99__calculator/test.code"
struct Writer *test__pWriter__write__1_expression(struct Writer *self, struct Expression *expression) {
#line 196 "tests/99__calculator/test.code"
    struct Expression *__switch_196_value__ = expression;
#line 197 "tests/99__calculator/test.code"
    if (__switch_196_value__->variant == 1) {
#line 198 "tests/99__calculator/test.code"
        return test__pWriter__write__1_signed(self, __switch_196_value__->variant_1.value);
    }
#line 200 "tests/99__calculator/test.code"
    else if (__switch_196_value__->variant == 2) {
#line 201 "tests/99__calculator/test.code"
        return test__pWriter__write(test__pWriter__write__1_expression(test__pWriter__write(test__pWriter__write__1_expression(test__pWriter__write(self, (struct String){.data = "(", .length = 1}), __switch_196_value__->variant_2.left), (struct String){.data = " + ", .length = 3}), __switch_196_value__->variant_2.right), (struct String){.data = ")", .length = 1});
    }
#line 203 "tests/99__calculator/test.code"
    else if (__switch_196_value__->variant == 3) {
#line 204 "tests/99__calculator/test.code"
        return test__pWriter__write(test__pWriter__write__1_expression(test__pWriter__write(test__pWriter__write__1_expression(test__pWriter__write(self, (struct String){.data = "(", .length = 1}), __switch_196_value__->variant_3.left), (struct String){.data = " / ", .length = 3}), __switch_196_value__->variant_3.right), (struct String){.data = ")", .length = 1});
    }
#line 206 "tests/99__calculator/test.code"
    else if (__switch_196_value__->variant == 4) {
#line 207 "tests/99__calculator/test.code"
        return test__pWriter__write(test__pWriter__write__1_expression(test__pWriter__write(test__pWriter__write__1_expression(test__pWriter__write(self, (struct String){.data = "(", .length = 1}), __switch_196_value__->variant_4.left), (struct String){.data = " * ", .length = 3}), __switch_196_value__->variant_4.right), (struct String){.data = ")", .length = 1});
    }
#line 209 "tests/99__calculator/test.code"
    else if (__switch_196_value__->variant == 5) {
#line 210 "tests/99__calculator/test.code"
        return test__pWriter__write(test__pWriter__write__1_expression(test__pWriter__write(test__pWriter__write__1_expression(test__pWriter__write(self, (struct String){.data = "(", .length = 1}), __switch_196_value__->variant_5.left), (struct String){.data = " - ", .length = 3}), __switch_196_value__->variant_5.right), (struct String){.data = ")", .length = 1});
    }
#line 212 "tests/99__calculator/test.code"
    else if (__switch_196_value__->variant == 6) {
#line 213 "tests/99__calculator/test.code"
        return test__pWriter__write(test__pWriter__write(self, (struct String){.data = "Error: ", .length = 7}), __switch_196_value__->variant_6.message);
    }
#line 215 "tests/99__calculator/test.code"
    else if (__switch_196_value__->variant == 0) {
#line 216 "tests/99__calculator/test.code"
        return test__pWriter__write(self, (struct String){.data = "Nil!", .length = 4});
    }
#line 219 "tests/99__calculator/test.code"
    return self;
}

#line 231 "tests/99__calculator/test.code"
struct Token test__pTokenizer__peek_token(struct Tokenizer *self) {
#line 232 "tests/99__calculator/test.code"
    if (self->current_token.variant == 0) {
#line 233 "tests/99__calculator/test.code"
        self->current_token = test__pTokenizer__scan_token(self);
    }
#line 235 "tests/99__calculator/test.code"
    return self->current_token;
}

#line 238 "tests/99__calculator/test.code"
struct Token test__pTokenizer__next_token(struct Tokenizer *self) {
#line 239 "tests/99__calculator/test.code"
    struct Token token = test__pTokenizer__peek_token(self);
#line 240 "tests/99__calculator/test.code"
    self->current_token = (struct Token){.variant = 0};
#line 241 "tests/99__calculator/test.code"
    return token;
}

#line 244 "tests/99__calculator/test.code"
struct Token test__pTokenizer__scan_token(struct Tokenizer *self) {
#line 245 "tests/99__calculator/test.code"
    while (self->data[self->index] == ' ') {
#line 246 "tests/99__calculator/test.code"
        self->index = self->index + 1;
    }
#line 248 "tests/99__calculator/test.code"
    uint8_t ch = self->data[self->index];
#line 249 "tests/99__calculator/test.code"
    if (ch == 0) {
#line 250 "tests/99__calculator/test.code"
        return (struct Token){.variant = 6, .variant_6 = (struct Stop){.span = (struct Span){.start = self->index, .end = self->index}}};
    }
#line 252 "tests/99__calculator/test.code"
    if (ch >= '0' && ch <= '9') {
#line 253 "tests/99__calculator/test.code"
        return test__pTokenizer__scan_number_token(self);
    }
#line 255 "tests/99__calculator/test.code"
    self->index = self->index + 1;
#line 256 "tests/99__calculator/test.code"
    if (ch == '+') {
#line 257 "tests/99__calculator/test.code"
        return (struct Token){.variant = 2, .variant_2 = (struct Plus){.span = (struct Span){.start = self->index - 1, .end = self->index}}};
    }
#line 259 "tests/99__calculator/test.code"
    if (ch == '-') {
#line 260 "tests/99__calculator/test.code"
        return (struct Token){.variant = 3, .variant_3 = (struct Minus){.span = (struct Span){.start = self->index - 1, .end = self->index}}};
    }
#line 262 "tests/99__calculator/test.code"
    if (ch == '*') {
#line 263 "tests/99__calculator/test.code"
        return (struct Token){.variant = 4, .variant_4 = (struct Multiply){.span = (struct Span){.start = self->index - 1, .end = self->index}}};
    }
#line 265 "tests/99__calculator/test.code"
    if (ch == '/') {
#line 266 "tests/99__calculator/test.code"
        return (struct Token){.variant = 5, .variant_5 = (struct Divide){.span = (struct Span){.start = self->index - 1, .end = self->index}}};
    }
#line 268 "tests/99__calculator/test.code"
    return (struct Token){.variant = 7, .variant_7 = (struct Error){.span = (struct Span){.start = self->index - 1, .end = self->index}, .message = (struct String){.data = "Unexpected character", .length = 20}}};
}

#line 274 "tests/99__calculator/test.code"
struct Token test__pTokenizer__scan_number_token(struct Tokenizer *self) {
#line 275 "tests/99__calculator/test.code"
    int32_t start = self->index;
#line 276 "tests/99__calculator/test.code"
    int32_t value = 0;
#line 277 "tests/99__calculator/test.code"
    for (;;) {
#line 278 "tests/99__calculator/test.code"
        uint8_t c = self->data[self->index];
#line 279 "tests/99__calculator/test.code"
        if (c < '0' || c > '9') {
#line 280 "tests/99__calculator/test.code"
            break;
        }
#line 282 "tests/99__calculator/test.code"
        value = value * 10 + ((int32_t) (c - '0'));
#line 283 "tests/99__calculator/test.code"
        self->index = self->index + 1;
    }
#line 285 "tests/99__calculator/test.code"
    return (struct Token){.variant = 1, .variant_1 = (struct Number){.span = (struct Span){.start = start, .end = self->index}, .value = value}};
}

#line 339 "tests/99__calculator/test.code"
struct Span test__pToken__span(struct Token *self) {
#line 340 "tests/99__calculator/test.code"
    struct Token *__switch_340_value__ = self;
#line 341 "tests/99__calculator/test.code"
    if (__switch_340_value__->variant == 1) {
#line 342 "tests/99__calculator/test.code"
        return __switch_340_value__->variant_1.span;
    }
#line 344 "tests/99__calculator/test.code"
    else if (__switch_340_value__->variant == 2) {
#line 345 "tests/99__calculator/test.code"
        return __switch_340_value__->variant_2.span;
    }
#line 347 "tests/99__calculator/test.code"
    else if (__switch_340_value__->variant == 3) {
#line 348 "tests/99__calculator/test.code"
        return __switch_340_value__->variant_3.span;
    }
#line 350 "tests/99__calculator/test.code"
    else if (__switch_340_value__->variant == 4) {
#line 351 "tests/99__calculator/test.code"
        return __switch_340_value__->variant_4.span;
    }
#line 353 "tests/99__calculator/test.code"
    else if (__switch_340_value__->variant == 5) {
#line 354 "tests/99__calculator/test.code"
        return __switch_340_value__->variant_5.span;
    }
#line 356 "tests/99__calculator/test.code"
    else if (__switch_340_value__->variant == 6) {
#line 357 "tests/99__calculator/test.code"
        return __switch_340_value__->variant_6.span;
    }
#line 359 "tests/99__calculator/test.code"
    else if (__switch_340_value__->variant == 7) {
#line 360 "tests/99__calculator/test.code"
        return __switch_340_value__->variant_7.span;
    }
#line 362 "tests/99__calculator/test.code"
    else if (__switch_340_value__->variant == 0) {
#line 363 "tests/99__calculator/test.code"
        return (struct Span){.start = 0, .end = 0};
    }
}

#line 368 "tests/99__calculator/test.code"
struct Writer *test__pWriter__write__1_token(struct Writer *self, struct Token *token) {
#line 369 "tests/99__calculator/test.code"
    struct Token *__switch_369_value__ = token;
#line 370 "tests/99__calculator/test.code"
    if (__switch_369_value__->variant == 1) {
#line 371 "tests/99__calculator/test.code"
        return test__pWriter__write__1_signed(test__pWriter__write(self, (struct String){.data = "Number: ", .length = 8}), __switch_369_value__->variant_1.value);
    }
#line 373 "tests/99__calculator/test.code"
    else if (__switch_369_value__->variant == 2) {
#line 374 "tests/99__calculator/test.code"
        return test__pWriter__write(self, (struct String){.data = "Plus", .length = 4});
    }
#line 376 "tests/99__calculator/test.code"
    else if (__switch_369_value__->variant == 3) {
#line 377 "tests/99__calculator/test.code"
        return test__pWriter__write(self, (struct String){.data = "Minus", .length = 5});
    }
#line 379 "tests/99__calculator/test.code"
    else if (__switch_369_value__->variant == 4) {
#line 380 "tests/99__calculator/test.code"
        return test__pWriter__write(self, (struct String){.data = "Multiply", .length = 8});
    }
#line 382 "tests/99__calculator/test.code"
    else if (__switch_369_value__->variant == 5) {
#line 383 "tests/99__calculator/test.code"
        return test__pWriter__write(self, (struct String){.data = "Divide", .length = 6});
    }
#line 385 "tests/99__calculator/test.code"
    else if (__switch_369_value__->variant == 6) {
#line 386 "tests/99__calculator/test.code"
        return test__pWriter__write(self, (struct String){.data = "Stop", .length = 4});
    }
#line 388 "tests/99__calculator/test.code"
    else if (__switch_369_value__->variant == 7) {
#line 389 "tests/99__calculator/test.code"
        return test__pWriter__write(test__pWriter__write(self, (struct String){.data = "Error: ", .length = 7}), __switch_369_value__->variant_7.message);
    }
#line 391 "tests/99__calculator/test.code"
    else if (__switch_369_value__->variant == 0) {
#line 392 "tests/99__calculator/test.code"
        return test__pWriter__write(self, (struct String){.data = "Nil!", .length = 4});
    }
#line 395 "tests/99__calculator/test.code"
    return self;
}

#line 405 "tests/99__calculator/test.code"
struct Writer *test__pWriter__write__1_char(struct Writer *self, uint8_t c) {
#line 406 "tests/99__calculator/test.code"
    self->write_char(self->self, c);
#line 407 "tests/99__calculator/test.code"
    return self;
}

#line 410 "tests/99__calculator/test.code"
struct Writer *test__pWriter__write__1_signed(struct Writer *self, int32_t value) {
#line 412 "tests/99__calculator/test.code"
    if (value < 0) {
#line 413 "tests/99__calculator/test.code"
        test__pWriter__write__1_char(self, '-');
#line 414 "tests/99__calculator/test.code"
        return test__pWriter__write__1_signed(self, -value);
    }
#line 416 "tests/99__calculator/test.code"
    if (value >= 10) {
#line 417 "tests/99__calculator/test.code"
        test__pWriter__write__1_signed(self, value / 10);
    }
#line 419 "tests/99__calculator/test.code"
    return test__pWriter__write__1_char(self, ((uint8_t) (value % 10)) + '0');
}

#line 422 "tests/99__calculator/test.code"
struct Writer *test__pWriter__end_line(struct Writer *self) {
#line 423 "tests/99__calculator/test.code"
    test__pWriter__write__1_char(self, '\n');
#line 424 "tests/99__calculator/test.code"
    return self;
}

#line 435 "tests/99__calculator/test.code"
struct String_Builder *test__pString_Builder__write__1_char(struct String_Builder *self, uint8_t c) {
#line 436 "tests/99__calculator/test.code"
    if (self->length == self->data_size) {
#line 437 "tests/99__calculator/test.code"
        self->data_size = self->data_size + 8;
#line 438 "tests/99__calculator/test.code"
        self->data = ((uint8_t *) realloc(((void *) self->data), ((uint64_t) self->data_size)));
    }
#line 443 "tests/99__calculator/test.code"
    self->data[self->length] = c;
#line 444 "tests/99__calculator/test.code"
    self->length = self->length + 1;
#line 445 "tests/99__calculator/test.code"
    return self;
}

#line 448 "tests/99__calculator/test.code"
struct String test__pString_Builder__build(struct String_Builder *self) {
#line 449 "tests/99__calculator/test.code"
    test__pString_Builder__write__1_char(self, 0);
#line 450 "tests/99__calculator/test.code"
    struct String string = (struct String){.data = self->data, .length = self->length - 1};
#line 454 "tests/99__calculator/test.code"
    return *((struct String *) (&string));
}

#line 457 "tests/99__calculator/test.code"
struct String_Builder test__make_string_builder() {
#line 458 "tests/99__calculator/test.code"
    return test__make_string_builder__0_initial_data_size(4);
}

#line 461 "tests/99__calculator/test.code"
struct String_Builder test__make_string_builder__0_initial_data_size(int32_t initial_data_size) {
#line 462 "tests/99__calculator/test.code"
    return (struct String_Builder){.data = ((uint8_t *) malloc(((uint64_t) initial_data_size))), .data_size = initial_data_size, .length = 0};
}

#line 469 "tests/99__calculator/test.code"
void test__pString_Builder__write_char(struct String_Builder *self, uint8_t c) {
#line 470 "tests/99__calculator/test.code"
    test__pString_Builder__write__1_char(self, c);
}

#line 480 "tests/99__calculator/test.code"
struct Writer *test__pWriter__write(struct Writer *self, struct String string) {
#line 481 "tests/99__calculator/test.code"
    struct String string_copy = string;
#line 482 "tests/99__calculator/test.code"
    uint8_t *string_data = ((struct String *) (&string_copy))->data;
#line 483 "tests/99__calculator/test.code"
    uintmax_t index = 0;
#line 484 "tests/99__calculator/test.code"
    while (index < string.length) {
#line 485 "tests/99__calculator/test.code"
        test__pWriter__write__1_char(self, string_data[index]);
#line 486 "tests/99__calculator/test.code"
        index = index + 1;
    }
#line 488 "tests/99__calculator/test.code"
    return self;
}

#line 501 "tests/99__calculator/test.code"
void test__pFILE__write_char(FILE *self, uint8_t c) {
#line 502 "tests/99__calculator/test.code"
    fputc(((int32_t) c), __stdoutp);
}

