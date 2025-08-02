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

#line 12 "tests/99__calculator/calculator/tokenizer.code"
struct calculator__tokenizer_Token pcalculator__tokenizer_Tokenizer__peek_token(struct calculator__tokenizer_Tokenizer *self) {
#line 13 "tests/99__calculator/calculator/tokenizer.code"
    if (self->current_token.variant == 0) {
#line 14 "tests/99__calculator/calculator/tokenizer.code"
        {
#line 14 "tests/99__calculator/calculator/tokenizer.code"
            struct calculator__tokenizer_Tokenizer *__001__ = self;
#line 14 "tests/99__calculator/calculator/tokenizer.code"
            self->current_token = pcalculator__tokenizer_Tokenizer__scan_token(__001__);
        }
    }
#line 16 "tests/99__calculator/calculator/tokenizer.code"
    return self->current_token;
}

#line 19 "tests/99__calculator/calculator/tokenizer.code"
struct calculator__tokenizer_Token pcalculator__tokenizer_Tokenizer__next_token(struct calculator__tokenizer_Tokenizer *self) {
#line 20 "tests/99__calculator/calculator/tokenizer.code"
    struct calculator__tokenizer_Token token;
#line 20 "tests/99__calculator/calculator/tokenizer.code"
    {
#line 20 "tests/99__calculator/calculator/tokenizer.code"
        struct calculator__tokenizer_Tokenizer *__001__ = self;
#line 20 "tests/99__calculator/calculator/tokenizer.code"
        token = pcalculator__tokenizer_Tokenizer__peek_token(__001__);
    }
#line 21 "tests/99__calculator/calculator/tokenizer.code"
    self->current_token = (struct calculator__tokenizer_Token){.variant = 0};
#line 22 "tests/99__calculator/calculator/tokenizer.code"
    return token;
}

