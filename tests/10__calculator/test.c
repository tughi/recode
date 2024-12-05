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
extern FILE *stdout;
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

void main(int32_t argc, uint8_t **argv);

int32_t evaluate__0_expression(struct Expression *expression);

struct Expression pParser__parse_expression(struct Parser *self);

struct Expression pParser__parse_additive_expression(struct Parser *self);

struct Expression pParser__parse_multiplicative_expression(struct Parser *self);

struct Expression pParser__parse_primary_expression(struct Parser *self);

struct Span pExpression__span(struct Expression *self);

struct Writer *pWriter__write__1_expression(struct Writer *self, struct Expression *expression);

struct Token pTokenizer__peek_token(struct Tokenizer *self);

struct Token pTokenizer__next_token(struct Tokenizer *self);

struct Token pTokenizer__scan_token(struct Tokenizer *self);

struct Token pTokenizer__scan_number_token(struct Tokenizer *self);

struct Span pToken__span(struct Token *self);

struct Writer *pWriter__write__1_token(struct Writer *self, struct Token *token);

struct Writer *pWriter__write__1_char(struct Writer *self, uint8_t c);

struct Writer *pWriter__write__1_signed(struct Writer *self, int32_t value);

struct Writer *pWriter__end_line(struct Writer *self);

struct String_Builder *pString_Builder__write__1_char(struct String_Builder *self, uint8_t c);

struct String pString_Builder__build(struct String_Builder *self);

struct String_Builder make_string_builder();

struct String_Builder make_string_builder__0_initial_data_size(int32_t initial_data_size);

void pString_Builder__write_char(struct String_Builder *self, uint8_t c);

struct Writer *pWriter__write(struct Writer *self, struct String string);

int32_t fputc(int32_t c, FILE *file);

void pFILE__write_char(FILE *self, uint8_t c);

void *malloc(uint64_t size);

void *realloc(void *block, uint64_t size);

void exit(int32_t code);

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

#line 1 "tests/10__calculator/test.code"
void main(int32_t argc, uint8_t **argv) {
#line 2 "tests/10__calculator/test.code"
    if (argc != 2) {
#line 3 "tests/10__calculator/test.code"
        exit(1);
    }
#line 6 "tests/10__calculator/test.code"
    struct Tokenizer tokenizer = (struct Tokenizer){.data = argv[1], .index = 0};
#line 11 "tests/10__calculator/test.code"
    struct Writer stdout_writer = (struct Writer){.self = stdout, .write_char = ((void (*)(void *self, uint8_t c)) pFILE__write_char)};
#line 13 "tests/10__calculator/test.code"
    while (pTokenizer__peek_token(&tokenizer).variant != 6) {
#line 14 "tests/10__calculator/test.code"
        struct Token token = pTokenizer__next_token(&tokenizer);
#line 15 "tests/10__calculator/test.code"
        pWriter__end_line(pWriter__write__1_token(&stdout_writer, &token));
    }
#line 18 "tests/10__calculator/test.code"
    struct Parser parser = (struct Parser){.tokenizer = (struct Tokenizer){.data = argv[1], .index = 0}};
#line 22 "tests/10__calculator/test.code"
    struct Expression expression = pParser__parse_expression(&parser);
#line 23 "tests/10__calculator/test.code"
    pWriter__end_line(pWriter__write__1_expression(pWriter__write(&stdout_writer, (struct String){.data = "Expression: ", .length = 12}), &expression));
#line 25 "tests/10__calculator/test.code"
    int32_t result = evaluate__0_expression(&expression);
#line 26 "tests/10__calculator/test.code"
    pWriter__end_line(pWriter__write__1_signed(pWriter__write(&stdout_writer, (struct String){.data = "Result: ", .length = 8}), result));
}

