/* Copyright (C) 2024 Stefan Selariu */

#ifndef __PARSED_SOURCE_H__
#define __PARSED_SOURCE_H__

#include "Token.h"

typedef enum Parsed_Expression_Kind {
    PARSED_EXPRESSION_KIND__ADD,
    PARSED_EXPRESSION_KIND__ADDRESS_OF,
    PARSED_EXPRESSION_KIND__ARRAY_ACCESS,
    PARSED_EXPRESSION_KIND__BOOL,
    PARSED_EXPRESSION_KIND__CALL,
    PARSED_EXPRESSION_KIND__CAST,
    PARSED_EXPRESSION_KIND__CHARACTER,
    PARSED_EXPRESSION_KIND__DEREFERENCE,
    PARSED_EXPRESSION_KIND__DIVIDE,
    PARSED_EXPRESSION_KIND__EQUALS,
    PARSED_EXPRESSION_KIND__GREATER,
    PARSED_EXPRESSION_KIND__GREATER_OR_EQUALS,
    PARSED_EXPRESSION_KIND__GROUP,
    PARSED_EXPRESSION_KIND__INTEGER,
    PARSED_EXPRESSION_KIND__LESS,
    PARSED_EXPRESSION_KIND__LESS_OR_EQUALS,
    PARSED_EXPRESSION_KIND__LOGIC_AND,
    PARSED_EXPRESSION_KIND__LOGIC_OR,
    PARSED_EXPRESSION_KIND__MEMBER_ACCESS,
    PARSED_EXPRESSION_KIND__MINUS,
    PARSED_EXPRESSION_KIND__MODULO,
    PARSED_EXPRESSION_KIND__MULTIPLY,
    PARSED_EXPRESSION_KIND__NOT,
    PARSED_EXPRESSION_KIND__NOT_EQUALS,
    PARSED_EXPRESSION_KIND__NULL,
    PARSED_EXPRESSION_KIND__SIZEOF,
    PARSED_EXPRESSION_KIND__STRING,
    PARSED_EXPRESSION_KIND__SUBSTRACT,
    PARSED_EXPRESSION_KIND__SYMBOL
} Parsed_Expression_Kind;

typedef struct Parsed_Expression {
    Parsed_Expression_Kind kind;
    Source_Location *location;
} Parsed_Expression;

typedef enum Parsed_Type_Kind {
    PARSED_TYPE_KIND__ARRAY,
    PARSED_TYPE_KIND__FUNCTION,
    PARSED_TYPE_KIND__NAMED,
    PARSED_TYPE_KIND__POINTER
} Parsed_Type_Kind;

typedef struct Parsed_Type {
    Parsed_Type_Kind kind;
    Source_Location *location;
} Parsed_Type;

Parsed_Type *Parsed_Type__create_kind(Parsed_Type_Kind kind, size_t kind_size, Source_Location *location);

typedef struct Parsed_Array_Type {
    Parsed_Type super;
    Parsed_Type *item_type;
    bool is_checked;
    Parsed_Expression *size_expression;
} Parsed_Array_Type;

Parsed_Array_Type *Parsed_Array_Type__create(Source_Location *location, Parsed_Type *item_type, bool is_checked, Parsed_Expression *size_expression);

typedef struct Parsed_Function_Parameter {
    Token *name;
    Parsed_Type *type;
    struct Parsed_Function_Parameter *next_parameter;
} Parsed_Function_Parameter;

Parsed_Function_Parameter *Parsed_Function_Parameter__create(Token *name, Parsed_Type *type);

typedef struct Parsed_Function_Type {
    Parsed_Type super;
    Parsed_Function_Parameter *first_parameter;
    Parsed_Type *return_type;
} Parsed_Function_Type;

Parsed_Type *Parsed_Function_Type__create(Source_Location *location, Parsed_Function_Parameter *first_parameter, Parsed_Type *return_type);

typedef struct Parsed_Named_Type {
    Parsed_Type super;
    String *name;
} Parsed_Named_Type;

