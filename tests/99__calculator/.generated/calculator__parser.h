#ifndef __calculator__parser_H__
#define __calculator__parser_H__

#include "types.h"

#include "calculator__expression.h"
#include "calculator__source.h"
#include "calculator__tokenizer.h"

struct calculator__expression_Expression pcalculator__parser_Parser__parse_expression(struct calculator__parser_Parser *self);

struct calculator__expression_Expression pcalculator__parser_Parser__parse_additive_expression(struct calculator__parser_Parser *self);

struct calculator__expression_Expression pcalculator__parser_Parser__parse_multiplicative_expression(struct calculator__parser_Parser *self);

struct calculator__expression_Expression pcalculator__parser_Parser__parse_primary_expression(struct calculator__parser_Parser *self);

#endif // __calculator__parser_H__
