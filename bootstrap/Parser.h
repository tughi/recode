#ifndef __recode__parser_h__
#define __recode__parser_h__

#include "Token.h"

struct Expression {
    enum Kind {
        BINARY,
        LITERAL,
        UNARY,
        VARIABLE,
    } kind;

    union {
        struct {
            Token *operator_token;
            Expression *left_expression;
            Expression *right_expression;
        } binary;
        struct {
            Token *value;
        } literal;
        struct {
            Token *operator_token;
            Expression *expression;
        } unary;
        struct {
            Token *name;
        } variable;
    };
};

struct Statement {
    enum Kind {
        DECLARATION,
        ERROR,
        ASSIGNMENT,
        STRUCT_DECLARATION,
    } kind;

    union {
        struct {
            const char *parser_file;
            int parser_line;
            const char *expected_token;
            Token *found_token;
        } error;
        struct {
            Token *name;
        } struct_declaration;
    };
};

Statement *parse(Token *first);

#endif
