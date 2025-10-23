#ifndef __calculator__expression_H__
#define __calculator__expression_H__

#include "types.h"

#include "calculator__source.h"
#include "io.h"
#include "libc.h"

struct calculator__source_Span pcalculator__expression_Expression__span(struct calculator__expression_Expression *self);

struct io_Writer *pio_Writer__write_expression(struct io_Writer *self, struct calculator__expression_Expression *expression);

#endif // __calculator__expression_H__
