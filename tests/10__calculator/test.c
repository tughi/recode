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

extern FILE *stdin;
extern FILE *__stdoutp;
extern FILE *stderr;
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

#line 3 "tests/10__calculator/test.code"
int32_t test__main(int32_t argc, uint8_t **argv) {
#line 4 "tests/10__calculator/test.code"
    if (argc != 2) {
#line 5 "tests/10__calculator/test.code"
        exit(1);
    }
#line 8 "tests/10__calculator/test.code"
    struct Tokenizer tokenizer = (struct Tokenizer){.data = argv[1], .index = 0};
#line 13 "tests/10__calculator/test.code"
    struct Writer stdout_writer = (struct Writer){.self = __stdoutp, .write_char = ((void (*)(void *self, uint8_t c)) test__pFILE__write_char)};
#line 15 "tests/10__calculator/test.code"
    while (test__pTokenizer__peek_token(&tokenizer).variant != 6) {
#line 16 "tests/10__calculator/test.code"
        struct Token token = test__pTokenizer__next_token(&tokenizer);
#line 17 "tests/10__calculator/test.code"
        test__pWriter__end_line(test__pWriter__write__1_token(&stdout_writer, &token));
    }
#line 20 "tests/10__calculator/test.code"
    struct Parser parser = (struct Parser){.tokenizer = (struct Tokenizer){.data = argv[1], .index = 0}};
#line 24 "tests/10__calculator/test.code"
    struct Expression expression = test__pParser__parse_expression(&parser);
#line 25 "tests/10__calculator/test.code"
    test__pWriter__end_line(test__pWriter__write__1_expression(test__pWriter__write(&stdout_writer, (struct String){.data = "Expression: ", .length = 12}), &expression));
#line 27 "tests/10__calculator/test.code"
    int32_t result = test__evaluate__0_expression(&expression);
#line 28 "tests/10__calculator/test.code"
    test__pWriter__end_line(test__pWriter__write__1_signed(test__pWriter__write(&stdout_writer, (struct String){.data = "Result: ", .length = 8}), result));
#line 30 "tests/10__calculator/test.code"
    return 0;
}

#line 35 "tests/10__calculator/test.code"
int32_t test__evaluate__0_expression(struct Expression *expression) {
#line 36 "tests/10__calculator/test.code"
    struct Expression *__switch_36_value__ = expression;
#line 37 "tests/10__calculator/test.code"
    if (__switch_36_value__->variant == 1) {
#line 38 "tests/10__calculator/test.code"
        return __switch_36_value__->variant_1.value;
    }
#line 40 "tests/10__calculator/test.code"
    else if (__switch_36_value__->variant == 2) {
#line 41 "tests/10__calculator/test.code"
        return test__evaluate__0_expression(__switch_36_value__->variant_2.left) + test__evaluate__0_expression(__switch_36_value__->variant_2.right);
    }
#line 43 "tests/10__calculator/test.code"
    else if (__switch_36_value__->variant == 3) {
#line 44 "tests/10__calculator/test.code"
        return test__evaluate__0_expression(__switch_36_value__->variant_3.left) / test__evaluate__0_expression(__switch_36_value__->variant_3.right);
    }
#line 46 "tests/10__calculator/test.code"
    else if (__switch_36_value__->variant == 4) {
#line 47 "tests/10__calculator/test.code"
        return test__evaluate__0_expression(__switch_36_value__->variant_4.left) * test__evaluate__0_expression(__switch_36_value__->variant_4.right);
    }
#line 49 "tests/10__calculator/test.code"
    else if (__switch_36_value__->variant == 5) {
#line 50 "tests/10__calculator/test.code"
        return test__evaluate__0_expression(__switch_36_value__->variant_5.left) - test__evaluate__0_expression(__switch_36_value__->variant_5.right);
    }
#line 52 "tests/10__calculator/test.code"
    else {
#line 53 "tests/10__calculator/test.code"
        exit(1);
    }
}

#line 64 "tests/10__calculator/test.code"
struct Expression test__pParser__parse_expression(struct Parser *self) {
#line 65 "tests/10__calculator/test.code"
    return test__pParser__parse_additive_expression(self);
}

