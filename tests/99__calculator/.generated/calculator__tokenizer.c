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

#line 13 "tests/99__calculator/calculator/tokenizer.code"
struct calculator__tokenizer_Token pcalculator__tokenizer_Tokenizer__peek_token(struct calculator__tokenizer_Tokenizer *self) {
#line 14 "tests/99__calculator/calculator/tokenizer.code"
    if (self->current_token.variant == 0) {
#line 15 "tests/99__calculator/calculator/tokenizer.code"
        self->current_token = pcalculator__tokenizer_Tokenizer__scan_token(self);
    }
#line 17 "tests/99__calculator/calculator/tokenizer.code"
    return self->current_token;
}

#line 20 "tests/99__calculator/calculator/tokenizer.code"
struct calculator__tokenizer_Token pcalculator__tokenizer_Tokenizer__next_token(struct calculator__tokenizer_Tokenizer *self) {
#line 21 "tests/99__calculator/calculator/tokenizer.code"
    struct calculator__tokenizer_Token token = pcalculator__tokenizer_Tokenizer__peek_token(self);
#line 22 "tests/99__calculator/calculator/tokenizer.code"
    self->current_token = (struct calculator__tokenizer_Token){.variant = 0};
#line 23 "tests/99__calculator/calculator/tokenizer.code"
    return token;
}

#line 26 "tests/99__calculator/calculator/tokenizer.code"
struct calculator__tokenizer_Token pcalculator__tokenizer_Tokenizer__scan_token(struct calculator__tokenizer_Tokenizer *self) {
#line 27 "tests/99__calculator/calculator/tokenizer.code"
    while (self->data[self->index] == ' ') {
#line 28 "tests/99__calculator/calculator/tokenizer.code"
        self->index = self->index + 1;
    }
#line 30 "tests/99__calculator/calculator/tokenizer.code"
    uint8_t ch = self->data[self->index];
#line 31 "tests/99__calculator/calculator/tokenizer.code"
    if (ch == 0) {
#line 32 "tests/99__calculator/calculator/tokenizer.code"
        return (struct calculator__tokenizer_Token){.variant = 6, .variant_6 = (struct calculator__tokenizer_Stop){.span = (struct calculator__source_Span){.start = self->index, .end = self->index}}};
    }
#line 34 "tests/99__calculator/calculator/tokenizer.code"
    if (ch >= '0' && ch <= '9') {
#line 35 "tests/99__calculator/calculator/tokenizer.code"
        return pcalculator__tokenizer_Tokenizer__scan_number_token(self);
    }
#line 37 "tests/99__calculator/calculator/tokenizer.code"
    self->index = self->index + 1;
#line 38 "tests/99__calculator/calculator/tokenizer.code"
    if (ch == '+') {
#line 39 "tests/99__calculator/calculator/tokenizer.code"
        return (struct calculator__tokenizer_Token){.variant = 2, .variant_2 = (struct calculator__tokenizer_Plus){.span = (struct calculator__source_Span){.start = self->index - 1, .end = self->index}}};
    }
#line 41 "tests/99__calculator/calculator/tokenizer.code"
    if (ch == '-') {
#line 42 "tests/99__calculator/calculator/tokenizer.code"
        return (struct calculator__tokenizer_Token){.variant = 3, .variant_3 = (struct calculator__tokenizer_Minus){.span = (struct calculator__source_Span){.start = self->index - 1, .end = self->index}}};
    }
#line 44 "tests/99__calculator/calculator/tokenizer.code"
    if (ch == '*') {
#line 45 "tests/99__calculator/calculator/tokenizer.code"
        return (struct calculator__tokenizer_Token){.variant = 4, .variant_4 = (struct calculator__tokenizer_Multiply){.span = (struct calculator__source_Span){.start = self->index - 1, .end = self->index}}};
    }
#line 47 "tests/99__calculator/calculator/tokenizer.code"
    if (ch == '/') {
#line 48 "tests/99__calculator/calculator/tokenizer.code"
        return (struct calculator__tokenizer_Token){.variant = 5, .variant_5 = (struct calculator__tokenizer_Divide){.span = (struct calculator__source_Span){.start = self->index - 1, .end = self->index}}};
    }
#line 50 "tests/99__calculator/calculator/tokenizer.code"
    return (struct calculator__tokenizer_Token){.variant = 7, .variant_7 = (struct calculator__source_Error){.span = (struct calculator__source_Span){.start = self->index - 1, .end = self->index}, .message = (struct String){.data = "Unexpected character", .length = 20}}};
}

#line 56 "tests/99__calculator/calculator/tokenizer.code"
struct calculator__tokenizer_Token pcalculator__tokenizer_Tokenizer__scan_number_token(struct calculator__tokenizer_Tokenizer *self) {
#line 57 "tests/99__calculator/calculator/tokenizer.code"
    int32_t start = self->index;
#line 58 "tests/99__calculator/calculator/tokenizer.code"
    int32_t value = 0;
#line 59 "tests/99__calculator/calculator/tokenizer.code"
    for (;;) {
#line 60 "tests/99__calculator/calculator/tokenizer.code"
        uint8_t c = self->data[self->index];
#line 61 "tests/99__calculator/calculator/tokenizer.code"
        if (c < '0' || c > '9') {
#line 62 "tests/99__calculator/calculator/tokenizer.code"
            break;
        }
#line 64 "tests/99__calculator/calculator/tokenizer.code"
        value = value * 10 + ((int32_t) (c - '0'));
#line 65 "tests/99__calculator/calculator/tokenizer.code"
        self->index = self->index + 1;
    }
#line 67 "tests/99__calculator/calculator/tokenizer.code"
    return (struct calculator__tokenizer_Token){.variant = 1, .variant_1 = (struct calculator__expression_Number){.span = (struct calculator__source_Span){.start = start, .end = self->index}, .value = value}};
}

