#ifndef __CHECKED_SOURCE_H__
#define __CHECKED_SOURCE_H__

#include "Parsed_Source.h"

typedef struct Checked_Module {
    String *name;
    Source *source;
    struct Checked_Module *next_module;
} Checked_Module;

Checked_Module *Checked_Module__create(String *name, Source *source);

typedef struct Checked_Modules {
    Checked_Module *builtin_module;
    Checked_Module *first_module;
    Checked_Module *last_module;
} Checked_Modules;

void Checked_Modules__append(Checked_Modules *self, Checked_Module *module);

Checked_Module *Checked_Modules__find(Checked_Modules *self, String *name);

typedef enum Checked_Type_Kind {
    /* Builtins */
    CHECKED_TYPE_KIND__ANY,
    CHECKED_TYPE_KIND__BOOL,
    CHECKED_TYPE_KIND__I16,
    CHECKED_TYPE_KIND__I32,
    CHECKED_TYPE_KIND__I64,
    CHECKED_TYPE_KIND__I8,
    CHECKED_TYPE_KIND__ISIZE,
    CHECKED_TYPE_KIND__MODULE,  /* Pseudo type */
    CHECKED_TYPE_KIND__NIL,     /* Pseudo type */
    CHECKED_TYPE_KIND__NOTHING, /* Pseudo type */
    CHECKED_TYPE_KIND__NULL,    /* Pseudo type */
    CHECKED_TYPE_KIND__STR,
    CHECKED_TYPE_KIND__TYPE, /* Pseudo type */
    CHECKED_TYPE_KIND__U16,
    CHECKED_TYPE_KIND__U32,
    CHECKED_TYPE_KIND__U64,
    CHECKED_TYPE_KIND__U8,
    CHECKED_TYPE_KIND__USIZE,
    /* Defined */
    CHECKED_TYPE_KIND__ARRAY,
    CHECKED_TYPE_KIND__EXTERNAL,
    CHECKED_TYPE_KIND__GENERIC,
    CHECKED_TYPE_KIND__PROCEDURE,
    CHECKED_TYPE_KIND__STRUCT,
    CHECKED_TYPE_KIND__TRAIT,
    CHECKED_TYPE_KIND__UNION,
    /* Dynamic */
    CHECKED_TYPE_KIND__PROCEDURE_POINTER,
    CHECKED_TYPE_KIND__MULTI_POINTER,
    CHECKED_TYPE_KIND__POINTER
} Checked_Type_Kind;

struct Checked_Type_Symbol;
struct Checked_Type_Dependency;

typedef struct Checked_Type {
    Checked_Type_Kind kind;
    Source_Location location;
    struct Checked_Type_Symbol *symbol;
    struct Checked_Type *next_type;
    struct Checked_Type_Dependency *first_dependency;

    bool has_generated_definition;
} Checked_Type;

struct Checked_Type_Dependency {
    Checked_Type *type;
    struct Checked_Type_Dependency *next_dependency;
};

Checked_Type *Checked_Type__create_kind(Checked_Type_Kind kind, size_t kind_size, Source_Location location);

bool Checked_Type__is_numeric_type(Checked_Type *self);

void String__append_mangled_type_name(String *self, Checked_Type *type);

