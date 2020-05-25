#ifndef __recode__ast_h__
#define __recode__ast_h__

#include "List.h"
#include "Token.h"

struct Composite_Type;
struct Expression;

typedef struct {
    int is_reference;
    Token *name;
    struct Composite_Type *type;
    struct Expression *default_value;
} Member, Parameter;

typedef List Member_List;
typedef List Parameter_List;

typedef struct Composite_Type {
    enum {
        COMPOSITE_TYPE__ARRAY,
        COMPOSITE_TYPE__FUNCTION,
        COMPOSITE_TYPE__POINTER,
        COMPOSITE_TYPE__NAMED,
    } kind;

    Source_Location *location;

    union {
        struct {
            struct Composite_Type *item_type;
        } array_data;
        struct {
            Parameter_List *parameters;
            struct Composite_Type *return_type;
        } function_data;
        struct {
            struct Composite_Type *type;
        } pointer_data;
        struct {
            Token *name;
        } named_data;
    };
} Composite_Type;

char *composite_type__get_kind_name(Composite_Type *self);

typedef struct Argument {
    Token *name;
    struct Expression *value;
} Argument;

typedef List Argument_List;

typedef struct Expression {
    enum {
        EXPRESSION__ARRAY_ITEM,
        EXPRESSION__BINARY,
        EXPRESSION__CALL,
        EXPRESSION__CAST,
        EXPRESSION__LITERAL,
        EXPRESSION__MEMBER,
        EXPRESSION__SIZE_OF,
        EXPRESSION__UNARY,
        EXPRESSION__VARIABLE,
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
            Argument_List *arguments;
        } call_data;
        struct {
            struct Expression *expression;
            Composite_Type *type;
        } cast_data;
        struct {
            Token *value;
        } literal_data;
        struct {
            struct Expression *object;
            Token *name;
        } member_data;
        struct {
            Composite_Type *type;
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

typedef List Statement_List;

typedef struct Statement {
    enum {
        STATEMENT__ASSIGNMENT,
        STATEMENT__BLOCK,
        STATEMENT__BREAK,
        STATEMENT__EXPRESSION,
        STATEMENT__FUNCTION,
        STATEMENT__IF,
        STATEMENT__LOOP,
        STATEMENT__RETURN,
        STATEMENT__SKIP,
        STATEMENT__STRUCT,
        STATEMENT__VARIABLE,
    } kind;

    Source_Location *location;

    union {
        struct {
            Expression *destination;
            Token *operator_token;
            Expression *value;
        } assignment_data;
        struct {
            Statement_List *statements;
        } block_data;
        struct {
            Expression *expression;
        } expression_data;
        struct {
            Token *name;
            Composite_Type *return_type;
            Parameter_List *parameters;
            Statement_List *statements;
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
            Member_List *members;
            int is_declaration;
        } struct_data;
        struct {
            Token *name;
            Composite_Type *type;
            Expression *value;
            int is_external;
        } variable_data;
    };
} Statement;

char *statement__get_kind_name(Statement *self);

typedef struct Named_Type {
    enum {
        NAMED_TYPE__BOOLEAN,
        NAMED_TYPE__INTEGER,
        NAMED_TYPE__CUSTOM,
    } kind;

    String *name;
    Source_Location *location;

    union {
        struct {
            Statement *statement;
        } custom_data;
    };
} Named_Type;

Named_Type *named_type__create(int kind, String *name, Source_Location *location);
char *named_type__get_kind_name(Named_Type *self);

typedef List Named_Type_List;

void named_type_list__add(Named_Type_List *self, Named_Type *item);
Named_Type *named_type_list__find(Named_Type_List *self, String *name);

typedef struct Compilation_Unit {
    Named_Type_List *named_types;
    Statement_List *statements;
} Compilation_Unit;

Compilation_Unit *compilation_unit__create();

#endif
