#ifndef __recode__parser_h__
#define __recode__parser_h__

#include "Token.h"

struct Type;
struct Expression;

typedef struct Member {
    Token *name;
    struct Type *type;
    struct Expression *default_value;
    struct Member *next;
} Member;

typedef struct Type {
    enum {
        TYPE_ARRAY,
        TYPE_PROCEDURE,
        TYPE_REFERENCE,
        TYPE_SIMPLE,
        TYPE_TUPLE,
    } kind;

    union {
        struct {
            struct Type *item_type;
        } array;
        struct {
            Member *first_parameter;
            struct Type *return_type;
        } procedure;
        struct {
            struct Type *type;
        } reference;
        struct {
            Token *name;
        } simple;
        struct {
            Member *first_member;
        } tuple;
    };
} Type;

typedef struct Argument {
    Token *name;
    struct Expression *value;
    struct Argument *next;
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
            Argument *first_argument;
        } call;
        struct {
            struct Expression *expression;
            Token *type;
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
        STATEMENT_IF,
        STATEMENT_LOOP,
        STATEMENT_PROCEDURE_DEFINITION,
        STATEMENT_RETURN,
        STATEMENT_SKIP,
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
            Expression *condition;
            struct Statement *true_block;
            struct Statement *false_block;
        } if_;
        struct {
            struct Statement *block;
        } loop;
        struct {
            Expression *name;
            Member *first_parameter;
            Type *return_type;
            struct Statement *first_statement;
        } procedure_definition;
        Expression *return_expression;
        struct {
            Expression *name;
            Token *base;
            Member *first_member;
        } struct_definition;
        struct {
            Expression *name;
            Type *type;
            Expression *value;
        } variable_declaration;
    };

    struct Statement *next;
} Statement;

Statement *parse(Token *first);

#endif