#line 31 "tests/10__calculator/test.code"
int32_t evaluate__0_expression(struct Expression *expression) {
#line 32 "tests/10__calculator/test.code"
    while (false) {
    }
#line 33 "tests/10__calculator/test.code"
    if (expression->variant == 1) {
#line 34 "tests/10__calculator/test.code"
        return expression->variant_1.value;
    }
#line 36 "tests/10__calculator/test.code"
    else if (expression->variant == 2) {
#line 37 "tests/10__calculator/test.code"
        return evaluate__0_expression(expression->variant_2.left) + evaluate__0_expression(expression->variant_2.right);
    }
#line 39 "tests/10__calculator/test.code"
    else if (expression->variant == 3) {
#line 40 "tests/10__calculator/test.code"
        return evaluate__0_expression(expression->variant_3.left) / evaluate__0_expression(expression->variant_3.right);
    }
#line 42 "tests/10__calculator/test.code"
    else if (expression->variant == 4) {
#line 43 "tests/10__calculator/test.code"
        return evaluate__0_expression(expression->variant_4.left) * evaluate__0_expression(expression->variant_4.right);
    }
#line 45 "tests/10__calculator/test.code"
    else if (expression->variant == 5) {
#line 46 "tests/10__calculator/test.code"
        return evaluate__0_expression(expression->variant_5.left) - evaluate__0_expression(expression->variant_5.right);
    }
#line 48 "tests/10__calculator/test.code"
     else {
#line 49 "tests/10__calculator/test.code"
        exit(1);
    }
}

#line 60 "tests/10__calculator/test.code"
struct Expression pParser__parse_expression(struct Parser *self) {
#line 61 "tests/10__calculator/test.code"
    return pParser__parse_additive_expression(self);
}

#line 64 "tests/10__calculator/test.code"
struct Expression pParser__parse_additive_expression(struct Parser *self) {
#line 65 "tests/10__calculator/test.code"
    struct Expression expression = pParser__parse_multiplicative_expression(self);
#line 66 "tests/10__calculator/test.code"
    for (;;) {
#line 67 "tests/10__calculator/test.code"
        struct Token token = pTokenizer__peek_token(&self->tokenizer);
#line 68 "tests/10__calculator/test.code"
        if (token.variant == 2) {
#line 69 "tests/10__calculator/test.code"
            pTokenizer__next_token(&self->tokenizer);
#line 70 "tests/10__calculator/test.code"
            struct Expression other_expression = pParser__parse_multiplicative_expression(self);
#line 71 "tests/10__calculator/test.code"
            expression = (struct Expression){.variant = 2, .variant_2 = (struct Addition){.span = (struct Span){.start = pExpression__span(&expression).start, .end = pExpression__span(&other_expression).end}, .left = __alloc_Expression_value(expression), .right = __alloc_Expression_value(other_expression)}};
        } else if (token.variant == 3) {
#line 77 "tests/10__calculator/test.code"
            pTokenizer__next_token(&self->tokenizer);
#line 78 "tests/10__calculator/test.code"
            struct Expression other_expression = pParser__parse_multiplicative_expression(self);
#line 79 "tests/10__calculator/test.code"
            expression = (struct Expression){.variant = 5, .variant_5 = (struct Subtraction){.span = (struct Span){.start = pExpression__span(&expression).start, .end = pExpression__span(&other_expression).end}, .left = __alloc_Expression_value(expression), .right = __alloc_Expression_value(other_expression)}};
        } else {
#line 85 "tests/10__calculator/test.code"
            break;
        }
    }
#line 88 "tests/10__calculator/test.code"
    return expression;
}

#line 91 "tests/10__calculator/test.code"
struct Expression pParser__parse_multiplicative_expression(struct Parser *self) {
#line 92 "tests/10__calculator/test.code"
    struct Expression expression = pParser__parse_primary_expression(self);
#line 93 "tests/10__calculator/test.code"
    for (;;) {
#line 94 "tests/10__calculator/test.code"
        struct Token token = pTokenizer__peek_token(&self->tokenizer);
#line 95 "tests/10__calculator/test.code"
        if (token.variant == 4) {
#line 96 "tests/10__calculator/test.code"
            pTokenizer__next_token(&self->tokenizer);
#line 97 "tests/10__calculator/test.code"
            struct Expression other_expression = pParser__parse_primary_expression(self);
#line 98 "tests/10__calculator/test.code"
            expression = (struct Expression){.variant = 4, .variant_4 = (struct Multiplication){.span = (struct Span){.start = pExpression__span(&expression).start, .end = pExpression__span(&other_expression).end}, .left = __alloc_Expression_value(expression), .right = __alloc_Expression_value(other_expression)}};
        } else if (token.variant == 5) {
#line 104 "tests/10__calculator/test.code"
            pTokenizer__next_token(&self->tokenizer);
#line 105 "tests/10__calculator/test.code"
            struct Expression other_expression = pParser__parse_primary_expression(self);
#line 106 "tests/10__calculator/test.code"
            expression = (struct Expression){.variant = 3, .variant_3 = (struct Division){.span = (struct Span){.start = pExpression__span(&expression).start, .end = pExpression__span(&other_expression).end}, .left = __alloc_Expression_value(expression), .right = __alloc_Expression_value(other_expression)}};
        } else {
#line 112 "tests/10__calculator/test.code"
            break;
        }
    }
#line 115 "tests/10__calculator/test.code"
    return expression;
}

