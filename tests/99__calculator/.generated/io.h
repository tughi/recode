#ifndef __io_H__
#define __io_H__

#include "types.h"

#include "libc.h"

struct io_Writer *pio_Writer__write_string__anon(struct io_Writer *self, struct String string);

struct io_Writer *pio_Writer__write__char(struct io_Writer *self, uint8_t c);

struct io_Writer *pio_Writer__write_signed__signed(struct io_Writer *self, int32_t value);

struct io_Writer *pio_Writer__end_line(struct io_Writer *self);

#endif // __io_H__
