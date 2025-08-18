#ifndef __PARSED_SOURCE_H__
#define __PARSED_SOURCE_H__

#include "Token.h"

typedef enum Parsed_Expression_Kind {
    PARSED_EXPRESSION_KIND__ADD,
    PARSED_EXPRESSION_KIND__ADDRESS_OF,
    PARSED_EXPRESSION_KIND__ALLOC,
    PARSED_EXPRESSION_KIND__ARRAY_ACCESS,
    PARSED_EXPRESSION_KIND__BLOCK,
    PARSED_EXPRESSION_KIND__BOOL,
    PARSED_EXPRESSION_KIND__CALL,
    PARSED_EXPRESSION_KIND__CAST,
    PARSED_EXPRESSION_KIND__CHARACTER,
    PARSED_EXPRESSION_KIND__DEREFERENCE,
    PARSED_EXPRESSION_KIND__DIVIDE,
    PARSED_EXPRESSION_KIND__EQUALS,
    PARSED_EXPRESSION_KIND__GREATER_OR_EQUALS,
    PARSED_EXPRESSION_KIND__GREATER,
    PARSED_EXPRESSION_KIND__GROUP,
    PARSED_EXPRESSION_KIND__INTEGER,
    PARSED_EXPRESSION_KIND__IS,
    PARSED_EXPRESSION_KIND__LESS_OR_EQUALS,
    PARSED_EXPRESSION_KIND__LESS,
    PARSED_EXPRESSION_KIND__LOGIC_AND,
    PARSED_EXPRESSION_KIND__LOGIC_OR,
    PARSED_EXPRESSION_KIND__MEMBER_ACCESS,
    PARSED_EXPRESSION_KIND__MINUS,
    PARSED_EXPRESSION_KIND__MODULO,
    PARSED_EXPRESSION_KIND__MULTIPLY,
    PARSED_EXPRESSION_KIND__NOT_EQUALS,
    PARSED_EXPRESSION_KIND__NOT,
    PARSED_EXPRESSION_KIND__NULL,
    PARSED_EXPRESSION_KIND__SIZEOF,
    PARSED_EXPRESSION_KIND__STRING,
    PARSED_EXPRESSION_KIND__SUBTRACT,
    PARSED_EXPRESSION_KIND__SYMBOL,
    PARSED_EXPRESSION_KIND__TRY,
    PARSED_EXPRESSION_KIND__TYPE_SPECIALIZATION,
} Parsed_Expression_Kind;

typedef struct Parsed_Expression {
    Parsed_Expression_Kind kind;
    Source_Location location;
} Parsed_Expression;

typedef enum Parsed_Type_Kind {
    PARSED_TYPE_KIND__ARRAY,
    PARSED_TYPE_KIND__PROCEDURE,
    PARSED_TYPE_KIND__MULTI_POINTER,
    PARSED_TYPE_KIND__NAMED,
    PARSED_TYPE_KIND__POINTER,
    PARSED_TYPE_KIND__RECEIVER
} Parsed_Type_Kind;

typedef struct Parsed_Type {
    Parsed_Type_Kind kind;
    Source_Location location;
} Parsed_Type;

Parsed_Type *Parsed_Type__create_kind(Parsed_Type_Kind kind, size_t kind_size, Source_Location location);

typedef struct Parsed_Array_Type {
    Parsed_Type super;
    Parsed_Type *item_type;
    Parsed_Expression *size_expression;
} Parsed_Array_Type;

Parsed_Array_Type *Parsed_Array_Type__create(Source_Location location, Parsed_Type *item_type, Parsed_Expression *size_expression);

typedef struct Parsed_Procedure_Parameter {
    Token *label;
    Token *name;
    Parsed_Type *type;
    struct Parsed_Procedure_Parameter *next_parameter;
} Parsed_Procedure_Parameter;

Parsed_Procedure_Parameter *Parsed_Procedure_Parameter__create(Token *label, Token *name, Parsed_Type *type);

typedef struct Parsed_Procedure_Type {
    Parsed_Type super;
    Parsed_Procedure_Parameter *first_parameter;
    Parsed_Type *return_type;
} Parsed_Procedure_Type;

Parsed_Type *Parsed_Procedure_Type__create(Source_Location location, Parsed_Procedure_Parameter *first_parameter, Parsed_Type *return_type);

typedef struct Parsed_Multi_Pointer_Type {
    Parsed_Type super;
    Parsed_Type *item_type;
} Parsed_Multi_Pointer_Type;

Parsed_Type *Parsed_Multi_Pointer_Type__create(Source_Location location, Parsed_Type *item_type);

