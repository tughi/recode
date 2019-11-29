#ifndef __recode__parser_h__
#define __recode__parser_h__

#include "Token.h"

struct Expression {
    enum Type {
        BINARY,
        LITERAL,
        UNARY,
        VARIABLE,
    };

    Type type;

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

Expression *parse(Token *first);

#endif
