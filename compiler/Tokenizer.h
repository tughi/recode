/* Copyright (C) 2024 Stefan Selariu */

#ifndef __TOKENIZER_H__
#define __TOKENIZER_H__

#include "Token.h"

typedef struct Tokenizer {
    Source *source;
    size_t source_index;
    size_t source_line;
    size_t source_column;

    String *lexeme_buffer;
} Tokenizer;

Tokenizer *create_tokenizer(Source *source);

Token *pTokenizer__next(Tokenizer *tokenizer);

#endif
