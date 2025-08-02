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

#line 10 "tests/99__calculator/test.code"
int32_t test__main(int32_t argc, uint8_t **argv) {
#line 11 "tests/99__calculator/test.code"
    os__init();
#line 13 "tests/99__calculator/test.code"
    if (argc != 2) {
#line 14 "tests/99__calculator/test.code"
        {
#line 14 "tests/99__calculator/test.code"
            int32_t __001__ = 1;
#line 14 "tests/99__calculator/test.code"
            exit(__001__);
        }
    }
#line 17 "tests/99__calculator/test.code"
    struct calculator__tokenizer_Tokenizer input_tokenizer;
#line 17 "tests/99__calculator/test.code"
    {
#line 18 "tests/99__calculator/test.code"
        int32_t __001__ = 1;
#line 18 "tests/99__calculator/test.code"
        uint8_t *__002__ = argv[__001__];
#line 19 "tests/99__calculator/test.code"
        int32_t __003__ = 0;
#line 17 "tests/99__calculator/test.code"
        input_tokenizer = (struct calculator__tokenizer_Tokenizer){.data = __002__, .index = __003__};
    }
#line 22 "tests/99__calculator/test.code"
    for (;;) {
#line 22 "tests/99__calculator/test.code"
        {
#line 22 "tests/99__calculator/test.code"
            struct calculator__tokenizer_Tokenizer *__001__ = &input_tokenizer;
#line 22 "tests/99__calculator/test.code"
            if (pcalculator__tokenizer_Tokenizer__peek_token(__001__).variant != 6) {} else break;
        }
#line 23 "tests/99__calculator/test.code"
        struct calculator__tokenizer_Token token;
#line 23 "tests/99__calculator/test.code"
        {
#line 23 "tests/99__calculator/test.code"
            struct calculator__tokenizer_Tokenizer *__001__ = &input_tokenizer;
#line 23 "tests/99__calculator/test.code"
            token = pcalculator__tokenizer_Tokenizer__next_token(__001__);
        }
#line 24 "tests/99__calculator/test.code"
        {
#line 24 "tests/99__calculator/test.code"
            struct io_Writer *__001__ = os__stdout;
#line 24 "tests/99__calculator/test.code"
            struct calculator__tokenizer_Token *__002__ = &token;
#line 24 "tests/99__calculator/test.code"
            struct io_Writer *__003__ = pio_Writer__write_token(__001__, __002__);
#line 24 "tests/99__calculator/test.code"
            pio_Writer__end_line(__003__);
        }
    }
#line 27 "tests/99__calculator/test.code"
    struct calculator__parser_Parser input_parser;
#line 27 "tests/99__calculator/test.code"
    {
#line 28 "tests/99__calculator/test.code"
        int32_t __001__ = 1;
#line 28 "tests/99__calculator/test.code"
        uint8_t *__002__ = argv[__001__];
#line 29 "tests/99__calculator/test.code"
        int32_t __003__ = 0;
#line 27 "tests/99__calculator/test.code"
        struct calculator__tokenizer_Tokenizer __004__ = (struct calculator__tokenizer_Tokenizer){.data = __002__, .index = __003__};
#line 27 "tests/99__calculator/test.code"
        input_parser = (struct calculator__parser_Parser){.tokenizer = __004__};
    }
#line 31 "tests/99__calculator/test.code"
    struct calculator__expression_Expression expression;
#line 31 "tests/99__calculator/test.code"
    {
#line 31 "tests/99__calculator/test.code"
        struct calculator__parser_Parser *__001__ = &input_parser;
#line 31 "tests/99__calculator/test.code"
        expression = pcalculator__parser_Parser__parse_expression(__001__);
    }
#line 32 "tests/99__calculator/test.code"
    {
#line 32 "tests/99__calculator/test.code"
        struct io_Writer *__001__ = os__stdout;
#line 32 "tests/99__calculator/test.code"
        struct String __002__ = (struct String){.data = "Expression: ", .length = 12};
#line 32 "tests/99__calculator/test.code"
        struct io_Writer *__003__ = pio_Writer__write_string(__001__, __002__);
#line 32 "tests/99__calculator/test.code"
        struct calculator__expression_Expression *__004__ = &expression;
#line 32 "tests/99__calculator/test.code"
        struct io_Writer *__005__ = pio_Writer__write_expression(__003__, __004__);
#line 32 "tests/99__calculator/test.code"
        pio_Writer__end_line(__005__);
    }
#line 34 "tests/99__calculator/test.code"
    int32_t result;
#line 34 "tests/99__calculator/test.code"
    {
#line 34 "tests/99__calculator/test.code"
        struct calculator__expression_Expression *__001__ = &expression;
#line 34 "tests/99__calculator/test.code"
        result = test__evaluate(__001__);
    }
#line 35 "tests/99__calculator/test.code"
    {
#line 35 "tests/99__calculator/test.code"
        struct io_Writer *__001__ = os__stdout;
#line 35 "tests/99__calculator/test.code"
        struct String __002__ = (struct String){.data = "Result: ", .length = 8};
#line 35 "tests/99__calculator/test.code"
        struct io_Writer *__003__ = pio_Writer__write_string(__001__, __002__);
#line 35 "tests/99__calculator/test.code"
        int32_t __004__ = result;
#line 35 "tests/99__calculator/test.code"
        struct io_Writer *__005__ = pio_Writer__write_signed(__003__, __004__);
#line 35 "tests/99__calculator/test.code"
        pio_Writer__end_line(__005__);
    }
#line 37 "tests/99__calculator/test.code"
    return 0;
}

