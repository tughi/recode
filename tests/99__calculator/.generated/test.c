#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

#include "test.h"

struct test_Parser *__alloc__test_Parser__(struct test_Parser value) {
    struct test_Parser *result = (struct test_Parser *)malloc(sizeof(struct test_Parser));
    *result = value;
    return result;
}

struct test_Tokenizer *__alloc__test_Tokenizer__(struct test_Tokenizer value) {
    struct test_Tokenizer *result = (struct test_Tokenizer *)malloc(sizeof(struct test_Tokenizer));
    *result = value;
    return result;
}

struct test_Token *__alloc__test_Token__(struct test_Token value) {
struct test_Token *result = (struct test_Token *)malloc(sizeof(struct test_Token));
    *result = value;
    return result;
}

struct test_Number *__alloc__test_Number__(struct test_Number value) {
    struct test_Number *result = (struct test_Number *)malloc(sizeof(struct test_Number));
    *result = value;
    return result;
}

struct test_Plus *__alloc__test_Plus__(struct test_Plus value) {
    struct test_Plus *result = (struct test_Plus *)malloc(sizeof(struct test_Plus));
    *result = value;
    return result;
}

struct test_Minus *__alloc__test_Minus__(struct test_Minus value) {
    struct test_Minus *result = (struct test_Minus *)malloc(sizeof(struct test_Minus));
    *result = value;
    return result;
}

struct test_Multiply *__alloc__test_Multiply__(struct test_Multiply value) {
    struct test_Multiply *result = (struct test_Multiply *)malloc(sizeof(struct test_Multiply));
    *result = value;
    return result;
}

struct test_Divide *__alloc__test_Divide__(struct test_Divide value) {
    struct test_Divide *result = (struct test_Divide *)malloc(sizeof(struct test_Divide));
    *result = value;
    return result;
}

struct test_Stop *__alloc__test_Stop__(struct test_Stop value) {
    struct test_Stop *result = (struct test_Stop *)malloc(sizeof(struct test_Stop));
    *result = value;
    return result;
}

struct test_Error *__alloc__test_Error__(struct test_Error value) {
    struct test_Error *result = (struct test_Error *)malloc(sizeof(struct test_Error));
    *result = value;
    return result;
}

struct String *__alloc__String__(struct String value) {
    struct String *result = (struct String *)malloc(sizeof(struct String));
    *result = value;
    return result;
}

struct test_Expression *__alloc__test_Expression__(struct test_Expression value) {
struct test_Expression *result = (struct test_Expression *)malloc(sizeof(struct test_Expression));
    *result = value;
    return result;
}

struct test_Addition *__alloc__test_Addition__(struct test_Addition value) {
    struct test_Addition *result = (struct test_Addition *)malloc(sizeof(struct test_Addition));
    *result = value;
    return result;
}

struct test_Division *__alloc__test_Division__(struct test_Division value) {
    struct test_Division *result = (struct test_Division *)malloc(sizeof(struct test_Division));
    *result = value;
    return result;
}

struct test_Multiplication *__alloc__test_Multiplication__(struct test_Multiplication value) {
    struct test_Multiplication *result = (struct test_Multiplication *)malloc(sizeof(struct test_Multiplication));
    *result = value;
    return result;
}

struct test_Subtraction *__alloc__test_Subtraction__(struct test_Subtraction value) {
    struct test_Subtraction *result = (struct test_Subtraction *)malloc(sizeof(struct test_Subtraction));
    *result = value;
    return result;
}

struct test_String_Builder *__alloc__test_String_Builder__(struct test_String_Builder value) {
    struct test_String_Builder *result = (struct test_String_Builder *)malloc(sizeof(struct test_String_Builder));
    *result = value;
    return result;
}

