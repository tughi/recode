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

#line 43 "tests/99__calculator/calculator/expression/expression.code"
struct calculator__source_Span pcalculator__expression_Expression__span(struct calculator__expression_Expression *self) {
#line 44 "tests/99__calculator/calculator/expression/expression.code"
    struct calculator__expression_Expression *__switch_44_value__ = self;
#line 45 "tests/99__calculator/calculator/expression/expression.code"
    if (__switch_44_value__->variant == 1) {
#line 46 "tests/99__calculator/calculator/expression/expression.code"
        {
#line 46 "tests/99__calculator/calculator/expression/expression.code"
            struct calculator__source_Span __001__ = __switch_44_value__->variant_1.span;
#line 46 "tests/99__calculator/calculator/expression/expression.code"
            return __001__;
#line 46 "tests/99__calculator/calculator/expression/expression.code"
        }
#line 47 "tests/99__calculator/calculator/expression/expression.code"
    }
#line 48 "tests/99__calculator/calculator/expression/expression.code"
    else if (__switch_44_value__->variant == 2) {
#line 49 "tests/99__calculator/calculator/expression/expression.code"
        {
#line 49 "tests/99__calculator/calculator/expression/expression.code"
            struct calculator__source_Span __002__ = __switch_44_value__->variant_2.span;
#line 49 "tests/99__calculator/calculator/expression/expression.code"
            return __002__;
#line 49 "tests/99__calculator/calculator/expression/expression.code"
        }
#line 50 "tests/99__calculator/calculator/expression/expression.code"
    }
#line 51 "tests/99__calculator/calculator/expression/expression.code"
    else if (__switch_44_value__->variant == 3) {
#line 52 "tests/99__calculator/calculator/expression/expression.code"
        {
#line 52 "tests/99__calculator/calculator/expression/expression.code"
            struct calculator__source_Span __003__ = __switch_44_value__->variant_3.span;
#line 52 "tests/99__calculator/calculator/expression/expression.code"
            return __003__;
#line 52 "tests/99__calculator/calculator/expression/expression.code"
        }
#line 53 "tests/99__calculator/calculator/expression/expression.code"
    }
#line 54 "tests/99__calculator/calculator/expression/expression.code"
    else if (__switch_44_value__->variant == 4) {
#line 55 "tests/99__calculator/calculator/expression/expression.code"
        {
#line 55 "tests/99__calculator/calculator/expression/expression.code"
            struct calculator__source_Span __004__ = __switch_44_value__->variant_4.span;
#line 55 "tests/99__calculator/calculator/expression/expression.code"
            return __004__;
#line 55 "tests/99__calculator/calculator/expression/expression.code"
        }
#line 56 "tests/99__calculator/calculator/expression/expression.code"
    }
#line 57 "tests/99__calculator/calculator/expression/expression.code"
    else if (__switch_44_value__->variant == 5) {
#line 58 "tests/99__calculator/calculator/expression/expression.code"
        {
#line 58 "tests/99__calculator/calculator/expression/expression.code"
            struct calculator__source_Span __005__ = __switch_44_value__->variant_5.span;
#line 58 "tests/99__calculator/calculator/expression/expression.code"
            return __005__;
#line 58 "tests/99__calculator/calculator/expression/expression.code"
        }
#line 59 "tests/99__calculator/calculator/expression/expression.code"
    }
#line 60 "tests/99__calculator/calculator/expression/expression.code"
    else if (__switch_44_value__->variant == 6) {
#line 61 "tests/99__calculator/calculator/expression/expression.code"
        {
#line 61 "tests/99__calculator/calculator/expression/expression.code"
            struct calculator__source_Span __006__ = __switch_44_value__->variant_6.span;
#line 61 "tests/99__calculator/calculator/expression/expression.code"
            return __006__;
#line 61 "tests/99__calculator/calculator/expression/expression.code"
        }
#line 62 "tests/99__calculator/calculator/expression/expression.code"
    }
#line 63 "tests/99__calculator/calculator/expression/expression.code"
    else {
#line 65 "tests/99__calculator/calculator/expression/expression.code"
    }
#line 67 "tests/99__calculator/calculator/expression/expression.code"
    exit(1);
#line 68 "tests/99__calculator/calculator/expression/expression.code"
}

