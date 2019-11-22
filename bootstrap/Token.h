#ifndef __recode__token_h__
#define __recode__token_h__

#include <string>

struct Token {
    enum Type {
        END_OF_FILE,
        END_OF_LINE,
        ENUM,
        IDENTIFIER,
        INTEGER,
        OTHER,
        STRUCT,
    };

    Type type;

    std::string lexeme;
    int line;
    int column;

    union {
        int integer;
    };

    Token(Type type, std::string lexeme, int line, int column);

    Token(int integer, std::string lexeme, int line, int column);
};

#endif
