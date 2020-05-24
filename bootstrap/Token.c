#include "Token.h"

#include "Logging.h"

#include <stdlib.h>

static Token *token__create(int kind, Source_Location *location, String *lexeme) {
    Token *self = malloc(sizeof(Token));
    self->kind = kind;
    self->location = location;
    self->lexeme = lexeme;
    return self;
}

Token *token__create_character(Source_Location *location, String *lexeme, char value) {
    Token *self = token__create(TOKEN_CHARACTER, location, lexeme);
    self->character_data.value = value;
    return self;
}

Token *token__create_comment(Source_Location *location, String *lexeme) {
    return token__create(TOKEN_COMMENT, location, lexeme);
}

Token *token__create_end_of_file(Source_Location *location, String *lexeme) {
    return token__create(TOKEN_END_OF_FILE, location, lexeme);
}

Token *token__create_end_of_line(Source_Location *location, String *lexeme) {
    return token__create(TOKEN_END_OF_LINE, location, lexeme);
}

Token *token__create_error(Source_Location *location, String *lexeme) {
    return token__create(TOKEN_ERROR, location, lexeme);
}

Token *token__create_identifier(Source_Location *location, String *lexeme) {
    return token__create(TOKEN_IDENTIFIER, location, lexeme);
}

Token *token__create_integer(Source_Location *location, String *lexeme, int value) {
    Token *self = token__create(TOKEN_INTEGER, location, lexeme);
    self->integer_data.value = value;
    return self;
}

Token *token__create_keyword(Source_Location *location, String *lexeme) {
    return token__create(TOKEN_KEYWORD, location, lexeme);
}

Token *token__create_other(Source_Location *location, String *lexeme) {
    return token__create(TOKEN_OTHER, location, lexeme);
}

Token *token__create_space(Source_Location *location, String *lexeme, int count) {
    Token *self = token__create(TOKEN_SPACE, location, lexeme);
    self->space_data.count = count;
    return self;
}

Token *token__create_string(Source_Location *location, String *lexeme, String *value) {
    Token *self = token__create(TOKEN_STRING, location, lexeme);
    self->string_data.value = value;
    return self;
}

char *token__get_kind_name(Token *self) {
    switch (self->kind) {
    case TOKEN_CHARACTER:
        return "CHARACTER";
    case TOKEN_COMMENT:
        return "COMMENT";
    case TOKEN_END_OF_FILE:
        return "END_OF_FILE";
    case TOKEN_END_OF_LINE:
        return "END_OF_LINE";
    case TOKEN_ERROR:
        return "ERROR";
    case TOKEN_IDENTIFIER:
        return "IDENTIFIER";
    case TOKEN_INTEGER:
        return "INTEGER";
    case TOKEN_KEYWORD:
        return "KEYWORD";
    case TOKEN_OTHER:
        return "OTHER";
    case TOKEN_SPACE:
        return "SPACE";
    case TOKEN_STRING:
        return "STRING";
    default:
        PANIC(__FILE__, __LINE__, "Unsupported token kind: %d", self->kind);
    }
}

void token__join(Token *self, Token *other) {
    string__append_string(self->lexeme, other->lexeme);
    other->lexeme = string__create("");
}