typedef enum Checked_Expression_Kind {
    CHECKED_EXPRESSION_KIND__ADD,
    CHECKED_EXPRESSION_KIND__ADDRESS_OF,
    CHECKED_EXPRESSION_KIND__ALLOC,
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
    CHECKED_EXPRESSION_KIND__IS_UNION_VARIANT,
    CHECKED_EXPRESSION_KIND__LESS,
    CHECKED_EXPRESSION_KIND__LESS_OR_EQUALS,
    CHECKED_EXPRESSION_KIND__LOGIC_AND,
    CHECKED_EXPRESSION_KIND__LOGIC_OR,
    CHECKED_EXPRESSION_KIND__MAKE_STRUCT,
    CHECKED_EXPRESSION_KIND__MAKE_UNION,
    CHECKED_EXPRESSION_KIND__MEMBER_ACCESS,
    CHECKED_EXPRESSION_KIND__MINUS,
    CHECKED_EXPRESSION_KIND__MODULO,
    CHECKED_EXPRESSION_KIND__MULTIPLY,
    CHECKED_EXPRESSION_KIND__NOT,
    CHECKED_EXPRESSION_KIND__NOT_EQUALS,
    CHECKED_EXPRESSION_KIND__NULL,
    CHECKED_EXPRESSION_KIND__RECEIVER_METHOD,
    CHECKED_EXPRESSION_KIND__SIZEOF,
    CHECKED_EXPRESSION_KIND__STRING,
    CHECKED_EXPRESSION_KIND__STRING_LENGTH,
    CHECKED_EXPRESSION_KIND__SUBTRACT,
    CHECKED_EXPRESSION_KIND__SYMBOL,
    CHECKED_EXPRESSION_KIND__TYPE,
} Checked_Expression_Kind;

typedef struct Checked_Expression {
    Checked_Expression_Kind kind;
    Source_Location location;
    Checked_Type *type;

    String *temp_variable_name; // Used by the generator to store the result of the expression
} Checked_Expression;

bool Checked_Expression__is_mutable(Checked_Expression *self);

typedef struct Checked_Array_Type {
    Checked_Type super;
    Checked_Type *item_type;
    Checked_Expression *size_expression;
} Checked_Array_Type;

Checked_Array_Type *Checked_Array_Type__create(Source_Location location, Checked_Type *item_type, Checked_Expression *size_expression);

typedef struct Checked_Type_Argument {
    Source_Location location;
    String *name;
    Checked_Type *type;
    struct Checked_Type_Argument *next_type_argument;
} Checked_Type_Argument;

Checked_Type_Argument *Checked_Type_Argument__create(Source_Location location, String *name, Checked_Type *type);

struct Checked_Generic_Type;

typedef struct Checked_Named_Type {
    Checked_Type super;
    String *name;
    Checked_Module *module;

    struct Checked_Generic_Type *generic_type;
    Checked_Type_Argument *first_type_argument;
} Checked_Named_Type;

Checked_Named_Type *Checked_Named_Type__create_kind(Checked_Type_Kind kind, size_t kind_size, Source_Location location, String *name, Checked_Module *module);

typedef struct Checked_Generic_Type {
    Checked_Named_Type super;
    Parsed_Type_Statement *parsed_type_statement;
} Checked_Generic_Type;

Checked_Generic_Type *Checked_Generic_Type__create(Source_Location location, String *name, Checked_Module *module, Parsed_Type_Statement *parsed_type_statement);

typedef struct Checked_External_Type {
    Checked_Named_Type super;
} Checked_External_Type;

Checked_External_Type *Checked_External_Type__create(Source_Location location, String *name, Checked_Module *module);

typedef struct Checked_Procedure_Parameter {
    Source_Location location;
    String *label;
    String *name;
    Checked_Type *type;
    struct Checked_Procedure_Parameter *next_parameter;
} Checked_Procedure_Parameter;

Checked_Procedure_Parameter *Checked_Procedure_Parameter__create(Source_Location location, String *label, String *name, Checked_Type *type);

typedef struct Checked_Procedure_Type {
    Checked_Type super;
    Checked_Type *return_type;
    Checked_Procedure_Parameter *first_parameter;
} Checked_Procedure_Type;

Checked_Procedure_Type *Checked_Procedure_Type__create(Source_Location location, Checked_Procedure_Parameter *first_parameter, Checked_Type *return_type);

bool Checked_Procedure_Type__equals(Checked_Procedure_Type *self, Checked_Procedure_Type *other);

typedef struct Checked_Procedure_Pointer_Type {
    Checked_Type super;
    Checked_Procedure_Type *procedure_type;
} Checked_Procedure_Pointer_Type;

Checked_Procedure_Pointer_Type *Checked_Procedure_Pointer_Type__create(Source_Location location, Checked_Procedure_Type *procedure_type);

typedef struct Checked_Multi_Pointer_Type {
    Checked_Type super;
    Checked_Type *item_type;
} Checked_Multi_Pointer_Type;

