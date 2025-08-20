#include "test.h"
#include "calculator__expression.h"
#include "calculator__source.h"
#include "libc.h"
#include "io.h"
#include "calculator__parser.h"
#include "calculator__tokenizer.h"
#include "os.h"
#include "string.h"

void *malloc(uintmax_t size);

#line 9 "tests/99__calculator/calculator/parser/parser.code"
struct calculator__expression_Expression pcalculator__parser_Parser__parse_expression(struct calculator__parser_Parser *self) {
#line 10 "tests/99__calculator/calculator/parser/parser.code"
    {
#line 10 "tests/99__calculator/calculator/parser/parser.code"
        struct calculator__expression_Expression __001__ = pcalculator__parser_Parser__parse_additive_expression(self);
#line 10 "tests/99__calculator/calculator/parser/parser.code"
        return __001__;
#line 10 "tests/99__calculator/calculator/parser/parser.code"
    }
#line 11 "tests/99__calculator/calculator/parser/parser.code"
}

#line 13 "tests/99__calculator/calculator/parser/parser.code"
struct calculator__expression_Expression pcalculator__parser_Parser__parse_additive_expression(struct calculator__parser_Parser *self) {
#line 14 "tests/99__calculator/calculator/parser/parser.code"
    struct calculator__expression_Expression parsed_expression = pcalculator__parser_Parser__parse_multiplicative_expression(self);
#line 15 "tests/99__calculator/calculator/parser/parser.code"
    for (;;) {
#line 16 "tests/99__calculator/calculator/parser/parser.code"
        struct calculator__tokenizer_Token __switch_16_value__ = pcalculator__tokenizer_Tokenizer__peek_token(&self->tokenizer);
#line 17 "tests/99__calculator/calculator/parser/parser.code"
        if (__switch_16_value__.variant == 2) {
#line 18 "tests/99__calculator/calculator/parser/parser.code"
            pcalculator__tokenizer_Tokenizer__next_token(&self->tokenizer);
#line 19 "tests/99__calculator/calculator/parser/parser.code"
            struct calculator__expression_Expression other_expression = pcalculator__parser_Parser__parse_multiplicative_expression(self);
#line 20 "tests/99__calculator/calculator/parser/parser.code"
            {
#line 21 "tests/99__calculator/calculator/parser/parser.code"
                struct calculator__source_Span __001__ = (struct calculator__source_Span){.start = pcalculator__expression_Expression__span(&parsed_expression).start, .end = pcalculator__expression_Expression__span(&other_expression).end};
#line 22 "tests/99__calculator/calculator/parser/parser.code"
                struct calculator__expression_Expression *__002__ = (struct calculator__expression_Expression *)malloc(sizeof(struct calculator__expression_Expression));
#line 22 "tests/99__calculator/calculator/parser/parser.code"
                *__002__ = parsed_expression;
#line 22 "tests/99__calculator/calculator/parser/parser.code"
                struct calculator__expression_Expression *__003__ = __002__;
#line 23 "tests/99__calculator/calculator/parser/parser.code"
                struct calculator__expression_Expression *__004__ = (struct calculator__expression_Expression *)malloc(sizeof(struct calculator__expression_Expression));
#line 23 "tests/99__calculator/calculator/parser/parser.code"
                *__004__ = other_expression;
#line 23 "tests/99__calculator/calculator/parser/parser.code"
                struct calculator__expression_Expression *__005__ = __004__;
#line 20 "tests/99__calculator/calculator/parser/parser.code"
                parsed_expression = (struct calculator__expression_Expression){.variant = 2, .variant_2 = (struct calculator__expression_Addition){.span = __001__, .left = __003__, .right = __005__}};
#line 24 "tests/99__calculator/calculator/parser/parser.code"
            }
#line 25 "tests/99__calculator/calculator/parser/parser.code"
        }
#line 26 "tests/99__calculator/calculator/parser/parser.code"
        else if (__switch_16_value__.variant == 3) {
#line 27 "tests/99__calculator/calculator/parser/parser.code"
            pcalculator__tokenizer_Tokenizer__next_token(&self->tokenizer);
#line 28 "tests/99__calculator/calculator/parser/parser.code"
            struct calculator__expression_Expression other_expression = pcalculator__parser_Parser__parse_multiplicative_expression(self);
#line 29 "tests/99__calculator/calculator/parser/parser.code"
            {
#line 30 "tests/99__calculator/calculator/parser/parser.code"
                struct calculator__source_Span __006__ = (struct calculator__source_Span){.start = pcalculator__expression_Expression__span(&parsed_expression).start, .end = pcalculator__expression_Expression__span(&other_expression).end};
#line 31 "tests/99__calculator/calculator/parser/parser.code"
                struct calculator__expression_Expression *__007__ = (struct calculator__expression_Expression *)malloc(sizeof(struct calculator__expression_Expression));
#line 31 "tests/99__calculator/calculator/parser/parser.code"
                *__007__ = parsed_expression;
#line 31 "tests/99__calculator/calculator/parser/parser.code"
                struct calculator__expression_Expression *__008__ = __007__;
#line 32 "tests/99__calculator/calculator/parser/parser.code"
                struct calculator__expression_Expression *__009__ = (struct calculator__expression_Expression *)malloc(sizeof(struct calculator__expression_Expression));
#line 32 "tests/99__calculator/calculator/parser/parser.code"
                *__009__ = other_expression;
#line 32 "tests/99__calculator/calculator/parser/parser.code"
                struct calculator__expression_Expression *__010__ = __009__;
#line 29 "tests/99__calculator/calculator/parser/parser.code"
                parsed_expression = (struct calculator__expression_Expression){.variant = 5, .variant_5 = (struct calculator__expression_Subtraction){.span = __006__, .left = __008__, .right = __010__}};
#line 33 "tests/99__calculator/calculator/parser/parser.code"
            }
#line 34 "tests/99__calculator/calculator/parser/parser.code"
        }
#line 35 "tests/99__calculator/calculator/parser/parser.code"
        else {
#line 36 "tests/99__calculator/calculator/parser/parser.code"
            break;
#line 37 "tests/99__calculator/calculator/parser/parser.code"
        }
#line 39 "tests/99__calculator/calculator/parser/parser.code"
    }
#line 40 "tests/99__calculator/calculator/parser/parser.code"
    {
#line 40 "tests/99__calculator/calculator/parser/parser.code"
        struct calculator__expression_Expression __011__ = parsed_expression;
#line 40 "tests/99__calculator/calculator/parser/parser.code"
        return __011__;
#line 40 "tests/99__calculator/calculator/parser/parser.code"
    }
#line 41 "tests/99__calculator/calculator/parser/parser.code"
}

