#ifndef __recode__token_h__
#define __recode__token_h__

#include "String.h"

struct Token {
    enum Type {
        CHARACTER,
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

    Type type;

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

    Token(Type type, String *lexeme, int line, int column);

    Token(char value, String *lexeme, int line, int column);

    Token(int value, String *lexeme, int line, int column);

    Token(String *value, String *lexeme, int line, int column);
};

#endif