#line 25 "tests/99__calculator/calculator/tokenizer.code"
struct calculator__tokenizer_Token pcalculator__tokenizer_Tokenizer__scan_token(struct calculator__tokenizer_Tokenizer *self) {
#line 26 "tests/99__calculator/calculator/tokenizer.code"
    for (;;) {
#line 26 "tests/99__calculator/calculator/tokenizer.code"
        {
#line 26 "tests/99__calculator/calculator/tokenizer.code"
            int32_t __001__ = self->index;
#line 26 "tests/99__calculator/calculator/tokenizer.code"
            if (self->data[__001__] == ' ') {} else break;
        }
#line 27 "tests/99__calculator/calculator/tokenizer.code"
        self->index = self->index + 1;
    }
#line 29 "tests/99__calculator/calculator/tokenizer.code"
    uint8_t ch;
#line 29 "tests/99__calculator/calculator/tokenizer.code"
    {
#line 29 "tests/99__calculator/calculator/tokenizer.code"
        int32_t __001__ = self->index;
#line 29 "tests/99__calculator/calculator/tokenizer.code"
        ch = self->data[__001__];
    }
#line 30 "tests/99__calculator/calculator/tokenizer.code"
    if (ch == 0) {
#line 31 "tests/99__calculator/calculator/tokenizer.code"
        {
#line 31 "tests/99__calculator/calculator/tokenizer.code"
            int32_t __001__ = self->index;
#line 31 "tests/99__calculator/calculator/tokenizer.code"
            int32_t __002__ = self->index;
#line 31 "tests/99__calculator/calculator/tokenizer.code"
            struct calculator__source_Span __003__ = (struct calculator__source_Span){.start = __001__, .end = __002__};
#line 31 "tests/99__calculator/calculator/tokenizer.code"
            return (struct calculator__tokenizer_Token){.variant = 6, .variant_6 = (struct calculator__tokenizer_Stop){.span = __003__}};
        }
    }
#line 33 "tests/99__calculator/calculator/tokenizer.code"
    {
#line 33 "tests/99__calculator/calculator/tokenizer.code"
        bool __001__ = ch >= '0';
#line 33 "tests/99__calculator/calculator/tokenizer.code"
        if (__001__) {
#line 33 "tests/99__calculator/calculator/tokenizer.code"
            __001__ = ch <= '9';
        }
#line 33 "tests/99__calculator/calculator/tokenizer.code"
        if (__001__) {
#line 34 "tests/99__calculator/calculator/tokenizer.code"
            {
#line 34 "tests/99__calculator/calculator/tokenizer.code"
                struct calculator__tokenizer_Tokenizer *__001__ = self;
#line 34 "tests/99__calculator/calculator/tokenizer.code"
                return pcalculator__tokenizer_Tokenizer__scan_number_token(__001__);
            }
        }
    }
#line 36 "tests/99__calculator/calculator/tokenizer.code"
    self->index = self->index + 1;
#line 37 "tests/99__calculator/calculator/tokenizer.code"
    if (ch == '+') {
#line 38 "tests/99__calculator/calculator/tokenizer.code"
        {
#line 38 "tests/99__calculator/calculator/tokenizer.code"
            int32_t __001__ = self->index - 1;
#line 38 "tests/99__calculator/calculator/tokenizer.code"
            int32_t __002__ = self->index;
#line 38 "tests/99__calculator/calculator/tokenizer.code"
            struct calculator__source_Span __003__ = (struct calculator__source_Span){.start = __001__, .end = __002__};
#line 38 "tests/99__calculator/calculator/tokenizer.code"
            return (struct calculator__tokenizer_Token){.variant = 2, .variant_2 = (struct calculator__tokenizer_Plus){.span = __003__}};
        }
    }
#line 40 "tests/99__calculator/calculator/tokenizer.code"
    if (ch == '-') {
#line 41 "tests/99__calculator/calculator/tokenizer.code"
        {
#line 41 "tests/99__calculator/calculator/tokenizer.code"
            int32_t __001__ = self->index - 1;
#line 41 "tests/99__calculator/calculator/tokenizer.code"
            int32_t __002__ = self->index;
#line 41 "tests/99__calculator/calculator/tokenizer.code"
            struct calculator__source_Span __003__ = (struct calculator__source_Span){.start = __001__, .end = __002__};
#line 41 "tests/99__calculator/calculator/tokenizer.code"
            return (struct calculator__tokenizer_Token){.variant = 3, .variant_3 = (struct calculator__tokenizer_Minus){.span = __003__}};
        }
    }
#line 43 "tests/99__calculator/calculator/tokenizer.code"
    if (ch == '*') {
#line 44 "tests/99__calculator/calculator/tokenizer.code"
        {
#line 44 "tests/99__calculator/calculator/tokenizer.code"
            int32_t __001__ = self->index - 1;
#line 44 "tests/99__calculator/calculator/tokenizer.code"
            int32_t __002__ = self->index;
#line 44 "tests/99__calculator/calculator/tokenizer.code"
            struct calculator__source_Span __003__ = (struct calculator__source_Span){.start = __001__, .end = __002__};
#line 44 "tests/99__calculator/calculator/tokenizer.code"
            return (struct calculator__tokenizer_Token){.variant = 4, .variant_4 = (struct calculator__tokenizer_Multiply){.span = __003__}};
        }
    }
#line 46 "tests/99__calculator/calculator/tokenizer.code"
    if (ch == '/') {
#line 47 "tests/99__calculator/calculator/tokenizer.code"
        {
#line 47 "tests/99__calculator/calculator/tokenizer.code"
            int32_t __001__ = self->index - 1;
#line 47 "tests/99__calculator/calculator/tokenizer.code"
            int32_t __002__ = self->index;
#line 47 "tests/99__calculator/calculator/tokenizer.code"
            struct calculator__source_Span __003__ = (struct calculator__source_Span){.start = __001__, .end = __002__};
#line 47 "tests/99__calculator/calculator/tokenizer.code"
            return (struct calculator__tokenizer_Token){.variant = 5, .variant_5 = (struct calculator__tokenizer_Divide){.span = __003__}};
        }
    }
#line 49 "tests/99__calculator/calculator/tokenizer.code"
    {
#line 50 "tests/99__calculator/calculator/tokenizer.code"
        int32_t __001__ = self->index - 1;
#line 50 "tests/99__calculator/calculator/tokenizer.code"
        int32_t __002__ = self->index;
#line 50 "tests/99__calculator/calculator/tokenizer.code"
        struct calculator__source_Span __003__ = (struct calculator__source_Span){.start = __001__, .end = __002__};
#line 51 "tests/99__calculator/calculator/tokenizer.code"
        struct String __004__ = (struct String){.data = "Unexpected character", .length = 20};
#line 49 "tests/99__calculator/calculator/tokenizer.code"
        return (struct calculator__tokenizer_Token){.variant = 7, .variant_7 = (struct calculator__source_Error){.span = __003__, .message = __004__}};
    }
}

