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

#line 9 "tests/99__calculator/calculator/parser.code"
struct calculator__expression_Expression pcalculator__parser_Parser__parse_expression(struct calculator__parser_Parser *self) {
#line 10 "tests/99__calculator/calculator/parser.code"
    {
#line 10 "tests/99__calculator/calculator/parser.code"
        struct calculator__parser_Parser *__001__ = self;
#line 10 "tests/99__calculator/calculator/parser.code"
        return pcalculator__parser_Parser__parse_additive_expression(__001__);
    }
}

#line 13 "tests/99__calculator/calculator/parser.code"
struct calculator__expression_Expression pcalculator__parser_Parser__parse_additive_expression(struct calculator__parser_Parser *self) {
#line 14 "tests/99__calculator/calculator/parser.code"
    struct calculator__expression_Expression parsed_expression;
#line 14 "tests/99__calculator/calculator/parser.code"
    {
#line 14 "tests/99__calculator/calculator/parser.code"
        struct calculator__parser_Parser *__001__ = self;
#line 14 "tests/99__calculator/calculator/parser.code"
        parsed_expression = pcalculator__parser_Parser__parse_multiplicative_expression(__001__);
    }
#line 15 "tests/99__calculator/calculator/parser.code"
    for (;;) {
#line 16 "tests/99__calculator/calculator/parser.code"
        struct calculator__tokenizer_Token __switch_16_value__ = pcalculator__tokenizer_Tokenizer__peek_token(&self->tokenizer);
#line 17 "tests/99__calculator/calculator/parser.code"
        if (__switch_16_value__.variant == 2) {
#line 18 "tests/99__calculator/calculator/parser.code"
            {
#line 18 "tests/99__calculator/calculator/parser.code"
                struct calculator__tokenizer_Tokenizer *__001__ = &self->tokenizer;
#line 18 "tests/99__calculator/calculator/parser.code"
                pcalculator__tokenizer_Tokenizer__next_token(__001__);
            }
#line 19 "tests/99__calculator/calculator/parser.code"
            struct calculator__expression_Expression other_expression;
#line 19 "tests/99__calculator/calculator/parser.code"
            {
#line 19 "tests/99__calculator/calculator/parser.code"
                struct calculator__parser_Parser *__001__ = self;
#line 19 "tests/99__calculator/calculator/parser.code"
                other_expression = pcalculator__parser_Parser__parse_multiplicative_expression(__001__);
            }
#line 20 "tests/99__calculator/calculator/parser.code"
            {
#line 21 "tests/99__calculator/calculator/parser.code"
                struct calculator__expression_Expression *__001__ = &parsed_expression;
#line 21 "tests/99__calculator/calculator/parser.code"
                struct calculator__source_Span __002__ = pcalculator__expression_Expression__span(__001__);
#line 21 "tests/99__calculator/calculator/parser.code"
                int32_t __003__ = __002__.start;
#line 21 "tests/99__calculator/calculator/parser.code"
                struct calculator__expression_Expression *__004__ = &other_expression;
#line 21 "tests/99__calculator/calculator/parser.code"
                struct calculator__source_Span __005__ = pcalculator__expression_Expression__span(__004__);
#line 21 "tests/99__calculator/calculator/parser.code"
                int32_t __006__ = __005__.end;
#line 21 "tests/99__calculator/calculator/parser.code"
                struct calculator__source_Span __007__ = (struct calculator__source_Span){.start = __003__, .end = __006__};
#line 22 "tests/99__calculator/calculator/parser.code"
                struct calculator__expression_Expression *__008__ = (struct calculator__expression_Expression *)malloc(sizeof(struct calculator__expression_Expression));
#line 22 "tests/99__calculator/calculator/parser.code"
                *__008__ = parsed_expression;
#line 22 "tests/99__calculator/calculator/parser.code"
                struct calculator__expression_Expression *__009__ = __008__;
#line 23 "tests/99__calculator/calculator/parser.code"
                struct calculator__expression_Expression *__010__ = (struct calculator__expression_Expression *)malloc(sizeof(struct calculator__expression_Expression));
#line 23 "tests/99__calculator/calculator/parser.code"
                *__010__ = other_expression;
#line 23 "tests/99__calculator/calculator/parser.code"
                struct calculator__expression_Expression *__011__ = __010__;
#line 20 "tests/99__calculator/calculator/parser.code"
                parsed_expression = (struct calculator__expression_Expression){.variant = 2, .variant_2 = (struct calculator__expression_Addition){.span = __007__, .left = __009__, .right = __011__}};
            }
        }
#line 26 "tests/99__calculator/calculator/parser.code"
        else if (__switch_16_value__.variant == 3) {
#line 27 "tests/99__calculator/calculator/parser.code"
            {
#line 27 "tests/99__calculator/calculator/parser.code"
                struct calculator__tokenizer_Tokenizer *__001__ = &self->tokenizer;
#line 27 "tests/99__calculator/calculator/parser.code"
                pcalculator__tokenizer_Tokenizer__next_token(__001__);
            }
#line 28 "tests/99__calculator/calculator/parser.code"
            struct calculator__expression_Expression other_expression;
#line 28 "tests/99__calculator/calculator/parser.code"
            {
#line 28 "tests/99__calculator/calculator/parser.code"
                struct calculator__parser_Parser *__001__ = self;
#line 28 "tests/99__calculator/calculator/parser.code"
                other_expression = pcalculator__parser_Parser__parse_multiplicative_expression(__001__);
            }
#line 29 "tests/99__calculator/calculator/parser.code"
            {
#line 30 "tests/99__calculator/calculator/parser.code"
                struct calculator__expression_Expression *__001__ = &parsed_expression;
#line 30 "tests/99__calculator/calculator/parser.code"
                struct calculator__source_Span __002__ = pcalculator__expression_Expression__span(__001__);
#line 30 "tests/99__calculator/calculator/parser.code"
                int32_t __003__ = __002__.start;
#line 30 "tests/99__calculator/calculator/parser.code"
                struct calculator__expression_Expression *__004__ = &other_expression;
#line 30 "tests/99__calculator/calculator/parser.code"
                struct calculator__source_Span __005__ = pcalculator__expression_Expression__span(__004__);
#line 30 "tests/99__calculator/calculator/parser.code"
                int32_t __006__ = __005__.end;
#line 30 "tests/99__calculator/calculator/parser.code"
                struct calculator__source_Span __007__ = (struct calculator__source_Span){.start = __003__, .end = __006__};
#line 31 "tests/99__calculator/calculator/parser.code"
                struct calculator__expression_Expression *__008__ = (struct calculator__expression_Expression *)malloc(sizeof(struct calculator__expression_Expression));
#line 31 "tests/99__calculator/calculator/parser.code"
                *__008__ = parsed_expression;
#line 31 "tests/99__calculator/calculator/parser.code"
                struct calculator__expression_Expression *__009__ = __008__;
#line 32 "tests/99__calculator/calculator/parser.code"
                struct calculator__expression_Expression *__010__ = (struct calculator__expression_Expression *)malloc(sizeof(struct calculator__expression_Expression));
#line 32 "tests/99__calculator/calculator/parser.code"
                *__010__ = other_expression;
#line 32 "tests/99__calculator/calculator/parser.code"
                struct calculator__expression_Expression *__011__ = __010__;
#line 29 "tests/99__calculator/calculator/parser.code"
                parsed_expression = (struct calculator__expression_Expression){.variant = 5, .variant_5 = (struct calculator__expression_Subtraction){.span = __007__, .left = __009__, .right = __011__}};
            }
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
    struct calculator__expression_Expression parsed_expression;
#line 44 "tests/99__calculator/calculator/parser.code"
    {
#line 44 "tests/99__calculator/calculator/parser.code"
        struct calculator__parser_Parser *__001__ = self;
#line 44 "tests/99__calculator/calculator/parser.code"
        parsed_expression = pcalculator__parser_Parser__parse_primary_expression(__001__);
    }
#line 45 "tests/99__calculator/calculator/parser.code"
    for (;;) {
#line 46 "tests/99__calculator/calculator/parser.code"
        struct calculator__tokenizer_Token token;
#line 46 "tests/99__calculator/calculator/parser.code"
        {
#line 46 "tests/99__calculator/calculator/parser.code"
            struct calculator__tokenizer_Tokenizer *__001__ = &self->tokenizer;
#line 46 "tests/99__calculator/calculator/parser.code"
            token = pcalculator__tokenizer_Tokenizer__peek_token(__001__);
        }
#line 47 "tests/99__calculator/calculator/parser.code"
        if (token.variant == 4) {
#line 48 "tests/99__calculator/calculator/parser.code"
            {
#line 48 "tests/99__calculator/calculator/parser.code"
                struct calculator__tokenizer_Tokenizer *__001__ = &self->tokenizer;
#line 48 "tests/99__calculator/calculator/parser.code"
                pcalculator__tokenizer_Tokenizer__next_token(__001__);
            }
#line 49 "tests/99__calculator/calculator/parser.code"
            struct calculator__expression_Expression other_expression;
#line 49 "tests/99__calculator/calculator/parser.code"
            {
#line 49 "tests/99__calculator/calculator/parser.code"
                struct calculator__parser_Parser *__001__ = self;
#line 49 "tests/99__calculator/calculator/parser.code"
                other_expression = pcalculator__parser_Parser__parse_primary_expression(__001__);
            }
#line 50 "tests/99__calculator/calculator/parser.code"
            {
#line 51 "tests/99__calculator/calculator/parser.code"
                struct calculator__expression_Expression *__001__ = &parsed_expression;
#line 51 "tests/99__calculator/calculator/parser.code"
                struct calculator__source_Span __002__ = pcalculator__expression_Expression__span(__001__);
#line 51 "tests/99__calculator/calculator/parser.code"
                int32_t __003__ = __002__.start;
#line 51 "tests/99__calculator/calculator/parser.code"
                struct calculator__expression_Expression *__004__ = &other_expression;
#line 51 "tests/99__calculator/calculator/parser.code"
                struct calculator__source_Span __005__ = pcalculator__expression_Expression__span(__004__);
#line 51 "tests/99__calculator/calculator/parser.code"
                int32_t __006__ = __005__.end;
#line 51 "tests/99__calculator/calculator/parser.code"
                struct calculator__source_Span __007__ = (struct calculator__source_Span){.start = __003__, .end = __006__};
#line 52 "tests/99__calculator/calculator/parser.code"
                struct calculator__expression_Expression *__008__ = (struct calculator__expression_Expression *)malloc(sizeof(struct calculator__expression_Expression));
#line 52 "tests/99__calculator/calculator/parser.code"
                *__008__ = parsed_expression;
#line 52 "tests/99__calculator/calculator/parser.code"
                struct calculator__expression_Expression *__009__ = __008__;
#line 53 "tests/99__calculator/calculator/parser.code"
                struct calculator__expression_Expression *__010__ = (struct calculator__expression_Expression *)malloc(sizeof(struct calculator__expression_Expression));
#line 53 "tests/99__calculator/calculator/parser.code"
                *__010__ = other_expression;
#line 53 "tests/99__calculator/calculator/parser.code"
                struct calculator__expression_Expression *__011__ = __010__;
#line 50 "tests/99__calculator/calculator/parser.code"
                parsed_expression = (struct calculator__expression_Expression){.variant = 4, .variant_4 = (struct calculator__expression_Multiplication){.span = __007__, .left = __009__, .right = __011__}};
            }
        } else if (token.variant == 5) {
#line 56 "tests/99__calculator/calculator/parser.code"
            {
#line 56 "tests/99__calculator/calculator/parser.code"
                struct calculator__tokenizer_Tokenizer *__001__ = &self->tokenizer;
#line 56 "tests/99__calculator/calculator/parser.code"
                pcalculator__tokenizer_Tokenizer__next_token(__001__);
            }
#line 57 "tests/99__calculator/calculator/parser.code"
            struct calculator__expression_Expression other_expression;
#line 57 "tests/99__calculator/calculator/parser.code"
            {
#line 57 "tests/99__calculator/calculator/parser.code"
                struct calculator__parser_Parser *__001__ = self;
#line 57 "tests/99__calculator/calculator/parser.code"
                other_expression = pcalculator__parser_Parser__parse_primary_expression(__001__);
            }
#line 58 "tests/99__calculator/calculator/parser.code"
            {
#line 59 "tests/99__calculator/calculator/parser.code"
                struct calculator__expression_Expression *__001__ = &parsed_expression;
#line 59 "tests/99__calculator/calculator/parser.code"
                struct calculator__source_Span __002__ = pcalculator__expression_Expression__span(__001__);
#line 59 "tests/99__calculator/calculator/parser.code"
                int32_t __003__ = __002__.start;
#line 59 "tests/99__calculator/calculator/parser.code"
                struct calculator__expression_Expression *__004__ = &other_expression;
#line 59 "tests/99__calculator/calculator/parser.code"
                struct calculator__source_Span __005__ = pcalculator__expression_Expression__span(__004__);
#line 59 "tests/99__calculator/calculator/parser.code"
                int32_t __006__ = __005__.end;
#line 59 "tests/99__calculator/calculator/parser.code"
                struct calculator__source_Span __007__ = (struct calculator__source_Span){.start = __003__, .end = __006__};
#line 60 "tests/99__calculator/calculator/parser.code"
                struct calculator__expression_Expression *__008__ = (struct calculator__expression_Expression *)malloc(sizeof(struct calculator__expression_Expression));
#line 60 "tests/99__calculator/calculator/parser.code"
                *__008__ = parsed_expression;
#line 60 "tests/99__calculator/calculator/parser.code"
                struct calculator__expression_Expression *__009__ = __008__;
#line 61 "tests/99__calculator/calculator/parser.code"
                struct calculator__expression_Expression *__010__ = (struct calculator__expression_Expression *)malloc(sizeof(struct calculator__expression_Expression));
#line 61 "tests/99__calculator/calculator/parser.code"
                *__010__ = other_expression;
#line 61 "tests/99__calculator/calculator/parser.code"
                struct calculator__expression_Expression *__011__ = __010__;
#line 58 "tests/99__calculator/calculator/parser.code"
                parsed_expression = (struct calculator__expression_Expression){.variant = 3, .variant_3 = (struct calculator__expression_Division){.span = __007__, .left = __009__, .right = __011__}};
            }
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
    struct calculator__tokenizer_Token token;
#line 71 "tests/99__calculator/calculator/parser.code"
    {
#line 71 "tests/99__calculator/calculator/parser.code"
        struct calculator__tokenizer_Tokenizer *__001__ = &self->tokenizer;
#line 71 "tests/99__calculator/calculator/parser.code"
        token = pcalculator__tokenizer_Tokenizer__next_token(__001__);
    }
#line 72 "tests/99__calculator/calculator/parser.code"
    if (token.variant == 1) {
#line 73 "tests/99__calculator/calculator/parser.code"
        return (struct calculator__expression_Expression){.variant = 1, .variant_1 = token.variant_1};
    }
#line 75 "tests/99__calculator/calculator/parser.code"
    {
#line 76 "tests/99__calculator/calculator/parser.code"
        struct calculator__tokenizer_Token *__001__ = &token;
#line 76 "tests/99__calculator/calculator/parser.code"
        struct calculator__source_Span __002__ = pcalculator__tokenizer_Token__span(__001__);
#line 77 "tests/99__calculator/calculator/parser.code"
        struct String __003__ = (struct String){.data = "Expected number", .length = 15};
#line 75 "tests/99__calculator/calculator/parser.code"
        return (struct calculator__expression_Expression){.variant = 6, .variant_6 = (struct calculator__source_Error){.span = __002__, .message = __003__}};
    }
}