Checked_Multi_Pointer_Type *Checked_Multi_Pointer_Type__create(Source_Location location, Checked_Type *item_type);

typedef struct Checked_Pointer_Type {
    Checked_Type super;
    Checked_Type *other_type;
} Checked_Pointer_Type;

Checked_Pointer_Type *Checked_Pointer_Type__create(Source_Location location, Checked_Type *other_type);

typedef struct Checked_Struct_Member {
    Source_Location location;
    String *name;
    Checked_Type *type;
    struct Checked_Struct_Member *next_member;
} Checked_Struct_Member;

Checked_Struct_Member *Checked_Struct_Member__create(Source_Location location, String *name, Checked_Type *type);

typedef struct Checked_Struct_Type {
    Checked_Named_Type super;
    Checked_Struct_Member *first_member;
    Parsed_Struct_Type_Specifier *parsed_type_specifier;
} Checked_Struct_Type;

Checked_Struct_Type *Checked_Struct_Type__create(Source_Location location, String *name, Checked_Module *module, Parsed_Struct_Type_Specifier *parsed_type_specifier);

Checked_Struct_Member *Checked_Struct_Type__find_member(Checked_Struct_Type *self, String *name);

typedef struct Checked_Trait_Method {
    Source_Location location;
    String *name;
    Checked_Procedure_Type *procedure_type;
    Checked_Struct_Member *struct_member;
    struct Checked_Trait_Method *next_method;
} Checked_Trait_Method;

Checked_Trait_Method *Checked_Trait_Method__create(Source_Location location, String *name, Checked_Procedure_Type *procedure_type, Checked_Struct_Member *struct_member);

typedef struct Checked_Trait_Type {
    Checked_Named_Type super;
    Checked_Struct_Type *struct_type;
    Checked_Struct_Member *self_struct_member;
    Checked_Trait_Method *first_method;
} Checked_Trait_Type;

Checked_Trait_Type *Checked_Trait_Type__create(Source_Location location, String *name, Checked_Module *module);

typedef struct Checked_Union_Variant {
    Checked_Type *type;
    int32_t index;
    struct Checked_Union_Variant *next_variant;
} Checked_Union_Variant;

Checked_Union_Variant *Checked_Union_Variant__create(Source_Location location, Checked_Type *type, int32_t index);

typedef struct Checked_Union_Type {
    Checked_Named_Type super;
    Checked_Union_Variant *first_variant;
    int32_t variant_count;
} Checked_Union_Type;

Checked_Union_Type *Checked_Union_Type__create(Source_Location location, String *name, Checked_Module *module);

bool Checked_Type__equals(Checked_Type *self, Checked_Type *other);

void pWriter__write__checked_type(Writer *writer, Checked_Type *type);

typedef enum Checked_Symbol_Kind {
    CHECKED_SYMBOL_KIND__ENUM_MEMBER,
    CHECKED_SYMBOL_KIND__EXTERNAL,
    CHECKED_SYMBOL_KIND__GENERIC_PROCEDURE,
    CHECKED_SYMBOL_KIND__IMPORT,
    CHECKED_SYMBOL_KIND__PROCEDURE_PARAMETER,
    CHECKED_SYMBOL_KIND__PROCEDURE,
    CHECKED_SYMBOL_KIND__TYPE,
    CHECKED_SYMBOL_KIND__TYPE_ARGUMENT,
    CHECKED_SYMBOL_KIND__UNION_SWITCH_VARIANT,
    CHECKED_SYMBOL_KIND__VARIABLE,
} Checked_Symbol_Kind;

typedef struct Checked_Symbol {
    Checked_Symbol_Kind kind;
    Checked_Module *module;
    Source_Location location;
    String *name;
    Checked_Type *type;
    bool is_global;
    struct Checked_Symbol *prev_symbol;
    struct Checked_Symbol *next_symbol;
} Checked_Symbol;

Checked_Symbol *Checked_Symbol__create_kind(Checked_Symbol_Kind kind, size_t kind_size, Checked_Module *module, Source_Location location, String *name, Checked_Type *type, bool is_global);

