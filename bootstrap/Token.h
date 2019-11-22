#ifndef __recode__token_h__
#define __recode__token_h__

#include "String.h"

struct Token {
    enum Type {
        CHAR,
        END_OF_FILE,
        END_OF_LINE,
        ENUM,
        ERROR,
        IDENTIFIER,
        INTEGER,
        OPERATOR,
        STRING,
        STRUCT,
    };

    Type type;

    String *lexeme;
    int line;
    int column;

    union {
        char character;
        int integer;
        String *string;
    };

    Token(Type type, String *lexeme, int line, int column);

    Token(char character, String *lexeme, int line, int column);

    Token(int integer, String *lexeme, int line, int column);

    Token(String *string, String *lexeme, int line, int column);
};

#endif
