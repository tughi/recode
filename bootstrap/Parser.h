#ifndef __recode__parser_h__
#define __recode__parser_h__

#include "List.h"
#include "Token.h"

struct Type;
struct Expression;

typedef struct {
    Token *name;
    struct Type *type;
    struct Expression *default_value;
} Member, Parameter;

typedef struct Type {
    enum {
        TYPE_ARRAY,
        TYPE_FUNCTION,
        TYPE_POINTER,
        TYPE_SIMPLE,
        TYPE_TUPLE,
    } kind;

    union {
        struct {
            struct Type *item_type;
        } array;
        struct {
            List *parameters;
            struct Type *return_type;
        } function;
        struct {
            struct Type *type;
        } pointer;
        struct {
            Token *name;
        } simple;
        struct {
            List *members;
        } tuple;
    };
} Type;

typedef struct Argument {
    Token *name;
    struct Expression *value;
} Argument;

typedef struct Expression {
    enum {
        EXPRESSION_ARRAY_ITEM,
        EXPRESSION_BINARY,
        EXPRESSION_CALL,
        EXPRESSION_CAST,
        EXPRESSION_LITERAL,
        EXPRESSION_MEMBER,
        EXPRESSION_UNARY,
        EXPRESSION_VARIABLE,
    } kind;

    union {
        struct {
            struct Expression *array;
            struct Expression *index;
        } array_item;
        struct {
            Token *operator_token;
            struct Expression *left_expression;
            struct Expression *right_expression;
        } binary;
        struct {
            struct Expression *callee;
            List *arguments;
        } call;
        struct {
            struct Expression *expression;
            Type *type;
        } cast;
        struct {
            Token *value;
        } literal;
        struct {
            struct Expression *object;
            Token *name;
        } member;
        struct {
            Token *operator_token;
            struct Expression *expression;
        } unary;
        struct {
            Token *name;
        } variable;
    };
} Expression;

typedef struct Statement {
    enum {
        STATEMENT_ASSIGNMENT,
        STATEMENT_BLOCK,
        STATEMENT_BREAK,
        STATEMENT_EXPRESSION,
        STATEMENT_FUNCTION_DECLARATION,
        STATEMENT_FUNCTION_DEFINITION,
        STATEMENT_IF,
        STATEMENT_LOOP,
        STATEMENT_RETURN,
        STATEMENT_SKIP,
        STATEMENT_STRUCT_DECLARATION,
        STATEMENT_STRUCT_DEFINITION,
        STATEMENT_VARIABLE_DECLARATION,
    } kind;

    union {
        struct {
            Expression *destination;
            Token *operator_token;
            Expression *value;
        } assignment;
        struct {
            struct Statement *first_statement;
        } block;
        Expression *expression;
        struct {
            Expression *name;
            Type *return_type;
            List *parameters;
        } function_declaration;
        struct {
            Expression *name;
            Type *return_type;
            List *parameters;
            struct Statement *first_statement;
        } function_definition;
        struct {
            Expression *condition;
            struct Statement *true_block;
            struct Statement *false_block;
        } if_;
        struct {
            struct Statement *block;
        } loop;
        Expression *return_expression;
        struct {
            Expression *name;
        } struct_declaration;
        struct {
            Expression *name;
            Token *base;
            List *members;
        } struct_definition;
        struct {
            Expression *name;
            Type *type;
            Expression *value;
            int external;
        } variable_declaration;
    };

    struct Statement *next;
} Statement;

Statement *parse(List *tokens);

#endif