typedef struct Checked_Enum_Member_Symbol {
    Checked_Symbol super;
} Checked_Enum_Member_Symbol;

Checked_Enum_Member_Symbol *Checked_Enum_Member_Symbol__create(Checked_Module *module, Source_Location location, String *name, Checked_Type *type);

typedef struct Checked_External_Symbol {
    Checked_Symbol super;
    Checked_Symbol *other_symbol;
} Checked_External_Symbol;

Checked_External_Symbol *Checked_External_Symbol__create(Source_Location location, String *name, Checked_Symbol *other_symbol);

typedef struct Checked_Generic_Procedure_Symbol {
    Checked_Symbol super;
    Checked_Type *receiver_type;
    Parsed_Procedure_Statement *parsed_procedure_statement;
} Checked_Generic_Procedure_Symbol;

Checked_Generic_Procedure_Symbol *Checked_Generic_Procedure_Symbol__create(Checked_Module *module, Source_Location location, String *name, Checked_Type *receiver_type, Parsed_Procedure_Statement *parsed_procedure_statement);

typedef struct Checked_Import_Symbol {
    Checked_Symbol super;
    Checked_Module *other_module;
} Checked_Import_Symbol;

Checked_Import_Symbol *Checked_Import_Symbol__create(Checked_Module *module, Source_Location location, String *name, Checked_Type *type, Checked_Module *other_module);

typedef enum Checked_Statement_Kind {
    CHECKED_STATEMENT_KIND__ASSIGNMENT,
    CHECKED_STATEMENT_KIND__BLOCK,
    CHECKED_STATEMENT_KIND__BREAK,
    CHECKED_STATEMENT_KIND__DECOMPOSED,
    CHECKED_STATEMENT_KIND__EXPRESSION,
    CHECKED_STATEMENT_KIND__IF,
    CHECKED_STATEMENT_KIND__LOOP,
    CHECKED_STATEMENT_KIND__RETURN,
    CHECKED_STATEMENT_KIND__UNION_IF,
    CHECKED_STATEMENT_KIND__UNION_SWITCH,
    CHECKED_STATEMENT_KIND__VARIABLE,
    CHECKED_STATEMENT_KIND__WHILE
} Checked_Statement_Kind;

typedef struct Checked_Statement {
    Checked_Statement_Kind kind;
    Source_Location location;
    struct Checked_Statement *next_statement;
} Checked_Statement;

Checked_Statement *Checked_Statement__create_kind(Checked_Statement_Kind kind, size_t kind_size, Source_Location location);

typedef struct Checked_Statements {
    Checked_Statement *first_statement;
    Checked_Statement *last_statement;
} Checked_Statements;

Checked_Statements *Checked_Statements__create();

Checked_Statements *Checked_Statements__create_copy(Checked_Statements *other);

void Checked_Statements__append(Checked_Statements *self, Checked_Statement *statement);

typedef struct Checked_Procedure_Symbol {
    Checked_Symbol super;
    Source_Location procedure_location;
    Parsed_Procedure_Statement *parsed_procedure_statement;
    Checked_Type_Argument *first_type_argument;
    String *procedure_name;
    Checked_Procedure_Type *procedure_type;
    Checked_Type *receiver_type;
    Checked_Statements *checked_statements;
    String *external_name;
} Checked_Procedure_Symbol;

Checked_Procedure_Symbol *Checked_Procedure_Symbol__create(Checked_Module *module, Source_Location location, String *symbol_name, Source_Location procedure_location, Parsed_Procedure_Statement *parsed_procedure_statement, Checked_Procedure_Type *procedure_type, Checked_Type *receiver_type);

void pWriter__write__checked_procedure_symbol(Writer *writer, Checked_Procedure_Symbol *procedure_symbol);

typedef struct Checked_Procedure_Parameter_Symbol {
    Checked_Symbol super;
} Checked_Procedure_Parameter_Symbol;

Checked_Procedure_Parameter_Symbol *Checked_Procedure_Parameter_Symbol__create(Checked_Module *module, Source_Location location, String *name, Checked_Type *type);

