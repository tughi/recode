#ifndef __test_H__
#define __test_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>


struct test_FILE;

extern struct test_FILE *__stdoutp;

int32_t test__main();

struct test_FILE *ptest_FILE__write__1_char(struct test_FILE *self, uint8_t ch);

int32_t fputc(int32_t c, struct test_FILE *stream);

#endif // __test_H__
