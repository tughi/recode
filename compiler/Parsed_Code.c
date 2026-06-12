#include "Parsed_Code.h"

Parsed_Type *Parsed_Type__create_kind(Parsed_Type_Kind kind, size_t kind_size, Source_Location location) {
    Parsed_Type *type = (Parsed_Type *)malloc(kind_size);
    type->kind = kind;
    type->location = location;
    return type;
}

Parsed_Array_Type *Parsed_Array_Type__create(Source_Location location, Parsed_Type *item_type, Integer_Token *length_literal) {
    Parsed_Array_Type *type = (Parsed_Array_Type *)Parsed_Type__create_kind(PARSED_TYPE_KIND__ARRAY, sizeof(Parsed_Array_Type), location);
    type->item_type = item_type;
    type->length_literal = length_literal;
    return type;
}

Parsed_Procedure_Parameter *Parsed_Procedure_Parameter__create(Token *label, Token *name, Parsed_Type *type) {
    Parsed_Procedure_Parameter *parameter = (Parsed_Procedure_Parameter *)malloc(sizeof(Parsed_Procedure_Parameter));
    parameter->label = label;
    parameter->name = name;
    parameter->type = type;
    parameter->next_parameter = NULL;
    return parameter;
}

Parsed_Type *Parsed_Procedure_Type__create(Source_Location location, Parsed_Procedure_Parameter *first_parameter, Parsed_Type *return_type, Parsed_Type *raise_type) {
    Parsed_Procedure_Type *type = (Parsed_Procedure_Type *)Parsed_Type__create_kind(PARSED_TYPE_KIND__PROCEDURE, sizeof(Parsed_Procedure_Type), location);
    type->first_parameter = first_parameter;
    type->return_type = return_type;
    type->raise_type = raise_type;
    return (Parsed_Type *)type;
}

Parsed_Type *Parsed_Multi_Pointer_Type__create(Source_Location location, Parsed_Type *item_type) {
    Parsed_Multi_Pointer_Type *type = (Parsed_Multi_Pointer_Type *)Parsed_Type__create_kind(PARSED_TYPE_KIND__MULTI_POINTER, sizeof(Parsed_Multi_Pointer_Type), location);
    type->item_type = item_type;
    return (Parsed_Type *)type;
}

Parsed_Type_Argument *Parsed_Type_Argument__create(Parsed_Type *type) {
    Parsed_Type_Argument *type_argument = (Parsed_Type_Argument *)malloc(sizeof(Parsed_Type_Argument));
    type_argument->type = type;
    type_argument->next_type_argument = NULL;
    return type_argument;
}

Parsed_Named_Type *Parsed_Named_Type__create(Token *package, Token *name) {
    Source_Location location = name->location;
    if (package != NULL) {
        location = Source_Location__merge(package->location, name->location);
    }
    Parsed_Named_Type *type = (Parsed_Named_Type *)Parsed_Type__create_kind(PARSED_TYPE_KIND__NAMED, sizeof(Parsed_Named_Type), location);
    type->package = package;
    type->name = name->lexeme;
    type->first_type_argument = NULL;
    return type;
}

Parsed_Optional_Type *Parsed_Optional_Type__create(Source_Location location, Parsed_Type *inner_type) {
    Parsed_Optional_Type *type = (Parsed_Optional_Type *)Parsed_Type__create_kind(PARSED_TYPE_KIND__OPTIONAL, sizeof(Parsed_Optional_Type), location);
    type->inner_type = inner_type;
    return type;
}

Parsed_Type *Parsed_Pointer_Type__create(Source_Location location, Parsed_Type *other_type) {
    Parsed_Pointer_Type *type = (Parsed_Pointer_Type *)Parsed_Type__create_kind(PARSED_TYPE_KIND__POINTER, sizeof(Parsed_Pointer_Type), location);
    type->other_type = other_type;
    return (Parsed_Type *)type;
}

Parsed_Receiver_Type *Parsed_Receiver_Type__create(Source_Location location) {
    return (Parsed_Receiver_Type *)Parsed_Type__create_kind(PARSED_TYPE_KIND__RECEIVER, sizeof(Parsed_Receiver_Type), location);
}

Parsed_Expression *Parsed_Expression__create_kind(Parsed_Expression_Kind kind, size_t kind_size, Source_Location location) {
    Parsed_Expression *expression = (Parsed_Expression *)malloc(kind_size);
    expression->kind = kind;
    expression->location = location;
    return expression;
}

