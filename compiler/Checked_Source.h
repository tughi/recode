/* Copyright (C) 2024 Stefan Selariu */

#ifndef __CHECKED_SOURCE_H__
#define __CHECKED_SOURCE_H__

#include "Builtins.h"
#include "Source_Location.h"

typedef enum Checked_Type_Kind {
    /* Builtins */
    CHECKED_TYPE_KIND__BOOL,
    CHECKED_TYPE_KIND__I8,
    CHECKED_TYPE_KIND__I16,
    CHECKED_TYPE_KIND__I32,
    CHECKED_TYPE_KIND__I64,
    CHECKED_TYPE_KIND__ISIZE,
    CHECKED_TYPE_KIND__U16,
    CHECKED_TYPE_KIND__U32,
    CHECKED_TYPE_KIND__U64,
    CHECKED_TYPE_KIND__U8,
    CHECKED_TYPE_KIND__USIZE,
    CHECKED_TYPE_KIND__ANY,
    CHECKED_TYPE_KIND__NOTHING, /* Pseudo type */
    CHECKED_TYPE_KIND__NULL,    /* Pseudo type */
    /* Defined */
    CHECKED_TYPE_KIND__ARRAY,
    CHECKED_TYPE_KIND__EXTERNAL,
    CHECKED_TYPE_KIND__FUNCTION,
    CHECKED_TYPE_KIND__STRUCT,
    CHECKED_TYPE_KIND__TRAIT,
    /* Dynamic */
    CHECKED_TYPE_KIND__FUNCTION_POINTER,
    CHECKED_TYPE_KIND__POINTER
} Checked_Type_Kind;

typedef struct Checked_Type {
    Checked_Type_Kind kind;
    Source_Location *location;
    struct Checked_Type *next_type;
} Checked_Type;

Checked_Type *Checked_Type__create_kind(Checked_Type_Kind kind, size_t kind_size, Source_Location *location);

bool Checked_Type__is_numeric_type(Checked_Type *self);

typedef enum Checked_Expression_Kind {
    CHECKED_EXPRESSION_KIND__ADD,
    CHECKED_EXPRESSION_KIND__ADDRESS_OF,
    CHECKED_EXPRESSION_KIND__ARRAY_ACCESS,
    CHECKED_EXPRESSION_KIND__BOOL,
    CHECKED_EXPRESSION_KIND__CALL,
    CHECKED_EXPRESSION_KIND__CAST,
    CHECKED_EXPRESSION_KIND__CHARACTER,
    CHECKED_EXPRESSION_KIND__DEREFERENCE,
    CHECKED_EXPRESSION_KIND__DIVIDE,
    CHECKED_EXPRESSION_KIND__EQUALS,
    CHECKED_EXPRESSION_KIND__GREATER,
    CHECKED_EXPRESSION_KIND__GREATER_OR_EQUALS,
    CHECKED_EXPRESSION_KIND__GROUP,
    CHECKED_EXPRESSION_KIND__INTEGER,
    CHECKED_EXPRESSION_KIND__LESS,
    CHECKED_EXPRESSION_KIND__LESS_OR_EQUALS,
    CHECKED_EXPRESSION_KIND__LOGIC_AND,
    CHECKED_EXPRESSION_KIND__LOGIC_OR,
    CHECKED_EXPRESSION_KIND__MAKE_STRUCT,
    CHECKED_EXPRESSION_KIND__MEMBER_ACCESS,
    CHECKED_EXPRESSION_KIND__MINUS,
    CHECKED_EXPRESSION_KIND__MODULO,
    CHECKED_EXPRESSION_KIND__MULTIPLY,
    CHECKED_EXPRESSION_KIND__NOT,
    CHECKED_EXPRESSION_KIND__NOT_EQUALS,
    CHECKED_EXPRESSION_KIND__NULL,
    CHECKED_EXPRESSION_KIND__SIZEOF,
    CHECKED_EXPRESSION_KIND__STRING,
    CHECKED_EXPRESSION_KIND__SUBSTRACT,
    CHECKED_EXPRESSION_KIND__SYMBOL
} Checked_Expression_Kind;