#line 6 "tests/99__calculator/test.code"
int32_t test__main(int32_t argc, uint8_t **argv) {
#line 7 "tests/99__calculator/test.code"
    os__init();
#line 9 "tests/99__calculator/test.code"
    if (argc != 2) {
#line 10 "tests/99__calculator/test.code"
        exit(1);
    }
#line 13 "tests/99__calculator/test.code"
    struct test_Tokenizer tokenizer = (struct test_Tokenizer){.data = argv[1], .index = 0};
#line 18 "tests/99__calculator/test.code"
    while (ptest_Tokenizer__peek_token(&tokenizer).variant != 6) {
#line 19 "tests/99__calculator/test.code"
        struct test_Token token = ptest_Tokenizer__next_token(&tokenizer);
#line 20 "tests/99__calculator/test.code"
        pio_Writer__end_line(pio_Writer__write__1_token(os__stdout, &token));
    }
#line 23 "tests/99__calculator/test.code"
    struct test_Parser parser = (struct test_Parser){.tokenizer = (struct test_Tokenizer){.data = argv[1], .index = 0}};
#line 27 "tests/99__calculator/test.code"
    struct test_Expression expression = ptest_Parser__parse_expression(&parser);
#line 28 "tests/99__calculator/test.code"
    pio_Writer__end_line(pio_Writer__write__1_expression(pio_Writer__write(os__stdout, (struct String){.data = "Expression: ", .length = 12}), &expression));
#line 30 "tests/99__calculator/test.code"
    int32_t result = test__evaluate__0_expression(&expression);
#line 31 "tests/99__calculator/test.code"
    pio_Writer__end_line(pio_Writer__write__1_signed(pio_Writer__write(os__stdout, (struct String){.data = "Result: ", .length = 8}), result));
#line 33 "tests/99__calculator/test.code"
    return 0;
}

#line 38 "tests/99__calculator/test.code"
int32_t test__evaluate__0_expression(struct test_Expression *expression) {
#line 39 "tests/99__calculator/test.code"
    struct test_Expression *__switch_39_value__ = expression;
#line 40 "tests/99__calculator/test.code"
    if (__switch_39_value__->variant == 1) {
#line 41 "tests/99__calculator/test.code"
        return __switch_39_value__->variant_1.value;
    }
#line 43 "tests/99__calculator/test.code"
    else if (__switch_39_value__->variant == 2) {
#line 44 "tests/99__calculator/test.code"
        return test__evaluate__0_expression(__switch_39_value__->variant_2.left) + test__evaluate__0_expression(__switch_39_value__->variant_2.right);
    }
#line 46 "tests/99__calculator/test.code"
    else if (__switch_39_value__->variant == 3) {
#line 47 "tests/99__calculator/test.code"
        return test__evaluate__0_expression(__switch_39_value__->variant_3.left) / test__evaluate__0_expression(__switch_39_value__->variant_3.right);
    }
#line 49 "tests/99__calculator/test.code"
    else if (__switch_39_value__->variant == 4) {
#line 50 "tests/99__calculator/test.code"
        return test__evaluate__0_expression(__switch_39_value__->variant_4.left) * test__evaluate__0_expression(__switch_39_value__->variant_4.right);
    }
#line 52 "tests/99__calculator/test.code"
    else if (__switch_39_value__->variant == 5) {
#line 53 "tests/99__calculator/test.code"
        return test__evaluate__0_expression(__switch_39_value__->variant_5.left) - test__evaluate__0_expression(__switch_39_value__->variant_5.right);
    }
#line 55 "tests/99__calculator/test.code"
    else {
#line 56 "tests/99__calculator/test.code"
        exit(1);
    }
}

#line 67 "tests/99__calculator/test.code"
struct test_Expression ptest_Parser__parse_expression(struct test_Parser *self) {
#line 68 "tests/99__calculator/test.code"
    return ptest_Parser__parse_additive_expression(self);
}

