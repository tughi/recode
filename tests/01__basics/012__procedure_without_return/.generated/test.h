#ifndef __test_H__
#define __test_H__

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>


void exit(int32_t status);

int32_t test__main();

void test__finish();

void test__nothing();

#endif // __test_H__
