#include "calculator__expression.h"

struct calculator__expression_Expression *__alloc__calculator__expression_Expression__(struct calculator__expression_Expression value) {
struct calculator__expression_Expression *result = (struct calculator__expression_Expression *)malloc(sizeof(struct calculator__expression_Expression));
    *result = value;
    return result;
}

struct calculator__expression_Number *__alloc__calculator__expression_Number__(struct calculator__expression_Number value) {
    struct calculator__expression_Number *result = (struct calculator__expression_Number *)malloc(sizeof(struct calculator__expression_Number));
    *result = value;
    return result;
}

struct calculator__expression_Addition *__alloc__calculator__expression_Addition__(struct calculator__expression_Addition value) {
    struct calculator__expression_Addition *result = (struct calculator__expression_Addition *)malloc(sizeof(struct calculator__expression_Addition));
    *result = value;
    return result;
}

struct calculator__expression_Division *__alloc__calculator__expression_Division__(struct calculator__expression_Division value) {
    struct calculator__expression_Division *result = (struct calculator__expression_Division *)malloc(sizeof(struct calculator__expression_Division));
    *result = value;
    return result;
}

struct calculator__expression_Multiplication *__alloc__calculator__expression_Multiplication__(struct calculator__expression_Multiplication value) {
    struct calculator__expression_Multiplication *result = (struct calculator__expression_Multiplication *)malloc(sizeof(struct calculator__expression_Multiplication));
    *result = value;
    return result;
}

struct calculator__expression_Subtraction *__alloc__calculator__expression_Subtraction__(struct calculator__expression_Subtraction value) {
    struct calculator__expression_Subtraction *result = (struct calculator__expression_Subtraction *)malloc(sizeof(struct calculator__expression_Subtraction));
    *result = value;
    return result;
}

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
        return (struct calculator__source_Span){.start = 0, .end = 0};
    }
}

#line 68 "tests/99__calculator/calculator/expression.code"
struct io_Writer *pio_Writer__write__1_expression(struct io_Writer *self, struct calculator__expression_Expression *expression) {
#line 69 "tests/99__calculator/calculator/expression.code"
    struct calculator__expression_Expression *__switch_69_value__ = expression;
#line 70 "tests/99__calculator/calculator/expression.code"
    if (__switch_69_value__->variant == 1) {
#line 71 "tests/99__calculator/calculator/expression.code"
        return pio_Writer__write__1_signed(self, __switch_69_value__->variant_1.value);
    }
#line 73 "tests/99__calculator/calculator/expression.code"
    else if (__switch_69_value__->variant == 2) {
#line 74 "tests/99__calculator/calculator/expression.code"
        return pio_Writer__write(pio_Writer__write__1_expression(pio_Writer__write(pio_Writer__write__1_expression(pio_Writer__write(self, (struct String){.data = "(", .length = 1}), __switch_69_value__->variant_2.left), (struct String){.data = " + ", .length = 3}), __switch_69_value__->variant_2.right), (struct String){.data = ")", .length = 1});
    }
#line 76 "tests/99__calculator/calculator/expression.code"
    else if (__switch_69_value__->variant == 3) {
#line 77 "tests/99__calculator/calculator/expression.code"
        return pio_Writer__write(pio_Writer__write__1_expression(pio_Writer__write(pio_Writer__write__1_expression(pio_Writer__write(self, (struct String){.data = "(", .length = 1}), __switch_69_value__->variant_3.left), (struct String){.data = " / ", .length = 3}), __switch_69_value__->variant_3.right), (struct String){.data = ")", .length = 1});
    }
#line 79 "tests/99__calculator/calculator/expression.code"
    else if (__switch_69_value__->variant == 4) {
#line 80 "tests/99__calculator/calculator/expression.code"
        return pio_Writer__write(pio_Writer__write__1_expression(pio_Writer__write(pio_Writer__write__1_expression(pio_Writer__write(self, (struct String){.data = "(", .length = 1}), __switch_69_value__->variant_4.left), (struct String){.data = " * ", .length = 3}), __switch_69_value__->variant_4.right), (struct String){.data = ")", .length = 1});
    }
#line 82 "tests/99__calculator/calculator/expression.code"
    else if (__switch_69_value__->variant == 5) {
#line 83 "tests/99__calculator/calculator/expression.code"
        return pio_Writer__write(pio_Writer__write__1_expression(pio_Writer__write(pio_Writer__write__1_expression(pio_Writer__write(self, (struct String){.data = "(", .length = 1}), __switch_69_value__->variant_5.left), (struct String){.data = " - ", .length = 3}), __switch_69_value__->variant_5.right), (struct String){.data = ")", .length = 1});
    }
#line 85 "tests/99__calculator/calculator/expression.code"
    else if (__switch_69_value__->variant == 6) {
#line 86 "tests/99__calculator/calculator/expression.code"
        return pio_Writer__write(pio_Writer__write(self, (struct String){.data = "Error: ", .length = 7}), __switch_69_value__->variant_6.message);
    }
#line 88 "tests/99__calculator/calculator/expression.code"
    else if (__switch_69_value__->variant == 0) {
#line 89 "tests/99__calculator/calculator/expression.code"
        return pio_Writer__write(self, (struct String){.data = "Nil!", .length = 4});
    }
#line 92 "tests/99__calculator/calculator/expression.code"
    return self;
}