Parsed_Alloc_Expression *Parsed_Alloc_Expression__create(Source_Location location, Parsed_Expression *value_expression) {
    Parsed_Alloc_Expression *expression = (Parsed_Alloc_Expression *)Parsed_Expression__create_kind(PARSED_EXPRESSION_KIND__ALLOC, sizeof(Parsed_Alloc_Expression), location);
    expression->value_expression = value_expression;
    return expression;
}

Parsed_Binary_Expression *Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind kind, Parsed_Expression *left_expression, Parsed_Expression *right_expression) {
    Parsed_Binary_Expression *expression = (Parsed_Binary_Expression *)Parsed_Expression__create_kind(kind, sizeof(Parsed_Binary_Expression), Source_Location__merge(left_expression->location, right_expression->location));
    expression->left_expression = left_expression;
    expression->right_expression = right_expression;
    return expression;
}

Parsed_Unary_Expression *Parsed_Unary_Expression__create_kind(Parsed_Expression_Kind kind, size_t kind_size, Source_Location location, Parsed_Expression *other_expression) {
    Parsed_Unary_Expression *expression = (Parsed_Unary_Expression *)Parsed_Expression__create_kind(kind, kind_size, location);
    expression->other_expression = other_expression;
    return expression;
}

Parsed_Literal_Expression *Parsed_Literal_Expression__create_kind(Parsed_Expression_Kind kind, size_t kind_size, Token *literal) {
    Parsed_Literal_Expression *expression = (Parsed_Literal_Expression *)Parsed_Expression__create_kind(kind, kind_size, literal->location);
    expression->literal = literal;
    return expression;
}

Parsed_Add_Expression *Parsed_Add_Expression__create(Parsed_Expression *left_expression, Parsed_Expression *right_expression) {
    return (Parsed_Add_Expression *)Parsed_Binary_Expression__create_kind(PARSED_EXPRESSION_KIND__ADD, left_expression, right_expression);
}

Parsed_Address_Of_Expression *Parsed_Address_Of_Expression__create(Source_Location location, Parsed_Expression *other_expression) {
    return (Parsed_Address_Of_Expression *)Parsed_Unary_Expression__create_kind(PARSED_EXPRESSION_KIND__ADDRESS_OF, sizeof(Parsed_Address_Of_Expression), location, other_expression);
}

Parsed_Array_Access_Expression *Parsed_Array_Access_Expression__create(Source_Location location, Parsed_Expression *array_expression, Parsed_Expression *index_expression) {
    Parsed_Array_Access_Expression *expression = (Parsed_Array_Access_Expression *)Parsed_Expression__create_kind(PARSED_EXPRESSION_KIND__ARRAY_ACCESS, sizeof(Parsed_Array_Access_Expression), location);
    expression->array_expression = array_expression;
    expression->index_expression = index_expression;
    return expression;
}

Parsed_Bool_Expression *Parsed_Bool_Expression__create(Token *literal, bool value) {
    Parsed_Bool_Expression *expression = (Parsed_Bool_Expression *)Parsed_Literal_Expression__create_kind(PARSED_EXPRESSION_KIND__BOOL, sizeof(Parsed_Bool_Expression), literal);
    expression->value = value;
    return expression;
}

Parsed_Call_Argument *Parsed_Call_Argument__create(Source_Location location, Identifier_Token *name, Parsed_Expression *expression) {
    Parsed_Call_Argument *argument = (Parsed_Call_Argument *)malloc(sizeof(Parsed_Call_Argument));
    argument->location = location;
    argument->name = name;
    argument->expression = expression;
    argument->next_argument = NULL;
    return argument;
}

Parsed_Call_Expression *Parsed_Call_Expression__create(Source_Location location, Parsed_Expression *callee_expression, Parsed_Call_Argument *first_argument) {
    Parsed_Call_Expression *expression = (Parsed_Call_Expression *)Parsed_Expression__create_kind(PARSED_EXPRESSION_KIND__CALL, sizeof(Parsed_Call_Expression), location);
    expression->callee_expression = callee_expression;
    expression->first_argument = first_argument;
    return expression;
}

Parsed_Cast_Expression *Parsed_Cast_Expression__create(Source_Location location, Parsed_Expression *other_expression, Parsed_Type *type) {
    Parsed_Cast_Expression *expression = (Parsed_Cast_Expression *)Parsed_Unary_Expression__create_kind(PARSED_EXPRESSION_KIND__CAST, sizeof(Parsed_Cast_Expression), location, other_expression);
    expression->type = type;
    return expression;
}