typedef struct Parsed_Type_Argument {
    Parsed_Type *type;
    struct Parsed_Type_Argument *next_type_argument;
} Parsed_Type_Argument;

Parsed_Type_Argument *Parsed_Type_Argument__create(Parsed_Type *type);

typedef struct Parsed_Named_Type {
    Parsed_Type super;
    Token *module;
    String *name;
    Parsed_Type_Argument *first_type_argument;
} Parsed_Named_Type;

Parsed_Named_Type *Parsed_Named_Type__create(Token *module, Token *name);

typedef struct Parsed_Pointer_Type {
    Parsed_Type super;
    Parsed_Type *other_type;
} Parsed_Pointer_Type;

Parsed_Type *Parsed_Pointer_Type__create(Source_Location location, Parsed_Type *other_type);

typedef struct Parsed_Receiver_Type {
    Parsed_Type super;
} Parsed_Receiver_Type;

Parsed_Receiver_Type *Parsed_Receiver_Type__create(Source_Location location);

Parsed_Expression *Parsed_Expression__create_kind(Parsed_Expression_Kind kind, size_t kind_size, Source_Location location);

typedef struct Parsed_Alloc_Expression {
    Parsed_Expression super;
    Parsed_Expression *value_expression;
} Parsed_Alloc_Expression;

Parsed_Alloc_Expression *Parsed_Alloc_Expression__create(Source_Location location, Parsed_Expression *value_expression);

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

Parsed_Unary_Expression *Parsed_Unary_Expression__create_kind(Parsed_Expression_Kind kind, size_t kind_size, Source_Location location, Parsed_Expression *other_expression);

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

Parsed_Address_Of_Expression *Parsed_Address_Of_Expression__create(Source_Location location, Parsed_Expression *other_expression);

typedef struct Parsed_Array_Access_Expression {
    Parsed_Expression super;
    Parsed_Expression *array_expression;
    Parsed_Expression *index_expression;
} Parsed_Array_Access_Expression;

Parsed_Array_Access_Expression *Parsed_Array_Access_Expression__create(Source_Location location, Parsed_Expression *array_expression, Parsed_Expression *index_expression);

typedef struct Parsed_Bool_Expression {
    Parsed_Literal_Expression super;
    bool value;
} Parsed_Bool_Expression;

Parsed_Bool_Expression *Parsed_Bool_Expression__create(Token *literal, bool value);

typedef struct Parsed_Call_Argument {
    Source_Location location;
    Identifier_Token *name;
    Parsed_Expression *expression;
    struct Parsed_Call_Argument *next_argument;
} Parsed_Call_Argument;

Parsed_Call_Argument *Parsed_Call_Argument__create(Source_Location location, Identifier_Token *name, Parsed_Expression *expression);

typedef struct Parsed_Call_Expression {
    Parsed_Expression super;
    Parsed_Expression *callee_expression;
    Parsed_Call_Argument *first_argument;
} Parsed_Call_Expression;

Parsed_Call_Expression *Parsed_Call_Expression__create(Source_Location location, Parsed_Expression *callee_expression, Parsed_Call_Argument *first_argument);

typedef struct Parsed_Cast_Expression {
    Parsed_Unary_Expression super;
    Parsed_Type *type;
} Parsed_Cast_Expression;

Parsed_Cast_Expression *Parsed_Cast_Expression__create(Source_Location location, Parsed_Expression *other_expression, Parsed_Type *type);

typedef struct Parsed_Character_Expression {
    Parsed_Literal_Expression super;
    char value;
} Parsed_Character_Expression;

Parsed_Character_Expression *Parsed_Character_Expression__create(Character_Token *literal);

typedef struct Parsed_Dereference_Expression {
    Parsed_Unary_Expression super;
} Parsed_Dereference_Expression;

Parsed_Dereference_Expression *Parsed_Dereference_Expression__create(Source_Location location, Parsed_Expression *other_expression);

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

Parsed_Group_Expression *Parsed_Group_Expression__create(Source_Location location, Parsed_Expression *other_expression);

typedef struct Parsed_Integer_Expression {
    Parsed_Literal_Expression super;
    uint64_t value;
    int32_t base;
    Parsed_Named_Type *type;
} Parsed_Integer_Expression;

Parsed_Integer_Expression *Parsed_Integer_Expression__create(Integer_Token *literal, Parsed_Named_Type *type);

typedef struct Parsed_Is_Expression {
    Parsed_Expression super;
    Parsed_Expression *value_expression;
    Parsed_Type *runtime_type;
    bool is_not;
} Parsed_Is_Expression;

Parsed_Is_Expression *Parsed_Is_Expression__create(Parsed_Expression *object_expression, Parsed_Type *runtime_type, bool is_not);

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

