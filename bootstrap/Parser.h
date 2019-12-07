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

struct Argument {
    Token *name;
    Expression *value;
    Argument *next;
};

struct Expression {
    enum Kind {
        ARRAY_ITEM,
        BINARY,
        CALL,
        LITERAL,
        MEMBER,
        UNARY,
        VARIABLE,
    } kind;

    union {
        struct {
            Expression *array;
            Expression *index;
        } array_item;
        struct {
            Token *operator_token;
            Expression *left_expression;
            Expression *right_expression;
        } binary;
        struct {
            Expression *callee;
            Argument *first_argument;
        } call;
        struct {
            Token *value;
        } literal;
        struct {
            Expression *object;
            Token *name;
        } member;
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
        ASSIGNMENT,
        BLOCK,
        EXPRESSION,
        IF,
        PROCEDURE_DEFINITION,
        RETURN,
        STRUCT_DEFINITION,
        VARIABLE_DECLARATION,
    } kind;

    union {
        struct {
            Expression *destination;
            Token *operator_token;
            Expression *value;
        } assignment;
        struct {
            Statement *first_statement;
        } block;
        Expression *expression;
        struct {
            Expression *condition;
            Statement *true_block;
            Statement *false_block;
        } if_;
        struct {
            Expression *name;
            Member *first_parameter;
            Type *return_type;
            Statement *first_statement;
        } procedure_definition;
        Expression *return_expression;
        struct {
            Expression *name;
            Member *first_member;
        } struct_definition;
        struct {
            Expression *name;
            Type *type;
            Expression *value;
        } variable_declaration;
    };

    Statement *next;
};

Statement *parse(Token *first);

#endif
