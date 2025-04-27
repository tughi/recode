#ifndef __test_H__
#define __test_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>


typedef struct test__FILE test__FILE;

extern test__FILE *__stdoutp;
int32_t fputc(int32_t ch, test__FILE *file);

int32_t test__main();

#endif // __test_H__