Parsed_Character_Expression *Parsed_Character_Expression__create(Character_Token *literal) {
    Parsed_Character_Expression *expression = (Parsed_Character_Expression *)Parsed_Literal_Expression__create_kind(PARSED_EXPRESSION_KIND__CHARACTER, sizeof(Parsed_Character_Expression), (Token *)literal);
    expression->value = literal->value;
    return expression;
}

Parsed_Dereference_Expression *Parsed_Dereference_Expression__create(Source_Location location, Parsed_Expression *other_expression) {
    return (Parsed_Dereference_Expression *)Parsed_Unary_Expression__create_kind(PARSED_EXPRESSION_KIND__DEREFERENCE, sizeof(Parsed_Dereference_Expression), location, other_expression);
}

Parsed_Divide_Expression *Parsed_Divide_Expression__create(Parsed_Expression *left_expression, Parsed_Expression *right_expression) {
    return (Parsed_Divide_Expression *)Parsed_Binary_Expression__create_kind(PARSED_EXPRESSION_KIND__DIVIDE, left_expression, right_expression);
}

Parsed_Equals_Expression *Parsed_Equals_Expression__create(Parsed_Expression *left_expression, Parsed_Expression *right_expression) {
    return (Parsed_Equals_Expression *)Parsed_Binary_Expression__create_kind(PARSED_EXPRESSION_KIND__EQUALS, left_expression, right_expression);
}

Parsed_Greater_Expression *Parsed_Greater_Expression__create(Parsed_Expression *left_expression, Parsed_Expression *right_expression) {
    return (Parsed_Greater_Expression *)Parsed_Binary_Expression__create_kind(PARSED_EXPRESSION_KIND__GREATER, left_expression, right_expression);
}

Parsed_Greater_Or_Equals_Expression *Parsed_Greater_Or_Equals_Expression__create(Parsed_Expression *left_expression, Parsed_Expression *right_expression) {
    return (Parsed_Greater_Or_Equals_Expression *)Parsed_Binary_Expression__create_kind(PARSED_EXPRESSION_KIND__GREATER_OR_EQUALS, left_expression, right_expression);
}

Parsed_Group_Expression *Parsed_Group_Expression__create(Source_Location location, Parsed_Expression *other_expression) {
    Parsed_Group_Expression *expression = (Parsed_Group_Expression *)Parsed_Expression__create_kind(PARSED_EXPRESSION_KIND__GROUP, sizeof(Parsed_Group_Expression), location);
    expression->other_expression = other_expression;
    return expression;
}

Parsed_Integer_Expression *Parsed_Integer_Expression__create(Integer_Token *literal, Parsed_Named_Type *type) {
    Parsed_Integer_Expression *expression = (Parsed_Integer_Expression *)Parsed_Literal_Expression__create_kind(PARSED_EXPRESSION_KIND__INTEGER, sizeof(Parsed_Integer_Expression), (Token *)literal);
    expression->value = literal->value;
    expression->base = literal->base;
    expression->type = type;
    return expression;
}

Parsed_Is_Expression *Parsed_Is_Expression__create(Parsed_Expression *value_expression, Parsed_Type *runtime_type, bool is_not, Identifier_Token *alias) {
    Parsed_Is_Expression *expression = (Parsed_Is_Expression *)Parsed_Expression__create_kind(PARSED_EXPRESSION_KIND__IS, sizeof(Parsed_Is_Expression), Source_Location__merge(value_expression->location, runtime_type->location));
    expression->value_expression = value_expression;
    expression->runtime_type = runtime_type;
    expression->is_not = is_not;
    expression->alias = alias;
    return expression;
}

Parsed_Less_Expression *Parsed_Less_Expression__create(Parsed_Expression *left_expression, Parsed_Expression *right_expression) {
    return (Parsed_Less_Expression *)Parsed_Binary_Expression__create_kind(PARSED_EXPRESSION_KIND__LESS, left_expression, right_expression);
}

Parsed_Less_Or_Equals_Expression *Parsed_Less_Or_Equals_Expression__create(Parsed_Expression *left_expression, Parsed_Expression *right_expression) {
    return (Parsed_Less_Or_Equals_Expression *)Parsed_Binary_Expression__create_kind(PARSED_EXPRESSION_KIND__LESS_OR_EQUALS, left_expression, right_expression);
}

Parsed_Logic_And_Expression *Parsed_Logic_And_Expression__create(Parsed_Expression *left_expression, Parsed_Expression *right_expression) {
    return (Parsed_Logic_And_Expression *)Parsed_Binary_Expression__create_kind(PARSED_EXPRESSION_KIND__LOGIC_AND, left_expression, right_expression);
}