#line 68 "tests/10__calculator/test.code"
struct Expression test__pParser__parse_additive_expression(struct Parser *self) {
#line 69 "tests/10__calculator/test.code"
    struct Expression expression = test__pParser__parse_multiplicative_expression(self);
#line 70 "tests/10__calculator/test.code"
    for (;;) {
#line 71 "tests/10__calculator/test.code"
        struct Token __switch_71_value__ = test__pTokenizer__peek_token(&self->tokenizer);
#line 72 "tests/10__calculator/test.code"
        if (__switch_71_value__.variant == 2) {
#line 73 "tests/10__calculator/test.code"
            test__pTokenizer__next_token(&self->tokenizer);
#line 74 "tests/10__calculator/test.code"
            struct Expression other_expression = test__pParser__parse_multiplicative_expression(self);
#line 75 "tests/10__calculator/test.code"
            expression = (struct Expression){.variant = 2, .variant_2 = (struct Addition){.span = (struct Span){.start = test__pExpression__span(&expression).start, .end = test__pExpression__span(&other_expression).end}, .left = __alloc_Expression_value(expression), .right = __alloc_Expression_value(other_expression)}};
        }
#line 81 "tests/10__calculator/test.code"
        else if (__switch_71_value__.variant == 3) {
#line 82 "tests/10__calculator/test.code"
            test__pTokenizer__next_token(&self->tokenizer);
#line 83 "tests/10__calculator/test.code"
            struct Expression other_expression = test__pParser__parse_multiplicative_expression(self);
#line 84 "tests/10__calculator/test.code"
            expression = (struct Expression){.variant = 5, .variant_5 = (struct Subtraction){.span = (struct Span){.start = test__pExpression__span(&expression).start, .end = test__pExpression__span(&other_expression).end}, .left = __alloc_Expression_value(expression), .right = __alloc_Expression_value(other_expression)}};
        }
#line 90 "tests/10__calculator/test.code"
        else {
#line 91 "tests/10__calculator/test.code"
            break;
        }
    }
#line 95 "tests/10__calculator/test.code"
    return expression;
}

#line 98 "tests/10__calculator/test.code"
struct Expression test__pParser__parse_multiplicative_expression(struct Parser *self) {
#line 99 "tests/10__calculator/test.code"
    struct Expression expression = test__pParser__parse_primary_expression(self);
#line 100 "tests/10__calculator/test.code"
    for (;;) {
#line 101 "tests/10__calculator/test.code"
        struct Token token = test__pTokenizer__peek_token(&self->tokenizer);
#line 102 "tests/10__calculator/test.code"
        if (token.variant == 4) {
#line 103 "tests/10__calculator/test.code"
            test__pTokenizer__next_token(&self->tokenizer);
#line 104 "tests/10__calculator/test.code"
            struct Expression other_expression = test__pParser__parse_primary_expression(self);
#line 105 "tests/10__calculator/test.code"
            expression = (struct Expression){.variant = 4, .variant_4 = (struct Multiplication){.span = (struct Span){.start = test__pExpression__span(&expression).start, .end = test__pExpression__span(&other_expression).end}, .left = __alloc_Expression_value(expression), .right = __alloc_Expression_value(other_expression)}};
        } else if (token.variant == 5) {
#line 111 "tests/10__calculator/test.code"
            test__pTokenizer__next_token(&self->tokenizer);
#line 112 "tests/10__calculator/test.code"
            struct Expression other_expression = test__pParser__parse_primary_expression(self);
#line 113 "tests/10__calculator/test.code"
            expression = (struct Expression){.variant = 3, .variant_3 = (struct Division){.span = (struct Span){.start = test__pExpression__span(&expression).start, .end = test__pExpression__span(&other_expression).end}, .left = __alloc_Expression_value(expression), .right = __alloc_Expression_value(other_expression)}};
        } else {
#line 119 "tests/10__calculator/test.code"
            break;
        }
    }
#line 122 "tests/10__calculator/test.code"
    return expression;
}

#line 125 "tests/10__calculator/test.code"
struct Expression test__pParser__parse_primary_expression(struct Parser *self) {
#line 126 "tests/10__calculator/test.code"
    struct Token token = test__pTokenizer__next_token(&self->tokenizer);
#line 127 "tests/10__calculator/test.code"
    if (token.variant == 1) {
#line 128 "tests/10__calculator/test.code"
        return (struct Expression){.variant = 1, .variant_1 = token.variant_1};
    }
#line 130 "tests/10__calculator/test.code"
    return (struct Expression){.variant = 6, .variant_6 = (struct Error){.span = test__pToken__span(&token), .message = (struct String){.data = "Expected number", .length = 15}}};
}

