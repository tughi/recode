#pragma once

#include "Token.h"

typedef struct Lexer {
    String source;
    size_t source_position;
} Lexer;

void lexer_init(Lexer *lexer, String source);
Token lexer_next(Lexer *lexer);