#line 118 "tests/10__calculator/test.code"
struct Expression pParser__parse_primary_expression(struct Parser *self) {
#line 119 "tests/10__calculator/test.code"
    struct Token token = pTokenizer__next_token(&self->tokenizer);
#line 120 "tests/10__calculator/test.code"
    if (token.variant == 1) {
#line 121 "tests/10__calculator/test.code"
        return (struct Expression){.variant = 1, .variant_1 = token.variant_1};
    }
#line 123 "tests/10__calculator/test.code"
    return (struct Expression){.variant = 6, .variant_6 = (struct Error){.span = pToken__span(&token), .message = (struct String){.data = "Expected number", .length = 15}}};
}

#line 164 "tests/10__calculator/test.code"
struct Span pExpression__span(struct Expression *self) {
#line 165 "tests/10__calculator/test.code"
    while (false) {
    }
#line 166 "tests/10__calculator/test.code"
    if (self->variant == 1) {
#line 167 "tests/10__calculator/test.code"
        return self->variant_1.span;
    }
#line 169 "tests/10__calculator/test.code"
    else if (self->variant == 2) {
#line 170 "tests/10__calculator/test.code"
        return self->variant_2.span;
    }
#line 172 "tests/10__calculator/test.code"
    else if (self->variant == 3) {
#line 173 "tests/10__calculator/test.code"
        return self->variant_3.span;
    }
#line 175 "tests/10__calculator/test.code"
    else if (self->variant == 4) {
#line 176 "tests/10__calculator/test.code"
        return self->variant_4.span;
    }
#line 178 "tests/10__calculator/test.code"
    else if (self->variant == 5) {
#line 179 "tests/10__calculator/test.code"
        return self->variant_5.span;
    }
#line 181 "tests/10__calculator/test.code"
    else if (self->variant == 6) {
#line 182 "tests/10__calculator/test.code"
        return self->variant_6.span;
    }
#line 184 "tests/10__calculator/test.code"
    else if (self->variant == 0) {
#line 185 "tests/10__calculator/test.code"
        return (struct Span){.start = 0, .end = 0};
    }
}

#line 190 "tests/10__calculator/test.code"
struct Writer *pWriter__write__1_expression(struct Writer *self, struct Expression *expression) {
#line 191 "tests/10__calculator/test.code"
    while (false) {
    }
#line 192 "tests/10__calculator/test.code"
    if (expression->variant == 1) {
#line 193 "tests/10__calculator/test.code"
        return pWriter__write__1_signed(self, expression->variant_1.value);
    }
#line 195 "tests/10__calculator/test.code"
    else if (expression->variant == 2) {
#line 196 "tests/10__calculator/test.code"
        return pWriter__write(pWriter__write__1_expression(pWriter__write(pWriter__write__1_expression(pWriter__write(self, (struct String){.data = "(", .length = 1}), expression->variant_2.left), (struct String){.data = " + ", .length = 3}), expression->variant_2.right), (struct String){.data = ")", .length = 1});
    }
#line 198 "tests/10__calculator/test.code"
    else if (expression->variant == 3) {
#line 199 "tests/10__calculator/test.code"
        return pWriter__write(pWriter__write__1_expression(pWriter__write(pWriter__write__1_expression(pWriter__write(self, (struct String){.data = "(", .length = 1}), expression->variant_3.left), (struct String){.data = " / ", .length = 3}), expression->variant_3.right), (struct String){.data = ")", .length = 1});
    }
#line 201 "tests/10__calculator/test.code"
    else if (expression->variant == 4) {
#line 202 "tests/10__calculator/test.code"
        return pWriter__write(pWriter__write__1_expression(pWriter__write(pWriter__write__1_expression(pWriter__write(self, (struct String){.data = "(", .length = 1}), expression->variant_4.left), (struct String){.data = " * ", .length = 3}), expression->variant_4.right), (struct String){.data = ")", .length = 1});
    }
#line 204 "tests/10__calculator/test.code"
    else if (expression->variant == 5) {
#line 205 "tests/10__calculator/test.code"
        return pWriter__write(pWriter__write__1_expression(pWriter__write(pWriter__write__1_expression(pWriter__write(self, (struct String){.data = "(", .length = 1}), expression->variant_5.left), (struct String){.data = " - ", .length = 3}), expression->variant_5.right), (struct String){.data = ")", .length = 1});
    }
#line 207 "tests/10__calculator/test.code"
    else if (expression->variant == 6) {
#line 208 "tests/10__calculator/test.code"
        return pWriter__write(pWriter__write(self, (struct String){.data = "Error: ", .length = 7}), expression->variant_6.message);
    }
#line 210 "tests/10__calculator/test.code"
    else if (expression->variant == 0) {
#line 211 "tests/10__calculator/test.code"
        return pWriter__write(self, (struct String){.data = "Nil!", .length = 4});
    }
#line 214 "tests/10__calculator/test.code"
    return self;
}