Parsed_Type *Parsed_Named_Type__create(Token *name);

typedef struct Parsed_Pointer_Type {
    Parsed_Type super;
    Parsed_Type *other_type;
} Parsed_Pointer_Type;

Parsed_Type *Parsed_Pointer_Type__create(Parsed_Type *other_type);

Parsed_Expression *Parsed_Expression__create_kind(Parsed_Expression_Kind kind, size_t kind_size, Source_Location *location);

typedef struct Parsed_Binary_Expression {
    Parsed_Expression super;
    Parsed_Expression *left_expression;
    Parsed_Expression *right_expression;
} Parsed_Binary_Expression;

Parsed_Binary_Expression *Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind kind, Parsed_Expression *left_expression, Parsed_Expression *right_expression);

typedef struct Parsed_Unary_Expression {
    Parsed_Expression super;
    Parsed_Expression *other_expression;
} Parsed_Unary_Expression;

Parsed_Unary_Expression *Parsed_Unary_Expression__create_kind(Parsed_Expression_Kind kind, size_t kind_size, Source_Location *location, Parsed_Expression *other_expression);

typedef struct Parsed_Literal_Expression {
    Parsed_Expression super;
    Token *literal;
} Parsed_Literal_Expression;

Parsed_Literal_Expression *Parsed_Literal_Expression__create_kind(Parsed_Expression_Kind kind, size_t kind_size, Token *literal);

typedef struct Parsed_Add_Expression {
    Parsed_Binary_Expression super;
} Parsed_Add_Expression;

Parsed_Add_Expression *Parsed_Add_Expression__create(Parsed_Expression *left_expression, Parsed_Expression *right_expression);

typedef struct Parsed_Address_Of_Expression {
    Parsed_Unary_Expression super;
} Parsed_Address_Of_Expression;

Parsed_Address_Of_Expression *Parsed_Address_Of_Expression__create(Source_Location *location, Parsed_Expression *other_expression);

typedef struct Parsed_Array_Access_Expression {
    Parsed_Expression super;
    Parsed_Expression *array_expression;
    Parsed_Expression *index_expression;
} Parsed_Array_Access_Expression;

Parsed_Array_Access_Expression *Parsed_Array_Access_Expression__create(Parsed_Expression *array_expression, Parsed_Expression *index_expression);

typedef struct Parsed_Bool_Expression {
    Parsed_Literal_Expression super;
    bool value;
} Parsed_Bool_Expression;

Parsed_Bool_Expression *Parsed_Bool_Expression__create(Token *literal, bool value);

typedef struct Parsed_Call_Argument {
    Parsed_Expression *expression;
    struct Parsed_Call_Argument *next_argument;
} Parsed_Call_Argument;

Parsed_Call_Argument *Parsed_Call_Argument__create(Parsed_Expression *expression);

typedef struct Parsed_Call_Expression {
    Parsed_Expression super;
    Parsed_Expression *callee_expression;
    Parsed_Call_Argument *first_argument;
} Parsed_Call_Expression;

Parsed_Call_Expression *Parsed_Call_Expression__create(Parsed_Expression *callee_expression, Parsed_Call_Argument *first_argument);

typedef struct Parsed_Cast_Expression {
    Parsed_Unary_Expression super;
    Parsed_Type *type;
} Parsed_Cast_Expression;

Parsed_Cast_Expression *Parsed_Cast_Expression__create(Source_Location *location, Parsed_Expression *other_expression, Parsed_Type *type);

typedef struct Parsed_Character_Expression {
    Parsed_Literal_Expression super;
    char value;
} Parsed_Character_Expression;

Parsed_Character_Expression *Parsed_Character_Expression__create(Character_Token *literal);

typedef struct Parsed_Dereference_Expression {
    Parsed_Unary_Expression super;
} Parsed_Dereference_Expression;

Parsed_Dereference_Expression *Parsed_Dereference_Expression__create(Source_Location *location, Parsed_Expression *other_expression);

