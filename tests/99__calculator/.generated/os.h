#ifndef __os_H__
#define __os_H__

#include "types.h"

#include "io.h"
#include "libc.h"

extern struct io_Writer *os__stdout;

extern struct io_Writer *os__stderr;

void os__init();

void plibc_FILE__write_char__anon(struct libc_FILE *self, uint8_t c);

#endif // __os_H__