#line 71 "tests/99__calculator/test.code"
struct test_Expression ptest_Parser__parse_additive_expression(struct test_Parser *self) {
#line 72 "tests/99__calculator/test.code"
    struct test_Expression expression = ptest_Parser__parse_multiplicative_expression(self);
#line 73 "tests/99__calculator/test.code"
    for (;;) {
#line 74 "tests/99__calculator/test.code"
        struct test_Token __switch_74_value__ = ptest_Tokenizer__peek_token(&self->tokenizer);
#line 75 "tests/99__calculator/test.code"
        if (__switch_74_value__.variant == 2) {
#line 76 "tests/99__calculator/test.code"
            ptest_Tokenizer__next_token(&self->tokenizer);
#line 77 "tests/99__calculator/test.code"
            struct test_Expression other_expression = ptest_Parser__parse_multiplicative_expression(self);
#line 78 "tests/99__calculator/test.code"
            expression = (struct test_Expression){.variant = 2, .variant_2 = (struct test_Addition){.span = (struct calculator__source_Span){.start = ptest_Expression__span(&expression).start, .end = ptest_Expression__span(&other_expression).end}, .left = __alloc__test_Expression__(expression), .right = __alloc__test_Expression__(other_expression)}};
        }
#line 84 "tests/99__calculator/test.code"
        else if (__switch_74_value__.variant == 3) {
#line 85 "tests/99__calculator/test.code"
            ptest_Tokenizer__next_token(&self->tokenizer);
#line 86 "tests/99__calculator/test.code"
            struct test_Expression other_expression = ptest_Parser__parse_multiplicative_expression(self);
#line 87 "tests/99__calculator/test.code"
            expression = (struct test_Expression){.variant = 5, .variant_5 = (struct test_Subtraction){.span = (struct calculator__source_Span){.start = ptest_Expression__span(&expression).start, .end = ptest_Expression__span(&other_expression).end}, .left = __alloc__test_Expression__(expression), .right = __alloc__test_Expression__(other_expression)}};
        }
#line 93 "tests/99__calculator/test.code"
        else {
#line 94 "tests/99__calculator/test.code"
            break;
        }
    }
#line 98 "tests/99__calculator/test.code"
    return expression;
}

#line 101 "tests/99__calculator/test.code"
struct test_Expression ptest_Parser__parse_multiplicative_expression(struct test_Parser *self) {
#line 102 "tests/99__calculator/test.code"
    struct test_Expression expression = ptest_Parser__parse_primary_expression(self);
#line 103 "tests/99__calculator/test.code"
    for (;;) {
#line 104 "tests/99__calculator/test.code"
        struct test_Token token = ptest_Tokenizer__peek_token(&self->tokenizer);
#line 105 "tests/99__calculator/test.code"
        if (token.variant == 4) {
#line 106 "tests/99__calculator/test.code"
            ptest_Tokenizer__next_token(&self->tokenizer);
#line 107 "tests/99__calculator/test.code"
            struct test_Expression other_expression = ptest_Parser__parse_primary_expression(self);
#line 108 "tests/99__calculator/test.code"
            expression = (struct test_Expression){.variant = 4, .variant_4 = (struct test_Multiplication){.span = (struct calculator__source_Span){.start = ptest_Expression__span(&expression).start, .end = ptest_Expression__span(&other_expression).end}, .left = __alloc__test_Expression__(expression), .right = __alloc__test_Expression__(other_expression)}};
        } else if (token.variant == 5) {
#line 114 "tests/99__calculator/test.code"
            ptest_Tokenizer__next_token(&self->tokenizer);
#line 115 "tests/99__calculator/test.code"
            struct test_Expression other_expression = ptest_Parser__parse_primary_expression(self);
#line 116 "tests/99__calculator/test.code"
            expression = (struct test_Expression){.variant = 3, .variant_3 = (struct test_Division){.span = (struct calculator__source_Span){.start = ptest_Expression__span(&expression).start, .end = ptest_Expression__span(&other_expression).end}, .left = __alloc__test_Expression__(expression), .right = __alloc__test_Expression__(other_expression)}};
        } else {
#line 122 "tests/99__calculator/test.code"
            break;
        }
    }
#line 125 "tests/99__calculator/test.code"
    return expression;
}

