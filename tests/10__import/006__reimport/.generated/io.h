#ifndef __io_H__
#define __io_H__

#include "types.h"

#include "libc.h"

struct io_Writer *pio_Writer__write(struct io_Writer *writer, int32_t c);

int32_t plibc_FILE__write_char(struct libc_FILE *file, int32_t c);

#endif // __io_H__
