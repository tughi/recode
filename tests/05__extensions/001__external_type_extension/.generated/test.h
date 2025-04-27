#ifndef __test_H__
#define __test_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>


typedef struct test__FILE test__FILE;

extern test__FILE *__stdoutp;
int32_t test__main();

test__FILE *test__ptest__FILE__write__1_char(test__FILE *self, uint8_t ch);

int32_t fputc(int32_t c, test__FILE *stream);

#endif // __test_H__