#line 128 "tests/99__calculator/test.code"
struct test_Expression ptest_Parser__parse_primary_expression(struct test_Parser *self) {
#line 129 "tests/99__calculator/test.code"
    struct test_Token token = ptest_Tokenizer__next_token(&self->tokenizer);
#line 130 "tests/99__calculator/test.code"
    if (token.variant == 1) {
#line 131 "tests/99__calculator/test.code"
        return (struct test_Expression){.variant = 1, .variant_1 = token.variant_1};
    }
#line 133 "tests/99__calculator/test.code"
    return (struct test_Expression){.variant = 6, .variant_6 = (struct test_Error){.span = ptest_Token__span(&token), .message = (struct String){.data = "Expected number", .length = 15}}};
}

#line 174 "tests/99__calculator/test.code"
struct calculator__source_Span ptest_Expression__span(struct test_Expression *self) {
#line 175 "tests/99__calculator/test.code"
    struct test_Expression *__switch_175_value__ = self;
#line 176 "tests/99__calculator/test.code"
    if (__switch_175_value__->variant == 1) {
#line 177 "tests/99__calculator/test.code"
        return __switch_175_value__->variant_1.span;
    }
#line 179 "tests/99__calculator/test.code"
    else if (__switch_175_value__->variant == 2) {
#line 180 "tests/99__calculator/test.code"
        return __switch_175_value__->variant_2.span;
    }
#line 182 "tests/99__calculator/test.code"
    else if (__switch_175_value__->variant == 3) {
#line 183 "tests/99__calculator/test.code"
        return __switch_175_value__->variant_3.span;
    }
#line 185 "tests/99__calculator/test.code"
    else if (__switch_175_value__->variant == 4) {
#line 186 "tests/99__calculator/test.code"
        return __switch_175_value__->variant_4.span;
    }
#line 188 "tests/99__calculator/test.code"
    else if (__switch_175_value__->variant == 5) {
#line 189 "tests/99__calculator/test.code"
        return __switch_175_value__->variant_5.span;
    }
#line 191 "tests/99__calculator/test.code"
    else if (__switch_175_value__->variant == 6) {
#line 192 "tests/99__calculator/test.code"
        return __switch_175_value__->variant_6.span;
    }
#line 194 "tests/99__calculator/test.code"
    else if (__switch_175_value__->variant == 0) {
#line 195 "tests/99__calculator/test.code"
        return (struct calculator__source_Span){.start = 0, .end = 0};
    }
}