Parsed_Logic_Or_Expression *Parsed_Logic_Or_Expression__create(Parsed_Expression *left_expression, Parsed_Expression *right_expression) {
    return (Parsed_Logic_Or_Expression *)Parsed_Binary_Expression__create_kind(PARSED_EXPRESSION_KIND__LOGIC_OR, left_expression, right_expression);
}

Parsed_Make_Array_Expression *Parsed_Make_Array_Expression__create(Source_Location location, Parsed_Type *array_type, Parsed_Call_Argument *first_argument) {
    Parsed_Make_Array_Expression *expression = (Parsed_Make_Array_Expression *)Parsed_Expression__create_kind(PARSED_EXPRESSION_KIND__MAKE_ARRAY, sizeof(Parsed_Make_Array_Expression), location);
    expression->array_type = array_type;
    expression->first_argument = first_argument;
    return expression;
}

Parsed_Member_Access_Expression *Parsed_Member_Access_Expression__create(Parsed_Expression *object_expression, Token *member_name) {
    Parsed_Member_Access_Expression *expression = (Parsed_Member_Access_Expression *)Parsed_Expression__create_kind(PARSED_EXPRESSION_KIND__MEMBER_ACCESS, sizeof(Parsed_Member_Access_Expression), Source_Location__merge(object_expression->location, member_name->location));
    expression->object_expression = object_expression;
    expression->member_name = member_name;
    return expression;
}

Parsed_Minus_Expression *Parsed_Minus_Expression__create(Source_Location location, Parsed_Expression *other_expression) {
    return (Parsed_Minus_Expression *)Parsed_Unary_Expression__create_kind(PARSED_EXPRESSION_KIND__MINUS, sizeof(Parsed_Minus_Expression), location, other_expression);
}

Parsed_Modulo_Expression *Parsed_Modulo_Expression__create(Parsed_Expression *left_expression, Parsed_Expression *right_expression) {
    return (Parsed_Modulo_Expression *)Parsed_Binary_Expression__create_kind(PARSED_EXPRESSION_KIND__MODULO, left_expression, right_expression);
}

Parsed_Multiply_Expression *Parsed_Multiply_Expression__create(Parsed_Expression *left_expression, Parsed_Expression *right_expression) {
    return (Parsed_Multiply_Expression *)Parsed_Binary_Expression__create_kind(PARSED_EXPRESSION_KIND__MULTIPLY, left_expression, right_expression);
}

Parsed_Not_Expression *Parsed_Not_Expression__create(Source_Location location, Parsed_Expression *other_expression) {
    return (Parsed_Not_Expression *)Parsed_Unary_Expression__create_kind(PARSED_EXPRESSION_KIND__NOT, sizeof(Parsed_Not_Expression), location, other_expression);
}

Parsed_Not_Equals_Expression *Parsed_Not_Equals_Expression__create(Parsed_Expression *left_expression, Parsed_Expression *right_expression) {
    return (Parsed_Not_Equals_Expression *)Parsed_Binary_Expression__create_kind(PARSED_EXPRESSION_KIND__NOT_EQUALS, left_expression, right_expression);
}

Parsed_Null_Expression *Parsed_Null_Expression__create(Token *literal) {
    return (Parsed_Null_Expression *)Parsed_Literal_Expression__create_kind(PARSED_EXPRESSION_KIND__NULL, sizeof(Parsed_Null_Expression), literal);
}

Parsed_String_Expression *Parsed_String_Expression__create(String_Token *literal) {
    Parsed_String_Expression *expression = (Parsed_String_Expression *)Parsed_Literal_Expression__create_kind(PARSED_EXPRESSION_KIND__STRING, sizeof(Parsed_String_Expression), (Token *)literal);
    expression->value = literal->value;
    return expression;
}

Parsed_Subtract_Expression *Parsed_Subtract_Expression__create(Parsed_Expression *left_expression, Parsed_Expression *right_expression) {
    return (Parsed_Subtract_Expression *)Parsed_Binary_Expression__create_kind(PARSED_EXPRESSION_KIND__SUBTRACT, left_expression, right_expression);
}

Parsed_Symbol_Expression *Parsed_Symbol_Expression__create(Token *name) {
    Parsed_Symbol_Expression *expression = (Parsed_Symbol_Expression *)Parsed_Expression__create_kind(PARSED_EXPRESSION_KIND__SYMBOL, sizeof(Parsed_Symbol_Expression), name->location);
    expression->name = name;
    return expression;
}

