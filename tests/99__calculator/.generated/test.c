#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

#include "test.h"

struct test__Parser *__alloc_test__Parser_value(struct test__Parser value) {
    struct test__Parser *result = (struct test__Parser *)malloc(sizeof(struct test__Parser));
    *result = value;
    return result;
}

struct test__Tokenizer *__alloc_test__Tokenizer_value(struct test__Tokenizer value) {
    struct test__Tokenizer *result = (struct test__Tokenizer *)malloc(sizeof(struct test__Tokenizer));
    *result = value;
    return result;
}

struct test__Token *__alloc_test__Token_value(struct test__Token value) {
struct test__Token *result = (struct test__Token *)malloc(sizeof(struct test__Token));
    *result = value;
    return result;
}

struct test__Number *__alloc_test__Number_value(struct test__Number value) {
    struct test__Number *result = (struct test__Number *)malloc(sizeof(struct test__Number));
    *result = value;
    return result;
}

struct test__Span *__alloc_test__Span_value(struct test__Span value) {
    struct test__Span *result = (struct test__Span *)malloc(sizeof(struct test__Span));
    *result = value;
    return result;
}

struct test__Plus *__alloc_test__Plus_value(struct test__Plus value) {
    struct test__Plus *result = (struct test__Plus *)malloc(sizeof(struct test__Plus));
    *result = value;
    return result;
}

struct test__Minus *__alloc_test__Minus_value(struct test__Minus value) {
    struct test__Minus *result = (struct test__Minus *)malloc(sizeof(struct test__Minus));
    *result = value;
    return result;
}

struct test__Multiply *__alloc_test__Multiply_value(struct test__Multiply value) {
    struct test__Multiply *result = (struct test__Multiply *)malloc(sizeof(struct test__Multiply));
    *result = value;
    return result;
}

struct test__Divide *__alloc_test__Divide_value(struct test__Divide value) {
    struct test__Divide *result = (struct test__Divide *)malloc(sizeof(struct test__Divide));
    *result = value;
    return result;
}

struct test__Stop *__alloc_test__Stop_value(struct test__Stop value) {
    struct test__Stop *result = (struct test__Stop *)malloc(sizeof(struct test__Stop));
    *result = value;
    return result;
}

struct test__Error *__alloc_test__Error_value(struct test__Error value) {
    struct test__Error *result = (struct test__Error *)malloc(sizeof(struct test__Error));
    *result = value;
    return result;
}

struct String *__alloc_String_value(struct String value) {
    struct String *result = (struct String *)malloc(sizeof(struct String));
    *result = value;
    return result;
}

struct test__Expression *__alloc_test__Expression_value(struct test__Expression value) {
struct test__Expression *result = (struct test__Expression *)malloc(sizeof(struct test__Expression));
    *result = value;
    return result;
}

struct test__Addition *__alloc_test__Addition_value(struct test__Addition value) {
    struct test__Addition *result = (struct test__Addition *)malloc(sizeof(struct test__Addition));
    *result = value;
    return result;
}

struct test__Division *__alloc_test__Division_value(struct test__Division value) {
    struct test__Division *result = (struct test__Division *)malloc(sizeof(struct test__Division));
    *result = value;
    return result;
}

struct test__Multiplication *__alloc_test__Multiplication_value(struct test__Multiplication value) {
    struct test__Multiplication *result = (struct test__Multiplication *)malloc(sizeof(struct test__Multiplication));
    *result = value;
    return result;
}

struct test__Subtraction *__alloc_test__Subtraction_value(struct test__Subtraction value) {
    struct test__Subtraction *result = (struct test__Subtraction *)malloc(sizeof(struct test__Subtraction));
    *result = value;
    return result;
}

struct test__Writer *__alloc_test__Writer_value(struct test__Writer value) {
    struct test__Writer *result = (struct test__Writer *)malloc(sizeof(struct test__Writer));
    *result = value;
    return result;
}