#line 200 "tests/99__calculator/test.code"
struct io_Writer *pio_Writer__write__1_expression(struct io_Writer *self, struct test_Expression *expression) {
#line 201 "tests/99__calculator/test.code"
    struct test_Expression *__switch_201_value__ = expression;
#line 202 "tests/99__calculator/test.code"
    if (__switch_201_value__->variant == 1) {
#line 203 "tests/99__calculator/test.code"
        return pio_Writer__write__1_signed(self, __switch_201_value__->variant_1.value);
    }
#line 205 "tests/99__calculator/test.code"
    else if (__switch_201_value__->variant == 2) {
#line 206 "tests/99__calculator/test.code"
        return pio_Writer__write(pio_Writer__write__1_expression(pio_Writer__write(pio_Writer__write__1_expression(pio_Writer__write(self, (struct String){.data = "(", .length = 1}), __switch_201_value__->variant_2.left), (struct String){.data = " + ", .length = 3}), __switch_201_value__->variant_2.right), (struct String){.data = ")", .length = 1});
    }
#line 208 "tests/99__calculator/test.code"
    else if (__switch_201_value__->variant == 3) {
#line 209 "tests/99__calculator/test.code"
        return pio_Writer__write(pio_Writer__write__1_expression(pio_Writer__write(pio_Writer__write__1_expression(pio_Writer__write(self, (struct String){.data = "(", .length = 1}), __switch_201_value__->variant_3.left), (struct String){.data = " / ", .length = 3}), __switch_201_value__->variant_3.right), (struct String){.data = ")", .length = 1});
    }
#line 211 "tests/99__calculator/test.code"
    else if (__switch_201_value__->variant == 4) {
#line 212 "tests/99__calculator/test.code"
        return pio_Writer__write(pio_Writer__write__1_expression(pio_Writer__write(pio_Writer__write__1_expression(pio_Writer__write(self, (struct String){.data = "(", .length = 1}), __switch_201_value__->variant_4.left), (struct String){.data = " * ", .length = 3}), __switch_201_value__->variant_4.right), (struct String){.data = ")", .length = 1});
    }
#line 214 "tests/99__calculator/test.code"
    else if (__switch_201_value__->variant == 5) {
#line 215 "tests/99__calculator/test.code"
        return pio_Writer__write(pio_Writer__write__1_expression(pio_Writer__write(pio_Writer__write__1_expression(pio_Writer__write(self, (struct String){.data = "(", .length = 1}), __switch_201_value__->variant_5.left), (struct String){.data = " - ", .length = 3}), __switch_201_value__->variant_5.right), (struct String){.data = ")", .length = 1});
    }
#line 217 "tests/99__calculator/test.code"
    else if (__switch_201_value__->variant == 6) {
#line 218 "tests/99__calculator/test.code"
        return pio_Writer__write(pio_Writer__write(self, (struct String){.data = "Error: ", .length = 7}), __switch_201_value__->variant_6.message);
    }
#line 220 "tests/99__calculator/test.code"
    else if (__switch_201_value__->variant == 0) {
#line 221 "tests/99__calculator/test.code"
        return pio_Writer__write(self, (struct String){.data = "Nil!", .length = 4});
    }
#line 224 "tests/99__calculator/test.code"
    return self;
}

#line 236 "tests/99__calculator/test.code"
struct test_Token ptest_Tokenizer__peek_token(struct test_Tokenizer *self) {
#line 237 "tests/99__calculator/test.code"
    if (self->current_token.variant == 0) {
#line 238 "tests/99__calculator/test.code"
        self->current_token = ptest_Tokenizer__scan_token(self);
    }
#line 240 "tests/99__calculator/test.code"
    return self->current_token;
}

#line 243 "tests/99__calculator/test.code"
struct test_Token ptest_Tokenizer__next_token(struct test_Tokenizer *self) {
#line 244 "tests/99__calculator/test.code"
    struct test_Token token = ptest_Tokenizer__peek_token(self);
#line 245 "tests/99__calculator/test.code"
    self->current_token = (struct test_Token){.variant = 0};
#line 246 "tests/99__calculator/test.code"
    return token;
}

#line 249 "tests/99__calculator/test.code"
struct test_Token ptest_Tokenizer__scan_token(struct test_Tokenizer *self) {
#line 250 "tests/99__calculator/test.code"
    while (self->data[self->index] == ' ') {
#line 251 "tests/99__calculator/test.code"
        self->index = self->index + 1;
    }
#line 253 "tests/99__calculator/test.code"
    uint8_t ch = self->data[self->index];
#line 254 "tests/99__calculator/test.code"
    if (ch == 0) {
#line 255 "tests/99__calculator/test.code"
        return (struct test_Token){.variant = 6, .variant_6 = (struct test_Stop){.span = (struct calculator__source_Span){.start = self->index, .end = self->index}}};
    }
#line 257 "tests/99__calculator/test.code"
    if (ch >= '0' && ch <= '9') {
#line 258 "tests/99__calculator/test.code"
        return ptest_Tokenizer__scan_number_token(self);
    }
#line 260 "tests/99__calculator/test.code"
    self->index = self->index + 1;
#line 261 "tests/99__calculator/test.code"
    if (ch == '+') {
#line 262 "tests/99__calculator/test.code"
        return (struct test_Token){.variant = 2, .variant_2 = (struct test_Plus){.span = (struct calculator__source_Span){.start = self->index - 1, .end = self->index}}};
    }
#line 264 "tests/99__calculator/test.code"
    if (ch == '-') {
#line 265 "tests/99__calculator/test.code"
        return (struct test_Token){.variant = 3, .variant_3 = (struct test_Minus){.span = (struct calculator__source_Span){.start = self->index - 1, .end = self->index}}};
    }
#line 267 "tests/99__calculator/test.code"
    if (ch == '*') {
#line 268 "tests/99__calculator/test.code"
        return (struct test_Token){.variant = 4, .variant_4 = (struct test_Multiply){.span = (struct calculator__source_Span){.start = self->index - 1, .end = self->index}}};
    }
#line 270 "tests/99__calculator/test.code"
    if (ch == '/') {
#line 271 "tests/99__calculator/test.code"
        return (struct test_Token){.variant = 5, .variant_5 = (struct test_Divide){.span = (struct calculator__source_Span){.start = self->index - 1, .end = self->index}}};
    }
#line 273 "tests/99__calculator/test.code"
    return (struct test_Token){.variant = 7, .variant_7 = (struct test_Error){.span = (struct calculator__source_Span){.start = self->index - 1, .end = self->index}, .message = (struct String){.data = "Unexpected character", .length = 20}}};
}

