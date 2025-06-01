#include "calculator__parser.h"

struct calculator__parser_Parser *__alloc__calculator__parser_Parser__(struct calculator__parser_Parser value) {
    struct calculator__parser_Parser *result = (struct calculator__parser_Parser *)malloc(sizeof(struct calculator__parser_Parser));
    *result = value;
    return result;
}

#line 9 "tests/99__calculator/calculator/parser.code"
struct calculator__expression_Expression pcalculator__parser_Parser__parse_expression(struct calculator__parser_Parser *self) {
#line 10 "tests/99__calculator/calculator/parser.code"
    return pcalculator__parser_Parser__parse_additive_expression(self);
}

#line 13 "tests/99__calculator/calculator/parser.code"
struct calculator__expression_Expression pcalculator__parser_Parser__parse_additive_expression(struct calculator__parser_Parser *self) {
#line 14 "tests/99__calculator/calculator/parser.code"
    struct calculator__expression_Expression parsed_expression = pcalculator__parser_Parser__parse_multiplicative_expression(self);
#line 15 "tests/99__calculator/calculator/parser.code"
    for (;;) {
#line 16 "tests/99__calculator/calculator/parser.code"
        struct calculator__tokenizer_Token __switch_16_value__ = pcalculator__tokenizer_Tokenizer__peek_token(&self->tokenizer);
#line 17 "tests/99__calculator/calculator/parser.code"
        if (__switch_16_value__.variant == 2) {
#line 18 "tests/99__calculator/calculator/parser.code"
            pcalculator__tokenizer_Tokenizer__next_token(&self->tokenizer);
#line 19 "tests/99__calculator/calculator/parser.code"
            struct calculator__expression_Expression other_expression = pcalculator__parser_Parser__parse_multiplicative_expression(self);
#line 20 "tests/99__calculator/calculator/parser.code"
            parsed_expression = (struct calculator__expression_Expression){.variant = 2, .variant_2 = (struct calculator__expression_Addition){.span = (struct calculator__source_Span){.start = pcalculator__expression_Expression__span(&parsed_expression).start, .end = pcalculator__expression_Expression__span(&other_expression).end}, .left = __alloc__calculator__expression_Expression__(parsed_expression), .right = __alloc__calculator__expression_Expression__(other_expression)}};
        }
#line 26 "tests/99__calculator/calculator/parser.code"
        else if (__switch_16_value__.variant == 3) {
#line 27 "tests/99__calculator/calculator/parser.code"
            pcalculator__tokenizer_Tokenizer__next_token(&self->tokenizer);
#line 28 "tests/99__calculator/calculator/parser.code"
            struct calculator__expression_Expression other_expression = pcalculator__parser_Parser__parse_multiplicative_expression(self);
#line 29 "tests/99__calculator/calculator/parser.code"
            parsed_expression = (struct calculator__expression_Expression){.variant = 5, .variant_5 = (struct calculator__expression_Subtraction){.span = (struct calculator__source_Span){.start = pcalculator__expression_Expression__span(&parsed_expression).start, .end = pcalculator__expression_Expression__span(&other_expression).end}, .left = __alloc__calculator__expression_Expression__(parsed_expression), .right = __alloc__calculator__expression_Expression__(other_expression)}};
        }
#line 35 "tests/99__calculator/calculator/parser.code"
        else {
#line 36 "tests/99__calculator/calculator/parser.code"
            break;
        }
    }
#line 40 "tests/99__calculator/calculator/parser.code"
    return parsed_expression;
}

#line 43 "tests/99__calculator/calculator/parser.code"
struct calculator__expression_Expression pcalculator__parser_Parser__parse_multiplicative_expression(struct calculator__parser_Parser *self) {
#line 44 "tests/99__calculator/calculator/parser.code"
    struct calculator__expression_Expression parsed_expression = pcalculator__parser_Parser__parse_primary_expression(self);
#line 45 "tests/99__calculator/calculator/parser.code"
    for (;;) {
#line 46 "tests/99__calculator/calculator/parser.code"
        struct calculator__tokenizer_Token token = pcalculator__tokenizer_Tokenizer__peek_token(&self->tokenizer);
#line 47 "tests/99__calculator/calculator/parser.code"
        if (token.variant == 4) {
#line 48 "tests/99__calculator/calculator/parser.code"
            pcalculator__tokenizer_Tokenizer__next_token(&self->tokenizer);
#line 49 "tests/99__calculator/calculator/parser.code"
            struct calculator__expression_Expression other_expression = pcalculator__parser_Parser__parse_primary_expression(self);
#line 50 "tests/99__calculator/calculator/parser.code"
            parsed_expression = (struct calculator__expression_Expression){.variant = 4, .variant_4 = (struct calculator__expression_Multiplication){.span = (struct calculator__source_Span){.start = pcalculator__expression_Expression__span(&parsed_expression).start, .end = pcalculator__expression_Expression__span(&other_expression).end}, .left = __alloc__calculator__expression_Expression__(parsed_expression), .right = __alloc__calculator__expression_Expression__(other_expression)}};
        } else if (token.variant == 5) {
#line 56 "tests/99__calculator/calculator/parser.code"
            pcalculator__tokenizer_Tokenizer__next_token(&self->tokenizer);
#line 57 "tests/99__calculator/calculator/parser.code"
            struct calculator__expression_Expression other_expression = pcalculator__parser_Parser__parse_primary_expression(self);
#line 58 "tests/99__calculator/calculator/parser.code"
            parsed_expression = (struct calculator__expression_Expression){.variant = 3, .variant_3 = (struct calculator__expression_Division){.span = (struct calculator__source_Span){.start = pcalculator__expression_Expression__span(&parsed_expression).start, .end = pcalculator__expression_Expression__span(&other_expression).end}, .left = __alloc__calculator__expression_Expression__(parsed_expression), .right = __alloc__calculator__expression_Expression__(other_expression)}};
        } else {
#line 64 "tests/99__calculator/calculator/parser.code"
            break;
        }
    }
#line 67 "tests/99__calculator/calculator/parser.code"
    return parsed_expression;
}

#line 70 "tests/99__calculator/calculator/parser.code"
struct calculator__expression_Expression pcalculator__parser_Parser__parse_primary_expression(struct calculator__parser_Parser *self) {
#line 71 "tests/99__calculator/calculator/parser.code"
    struct calculator__tokenizer_Token token = pcalculator__tokenizer_Tokenizer__next_token(&self->tokenizer);
#line 72 "tests/99__calculator/calculator/parser.code"
    if (token.variant == 1) {
#line 73 "tests/99__calculator/calculator/parser.code"
        return (struct calculator__expression_Expression){.variant = 1, .variant_1 = token.variant_1};
    }
#line 75 "tests/99__calculator/calculator/parser.code"
    return (struct calculator__expression_Expression){.variant = 6, .variant_6 = (struct calculator__source_Error){.span = pcalculator__tokenizer_Token__span(&token), .message = (struct String){.data = "Expected number", .length = 15}}};
}

