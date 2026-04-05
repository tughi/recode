#ifndef __calculator__tokenizer_H__
#define __calculator__tokenizer_H__

#include "types.h"

#include "calculator__expression.h"
#include "calculator__source.h"
#include "io.h"
#include "libc.h"

struct calculator__source_Span pcalculator__tokenizer_Token__span(struct calculator__tokenizer_Token *self);

struct io_Writer *pio_Writer__write_token__anon(struct io_Writer *self, struct calculator__tokenizer_Token *token);

struct calculator__tokenizer_Token pcalculator__tokenizer_Tokenizer__peek_token(struct calculator__tokenizer_Tokenizer *self);

struct calculator__tokenizer_Token pcalculator__tokenizer_Tokenizer__next_token(struct calculator__tokenizer_Tokenizer *self);

struct calculator__tokenizer_Token pcalculator__tokenizer_Tokenizer__scan_token(struct calculator__tokenizer_Tokenizer *self);

struct calculator__tokenizer_Token pcalculator__tokenizer_Tokenizer__scan_number_token(struct calculator__tokenizer_Tokenizer *self);

#endif // __calculator__tokenizer_H__