Parsed_Try_Expression *Parsed_Try_Expression__create(Source_Location location, Parsed_Expression *expression, Parsed_Expression *else_expression) {
    Parsed_Try_Expression *try_expression = (Parsed_Try_Expression *)Parsed_Expression__create_kind(PARSED_EXPRESSION_KIND__TRY, sizeof(Parsed_Try_Expression), location);
    try_expression->expression = expression;
    try_expression->else_expression = else_expression;
    return try_expression;
}

Parsed_Type_Alignment_Expression *Parsed_Type_Alignment_Expression__create(Source_Location location, Parsed_Type *type) {
    Parsed_Type_Alignment_Expression *expression = (Parsed_Type_Alignment_Expression *)Parsed_Expression__create_kind(PARSED_EXPRESSION_KIND__TYPE_ALIGNMENT, sizeof(Parsed_Type_Alignment_Expression), location);
    expression->type = type;
    return expression;
}

Parsed_Type_Size_Expression *Parsed_Type_Size_Expression__create(Source_Location location, Parsed_Type *type) {
    Parsed_Type_Size_Expression *expression = (Parsed_Type_Size_Expression *)Parsed_Expression__create_kind(PARSED_EXPRESSION_KIND__TYPE_SIZE, sizeof(Parsed_Type_Size_Expression), location);
    expression->type = type;
    return expression;
}

Parsed_Type_Specialization_Expression *Parsed_Type_Specialization_Expression__create(Source_Location location, Parsed_Expression *type_expression, Parsed_Type_Argument *first_type_argument) {
    Parsed_Type_Specialization_Expression *expression = (Parsed_Type_Specialization_Expression *)Parsed_Expression__create_kind(PARSED_EXPRESSION_KIND__TYPE_SPECIALIZATION, sizeof(Parsed_Type_Specialization_Expression), location);
    expression->type_expression = type_expression;
    expression->first_type_argument = first_type_argument;
    return expression;
}

Parsed_Statement *Parsed_Statement__create_kind(Parsed_Statement_Kind kind, size_t kind_size, Source_Location location) {
    Parsed_Statement *statement = (Parsed_Statement *)malloc(kind_size);
    statement->kind = kind;
    statement->location = location;
    statement->next_statement = NULL;
    return statement;
}

Parsed_Named_Statement *Parsed_Named_Statement__create_kind(Parsed_Statement_Kind kind, size_t kind_size, Source_Location location, Token *name) {
    Parsed_Named_Statement *statement = (Parsed_Named_Statement *)Parsed_Statement__create_kind(kind, kind_size, location);
    statement->name = name;
    return statement;
}

Parsed_Assignment_Statement *Parsed_Assignment_Statement__create(Parsed_Expression *object_expression, Parsed_Expression *value_expression) {
    Parsed_Assignment_Statement *statement = (Parsed_Assignment_Statement *)Parsed_Statement__create_kind(PARSED_STATEMENT_KIND__ASSIGNMENT, sizeof(Parsed_Assignment_Statement), Source_Location__merge(object_expression->location, value_expression->location));
    statement->object_expression = object_expression;
    statement->value_expression = value_expression;
    return statement;
}

Parsed_Block_Statement *Parsed_Block_Statement__create(Source_Location location, Parsed_Statements *statements) {
    Parsed_Block_Statement *statement = (Parsed_Block_Statement *)Parsed_Statement__create_kind(PARSED_STATEMENT_KIND__BLOCK, sizeof(Parsed_Block_Statement), location);
    statement->statements = statements;
    return statement;
}

Parsed_Block_Expression *Parsed_Block_Expression__create(struct Parsed_Block_Statement *block_statement) {
    Parsed_Block_Expression *expression = (Parsed_Block_Expression *)Parsed_Expression__create_kind(PARSED_EXPRESSION_KIND__BLOCK, sizeof(Parsed_Block_Expression), block_statement->super.location);
    expression->block_statement = block_statement;
    return expression;
}

Parsed_Statement *Parsed_Break_Statement__create(Source_Location location) {
    return Parsed_Statement__create_kind(PARSED_STATEMENT_KIND__BREAK, sizeof(Parsed_Break_Statement), location);
}

Parsed_Constant_Statement *Parsed_Constant_Statement__create(Source_Location location, Token *name, Parsed_Expression *value_expression) {
    Parsed_Constant_Statement *statement = (Parsed_Constant_Statement *)Parsed_Named_Statement__create_kind(PARSED_STATEMENT_KIND__CONSTANT, sizeof(Parsed_Constant_Statement), location, name);
    statement->value_expression = value_expression;
    return statement;
}

