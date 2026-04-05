#ifndef __test_H__
#define __test_H__

#include "types.h"


extern struct test_FILE *__stdoutp;

int32_t test__main();

void pi32__write_to__anon(int32_t *self, struct test_Writer *writer);

void pstr__write_to__anon(struct String *self, struct test_Writer *writer);

struct test_Writer *ptest_Writer__end_line(struct test_Writer *self);

struct test_Writer *ptest_Writer__write__anon(struct test_Writer *self, struct test_Writable writable);

int32_t fputc(int32_t c, struct test_FILE *file);

void ptest_FILE__write_char__anon(struct test_FILE *self, uint8_t c);

#endif // __test_H__
