#include "test.h"
#include "calculator__expression.h"
#include "calculator__parser.h"
#include "calculator__tokenizer.h"
#include "calculator__source.h"
#include "io.h"
#include "libc.h"
#include "os.h"
#include "string.h"

void *malloc(uintmax_t size);

#line 10 "tests/99__calculator/test.code"
int32_t test__main__anon__anon(int32_t argc, uint8_t **argv) {
#line 11 "tests/99__calculator/test.code"
    os__init();
#line 13 "tests/99__calculator/test.code"
    if (argc != 2) {
#line 14 "tests/99__calculator/test.code"
        exit(1);
#line 15 "tests/99__calculator/test.code"
    }
#line 17 "tests/99__calculator/test.code"
    struct calculator__tokenizer_Tokenizer input_tokenizer = (struct calculator__tokenizer_Tokenizer){.data = argv[1], .index = 0};
#line 22 "tests/99__calculator/test.code"
    while (pcalculator__tokenizer_Tokenizer__peek_token(&input_tokenizer).variant != 6) {
#line 23 "tests/99__calculator/test.code"
        struct calculator__tokenizer_Token token = pcalculator__tokenizer_Tokenizer__next_token(&input_tokenizer);
#line 24 "tests/99__calculator/test.code"
        pio_Writer__end_line(pio_Writer__write_token__anon(os__stdout, &token));
#line 25 "tests/99__calculator/test.code"
    }
#line 27 "tests/99__calculator/test.code"
    struct calculator__parser_Parser input_parser = (struct calculator__parser_Parser){.tokenizer = (struct calculator__tokenizer_Tokenizer){.data = argv[1], .index = 0}};
#line 31 "tests/99__calculator/test.code"
    struct calculator__expression_Expression expression = pcalculator__parser_Parser__parse_expression(&input_parser);
#line 32 "tests/99__calculator/test.code"
    pio_Writer__end_line(pio_Writer__write_expression__anon(pio_Writer__write_string__anon(os__stdout, (struct String){.data = "Expression: ", .length = 12}), &expression));
#line 34 "tests/99__calculator/test.code"
    int32_t result = test__evaluate__expression(&expression);
#line 35 "tests/99__calculator/test.code"
    pio_Writer__end_line(pio_Writer__write_signed__signed(pio_Writer__write_string__anon(os__stdout, (struct String){.data = "Result: ", .length = 8}), result));
#line 37 "tests/99__calculator/test.code"
    {
#line 37 "tests/99__calculator/test.code"
        int32_t __001__ = 0;
#line 37 "tests/99__calculator/test.code"
        return __001__;
#line 37 "tests/99__calculator/test.code"
    }
#line 38 "tests/99__calculator/test.code"
}

#line 40 "tests/99__calculator/test.code"
int32_t test__evaluate__expression(struct calculator__expression_Expression *expression) {
#line 41 "tests/99__calculator/test.code"
    struct calculator__expression_Expression *__switch_41_value__ = expression;
#line 42 "tests/99__calculator/test.code"
    if (__switch_41_value__->variant == 1) {
#line 43 "tests/99__calculator/test.code"
        {
#line 43 "tests/99__calculator/test.code"
            int32_t __001__ = __switch_41_value__->variant_1.value;
#line 43 "tests/99__calculator/test.code"
            return __001__;
#line 43 "tests/99__calculator/test.code"
        }
#line 44 "tests/99__calculator/test.code"
    }
#line 45 "tests/99__calculator/test.code"
    else if (__switch_41_value__->variant == 2) {
#line 46 "tests/99__calculator/test.code"
        {
#line 46 "tests/99__calculator/test.code"
            int32_t __002__ = test__evaluate__expression(__switch_41_value__->variant_2.left) + test__evaluate__expression(__switch_41_value__->variant_2.right);
#line 46 "tests/99__calculator/test.code"
            return __002__;
#line 46 "tests/99__calculator/test.code"
        }
#line 47 "tests/99__calculator/test.code"
    }
#line 48 "tests/99__calculator/test.code"
    else if (__switch_41_value__->variant == 3) {
#line 49 "tests/99__calculator/test.code"
        {
#line 49 "tests/99__calculator/test.code"
            int32_t __003__ = test__evaluate__expression(__switch_41_value__->variant_3.left) / test__evaluate__expression(__switch_41_value__->variant_3.right);
#line 49 "tests/99__calculator/test.code"
            return __003__;
#line 49 "tests/99__calculator/test.code"
        }
#line 50 "tests/99__calculator/test.code"
    }
#line 51 "tests/99__calculator/test.code"
    else if (__switch_41_value__->variant == 4) {
#line 52 "tests/99__calculator/test.code"
        {
#line 52 "tests/99__calculator/test.code"
            int32_t __004__ = test__evaluate__expression(__switch_41_value__->variant_4.left) * test__evaluate__expression(__switch_41_value__->variant_4.right);
#line 52 "tests/99__calculator/test.code"
            return __004__;
#line 52 "tests/99__calculator/test.code"
        }
#line 53 "tests/99__calculator/test.code"
    }
#line 54 "tests/99__calculator/test.code"
    else if (__switch_41_value__->variant == 5) {
#line 55 "tests/99__calculator/test.code"
        {
#line 55 "tests/99__calculator/test.code"
            int32_t __005__ = test__evaluate__expression(__switch_41_value__->variant_5.left) - test__evaluate__expression(__switch_41_value__->variant_5.right);
#line 55 "tests/99__calculator/test.code"
            return __005__;
#line 55 "tests/99__calculator/test.code"
        }
#line 56 "tests/99__calculator/test.code"
    }
#line 57 "tests/99__calculator/test.code"
    else {
#line 59 "tests/99__calculator/test.code"
    }
#line 61 "tests/99__calculator/test.code"
    exit(1);
#line 62 "tests/99__calculator/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main__anon__anon(argc, (uint8_t **)argv);
}

