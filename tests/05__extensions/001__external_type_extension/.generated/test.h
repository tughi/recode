#ifndef __test_H__
#define __test_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>


typedef struct FILE FILE;

extern FILE *__stdoutp;
int32_t test__main();

FILE *test__pFILE__write__1_char(FILE *self, uint8_t ch);

int32_t fputc(int32_t c, FILE *stream);

#endif // __test_H__
