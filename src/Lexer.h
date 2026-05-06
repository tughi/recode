#pragma once

#include "Source.h"
#include "Token.h"

typedef struct Lexer Lexer;

Lexer *lexer_create(Source source);
void lexer_destroy(Lexer *lexer);
Token lexer_next(Lexer *lexer);
