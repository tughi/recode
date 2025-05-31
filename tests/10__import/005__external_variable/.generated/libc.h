#ifndef __libc_H__
#define __libc_H__

#include "builtin_types.h"


extern struct libc_FILE *__stdoutp;

int32_t fputc(int32_t c, struct libc_FILE *file);

#endif // __libc_H__
