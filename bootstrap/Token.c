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
    Token *self = token__create(TOKEN__CHARACTER, location, lexeme);
    self->character_data.value = value;
    return self;
}

Token *token__create_comment(Source_Location *location, String *lexeme) {
    return token__create(TOKEN__COMMENT, location, lexeme);
}

Token *token__create_end_of_file(Source_Location *location, String *lexeme) {
    return token__create(TOKEN__END_OF_FILE, location, lexeme);
}

Token *token__create_end_of_line(Source_Location *location, String *lexeme) {
    return token__create(TOKEN__END_OF_LINE, location, lexeme);
}

Token *token__create_error(Source_Location *location, String *lexeme) {
    return token__create(TOKEN__ERROR, location, lexeme);
}

Token *token__create_identifier(Source_Location *location, String *lexeme) {
    return token__create(TOKEN__IDENTIFIER, location, lexeme);
}

Token *token__create_integer(Source_Location *location, String *lexeme, int value) {
    Token *self = token__create(TOKEN__INTEGER, location, lexeme);
    self->integer_data.value = value;
    return self;
}

Token *token__create_keyword(Source_Location *location, String *lexeme) {
    return token__create(TOKEN__KEYWORD, location, lexeme);
}

Token *token__create_other(Source_Location *location, String *lexeme) {
    return token__create(TOKEN__OTHER, location, lexeme);
}

Token *token__create_space(Source_Location *location, String *lexeme, int count) {
    Token *self = token__create(TOKEN__SPACE, location, lexeme);
    self->space_data.count = count;
    return self;
}

Token *token__create_string(Source_Location *location, String *lexeme, String *value) {
    Token *self = token__create(TOKEN__STRING, location, lexeme);
    self->string_data.value = value;
    return self;
}

char *token__get_kind_name(Token *self) {
    switch (self->kind) {
    case TOKEN__CHARACTER:
        return "CHARACTER";
    case TOKEN__COMMENT:
        return "COMMENT";
    case TOKEN__END_OF_FILE:
        return "END_OF_FILE";
    case TOKEN__END_OF_LINE:
        return "END_OF_LINE";
    case TOKEN__ERROR:
        return "ERROR";
    case TOKEN__IDENTIFIER:
        return "IDENTIFIER";
    case TOKEN__INTEGER:
        return "INTEGER";
    case TOKEN__KEYWORD:
        return "KEYWORD";
    case TOKEN__OTHER:
        return "OTHER";
    case TOKEN__SPACE:
        return "SPACE";
    case TOKEN__STRING:
        return "STRING";
    default:
        PANIC(__FILE__, __LINE__, "Unsupported token kind: %d", self->kind);
    }
}

void token__join(Token *self, Token *other) {
    string__append_string(self->lexeme, other->lexeme);
    other->lexeme = string__create("");
}
