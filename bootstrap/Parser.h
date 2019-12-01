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
        ASSIGNMENT,
        STRUCT_DECLARATION,
    } kind;

    union {
        struct {
             Token *name;
        } struct_declaration;
    };
};

Statement *parse(Token *first);

#endif
