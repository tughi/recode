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

#line 43 "tests/99__calculator/calculator/expression.code"
struct calculator__source_Span pcalculator__expression_Expression__span(struct calculator__expression_Expression *self) {
#line 44 "tests/99__calculator/calculator/expression.code"
    struct calculator__expression_Expression *__switch_44_value__ = self;
#line 45 "tests/99__calculator/calculator/expression.code"
    if (__switch_44_value__->variant == 1) {
#line 46 "tests/99__calculator/calculator/expression.code"
        return __switch_44_value__->variant_1.span;
    }
#line 48 "tests/99__calculator/calculator/expression.code"
    else if (__switch_44_value__->variant == 2) {
#line 49 "tests/99__calculator/calculator/expression.code"
        return __switch_44_value__->variant_2.span;
    }
#line 51 "tests/99__calculator/calculator/expression.code"
    else if (__switch_44_value__->variant == 3) {
#line 52 "tests/99__calculator/calculator/expression.code"
        return __switch_44_value__->variant_3.span;
    }
#line 54 "tests/99__calculator/calculator/expression.code"
    else if (__switch_44_value__->variant == 4) {
#line 55 "tests/99__calculator/calculator/expression.code"
        return __switch_44_value__->variant_4.span;
    }
#line 57 "tests/99__calculator/calculator/expression.code"
    else if (__switch_44_value__->variant == 5) {
#line 58 "tests/99__calculator/calculator/expression.code"
        return __switch_44_value__->variant_5.span;
    }
#line 60 "tests/99__calculator/calculator/expression.code"
    else if (__switch_44_value__->variant == 6) {
#line 61 "tests/99__calculator/calculator/expression.code"
        return __switch_44_value__->variant_6.span;
    }
#line 63 "tests/99__calculator/calculator/expression.code"
    else {
    }
#line 67 "tests/99__calculator/calculator/expression.code"
    exit(1);
}

#line 70 "tests/99__calculator/calculator/expression.code"
struct io_Writer *pio_Writer__write_expression(struct io_Writer *self, struct calculator__expression_Expression *expression) {
#line 71 "tests/99__calculator/calculator/expression.code"
    struct calculator__expression_Expression *__switch_71_value__ = expression;
#line 72 "tests/99__calculator/calculator/expression.code"
    if (__switch_71_value__->variant == 1) {
#line 73 "tests/99__calculator/calculator/expression.code"
        return pio_Writer__write_signed(self, __switch_71_value__->variant_1.value);
    }
#line 75 "tests/99__calculator/calculator/expression.code"
    else if (__switch_71_value__->variant == 2) {
#line 76 "tests/99__calculator/calculator/expression.code"
        return pio_Writer__write_string(pio_Writer__write_expression(pio_Writer__write_string(pio_Writer__write_expression(pio_Writer__write_string(self, (struct String){.data = "(", .length = 1}), __switch_71_value__->variant_2.left), (struct String){.data = " + ", .length = 3}), __switch_71_value__->variant_2.right), (struct String){.data = ")", .length = 1});
    }
#line 78 "tests/99__calculator/calculator/expression.code"
    else if (__switch_71_value__->variant == 3) {
#line 79 "tests/99__calculator/calculator/expression.code"
        return pio_Writer__write_string(pio_Writer__write_expression(pio_Writer__write_string(pio_Writer__write_expression(pio_Writer__write_string(self, (struct String){.data = "(", .length = 1}), __switch_71_value__->variant_3.left), (struct String){.data = " / ", .length = 3}), __switch_71_value__->variant_3.right), (struct String){.data = ")", .length = 1});
    }
#line 81 "tests/99__calculator/calculator/expression.code"
    else if (__switch_71_value__->variant == 4) {
#line 82 "tests/99__calculator/calculator/expression.code"
        return pio_Writer__write_string(pio_Writer__write_expression(pio_Writer__write_string(pio_Writer__write_expression(pio_Writer__write_string(self, (struct String){.data = "(", .length = 1}), __switch_71_value__->variant_4.left), (struct String){.data = " * ", .length = 3}), __switch_71_value__->variant_4.right), (struct String){.data = ")", .length = 1});
    }
#line 84 "tests/99__calculator/calculator/expression.code"
    else if (__switch_71_value__->variant == 5) {
#line 85 "tests/99__calculator/calculator/expression.code"
        return pio_Writer__write_string(pio_Writer__write_expression(pio_Writer__write_string(pio_Writer__write_expression(pio_Writer__write_string(self, (struct String){.data = "(", .length = 1}), __switch_71_value__->variant_5.left), (struct String){.data = " - ", .length = 3}), __switch_71_value__->variant_5.right), (struct String){.data = ")", .length = 1});
    }
#line 87 "tests/99__calculator/calculator/expression.code"
    else if (__switch_71_value__->variant == 6) {
#line 88 "tests/99__calculator/calculator/expression.code"
        return pio_Writer__write_string(pio_Writer__write_string(self, (struct String){.data = "Error: ", .length = 7}), __switch_71_value__->variant_6.message);
    }
#line 90 "tests/99__calculator/calculator/expression.code"
    else if (__switch_71_value__->variant == 0) {
#line 91 "tests/99__calculator/calculator/expression.code"
        return pio_Writer__write_string(self, (struct String){.data = "Nil!", .length = 4});
    }
#line 94 "tests/99__calculator/calculator/expression.code"
    return self;
}