typedef struct Checked_Expression {
    Checked_Expression_Kind kind;
    Source_Location *location;
    Checked_Type *type;
} Checked_Expression;

typedef struct Checked_Array_Type {
    Checked_Type super;
    Checked_Type *item_type;
    bool is_checked;
    Checked_Expression *size_expression;
} Checked_Array_Type;

Checked_Array_Type *Checked_Array_Type__create(Source_Location *location, Checked_Type *item_type, bool is_checked, Checked_Expression *size_expression);

typedef struct Checked_Named_Type {
    Checked_Type super;
    String *name;
} Checked_Named_Type;

Checked_Named_Type *Checked_Named_Type__create_kind(Checked_Type_Kind kind, size_t kind_size, Source_Location *location, String *name);

typedef struct Checked_External_Type {
    Checked_Named_Type super;
} Checked_External_Type;

Checked_External_Type *Checked_External_Type__create(Source_Location *location, String *name);

typedef struct Checked_Function_Parameter {
    Source_Location *location;
    String *label;
    String *name;
    Checked_Type *type;
    struct Checked_Function_Parameter *next_parameter;
} Checked_Function_Parameter;

Checked_Function_Parameter *Checked_Function_Parameter__create(Source_Location *location, String *label, String *name, Checked_Type *type);

typedef struct Checked_Function_Type {
    Checked_Type super;
    Checked_Type *return_type;
    Checked_Function_Parameter *first_parameter;
} Checked_Function_Type;

Checked_Function_Type *Checked_Function_Type__create(Source_Location *location, Checked_Function_Parameter *first_parameter, Checked_Type *return_type);

bool Checked_Function_Type__equals(Checked_Function_Type *self, Checked_Function_Type *other);

typedef struct Checked_Function_Pointer_Type {
    Checked_Type super;
    Checked_Function_Type *function_type;
} Checked_Function_Pointer_Type;

Checked_Function_Pointer_Type *Checked_Function_Pointer_Type__create(Source_Location *location, Checked_Function_Type *function_type);

typedef struct Checked_Pointer_Type {
    Checked_Type super;
    Checked_Type *other_type;
} Checked_Pointer_Type;

Checked_Pointer_Type *Checked_Pointer_Type__create(Source_Location *location, Checked_Type *other_type);

typedef struct Checked_Struct_Member {
    Source_Location *location;
    String *name;
    Checked_Type *type;
    struct Checked_Struct_Member *next_member;
} Checked_Struct_Member;

Checked_Struct_Member *Checked_Struct_Member__create(Source_Location *location, String *name, Checked_Type *type);

typedef struct Checked_Struct_Type {
    Checked_Named_Type super;
    Checked_Struct_Member *first_member;
} Checked_Struct_Type;

Checked_Struct_Type *Checked_Struct_Type__create(Source_Location *location, String *name);

Checked_Struct_Member *Checked_Struct_Type__find_member(Checked_Struct_Type *self, String *name);

typedef struct Checked_Trait_Method {
    Source_Location *location;
    String *name;
    Checked_Function_Type *function_type;
    Checked_Struct_Member *struct_member;
    struct Checked_Trait_Method *next_method;
} Checked_Trait_Method;

Checked_Trait_Method *Checked_Trait_Method__create(Source_Location *location, String *name, Checked_Function_Type *function_type, Checked_Struct_Member *struct_member);

typedef struct Checked_Trait_Type {
    Checked_Named_Type super;
    Checked_Struct_Type *struct_type;
    Checked_Struct_Member *self_struct_member;
    Checked_Trait_Method *first_method;
} Checked_Trait_Type;

Checked_Trait_Type *Checked_Trait_Type__create(Source_Location *location, String *name);

bool Checked_Type__equals(Checked_Type *self, Checked_Type *other);

void pWriter__write__checked_function_parameter(Writer *writer, Checked_Function_Parameter *parameter);

void pWriter__write__checked_type(Writer *writer, Checked_Type *type);