Parsed_Defer_Statement *Parsed_Defer_Statement__create(Source_Location location, Parsed_Statement *statement) {
    Parsed_Defer_Statement *defer_statement = (Parsed_Defer_Statement *)Parsed_Statement__create_kind(PARSED_STATEMENT_KIND__DEFER, sizeof(Parsed_Defer_Statement), location);
    defer_statement->statement = statement;
    return defer_statement;
}

Parsed_Expression_Statement *Parsed_Expression_Statement__create(Parsed_Expression *expression) {
    Parsed_Expression_Statement *statement = (Parsed_Expression_Statement *)Parsed_Statement__create_kind(PARSED_STATEMENT_KIND__EXPRESSION, sizeof(Parsed_Expression_Statement), expression->location);
    statement->expression = expression;
    return statement;
}

Parsed_Statement *Parsed_Procedure_Statement__create(Source_Location location, Token *name, Parsed_Type_Parameter *first_type_parameter, bool is_method, Parsed_Procedure_Parameter *first_parameter, Parsed_Type *return_type, Parsed_Type *raise_type, bool is_external, Parsed_Block_Statement *block_statement, String_Token *external_name) {
    Parsed_Procedure_Statement *statement = (Parsed_Procedure_Statement *)Parsed_Named_Statement__create_kind(PARSED_STATEMENT_KIND__PROCEDURE, sizeof(Parsed_Procedure_Statement), location, name);
    statement->first_type_parameter = first_type_parameter;
    statement->is_method = is_method;
    statement->first_parameter = first_parameter;
    statement->return_type = return_type;
    statement->raise_type = raise_type;
    statement->is_external = is_external;
    statement->block_statement = block_statement;
    statement->external_name = external_name;
    return (Parsed_Statement *)statement;
}

Parsed_Statement *Parsed_Import_Statement__create(Source_Location location, String *import_name, Parsed_Package *parsed_package) {
    Parsed_Import_Statement *statement = (Parsed_Import_Statement *)Parsed_Statement__create_kind(PARSED_STATEMENT_KIND__IMPORT, sizeof(Parsed_Import_Statement), location);
    statement->import_name = import_name;
    statement->parsed_package = parsed_package;
    return (Parsed_Statement *)statement;
}

Parsed_Statement *Parsed_If_Statement__create(Source_Location location, Parsed_Expression *condition_expression, Parsed_Statement *true_statement, Parsed_Statement *false_statement) {
    Parsed_If_Statement *statement = (Parsed_If_Statement *)Parsed_Statement__create_kind(PARSED_STATEMENT_KIND__IF, sizeof(Parsed_If_Statement), location);
    statement->condition_expression = condition_expression;
    statement->true_statement = true_statement;
    statement->false_statement = false_statement;
    return (Parsed_Statement *)statement;
}

Parsed_Statement *Parsed_Loop_Statement__create(Source_Location location, Parsed_Statement *body_statement) {
    Parsed_Loop_Statement *statement = (Parsed_Loop_Statement *)Parsed_Statement__create_kind(PARSED_STATEMENT_KIND__LOOP, sizeof(Parsed_Loop_Statement), location);
    statement->body_statement = body_statement;
    return (Parsed_Statement *)statement;
}

Parsed_Raise_Statement *Parsed_Raise_Statement__create(Source_Location location, Parsed_Expression *expression) {
    Parsed_Raise_Statement *statement = (Parsed_Raise_Statement *)Parsed_Statement__create_kind(PARSED_STATEMENT_KIND__RAISE, sizeof(Parsed_Raise_Statement), location);
    statement->expression = expression;
    return statement;
}

Parsed_Statement *Parsed_Return_Statement__create(Source_Location location, Parsed_Expression *expression) {
    Parsed_Return_Statement *statement = (Parsed_Return_Statement *)Parsed_Statement__create_kind(PARSED_STATEMENT_KIND__RETURN, sizeof(Parsed_Return_Statement), location);
    statement->expression = expression;
    return (Parsed_Statement *)statement;
}

Parsed_Type_Parameter *Parsed_Type_Parameter__create(Token *name) {
    Parsed_Type_Parameter *parameter = (Parsed_Type_Parameter *)malloc(sizeof(Parsed_Type_Parameter));
    parameter->name = name;
    parameter->next_type_parameter = NULL;
    return parameter;
}