struct test__String_Builder *__alloc_test__String_Builder_value(struct test__String_Builder value) {
    struct test__String_Builder *result = (struct test__String_Builder *)malloc(sizeof(struct test__String_Builder));
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
    struct test__Tokenizer tokenizer = (struct test__Tokenizer){.data = argv[1], .index = 0};
#line 11 "tests/99__calculator/test.code"
    struct test__Writer stdout_writer = (struct test__Writer){.self = __stdoutp, .write_char = ((void (*)(void *self, uint8_t c)) test__ptest__FILE__write_char)};
#line 13 "tests/99__calculator/test.code"
    while (test__ptest__Tokenizer__peek_token(&tokenizer).variant != 6) {
#line 14 "tests/99__calculator/test.code"
        struct test__Token token = test__ptest__Tokenizer__next_token(&tokenizer);
#line 15 "tests/99__calculator/test.code"
        test__ptest__Writer__end_line(test__ptest__Writer__write__1_token(&stdout_writer, &token));
    }
#line 18 "tests/99__calculator/test.code"
    struct test__Parser parser = (struct test__Parser){.tokenizer = (struct test__Tokenizer){.data = argv[1], .index = 0}};
#line 22 "tests/99__calculator/test.code"
    struct test__Expression expression = test__ptest__Parser__parse_expression(&parser);
#line 23 "tests/99__calculator/test.code"
    test__ptest__Writer__end_line(test__ptest__Writer__write__1_expression(test__ptest__Writer__write(&stdout_writer, (struct String){.data = "Expression: ", .length = 12}), &expression));
#line 25 "tests/99__calculator/test.code"
    int32_t result = test__evaluate__0_expression(&expression);
#line 26 "tests/99__calculator/test.code"
    test__ptest__Writer__end_line(test__ptest__Writer__write__1_signed(test__ptest__Writer__write(&stdout_writer, (struct String){.data = "Result: ", .length = 8}), result));
#line 28 "tests/99__calculator/test.code"
    return 0;
}