Parsed_Minus_Expression *Parsed_Minus_Expression__create(Source_Location location, Parsed_Expression *other_expression);

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

Parsed_Not_Expression *Parsed_Not_Expression__create(Source_Location location, Parsed_Expression *other_expression);

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

Parsed_Sizeof_Expression *Parsed_Sizeof_Expression__create(Source_Location location, Parsed_Type *type);

typedef struct Parsed_String_Expression {
    Parsed_Literal_Expression super;
    String *value;
} Parsed_String_Expression;

Parsed_String_Expression *Parsed_String_Expression__create(String_Token *literal);

typedef struct Parsed_Subtract_Expression {
    Parsed_Binary_Expression super;
} Parsed_Subtract_Expression;

Parsed_Subtract_Expression *Parsed_Subtract_Expression__create(Parsed_Expression *left_expression, Parsed_Expression *right_expression);

typedef struct Parsed_Symbol_Expression {
    Parsed_Expression super;
    Token *name;
} Parsed_Symbol_Expression;

Parsed_Symbol_Expression *Parsed_Symbol_Expression__create(Token *name);

typedef struct Parsed_Try_Expression {
    Parsed_Expression super;
    Parsed_Expression *expression;
    Parsed_Expression *else_expression;
} Parsed_Try_Expression;

Parsed_Try_Expression *Parsed_Try_Expression__create(Source_Location location, Parsed_Expression *expression, Parsed_Expression *else_expression);

typedef struct Parsed_Type_Specialization_Expression {
    Parsed_Expression super;
    Parsed_Expression *type_expression;
    Parsed_Type_Argument *first_type_argument;
} Parsed_Type_Specialization_Expression;

Parsed_Type_Specialization_Expression *Parsed_Type_Specialization_Expression__create(Source_Location location, Parsed_Expression *first_type_expression, Parsed_Type_Argument *type_argument);

typedef enum Parsed_Statement_Kind {
    PARSED_STATEMENT_KIND__ASSIGNMENT,
    PARSED_STATEMENT_KIND__BLOCK,
    PARSED_STATEMENT_KIND__BREAK,
    PARSED_STATEMENT_KIND__CONSTANT,
    PARSED_STATEMENT_KIND__DEFER,
    PARSED_STATEMENT_KIND__EXPRESSION,
    PARSED_STATEMENT_KIND__IF,
    PARSED_STATEMENT_KIND__IMPORT,
    PARSED_STATEMENT_KIND__LOOP,
    PARSED_STATEMENT_KIND__PROCEDURE,
    PARSED_STATEMENT_KIND__RAISE,
    PARSED_STATEMENT_KIND__RETURN,
    PARSED_STATEMENT_KIND__SWITCH,
    PARSED_STATEMENT_KIND__TYPE,
    PARSED_STATEMENT_KIND__VARIABLE,
    PARSED_STATEMENT_KIND__WHILE,
    PARSED_STATEMENT_KIND__YIELD,
} Parsed_Statement_Kind;

typedef struct Parsed_Statement {
    Parsed_Statement_Kind kind;
    Source_Location location;
    struct Parsed_Statement *next_statement;
} Parsed_Statement;

Parsed_Statement *Parsed_Statement__create_kind(Parsed_Statement_Kind kind, size_t kind_size, Source_Location location);

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

Parsed_Named_Statement *Parsed_Named_Statement__create_kind(Parsed_Statement_Kind kind, size_t kind_size, Source_Location location, Token *name);

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

Parsed_Block_Statement *Parsed_Block_Statement__create(Source_Location location, struct Parsed_Statements *statements);

typedef struct Parsed_Block_Expression {
    Parsed_Expression super;
    struct Parsed_Block_Statement *block_statement;
} Parsed_Block_Expression;

Parsed_Block_Expression *Parsed_Block_Expression__create(struct Parsed_Block_Statement *block_statement);

typedef struct Parsed_Break_Statement {
    Parsed_Statement super;
} Parsed_Break_Statement;

Parsed_Statement *Parsed_Break_Statement__create(Source_Location location);

typedef struct Parsed_Constant_Statement {
    Parsed_Named_Statement super;
    Parsed_Expression *value_expression;
} Parsed_Constant_Statement;

Parsed_Constant_Statement *Parsed_Constant_Statement__create(Source_Location location, Token *name, Parsed_Expression *value_expression);

typedef struct Parsed_Defer_Statement {
    Parsed_Statement super;
    Parsed_Statement *statement;
} Parsed_Defer_Statement;