Parsed_Type_Statement *Parsed_Type_Statement__create(Source_Location location, Token *name, Parsed_Type_Specifier *type_specifier, Parsed_Type_Parameter *first_type_parameter) {
    Parsed_Type_Statement *statement = (Parsed_Type_Statement *)Parsed_Named_Statement__create_kind(PARSED_STATEMENT_KIND__TYPE, sizeof(Parsed_Type_Statement), location, name);
    statement->type_specifier = type_specifier;
    statement->first_type_parameter = first_type_parameter;
    return statement;
}

Parsed_Switch_Case *Parsed_Switch_Else__create(Source_Location location) {
    Parsed_Switch_Case *switch_else = (Parsed_Switch_Case *)malloc(sizeof(Parsed_Switch_Case));
    switch_else->kind = PARSED_SWITCH_CASE_KIND__ELSE;
    switch_else->location = location;
    switch_else->statement = NULL;
    switch_else->next_case = NULL;
    return switch_else;
}

Parsed_Switch_Case *Parsed_Switch_Expression__create(Source_Location location, Parsed_Expression *expression) {
    Parsed_Switch_Case *switch_case = (Parsed_Switch_Case *)malloc(sizeof(Parsed_Switch_Case));
    switch_case->kind = PARSED_SWITCH_CASE_KIND__EXPRESSION;
    switch_case->location = location;
    switch_case->expression = expression;
    switch_case->statement = NULL;
    switch_case->next_case = NULL;
    return switch_case;
}

Parsed_Switch_Case *Parsed_Switch_Variant__create(Source_Location location, Parsed_Type *type, Identifier_Token *alias) {
    Parsed_Switch_Case *switch_variant = (Parsed_Switch_Case *)malloc(sizeof(Parsed_Switch_Case));
    switch_variant->kind = PARSED_SWITCH_CASE_KIND__VARIANT;
    switch_variant->location = location;
    switch_variant->variant.type = type;
    switch_variant->variant.alias = alias;
    switch_variant->statement = NULL;
    switch_variant->next_case = NULL;
    return switch_variant;
}

Parsed_Switch_Statement *Parsed_Switch_Statement__create(Source_Location location, Parsed_Expression *expression, Parsed_Switch_Case *first_case) {
    Parsed_Switch_Statement *statement = (Parsed_Switch_Statement *)Parsed_Statement__create_kind(PARSED_STATEMENT_KIND__SWITCH, sizeof(Parsed_Switch_Statement), location);
    statement->expression = expression;
    statement->first_case = first_case;
    return statement;
}

Parsed_Variable_Statement *Parsed_Variable_Statement__create(Source_Location location, Token *name, Parsed_Type *type, bool is_external, Parsed_Expression *expression, String_Token *external_name) {
    Parsed_Variable_Statement *statement = (Parsed_Variable_Statement *)Parsed_Named_Statement__create_kind(PARSED_STATEMENT_KIND__VARIABLE, sizeof(Parsed_Variable_Statement), location, name);
    statement->type = type;
    statement->is_external = is_external;
    statement->expression = expression;
    statement->external_name = external_name;
    return statement;
}

Parsed_Statement *Parsed_While_Statement__create(Source_Location location, Parsed_Expression *condition_expression, Parsed_Statement *body_statement) {
    Parsed_While_Statement *statement = (Parsed_While_Statement *)Parsed_Statement__create_kind(PARSED_STATEMENT_KIND__WHILE, sizeof(Parsed_While_Statement), location);
    statement->condition_expression = condition_expression;
    statement->body_statement = body_statement;
    return (Parsed_Statement *)statement;
}

Parsed_Yield_Statement *Parsed_Yield_Statement__create(Source_Location location, Parsed_Expression *expression) {
    Parsed_Yield_Statement *statement = (Parsed_Yield_Statement *)Parsed_Statement__create_kind(PARSED_STATEMENT_KIND__YIELD, sizeof(Parsed_Yield_Statement), location);
    statement->expression = expression;
    return statement;
}

Parsed_Statements *Parsed_Statements__create(bool has_globals) {
    Parsed_Statements *statements = (Parsed_Statements *)malloc(sizeof(Parsed_Statements));
    statements->first_statement = NULL;
    statements->last_statement = NULL;
    statements->has_globals = has_globals;
    return statements;
}

void Parsed_Statements__append(Parsed_Statements *self, Parsed_Statement *statement) {
    if (self->first_statement == NULL) {
        self->first_statement = statement;
    } else {
        self->last_statement->next_statement = statement;
    }
    self->last_statement = statement;
}

