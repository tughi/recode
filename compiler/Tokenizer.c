/* Copyright (C) 2024 Stefan Selariu */

#include "Tokenizer.h"

Tokenizer *create_tokenizer(Source *source) {
    Tokenizer *tokenizer = malloc(sizeof(Tokenizer));
    tokenizer->source = source;
    tokenizer->source_index = 0;
    tokenizer->source_line = 1;
    tokenizer->source_column = 1;
    tokenizer->lexeme_buffer = create_string();
    return tokenizer;
}

static char peek_char(Tokenizer *tokenizer) {
    return tokenizer->source->content[tokenizer->source_index];
}

static char next_char(Tokenizer *tokenizer) {
    char c = tokenizer->source->content[tokenizer->source_index];
    if (c != '\0') {
        tokenizer->source_index++;
        if (c == '\n') {
            tokenizer->source_line++;
            tokenizer->source_column = 1;
        } else {
            tokenizer->source_column++;
        }
    }
    return c;
}

Token *pTokenizer__next(Tokenizer *tokenizer) {
    Source_Location *location = create_source_location(tokenizer->source, tokenizer->source_line, tokenizer->source_column);
    pString__clear(tokenizer->lexeme_buffer);

    char c = peek_char(tokenizer);

    if (c == '\0') {
        return create_token(TOKEN_END_OF_FILE, location, tokenizer->lexeme_buffer, 0);
    }

    if (c == '\n') {
        next_char(tokenizer);
        return create_token(TOKEN_END_OF_LINE, location, tokenizer->lexeme_buffer, 0);
    }

    if (c == ' ') {
        uint64_t count = 0;
        while (peek_char(tokenizer) == ' ') {
            pString__append__char(tokenizer->lexeme_buffer, next_char(tokenizer));
            count++;
        }
        return create_token(TOKEN_SPACE, location, tokenizer->lexeme_buffer, count);
    }

    if (isalpha(c) || c == '_') {
        while (isalnum(c = peek_char(tokenizer)) || c == '_') {
            pString__append__char(tokenizer->lexeme_buffer, next_char(tokenizer));
        }
        return create_token(TOKEN_IDENTIFIER, location, tokenizer->lexeme_buffer, 0);
    }

    if (isdigit(c)) {
        uint64_t value = 0;
        while (isdigit(c = peek_char(tokenizer))) {
            pString__append__char(tokenizer->lexeme_buffer, next_char(tokenizer));
            value = value * 10 + (c - '0');
        }
        return create_token(TOKEN_NUMBER, location, tokenizer->lexeme_buffer, value);
    }

    pString__append__char(tokenizer->lexeme_buffer, c = next_char(tokenizer));
    return create_token(TOKEN_OTHER, location, tokenizer->lexeme_buffer, c);
}