#line 279 "tests/99__calculator/test.code"
struct test_Token ptest_Tokenizer__scan_number_token(struct test_Tokenizer *self) {
#line 280 "tests/99__calculator/test.code"
    int32_t start = self->index;
#line 281 "tests/99__calculator/test.code"
    int32_t value = 0;
#line 282 "tests/99__calculator/test.code"
    for (;;) {
#line 283 "tests/99__calculator/test.code"
        uint8_t c = self->data[self->index];
#line 284 "tests/99__calculator/test.code"
        if (c < '0' || c > '9') {
#line 285 "tests/99__calculator/test.code"
            break;
        }
#line 287 "tests/99__calculator/test.code"
        value = value * 10 + ((int32_t) (c - '0'));
#line 288 "tests/99__calculator/test.code"
        self->index = self->index + 1;
    }
#line 290 "tests/99__calculator/test.code"
    return (struct test_Token){.variant = 1, .variant_1 = (struct test_Number){.span = (struct calculator__source_Span){.start = start, .end = self->index}, .value = value}};
}

#line 338 "tests/99__calculator/test.code"
struct calculator__source_Span ptest_Token__span(struct test_Token *self) {
#line 339 "tests/99__calculator/test.code"
    struct test_Token *__switch_339_value__ = self;
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
        return (struct calculator__source_Span){.start = 0, .end = 0};
    }
}

#line 367 "tests/99__calculator/test.code"
struct io_Writer *pio_Writer__write__1_token(struct io_Writer *self, struct test_Token *token) {
#line 368 "tests/99__calculator/test.code"
    struct test_Token *__switch_368_value__ = token;
#line 369 "tests/99__calculator/test.code"
    if (__switch_368_value__->variant == 1) {
#line 370 "tests/99__calculator/test.code"
        return pio_Writer__write__1_signed(pio_Writer__write(self, (struct String){.data = "Number: ", .length = 8}), __switch_368_value__->variant_1.value);
    }
#line 372 "tests/99__calculator/test.code"
    else if (__switch_368_value__->variant == 2) {
#line 373 "tests/99__calculator/test.code"
        return pio_Writer__write(self, (struct String){.data = "Plus", .length = 4});
    }
#line 375 "tests/99__calculator/test.code"
    else if (__switch_368_value__->variant == 3) {
#line 376 "tests/99__calculator/test.code"
        return pio_Writer__write(self, (struct String){.data = "Minus", .length = 5});
    }
#line 378 "tests/99__calculator/test.code"
    else if (__switch_368_value__->variant == 4) {
#line 379 "tests/99__calculator/test.code"
        return pio_Writer__write(self, (struct String){.data = "Multiply", .length = 8});
    }
#line 381 "tests/99__calculator/test.code"
    else if (__switch_368_value__->variant == 5) {
#line 382 "tests/99__calculator/test.code"
        return pio_Writer__write(self, (struct String){.data = "Divide", .length = 6});
    }
#line 384 "tests/99__calculator/test.code"
    else if (__switch_368_value__->variant == 6) {
#line 385 "tests/99__calculator/test.code"
        return pio_Writer__write(self, (struct String){.data = "Stop", .length = 4});
    }
#line 387 "tests/99__calculator/test.code"
    else if (__switch_368_value__->variant == 7) {
#line 388 "tests/99__calculator/test.code"
        return pio_Writer__write(pio_Writer__write(self, (struct String){.data = "Error: ", .length = 7}), __switch_368_value__->variant_7.message);
    }
#line 390 "tests/99__calculator/test.code"
    else if (__switch_368_value__->variant == 0) {
#line 391 "tests/99__calculator/test.code"
        return pio_Writer__write(self, (struct String){.data = "Nil!", .length = 4});
    }
#line 394 "tests/99__calculator/test.code"
    return self;
}