typedef struct Parsed_Divide_Expression {
    Parsed_Binary_Expression super;
} Parsed_Divide_Expression;

Parsed_Divide_Expression *Parsed_Divide_Expression__create(Parsed_Expression *left_expression, Parsed_Expression *right_expression);

typedef struct Parsed_Equals_Expression {
    Parsed_Binary_Expression super;
} Parsed_Equals_Expression;

Parsed_Equals_Expression *Parsed_Equals_Expression__create(Parsed_Expression *left_expression, Parsed_Expression *right_expression);

typedef struct Parsed_Greater_Expression {
    Parsed_Binary_Expression super;
} Parsed_Greater_Expression;

Parsed_Greater_Expression *Parsed_Greater_Expression__create(Parsed_Expression *left_expression, Parsed_Expression *right_expression);

typedef struct Parsed_Greater_Or_Equals_Expression {
    Parsed_Binary_Expression super;
} Parsed_Greater_Or_Equals_Expression;

Parsed_Greater_Or_Equals_Expression *Parsed_Greater_Or_Equals_Expression__create(Parsed_Expression *left_expression, Parsed_Expression *right_expression);

typedef struct Parsed_Group_Expression {
    Parsed_Expression super;
    Parsed_Expression *other_expression;
} Parsed_Group_Expression;

Parsed_Group_Expression *Parsed_Group_Expression__create(Source_Location *location, Parsed_Expression *other_expression);

typedef struct Parsed_Integer_Expression {
    Parsed_Literal_Expression super;
    uint64_t value;
    Parsed_Named_Type *type;
} Parsed_Integer_Expression;

Parsed_Integer_Expression *Parsed_Integer_Expression__create(Integer_Token *literal, Parsed_Named_Type *type);

typedef struct Parsed_Less_Expression {
    Parsed_Binary_Expression super;
} Parsed_Less_Expression;

Parsed_Less_Expression *Parsed_Less_Expression__create(Parsed_Expression *left_expression, Parsed_Expression *right_expression);

typedef struct Parsed_Less_Or_Equals_Expression {
    Parsed_Binary_Expression super;
} Parsed_Less_Or_Equals_Expression;

Parsed_Less_Or_Equals_Expression *Parsed_Less_Or_Equals_Expression__create(Parsed_Expression *left_expression, Parsed_Expression *right_expression);

typedef struct Parsed_Logic_And_Expression {
    Parsed_Binary_Expression super;
} Parsed_Logic_And_Expression;

Parsed_Logic_And_Expression *Parsed_Logic_And_Expression__create(Parsed_Expression *left_expression, Parsed_Expression *right_expression);

typedef struct Parsed_Logic_Or_Expression {
    Parsed_Binary_Expression super;
} Parsed_Logic_Or_Expression;

Parsed_Logic_Or_Expression *Parsed_Logic_Or_Expression__create(Parsed_Expression *left_expression, Parsed_Expression *right_expression);

typedef struct Parsed_Member_Access_Expression {
    Parsed_Expression super;
    Parsed_Expression *object_expression;
    Token *member_name;
} Parsed_Member_Access_Expression;

Parsed_Member_Access_Expression *Parsed_Member_Access_Expression__create(Parsed_Expression *object_expression, Token *member_name);

typedef struct Parsed_Minus_Expression {
    Parsed_Unary_Expression super;
} Parsed_Minus_Expression;

Parsed_Minus_Expression *Parsed_Minus_Expression__create(Source_Location *location, Parsed_Expression *other_expression);

typedef struct Parsed_Modulo_Expression {
    Parsed_Binary_Expression super;
} Parsed_Modulo_Expression;

Parsed_Modulo_Expression *Parsed_Modulo_Expression__create(Parsed_Expression *left_expression, Parsed_Expression *right_expression);

typedef struct Parsed_Multiply_Expression {
    Parsed_Binary_Expression super;
} Parsed_Multiply_Expression;