typedef struct Checked_Type_Symbol {
    Checked_Symbol super;
    Checked_Named_Type *named_type;
} Checked_Type_Symbol;

Checked_Type_Symbol *Checked_Type_Symbol__create(Checked_Module *module, Source_Location location, String *name, Checked_Type *type, Checked_Named_Type *named_type);

typedef struct Checked_Type_Argument_Symbol {
    Checked_Symbol super;
    Checked_Type *argument_type;
} Checked_Type_Argument_Symbol;

Checked_Type_Argument_Symbol *Checked_Type_Argument_Symbol__create(Source_Location location, String *name, Checked_Type *type, Checked_Type *argument_type);

struct Checked_Variable_Statement;

typedef struct Checked_Variable_Symbol {
    Checked_Symbol super;
    String *external_name;
    struct Checked_Variable_Statement *statement;
} Checked_Variable_Symbol;

Checked_Variable_Symbol *Checked_Variable_Symbol__create(Checked_Module *module, Source_Location location, String *name, Checked_Type *type, bool is_global);

typedef struct Checked_Union_Switch_Variant_Symbol {
    Checked_Symbol super;
    Checked_Expression *union_expression;
    Checked_Union_Variant *union_variant;
} Checked_Union_Switch_Variant_Symbol;

Checked_Union_Switch_Variant_Symbol *Checked_Union_Switch_Variant_Symbol__create(Checked_Module *module, Source_Location location, String *name, Checked_Expression *union_expression, Checked_Union_Variant *union_variant);

typedef struct Checked_Symbols {
    struct Checked_Symbols *parent;
    Checked_Symbol *first_symbol;
    Checked_Symbol *last_symbol;
} Checked_Symbols;

Checked_Symbols *Checked_Symbols__create(Checked_Symbols *parent);

Checked_Symbol *Checked_Symbols__find_sibling_symbol(Checked_Symbols *self, Checked_Module *module, String *name);

void Checked_Symbols__append_symbol(Checked_Symbols *self, Checked_Symbol *symbol);

Checked_Symbol *Checked_Symbols__find_symbol(Checked_Symbols *self, Checked_Module *module, String *name);

Checked_Expression *Checked_Expression__create_kind(Checked_Expression_Kind kind, size_t kind_size, Source_Location location, Checked_Type *type);

typedef struct Checked_Alloc_Expression {
    Checked_Expression super;
    Checked_Expression *value_expression;
} Checked_Alloc_Expression;

Checked_Alloc_Expression *Checked_Alloc_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *value_expression);

typedef struct Checked_Binary_Expression {
    Checked_Expression super;
    Checked_Expression *left_expression;
    Checked_Expression *right_expression;
} Checked_Binary_Expression;

Checked_Binary_Expression *Checked_Binary_Expression__create_kind(Checked_Expression_Kind kind, Source_Location location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression);

typedef struct Checked_Unary_Expression {
    Checked_Expression super;
    Checked_Expression *other_expression;
} Checked_Unary_Expression;

Checked_Unary_Expression *Checked_Unary_Expression__create_kind(Checked_Expression_Kind kind, size_t kind_size, Source_Location location, Checked_Type *type, Checked_Expression *other_expression);

typedef struct Checked_Add_Expression {
    Checked_Binary_Expression super;
} Checked_Add_Expression;

Checked_Add_Expression *Checked_Add_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression);

typedef struct Checked_Address_Of_Expression {
    Checked_Unary_Expression super;
} Checked_Address_Of_Expression;

Checked_Address_Of_Expression *Checked_Address_Of_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *other_expression);

typedef struct Checked_Array_Access_Expression {
    Checked_Expression super;
    Checked_Expression *array_expression;
    Checked_Expression *index_expression;
} Checked_Array_Access_Expression;

Checked_Array_Access_Expression *Checked_Array_Access_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *array_expression, Checked_Expression *index_expression);

typedef struct Checked_Bool_Expression {
    Checked_Expression super;
    bool value;
} Checked_Bool_Expression;