#line 171 "tests/10__calculator/test.code"
struct Span test__pExpression__span(struct Expression *self) {
#line 172 "tests/10__calculator/test.code"
    struct Expression *__switch_172_value__ = self;
#line 173 "tests/10__calculator/test.code"
    if (__switch_172_value__->variant == 1) {
#line 174 "tests/10__calculator/test.code"
        return __switch_172_value__->variant_1.span;
    }
#line 176 "tests/10__calculator/test.code"
    else if (__switch_172_value__->variant == 2) {
#line 177 "tests/10__calculator/test.code"
        return __switch_172_value__->variant_2.span;
    }
#line 179 "tests/10__calculator/test.code"
    else if (__switch_172_value__->variant == 3) {
#line 180 "tests/10__calculator/test.code"
        return __switch_172_value__->variant_3.span;
    }
#line 182 "tests/10__calculator/test.code"
    else if (__switch_172_value__->variant == 4) {
#line 183 "tests/10__calculator/test.code"
        return __switch_172_value__->variant_4.span;
    }
#line 185 "tests/10__calculator/test.code"
    else if (__switch_172_value__->variant == 5) {
#line 186 "tests/10__calculator/test.code"
        return __switch_172_value__->variant_5.span;
    }
#line 188 "tests/10__calculator/test.code"
    else if (__switch_172_value__->variant == 6) {
#line 189 "tests/10__calculator/test.code"
        return __switch_172_value__->variant_6.span;
    }
#line 191 "tests/10__calculator/test.code"
    else if (__switch_172_value__->variant == 0) {
#line 192 "tests/10__calculator/test.code"
        return (struct Span){.start = 0, .end = 0};
    }
}

#line 197 "tests/10__calculator/test.code"
struct Writer *test__pWriter__write__1_expression(struct Writer *self, struct Expression *expression) {
#line 198 "tests/10__calculator/test.code"
    struct Expression *__switch_198_value__ = expression;
#line 199 "tests/10__calculator/test.code"
    if (__switch_198_value__->variant == 1) {
#line 200 "tests/10__calculator/test.code"
        return test__pWriter__write__1_signed(self, __switch_198_value__->variant_1.value);
    }
#line 202 "tests/10__calculator/test.code"
    else if (__switch_198_value__->variant == 2) {
#line 203 "tests/10__calculator/test.code"
        return test__pWriter__write(test__pWriter__write__1_expression(test__pWriter__write(test__pWriter__write__1_expression(test__pWriter__write(self, (struct String){.data = "(", .length = 1}), __switch_198_value__->variant_2.left), (struct String){.data = " + ", .length = 3}), __switch_198_value__->variant_2.right), (struct String){.data = ")", .length = 1});
    }
#line 205 "tests/10__calculator/test.code"
    else if (__switch_198_value__->variant == 3) {
#line 206 "tests/10__calculator/test.code"
        return test__pWriter__write(test__pWriter__write__1_expression(test__pWriter__write(test__pWriter__write__1_expression(test__pWriter__write(self, (struct String){.data = "(", .length = 1}), __switch_198_value__->variant_3.left), (struct String){.data = " / ", .length = 3}), __switch_198_value__->variant_3.right), (struct String){.data = ")", .length = 1});
    }
#line 208 "tests/10__calculator/test.code"
    else if (__switch_198_value__->variant == 4) {
#line 209 "tests/10__calculator/test.code"
        return test__pWriter__write(test__pWriter__write__1_expression(test__pWriter__write(test__pWriter__write__1_expression(test__pWriter__write(self, (struct String){.data = "(", .length = 1}), __switch_198_value__->variant_4.left), (struct String){.data = " * ", .length = 3}), __switch_198_value__->variant_4.right), (struct String){.data = ")", .length = 1});
    }
#line 211 "tests/10__calculator/test.code"
    else if (__switch_198_value__->variant == 5) {
#line 212 "tests/10__calculator/test.code"
        return test__pWriter__write(test__pWriter__write__1_expression(test__pWriter__write(test__pWriter__write__1_expression(test__pWriter__write(self, (struct String){.data = "(", .length = 1}), __switch_198_value__->variant_5.left), (struct String){.data = " - ", .length = 3}), __switch_198_value__->variant_5.right), (struct String){.data = ")", .length = 1});
    }
#line 214 "tests/10__calculator/test.code"
    else if (__switch_198_value__->variant == 6) {
#line 215 "tests/10__calculator/test.code"
        return test__pWriter__write(test__pWriter__write(self, (struct String){.data = "Error: ", .length = 7}), __switch_198_value__->variant_6.message);
    }
#line 217 "tests/10__calculator/test.code"
    else if (__switch_198_value__->variant == 0) {
#line 218 "tests/10__calculator/test.code"
        return test__pWriter__write(self, (struct String){.data = "Nil!", .length = 4});
    }
#line 221 "tests/10__calculator/test.code"
    return self;
}

