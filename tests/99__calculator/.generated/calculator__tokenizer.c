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

#line 36 "tests/99__calculator/calculator/tokenizer/tokens.code"
struct calculator__source_Span pcalculator__tokenizer_Token__span(struct calculator__tokenizer_Token *self) {
#line 37 "tests/99__calculator/calculator/tokenizer/tokens.code"
    struct calculator__tokenizer_Token *__switch_37_value__ = self;
#line 38 "tests/99__calculator/calculator/tokenizer/tokens.code"
    if (__switch_37_value__->variant == 1) {
#line 39 "tests/99__calculator/calculator/tokenizer/tokens.code"
        {
#line 39 "tests/99__calculator/calculator/tokenizer/tokens.code"
            struct calculator__source_Span __001__ = __switch_37_value__->variant_1.span;
#line 39 "tests/99__calculator/calculator/tokenizer/tokens.code"
            return __001__;
#line 39 "tests/99__calculator/calculator/tokenizer/tokens.code"
        }
#line 40 "tests/99__calculator/calculator/tokenizer/tokens.code"
    }
#line 41 "tests/99__calculator/calculator/tokenizer/tokens.code"
    else if (__switch_37_value__->variant == 2) {
#line 42 "tests/99__calculator/calculator/tokenizer/tokens.code"
        {
#line 42 "tests/99__calculator/calculator/tokenizer/tokens.code"
            struct calculator__source_Span __002__ = __switch_37_value__->variant_2.span;
#line 42 "tests/99__calculator/calculator/tokenizer/tokens.code"
            return __002__;
#line 42 "tests/99__calculator/calculator/tokenizer/tokens.code"
        }
#line 43 "tests/99__calculator/calculator/tokenizer/tokens.code"
    }
#line 44 "tests/99__calculator/calculator/tokenizer/tokens.code"
    else if (__switch_37_value__->variant == 3) {
#line 45 "tests/99__calculator/calculator/tokenizer/tokens.code"
        {
#line 45 "tests/99__calculator/calculator/tokenizer/tokens.code"
            struct calculator__source_Span __003__ = __switch_37_value__->variant_3.span;
#line 45 "tests/99__calculator/calculator/tokenizer/tokens.code"
            return __003__;
#line 45 "tests/99__calculator/calculator/tokenizer/tokens.code"
        }
#line 46 "tests/99__calculator/calculator/tokenizer/tokens.code"
    }
#line 47 "tests/99__calculator/calculator/tokenizer/tokens.code"
    else if (__switch_37_value__->variant == 4) {
#line 48 "tests/99__calculator/calculator/tokenizer/tokens.code"
        {
#line 48 "tests/99__calculator/calculator/tokenizer/tokens.code"
            struct calculator__source_Span __004__ = __switch_37_value__->variant_4.span;
#line 48 "tests/99__calculator/calculator/tokenizer/tokens.code"
            return __004__;
#line 48 "tests/99__calculator/calculator/tokenizer/tokens.code"
        }
#line 49 "tests/99__calculator/calculator/tokenizer/tokens.code"
    }
#line 50 "tests/99__calculator/calculator/tokenizer/tokens.code"
    else if (__switch_37_value__->variant == 5) {
#line 51 "tests/99__calculator/calculator/tokenizer/tokens.code"
        {
#line 51 "tests/99__calculator/calculator/tokenizer/tokens.code"
            struct calculator__source_Span __005__ = __switch_37_value__->variant_5.span;
#line 51 "tests/99__calculator/calculator/tokenizer/tokens.code"
            return __005__;
#line 51 "tests/99__calculator/calculator/tokenizer/tokens.code"
        }
#line 52 "tests/99__calculator/calculator/tokenizer/tokens.code"
    }
#line 53 "tests/99__calculator/calculator/tokenizer/tokens.code"
    else if (__switch_37_value__->variant == 6) {
#line 54 "tests/99__calculator/calculator/tokenizer/tokens.code"
        {
#line 54 "tests/99__calculator/calculator/tokenizer/tokens.code"
            struct calculator__source_Span __006__ = __switch_37_value__->variant_6.span;
#line 54 "tests/99__calculator/calculator/tokenizer/tokens.code"
            return __006__;
#line 54 "tests/99__calculator/calculator/tokenizer/tokens.code"
        }
#line 55 "tests/99__calculator/calculator/tokenizer/tokens.code"
    }
#line 56 "tests/99__calculator/calculator/tokenizer/tokens.code"
    else if (__switch_37_value__->variant == 7) {
#line 57 "tests/99__calculator/calculator/tokenizer/tokens.code"
        {
#line 57 "tests/99__calculator/calculator/tokenizer/tokens.code"
            struct calculator__source_Span __007__ = __switch_37_value__->variant_7.span;
#line 57 "tests/99__calculator/calculator/tokenizer/tokens.code"
            return __007__;
#line 57 "tests/99__calculator/calculator/tokenizer/tokens.code"
        }
#line 58 "tests/99__calculator/calculator/tokenizer/tokens.code"
    }
#line 59 "tests/99__calculator/calculator/tokenizer/tokens.code"
    else {
#line 61 "tests/99__calculator/calculator/tokenizer/tokens.code"
    }
#line 63 "tests/99__calculator/calculator/tokenizer/tokens.code"
    exit(1);
#line 64 "tests/99__calculator/calculator/tokenizer/tokens.code"
}