Parsed_Multiply_Expression *Parsed_Multiply_Expression__create(Parsed_Expression *left_expression, Parsed_Expression *right_expression);

typedef struct Parsed_Not_Expression {
    Parsed_Unary_Expression super;
} Parsed_Not_Expression;

Parsed_Not_Expression *Parsed_Not_Expression__create(Source_Location *location, Parsed_Expression *other_expression);

typedef struct Parsed_Not_Equals_Expression {
    Parsed_Binary_Expression super;
} Parsed_Not_Equals_Expression;

Parsed_Not_Equals_Expression *Parsed_Not_Equals_Expression__create(Parsed_Expression *left_expression, Parsed_Expression *right_expression);

typedef struct Parsed_Null_Expression {
    Parsed_Literal_Expression super;
} Parsed_Null_Expression;

Parsed_Null_Expression *Parsed_Null_Expression__create(Token *literal);

typedef struct Parsed_Sizeof_Expression {
    Parsed_Expression super;
    Parsed_Type *type;
} Parsed_Sizeof_Expression;

Parsed_Sizeof_Expression *Parsed_Sizeof_Expression__create(Source_Location *location, Parsed_Type *type);

typedef struct Parsed_String_Expression {
    Parsed_Literal_Expression super;
    String *value;
} Parsed_String_Expression;

Parsed_String_Expression *Parsed_String_Expression__create(String_Token *literal);

typedef struct Parsed_Substract_Expression {
    Parsed_Binary_Expression super;
} Parsed_Substract_Expression;

Parsed_Substract_Expression *Parsed_Substract_Expression__create(Parsed_Expression *left_expression, Parsed_Expression *right_expression);

typedef struct Parsed_Symbol_Expression {
    Parsed_Expression super;
    Token *name;
} Parsed_Symbol_Expression;

Parsed_Symbol_Expression *Parsed_Symbol_Expression__create(Token *name);

typedef enum Parsed_Statement_Kind {
    PARSED_STATEMENT_KIND__ASSIGNMENT,
    PARSED_STATEMENT_KIND__BLOCK,
    PARSED_STATEMENT_KIND__BREAK,
    PARSED_STATEMENT_KIND__EXPRESSION,
    PARSED_STATEMENT_KIND__EXTERNAL_TYPE,
    PARSED_STATEMENT_KIND__FUNCTION,
    PARSED_STATEMENT_KIND__IF,
    PARSED_STATEMENT_KIND__LOOP,
    PARSED_STATEMENT_KIND__RETURN,
    PARSED_STATEMENT_KIND__STRUCT,
    PARSED_STATEMENT_KIND__VARIABLE,
    PARSED_STATEMENT_KIND__WHILE
} Parsed_Statement_Kind;

typedef struct Parsed_Statement {
    Parsed_Statement_Kind kind;
    Source_Location *location;
    struct Parsed_Statement *next_statement;
} Parsed_Statement;

Parsed_Statement *Parsed_Statement__create_kind(Parsed_Statement_Kind kind, size_t kind_size, Source_Location *location);

typedef struct Parsed_Statements {
    Parsed_Statement *first_statement;
    Parsed_Statement *last_statement;
    bool has_globals;
} Parsed_Statements;

Parsed_Statements *Parsed_Statements__create(bool has_globals);

void Parsed_Statements__append(Parsed_Statements *self, Parsed_Statement *statement);

typedef struct Parsed_Named_Statement {
    Parsed_Statement super;
    Token *name;
} Parsed_Named_Statement;

Parsed_Named_Statement *Parsed_Named_Statement__create_kind(Parsed_Statement_Kind kind, size_t kind_size, Source_Location *location, Token *name);

typedef struct Parsed_Assignment_Statement {
    Parsed_Statement super;
    Parsed_Expression *object_expression;
    Parsed_Expression *value_expression;
} Parsed_Assignment_Statement;

