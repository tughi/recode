#pragma once

#include "File.h"
#include "Token.h"

typedef struct Lexer Lexer;

Lexer *lexer_create(File file);
void lexer_destroy(Lexer *lexer);
Token lexer_next(Lexer *lexer);
