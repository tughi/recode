#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

#include "io.h"

struct io_Writer *__alloc__io_Writer__(struct io_Writer value) {
    struct io_Writer *result = (struct io_Writer *)malloc(sizeof(struct io_Writer));
    *result = value;
    return result;
}

#line 7 "tests/99__calculator/io.code"
struct io_Writer *pio_Writer__write__1_char(struct io_Writer *self, uint8_t c) {
#line 8 "tests/99__calculator/io.code"
    self->write_char(self->self, c);
#line 9 "tests/99__calculator/io.code"
    return self;
}

#line 12 "tests/99__calculator/io.code"
struct io_Writer *pio_Writer__write__1_signed(struct io_Writer *self, int32_t value) {
#line 14 "tests/99__calculator/io.code"
    if (value < 0) {
#line 15 "tests/99__calculator/io.code"
        pio_Writer__write__1_char(self, '-');
#line 16 "tests/99__calculator/io.code"
        return pio_Writer__write__1_signed(self, -value);
    }
#line 18 "tests/99__calculator/io.code"
    if (value >= 10) {
#line 19 "tests/99__calculator/io.code"
        pio_Writer__write__1_signed(self, value / 10);
    }
#line 21 "tests/99__calculator/io.code"
    return pio_Writer__write__1_char(self, ((uint8_t) (value % 10)) + '0');
}

#line 24 "tests/99__calculator/io.code"
struct io_Writer *pio_Writer__end_line(struct io_Writer *self) {
#line 25 "tests/99__calculator/io.code"
    pio_Writer__write__1_char(self, '\n');
#line 26 "tests/99__calculator/io.code"
    return self;
}