typedef enum Checked_Symbol_Kind {
    CHECKED_SYMBOL_KIND__ENUM_MEMBER,
    CHECKED_SYMBOL_KIND__FUNCTION,
    CHECKED_SYMBOL_KIND__FUNCTION_PARAMETER,
    CHECKED_SYMBOL_KIND__TYPE,
    CHECKED_SYMBOL_KIND__VARIABLE
} Checked_Symbol_Kind;

typedef struct Checked_Symbol {
    Checked_Symbol_Kind kind;
    Source_Location *location;
    String *name;
    Checked_Type *type;
    struct Checked_Symbol *prev_symbol;
    struct Checked_Symbol *next_symbol;
} Checked_Symbol;

Checked_Symbol *Checked_Symbol__create_kind(Checked_Symbol_Kind kind, size_t kind_size, Source_Location *location, String *name, Checked_Type *type);

typedef struct Checked_Enum_Member_Symbol {
    Checked_Symbol super;
} Checked_Enum_Member_Symbol;

Checked_Enum_Member_Symbol *Checked_Enum_Member_Symbol__create(Source_Location *location, String *name, Checked_Type *type);

typedef enum Checked_Statement_Kind {
    CHECKED_STATEMENT_KIND__ASSIGNMENT,
    CHECKED_STATEMENT_KIND__BLOCK,
    CHECKED_STATEMENT_KIND__BREAK,
    CHECKED_STATEMENT_KIND__EXPRESSION,
    CHECKED_STATEMENT_KIND__IF,
    CHECKED_STATEMENT_KIND__LOOP,
    CHECKED_STATEMENT_KIND__RETURN,
    CHECKED_STATEMENT_KIND__VARIABLE,
    CHECKED_STATEMENT_KIND__WHILE
} Checked_Statement_Kind;

typedef struct Checked_Statement {
    Checked_Statement_Kind kind;
    Source_Location *location;
    struct Checked_Statement *next_statement;
} Checked_Statement;

Checked_Statement *Checked_Statement__create_kind(Checked_Statement_Kind kind, size_t kind_size, Source_Location *location);

typedef struct Checked_Statements {
    Checked_Statement *first_statement;
    Checked_Statement *last_statement;
} Checked_Statements;

Checked_Statements *Checked_Statements__create();

void Checked_Statements__append(Checked_Statements *self, Checked_Statement *statement);

typedef struct Checked_Function_Symbol {
    Checked_Symbol super;
    String *function_name;
    Checked_Function_Type *function_type;
    Checked_Type *receiver_type;
    Checked_Statements *checked_statements;
} Checked_Function_Symbol;

Checked_Function_Symbol *Checked_Function_Symbol__create(Source_Location *location, String *symbol_name, String *function_name, Checked_Function_Type *function_type, Checked_Type *receiver_type);

typedef struct Checked_Function_Parameter_Symbol {
    Checked_Symbol super;
} Checked_Function_Parameter_Symbol;

Checked_Function_Parameter_Symbol *Checked_Function_Parameter_Symbol__create(Source_Location *location, String *name, Checked_Type *type);

typedef struct Checked_Type_Symbol {
    Checked_Symbol super;
    Checked_Named_Type *named_type;
} Checked_Type_Symbol;

Checked_Type_Symbol *Checked_Type_Symbol__create(Source_Location *location, String *name, Checked_Named_Type *named_type);

typedef struct Checked_Variable_Symbol {
    Checked_Symbol super;
} Checked_Variable_Symbol;

Checked_Variable_Symbol *Checked_Variable_Symbol__create(Source_Location *location, String *name, Checked_Type *type);

typedef struct Checked_Symbols {
    struct Checked_Symbols *parent;
    Checked_Symbol *first_symbol;
    Checked_Symbol *last_symbol;
} Checked_Symbols;

Checked_Symbols *Checked_Symbols__create(Checked_Symbols *parent);

Checked_Symbol *Checked_Symbols__find_sibling_symbol(Checked_Symbols *self, String *name);

void Checked_Symbols__append_symbol(Checked_Symbols *self, Checked_Symbol *symbol);

Checked_Symbol *Checked_Symbols__find_symbol(Checked_Symbols *self, String *name);

