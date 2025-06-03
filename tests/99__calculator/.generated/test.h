#ifndef __test_H__
#define __test_H__

#include "builtin_types.h"

#include "calculator__expression.h"
#include "calculator__parser.h"
#include "calculator__tokenizer.h"
#include "calculator__source.h"
#include "io.h"
#include "libc.h"
#include "os.h"
#include "string.h"

int32_t test__main(int32_t argc, uint8_t **argv);

int32_t test__evaluate(struct calculator__expression_Expression *expression);

#endif // __test_H__