#line 226 "tests/10__calculator/test.code"
struct Token pTokenizer__peek_token(struct Tokenizer *self) {
#line 227 "tests/10__calculator/test.code"
    if (self->current_token.variant == 0) {
#line 228 "tests/10__calculator/test.code"
        self->current_token = pTokenizer__scan_token(self);
    }
#line 230 "tests/10__calculator/test.code"
    return self->current_token;
}

#line 233 "tests/10__calculator/test.code"
struct Token pTokenizer__next_token(struct Tokenizer *self) {
#line 234 "tests/10__calculator/test.code"
    struct Token token = pTokenizer__peek_token(self);
#line 235 "tests/10__calculator/test.code"
    self->current_token = (struct Token){.variant = 0};
#line 236 "tests/10__calculator/test.code"
    return token;
}

#line 239 "tests/10__calculator/test.code"
struct Token pTokenizer__scan_token(struct Tokenizer *self) {
#line 240 "tests/10__calculator/test.code"
    while (self->data[self->index] == ' ') {
#line 241 "tests/10__calculator/test.code"
        self->index = self->index + 1;
    }
#line 243 "tests/10__calculator/test.code"
    uint8_t ch = self->data[self->index];
#line 244 "tests/10__calculator/test.code"
    if (ch == 0) {
#line 245 "tests/10__calculator/test.code"
        return (struct Token){.variant = 6, .variant_6 = (struct Stop){.span = (struct Span){.start = self->index, .end = self->index}}};
    }
#line 247 "tests/10__calculator/test.code"
    if (ch != ' ') {
#line 248 "tests/10__calculator/test.code"
        if (ch >= '0' && ch <= '9') {
#line 249 "tests/10__calculator/test.code"
            return pTokenizer__scan_number_token(self);
        }
#line 251 "tests/10__calculator/test.code"
        self->index = self->index + 1;
#line 252 "tests/10__calculator/test.code"
        if (ch == '+') {
#line 253 "tests/10__calculator/test.code"
            return (struct Token){.variant = 2, .variant_2 = (struct Plus){.span = (struct Span){.start = self->index - 1, .end = self->index}}};
        }
#line 255 "tests/10__calculator/test.code"
        if (ch == '-') {
#line 256 "tests/10__calculator/test.code"
            return (struct Token){.variant = 3, .variant_3 = (struct Minus){.span = (struct Span){.start = self->index - 1, .end = self->index}}};
        }
#line 258 "tests/10__calculator/test.code"
        if (ch == '*') {
#line 259 "tests/10__calculator/test.code"
            return (struct Token){.variant = 4, .variant_4 = (struct Multiply){.span = (struct Span){.start = self->index - 1, .end = self->index}}};
        }
#line 261 "tests/10__calculator/test.code"
        if (ch == '/') {
#line 262 "tests/10__calculator/test.code"
            return (struct Token){.variant = 5, .variant_5 = (struct Divide){.span = (struct Span){.start = self->index - 1, .end = self->index}}};
        }
#line 264 "tests/10__calculator/test.code"
        return (struct Token){.variant = 7, .variant_7 = (struct Error){.span = (struct Span){.start = self->index - 1, .end = self->index}, .message = (struct String){.data = "Unexpected character", .length = 20}}};
    }
}

