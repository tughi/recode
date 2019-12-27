#ifndef __recode__token_h__
#define __recode__token_h__

#include "String.h"

typedef struct Token {
    enum {
        TOKEN_CHARACTER,
        TOKEN_COMMENT,
        TOKEN_END_OF_FILE,
        TOKEN_END_OF_LINE,
        TOKEN_ERROR,
        TOKEN_IDENTIFIER,
        TOKEN_INTEGER,
        TOKEN_KEYWORD,
        TOKEN_OTHER,
        TOKEN_SPACE,
        TOKEN_STRING,
    } kind;

    String *lexeme;
    int line;
    int column;

    union {
        struct {
            char value;
        } character;
        struct {
            int value;
        } integer;
        struct {
            int count;
        } space;
        struct {
            String *value;
        } string;
    };

    struct Token *next;
} Token;

Token *token__create_character(String *lexeme, int line, int column, char value);
Token *token__create_comment(String *lexeme, int line, int column);
Token *token__create_end_of_file(String *lexeme, int line, int column);
Token *token__create_end_of_line(String *lexeme, int line, int column);
Token *token__create_error(String *lexeme, int line, int column);
Token *token__create_identifier(String *lexeme, int line, int column);
Token *token__create_integer(String *lexeme, int line, int column, int value);
Token *token__create_keyword(String *lexeme, int line, int column);
Token *token__create_other(String *lexeme, int line, int column);
Token *token__create_space(String *lexeme, int line, int column, int count);
Token *token__create_string(String *lexeme, int line, int column, String *value);

void token__join_next(Token *self);

#endif