Parsed_Defer_Statement *Parsed_Defer_Statement__create(Source_Location location, Parsed_Statement *statement);

typedef struct Parsed_Expression_Statement {
    Parsed_Statement super;
    Parsed_Expression *expression;
} Parsed_Expression_Statement;

Parsed_Expression_Statement *Parsed_Expression_Statement__create(Parsed_Expression *expression);

typedef struct Parsed_Type_Parameter {
    Token *name;
    struct Parsed_Type_Parameter *next_type_parameter;
} Parsed_Type_Parameter;

Parsed_Type_Parameter *Parsed_Type_Parameter__create(Token *name);

typedef struct Parsed_Procedure_Statement {
    Parsed_Named_Statement super;
    Parsed_Type_Parameter *first_type_parameter;
    bool is_method;
    Parsed_Procedure_Parameter *first_parameter;
    Parsed_Type *return_type;
    Parsed_Type *raise_type;
    bool is_external;
    struct Parsed_Block_Statement *block_statement;
    String_Token *external_name;
} Parsed_Procedure_Statement;

Parsed_Statement *Parsed_Procedure_Statement__create(Source_Location location, Token *name, Parsed_Type_Parameter *first_type_parameter, bool is_method, Parsed_Procedure_Parameter *first_parameter, Parsed_Type *return_type, Parsed_Type *raise_type, bool is_external, struct Parsed_Block_Statement *block_statement, String_Token *external_name);

typedef struct Parsed_If_Statement {
    Parsed_Statement super;
    Parsed_Expression *condition_expression;
    Identifier_Token *variant_alias;
    Parsed_Statement *true_statement;
    Parsed_Statement *false_statement;
} Parsed_If_Statement;

Parsed_Statement *Parsed_If_Statement__create(Source_Location location, Parsed_Expression *condition_expression, Identifier_Token *variant_alias, Parsed_Statement *true_statement, Parsed_Statement *false_statement);

typedef struct Parsed_Loop_Statement {
    Parsed_Statement super;
    Parsed_Statement *body_statement;
} Parsed_Loop_Statement;

Parsed_Statement *Parsed_Loop_Statement__create(Source_Location location, Parsed_Statement *body_statement);

typedef struct Parsed_Raise_Statement {
    Parsed_Statement super;
    Parsed_Expression *expression;
} Parsed_Raise_Statement;

Parsed_Raise_Statement *Parsed_Raise_Statement__create(Source_Location location, Parsed_Expression *expression);

typedef struct Parsed_Return_Statement {
    Parsed_Statement super;
    Parsed_Expression *expression;
} Parsed_Return_Statement;

Parsed_Statement *Parsed_Return_Statement__create(Source_Location location, Parsed_Expression *expression);

typedef enum Parsed_Type_Specifier_Kind {
    PARSED_TYPE_SPECIFIER_KIND__BUILTIN,
    PARSED_TYPE_SPECIFIER_KIND__EXTERNAL,
    PARSED_TYPE_SPECIFIER_KIND__STRUCT,
    PARSED_TYPE_SPECIFIER_KIND__TRAIT,
    PARSED_TYPE_SPECIFIER_KIND__VARIANT,
} Parsed_Type_Specifier_Kind;

typedef struct Parsed_Type_Specifier {
    Parsed_Type_Specifier_Kind kind;
    Source_Location location;
} Parsed_Type_Specifier;

typedef struct Parsed_Type_Statement {
    Parsed_Named_Statement super;
    Parsed_Type_Specifier *type_specifier;
    Parsed_Type_Parameter *first_type_parameter;
} Parsed_Type_Statement;

Parsed_Type_Statement *Parsed_Type_Statement__create(Source_Location location, Token *name, Parsed_Type_Specifier *type_specifier, Parsed_Type_Parameter *first_type_parameter);

typedef enum Parsed_Switch_Case_Kind {
    PARSED_SWITCH_CASE_KIND__ELSE,
    PARSED_SWITCH_CASE_KIND__EXPRESSION,
    PARSED_SWITCH_CASE_KIND__VARIANT,
} Parsed_Switch_Case_Kind;

typedef struct Parsed_Switch_Case {
    Parsed_Switch_Case_Kind kind;
    Source_Location location;
    union {
        Parsed_Expression *expression;
        struct {
            Parsed_Type *type;
            Identifier_Token *alias;
        } variant;
    };
    Parsed_Statement *statement;
    struct Parsed_Switch_Case *next_case;
} Parsed_Switch_Case;

Parsed_Switch_Case *Parsed_Switch_Else__create(Source_Location location);

Parsed_Switch_Case *Parsed_Switch_Expression__create(Source_Location location, Parsed_Expression *expression);