Parsed_Type_Specifier *Parsed_Type_Specifier__create(Parsed_Type_Specifier_Kind kind, size_t kind_size, Source_Location location) {
    Parsed_Type_Specifier *specifier = (Parsed_Type_Specifier *)malloc(kind_size);
    specifier->kind = kind;
    specifier->location = location;
    return specifier;
}

Parsed_Builtin_Type_Specifier *Parsed_Builtin_Type_Specifier__create(Source_Location location) {
    Parsed_Builtin_Type_Specifier *type_specifier = (Parsed_Builtin_Type_Specifier *)Parsed_Type_Specifier__create(PARSED_TYPE_SPECIFIER_KIND__BUILTIN, sizeof(Parsed_Builtin_Type_Specifier), location);
    return type_specifier;
}

Parsed_External_Type_Specifier *Parsed_External_Type_Specifier__create(Source_Location location) {
    return (Parsed_External_Type_Specifier *)Parsed_Type_Specifier__create(PARSED_TYPE_SPECIFIER_KIND__EXTERNAL, sizeof(Parsed_External_Type_Specifier), location);
}

Parsed_Struct_Member *Parsed_Struct_Member__create(Token *name, Parsed_Type *type) {
    Parsed_Struct_Member *member = (Parsed_Struct_Member *)malloc(sizeof(Parsed_Struct_Member));
    member->name = name;
    member->type = type;
    member->next_member = NULL;
    return member;
}

Parsed_Struct_Type_Specifier *Parsed_Struct_Type_Specifier__create(Source_Location location, Parsed_Struct_Member *first_member) {
    Parsed_Struct_Type_Specifier *type_specifier = (Parsed_Struct_Type_Specifier *)Parsed_Type_Specifier__create(PARSED_TYPE_SPECIFIER_KIND__STRUCT, sizeof(Parsed_Struct_Type_Specifier), location);
    type_specifier->first_member = first_member;
    return type_specifier;
}

Parsed_Trait_Method *Parsed_Trait_Method__create(Source_Location location, Token *name, Parsed_Procedure_Parameter *first_parameter, Parsed_Type *return_type, Parsed_Type *raise_type) {
    Parsed_Trait_Method *method = (Parsed_Trait_Method *)malloc(sizeof(Parsed_Trait_Method));
    method->location = location;
    method->name = name;
    method->first_parameter = first_parameter;
    method->return_type = return_type;
    method->raise_type = raise_type;
    method->next_method = NULL;
    return method;
}

Parsed_Trait_Type_Specifier *Parsed_Trait_Type_Specifier__create(Source_Location location, Parsed_Trait_Method *first_method) {
    Parsed_Trait_Type_Specifier *type_specifier = (Parsed_Trait_Type_Specifier *)Parsed_Type_Specifier__create(PARSED_TYPE_SPECIFIER_KIND__TRAIT, sizeof(Parsed_Trait_Type_Specifier), location);
    type_specifier->first_method = first_method;
    return type_specifier;
}

Parsed_Variant_Case *Parsed_Variant_Case__create(Parsed_Type *type) {
    Parsed_Variant_Case *variant = (Parsed_Variant_Case *)malloc(sizeof(Parsed_Variant_Case));
    variant->type = type;
    variant->next_variant = NULL;
    return variant;
}

Parsed_Variant_Type_Specifier *Parsed_Variant_Type_Specifier__create(Source_Location location, Parsed_Variant_Case *first_variant) {
    Parsed_Variant_Type_Specifier *type_specifier = (Parsed_Variant_Type_Specifier *)Parsed_Type_Specifier__create(PARSED_TYPE_SPECIFIER_KIND__VARIANT, sizeof(Parsed_Variant_Type_Specifier), location);
    type_specifier->first_variant_case = first_variant;
    return type_specifier;
}

Parsed_Module *Parsed_Module__create(Source *source, Parsed_Statements *statements) {
    Parsed_Module *parsed_source = (Parsed_Module *)malloc(sizeof(Parsed_Module));
    parsed_source->source = source;
    parsed_source->statements = statements;
    parsed_source->next_module = NULL;
    return parsed_source;
}

Parsed_Package *Parsed_Package__create(String *name, bool is_root) {
    Parsed_Package *package = (Parsed_Package *)malloc(sizeof(Parsed_Package));
    package->name = name;
    package->first_module = NULL;
    package->import_location = NULL;
    package->is_root = is_root;
    package->next_package = NULL;
    return package;
}