#line 233 "tests/10__calculator/test.code"
struct Token test__pTokenizer__peek_token(struct Tokenizer *self) {
#line 234 "tests/10__calculator/test.code"
    if (self->current_token.variant == 0) {
#line 235 "tests/10__calculator/test.code"
        self->current_token = test__pTokenizer__scan_token(self);
    }
#line 237 "tests/10__calculator/test.code"
    return self->current_token;
}

#line 240 "tests/10__calculator/test.code"
struct Token test__pTokenizer__next_token(struct Tokenizer *self) {
#line 241 "tests/10__calculator/test.code"
    struct Token token = test__pTokenizer__peek_token(self);
#line 242 "tests/10__calculator/test.code"
    self->current_token = (struct Token){.variant = 0};
#line 243 "tests/10__calculator/test.code"
    return token;
}

#line 246 "tests/10__calculator/test.code"
struct Token test__pTokenizer__scan_token(struct Tokenizer *self) {
#line 247 "tests/10__calculator/test.code"
    while (self->data[self->index] == ' ') {
#line 248 "tests/10__calculator/test.code"
        self->index = self->index + 1;
    }
#line 250 "tests/10__calculator/test.code"
    uint8_t ch = self->data[self->index];
#line 251 "tests/10__calculator/test.code"
    if (ch == 0) {
#line 252 "tests/10__calculator/test.code"
        return (struct Token){.variant = 6, .variant_6 = (struct Stop){.span = (struct Span){.start = self->index, .end = self->index}}};
    }
#line 254 "tests/10__calculator/test.code"
    if (ch != ' ') {
#line 255 "tests/10__calculator/test.code"
        if (ch >= '0' && ch <= '9') {
#line 256 "tests/10__calculator/test.code"
            return test__pTokenizer__scan_number_token(self);
        }
#line 258 "tests/10__calculator/test.code"
        self->index = self->index + 1;
#line 259 "tests/10__calculator/test.code"
        if (ch == '+') {
#line 260 "tests/10__calculator/test.code"
            return (struct Token){.variant = 2, .variant_2 = (struct Plus){.span = (struct Span){.start = self->index - 1, .end = self->index}}};
        }
#line 262 "tests/10__calculator/test.code"
        if (ch == '-') {
#line 263 "tests/10__calculator/test.code"
            return (struct Token){.variant = 3, .variant_3 = (struct Minus){.span = (struct Span){.start = self->index - 1, .end = self->index}}};
        }
#line 265 "tests/10__calculator/test.code"
        if (ch == '*') {
#line 266 "tests/10__calculator/test.code"
            return (struct Token){.variant = 4, .variant_4 = (struct Multiply){.span = (struct Span){.start = self->index - 1, .end = self->index}}};
        }
#line 268 "tests/10__calculator/test.code"
        if (ch == '/') {
#line 269 "tests/10__calculator/test.code"
            return (struct Token){.variant = 5, .variant_5 = (struct Divide){.span = (struct Span){.start = self->index - 1, .end = self->index}}};
        }
#line 271 "tests/10__calculator/test.code"
        return (struct Token){.variant = 7, .variant_7 = (struct Error){.span = (struct Span){.start = self->index - 1, .end = self->index}, .message = (struct String){.data = "Unexpected character", .length = 20}}};
    }
}

#line 278 "tests/10__calculator/test.code"
struct Token test__pTokenizer__scan_number_token(struct Tokenizer *self) {
#line 279 "tests/10__calculator/test.code"
    int32_t start = self->index;
#line 280 "tests/10__calculator/test.code"
    int32_t value = 0;
#line 281 "tests/10__calculator/test.code"
    for (;;) {
#line 282 "tests/10__calculator/test.code"
        uint8_t c = self->data[self->index];
#line 283 "tests/10__calculator/test.code"
        if (c < '0' || c > '9') {
#line 284 "tests/10__calculator/test.code"
            break;
        }
#line 286 "tests/10__calculator/test.code"
        value = value * 10 + ((int32_t) (c - '0'));
#line 287 "tests/10__calculator/test.code"
        self->index = self->index + 1;
    }
#line 289 "tests/10__calculator/test.code"
    return (struct Token){.variant = 1, .variant_1 = (struct Number){.span = (struct Span){.start = start, .end = self->index}, .value = value}};
}