Parsed_Assignment_Statement *Parsed_Assignment_Statement__create(Parsed_Expression *object_expression, Parsed_Expression *value_expression);

typedef struct Parsed_Block_Statement {
    Parsed_Statement super;
    struct Parsed_Statements *statements;
} Parsed_Block_Statement;

Parsed_Block_Statement *Parsed_Block_Statement__create(Source_Location *location, struct Parsed_Statements *statements);

typedef struct Parsed_Break_Statement {
    Parsed_Statement super;
} Parsed_Break_Statement;

Parsed_Statement *Parsed_Break_Statement__create(Source_Location *location);

typedef struct Parsed_Expression_Statement {
    Parsed_Statement super;
    Parsed_Expression *expression;
} Parsed_Expression_Statement;

Parsed_Expression_Statement *Parsed_Expression_Statement__create(Parsed_Expression *expression);

typedef struct Parsed_External_Type_Statement {
    Parsed_Named_Statement super;
} Parsed_External_Type_Statement;

Parsed_External_Type_Statement *Parsed_External_Type_Statement__create(Source_Location *location, Token *name);

typedef struct Parsed_Function_Statement {
    Parsed_Named_Statement super;
    Parsed_Function_Parameter *first_parameter;
    Parsed_Type *return_type;
    struct Parsed_Statements *statements;
    bool is_external;
} Parsed_Function_Statement;

Parsed_Statement *Parsed_Function_Statement__create(Source_Location *location, Token *name, Parsed_Function_Parameter *first_parameter, Parsed_Type *resturn_type, struct Parsed_Statements *statements, bool is_external);

typedef struct Parsed_If_Statement {
    Parsed_Statement super;
    Parsed_Expression *condition_expression;
    Parsed_Statement *true_statement;
    Parsed_Statement *false_statement;
} Parsed_If_Statement;

Parsed_Statement *Parsed_If_Statement__create(Source_Location *location, Parsed_Expression *condition_expression, Parsed_Statement *true_statement, Parsed_Statement *false_statement);

typedef struct Parsed_Loop_Statement {
    Parsed_Statement super;
    Parsed_Statement *body_statement;
} Parsed_Loop_Statement;

Parsed_Statement *Parsed_Loop_Statement__create(Source_Location *location, Parsed_Statement *body_statement);

typedef struct Parsed_Return_Statement {
    Parsed_Statement super;
    Parsed_Expression *expression;
} Parsed_Return_Statement;

Parsed_Statement *Parsed_Return_Statement__create(Source_Location *location, Parsed_Expression *expression);

typedef struct Parsed_Struct_Member {
    Token *name;
    Parsed_Type *type;
    struct Parsed_Struct_Member *next_member;
} Parsed_Struct_Member;

Parsed_Struct_Member *Parsed_Struct_Member__create(Token *name, Parsed_Type *type);

typedef struct Parsed_Struct_Statement {
    Parsed_Named_Statement super;
    Parsed_Struct_Member *first_member;
} Parsed_Struct_Statement;

Parsed_Struct_Statement *Parsed_Struct_Statement__create(Source_Location *location, Token *name);

typedef struct Parsed_Variable_Statement {
    Parsed_Named_Statement super;
    Parsed_Type *type;
    Parsed_Expression *expression;
    bool is_external;
} Parsed_Variable_Statement;

Parsed_Variable_Statement *Parsed_Variable_Statement__create(Source_Location *location, Token *name, Parsed_Type *type, Parsed_Expression *expression, bool is_external);

typedef struct Parsed_While_Statement {
    Parsed_Statement super;
    Parsed_Expression *condition_expression;
    Parsed_Statement *body_statement;
} Parsed_While_Statement;

Parsed_Statement *Parsed_While_Statement__create(Source_Location *location, Parsed_Expression *condition_expression, Parsed_Statement *body_statement);

typedef struct Parsed_Source {
    Source *first_source;
    Parsed_Statements *statements;
} Parsed_Source;

Parsed_Source *Parsed_Source__create();

#endif