#line 55 "tests/99__calculator/calculator/tokenizer.code"
struct calculator__tokenizer_Token pcalculator__tokenizer_Tokenizer__scan_number_token(struct calculator__tokenizer_Tokenizer *self) {
#line 56 "tests/99__calculator/calculator/tokenizer.code"
    int32_t start = self->index;
#line 57 "tests/99__calculator/calculator/tokenizer.code"
    int32_t value = 0;
#line 58 "tests/99__calculator/calculator/tokenizer.code"
    for (;;) {
#line 59 "tests/99__calculator/calculator/tokenizer.code"
        uint8_t c;
#line 59 "tests/99__calculator/calculator/tokenizer.code"
        {
#line 59 "tests/99__calculator/calculator/tokenizer.code"
            int32_t __001__ = self->index;
#line 59 "tests/99__calculator/calculator/tokenizer.code"
            c = self->data[__001__];
        }
#line 60 "tests/99__calculator/calculator/tokenizer.code"
        {
#line 60 "tests/99__calculator/calculator/tokenizer.code"
            bool __001__ = c < '0';
#line 60 "tests/99__calculator/calculator/tokenizer.code"
            if (__001__) {} else {
#line 60 "tests/99__calculator/calculator/tokenizer.code"
                __001__ = c > '9';
            }
#line 60 "tests/99__calculator/calculator/tokenizer.code"
            if (__001__) {
#line 61 "tests/99__calculator/calculator/tokenizer.code"
                break;
            }
        }
#line 63 "tests/99__calculator/calculator/tokenizer.code"
        value = value * 10 + ((int32_t) (c - '0'));
#line 64 "tests/99__calculator/calculator/tokenizer.code"
        self->index = self->index + 1;
    }
#line 66 "tests/99__calculator/calculator/tokenizer.code"
    {
#line 67 "tests/99__calculator/calculator/tokenizer.code"
        int32_t __001__ = start;
#line 67 "tests/99__calculator/calculator/tokenizer.code"
        int32_t __002__ = self->index;
#line 67 "tests/99__calculator/calculator/tokenizer.code"
        struct calculator__source_Span __003__ = (struct calculator__source_Span){.start = __001__, .end = __002__};
#line 68 "tests/99__calculator/calculator/tokenizer.code"
        int32_t __004__ = value;
#line 66 "tests/99__calculator/calculator/tokenizer.code"
        return (struct calculator__tokenizer_Token){.variant = 1, .variant_1 = (struct calculator__expression_Number){.span = __003__, .value = __004__}};
    }
}

