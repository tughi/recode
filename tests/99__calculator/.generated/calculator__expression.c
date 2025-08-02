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

#line 42 "tests/99__calculator/calculator/expression.code"
struct calculator__source_Span pcalculator__expression_Expression__span(struct calculator__expression_Expression *self) {
#line 43 "tests/99__calculator/calculator/expression.code"
    struct calculator__expression_Expression *__switch_43_value__ = self;
#line 44 "tests/99__calculator/calculator/expression.code"
    if (__switch_43_value__->variant == 1) {
#line 45 "tests/99__calculator/calculator/expression.code"
        return __switch_43_value__->variant_1.span;
    }
#line 47 "tests/99__calculator/calculator/expression.code"
    else if (__switch_43_value__->variant == 2) {
#line 48 "tests/99__calculator/calculator/expression.code"
        return __switch_43_value__->variant_2.span;
    }
#line 50 "tests/99__calculator/calculator/expression.code"
    else if (__switch_43_value__->variant == 3) {
#line 51 "tests/99__calculator/calculator/expression.code"
        return __switch_43_value__->variant_3.span;
    }
#line 53 "tests/99__calculator/calculator/expression.code"
    else if (__switch_43_value__->variant == 4) {
#line 54 "tests/99__calculator/calculator/expression.code"
        return __switch_43_value__->variant_4.span;
    }
#line 56 "tests/99__calculator/calculator/expression.code"
    else if (__switch_43_value__->variant == 5) {
#line 57 "tests/99__calculator/calculator/expression.code"
        return __switch_43_value__->variant_5.span;
    }
#line 59 "tests/99__calculator/calculator/expression.code"
    else if (__switch_43_value__->variant == 6) {
#line 60 "tests/99__calculator/calculator/expression.code"
        return __switch_43_value__->variant_6.span;
    }
#line 62 "tests/99__calculator/calculator/expression.code"
    else if (__switch_43_value__->variant == 0) {
#line 63 "tests/99__calculator/calculator/expression.code"
        {
#line 63 "tests/99__calculator/calculator/expression.code"
            int32_t __001__ = 0;
#line 63 "tests/99__calculator/calculator/expression.code"
            int32_t __002__ = 0;
#line 63 "tests/99__calculator/calculator/expression.code"
            return (struct calculator__source_Span){.start = __001__, .end = __002__};
        }
    }
}

