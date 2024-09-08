/* Copyright (C) 2024 Stefan Selariu */

#ifndef __TOKEN_H__
#define __TOKEN_H__

#include "Source_Location.h"
#include "String.h"
#include "Writer.h"

typedef enum Token_Type {
    TOKEN_CHARACTER,
    TOKEN_COMMENT,
    TOKEN_END_OF_FILE,
    TOKEN_END_OF_LINE,
    TOKEN_ERROR,
    TOKEN_IDENTIFIER,
    TOKEN_KEYWORD,
    TOKEN_NUMBER,
    TOKEN_OTHER,
    TOKEN_SPACE,
    TOKEN_STRING
} Token_Type;

Writer *pWriter__write__token_type(Writer *writer, Token_Type type);

typedef struct Token {
    Token_Type type;
    Source_Location *location;
    String *lexeme;
    uint64_t value;
} Token;

Token *create_token(Token_Type type, Source_Location *location, String *lexeme, uint64_t value);

Writer *pWriter__write__token(Writer *writer, Token *token);

#endif
