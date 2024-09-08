/* Copyright (C) 2024 Stefan Selariu */

#include "Token.h"

Writer *pWriter__write__token_type(Writer *writer, Token_Type type) {
    switch (type) {
    case TOKEN_CHARACTER:
        return pWriter__write__cstring(writer, "TOKEN_CHARACTER");
    case TOKEN_COMMENT:
        return pWriter__write__cstring(writer, "TOKEN_COMMENT");
    case TOKEN_END_OF_FILE:
        return pWriter__write__cstring(writer, "TOKEN_END_OF_FILE");
    case TOKEN_END_OF_LINE:
        return pWriter__write__cstring(writer, "TOKEN_END_OF_LINE");
    case TOKEN_ERROR:
        return pWriter__write__cstring(writer, "TOKEN_ERROR");
    case TOKEN_IDENTIFIER:
        return pWriter__write__cstring(writer, "TOKEN_IDENTIFIER");
    case TOKEN_KEYWORD:
        return pWriter__write__cstring(writer, "TOKEN_KEYWORD");
    case TOKEN_NUMBER:
        return pWriter__write__cstring(writer, "TOKEN_NUMBER");
    case TOKEN_OTHER:
        return pWriter__write__cstring(writer, "TOKEN_OTHER");
    case TOKEN_SPACE:
        return pWriter__write__cstring(writer, "TOKEN_SPACE");
    case TOKEN_STRING:
        return pWriter__write__cstring(writer, "TOKEN_STRING");
    default:
        fprintf(stderr, "Unknown token type: %d\n", type);
        exit(1);
    }
}

Token *create_token(Token_Type type, Source_Location *location, String *lexeme, uint64_t value) {
    Token *token = malloc(sizeof(Token));
    token->type = type;
    token->location = location;
    token->lexeme = lexeme;
    token->value = value;
    return token;
}

Writer *pWriter__write__token(Writer *writer, Token *token) {
    pWriter__write__cstring(writer, "Token { type: ");
    pWriter__write__token_type(writer, token->type);
    if (token->value != 0) {
        pWriter__write__cstring(writer, ", value: ");
        pWriter__write__u64(writer, token->value);
    }
    pWriter__write__cstring(writer, " }");
    return writer;
}