#line 66 "tests/99__calculator/calculator/tokenizer/tokens.code"
struct io_Writer *pio_Writer__write_token__anon(struct io_Writer *self, struct calculator__tokenizer_Token *token) {
#line 67 "tests/99__calculator/calculator/tokenizer/tokens.code"
    struct calculator__tokenizer_Token *__switch_67_value__ = token;
#line 68 "tests/99__calculator/calculator/tokenizer/tokens.code"
    if (__switch_67_value__->variant == 1) {
#line 69 "tests/99__calculator/calculator/tokenizer/tokens.code"
        {
#line 69 "tests/99__calculator/calculator/tokenizer/tokens.code"
            struct io_Writer *__001__ = pio_Writer__write_signed__signed(pio_Writer__write_string__anon(self, (struct String){.data = "Number: ", .length = 8}), __switch_67_value__->variant_1.value);
#line 69 "tests/99__calculator/calculator/tokenizer/tokens.code"
            return __001__;
#line 69 "tests/99__calculator/calculator/tokenizer/tokens.code"
        }
#line 70 "tests/99__calculator/calculator/tokenizer/tokens.code"
    }
#line 71 "tests/99__calculator/calculator/tokenizer/tokens.code"
    else if (__switch_67_value__->variant == 2) {
#line 72 "tests/99__calculator/calculator/tokenizer/tokens.code"
        {
#line 72 "tests/99__calculator/calculator/tokenizer/tokens.code"
            struct io_Writer *__002__ = pio_Writer__write_string__anon(self, (struct String){.data = "Plus", .length = 4});
#line 72 "tests/99__calculator/calculator/tokenizer/tokens.code"
            return __002__;
#line 72 "tests/99__calculator/calculator/tokenizer/tokens.code"
        }
#line 73 "tests/99__calculator/calculator/tokenizer/tokens.code"
    }
#line 74 "tests/99__calculator/calculator/tokenizer/tokens.code"
    else if (__switch_67_value__->variant == 3) {
#line 75 "tests/99__calculator/calculator/tokenizer/tokens.code"
        {
#line 75 "tests/99__calculator/calculator/tokenizer/tokens.code"
            struct io_Writer *__003__ = pio_Writer__write_string__anon(self, (struct String){.data = "Minus", .length = 5});
#line 75 "tests/99__calculator/calculator/tokenizer/tokens.code"
            return __003__;
#line 75 "tests/99__calculator/calculator/tokenizer/tokens.code"
        }
#line 76 "tests/99__calculator/calculator/tokenizer/tokens.code"
    }
#line 77 "tests/99__calculator/calculator/tokenizer/tokens.code"
    else if (__switch_67_value__->variant == 4) {
#line 78 "tests/99__calculator/calculator/tokenizer/tokens.code"
        {
#line 78 "tests/99__calculator/calculator/tokenizer/tokens.code"
            struct io_Writer *__004__ = pio_Writer__write_string__anon(self, (struct String){.data = "Multiply", .length = 8});
#line 78 "tests/99__calculator/calculator/tokenizer/tokens.code"
            return __004__;
#line 78 "tests/99__calculator/calculator/tokenizer/tokens.code"
        }
#line 79 "tests/99__calculator/calculator/tokenizer/tokens.code"
    }
#line 80 "tests/99__calculator/calculator/tokenizer/tokens.code"
    else if (__switch_67_value__->variant == 5) {
#line 81 "tests/99__calculator/calculator/tokenizer/tokens.code"
        {
#line 81 "tests/99__calculator/calculator/tokenizer/tokens.code"
            struct io_Writer *__005__ = pio_Writer__write_string__anon(self, (struct String){.data = "Divide", .length = 6});
#line 81 "tests/99__calculator/calculator/tokenizer/tokens.code"
            return __005__;
#line 81 "tests/99__calculator/calculator/tokenizer/tokens.code"
        }
#line 82 "tests/99__calculator/calculator/tokenizer/tokens.code"
    }
#line 83 "tests/99__calculator/calculator/tokenizer/tokens.code"
    else if (__switch_67_value__->variant == 6) {
#line 84 "tests/99__calculator/calculator/tokenizer/tokens.code"
        {
#line 84 "tests/99__calculator/calculator/tokenizer/tokens.code"
            struct io_Writer *__006__ = pio_Writer__write_string__anon(self, (struct String){.data = "Stop", .length = 4});
#line 84 "tests/99__calculator/calculator/tokenizer/tokens.code"
            return __006__;
#line 84 "tests/99__calculator/calculator/tokenizer/tokens.code"
        }
#line 85 "tests/99__calculator/calculator/tokenizer/tokens.code"
    }
#line 86 "tests/99__calculator/calculator/tokenizer/tokens.code"
    else if (__switch_67_value__->variant == 7) {
#line 87 "tests/99__calculator/calculator/tokenizer/tokens.code"
        {
#line 87 "tests/99__calculator/calculator/tokenizer/tokens.code"
            struct io_Writer *__007__ = pio_Writer__write_string__anon(pio_Writer__write_string__anon(self, (struct String){.data = "Error: ", .length = 7}), __switch_67_value__->variant_7.message);
#line 87 "tests/99__calculator/calculator/tokenizer/tokens.code"
            return __007__;
#line 87 "tests/99__calculator/calculator/tokenizer/tokens.code"
        }
#line 88 "tests/99__calculator/calculator/tokenizer/tokens.code"
    }
#line 89 "tests/99__calculator/calculator/tokenizer/tokens.code"
    else if (__switch_67_value__->variant == 0) {
#line 90 "tests/99__calculator/calculator/tokenizer/tokens.code"
        {
#line 90 "tests/99__calculator/calculator/tokenizer/tokens.code"
            struct io_Writer *__008__ = pio_Writer__write_string__anon(self, (struct String){.data = "Nil!", .length = 4});
#line 90 "tests/99__calculator/calculator/tokenizer/tokens.code"
            return __008__;
#line 90 "tests/99__calculator/calculator/tokenizer/tokens.code"
        }
#line 91 "tests/99__calculator/calculator/tokenizer/tokens.code"
    }
#line 93 "tests/99__calculator/calculator/tokenizer/tokens.code"
    {
#line 93 "tests/99__calculator/calculator/tokenizer/tokens.code"
        struct io_Writer *__009__ = self;
#line 93 "tests/99__calculator/calculator/tokenizer/tokens.code"
        return __009__;
#line 93 "tests/99__calculator/calculator/tokenizer/tokens.code"
    }
#line 94 "tests/99__calculator/calculator/tokenizer/tokens.code"
}