#line 70 "tests/99__calculator/calculator/expression/expression.code"
struct io_Writer *pio_Writer__write_expression__anon(struct io_Writer *self, struct calculator__expression_Expression *expression) {
#line 71 "tests/99__calculator/calculator/expression/expression.code"
    struct calculator__expression_Expression *__switch_71_value__ = expression;
#line 72 "tests/99__calculator/calculator/expression/expression.code"
    if (__switch_71_value__->variant == 1) {
#line 73 "tests/99__calculator/calculator/expression/expression.code"
        {
#line 73 "tests/99__calculator/calculator/expression/expression.code"
            struct io_Writer *__001__ = pio_Writer__write_signed__signed(self, __switch_71_value__->variant_1.value);
#line 73 "tests/99__calculator/calculator/expression/expression.code"
            return __001__;
#line 73 "tests/99__calculator/calculator/expression/expression.code"
        }
#line 74 "tests/99__calculator/calculator/expression/expression.code"
    }
#line 75 "tests/99__calculator/calculator/expression/expression.code"
    else if (__switch_71_value__->variant == 2) {
#line 76 "tests/99__calculator/calculator/expression/expression.code"
        {
#line 76 "tests/99__calculator/calculator/expression/expression.code"
            struct io_Writer *__002__ = pio_Writer__write_string__anon(pio_Writer__write_expression__anon(pio_Writer__write_string__anon(pio_Writer__write_expression__anon(pio_Writer__write_string__anon(self, (struct String){.data = "(", .length = 1}), __switch_71_value__->variant_2.left), (struct String){.data = " + ", .length = 3}), __switch_71_value__->variant_2.right), (struct String){.data = ")", .length = 1});
#line 76 "tests/99__calculator/calculator/expression/expression.code"
            return __002__;
#line 76 "tests/99__calculator/calculator/expression/expression.code"
        }
#line 77 "tests/99__calculator/calculator/expression/expression.code"
    }
#line 78 "tests/99__calculator/calculator/expression/expression.code"
    else if (__switch_71_value__->variant == 3) {
#line 79 "tests/99__calculator/calculator/expression/expression.code"
        {
#line 79 "tests/99__calculator/calculator/expression/expression.code"
            struct io_Writer *__003__ = pio_Writer__write_string__anon(pio_Writer__write_expression__anon(pio_Writer__write_string__anon(pio_Writer__write_expression__anon(pio_Writer__write_string__anon(self, (struct String){.data = "(", .length = 1}), __switch_71_value__->variant_3.left), (struct String){.data = " / ", .length = 3}), __switch_71_value__->variant_3.right), (struct String){.data = ")", .length = 1});
#line 79 "tests/99__calculator/calculator/expression/expression.code"
            return __003__;
#line 79 "tests/99__calculator/calculator/expression/expression.code"
        }
#line 80 "tests/99__calculator/calculator/expression/expression.code"
    }
#line 81 "tests/99__calculator/calculator/expression/expression.code"
    else if (__switch_71_value__->variant == 4) {
#line 82 "tests/99__calculator/calculator/expression/expression.code"
        {
#line 82 "tests/99__calculator/calculator/expression/expression.code"
            struct io_Writer *__004__ = pio_Writer__write_string__anon(pio_Writer__write_expression__anon(pio_Writer__write_string__anon(pio_Writer__write_expression__anon(pio_Writer__write_string__anon(self, (struct String){.data = "(", .length = 1}), __switch_71_value__->variant_4.left), (struct String){.data = " * ", .length = 3}), __switch_71_value__->variant_4.right), (struct String){.data = ")", .length = 1});
#line 82 "tests/99__calculator/calculator/expression/expression.code"
            return __004__;
#line 82 "tests/99__calculator/calculator/expression/expression.code"
        }
#line 83 "tests/99__calculator/calculator/expression/expression.code"
    }
#line 84 "tests/99__calculator/calculator/expression/expression.code"
    else if (__switch_71_value__->variant == 5) {
#line 85 "tests/99__calculator/calculator/expression/expression.code"
        {
#line 85 "tests/99__calculator/calculator/expression/expression.code"
            struct io_Writer *__005__ = pio_Writer__write_string__anon(pio_Writer__write_expression__anon(pio_Writer__write_string__anon(pio_Writer__write_expression__anon(pio_Writer__write_string__anon(self, (struct String){.data = "(", .length = 1}), __switch_71_value__->variant_5.left), (struct String){.data = " - ", .length = 3}), __switch_71_value__->variant_5.right), (struct String){.data = ")", .length = 1});
#line 85 "tests/99__calculator/calculator/expression/expression.code"
            return __005__;
#line 85 "tests/99__calculator/calculator/expression/expression.code"
        }
#line 86 "tests/99__calculator/calculator/expression/expression.code"
    }
#line 87 "tests/99__calculator/calculator/expression/expression.code"
    else if (__switch_71_value__->variant == 6) {
#line 88 "tests/99__calculator/calculator/expression/expression.code"
        {
#line 88 "tests/99__calculator/calculator/expression/expression.code"
            struct io_Writer *__006__ = pio_Writer__write_string__anon(pio_Writer__write_string__anon(self, (struct String){.data = "Error: ", .length = 7}), __switch_71_value__->variant_6.message);
#line 88 "tests/99__calculator/calculator/expression/expression.code"
            return __006__;
#line 88 "tests/99__calculator/calculator/expression/expression.code"
        }
#line 89 "tests/99__calculator/calculator/expression/expression.code"
    }
#line 90 "tests/99__calculator/calculator/expression/expression.code"
    else if (__switch_71_value__->variant == 0) {
#line 91 "tests/99__calculator/calculator/expression/expression.code"
        {
#line 91 "tests/99__calculator/calculator/expression/expression.code"
            struct io_Writer *__007__ = pio_Writer__write_string__anon(self, (struct String){.data = "Nil!", .length = 4});
#line 91 "tests/99__calculator/calculator/expression/expression.code"
            return __007__;
#line 91 "tests/99__calculator/calculator/expression/expression.code"
        }
#line 92 "tests/99__calculator/calculator/expression/expression.code"
    }
#line 94 "tests/99__calculator/calculator/expression/expression.code"
    {
#line 94 "tests/99__calculator/calculator/expression/expression.code"
        struct io_Writer *__008__ = self;
#line 94 "tests/99__calculator/calculator/expression/expression.code"
        return __008__;
#line 94 "tests/99__calculator/calculator/expression/expression.code"
    }
#line 95 "tests/99__calculator/calculator/expression/expression.code"
}