Checked_Bool_Expression *Checked_Bool_Expression__create(Source_Location location, Checked_Type *type, bool value);

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

Checked_Call_Expression *Checked_Call_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *callee_expression, Checked_Call_Argument *first_argument);

typedef struct Checked_Cast_Expression {
    Checked_Expression super;
    Checked_Expression *other_expression;
} Checked_Cast_Expression;

Checked_Cast_Expression *Checked_Cast_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *other_expression);

typedef struct Checked_Character_Expression {
    Checked_Expression super;
    char value;
} Checked_Character_Expression;

Checked_Character_Expression *Checked_Character_Expression__create(Source_Location location, Checked_Type *type, char value);

typedef struct Checked_Dereference_Expression {
    Checked_Unary_Expression super;
} Checked_Dereference_Expression;

Checked_Dereference_Expression *Checked_Dereference_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *other_expression);

typedef struct Checked_Divide_Expression {
    Checked_Binary_Expression super;
} Checked_Divide_Expression;

Checked_Divide_Expression *Checked_Divide_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression);

typedef struct Checked_Equals_Expression {
    Checked_Binary_Expression super;
} Checked_Equals_Expression;

Checked_Equals_Expression *Checked_Equals_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression);

typedef struct Checked_Greater_Expression {
    Checked_Binary_Expression super;
} Checked_Greater_Expression;

Checked_Greater_Expression *Checked_Greater_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression);

typedef struct Checked_Greater_Or_Equals_Expression {
    Checked_Binary_Expression super;
} Checked_Greater_Or_Equals_Expression;

Checked_Greater_Or_Equals_Expression *Checked_Greater_Or_Equals_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression);

typedef struct Checked_Group_Expression {
    Checked_Expression super;
    Checked_Expression *other_expression;
} Checked_Group_Expression;

Checked_Group_Expression *Checked_Group_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *other_expression);

typedef struct Checked_Integer_Expression {
    Checked_Expression super;
    uint64_t value;
    int32_t base;
} Checked_Integer_Expression;

Checked_Integer_Expression *Checked_Integer_Expression__create(Source_Location location, Checked_Type *type, uint64_t value, int32_t base);

typedef struct Checked_Is_Union_Variant_Expression {
    Checked_Expression super;
    Checked_Expression *union_expression;
    Checked_Union_Variant *union_variant;
    bool is_not;
} Checked_Is_Union_Variant_Expression;

Checked_Is_Union_Variant_Expression *Checked_Is_Union_Variant_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *union_expression, Checked_Union_Variant *union_variant, bool is_not);

typedef struct Checked_Less_Expression {
    Checked_Binary_Expression super;
} Checked_Less_Expression;

Checked_Less_Expression *Checked_Less_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression);

typedef struct Checked_Less_Or_Equals_Expression {
    Checked_Binary_Expression super;
} Checked_Less_Or_Equals_Expression;

Checked_Less_Or_Equals_Expression *Checked_Less_Or_Equals_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression);

typedef struct Checked_Logic_And_Expression {
    Checked_Binary_Expression super;
} Checked_Logic_And_Expression;

Checked_Logic_And_Expression *Checked_Logic_And_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression);

typedef struct Checked_Logic_Or_Expression {
    Checked_Binary_Expression super;
} Checked_Logic_Or_Expression;

Checked_Logic_Or_Expression *Checked_Logic_Or_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression);

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

Checked_Make_Struct_Expression *Checked_Make_Struct_Expression__create(Source_Location location, Checked_Type *type, Checked_Struct_Type *struct_type, Checked_Make_Struct_Argument *first_argument);

typedef struct Checked_Make_Union_Expression {
    Checked_Expression super;
    Checked_Union_Type *union_type;
    Checked_Union_Variant *union_variant;
    Checked_Expression *expression;
} Checked_Make_Union_Expression;

Checked_Make_Union_Expression *Checked_Make_Union_Expression__create(Source_Location location, Checked_Type *type, Checked_Union_Type *union_type, Checked_Union_Variant *union_variant, Checked_Expression *expression);