#line 40 "tests/99__calculator/test.code"
int32_t test__evaluate(struct calculator__expression_Expression *expression) {
#line 41 "tests/99__calculator/test.code"
    struct calculator__expression_Expression *__switch_41_value__ = expression;
#line 42 "tests/99__calculator/test.code"
    if (__switch_41_value__->variant == 1) {
#line 43 "tests/99__calculator/test.code"
        return __switch_41_value__->variant_1.value;
    }
#line 45 "tests/99__calculator/test.code"
    else if (__switch_41_value__->variant == 2) {
#line 46 "tests/99__calculator/test.code"
        {
#line 46 "tests/99__calculator/test.code"
            struct calculator__expression_Expression *__001__ = __switch_41_value__->variant_2.left;
#line 46 "tests/99__calculator/test.code"
            struct calculator__expression_Expression *__002__ = __switch_41_value__->variant_2.right;
#line 46 "tests/99__calculator/test.code"
            return test__evaluate(__001__) + test__evaluate(__002__);
        }
    }
#line 48 "tests/99__calculator/test.code"
    else if (__switch_41_value__->variant == 3) {
#line 49 "tests/99__calculator/test.code"
        {
#line 49 "tests/99__calculator/test.code"
            struct calculator__expression_Expression *__001__ = __switch_41_value__->variant_3.left;
#line 49 "tests/99__calculator/test.code"
            struct calculator__expression_Expression *__002__ = __switch_41_value__->variant_3.right;
#line 49 "tests/99__calculator/test.code"
            return test__evaluate(__001__) / test__evaluate(__002__);
        }
    }
#line 51 "tests/99__calculator/test.code"
    else if (__switch_41_value__->variant == 4) {
#line 52 "tests/99__calculator/test.code"
        {
#line 52 "tests/99__calculator/test.code"
            struct calculator__expression_Expression *__001__ = __switch_41_value__->variant_4.left;
#line 52 "tests/99__calculator/test.code"
            struct calculator__expression_Expression *__002__ = __switch_41_value__->variant_4.right;
#line 52 "tests/99__calculator/test.code"
            return test__evaluate(__001__) * test__evaluate(__002__);
        }
    }
#line 54 "tests/99__calculator/test.code"
    else if (__switch_41_value__->variant == 5) {
#line 55 "tests/99__calculator/test.code"
        {
#line 55 "tests/99__calculator/test.code"
            struct calculator__expression_Expression *__001__ = __switch_41_value__->variant_5.left;
#line 55 "tests/99__calculator/test.code"
            struct calculator__expression_Expression *__002__ = __switch_41_value__->variant_5.right;
#line 55 "tests/99__calculator/test.code"
            return test__evaluate(__001__) - test__evaluate(__002__);
        }
    }
#line 57 "tests/99__calculator/test.code"
    else {
#line 58 "tests/99__calculator/test.code"
        {
#line 58 "tests/99__calculator/test.code"
            int32_t __001__ = 1;
#line 58 "tests/99__calculator/test.code"
            exit(__001__);
        }
    }
}

int32_t main(int argc, const char **argv) {
    return test__main(argc, (uint8_t **)argv);
}

