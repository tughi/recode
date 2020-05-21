#include "Token.h"

#include "Logging.h"

#include <stdlib.h>

static Token *token__create(int kind, String *lexeme, int line, int column) {
    Token *self = malloc(sizeof(Token));
    self->kind = kind;
    self->lexeme = lexeme;
    self->line = line;
    self->column = column;
    return self;
}

Token *token__create_character(String *lexeme, int line, int column, char value) {
    Token *self = token__create(TOKEN_CHARACTER, lexeme, line, column);
    self->character.value = value;
    return self;
}

Token *token__create_comment(String *lexeme, int line, int column) {
    return token__create(TOKEN_COMMENT, lexeme, line, column);
}

Token *token__create_end_of_file(String *lexeme, int line, int column) {
    return token__create(TOKEN_END_OF_FILE, lexeme, line, column);
}

Token *token__create_end_of_line(String *lexeme, int line, int column) {
    return token__create(TOKEN_END_OF_LINE, lexeme, line, column);
}

Token *token__create_error(String *lexeme, int line, int column) {
    return token__create(TOKEN_ERROR, lexeme, line, column);
}

Token *token__create_identifier(String *lexeme, int line, int column) {
    return token__create(TOKEN_IDENTIFIER, lexeme, line, column);
}

Token *token__create_integer(String *lexeme, int line, int column, int value) {
    Token *self = token__create(TOKEN_INTEGER, lexeme, line, column);
    self->integer.value = value;
    return self;
}

Token *token__create_keyword(String *lexeme, int line, int column) {
    return token__create(TOKEN_KEYWORD, lexeme, line, column);
}

Token *token__create_other(String *lexeme, int line, int column) {
    return token__create(TOKEN_OTHER, lexeme, line, column);
}

Token *token__create_space(String *lexeme, int line, int column, int count) {
    Token *self = token__create(TOKEN_SPACE, lexeme, line, column);
    self->space.count = count;
    return self;
}

Token *token__create_string(String *lexeme, int line, int column, String *value) {
    Token *self = token__create(TOKEN_STRING, lexeme, line, column);
    self->string.value = value;
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
