#pragma once

#include "Source.h"
#include "Token.h"

typedef struct {
    Source  source;
    Token  *tokens;
    size_t  tokens_size;
    Token **lines;
    size_t  lines_size;
} Lexed_Source;

Lexed_Source tokenize(Source source);
void lexed_source_destroy(Lexed_Source lexed_source);