#line 33 "tests/99__calculator/test.code"
int32_t test__evaluate__0_expression(struct test__Expression *expression) {
#line 34 "tests/99__calculator/test.code"
    struct test__Expression *__switch_34_value__ = expression;
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
struct test__Expression test__ptest__Parser__parse_expression(struct test__Parser *self) {
#line 63 "tests/99__calculator/test.code"
    return test__ptest__Parser__parse_additive_expression(self);
}

#line 66 "tests/99__calculator/test.code"
struct test__Expression test__ptest__Parser__parse_additive_expression(struct test__Parser *self) {
#line 67 "tests/99__calculator/test.code"
    struct test__Expression expression = test__ptest__Parser__parse_multiplicative_expression(self);
#line 68 "tests/99__calculator/test.code"
    for (;;) {
#line 69 "tests/99__calculator/test.code"
        struct test__Token __switch_69_value__ = test__ptest__Tokenizer__peek_token(&self->tokenizer);
#line 70 "tests/99__calculator/test.code"
        if (__switch_69_value__.variant == 2) {
#line 71 "tests/99__calculator/test.code"
            test__ptest__Tokenizer__next_token(&self->tokenizer);
#line 72 "tests/99__calculator/test.code"
            struct test__Expression other_expression = test__ptest__Parser__parse_multiplicative_expression(self);
#line 73 "tests/99__calculator/test.code"
            expression = (struct test__Expression){.variant = 2, .variant_2 = (struct test__Addition){.span = (struct test__Span){.start = test__ptest__Expression__span(&expression).start, .end = test__ptest__Expression__span(&other_expression).end}, .left = __alloc_test__Expression_value(expression), .right = __alloc_test__Expression_value(other_expression)}};
        }
#line 79 "tests/99__calculator/test.code"
        else if (__switch_69_value__.variant == 3) {
#line 80 "tests/99__calculator/test.code"
            test__ptest__Tokenizer__next_token(&self->tokenizer);
#line 81 "tests/99__calculator/test.code"
            struct test__Expression other_expression = test__ptest__Parser__parse_multiplicative_expression(self);
#line 82 "tests/99__calculator/test.code"
            expression = (struct test__Expression){.variant = 5, .variant_5 = (struct test__Subtraction){.span = (struct test__Span){.start = test__ptest__Expression__span(&expression).start, .end = test__ptest__Expression__span(&other_expression).end}, .left = __alloc_test__Expression_value(expression), .right = __alloc_test__Expression_value(other_expression)}};
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
struct test__Expression test__ptest__Parser__parse_multiplicative_expression(struct test__Parser *self) {
#line 97 "tests/99__calculator/test.code"
    struct test__Expression expression = test__ptest__Parser__parse_primary_expression(self);
#line 98 "tests/99__calculator/test.code"
    for (;;) {
#line 99 "tests/99__calculator/test.code"
        struct test__Token token = test__ptest__Tokenizer__peek_token(&self->tokenizer);
#line 100 "tests/99__calculator/test.code"
        if (token.variant == 4) {
#line 101 "tests/99__calculator/test.code"
            test__ptest__Tokenizer__next_token(&self->tokenizer);
#line 102 "tests/99__calculator/test.code"
            struct test__Expression other_expression = test__ptest__Parser__parse_primary_expression(self);
#line 103 "tests/99__calculator/test.code"
            expression = (struct test__Expression){.variant = 4, .variant_4 = (struct test__Multiplication){.span = (struct test__Span){.start = test__ptest__Expression__span(&expression).start, .end = test__ptest__Expression__span(&other_expression).end}, .left = __alloc_test__Expression_value(expression), .right = __alloc_test__Expression_value(other_expression)}};
        } else if (token.variant == 5) {
#line 109 "tests/99__calculator/test.code"
            test__ptest__Tokenizer__next_token(&self->tokenizer);
#line 110 "tests/99__calculator/test.code"
            struct test__Expression other_expression = test__ptest__Parser__parse_primary_expression(self);
#line 111 "tests/99__calculator/test.code"
            expression = (struct test__Expression){.variant = 3, .variant_3 = (struct test__Division){.span = (struct test__Span){.start = test__ptest__Expression__span(&expression).start, .end = test__ptest__Expression__span(&other_expression).end}, .left = __alloc_test__Expression_value(expression), .right = __alloc_test__Expression_value(other_expression)}};
        } else {
#line 117 "tests/99__calculator/test.code"
            break;
        }
    }
#line 120 "tests/99__calculator/test.code"
    return expression;
}

#line 123 "tests/99__calculator/test.code"
struct test__Expression test__ptest__Parser__parse_primary_expression(struct test__Parser *self) {
#line 124 "tests/99__calculator/test.code"
    struct test__Token token = test__ptest__Tokenizer__next_token(&self->tokenizer);
#line 125 "tests/99__calculator/test.code"
    if (token.variant == 1) {
#line 126 "tests/99__calculator/test.code"
        return (struct test__Expression){.variant = 1, .variant_1 = token.variant_1};
    }
#line 128 "tests/99__calculator/test.code"
    return (struct test__Expression){.variant = 6, .variant_6 = (struct test__Error){.span = test__ptest__Token__span(&token), .message = (struct String){.data = "Expected number", .length = 15}}};
}

#line 169 "tests/99__calculator/test.code"
struct test__Span test__ptest__Expression__span(struct test__Expression *self) {
#line 170 "tests/99__calculator/test.code"
    struct test__Expression *__switch_170_value__ = self;
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
        return (struct test__Span){.start = 0, .end = 0};
    }
}

#line 195 "tests/99__calculator/test.code"
struct test__Writer *test__ptest__Writer__write__1_expression(struct test__Writer *self, struct test__Expression *expression) {
#line 196 "tests/99__calculator/test.code"
    struct test__Expression *__switch_196_value__ = expression;
#line 197 "tests/99__calculator/test.code"
    if (__switch_196_value__->variant == 1) {
#line 198 "tests/99__calculator/test.code"
        return test__ptest__Writer__write__1_signed(self, __switch_196_value__->variant_1.value);
    }
#line 200 "tests/99__calculator/test.code"
    else if (__switch_196_value__->variant == 2) {
#line 201 "tests/99__calculator/test.code"
        return test__ptest__Writer__write(test__ptest__Writer__write__1_expression(test__ptest__Writer__write(test__ptest__Writer__write__1_expression(test__ptest__Writer__write(self, (struct String){.data = "(", .length = 1}), __switch_196_value__->variant_2.left), (struct String){.data = " + ", .length = 3}), __switch_196_value__->variant_2.right), (struct String){.data = ")", .length = 1});
    }
#line 203 "tests/99__calculator/test.code"
    else if (__switch_196_value__->variant == 3) {
#line 204 "tests/99__calculator/test.code"
        return test__ptest__Writer__write(test__ptest__Writer__write__1_expression(test__ptest__Writer__write(test__ptest__Writer__write__1_expression(test__ptest__Writer__write(self, (struct String){.data = "(", .length = 1}), __switch_196_value__->variant_3.left), (struct String){.data = " / ", .length = 3}), __switch_196_value__->variant_3.right), (struct String){.data = ")", .length = 1});
    }
#line 206 "tests/99__calculator/test.code"
    else if (__switch_196_value__->variant == 4) {
#line 207 "tests/99__calculator/test.code"
        return test__ptest__Writer__write(test__ptest__Writer__write__1_expression(test__ptest__Writer__write(test__ptest__Writer__write__1_expression(test__ptest__Writer__write(self, (struct String){.data = "(", .length = 1}), __switch_196_value__->variant_4.left), (struct String){.data = " * ", .length = 3}), __switch_196_value__->variant_4.right), (struct String){.data = ")", .length = 1});
    }
#line 209 "tests/99__calculator/test.code"
    else if (__switch_196_value__->variant == 5) {
#line 210 "tests/99__calculator/test.code"
        return test__ptest__Writer__write(test__ptest__Writer__write__1_expression(test__ptest__Writer__write(test__ptest__Writer__write__1_expression(test__ptest__Writer__write(self, (struct String){.data = "(", .length = 1}), __switch_196_value__->variant_5.left), (struct String){.data = " - ", .length = 3}), __switch_196_value__->variant_5.right), (struct String){.data = ")", .length = 1});
    }
#line 212 "tests/99__calculator/test.code"
    else if (__switch_196_value__->variant == 6) {
#line 213 "tests/99__calculator/test.code"
        return test__ptest__Writer__write(test__ptest__Writer__write(self, (struct String){.data = "Error: ", .length = 7}), __switch_196_value__->variant_6.message);
    }
#line 215 "tests/99__calculator/test.code"
    else if (__switch_196_value__->variant == 0) {
#line 216 "tests/99__calculator/test.code"
        return test__ptest__Writer__write(self, (struct String){.data = "Nil!", .length = 4});
    }
#line 219 "tests/99__calculator/test.code"
    return self;
}

#line 231 "tests/99__calculator/test.code"
struct test__Token test__ptest__Tokenizer__peek_token(struct test__Tokenizer *self) {
#line 232 "tests/99__calculator/test.code"
    if (self->current_token.variant == 0) {
#line 233 "tests/99__calculator/test.code"
        self->current_token = test__ptest__Tokenizer__scan_token(self);
    }
#line 235 "tests/99__calculator/test.code"
    return self->current_token;
}

#line 238 "tests/99__calculator/test.code"
struct test__Token test__ptest__Tokenizer__next_token(struct test__Tokenizer *self) {
#line 239 "tests/99__calculator/test.code"
    struct test__Token token = test__ptest__Tokenizer__peek_token(self);
#line 240 "tests/99__calculator/test.code"
    self->current_token = (struct test__Token){.variant = 0};
#line 241 "tests/99__calculator/test.code"
    return token;
}

#line 244 "tests/99__calculator/test.code"
struct test__Token test__ptest__Tokenizer__scan_token(struct test__Tokenizer *self) {
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
        return (struct test__Token){.variant = 6, .variant_6 = (struct test__Stop){.span = (struct test__Span){.start = self->index, .end = self->index}}};
    }
#line 252 "tests/99__calculator/test.code"
    if (ch >= '0' && ch <= '9') {
#line 253 "tests/99__calculator/test.code"
        return test__ptest__Tokenizer__scan_number_token(self);
    }
#line 255 "tests/99__calculator/test.code"
    self->index = self->index + 1;
#line 256 "tests/99__calculator/test.code"
    if (ch == '+') {
#line 257 "tests/99__calculator/test.code"
        return (struct test__Token){.variant = 2, .variant_2 = (struct test__Plus){.span = (struct test__Span){.start = self->index - 1, .end = self->index}}};
    }
#line 259 "tests/99__calculator/test.code"
    if (ch == '-') {
#line 260 "tests/99__calculator/test.code"
        return (struct test__Token){.variant = 3, .variant_3 = (struct test__Minus){.span = (struct test__Span){.start = self->index - 1, .end = self->index}}};
    }
#line 262 "tests/99__calculator/test.code"
    if (ch == '*') {
#line 263 "tests/99__calculator/test.code"
        return (struct test__Token){.variant = 4, .variant_4 = (struct test__Multiply){.span = (struct test__Span){.start = self->index - 1, .end = self->index}}};
    }
#line 265 "tests/99__calculator/test.code"
    if (ch == '/') {
#line 266 "tests/99__calculator/test.code"
        return (struct test__Token){.variant = 5, .variant_5 = (struct test__Divide){.span = (struct test__Span){.start = self->index - 1, .end = self->index}}};
    }
#line 268 "tests/99__calculator/test.code"
    return (struct test__Token){.variant = 7, .variant_7 = (struct test__Error){.span = (struct test__Span){.start = self->index - 1, .end = self->index}, .message = (struct String){.data = "Unexpected character", .length = 20}}};
}

#line 274 "tests/99__calculator/test.code"
struct test__Token test__ptest__Tokenizer__scan_number_token(struct test__Tokenizer *self) {
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
    return (struct test__Token){.variant = 1, .variant_1 = (struct test__Number){.span = (struct test__Span){.start = start, .end = self->index}, .value = value}};
}

#line 338 "tests/99__calculator/test.code"
struct test__Span test__ptest__Token__span(struct test__Token *self) {
#line 339 "tests/99__calculator/test.code"
    struct test__Token *__switch_339_value__ = self;
#line 340 "tests/99__calculator/test.code"
    if (__switch_339_value__->variant == 1) {
#line 341 "tests/99__calculator/test.code"
        return __switch_339_value__->variant_1.span;
    }
#line 343 "tests/99__calculator/test.code"
    else if (__switch_339_value__->variant == 2) {
#line 344 "tests/99__calculator/test.code"
        return __switch_339_value__->variant_2.span;
    }
#line 346 "tests/99__calculator/test.code"
    else if (__switch_339_value__->variant == 3) {
#line 347 "tests/99__calculator/test.code"
        return __switch_339_value__->variant_3.span;
    }
#line 349 "tests/99__calculator/test.code"
    else if (__switch_339_value__->variant == 4) {
#line 350 "tests/99__calculator/test.code"
        return __switch_339_value__->variant_4.span;
    }
#line 352 "tests/99__calculator/test.code"
    else if (__switch_339_value__->variant == 5) {
#line 353 "tests/99__calculator/test.code"
        return __switch_339_value__->variant_5.span;
    }
#line 355 "tests/99__calculator/test.code"
    else if (__switch_339_value__->variant == 6) {
#line 356 "tests/99__calculator/test.code"
        return __switch_339_value__->variant_6.span;
    }
#line 358 "tests/99__calculator/test.code"
    else if (__switch_339_value__->variant == 7) {
#line 359 "tests/99__calculator/test.code"
        return __switch_339_value__->variant_7.span;
    }
#line 361 "tests/99__calculator/test.code"
    else if (__switch_339_value__->variant == 0) {
#line 362 "tests/99__calculator/test.code"
        return (struct test__Span){.start = 0, .end = 0};
    }
}

#line 367 "tests/99__calculator/test.code"
struct test__Writer *test__ptest__Writer__write__1_token(struct test__Writer *self, struct test__Token *token) {
#line 368 "tests/99__calculator/test.code"
    struct test__Token *__switch_368_value__ = token;
#line 369 "tests/99__calculator/test.code"
    if (__switch_368_value__->variant == 1) {
#line 370 "tests/99__calculator/test.code"
        return test__ptest__Writer__write__1_signed(test__ptest__Writer__write(self, (struct String){.data = "Number: ", .length = 8}), __switch_368_value__->variant_1.value);
    }
#line 372 "tests/99__calculator/test.code"
    else if (__switch_368_value__->variant == 2) {
#line 373 "tests/99__calculator/test.code"
        return test__ptest__Writer__write(self, (struct String){.data = "Plus", .length = 4});
    }
#line 375 "tests/99__calculator/test.code"
    else if (__switch_368_value__->variant == 3) {
#line 376 "tests/99__calculator/test.code"
        return test__ptest__Writer__write(self, (struct String){.data = "Minus", .length = 5});
    }
#line 378 "tests/99__calculator/test.code"
    else if (__switch_368_value__->variant == 4) {
#line 379 "tests/99__calculator/test.code"
        return test__ptest__Writer__write(self, (struct String){.data = "Multiply", .length = 8});
    }
#line 381 "tests/99__calculator/test.code"
    else if (__switch_368_value__->variant == 5) {
#line 382 "tests/99__calculator/test.code"
        return test__ptest__Writer__write(self, (struct String){.data = "Divide", .length = 6});
    }
#line 384 "tests/99__calculator/test.code"
    else if (__switch_368_value__->variant == 6) {
#line 385 "tests/99__calculator/test.code"
        return test__ptest__Writer__write(self, (struct String){.data = "Stop", .length = 4});
    }
#line 387 "tests/99__calculator/test.code"
    else if (__switch_368_value__->variant == 7) {
#line 388 "tests/99__calculator/test.code"
        return test__ptest__Writer__write(test__ptest__Writer__write(self, (struct String){.data = "Error: ", .length = 7}), __switch_368_value__->variant_7.message);
    }
#line 390 "tests/99__calculator/test.code"
    else if (__switch_368_value__->variant == 0) {
#line 391 "tests/99__calculator/test.code"
        return test__ptest__Writer__write(self, (struct String){.data = "Nil!", .length = 4});
    }
#line 394 "tests/99__calculator/test.code"
    return self;
}

#line 403 "tests/99__calculator/test.code"
struct test__Writer *test__ptest__Writer__write__1_char(struct test__Writer *self, uint8_t c) {
#line 404 "tests/99__calculator/test.code"
    self->write_char(self->self, c);
#line 405 "tests/99__calculator/test.code"
    return self;
}

#line 408 "tests/99__calculator/test.code"
struct test__Writer *test__ptest__Writer__write__1_signed(struct test__Writer *self, int32_t value) {
#line 410 "tests/99__calculator/test.code"
    if (value < 0) {
#line 411 "tests/99__calculator/test.code"
        test__ptest__Writer__write__1_char(self, '-');
#line 412 "tests/99__calculator/test.code"
        return test__ptest__Writer__write__1_signed(self, -value);
    }
#line 414 "tests/99__calculator/test.code"
    if (value >= 10) {
#line 415 "tests/99__calculator/test.code"
        test__ptest__Writer__write__1_signed(self, value / 10);
    }
#line 417 "tests/99__calculator/test.code"
    return test__ptest__Writer__write__1_char(self, ((uint8_t) (value % 10)) + '0');
}

#line 420 "tests/99__calculator/test.code"
struct test__Writer *test__ptest__Writer__end_line(struct test__Writer *self) {
#line 421 "tests/99__calculator/test.code"
    test__ptest__Writer__write__1_char(self, '\n');
#line 422 "tests/99__calculator/test.code"
    return self;
}

#line 433 "tests/99__calculator/test.code"
struct test__String_Builder *test__ptest__String_Builder__write__1_char(struct test__String_Builder *self, uint8_t c) {
#line 434 "tests/99__calculator/test.code"
    if (self->length == self->data_size) {
#line 435 "tests/99__calculator/test.code"
        self->data_size = self->data_size + 8;
#line 436 "tests/99__calculator/test.code"
        self->data = ((uint8_t *) realloc(((void *) self->data), ((uint64_t) self->data_size)));
    }
#line 441 "tests/99__calculator/test.code"
    self->data[self->length] = c;
#line 442 "tests/99__calculator/test.code"
    self->length = self->length + 1;
#line 443 "tests/99__calculator/test.code"
    return self;
}

#line 446 "tests/99__calculator/test.code"
struct String test__ptest__String_Builder__build(struct test__String_Builder *self) {
#line 447 "tests/99__calculator/test.code"
    test__ptest__String_Builder__write__1_char(self, 0);
#line 448 "tests/99__calculator/test.code"
    struct String string = (struct String){.data = self->data, .length = self->length - 1};
#line 452 "tests/99__calculator/test.code"
    return *((struct String *) (&string));
}

#line 455 "tests/99__calculator/test.code"
struct test__String_Builder test__make_string_builder() {
#line 456 "tests/99__calculator/test.code"
    return test__make_string_builder__0_initial_data_size(4);
}

#line 459 "tests/99__calculator/test.code"
struct test__String_Builder test__make_string_builder__0_initial_data_size(int32_t initial_data_size) {
#line 460 "tests/99__calculator/test.code"
    return (struct test__String_Builder){.data = ((uint8_t *) malloc(((uint64_t) initial_data_size))), .data_size = initial_data_size, .length = 0};
}

#line 467 "tests/99__calculator/test.code"
void test__ptest__String_Builder__write_char(struct test__String_Builder *self, uint8_t c) {
#line 468 "tests/99__calculator/test.code"
    test__ptest__String_Builder__write__1_char(self, c);
}

#line 478 "tests/99__calculator/test.code"
struct test__Writer *test__ptest__Writer__write(struct test__Writer *self, struct String string) {
#line 479 "tests/99__calculator/test.code"
    struct String string_copy = string;
#line 480 "tests/99__calculator/test.code"
    uint8_t *string_data = ((struct String *) (&string_copy))->data;
#line 481 "tests/99__calculator/test.code"
    uintmax_t index = 0;
#line 482 "tests/99__calculator/test.code"
    while (index < string.length) {
#line 483 "tests/99__calculator/test.code"
        test__ptest__Writer__write__1_char(self, string_data[index]);
#line 484 "tests/99__calculator/test.code"
        index = index + 1;
    }
#line 486 "tests/99__calculator/test.code"
    return self;
}

#line 499 "tests/99__calculator/test.code"
void test__ptest__FILE__write_char(test__FILE *self, uint8_t c) {
#line 500 "tests/99__calculator/test.code"
    fputc(((int32_t) c), __stdoutp);
}

int32_t main(int argc, const char **argv) {
    return test__main(argc, (uint8_t **)argv);
}