#line 43 "tests/99__calculator/calculator/parser/parser.code"
struct calculator__expression_Expression pcalculator__parser_Parser__parse_multiplicative_expression(struct calculator__parser_Parser *self) {
#line 44 "tests/99__calculator/calculator/parser/parser.code"
    struct calculator__expression_Expression parsed_expression = pcalculator__parser_Parser__parse_primary_expression(self);
#line 45 "tests/99__calculator/calculator/parser/parser.code"
    for (;;) {
#line 46 "tests/99__calculator/calculator/parser/parser.code"
        struct calculator__tokenizer_Token token = pcalculator__tokenizer_Tokenizer__peek_token(&self->tokenizer);
#line 47 "tests/99__calculator/calculator/parser/parser.code"
        if (token.variant == 4) {
#line 48 "tests/99__calculator/calculator/parser/parser.code"
            pcalculator__tokenizer_Tokenizer__next_token(&self->tokenizer);
#line 49 "tests/99__calculator/calculator/parser/parser.code"
            struct calculator__expression_Expression other_expression = pcalculator__parser_Parser__parse_primary_expression(self);
#line 50 "tests/99__calculator/calculator/parser/parser.code"
            {
#line 51 "tests/99__calculator/calculator/parser/parser.code"
                struct calculator__source_Span __001__ = (struct calculator__source_Span){.start = pcalculator__expression_Expression__span(&parsed_expression).start, .end = pcalculator__expression_Expression__span(&other_expression).end};
#line 52 "tests/99__calculator/calculator/parser/parser.code"
                struct calculator__expression_Expression *__002__ = (struct calculator__expression_Expression *)malloc(sizeof(struct calculator__expression_Expression));
#line 52 "tests/99__calculator/calculator/parser/parser.code"
                *__002__ = parsed_expression;
#line 52 "tests/99__calculator/calculator/parser/parser.code"
                struct calculator__expression_Expression *__003__ = __002__;
#line 53 "tests/99__calculator/calculator/parser/parser.code"
                struct calculator__expression_Expression *__004__ = (struct calculator__expression_Expression *)malloc(sizeof(struct calculator__expression_Expression));
#line 53 "tests/99__calculator/calculator/parser/parser.code"
                *__004__ = other_expression;
#line 53 "tests/99__calculator/calculator/parser/parser.code"
                struct calculator__expression_Expression *__005__ = __004__;
#line 50 "tests/99__calculator/calculator/parser/parser.code"
                parsed_expression = (struct calculator__expression_Expression){.variant = 4, .variant_4 = (struct calculator__expression_Multiplication){.span = __001__, .left = __003__, .right = __005__}};
#line 54 "tests/99__calculator/calculator/parser/parser.code"
            }
#line 55 "tests/99__calculator/calculator/parser/parser.code"
        } else if (token.variant == 5) {
#line 56 "tests/99__calculator/calculator/parser/parser.code"
            pcalculator__tokenizer_Tokenizer__next_token(&self->tokenizer);
#line 57 "tests/99__calculator/calculator/parser/parser.code"
            struct calculator__expression_Expression other_expression = pcalculator__parser_Parser__parse_primary_expression(self);
#line 58 "tests/99__calculator/calculator/parser/parser.code"
            {
#line 59 "tests/99__calculator/calculator/parser/parser.code"
                struct calculator__source_Span __006__ = (struct calculator__source_Span){.start = pcalculator__expression_Expression__span(&parsed_expression).start, .end = pcalculator__expression_Expression__span(&other_expression).end};
#line 60 "tests/99__calculator/calculator/parser/parser.code"
                struct calculator__expression_Expression *__007__ = (struct calculator__expression_Expression *)malloc(sizeof(struct calculator__expression_Expression));
#line 60 "tests/99__calculator/calculator/parser/parser.code"
                *__007__ = parsed_expression;
#line 60 "tests/99__calculator/calculator/parser/parser.code"
                struct calculator__expression_Expression *__008__ = __007__;
#line 61 "tests/99__calculator/calculator/parser/parser.code"
                struct calculator__expression_Expression *__009__ = (struct calculator__expression_Expression *)malloc(sizeof(struct calculator__expression_Expression));
#line 61 "tests/99__calculator/calculator/parser/parser.code"
                *__009__ = other_expression;
#line 61 "tests/99__calculator/calculator/parser/parser.code"
                struct calculator__expression_Expression *__010__ = __009__;
#line 58 "tests/99__calculator/calculator/parser/parser.code"
                parsed_expression = (struct calculator__expression_Expression){.variant = 3, .variant_3 = (struct calculator__expression_Division){.span = __006__, .left = __008__, .right = __010__}};
#line 62 "tests/99__calculator/calculator/parser/parser.code"
            }
#line 63 "tests/99__calculator/calculator/parser/parser.code"
        } else {
#line 64 "tests/99__calculator/calculator/parser/parser.code"
            break;
#line 65 "tests/99__calculator/calculator/parser/parser.code"
        }
#line 66 "tests/99__calculator/calculator/parser/parser.code"
    }
#line 67 "tests/99__calculator/calculator/parser/parser.code"
    {
#line 67 "tests/99__calculator/calculator/parser/parser.code"
        struct calculator__expression_Expression __011__ = parsed_expression;
#line 67 "tests/99__calculator/calculator/parser/parser.code"
        return __011__;
#line 67 "tests/99__calculator/calculator/parser/parser.code"
    }
#line 68 "tests/99__calculator/calculator/parser/parser.code"
}

