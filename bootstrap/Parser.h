#ifndef __recode__parser_h__
#define __recode__parser_h__

#include "Token.h"

struct Type;
struct Expression;

struct Member {
    Token *name;
    Type *type;
    Expression *default_value;
    Member *next;
};

struct Type {
    enum Kind {
        ARRAY,
        PROCEDURE,
        SIMPLE,
        TUPLE,
    } kind;

    union {
        struct {
            Type *item_type;
        } array;
        struct {
            Member *first_parameter;
            Type *return_type;
        } procedure;
        struct {
            Token *name;
        } simple;
        struct {
            Member *first_member;
        } tuple;
    };
};

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
        PROCEDURE_DECLARATION,
        RETURN,
        STRUCT_DECLARATION,
    } kind;

    union {
        struct {
            Token *name;
            Member *first_parameter;
            Type *return_type;
            Statement *first_statement;
        } procedure_declaration;
        Expression *return_expression;
        struct {
            Token *name;
            Member *first_member;
        } struct_declaration;
    };

    Statement *next;
};

Statement *parse(Token *first);

#endif