#line 68 "tests/99__calculator/calculator/expression.code"
struct io_Writer *pio_Writer__write_expression(struct io_Writer *self, struct calculator__expression_Expression *expression) {
#line 69 "tests/99__calculator/calculator/expression.code"
    struct calculator__expression_Expression *__switch_69_value__ = expression;
#line 70 "tests/99__calculator/calculator/expression.code"
    if (__switch_69_value__->variant == 1) {
#line 71 "tests/99__calculator/calculator/expression.code"
        {
#line 71 "tests/99__calculator/calculator/expression.code"
            struct io_Writer *__001__ = self;
#line 71 "tests/99__calculator/calculator/expression.code"
            int32_t __002__ = __switch_69_value__->variant_1.value;
#line 71 "tests/99__calculator/calculator/expression.code"
            return pio_Writer__write_signed(__001__, __002__);
        }
    }
#line 73 "tests/99__calculator/calculator/expression.code"
    else if (__switch_69_value__->variant == 2) {
#line 74 "tests/99__calculator/calculator/expression.code"
        {
#line 74 "tests/99__calculator/calculator/expression.code"
            struct io_Writer *__001__ = self;
#line 74 "tests/99__calculator/calculator/expression.code"
            struct String __002__ = (struct String){.data = "(", .length = 1};
#line 74 "tests/99__calculator/calculator/expression.code"
            struct io_Writer *__003__ = pio_Writer__write_string(__001__, __002__);
#line 74 "tests/99__calculator/calculator/expression.code"
            struct calculator__expression_Expression *__004__ = __switch_69_value__->variant_2.left;
#line 74 "tests/99__calculator/calculator/expression.code"
            struct io_Writer *__005__ = pio_Writer__write_expression(__003__, __004__);
#line 74 "tests/99__calculator/calculator/expression.code"
            struct String __006__ = (struct String){.data = " + ", .length = 3};
#line 74 "tests/99__calculator/calculator/expression.code"
            struct io_Writer *__007__ = pio_Writer__write_string(__005__, __006__);
#line 74 "tests/99__calculator/calculator/expression.code"
            struct calculator__expression_Expression *__008__ = __switch_69_value__->variant_2.right;
#line 74 "tests/99__calculator/calculator/expression.code"
            struct io_Writer *__009__ = pio_Writer__write_expression(__007__, __008__);
#line 74 "tests/99__calculator/calculator/expression.code"
            struct String __010__ = (struct String){.data = ")", .length = 1};
#line 74 "tests/99__calculator/calculator/expression.code"
            return pio_Writer__write_string(__009__, __010__);
        }
    }
#line 76 "tests/99__calculator/calculator/expression.code"
    else if (__switch_69_value__->variant == 3) {
#line 77 "tests/99__calculator/calculator/expression.code"
        {
#line 77 "tests/99__calculator/calculator/expression.code"
            struct io_Writer *__001__ = self;
#line 77 "tests/99__calculator/calculator/expression.code"
            struct String __002__ = (struct String){.data = "(", .length = 1};
#line 77 "tests/99__calculator/calculator/expression.code"
            struct io_Writer *__003__ = pio_Writer__write_string(__001__, __002__);
#line 77 "tests/99__calculator/calculator/expression.code"
            struct calculator__expression_Expression *__004__ = __switch_69_value__->variant_3.left;
#line 77 "tests/99__calculator/calculator/expression.code"
            struct io_Writer *__005__ = pio_Writer__write_expression(__003__, __004__);
#line 77 "tests/99__calculator/calculator/expression.code"
            struct String __006__ = (struct String){.data = " / ", .length = 3};
#line 77 "tests/99__calculator/calculator/expression.code"
            struct io_Writer *__007__ = pio_Writer__write_string(__005__, __006__);
#line 77 "tests/99__calculator/calculator/expression.code"
            struct calculator__expression_Expression *__008__ = __switch_69_value__->variant_3.right;
#line 77 "tests/99__calculator/calculator/expression.code"
            struct io_Writer *__009__ = pio_Writer__write_expression(__007__, __008__);
#line 77 "tests/99__calculator/calculator/expression.code"
            struct String __010__ = (struct String){.data = ")", .length = 1};
#line 77 "tests/99__calculator/calculator/expression.code"
            return pio_Writer__write_string(__009__, __010__);
        }
    }
#line 79 "tests/99__calculator/calculator/expression.code"
    else if (__switch_69_value__->variant == 4) {
#line 80 "tests/99__calculator/calculator/expression.code"
        {
#line 80 "tests/99__calculator/calculator/expression.code"
            struct io_Writer *__001__ = self;
#line 80 "tests/99__calculator/calculator/expression.code"
            struct String __002__ = (struct String){.data = "(", .length = 1};
#line 80 "tests/99__calculator/calculator/expression.code"
            struct io_Writer *__003__ = pio_Writer__write_string(__001__, __002__);
#line 80 "tests/99__calculator/calculator/expression.code"
            struct calculator__expression_Expression *__004__ = __switch_69_value__->variant_4.left;
#line 80 "tests/99__calculator/calculator/expression.code"
            struct io_Writer *__005__ = pio_Writer__write_expression(__003__, __004__);
#line 80 "tests/99__calculator/calculator/expression.code"
            struct String __006__ = (struct String){.data = " * ", .length = 3};
#line 80 "tests/99__calculator/calculator/expression.code"
            struct io_Writer *__007__ = pio_Writer__write_string(__005__, __006__);
#line 80 "tests/99__calculator/calculator/expression.code"
            struct calculator__expression_Expression *__008__ = __switch_69_value__->variant_4.right;
#line 80 "tests/99__calculator/calculator/expression.code"
            struct io_Writer *__009__ = pio_Writer__write_expression(__007__, __008__);
#line 80 "tests/99__calculator/calculator/expression.code"
            struct String __010__ = (struct String){.data = ")", .length = 1};
#line 80 "tests/99__calculator/calculator/expression.code"
            return pio_Writer__write_string(__009__, __010__);
        }
    }
#line 82 "tests/99__calculator/calculator/expression.code"
    else if (__switch_69_value__->variant == 5) {
#line 83 "tests/99__calculator/calculator/expression.code"
        {
#line 83 "tests/99__calculator/calculator/expression.code"
            struct io_Writer *__001__ = self;
#line 83 "tests/99__calculator/calculator/expression.code"
            struct String __002__ = (struct String){.data = "(", .length = 1};
#line 83 "tests/99__calculator/calculator/expression.code"
            struct io_Writer *__003__ = pio_Writer__write_string(__001__, __002__);
#line 83 "tests/99__calculator/calculator/expression.code"
            struct calculator__expression_Expression *__004__ = __switch_69_value__->variant_5.left;
#line 83 "tests/99__calculator/calculator/expression.code"
            struct io_Writer *__005__ = pio_Writer__write_expression(__003__, __004__);
#line 83 "tests/99__calculator/calculator/expression.code"
            struct String __006__ = (struct String){.data = " - ", .length = 3};
#line 83 "tests/99__calculator/calculator/expression.code"
            struct io_Writer *__007__ = pio_Writer__write_string(__005__, __006__);
#line 83 "tests/99__calculator/calculator/expression.code"
            struct calculator__expression_Expression *__008__ = __switch_69_value__->variant_5.right;
#line 83 "tests/99__calculator/calculator/expression.code"
            struct io_Writer *__009__ = pio_Writer__write_expression(__007__, __008__);
#line 83 "tests/99__calculator/calculator/expression.code"
            struct String __010__ = (struct String){.data = ")", .length = 1};
#line 83 "tests/99__calculator/calculator/expression.code"
            return pio_Writer__write_string(__009__, __010__);
        }
    }
#line 85 "tests/99__calculator/calculator/expression.code"
    else if (__switch_69_value__->variant == 6) {
#line 86 "tests/99__calculator/calculator/expression.code"
        {
#line 86 "tests/99__calculator/calculator/expression.code"
            struct io_Writer *__001__ = self;
#line 86 "tests/99__calculator/calculator/expression.code"
            struct String __002__ = (struct String){.data = "Error: ", .length = 7};
#line 86 "tests/99__calculator/calculator/expression.code"
            struct io_Writer *__003__ = pio_Writer__write_string(__001__, __002__);
#line 86 "tests/99__calculator/calculator/expression.code"
            struct String __004__ = __switch_69_value__->variant_6.message;
#line 86 "tests/99__calculator/calculator/expression.code"
            return pio_Writer__write_string(__003__, __004__);
        }
    }
#line 88 "tests/99__calculator/calculator/expression.code"
    else if (__switch_69_value__->variant == 0) {
#line 89 "tests/99__calculator/calculator/expression.code"
        {
#line 89 "tests/99__calculator/calculator/expression.code"
            struct io_Writer *__001__ = self;
#line 89 "tests/99__calculator/calculator/expression.code"
            struct String __002__ = (struct String){.data = "Nil!", .length = 4};
#line 89 "tests/99__calculator/calculator/expression.code"
            return pio_Writer__write_string(__001__, __002__);
        }
    }
#line 92 "tests/99__calculator/calculator/expression.code"
    return self;
}

