#ifndef __recode__parser_h__
#define __recode__parser_h__

#include "List.h"
#include "Token.h"

typedef struct {
    int line;
    int column;
} Location;

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

    Location location;
    union {
        struct {
            struct Type *item_type;
        } array_type_data;
        struct {
            List *parameters;
            struct Type *return_type;
        } function_type_data;
        struct {
            struct Type *type;
        } pointer_type_data;
        struct {
            Token *name;
        } simple_type_data;
        struct {
            List *members;
        } tuple_type_data;
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
        EXPRESSION_SIZE_OF,
        EXPRESSION_UNARY,
        EXPRESSION_VARIABLE,
    } kind;

    Location location;
    union {
        struct {
            struct Expression *array;
            struct Expression *index;
        } array_item_expression_data;
        struct {
            Token *operator_token;
            struct Expression *left_expression;
            struct Expression *right_expression;
        } binary_expression_data;
        struct {
            struct Expression *callee;
            List *arguments;
        } call_expression_data;
        struct {
            struct Expression *expression;
            Type *type;
        } cast_expression_data;
        struct {
            Token *value;
        } literal_expression_data;
        struct {
            struct Expression *object;
            Token *name;
        } member_expression_data;
        struct {
            Type *type;
        } size_of_expression_data;
        struct {
            Token *operator_token;
            struct Expression *expression;
        } unary_expression_data;
        struct {
            Token *name;
        } variable_expression_data;
    };
} Expression;

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

    union {
        struct {
            Expression *destination;
            Token *operator_token;
            Expression *value;
        } assignment_statement_data;
        struct {
            List *statements;
        } block_statement_data;
        struct {
            Expression *expression;
        } expression_statement_data;
        struct {
            Expression *name;
            Type *return_type;
            List *parameters;
            List *statements;
            int is_declaration;
        } function_statement_data;
        struct {
            Expression *condition;
            struct Statement *true_block;
            struct Statement *false_block;
        } if_statement_data;
        struct {
            struct Statement *block;
        } loop_statement_data;
        struct {
            Expression *expression;
        } return_statement_data;
        struct {
            Expression *name;
            Token *base;
            List *members;
            int is_declaration;
        } struct_statement_data;
        struct {
            Expression *name;
            Type *type;
            Expression *value;
            int is_external;
        } variable_statement_data;
    };
} Statement;

List *parse(List *tokens);

#endif
