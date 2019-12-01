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
        TAB,
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
            String *value;
        } string;
    };

    Token *next = nullptr;

    Token(Kind type, String *lexeme, int line, int column);

    Token(char value, String *lexeme, int line, int column);

    Token(int value, String *lexeme, int line, int column);

    Token(String *value, String *lexeme, int line, int column);

    void join_next();
};

#endif
