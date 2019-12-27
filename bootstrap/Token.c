#include "Token.h"

#include <stdlib.h>

void token__join_next(Token *self) {
    if (self->next) {
        string__append_string(self->lexeme, self->next->lexeme);
        self->next = self->next->next;
    }
}

static Token *token__create(int kind, String *lexeme, int line, int column) {
    Token *self = (Token *)malloc(sizeof(Token));
    self->kind = kind;
    self->lexeme = lexeme;
    self->line = line;
    self->column = column;
    self->next = NULL;
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