#line 103 "tests/99__calculator/calculator/tokenizer.code"
struct calculator__source_Span pcalculator__tokenizer_Token__span(struct calculator__tokenizer_Token *self) {
#line 104 "tests/99__calculator/calculator/tokenizer.code"
    struct calculator__tokenizer_Token *__switch_104_value__ = self;
#line 105 "tests/99__calculator/calculator/tokenizer.code"
    if (__switch_104_value__->variant == 1) {
#line 106 "tests/99__calculator/calculator/tokenizer.code"
        return __switch_104_value__->variant_1.span;
    }
#line 108 "tests/99__calculator/calculator/tokenizer.code"
    else if (__switch_104_value__->variant == 2) {
#line 109 "tests/99__calculator/calculator/tokenizer.code"
        return __switch_104_value__->variant_2.span;
    }
#line 111 "tests/99__calculator/calculator/tokenizer.code"
    else if (__switch_104_value__->variant == 3) {
#line 112 "tests/99__calculator/calculator/tokenizer.code"
        return __switch_104_value__->variant_3.span;
    }
#line 114 "tests/99__calculator/calculator/tokenizer.code"
    else if (__switch_104_value__->variant == 4) {
#line 115 "tests/99__calculator/calculator/tokenizer.code"
        return __switch_104_value__->variant_4.span;
    }
#line 117 "tests/99__calculator/calculator/tokenizer.code"
    else if (__switch_104_value__->variant == 5) {
#line 118 "tests/99__calculator/calculator/tokenizer.code"
        return __switch_104_value__->variant_5.span;
    }
#line 120 "tests/99__calculator/calculator/tokenizer.code"
    else if (__switch_104_value__->variant == 6) {
#line 121 "tests/99__calculator/calculator/tokenizer.code"
        return __switch_104_value__->variant_6.span;
    }
#line 123 "tests/99__calculator/calculator/tokenizer.code"
    else if (__switch_104_value__->variant == 7) {
#line 124 "tests/99__calculator/calculator/tokenizer.code"
        return __switch_104_value__->variant_7.span;
    }
#line 126 "tests/99__calculator/calculator/tokenizer.code"
    else {
    }
#line 130 "tests/99__calculator/calculator/tokenizer.code"
    exit(1);
}

#line 133 "tests/99__calculator/calculator/tokenizer.code"
struct io_Writer *pio_Writer__write_token(struct io_Writer *self, struct calculator__tokenizer_Token *token) {
#line 134 "tests/99__calculator/calculator/tokenizer.code"
    struct calculator__tokenizer_Token *__switch_134_value__ = token;
#line 135 "tests/99__calculator/calculator/tokenizer.code"
    if (__switch_134_value__->variant == 1) {
#line 136 "tests/99__calculator/calculator/tokenizer.code"
        return pio_Writer__write_signed(pio_Writer__write_string(self, (struct String){.data = "Number: ", .length = 8}), __switch_134_value__->variant_1.value);
    }
#line 138 "tests/99__calculator/calculator/tokenizer.code"
    else if (__switch_134_value__->variant == 2) {
#line 139 "tests/99__calculator/calculator/tokenizer.code"
        return pio_Writer__write_string(self, (struct String){.data = "Plus", .length = 4});
    }
#line 141 "tests/99__calculator/calculator/tokenizer.code"
    else if (__switch_134_value__->variant == 3) {
#line 142 "tests/99__calculator/calculator/tokenizer.code"
        return pio_Writer__write_string(self, (struct String){.data = "Minus", .length = 5});
    }
#line 144 "tests/99__calculator/calculator/tokenizer.code"
    else if (__switch_134_value__->variant == 4) {
#line 145 "tests/99__calculator/calculator/tokenizer.code"
        return pio_Writer__write_string(self, (struct String){.data = "Multiply", .length = 8});
    }
#line 147 "tests/99__calculator/calculator/tokenizer.code"
    else if (__switch_134_value__->variant == 5) {
#line 148 "tests/99__calculator/calculator/tokenizer.code"
        return pio_Writer__write_string(self, (struct String){.data = "Divide", .length = 6});
    }
#line 150 "tests/99__calculator/calculator/tokenizer.code"
    else if (__switch_134_value__->variant == 6) {
#line 151 "tests/99__calculator/calculator/tokenizer.code"
        return pio_Writer__write_string(self, (struct String){.data = "Stop", .length = 4});
    }
#line 153 "tests/99__calculator/calculator/tokenizer.code"
    else if (__switch_134_value__->variant == 7) {
#line 154 "tests/99__calculator/calculator/tokenizer.code"
        return pio_Writer__write_string(pio_Writer__write_string(self, (struct String){.data = "Error: ", .length = 7}), __switch_134_value__->variant_7.message);
    }
#line 156 "tests/99__calculator/calculator/tokenizer.code"
    else if (__switch_134_value__->variant == 0) {
#line 157 "tests/99__calculator/calculator/tokenizer.code"
        return pio_Writer__write_string(self, (struct String){.data = "Nil!", .length = 4});
    }
#line 160 "tests/99__calculator/calculator/tokenizer.code"
    return self;
}