typedef struct Checked_Member_Access_Expression {
    Checked_Expression super;
    Checked_Expression *object_expression;
    Checked_Struct_Member *member;
} Checked_Member_Access_Expression;

Checked_Member_Access_Expression *Checked_Member_Access_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *object_expression, Checked_Struct_Member *member);

typedef struct Checked_Receiver_Method_Expression {
    Checked_Expression super;
    Checked_Expression *receiver_expression;
    Checked_Expression *procedure_expression;
    Checked_Procedure_Type *procedure_type;
} Checked_Receiver_Method_Expression;

Checked_Receiver_Method_Expression *Checked_Receiver_Method_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *receiver_expression, Checked_Expression *procedure_expression, Checked_Procedure_Type *procedure_type);

typedef struct Checked_Minus_Expression {
    Checked_Unary_Expression super;
} Checked_Minus_Expression;

Checked_Minus_Expression *Checked_Minus_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *other_expression);

typedef struct Checked_Modulo_Expression {
    Checked_Binary_Expression super;
} Checked_Modulo_Expression;

Checked_Modulo_Expression *Checked_Modulo_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression);

typedef struct Checked_Multiply_Expression {
    Checked_Binary_Expression super;
} Checked_Multiply_Expression;

Checked_Multiply_Expression *Checked_Multiply_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression);

typedef struct Checked_Not_Expression {
    Checked_Unary_Expression super;
} Checked_Not_Expression;

Checked_Not_Expression *Checked_Not_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *other_expression);

typedef struct Checked_Not_Equals_Expression {
    Checked_Binary_Expression super;
} Checked_Not_Equals_Expression;

Checked_Not_Equals_Expression *Checked_Not_Equals_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression);

typedef struct Checked_Null_Expression {
    Checked_Expression super;
} Checked_Null_Expression;

Checked_Null_Expression *Checked_Null_Expression__create(Source_Location location, Checked_Type *type);

typedef struct Checked_Sizeof_Expression {
    Checked_Expression super;
    Checked_Type *sized_type;
} Checked_Sizeof_Expression;

Checked_Sizeof_Expression *Checked_Sizeof_Expression__create(Source_Location location, Checked_Type *type, Checked_Type *sized_type);

typedef struct Checked_String_Expression {
    Checked_Expression super;
    String *value;
} Checked_String_Expression;

Checked_String_Expression *Checked_String_Expression__create(Source_Location location, Checked_Type *type, String *value);

typedef struct Checked_String_Length_Expression {
    Checked_Expression super;
    Checked_Expression *string_expression;
} Checked_String_Length_Expression;

Checked_String_Length_Expression *Checked_String_Length_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *string_expression);

typedef struct Checked_Subtract_Expression {
    Checked_Binary_Expression super;
} Checked_Subtract_Expression;

Checked_Subtract_Expression *Checked_Subtract_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression);

typedef struct Checked_Symbol_Expression {
    Checked_Expression super;
    Checked_Symbol *symbol;
} Checked_Symbol_Expression;

Checked_Symbol_Expression *Checked_Symbol_Expression__create(Source_Location location, Checked_Type *type, Checked_Symbol *symbol);

typedef struct Checked_Type_Expression {
    Checked_Expression super;
    Checked_Named_Type *named_type;
} Checked_Type_Expression;

Checked_Type_Expression *Checked_Type_Expression__create(Source_Location location, Checked_Type *type, Checked_Named_Type *named_type);

typedef struct Checked_Assignment_Statement {
    Checked_Statement super;
    Checked_Expression *object_expression;
    Checked_Expression *value_expression;
} Checked_Assignment_Statement;

Checked_Assignment_Statement *Checked_Assignment_Statement__create(Source_Location location, Checked_Expression *object_expression, Checked_Expression *value_expression);

typedef struct Checked_Block_Statement {
    Checked_Statement super;
    Checked_Statements *statements;
} Checked_Block_Statement;

Checked_Block_Statement *Checked_Block_Statement__create(Source_Location location, Checked_Statements *statements);

typedef struct Checked_Break_Statement {
    Checked_Statement super;
} Checked_Break_Statement;

