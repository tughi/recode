#ifndef __recode__parser_h__
#define __recode__parser_h__

#include "List.h"
#include "Token.h"

struct Type;
struct Expression;

typedef struct {
    int is_reference;
    Token *name;
    struct Type *type;
#ifdef ENABLE__MEMBER_DEFAULT_VALUE
    struct Expression *default_value;
#endif
} Member, Parameter;

typedef struct Type {
    enum {
        TYPE_ARRAY,
        TYPE_FUNCTION,
        TYPE_POINTER,
        TYPE_SIMPLE,
        TYPE_TUPLE,
    } kind;

    Source_Location *location;

    union {
        struct {
            struct Type *item_type;
        } array_data;
        struct {
            List *parameters;
            struct Type *return_type;
        } function_data;
        struct {
            struct Type *type;
        } pointer_data;
        struct {
            Token *name;
        } simple_data;
        struct {
            List *members;
        } tuple_data;
    };
} Type;

char *type__get_kind_name(Type *self);

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
        EXPRESSION_SIZE_OF,
        EXPRESSION_UNARY,
        EXPRESSION_VARIABLE,
    } kind;

    Source_Location *location;

    union {
        struct {
            struct Expression *array;
            struct Expression *index;
        } array_item_data;
        struct {
            Token *operator_token;
            struct Expression *left_expression;
            struct Expression *right_expression;
        } binary_data;
        struct {
            struct Expression *callee;
            List *arguments;
        } call_data;
        struct {
            struct Expression *expression;
            Type *type;
        } cast_data;
        struct {
            Token *value;
        } literal_data;
        struct {
            struct Expression *object;
            Token *name;
        } member_data;
        struct {
            Type *type;
        } size_of_data;
        struct {
            Token *operator_token;
            struct Expression *expression;
        } unary_data;
        struct {
            Token *name;
        } variable_data;
    };
} Expression;

char *expression__get_kind_name(Expression *self);

typedef struct Statement {
    enum {
        STATEMENT_ASSIGNMENT,
        STATEMENT_BLOCK,
        STATEMENT_BREAK,
        STATEMENT_EXPRESSION,
        STATEMENT_FUNCTION,
        STATEMENT_IF,
        STATEMENT_LOOP,
        STATEMENT_RETURN,
        STATEMENT_SKIP,
        STATEMENT_STRUCT,
        STATEMENT_VARIABLE,
    } kind;

    Source_Location *location;

    union {
        struct {
            Expression *destination;
            Token *operator_token;
            Expression *value;
        } assignment_data;
        struct {
            List *statements;
        } block_data;
        struct {
            Expression *expression;
        } expression_data;
        struct {
            Token *name;
            Type *return_type;
            List *parameters;
            List *statements;
            int is_declaration;
        } function_data;
        struct {
            Expression *condition;
            struct Statement *true_block;
            struct Statement *false_block;
        } if_data;
        struct {
            struct Statement *block;
        } loop_data;
        struct {
            Expression *expression;
        } return_data;
        struct {
            Token *name;
            Token *base;
            List *members;
            int is_declaration;
        } struct_data;
        struct {
            Token *name;
            Type *type;
            Expression *value;
            int is_external;
        } variable_data;
    };
} Statement;

char *statement__get_kind_name(Statement *self);

List *parse(List *tokens);

#endif