Checked_Expression *Checked_Expression__create_kind(Checked_Expression_Kind kind, size_t kind_size, Source_Location *location, Checked_Type *type);

typedef struct Checked_Binary_Expression {
    Checked_Expression super;
    Checked_Expression *left_expression;
    Checked_Expression *right_expression;
} Checked_Binary_Expression;

Checked_Binary_Expression *Checked_Binary_Expression__create_kind(Checked_Expression_Kind kind, Source_Location *location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression);

typedef struct Checked_Unary_Expression {
    Checked_Expression super;
    Checked_Expression *other_expression;
} Checked_Unary_Expression;

Checked_Unary_Expression *Checked_Unary_Expression__create_kind(Checked_Expression_Kind kind, size_t kind_size, Source_Location *location, Checked_Type *type, Checked_Expression *other_expression);

typedef struct Checked_Add_Expression {
    Checked_Binary_Expression super;
} Checked_Add_Expression;

Checked_Add_Expression *Checked_Add_Expression__create(Source_Location *location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression);

typedef struct Checked_Address_Of_Expression {
    Checked_Unary_Expression super;
} Checked_Address_Of_Expression;

Checked_Address_Of_Expression *Checked_Address_Of_Expression__create(Source_Location *location, Checked_Type *type, Checked_Expression *other_expression);

typedef struct Checked_Array_Access_Expression {
    Checked_Expression super;
    Checked_Expression *array_expression;
    Checked_Expression *index_expression;
} Checked_Array_Access_Expression;

Checked_Array_Access_Expression *Checked_Array_Access_Expression__create(Source_Location *location, Checked_Type *type, Checked_Expression *array_expression, Checked_Expression *index_expression);

typedef struct Checked_Bool_Expression {
    Checked_Expression super;
    bool value;
} Checked_Bool_Expression;

Checked_Bool_Expression *Checked_Bool_Expression__create(Source_Location *location, Checked_Type *type, bool value);

typedef struct Checked_Call_Argument {
    Checked_Expression *expression;
    struct Checked_Call_Argument *next_argument;
} Checked_Call_Argument;

Checked_Call_Argument *Checked_Call_Argument__create(Checked_Expression *expression);

typedef struct Checked_Call_Expression {
    Checked_Expression super;
    Checked_Expression *callee_expression;
    Checked_Call_Argument *first_argument;
} Checked_Call_Expression;

Checked_Call_Expression *Checked_Call_Expression__create(Source_Location *location, Checked_Type *type, Checked_Expression *callee_expression, Checked_Call_Argument *first_argument);

typedef struct Checked_Cast_Expression {
    Checked_Expression super;
    Checked_Expression *other_expression;
} Checked_Cast_Expression;

Checked_Cast_Expression *Checked_Cast_Expression__create(Source_Location *location, Checked_Type *type, Checked_Expression *other_expression);

typedef struct Checked_Character_Expression {
    Checked_Expression super;
    char value;
} Checked_Character_Expression;

Checked_Character_Expression *Checked_Character_Expression__create(Source_Location *location, Checked_Type *type, char value);

typedef struct Checked_Dereference_Expression {
    Checked_Unary_Expression super;
} Checked_Dereference_Expression;

Checked_Dereference_Expression *Checked_Dereference_Expression__create(Source_Location *location, Checked_Type *type, Checked_Expression *other_expression);

typedef struct Checked_Divide_Expression {
    Checked_Binary_Expression super;
} Checked_Divide_Expression;

Checked_Divide_Expression *Checked_Divide_Expression__create(Source_Location *location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression);

typedef struct Checked_Equals_Expression {
    Checked_Binary_Expression super;
} Checked_Equals_Expression;

Checked_Equals_Expression *Checked_Equals_Expression__create(Source_Location *location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression);

typedef struct Checked_Greater_Expression {
    Checked_Binary_Expression super;
} Checked_Greater_Expression;

Checked_Greater_Expression *Checked_Greater_Expression__create(Source_Location *location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression);

typedef struct Checked_Greater_Or_Equals_Expression {
    Checked_Binary_Expression super;
} Checked_Greater_Or_Equals_Expression;