Checked_Break_Statement *Checked_Break_Statement__create(Source_Location location);

typedef struct Checked_Decomposed_Statement {
    Checked_Statement super;
    Checked_Statements *statements;
} Checked_Decomposed_Statement;

Checked_Decomposed_Statement *Checked_Decomposed_Statement__create(Source_Location location, Checked_Statements *statements);

typedef struct Checked_Expression_Statement {
    Checked_Statement super;
    Checked_Expression *expression;
} Checked_Expression_Statement;

Checked_Expression_Statement *Checked_Expression_Statement__create(Source_Location location, Checked_Expression *expression);

typedef struct Checked_If_Statement {
    Checked_Statement super;
    Checked_Expression *condition_expression;
    Checked_Statement *true_statement;
    Checked_Statement *false_statement;
} Checked_If_Statement;

Checked_If_Statement *Checked_If_Statement__create(Source_Location location, Checked_Expression *condition_expression, Checked_Statement *true_statement, Checked_Statement *false_statement);

typedef struct Checked_Loop_Statement {
    Checked_Statement super;
    Checked_Statement *body_statement;
} Checked_Loop_Statement;

Checked_Loop_Statement *Checked_Loop_Statement__create(Source_Location location, Checked_Statement *body_statement);

typedef struct Checked_Return_Statement {
    Checked_Statement super;
    Checked_Expression *expression;
} Checked_Return_Statement;

Checked_Return_Statement *Checked_Return_Statement__create(Source_Location location, Checked_Expression *expression);

typedef struct Checked_Union_If_Statement {
    Checked_Statement super;
    Checked_Expression *union_expression;
    Checked_Union_Variant *union_variant;
    Checked_Statement *true_statement;
    Checked_Statement *false_statement;
} Checked_Union_If_Statement;

Checked_Union_If_Statement *Checked_Union_If_Statement__create(Source_Location location, Checked_Expression *union_expression, Checked_Union_Variant *union_variant, Checked_Statement *true_statement, Checked_Statement *false_statement);

typedef struct Checked_Switch_Else {
    Source_Location location;
    Checked_Statement *statement;
} Checked_Switch_Else;

Checked_Switch_Else *Checked_Switch_Else__create(Source_Location location, Checked_Statement *statement);

typedef struct Checked_Union_Switch_Case {
    Source_Location location;
    Checked_Union_Type *union_type;
    Checked_Union_Variant *union_variant;
    Checked_Statement *statement;
    struct Checked_Union_Switch_Case *next_union_switch_case;
} Checked_Union_Switch_Case;

Checked_Union_Switch_Case *Checked_Union_Switch_Case__create(Source_Location location, Checked_Union_Type *union_type, Checked_Union_Variant *union_variant, Checked_Statement *statement);

typedef struct Checked_Union_Switch_Statement {
    Checked_Statement super;
    Checked_Expression *expression;
    Checked_Union_Switch_Case *first_union_switch_case;
    Checked_Switch_Else *switch_else;
} Checked_Union_Switch_Statement;

Checked_Union_Switch_Statement *Checked_Union_Switch_Statement__create(Source_Location location, Checked_Expression *expression, Checked_Union_Switch_Case *first_union_switch_case, Checked_Switch_Else *switch_else);

typedef struct Checked_Variable_Statement {
    Checked_Statement super;
    Checked_Variable_Symbol *variable;
    bool is_external;
    Checked_Expression *expression;
} Checked_Variable_Statement;

Checked_Variable_Statement *Checked_Variable_Statement__create(Source_Location location, Checked_Variable_Symbol *variable, bool is_external, Checked_Expression *expression);

typedef struct Checked_While_Statement {
    Checked_Statement super;
    Checked_Expression *condition_expression;
    Checked_Statement *body_statement;
} Checked_While_Statement;

Checked_While_Statement *Checked_While_Statement__create(Source_Location location, Checked_Expression *condition_expression, Checked_Statement *body_statement);

typedef struct Checked_Source {
    Checked_Module *first_module;
    struct Checked_Symbols *symbols;
} Checked_Source;

#endif
