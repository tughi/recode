#ifndef __recode__token_h__
#define __recode__token_h__

struct Token {
    enum Type {
        CHAR,
        END_OF_FILE,
        END_OF_LINE,
        ENUM,
        ERROR,
        IDENTIFIER,
        INTEGER,
        OTHER,
        STRING,
        STRUCT,
    };

    Type type;

    const char *lexeme;
    int line;
    int column;

    union {
        char character;
        int integer;
        const char *string;
    };

    Token(Type type, const char *lexeme, int line, int column);

    Token(char character, const char *lexeme, int line, int column);

    Token(int integer, const char *lexeme, int line, int column);

    Token(const char *string, const char *lexeme, int line, int column);
};

#endif