Checked_Greater_Or_Equals_Expression *Checked_Greater_Or_Equals_Expression__create(Source_Location *location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression);

typedef struct Checked_Group_Expression {
    Checked_Expression super;
    Checked_Expression *other_expression;
} Checked_Group_Expression;

Checked_Group_Expression *Checked_Group_Expression__create(Source_Location *location, Checked_Type *type, Checked_Expression *other_expression);

typedef struct Checked_Integer_Expression {
    Checked_Expression super;
    uint64_t value;
} Checked_Integer_Expression;

Checked_Integer_Expression *Checked_Integer_Expression__create(Source_Location *location, Checked_Type *type, uint64_t value);

typedef struct Checked_Less_Expression {
    Checked_Binary_Expression super;
} Checked_Less_Expression;

Checked_Less_Expression *Checked_Less_Expression__create(Source_Location *location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression);

typedef struct Checked_Less_Or_Equals_Expression {
    Checked_Binary_Expression super;
} Checked_Less_Or_Equals_Expression;

Checked_Less_Or_Equals_Expression *Checked_Less_Or_Equals_Expression__create(Source_Location *location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression);

typedef struct Checked_Logic_And_Expression {
    Checked_Binary_Expression super;
} Checked_Logic_And_Expression;

Checked_Logic_And_Expression *Checked_Logic_And_Expression__create(Source_Location *location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression);

typedef struct Checked_Logic_Or_Expression {
    Checked_Binary_Expression super;
} Checked_Logic_Or_Expression;

Checked_Logic_Or_Expression *Checked_Logic_Or_Expression__create(Source_Location *location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression);

typedef struct Checked_Make_Struct_Argument {
    Checked_Struct_Member *struct_member;
    Checked_Expression *expression;
    struct Checked_Make_Struct_Argument *next_argument;
} Checked_Make_Struct_Argument;

Checked_Make_Struct_Argument *Checked_Make_Struct_Argument__create(Checked_Struct_Member *struct_member, Checked_Expression *expression);

typedef struct Checked_Make_Struct_Expression {
    Checked_Expression super;
    Checked_Struct_Type *struct_type;
    Checked_Make_Struct_Argument *first_argument;
} Checked_Make_Struct_Expression;

Checked_Make_Struct_Expression *Checked_Make_Struct_Expression__create(Source_Location *location, Checked_Type *type, Checked_Struct_Type *struct_type, Checked_Make_Struct_Argument *first_argument);

typedef struct Checked_Member_Access_Expression {
    Checked_Expression super;
    Checked_Expression *object_expression;
    Checked_Struct_Member *member;
} Checked_Member_Access_Expression;

Checked_Member_Access_Expression *Checked_Member_Access_Expression__create(Source_Location *location, Checked_Type *type, Checked_Expression *object_expression, Checked_Struct_Member *member);

typedef struct Checked_Minus_Expression {
    Checked_Unary_Expression super;
} Checked_Minus_Expression;

Checked_Minus_Expression *Checked_Minus_Expression__create(Source_Location *location, Checked_Type *type, Checked_Expression *other_expression);

typedef struct Checked_Modulo_Expression {
    Checked_Binary_Expression super;
} Checked_Modulo_Expression;

Checked_Modulo_Expression *Checked_Modulo_Expression__create(Source_Location *location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression);

typedef struct Checked_Multiply_Expression {
    Checked_Binary_Expression super;
} Checked_Multiply_Expression;

Checked_Multiply_Expression *Checked_Multiply_Expression__create(Source_Location *location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression);

typedef struct Checked_Not_Expression {
    Checked_Unary_Expression super;
} Checked_Not_Expression;

Checked_Not_Expression *Checked_Not_Expression__create(Source_Location *location, Checked_Type *type, Checked_Expression *other_expression);

typedef struct Checked_Not_Equals_Expression {
    Checked_Binary_Expression super;
} Checked_Not_Equals_Expression;

Checked_Not_Equals_Expression *Checked_Not_Equals_Expression__create(Source_Location *location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression);