#line 102 "tests/99__calculator/calculator/tokenizer.code"
struct calculator__source_Span pcalculator__tokenizer_Token__span(struct calculator__tokenizer_Token *self) {
#line 103 "tests/99__calculator/calculator/tokenizer.code"
    struct calculator__tokenizer_Token *__switch_103_value__ = self;
#line 104 "tests/99__calculator/calculator/tokenizer.code"
    if (__switch_103_value__->variant == 1) {
#line 105 "tests/99__calculator/calculator/tokenizer.code"
        return __switch_103_value__->variant_1.span;
    }
#line 107 "tests/99__calculator/calculator/tokenizer.code"
    else if (__switch_103_value__->variant == 2) {
#line 108 "tests/99__calculator/calculator/tokenizer.code"
        return __switch_103_value__->variant_2.span;
    }
#line 110 "tests/99__calculator/calculator/tokenizer.code"
    else if (__switch_103_value__->variant == 3) {
#line 111 "tests/99__calculator/calculator/tokenizer.code"
        return __switch_103_value__->variant_3.span;
    }
#line 113 "tests/99__calculator/calculator/tokenizer.code"
    else if (__switch_103_value__->variant == 4) {
#line 114 "tests/99__calculator/calculator/tokenizer.code"
        return __switch_103_value__->variant_4.span;
    }
#line 116 "tests/99__calculator/calculator/tokenizer.code"
    else if (__switch_103_value__->variant == 5) {
#line 117 "tests/99__calculator/calculator/tokenizer.code"
        return __switch_103_value__->variant_5.span;
    }
#line 119 "tests/99__calculator/calculator/tokenizer.code"
    else if (__switch_103_value__->variant == 6) {
#line 120 "tests/99__calculator/calculator/tokenizer.code"
        return __switch_103_value__->variant_6.span;
    }
#line 122 "tests/99__calculator/calculator/tokenizer.code"
    else if (__switch_103_value__->variant == 7) {
#line 123 "tests/99__calculator/calculator/tokenizer.code"
        return __switch_103_value__->variant_7.span;
    }
#line 125 "tests/99__calculator/calculator/tokenizer.code"
    else if (__switch_103_value__->variant == 0) {
#line 126 "tests/99__calculator/calculator/tokenizer.code"
        {
#line 126 "tests/99__calculator/calculator/tokenizer.code"
            int32_t __001__ = 0;
#line 126 "tests/99__calculator/calculator/tokenizer.code"
            int32_t __002__ = 0;
#line 126 "tests/99__calculator/calculator/tokenizer.code"
            return (struct calculator__source_Span){.start = __001__, .end = __002__};
        }
    }
}

