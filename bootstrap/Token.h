#ifndef __recode__token_h__
#define __recode__token_h__

#include "String.h"

struct Token {
    enum Kind {
        CHARACTER,
        COMMENT,
        END_OF_FILE,
        END_OF_LINE,
        ERROR,
        IDENTIFIER,
        INTEGER,
        KEYWORD,
        OTHER,
        SPACE,
        STRING,
    };

    Kind type;

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

    Token *next = nullptr;

    void join_next();
};

Token *create_character(String *lexeme, int line, int column, char value);
Token *create_comment(String *lexeme, int line, int column);
Token *create_end_of_file(String *lexeme, int line, int column);
Token *create_end_of_line(String *lexeme, int line, int column);
Token *create_error(String *lexeme, int line, int column);
Token *create_identifier(String *lexeme, int line, int column);
Token *create_integer(String *lexeme, int line, int column, int value);
Token *create_keyword(String *lexeme, int line, int column);
Token *create_other(String *lexeme, int line, int column);
Token *create_space(String *lexeme, int line, int column, int count);
Token *create_string(String *lexeme, int line, int column, String *value);

#endif