Parsed_Switch_Case *Parsed_Switch_Variant__create(Source_Location location, Parsed_Type *type, Identifier_Token *alias);

typedef struct Parsed_Switch_Statement {
    Parsed_Statement super;
    Parsed_Expression *expression;
    Parsed_Switch_Case *first_case;
} Parsed_Switch_Statement;

Parsed_Switch_Statement *Parsed_Switch_Statement__create(Source_Location location, Parsed_Expression *expression, Parsed_Switch_Case *first_case);

typedef struct Parsed_Variable_Statement {
    Parsed_Named_Statement super;
    Parsed_Type *type;
    bool is_external;
    Parsed_Expression *expression;
    String_Token *external_name;
} Parsed_Variable_Statement;

Parsed_Variable_Statement *Parsed_Variable_Statement__create(Source_Location location, Token *name, Parsed_Type *type, bool is_external, Parsed_Expression *expression, String_Token *external_name);

typedef struct Parsed_While_Statement {
    Parsed_Statement super;
    Parsed_Expression *condition_expression;
    Parsed_Statement *body_statement;
} Parsed_While_Statement;

Parsed_Statement *Parsed_While_Statement__create(Source_Location location, Parsed_Expression *condition_expression, Parsed_Statement *body_statement);

typedef struct Parsed_Yield_Statement {
    Parsed_Statement super;
    Parsed_Expression *expression;
} Parsed_Yield_Statement;

Parsed_Yield_Statement *Parsed_Yield_Statement__create(Source_Location location, Parsed_Expression *expression);

typedef struct Parsed_Builtin_Type_Specifier {
    Parsed_Type_Specifier super;
} Parsed_Builtin_Type_Specifier;

Parsed_Builtin_Type_Specifier *Parsed_Builtin_Type_Specifier__create(Source_Location location);

typedef struct Parsed_External_Type_Specifier {
    Parsed_Type_Specifier super;
} Parsed_External_Type_Specifier;

Parsed_External_Type_Specifier *Parsed_External_Type_Specifier__create(Source_Location location);

typedef struct Parsed_Struct_Member {
    Token *name;
    Parsed_Type *type;
    struct Parsed_Struct_Member *next_member;
} Parsed_Struct_Member;

Parsed_Struct_Member *Parsed_Struct_Member__create(Token *name, Parsed_Type *type);

typedef struct Parsed_Struct_Type_Specifier {
    Parsed_Type_Specifier super;
    Parsed_Struct_Member *first_member;
} Parsed_Struct_Type_Specifier;

Parsed_Struct_Type_Specifier *Parsed_Struct_Type_Specifier__create(Source_Location location, Parsed_Struct_Member *first_member);

typedef struct Parsed_Trait_Method {
    Source_Location location;
    Token *name;
    Parsed_Procedure_Parameter *first_parameter;
    Parsed_Type *return_type;
    Parsed_Type *raise_type;
    struct Parsed_Trait_Method *next_method;
} Parsed_Trait_Method;

Parsed_Trait_Method *Parsed_Trait_Method__create(Source_Location location, Token *name, Parsed_Procedure_Parameter *first_parameter, Parsed_Type *return_type, Parsed_Type *raise_type);

typedef struct Parsed_Trait_Type_Specifier {
    Parsed_Type_Specifier super;
    Parsed_Trait_Method *first_method;
} Parsed_Trait_Type_Specifier;

Parsed_Trait_Type_Specifier *Parsed_Trait_Type_Specifier__create(Source_Location location, Parsed_Trait_Method *first_method);

typedef struct Parsed_Variant_Case {
    Parsed_Type *type;
    struct Parsed_Variant_Case *next_variant;
} Parsed_Variant_Case;

Parsed_Variant_Case *Parsed_Variant_Case__create(Parsed_Type *type);

typedef struct Parsed_Variant_Type_Specifier {
    Parsed_Type_Specifier super;
    Parsed_Variant_Case *first_variant_case;
} Parsed_Variant_Type_Specifier;

Parsed_Variant_Type_Specifier *Parsed_Variant_Type_Specifier__create(Source_Location location, Parsed_Variant_Case *first_variant);

typedef struct Parsed_Source {
    Source *source;
    String *package_name;
    Parsed_Statements *statements;
} Parsed_Source;

Parsed_Source *Parsed_Source__create();

typedef struct Parsed_Import_Statement {
    Parsed_Statement super;
    String *import_name;
    Parsed_Source *parsed_source;
} Parsed_Import_Statement;

Parsed_Statement *Parsed_Import_Statement__create(Source_Location location, String *import_name, Parsed_Source *parsed_source);

#endif