#line 343 "tests/10__calculator/test.code"
struct Span test__pToken__span(struct Token *self) {
#line 344 "tests/10__calculator/test.code"
    struct Token *__switch_344_value__ = self;
#line 345 "tests/10__calculator/test.code"
    if (__switch_344_value__->variant == 1) {
#line 346 "tests/10__calculator/test.code"
        return __switch_344_value__->variant_1.span;
    }
#line 348 "tests/10__calculator/test.code"
    else if (__switch_344_value__->variant == 2) {
#line 349 "tests/10__calculator/test.code"
        return __switch_344_value__->variant_2.span;
    }
#line 351 "tests/10__calculator/test.code"
    else if (__switch_344_value__->variant == 3) {
#line 352 "tests/10__calculator/test.code"
        return __switch_344_value__->variant_3.span;
    }
#line 354 "tests/10__calculator/test.code"
    else if (__switch_344_value__->variant == 4) {
#line 355 "tests/10__calculator/test.code"
        return __switch_344_value__->variant_4.span;
    }
#line 357 "tests/10__calculator/test.code"
    else if (__switch_344_value__->variant == 5) {
#line 358 "tests/10__calculator/test.code"
        return __switch_344_value__->variant_5.span;
    }
#line 360 "tests/10__calculator/test.code"
    else if (__switch_344_value__->variant == 6) {
#line 361 "tests/10__calculator/test.code"
        return __switch_344_value__->variant_6.span;
    }
#line 363 "tests/10__calculator/test.code"
    else if (__switch_344_value__->variant == 7) {
#line 364 "tests/10__calculator/test.code"
        return __switch_344_value__->variant_7.span;
    }
#line 366 "tests/10__calculator/test.code"
    else if (__switch_344_value__->variant == 0) {
#line 367 "tests/10__calculator/test.code"
        return (struct Span){.start = 0, .end = 0};
    }
}

#line 372 "tests/10__calculator/test.code"
struct Writer *test__pWriter__write__1_token(struct Writer *self, struct Token *token) {
#line 373 "tests/10__calculator/test.code"
    struct Token *__switch_373_value__ = token;
#line 374 "tests/10__calculator/test.code"
    if (__switch_373_value__->variant == 1) {
#line 375 "tests/10__calculator/test.code"
        return test__pWriter__write__1_signed(test__pWriter__write(self, (struct String){.data = "Number: ", .length = 8}), __switch_373_value__->variant_1.value);
    }
#line 377 "tests/10__calculator/test.code"
    else if (__switch_373_value__->variant == 2) {
#line 378 "tests/10__calculator/test.code"
        return test__pWriter__write(self, (struct String){.data = "Plus", .length = 4});
    }
#line 380 "tests/10__calculator/test.code"
    else if (__switch_373_value__->variant == 3) {
#line 381 "tests/10__calculator/test.code"
        return test__pWriter__write(self, (struct String){.data = "Minus", .length = 5});
    }
#line 383 "tests/10__calculator/test.code"
    else if (__switch_373_value__->variant == 4) {
#line 384 "tests/10__calculator/test.code"
        return test__pWriter__write(self, (struct String){.data = "Multiply", .length = 8});
    }
#line 386 "tests/10__calculator/test.code"
    else if (__switch_373_value__->variant == 5) {
#line 387 "tests/10__calculator/test.code"
        return test__pWriter__write(self, (struct String){.data = "Divide", .length = 6});
    }
#line 389 "tests/10__calculator/test.code"
    else if (__switch_373_value__->variant == 6) {
#line 390 "tests/10__calculator/test.code"
        return test__pWriter__write(self, (struct String){.data = "Stop", .length = 4});
    }
#line 392 "tests/10__calculator/test.code"
    else if (__switch_373_value__->variant == 7) {
#line 393 "tests/10__calculator/test.code"
        return test__pWriter__write(test__pWriter__write(self, (struct String){.data = "Error: ", .length = 7}), __switch_373_value__->variant_7.message);
    }
#line 395 "tests/10__calculator/test.code"
    else if (__switch_373_value__->variant == 0) {
#line 396 "tests/10__calculator/test.code"
        return test__pWriter__write(self, (struct String){.data = "Nil!", .length = 4});
    }
#line 399 "tests/10__calculator/test.code"
    return self;
}