#line 405 "tests/99__calculator/test.code"
struct test_String_Builder *ptest_String_Builder__write__1_char(struct test_String_Builder *self, uint8_t c) {
#line 406 "tests/99__calculator/test.code"
    if (self->length == self->data_size) {
#line 407 "tests/99__calculator/test.code"
        self->data_size = self->data_size + 8;
#line 408 "tests/99__calculator/test.code"
        self->data = ((uint8_t *) realloc(((void *) self->data), ((uint64_t) self->data_size)));
    }
#line 413 "tests/99__calculator/test.code"
    self->data[self->length] = c;
#line 414 "tests/99__calculator/test.code"
    self->length = self->length + 1;
#line 415 "tests/99__calculator/test.code"
    return self;
}

#line 418 "tests/99__calculator/test.code"
struct String ptest_String_Builder__build(struct test_String_Builder *self) {
#line 419 "tests/99__calculator/test.code"
    ptest_String_Builder__write__1_char(self, 0);
#line 420 "tests/99__calculator/test.code"
    struct String string = (struct String){.data = self->data, .length = self->length - 1};
#line 424 "tests/99__calculator/test.code"
    return *((struct String *) (&string));
}

#line 427 "tests/99__calculator/test.code"
struct test_String_Builder test__make_string_builder() {
#line 428 "tests/99__calculator/test.code"
    return test__make_string_builder__0_initial_data_size(4);
}

#line 431 "tests/99__calculator/test.code"
struct test_String_Builder test__make_string_builder__0_initial_data_size(int32_t initial_data_size) {
#line 432 "tests/99__calculator/test.code"
    return (struct test_String_Builder){.data = ((uint8_t *) malloc(((uint64_t) initial_data_size))), .data_size = initial_data_size, .length = 0};
}

#line 439 "tests/99__calculator/test.code"
void ptest_String_Builder__write_char(struct test_String_Builder *self, uint8_t c) {
#line 440 "tests/99__calculator/test.code"
    ptest_String_Builder__write__1_char(self, c);
}

#line 450 "tests/99__calculator/test.code"
struct io_Writer *pio_Writer__write(struct io_Writer *self, struct String string) {
#line 451 "tests/99__calculator/test.code"
    struct String string_copy = string;
#line 452 "tests/99__calculator/test.code"
    uint8_t *string_data = ((struct String *) (&string_copy))->data;
#line 453 "tests/99__calculator/test.code"
    uintmax_t index = 0;
#line 454 "tests/99__calculator/test.code"
    while (index < string.length) {
#line 455 "tests/99__calculator/test.code"
        pio_Writer__write__1_char(self, string_data[index]);
#line 456 "tests/99__calculator/test.code"
        index = index + 1;
    }
#line 458 "tests/99__calculator/test.code"
    return self;
}

int32_t main(int argc, const char **argv) {
    return test__main(argc, (uint8_t **)argv);
}

