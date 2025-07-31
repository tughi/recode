#include "test.h"
#include "calculator__expression.h"
#include "calculator__source.h"
#include "libc.h"
#include "io.h"
#include "calculator__parser.h"
#include "calculator__tokenizer.h"
#include "os.h"
#include "string.h"

struct calculator__tokenizer_Tokenizer *__alloc__calculator__tokenizer_Tokenizer__(struct calculator__tokenizer_Tokenizer value) {
    struct calculator__tokenizer_Tokenizer *result = (struct calculator__tokenizer_Tokenizer *)malloc(sizeof(struct calculator__tokenizer_Tokenizer));
    *result = value;
    return result;
}

struct calculator__tokenizer_Token *__alloc__calculator__tokenizer_Token__(struct calculator__tokenizer_Token value) {
struct calculator__tokenizer_Token *result = (struct calculator__tokenizer_Token *)malloc(sizeof(struct calculator__tokenizer_Token));
    *result = value;
    return result;
}

struct calculator__tokenizer_Plus *__alloc__calculator__tokenizer_Plus__(struct calculator__tokenizer_Plus value) {
    struct calculator__tokenizer_Plus *result = (struct calculator__tokenizer_Plus *)malloc(sizeof(struct calculator__tokenizer_Plus));
    *result = value;
    return result;
}

struct calculator__tokenizer_Minus *__alloc__calculator__tokenizer_Minus__(struct calculator__tokenizer_Minus value) {
    struct calculator__tokenizer_Minus *result = (struct calculator__tokenizer_Minus *)malloc(sizeof(struct calculator__tokenizer_Minus));
    *result = value;
    return result;
}

struct calculator__tokenizer_Multiply *__alloc__calculator__tokenizer_Multiply__(struct calculator__tokenizer_Multiply value) {
    struct calculator__tokenizer_Multiply *result = (struct calculator__tokenizer_Multiply *)malloc(sizeof(struct calculator__tokenizer_Multiply));
    *result = value;
    return result;
}

struct calculator__tokenizer_Divide *__alloc__calculator__tokenizer_Divide__(struct calculator__tokenizer_Divide value) {
    struct calculator__tokenizer_Divide *result = (struct calculator__tokenizer_Divide *)malloc(sizeof(struct calculator__tokenizer_Divide));
    *result = value;
    return result;
}

struct calculator__tokenizer_Stop *__alloc__calculator__tokenizer_Stop__(struct calculator__tokenizer_Stop value) {
    struct calculator__tokenizer_Stop *result = (struct calculator__tokenizer_Stop *)malloc(sizeof(struct calculator__tokenizer_Stop));
    *result = value;
    return result;
}

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
    while (self->data[self->index] == ' ') {
#line 27 "tests/99__calculator/calculator/tokenizer.code"
        self->index = self->index + 1;
    }
#line 29 "tests/99__calculator/calculator/tokenizer.code"
    uint8_t ch = self->data[self->index];
#line 30 "tests/99__calculator/calculator/tokenizer.code"
    if (ch == 0) {
#line 31 "tests/99__calculator/calculator/tokenizer.code"
        return (struct calculator__tokenizer_Token){.variant = 6, .variant_6 = (struct calculator__tokenizer_Stop){.span = (struct calculator__source_Span){.start = self->index, .end = self->index}}};
    }
#line 33 "tests/99__calculator/calculator/tokenizer.code"
    {
#line 33 "tests/99__calculator/calculator/tokenizer.code"
        bool __001__;
#line 33 "tests/99__calculator/calculator/tokenizer.code"
        bool __002__ = ch >= '0';
#line 33 "tests/99__calculator/calculator/tokenizer.code"
        if (__002__) {
#line 33 "tests/99__calculator/calculator/tokenizer.code"
            bool __003__ = ch <= '9';
#line 33 "tests/99__calculator/calculator/tokenizer.code"
            __001__ = __003__;
        } else {
#line 33 "tests/99__calculator/calculator/tokenizer.code"
            __001__ = __002__;
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
        return (struct calculator__tokenizer_Token){.variant = 2, .variant_2 = (struct calculator__tokenizer_Plus){.span = (struct calculator__source_Span){.start = self->index - 1, .end = self->index}}};
    }
#line 40 "tests/99__calculator/calculator/tokenizer.code"
    if (ch == '-') {
#line 41 "tests/99__calculator/calculator/tokenizer.code"
        return (struct calculator__tokenizer_Token){.variant = 3, .variant_3 = (struct calculator__tokenizer_Minus){.span = (struct calculator__source_Span){.start = self->index - 1, .end = self->index}}};
    }
#line 43 "tests/99__calculator/calculator/tokenizer.code"
    if (ch == '*') {
#line 44 "tests/99__calculator/calculator/tokenizer.code"
        return (struct calculator__tokenizer_Token){.variant = 4, .variant_4 = (struct calculator__tokenizer_Multiply){.span = (struct calculator__source_Span){.start = self->index - 1, .end = self->index}}};
    }
#line 46 "tests/99__calculator/calculator/tokenizer.code"
    if (ch == '/') {
#line 47 "tests/99__calculator/calculator/tokenizer.code"
        return (struct calculator__tokenizer_Token){.variant = 5, .variant_5 = (struct calculator__tokenizer_Divide){.span = (struct calculator__source_Span){.start = self->index - 1, .end = self->index}}};
    }
#line 49 "tests/99__calculator/calculator/tokenizer.code"
    return (struct calculator__tokenizer_Token){.variant = 7, .variant_7 = (struct calculator__source_Error){.span = (struct calculator__source_Span){.start = self->index - 1, .end = self->index}, .message = (struct String){.data = "Unexpected character", .length = 20}}};
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
        uint8_t c = self->data[self->index];
#line 60 "tests/99__calculator/calculator/tokenizer.code"
        {
#line 60 "tests/99__calculator/calculator/tokenizer.code"
            bool __001__;
#line 60 "tests/99__calculator/calculator/tokenizer.code"
            bool __002__ = c < '0';
#line 60 "tests/99__calculator/calculator/tokenizer.code"
            if (__002__) {
#line 60 "tests/99__calculator/calculator/tokenizer.code"
                __001__ = __002__;
            } else {
#line 60 "tests/99__calculator/calculator/tokenizer.code"
                bool __003__ = c > '9';
#line 60 "tests/99__calculator/calculator/tokenizer.code"
                __001__ = __003__;
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
    return (struct calculator__tokenizer_Token){.variant = 1, .variant_1 = (struct calculator__expression_Number){.span = (struct calculator__source_Span){.start = start, .end = self->index}, .value = value}};
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
        return (struct calculator__source_Span){.start = 0, .end = 0};
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