#line 409 "tests/10__calculator/test.code"
struct Writer *test__pWriter__write__1_char(struct Writer *self, uint8_t c) {
#line 410 "tests/10__calculator/test.code"
    self->write_char(self->self, c);
#line 411 "tests/10__calculator/test.code"
    return self;
}

#line 414 "tests/10__calculator/test.code"
struct Writer *test__pWriter__write__1_signed(struct Writer *self, int32_t value) {
#line 416 "tests/10__calculator/test.code"
    if (value < 0) {
#line 417 "tests/10__calculator/test.code"
        test__pWriter__write__1_char(self, '-');
#line 418 "tests/10__calculator/test.code"
        return test__pWriter__write__1_signed(self, -value);
    }
#line 420 "tests/10__calculator/test.code"
    if (value >= 10) {
#line 421 "tests/10__calculator/test.code"
        test__pWriter__write__1_signed(self, value / 10);
    }
#line 423 "tests/10__calculator/test.code"
    return test__pWriter__write__1_char(self, ((uint8_t) (value % 10)) + '0');
}

#line 426 "tests/10__calculator/test.code"
struct Writer *test__pWriter__end_line(struct Writer *self) {
#line 427 "tests/10__calculator/test.code"
    test__pWriter__write__1_char(self, '\n');
#line 428 "tests/10__calculator/test.code"
    return self;
}

#line 439 "tests/10__calculator/test.code"
struct String_Builder *test__pString_Builder__write__1_char(struct String_Builder *self, uint8_t c) {
#line 440 "tests/10__calculator/test.code"
    if (self->length == self->data_size) {
#line 441 "tests/10__calculator/test.code"
        self->data_size = self->data_size + 8;
#line 442 "tests/10__calculator/test.code"
        self->data = ((uint8_t *) realloc(((void *) self->data), ((uint64_t) self->data_size)));
    }
#line 447 "tests/10__calculator/test.code"
    self->data[self->length] = c;
#line 448 "tests/10__calculator/test.code"
    self->length = self->length + 1;
#line 449 "tests/10__calculator/test.code"
    return self;
}

#line 452 "tests/10__calculator/test.code"
struct String test__pString_Builder__build(struct String_Builder *self) {
#line 453 "tests/10__calculator/test.code"
    test__pString_Builder__write__1_char(self, 0);
#line 454 "tests/10__calculator/test.code"
    struct String string = (struct String){.data = self->data, .length = self->length - 1};
#line 458 "tests/10__calculator/test.code"
    return *((struct String *) (&string));
}

#line 461 "tests/10__calculator/test.code"
struct String_Builder test__make_string_builder() {
#line 462 "tests/10__calculator/test.code"
    return test__make_string_builder__0_initial_data_size(4);
}

#line 465 "tests/10__calculator/test.code"
struct String_Builder test__make_string_builder__0_initial_data_size(int32_t initial_data_size) {
#line 466 "tests/10__calculator/test.code"
    return (struct String_Builder){.data = ((uint8_t *) malloc(((uint64_t) initial_data_size))), .data_size = initial_data_size, .length = 0};
}

#line 473 "tests/10__calculator/test.code"
void test__pString_Builder__write_char(struct String_Builder *self, uint8_t c) {
#line 474 "tests/10__calculator/test.code"
    test__pString_Builder__write__1_char(self, c);
}

#line 484 "tests/10__calculator/test.code"
struct Writer *test__pWriter__write(struct Writer *self, struct String string) {
#line 485 "tests/10__calculator/test.code"
    struct String string_copy = string;
#line 486 "tests/10__calculator/test.code"
    uint8_t *string_data = ((struct String *) (&string_copy))->data;
#line 487 "tests/10__calculator/test.code"
    uintmax_t index = 0;
#line 488 "tests/10__calculator/test.code"
    while (index < string.length) {
#line 489 "tests/10__calculator/test.code"
        test__pWriter__write__1_char(self, string_data[index]);
#line 490 "tests/10__calculator/test.code"
        index = index + 1;
    }
#line 492 "tests/10__calculator/test.code"
    return self;
}

#line 505 "tests/10__calculator/test.code"
void test__pFILE__write_char(FILE *self, uint8_t c) {
#line 506 "tests/10__calculator/test.code"
    fputc(((int32_t) c), __stdoutp);
}

