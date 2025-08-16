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

#line 7 "tests/99__calculator/io.code"
struct io_Writer *pio_Writer__write_string(struct io_Writer *self, struct String string) {
#line 8 "tests/99__calculator/io.code"
    struct String string_copy = string;
#line 9 "tests/99__calculator/io.code"
    uint8_t *string_data = ((struct String *) (&string_copy))->data;
#line 10 "tests/99__calculator/io.code"
    uintmax_t index = 0u;
#line 11 "tests/99__calculator/io.code"
    while (index < string.length) {
#line 12 "tests/99__calculator/io.code"
        pio_Writer__write(self, string_data[index]);
#line 13 "tests/99__calculator/io.code"
        index = index + 1u;
#line 14 "tests/99__calculator/io.code"
    }
#line 15 "tests/99__calculator/io.code"
    return self;
#line 16 "tests/99__calculator/io.code"
}

#line 18 "tests/99__calculator/io.code"
struct io_Writer *pio_Writer__write(struct io_Writer *self, uint8_t c) {
#line 19 "tests/99__calculator/io.code"
    self->write_char(self->self, c);
#line 20 "tests/99__calculator/io.code"
    return self;
#line 21 "tests/99__calculator/io.code"
}

#line 23 "tests/99__calculator/io.code"
struct io_Writer *pio_Writer__write_signed(struct io_Writer *self, int32_t value) {
#line 25 "tests/99__calculator/io.code"
    if (value < 0) {
#line 26 "tests/99__calculator/io.code"
        pio_Writer__write(self, '-');
#line 27 "tests/99__calculator/io.code"
        return pio_Writer__write_signed(self, -value);
#line 28 "tests/99__calculator/io.code"
    }
#line 29 "tests/99__calculator/io.code"
    if (value >= 10) {
#line 30 "tests/99__calculator/io.code"
        pio_Writer__write_signed(self, value / 10);
#line 31 "tests/99__calculator/io.code"
    }
#line 32 "tests/99__calculator/io.code"
    return pio_Writer__write(self, ((uint8_t) (value % 10)) + '0');
#line 33 "tests/99__calculator/io.code"
}

#line 35 "tests/99__calculator/io.code"
struct io_Writer *pio_Writer__end_line(struct io_Writer *self) {
#line 36 "tests/99__calculator/io.code"
    pio_Writer__write(self, '\n');
#line 37 "tests/99__calculator/io.code"
    return self;
#line 38 "tests/99__calculator/io.code"
}