#line 131 "tests/99__calculator/calculator/tokenizer.code"
struct io_Writer *pio_Writer__write_token(struct io_Writer *self, struct calculator__tokenizer_Token *token) {
#line 132 "tests/99__calculator/calculator/tokenizer.code"
    struct calculator__tokenizer_Token *__switch_132_value__ = token;
#line 133 "tests/99__calculator/calculator/tokenizer.code"
    if (__switch_132_value__->variant == 1) {
#line 134 "tests/99__calculator/calculator/tokenizer.code"
        {
#line 134 "tests/99__calculator/calculator/tokenizer.code"
            struct io_Writer *__001__ = self;
#line 134 "tests/99__calculator/calculator/tokenizer.code"
            struct String __002__ = (struct String){.data = "Number: ", .length = 8};
#line 134 "tests/99__calculator/calculator/tokenizer.code"
            struct io_Writer *__003__ = pio_Writer__write_string(__001__, __002__);
#line 134 "tests/99__calculator/calculator/tokenizer.code"
            int32_t __004__ = __switch_132_value__->variant_1.value;
#line 134 "tests/99__calculator/calculator/tokenizer.code"
            return pio_Writer__write_signed(__003__, __004__);
        }
    }
#line 136 "tests/99__calculator/calculator/tokenizer.code"
    else if (__switch_132_value__->variant == 2) {
#line 137 "tests/99__calculator/calculator/tokenizer.code"
        {
#line 137 "tests/99__calculator/calculator/tokenizer.code"
            struct io_Writer *__001__ = self;
#line 137 "tests/99__calculator/calculator/tokenizer.code"
            struct String __002__ = (struct String){.data = "Plus", .length = 4};
#line 137 "tests/99__calculator/calculator/tokenizer.code"
            return pio_Writer__write_string(__001__, __002__);
        }
    }
#line 139 "tests/99__calculator/calculator/tokenizer.code"
    else if (__switch_132_value__->variant == 3) {
#line 140 "tests/99__calculator/calculator/tokenizer.code"
        {
#line 140 "tests/99__calculator/calculator/tokenizer.code"
            struct io_Writer *__001__ = self;
#line 140 "tests/99__calculator/calculator/tokenizer.code"
            struct String __002__ = (struct String){.data = "Minus", .length = 5};
#line 140 "tests/99__calculator/calculator/tokenizer.code"
            return pio_Writer__write_string(__001__, __002__);
        }
    }
#line 142 "tests/99__calculator/calculator/tokenizer.code"
    else if (__switch_132_value__->variant == 4) {
#line 143 "tests/99__calculator/calculator/tokenizer.code"
        {
#line 143 "tests/99__calculator/calculator/tokenizer.code"
            struct io_Writer *__001__ = self;
#line 143 "tests/99__calculator/calculator/tokenizer.code"
            struct String __002__ = (struct String){.data = "Multiply", .length = 8};
#line 143 "tests/99__calculator/calculator/tokenizer.code"
            return pio_Writer__write_string(__001__, __002__);
        }
    }
#line 145 "tests/99__calculator/calculator/tokenizer.code"
    else if (__switch_132_value__->variant == 5) {
#line 146 "tests/99__calculator/calculator/tokenizer.code"
        {
#line 146 "tests/99__calculator/calculator/tokenizer.code"
            struct io_Writer *__001__ = self;
#line 146 "tests/99__calculator/calculator/tokenizer.code"
            struct String __002__ = (struct String){.data = "Divide", .length = 6};
#line 146 "tests/99__calculator/calculator/tokenizer.code"
            return pio_Writer__write_string(__001__, __002__);
        }
    }
#line 148 "tests/99__calculator/calculator/tokenizer.code"
    else if (__switch_132_value__->variant == 6) {
#line 149 "tests/99__calculator/calculator/tokenizer.code"
        {
#line 149 "tests/99__calculator/calculator/tokenizer.code"
            struct io_Writer *__001__ = self;
#line 149 "tests/99__calculator/calculator/tokenizer.code"
            struct String __002__ = (struct String){.data = "Stop", .length = 4};
#line 149 "tests/99__calculator/calculator/tokenizer.code"
            return pio_Writer__write_string(__001__, __002__);
        }
    }
#line 151 "tests/99__calculator/calculator/tokenizer.code"
    else if (__switch_132_value__->variant == 7) {
#line 152 "tests/99__calculator/calculator/tokenizer.code"
        {
#line 152 "tests/99__calculator/calculator/tokenizer.code"
            struct io_Writer *__001__ = self;
#line 152 "tests/99__calculator/calculator/tokenizer.code"
            struct String __002__ = (struct String){.data = "Error: ", .length = 7};
#line 152 "tests/99__calculator/calculator/tokenizer.code"
            struct io_Writer *__003__ = pio_Writer__write_string(__001__, __002__);
#line 152 "tests/99__calculator/calculator/tokenizer.code"
            struct String __004__ = __switch_132_value__->variant_7.message;
#line 152 "tests/99__calculator/calculator/tokenizer.code"
            return pio_Writer__write_string(__003__, __004__);
        }
    }
#line 154 "tests/99__calculator/calculator/tokenizer.code"
    else if (__switch_132_value__->variant == 0) {
#line 155 "tests/99__calculator/calculator/tokenizer.code"
        {
#line 155 "tests/99__calculator/calculator/tokenizer.code"
            struct io_Writer *__001__ = self;
#line 155 "tests/99__calculator/calculator/tokenizer.code"
            struct String __002__ = (struct String){.data = "Nil!", .length = 4};
#line 155 "tests/99__calculator/calculator/tokenizer.code"
            return pio_Writer__write_string(__001__, __002__);
        }
    }
#line 158 "tests/99__calculator/calculator/tokenizer.code"
    return self;
}