#line 271 "tests/10__calculator/test.code"
struct Token pTokenizer__scan_number_token(struct Tokenizer *self) {
#line 272 "tests/10__calculator/test.code"
    int32_t start = self->index;
#line 273 "tests/10__calculator/test.code"
    int32_t value = 0;
#line 274 "tests/10__calculator/test.code"
    for (;;) {
#line 275 "tests/10__calculator/test.code"
        uint8_t c = self->data[self->index];
#line 276 "tests/10__calculator/test.code"
        if (c < '0' || c > '9') {
#line 277 "tests/10__calculator/test.code"
            break;
        }
#line 279 "tests/10__calculator/test.code"
        value = value * 10 + ((int32_t) (c - '0'));
#line 280 "tests/10__calculator/test.code"
        self->index = self->index + 1;
    }
#line 282 "tests/10__calculator/test.code"
    return (struct Token){.variant = 1, .variant_1 = (struct Number){.span = (struct Span){.start = start, .end = self->index}, .value = value}};
}

#line 336 "tests/10__calculator/test.code"
struct Span pToken__span(struct Token *self) {
#line 337 "tests/10__calculator/test.code"
    while (false) {
    }
#line 338 "tests/10__calculator/test.code"
    if (self->variant == 1) {
#line 339 "tests/10__calculator/test.code"
        return self->variant_1.span;
    }
#line 341 "tests/10__calculator/test.code"
    else if (self->variant == 2) {
#line 342 "tests/10__calculator/test.code"
        return self->variant_2.span;
    }
#line 344 "tests/10__calculator/test.code"
    else if (self->variant == 3) {
#line 345 "tests/10__calculator/test.code"
        return self->variant_3.span;
    }
#line 347 "tests/10__calculator/test.code"
    else if (self->variant == 4) {
#line 348 "tests/10__calculator/test.code"
        return self->variant_4.span;
    }
#line 350 "tests/10__calculator/test.code"
    else if (self->variant == 5) {
#line 351 "tests/10__calculator/test.code"
        return self->variant_5.span;
    }
#line 353 "tests/10__calculator/test.code"
    else if (self->variant == 6) {
#line 354 "tests/10__calculator/test.code"
        return self->variant_6.span;
    }
#line 356 "tests/10__calculator/test.code"
    else if (self->variant == 7) {
#line 357 "tests/10__calculator/test.code"
        return self->variant_7.span;
    }
#line 359 "tests/10__calculator/test.code"
    else if (self->variant == 0) {
#line 360 "tests/10__calculator/test.code"
        return (struct Span){.start = 0, .end = 0};
    }
}

#line 365 "tests/10__calculator/test.code"
struct Writer *pWriter__write__1_token(struct Writer *self, struct Token *token) {
#line 366 "tests/10__calculator/test.code"
    while (false) {
    }
#line 367 "tests/10__calculator/test.code"
    if (token->variant == 1) {
#line 368 "tests/10__calculator/test.code"
        return pWriter__write__1_signed(pWriter__write(self, (struct String){.data = "Number: ", .length = 8}), token->variant_1.value);
    }
#line 370 "tests/10__calculator/test.code"
    else if (token->variant == 2) {
#line 371 "tests/10__calculator/test.code"
        return pWriter__write(self, (struct String){.data = "Plus", .length = 4});
    }
#line 373 "tests/10__calculator/test.code"
    else if (token->variant == 3) {
#line 374 "tests/10__calculator/test.code"
        return pWriter__write(self, (struct String){.data = "Minus", .length = 5});
    }
#line 376 "tests/10__calculator/test.code"
    else if (token->variant == 4) {
#line 377 "tests/10__calculator/test.code"
        return pWriter__write(self, (struct String){.data = "Multiply", .length = 8});
    }
#line 379 "tests/10__calculator/test.code"
    else if (token->variant == 5) {
#line 380 "tests/10__calculator/test.code"
        return pWriter__write(self, (struct String){.data = "Divide", .length = 6});
    }
#line 382 "tests/10__calculator/test.code"
    else if (token->variant == 6) {
#line 383 "tests/10__calculator/test.code"
        return pWriter__write(self, (struct String){.data = "Stop", .length = 4});
    }
#line 385 "tests/10__calculator/test.code"
    else if (token->variant == 7) {
#line 386 "tests/10__calculator/test.code"
        return pWriter__write(pWriter__write(self, (struct String){.data = "Error: ", .length = 7}), token->variant_7.message);
    }
#line 388 "tests/10__calculator/test.code"
    else if (token->variant == 0) {
#line 389 "tests/10__calculator/test.code"
        return pWriter__write(self, (struct String){.data = "Nil!", .length = 4});
    }
#line 392 "tests/10__calculator/test.code"
    return self;
}

