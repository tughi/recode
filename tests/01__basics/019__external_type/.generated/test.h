#ifndef __test_H__
#define __test_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>


extern struct test_FILE *__stdoutp;

int32_t fputc(int32_t ch, struct test_FILE *file);

int32_t test__main();

#endif // __test_H__
