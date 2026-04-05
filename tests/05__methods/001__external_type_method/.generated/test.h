#ifndef __test_H__
#define __test_H__

#include "types.h"


extern struct test_FILE *__stdoutp;

int32_t test__main();

struct test_FILE *ptest_FILE__write__char(struct test_FILE *self, uint8_t ch);

int32_t fputc(int32_t c, struct test_FILE *stream);

#endif // __test_H__
