#ifndef __libc_H__
#define __libc_H__

#include "builtin_types.h"


extern struct libc_FILE *__stdinp;

extern struct libc_FILE *__stdoutp;

extern struct libc_FILE *__stderrp;

int32_t fputc(int32_t c, struct libc_FILE *file);

void *malloc(uint64_t size);

void *realloc(void *block, uint64_t size);

void exit(int32_t code);

#endif // __libc_H__