#line 402 "tests/10__calculator/test.code"
struct Writer *pWriter__write__1_char(struct Writer *self, uint8_t c) {
#line 403 "tests/10__calculator/test.code"
    self->write_char(self->self, c);
#line 404 "tests/10__calculator/test.code"
    return self;
}

#line 407 "tests/10__calculator/test.code"
struct Writer *pWriter__write__1_signed(struct Writer *self, int32_t value) {
#line 409 "tests/10__calculator/test.code"
    if (value < 0) {
#line 410 "tests/10__calculator/test.code"
        pWriter__write__1_char(self, '-');
#line 411 "tests/10__calculator/test.code"
        return pWriter__write__1_signed(self, -value);
    }
#line 413 "tests/10__calculator/test.code"
    if (value >= 10) {
#line 414 "tests/10__calculator/test.code"
        pWriter__write__1_signed(self, value / 10);
    }
#line 416 "tests/10__calculator/test.code"
    return pWriter__write__1_char(self, ((uint8_t) (value % 10)) + '0');
}

#line 419 "tests/10__calculator/test.code"
struct Writer *pWriter__end_line(struct Writer *self) {
#line 420 "tests/10__calculator/test.code"
    pWriter__write__1_char(self, '\n');
#line 421 "tests/10__calculator/test.code"
    return self;
}

#line 432 "tests/10__calculator/test.code"
struct String_Builder *pString_Builder__write__1_char(struct String_Builder *self, uint8_t c) {
#line 433 "tests/10__calculator/test.code"
    if (self->length == self->data_size) {
#line 434 "tests/10__calculator/test.code"
        self->data_size = self->data_size + 8;
#line 435 "tests/10__calculator/test.code"
        self->data = ((uint8_t *) realloc(((void *) self->data), ((uint64_t) self->data_size)));
    }
#line 440 "tests/10__calculator/test.code"
    self->data[self->length] = c;
#line 441 "tests/10__calculator/test.code"
    self->length = self->length + 1;
#line 442 "tests/10__calculator/test.code"
    return self;
}

#line 445 "tests/10__calculator/test.code"
struct String pString_Builder__build(struct String_Builder *self) {
#line 446 "tests/10__calculator/test.code"
    pString_Builder__write__1_char(self, 0);
#line 447 "tests/10__calculator/test.code"
    struct String string = (struct String){.data = self->data, .length = self->length - 1};
#line 451 "tests/10__calculator/test.code"
    return *((struct String *) (&string));
}

#line 454 "tests/10__calculator/test.code"
struct String_Builder make_string_builder() {
#line 455 "tests/10__calculator/test.code"
    return make_string_builder__0_initial_data_size(4);
}

#line 458 "tests/10__calculator/test.code"
struct String_Builder make_string_builder__0_initial_data_size(int32_t initial_data_size) {
#line 459 "tests/10__calculator/test.code"
    return (struct String_Builder){.data = ((uint8_t *) malloc(((uint64_t) initial_data_size))), .data_size = initial_data_size, .length = 0};
}

#line 466 "tests/10__calculator/test.code"
void pString_Builder__write_char(struct String_Builder *self, uint8_t c) {
#line 467 "tests/10__calculator/test.code"
    pString_Builder__write__1_char(self, c);
}

#line 477 "tests/10__calculator/test.code"
struct Writer *pWriter__write(struct Writer *self, struct String string) {
#line 478 "tests/10__calculator/test.code"
    struct String string_copy = string;
#line 479 "tests/10__calculator/test.code"
    uint8_t *string_data = ((struct String *) (&string_copy))->data;
#line 480 "tests/10__calculator/test.code"
    uintmax_t index = 0;
#line 481 "tests/10__calculator/test.code"
    while (index < string.length) {
#line 482 "tests/10__calculator/test.code"
        pWriter__write__1_char(self, string_data[index]);
#line 483 "tests/10__calculator/test.code"
        index = index + 1;
    }
#line 485 "tests/10__calculator/test.code"
    return self;
}

#line 498 "tests/10__calculator/test.code"
void pFILE__write_char(FILE *self, uint8_t c) {
#line 499 "tests/10__calculator/test.code"
    fputc(((int32_t) c), stdout);
}

