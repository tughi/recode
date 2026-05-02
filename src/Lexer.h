#pragma once

#include "String.h"
#include "Token.h"

typedef struct Lexer Lexer;

Lexer *lexer_create(String source);
void lexer_destroy(Lexer *lexer);
Token lexer_next(Lexer *lexer);
