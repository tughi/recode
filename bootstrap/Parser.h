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

typedef enum TypeKind {
    ARRAY,
    PROCEDURE,
    REFERENCE,
    SIMPLE,
    TUPLE,
} TypeKind;

typedef struct Type {
    TypeKind kind;

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

typedef enum ExpressionKind {
        ARRAY_ITEM,
        BINARY,
        CALL,
        LITERAL,
        MEMBER,
        UNARY,
        VARIABLE,
} ExpressionKind;

typedef struct Expression {
    ExpressionKind kind;

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

typedef enum StatementKind {
    ASSIGNMENT,
    BLOCK,
    BREAK,
    EXPRESSION,
    IF,
    LOOP,
    PROCEDURE_DEFINITION,
    RETURN,
    SKIP,
    STRUCT_DEFINITION,
    VARIABLE_DECLARATION,
} StatementKind;

typedef struct Statement {
    StatementKind kind;

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
