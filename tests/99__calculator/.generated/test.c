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
        exit(1);
    }
#line 17 "tests/99__calculator/test.code"
    struct calculator__tokenizer_Tokenizer input_tokenizer = (struct calculator__tokenizer_Tokenizer){.data = argv[1], .index = 0};
#line 22 "tests/99__calculator/test.code"
    while (pcalculator__tokenizer_Tokenizer__peek_token(&input_tokenizer).variant != 6) {
#line 23 "tests/99__calculator/test.code"
        struct calculator__tokenizer_Token token = pcalculator__tokenizer_Tokenizer__next_token(&input_tokenizer);
#line 24 "tests/99__calculator/test.code"
        pio_Writer__end_line(pio_Writer__write_token(os__stdout, &token));
    }
#line 27 "tests/99__calculator/test.code"
    struct calculator__parser_Parser input_parser = (struct calculator__parser_Parser){.tokenizer = (struct calculator__tokenizer_Tokenizer){.data = argv[1], .index = 0}};
#line 31 "tests/99__calculator/test.code"
    struct calculator__expression_Expression expression = pcalculator__parser_Parser__parse_expression(&input_parser);
#line 32 "tests/99__calculator/test.code"
    pio_Writer__end_line(pio_Writer__write_expression(pio_Writer__write_string(os__stdout, (struct String){.data = "Expression: ", .length = 12}), &expression));
#line 34 "tests/99__calculator/test.code"
    int32_t result = test__evaluate(&expression);
#line 35 "tests/99__calculator/test.code"
    pio_Writer__end_line(pio_Writer__write_signed(pio_Writer__write_string(os__stdout, (struct String){.data = "Result: ", .length = 8}), result));
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
        return test__evaluate(__switch_41_value__->variant_2.left) + test__evaluate(__switch_41_value__->variant_2.right);
    }
#line 48 "tests/99__calculator/test.code"
    else if (__switch_41_value__->variant == 3) {
#line 49 "tests/99__calculator/test.code"
        return test__evaluate(__switch_41_value__->variant_3.left) / test__evaluate(__switch_41_value__->variant_3.right);
    }
#line 51 "tests/99__calculator/test.code"
    else if (__switch_41_value__->variant == 4) {
#line 52 "tests/99__calculator/test.code"
        return test__evaluate(__switch_41_value__->variant_4.left) * test__evaluate(__switch_41_value__->variant_4.right);
    }
#line 54 "tests/99__calculator/test.code"
    else if (__switch_41_value__->variant == 5) {
#line 55 "tests/99__calculator/test.code"
        return test__evaluate(__switch_41_value__->variant_5.left) - test__evaluate(__switch_41_value__->variant_5.right);
    }
#line 57 "tests/99__calculator/test.code"
    else {
    }
#line 61 "tests/99__calculator/test.code"
    exit(1);
}

int32_t main(int argc, const char **argv) {
    return test__main(argc, (uint8_t **)argv);
}

