#ifndef __recode__ast_h__
#define __recode__ast_h__

#include "List.h"
#include "Token.h"

struct Type;
struct Expression;

typedef struct {
    int is_reference;
    Token *name;
    struct Type *type;
    struct Expression *default_value;
} Member, Parameter;

typedef List Member_List;
typedef List Parameter_List;

typedef struct Statement Statement;

typedef struct Type {
    enum {
        TYPE__ARRAY,
        TYPE__BOOLEAN,
        TYPE__FUNCTION,
        TYPE__INT,
        TYPE__INT8,
        TYPE__INT16,
        TYPE__INT32,
        TYPE__INT64,
        TYPE__POINTER,
        TYPE__NAMED,
        TYPE__NOTHING,
        TYPE__STRUCT,
    } kind;

    Source_Location *location;
    String *name;

    union {
        struct {
            struct Type *item_type;
            int size;
        } array_data;
        struct {
            Parameter_List *parameters;
            struct Type *return_type;
        } function_data;
        struct {
            struct Type *type;
        } pointer_data;
        struct {
            Token *name;
        } named_data;
        struct {
            Statement *statement;
        } struct_data;
    };
} Type;

Type *type__create_array(Source_Location *location, Type *item_type, int size);
Type *type__create_function(Source_Location *location, Type *return_type, List *parameters);
Type *type__create_named(Source_Location *location, Token *name);
Type *type__create_pointer(Source_Location *location, Type *type);
Type *type__create_struct(Source_Location *location, Statement *statement);
void type__convert(Type *self, Type *other);
char *type__get_kind_name(Type *self);
int type__equals(Type *self, Type *other);

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
        EXPRESSION__POINTED_VALUE,
        EXPRESSION__POINTER_TO,
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
            struct Expression *expression;
        } pointed_value_data;
        struct {
            struct Expression *expression;
        } pointer_to_data;
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
            Type *return_type;
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
            Type *type;
            Expression *value;
            int is_external;
        } variable_data;
    };
} Statement;

char *statement__get_kind_name(Statement *self);

typedef List Named_Functions;

Named_Functions *named_functions__create();
void named_functions__add(Named_Functions *self, String *name, Statement *statement);
Statement *named_functions__get(Named_Functions *self, String *name, Argument_List *arguments);

typedef List Named_Types;

Named_Types *named_types__create();
void named_types__add(Named_Types *self, String *name, Type *type);
Type *named_types__get(Named_Types *self, String *name);

typedef struct Compilation_Unit {
    Named_Functions *named_functions;
    Named_Types *named_types;
    Statement_List *statements;
} Compilation_Unit;

Compilation_Unit *compilation_unit__create(Named_Functions *named_functions, Named_Types *named_types, Statement_List *statements);

#endif