typedef struct Checked_Null_Expression {
    Checked_Expression super;
} Checked_Null_Expression;

Checked_Null_Expression *Checked_Null_Expression__create(Source_Location *location, Checked_Type *type);

typedef struct Checked_Sizeof_Expression {
    Checked_Expression super;
    Checked_Type *sized_type;
} Checked_Sizeof_Expression;

Checked_Sizeof_Expression *Checked_Sizeof_Expression__create(Source_Location *location, Checked_Type *type, Checked_Type *sized_type);

typedef struct Checked_String_Expression {
    Checked_Expression super;
    String *value;
} Checked_String_Expression;

Checked_String_Expression *Checked_String_Expression__create(Source_Location *location, Checked_Type *type, String *value);

typedef struct Checked_Substract_Expression {
    Checked_Binary_Expression super;
} Checked_Substract_Expression;

Checked_Substract_Expression *Checked_Substract_Expression__create(Source_Location *location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression);

typedef struct Checked_Symbol_Expression {
    Checked_Expression super;
    Checked_Symbol *symbol;
} Checked_Symbol_Expression;

Checked_Symbol_Expression *Checked_Symbol_Expression__create(Source_Location *location, Checked_Type *type, Checked_Symbol *symbol);

typedef struct Checked_Assignment_Statement {
    Checked_Statement super;
    Checked_Expression *object_expression;
    Checked_Expression *value_expression;
} Checked_Assignment_Statement;

Checked_Assignment_Statement *Checked_Assignment_Statement__create(Source_Location *location, Checked_Expression *object_expression, Checked_Expression *value_expression);

typedef struct Checked_Block_Statement {
    Checked_Statement super;
    Checked_Statements *statements;
} Checked_Block_Statement;

Checked_Block_Statement *Checked_Block_Statement__create(Source_Location *location, Checked_Statements *statements);

typedef struct Checked_Break_Statement {
    Checked_Statement super;
} Checked_Break_Statement;

Checked_Break_Statement *Checked_Break_Statement__create(Source_Location *location);

typedef struct Checked_Expression_Statement {
    Checked_Statement super;
    Checked_Expression *expression;
} Checked_Expression_Statement;

Checked_Expression_Statement *Checked_Expression_Statement__create(Source_Location *location, Checked_Expression *expression);

typedef struct Checked_If_Statement {
    Checked_Statement super;
    Checked_Expression *condition_expression;
    Checked_Statement *true_statement;
    Checked_Statement *false_statement;
} Checked_If_Statement;

Checked_If_Statement *Checked_If_Statement__create(Source_Location *location, Checked_Expression *condition_expression, Checked_Statement *true_statement, Checked_Statement *false_statement);

typedef struct Checked_Loop_Statement {
    Checked_Statement super;
    Checked_Statement *body_statement;
} Checked_Loop_Statement;

Checked_Loop_Statement *Checked_Loop_Statement__create(Source_Location *location, Checked_Statement *body_statement);

typedef struct Checked_Return_Statement {
    Checked_Statement super;
    Checked_Expression *expression;
} Checked_Return_Statement;

Checked_Return_Statement *Checked_Return_Statement__create(Source_Location *location, Checked_Expression *expression);

typedef struct Checked_Variable_Statement {
    Checked_Statement super;
    Checked_Variable_Symbol *variable;
    Checked_Expression *expression;
    bool is_external;
} Checked_Variable_Statement;

Checked_Variable_Statement *Checked_Variable_Statement__create(Source_Location *location, Checked_Variable_Symbol *variable, Checked_Expression *expression, bool is_external);

typedef struct Checked_While_Statement {
    Checked_Statement super;
    Checked_Expression *condition_expression;
    Checked_Statement *body_statement;
} Checked_While_Statement;

Checked_While_Statement *Checked_While_Statement__create(Source_Location *location, Checked_Expression *condition_expression, Checked_Statement *body_statement);

typedef struct Checked_Source {
    Source *first_source;
    Checked_Symbol *first_symbol;
    Checked_Statements *statements;
} Checked_Source;

#endif