#line 11 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
struct calculator__tokenizer_Token pcalculator__tokenizer_Tokenizer__peek_token(struct calculator__tokenizer_Tokenizer *self) {
#line 12 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
    if (self->current_token.variant == 0) {
#line 13 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
        self->current_token = pcalculator__tokenizer_Tokenizer__scan_token(self);
#line 14 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
    }
#line 15 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
    {
#line 15 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
        struct calculator__tokenizer_Token __001__ = self->current_token;
#line 15 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
        return __001__;
#line 15 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
    }
#line 16 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
}

#line 18 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
struct calculator__tokenizer_Token pcalculator__tokenizer_Tokenizer__next_token(struct calculator__tokenizer_Tokenizer *self) {
#line 19 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
    struct calculator__tokenizer_Token token = pcalculator__tokenizer_Tokenizer__peek_token(self);
#line 20 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
    self->current_token = (struct calculator__tokenizer_Token){.variant = 0};
#line 21 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
    {
#line 21 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
        struct calculator__tokenizer_Token __001__ = token;
#line 21 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
        return __001__;
#line 21 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
    }
#line 22 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
}

#line 24 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
struct calculator__tokenizer_Token pcalculator__tokenizer_Tokenizer__scan_token(struct calculator__tokenizer_Tokenizer *self) {
#line 25 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
    while (self->data[self->index] == ' ') {
#line 26 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
        self->index = self->index + 1;
#line 27 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
    }
#line 28 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
    uint8_t ch = self->data[self->index];
#line 29 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
    if (ch == 0) {
#line 30 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
        {
#line 30 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
            struct calculator__tokenizer_Token __001__ = (struct calculator__tokenizer_Token){.variant = 6, .variant_6 = (struct calculator__tokenizer_Stop){.span = (struct calculator__source_Span){.start = self->index, .end = self->index}}};
#line 30 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
            return __001__;
#line 30 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
        }
#line 31 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
    }
#line 32 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
    if (ch >= '0' && ch <= '9') {
#line 33 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
        {
#line 33 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
            struct calculator__tokenizer_Token __002__ = pcalculator__tokenizer_Tokenizer__scan_number_token(self);
#line 33 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
            return __002__;
#line 33 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
        }
#line 34 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
    }
#line 35 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
    self->index = self->index + 1;
#line 36 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
    if (ch == '+') {
#line 37 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
        {
#line 37 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
            struct calculator__tokenizer_Token __003__ = (struct calculator__tokenizer_Token){.variant = 2, .variant_2 = (struct calculator__tokenizer_Plus){.span = (struct calculator__source_Span){.start = self->index - 1, .end = self->index}}};
#line 37 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
            return __003__;
#line 37 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
        }
#line 38 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
    }
#line 39 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
    if (ch == '-') {
#line 40 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
        {
#line 40 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
            struct calculator__tokenizer_Token __004__ = (struct calculator__tokenizer_Token){.variant = 3, .variant_3 = (struct calculator__tokenizer_Minus){.span = (struct calculator__source_Span){.start = self->index - 1, .end = self->index}}};
#line 40 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
            return __004__;
#line 40 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
        }
#line 41 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
    }
#line 42 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
    if (ch == '*') {
#line 43 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
        {
#line 43 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
            struct calculator__tokenizer_Token __005__ = (struct calculator__tokenizer_Token){.variant = 4, .variant_4 = (struct calculator__tokenizer_Multiply){.span = (struct calculator__source_Span){.start = self->index - 1, .end = self->index}}};
#line 43 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
            return __005__;
#line 43 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
        }
#line 44 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
    }
#line 45 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
    if (ch == '/') {
#line 46 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
        {
#line 46 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
            struct calculator__tokenizer_Token __006__ = (struct calculator__tokenizer_Token){.variant = 5, .variant_5 = (struct calculator__tokenizer_Divide){.span = (struct calculator__source_Span){.start = self->index - 1, .end = self->index}}};
#line 46 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
            return __006__;
#line 46 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
        }
#line 47 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
    }
#line 48 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
    {
#line 48 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
        struct calculator__tokenizer_Token __007__ = (struct calculator__tokenizer_Token){.variant = 7, .variant_7 = (struct calculator__source_Error){.span = (struct calculator__source_Span){.start = self->index - 1, .end = self->index}, .message = (struct String){.data = "Unexpected character", .length = 20}}};
#line 48 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
        return __007__;
#line 51 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
    }
#line 52 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
}

#line 54 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
struct calculator__tokenizer_Token pcalculator__tokenizer_Tokenizer__scan_number_token(struct calculator__tokenizer_Tokenizer *self) {
#line 55 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
    int32_t start = self->index;
#line 56 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
    int32_t value = 0;
#line 57 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
    for (;;) {
#line 58 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
        uint8_t c = self->data[self->index];
#line 59 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
        if (c < '0' || c > '9') {
#line 60 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
            break;
#line 61 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
        }
#line 62 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
        value = value * 10 + ((int32_t) (c - '0'));
#line 63 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
        self->index = self->index + 1;
#line 64 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
    }
#line 65 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
    {
#line 65 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
        struct calculator__tokenizer_Token __001__ = (struct calculator__tokenizer_Token){.variant = 1, .variant_1 = (struct calculator__expression_Number){.span = (struct calculator__source_Span){.start = start, .end = self->index}, .value = value}};
#line 65 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
        return __001__;
#line 68 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
    }
#line 69 "tests/99__calculator/calculator/tokenizer/tokenizer.code"
}

