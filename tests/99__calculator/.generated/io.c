#include "test.h"
#include "calculator__expression.h"
#include "calculator__source.h"
#include "libc.h"
#include "io.h"
#include "calculator__parser.h"
#include "calculator__tokenizer.h"
#include "os.h"
#include "string.h"

struct io_Writer *__alloc__io_Writer__(struct io_Writer value) {
    struct io_Writer *result = (struct io_Writer *)malloc(sizeof(struct io_Writer));
    *result = value;
    return result;
}

#line 7 "tests/99__calculator/io.code"
struct io_Writer *pio_Writer__write_string(struct io_Writer *self, struct String string) {
#line 8 "tests/99__calculator/io.code"
    struct String string_copy = string;
#line 9 "tests/99__calculator/io.code"
    uint8_t *string_data = ((struct String *) (&string_copy))->data;
#line 10 "tests/99__calculator/io.code"
    uintmax_t index = 0;
#line 11 "tests/99__calculator/io.code"
    while (index < string.length) {
#line 12 "tests/99__calculator/io.code"
        {
#line 12 "tests/99__calculator/io.code"
            struct io_Writer *__001__ = self;
#line 12 "tests/99__calculator/io.code"
            uintmax_t __002__ = index;
#line 12 "tests/99__calculator/io.code"
            uint8_t __003__ = string_data[__002__];
#line 12 "tests/99__calculator/io.code"
            pio_Writer__write(__001__, __003__);
        }
#line 13 "tests/99__calculator/io.code"
        index = index + 1;
    }
#line 15 "tests/99__calculator/io.code"
    return self;
}

#line 18 "tests/99__calculator/io.code"
struct io_Writer *pio_Writer__write(struct io_Writer *self, uint8_t c) {
#line 19 "tests/99__calculator/io.code"
    {
#line 19 "tests/99__calculator/io.code"
        void *__001__ = self->self;
#line 19 "tests/99__calculator/io.code"
        uint8_t __002__ = c;
#line 19 "tests/99__calculator/io.code"
        self->write_char(__001__, __002__);
    }
#line 20 "tests/99__calculator/io.code"
    return self;
}

#line 23 "tests/99__calculator/io.code"
struct io_Writer *pio_Writer__write_signed(struct io_Writer *self, int32_t value) {
#line 25 "tests/99__calculator/io.code"
    if (value < 0) {
#line 26 "tests/99__calculator/io.code"
        {
#line 26 "tests/99__calculator/io.code"
            struct io_Writer *__001__ = self;
#line 26 "tests/99__calculator/io.code"
            uint8_t __002__ = '-';
#line 26 "tests/99__calculator/io.code"
            pio_Writer__write(__001__, __002__);
        }
#line 27 "tests/99__calculator/io.code"
        {
#line 27 "tests/99__calculator/io.code"
            struct io_Writer *__001__ = self;
#line 27 "tests/99__calculator/io.code"
            int32_t __002__ = -value;
#line 27 "tests/99__calculator/io.code"
            return pio_Writer__write_signed(__001__, __002__);
        }
    }
#line 29 "tests/99__calculator/io.code"
    if (value >= 10) {
#line 30 "tests/99__calculator/io.code"
        {
#line 30 "tests/99__calculator/io.code"
            struct io_Writer *__001__ = self;
#line 30 "tests/99__calculator/io.code"
            int32_t __002__ = value / 10;
#line 30 "tests/99__calculator/io.code"
            pio_Writer__write_signed(__001__, __002__);
        }
    }
#line 32 "tests/99__calculator/io.code"
    {
#line 32 "tests/99__calculator/io.code"
        struct io_Writer *__001__ = self;
#line 32 "tests/99__calculator/io.code"
        uint8_t __002__ = ((uint8_t) (value % 10)) + '0';
#line 32 "tests/99__calculator/io.code"
        return pio_Writer__write(__001__, __002__);
    }
}

#line 35 "tests/99__calculator/io.code"
struct io_Writer *pio_Writer__end_line(struct io_Writer *self) {
#line 36 "tests/99__calculator/io.code"
    {
#line 36 "tests/99__calculator/io.code"
        struct io_Writer *__001__ = self;
#line 36 "tests/99__calculator/io.code"
        uint8_t __002__ = '\n';
#line 36 "tests/99__calculator/io.code"
        pio_Writer__write(__001__, __002__);
    }
#line 37 "tests/99__calculator/io.code"
    return self;
}