#line 70 "tests/99__calculator/calculator/parser/parser.code"
struct calculator__expression_Expression pcalculator__parser_Parser__parse_primary_expression(struct calculator__parser_Parser *self) {
#line 71 "tests/99__calculator/calculator/parser/parser.code"
    struct calculator__tokenizer_Token token = pcalculator__tokenizer_Tokenizer__next_token(&self->tokenizer);
#line 72 "tests/99__calculator/calculator/parser/parser.code"
    if (token.variant == 1) {
#line 73 "tests/99__calculator/calculator/parser/parser.code"
        {
#line 73 "tests/99__calculator/calculator/parser/parser.code"
            struct calculator__expression_Expression __001__ = (struct calculator__expression_Expression){.variant = 1, .variant_1 = token.variant_1};
#line 73 "tests/99__calculator/calculator/parser/parser.code"
            return __001__;
#line 73 "tests/99__calculator/calculator/parser/parser.code"
        }
#line 74 "tests/99__calculator/calculator/parser/parser.code"
    }
#line 75 "tests/99__calculator/calculator/parser/parser.code"
    {
#line 75 "tests/99__calculator/calculator/parser/parser.code"
        struct calculator__expression_Expression __002__ = (struct calculator__expression_Expression){.variant = 6, .variant_6 = (struct calculator__source_Error){.span = pcalculator__tokenizer_Token__span(&token), .message = (struct String){.data = "Expected number", .length = 15}}};
#line 75 "tests/99__calculator/calculator/parser/parser.code"
        return __002__;
#line 78 "tests/99__calculator/calculator/parser/parser.code"
    }
#line 79 "tests/99__calculator/calculator/parser/parser.code"
}

