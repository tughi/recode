#ifndef __io_H__
#define __io_H__

#include "builtin_types.h"

#include "libc.h"

struct io_Writer {
    void *self;
    void (*write_char)(void *self, uint8_t c);
};

struct io_Writer *__alloc__io_Writer__(struct io_Writer value);

struct io_Writer *pio_Writer__write(struct io_Writer *self, struct String string);

struct io_Writer *pio_Writer__write__1_char(struct io_Writer *self, uint8_t c);

struct io_Writer *pio_Writer__write__1_signed(struct io_Writer *self, int32_t value);

struct io_Writer *pio_Writer__end_line(struct io_Writer *self);

#endif // __io_H__
