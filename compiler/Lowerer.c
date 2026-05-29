#include "Lowerer.h"
#include "File.h"

typedef struct Lowerer {
    Checked_Type *bool_type;
    Checked_Symbols *symbols;
    Checked_Package *checked_package;
    Checked_Type *return_type;
    int32_t temp_variable_counter;
} Lowerer;

typedef struct Decomposer {
    Lowerer *lowerer;
    Checked_Statements *statements;
} Decomposer;

Checked_Expression *Decomposer__decompose(Decomposer *self, Checked_Expression *expression);

void Lowerer__lower_block_statement(Lowerer *self, Checked_Block_Statement *block_statement);

Checked_Variable_Symbol *Decomposer__create_temp_variable_symbol(Decomposer *self, Source_Location location, Checked_Type *type) {
    if (self->statements == NULL) {
        self->statements = Checked_Statements__create();
    }

    String *temp_variable_name = String__create_from("__");
    self->lowerer->temp_variable_counter++;
    if (self->lowerer->temp_variable_counter < 100) {
        String__append_char(temp_variable_name, '0');
        if (self->lowerer->temp_variable_counter < 10) {
            String__append_char(temp_variable_name, '0');
        }
    }
    String__append_int16_t(temp_variable_name, self->lowerer->temp_variable_counter);
    String__append_cstring(temp_variable_name, "__");

    Checked_Variable_Symbol *temp_variable_symbol = Checked_Variable_Symbol__create(self->lowerer->checked_package, location, temp_variable_name, type, false);
    temp_variable_symbol->is_temp = true;
    Checked_Symbols__append_symbol(self->lowerer->symbols, (Checked_Symbol *)temp_variable_symbol);
    return temp_variable_symbol;
}

Checked_Expression *Decomposer__create_temp_variable_with_type(Decomposer *self, Checked_Expression *expression, Checked_Type *type) {
    Checked_Variable_Symbol *temp_variable_symbol = Decomposer__create_temp_variable_symbol(self, expression->location, type);
    temp_variable_symbol->is_temp = true;

    Checked_Variable_Statement *temp_variable_statement = Checked_Variable_Statement__create(expression->location, temp_variable_symbol, false, expression);
    Checked_Statements__append(self->statements, (Checked_Statement *)temp_variable_statement);

    return (Checked_Expression *)Checked_Symbol_Expression__create(expression->location, expression->type, (Checked_Symbol *)temp_variable_symbol);
}

Checked_Expression *Decomposer__create_temp_variable_without_value(Decomposer *self, Source_Location location, Checked_Type *type) {
    Checked_Variable_Symbol *temp_variable_symbol = Decomposer__create_temp_variable_symbol(self, location, type);
    temp_variable_symbol->is_temp = true;

    Checked_Variable_Statement *temp_variable_statement = Checked_Variable_Statement__create(location, temp_variable_symbol, false, NULL);
    Checked_Statements__append(self->statements, (Checked_Statement *)temp_variable_statement);

    return (Checked_Expression *)Checked_Symbol_Expression__create(location, type, (Checked_Symbol *)temp_variable_symbol);
}

Checked_Expression *Decomposer__create_temp_variable(Decomposer *self, Checked_Expression *expression) {
    return Decomposer__create_temp_variable_with_type(self, expression, expression->type);
}

Checked_Expression *Decomposer__decompose_address_of_expression(Decomposer *self, Checked_Address_Of_Expression *expression) {
    expression->super.other_expression = Decomposer__create_temp_variable(self, Decomposer__decompose(self, expression->super.other_expression));
    return (Checked_Expression *)expression;
}

Checked_Expression *Decomposer__decompose_binary_expression(Decomposer *self, Checked_Binary_Expression *expression) {
    expression->left_expression = Decomposer__create_temp_variable(self, Decomposer__decompose(self, expression->left_expression));
    expression->right_expression = Decomposer__decompose(self, expression->right_expression);
    return (Checked_Expression *)expression;
}

Checked_Expression *Decomposer__decompose_logic_and_expression(Decomposer *self, Checked_Logic_And_Expression *expression) {
    Checked_Expression *result_expression = Decomposer__create_temp_variable(self, Decomposer__decompose(self, expression->super.left_expression));

    Checked_Block_Statement *true_block = Checked_Block_Statement__create(result_expression->location, Checked_Statements__create());
    Checked_Statements *self_statements = self->statements;
    self->statements = true_block->statements;
    Checked_Statements__append(self->statements, (Checked_Statement *)Checked_Assignment_Statement__create(result_expression->location, result_expression, Decomposer__decompose(self, expression->super.right_expression)));
    self->statements = self_statements;

    Checked_Statements__append(self->statements, (Checked_Statement *)Checked_If_Statement__create(result_expression->location, result_expression, (Checked_Statement *)true_block, NULL));

    free(expression); // replaced by result_expression

    return (Checked_Expression *)result_expression;
}

Checked_Expression *Decomposer__decompose_logic_or_expression(Decomposer *self, Checked_Logic_Or_Expression *expression) {
    Checked_Expression *result_expression = Decomposer__create_temp_variable(self, Decomposer__decompose(self, expression->super.left_expression));

    Checked_Block_Statement *false_block = Checked_Block_Statement__create(result_expression->location, Checked_Statements__create());
    Checked_Statements *self_statements = self->statements;
    self->statements = false_block->statements;
    Checked_Statements__append(self->statements, (Checked_Statement *)Checked_Assignment_Statement__create(result_expression->location, result_expression, Decomposer__decompose(self, expression->super.right_expression)));
    self->statements = self_statements;

    Checked_Statements__append(self->statements, (Checked_Statement *)Checked_If_Statement__create(result_expression->location, result_expression, NULL, (Checked_Statement *)false_block));

    free(expression); // replaced by result_expression

    return (Checked_Expression *)result_expression;
}

Checked_Expression *Decomposer__decompose_unary_expression(Decomposer *self, Checked_Unary_Expression *expression) {
    expression->other_expression = Decomposer__decompose(self, expression->other_expression);
    return (Checked_Expression *)expression;
}

Checked_Expression *Decomposer__decompose_block_expression(Decomposer *self, Checked_Block_Expression *expression) {
    if (expression->block_statement->kind != CHECKED_STATEMENT_KIND__BLOCK) {
        pWriter__begin_location_message(stderr_writer, expression->super.location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Not a block statement");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    Checked_Block_Statement *block_statement = (Checked_Block_Statement *)expression->block_statement;

    // Lower the inner block statements first, so their temporaries are numbered before the block result.
    Lowerer__lower_block_statement(self->lowerer, block_statement);

    Checked_Expression *new_expression;
    if (expression->super.type->kind == CHECKED_TYPE_KIND__NOTHING) {
        new_expression = (Checked_Expression *)Checked_Nothing_Expression__create(expression->super.location, expression->super.type);
    } else {
        new_expression = Decomposer__create_temp_variable_without_value(self, expression->super.location, expression->super.type);
    }

    Checked_Statement *last_statement = block_statement->statements->last_statement;
    if (last_statement != NULL && last_statement->kind == CHECKED_STATEMENT_KIND__DECOMPOSED) {
        last_statement = ((Checked_Decomposed_Statement *)last_statement)->statements->last_statement;
    }
    if (last_statement != NULL && last_statement->kind == CHECKED_STATEMENT_KIND__YIELD) {
        Checked_Yield_Statement *yield_statement = (Checked_Yield_Statement *)last_statement;
        yield_statement->block_result_expression = new_expression;
    }

    Checked_Statements__append(self->statements, (Checked_Statement *)block_statement);

    return new_expression;
}

Checked_Expression *Decomposer__decompose_call_expression(Decomposer *self, Checked_Call_Expression *expression) {
    expression->callee_expression = Decomposer__decompose(self, expression->callee_expression);
    Checked_Call_Argument *call_argument = expression->first_argument;
    while (call_argument != NULL) {
        call_argument->expression = Decomposer__create_temp_variable_with_type(self, Decomposer__decompose(self, call_argument->expression), call_argument->parameter_type);
        call_argument = call_argument->next_argument;
    }
    return (Checked_Expression *)expression;
}

Checked_Expression *Decomposer__decompose_member_access_expression(Decomposer *self, Checked_Member_Access_Expression *expression) {
    expression->object_expression = Decomposer__decompose(self, expression->object_expression);
    if (expression->object_expression->kind == CHECKED_EXPRESSION_KIND__CALL) {
        expression->object_expression = Decomposer__create_temp_variable(self, expression->object_expression);
    }
    return (Checked_Expression *)expression;
}

Checked_Expression *Decomposer__decompose_array_access_expression(Decomposer *self, Checked_Array_Access_Expression *expression) {
    expression->array_expression = Decomposer__decompose(self, expression->array_expression);
    expression->index_expression = Decomposer__create_temp_variable(self, Decomposer__decompose(self, expression->index_expression));
    if (expression->array_expression->kind == CHECKED_EXPRESSION_KIND__ARRAY_ACCESS) {
        expression->array_expression = Decomposer__create_temp_variable(self, expression->array_expression);
    }
    return (Checked_Expression *)expression;
}

Checked_Expression *Decomposer__decompose_make_struct_expression(Decomposer *self, Checked_Make_Struct_Expression *expression) {
    Checked_Make_Struct_Argument *argument = expression->first_argument;
    while (argument != NULL) {
        argument->expression = Decomposer__create_temp_variable_with_type(self, Decomposer__decompose(self, argument->expression), argument->struct_member->type);
        argument = argument->next_argument;
    }
    return (Checked_Expression *)expression;
}

Checked_Expression *Decomposer__decompose_make_variant_expression(Decomposer *self, Checked_Make_Variant_Expression *expression) {
    expression->expression = Decomposer__decompose(self, expression->expression);
    return (Checked_Expression *)expression;
}

Checked_Expression *Decomposer__decompose_alloc_expression(Decomposer *self, Checked_Alloc_Expression *expression) {
    Checked_Expression *value_expression = expression->value_expression;
    expression->value_expression = NULL;
    Checked_Expression *result_expression = Decomposer__create_temp_variable(self, (Checked_Expression *)expression);
    Checked_Statements__append(self->statements, (Checked_Statement *)Checked_Assignment_Statement__create(value_expression->location, (Checked_Expression *)Checked_Dereference_Expression__create(expression->super.location, value_expression->type, result_expression), Decomposer__decompose(self, value_expression)));
    return result_expression;
}

Checked_Expression *Decomposer__decompose_is_variant_case_expression(Decomposer *self, Checked_Is_Variant_Case_Expression *expression) {
    expression->variant_expression = Decomposer__decompose(self, expression->variant_expression);
    return (Checked_Expression *)expression;
}

Checked_Expression *Decomposer__decompose_result_expression(Decomposer *self, Checked_Result_Expression *expression) {
    if (expression->raise_expression != NULL) {
        expression->raise_expression = Decomposer__decompose(self, expression->raise_expression);
    }
    if (expression->return_expression != NULL) {
        expression->return_expression = Decomposer__decompose(self, expression->return_expression);
    }
    return Decomposer__create_temp_variable(self, (Checked_Expression *)expression);
}

Checked_Expression *Decomposer__decompose_try_expression(Decomposer *self, Checked_Try_Expression *expression) {
    Checked_Expression *result_expression = Decomposer__create_temp_variable(self, Decomposer__decompose(self, (Checked_Expression *)expression->call_expression));
    if (result_expression->type->kind != CHECKED_TYPE_KIND__RESULT) {
        pWriter__begin_location_message(stderr_writer, expression->super.location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Expected result type");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    Checked_Result_Type *result_type = (Checked_Result_Type *)result_expression->type;

    if (result_type->return_type->kind == CHECKED_TYPE_KIND__NOTHING) {
        Checked_Result_Success_Expression *result_success_expression = Checked_Result_Success_Expression__create(result_expression->location, self->lowerer->bool_type, result_expression);
        Checked_Result_Error_Expression *result_error_expression = Checked_Result_Error_Expression__create(result_expression->location, result_type->raise_type, result_expression);

        Checked_Block_Statement *failed_block_statement = Checked_Block_Statement__create(expression->else_expression->location, Checked_Statements__create());
        Checked_Statements *self_statements = self->statements;
        self->statements = failed_block_statement->statements;
        expression->result_error_symbol->expression = (Checked_Expression *)result_error_expression;
        Checked_Expression *else_expression = Decomposer__decompose(self, expression->else_expression);
        self->statements = self_statements;

        Checked_Statements__append(self->statements, (Checked_Statement *)Checked_If_Statement__create(expression->super.location, (Checked_Expression *)result_success_expression, NULL, (Checked_Statement *)failed_block_statement));

        return else_expression;
    }

    Checked_Expression *new_expression = Decomposer__create_temp_variable_without_value(self, expression->super.location, result_type->return_type);

    Checked_Result_Success_Expression *result_success_expression = Checked_Result_Success_Expression__create(result_expression->location, self->lowerer->bool_type, result_expression);
    Checked_Result_Value_Expression *result_value_expression = Checked_Result_Value_Expression__create(result_expression->location, result_type->return_type, result_expression);
    Checked_Result_Error_Expression *result_error_expression = Checked_Result_Error_Expression__create(result_expression->location, result_type->raise_type, result_expression);

    Checked_Block_Statement *success_block_statement = Checked_Block_Statement__create(result_expression->location, Checked_Statements__create());
    Checked_Statements__append(success_block_statement->statements, (Checked_Statement *)Checked_Assignment_Statement__create(expression->super.location, new_expression, (Checked_Expression *)result_value_expression));

    Checked_Block_Statement *failed_block_statement = Checked_Block_Statement__create(expression->else_expression->location, Checked_Statements__create());
    Checked_Statements *self_statements = self->statements;
    self->statements = failed_block_statement->statements;
    expression->result_error_symbol->expression = (Checked_Expression *)result_error_expression;
    Checked_Statements__append(self->statements, (Checked_Statement *)Checked_Assignment_Statement__create(expression->else_expression->location, new_expression, Decomposer__decompose(self, expression->else_expression)));
    self->statements = self_statements;

    Checked_Statements__append(self->statements, (Checked_Statement *)Checked_If_Statement__create(expression->super.location, (Checked_Expression *)result_success_expression, (Checked_Statement *)success_block_statement, (Checked_Statement *)failed_block_statement));

    free(expression); // replaced by new_expression

    return (Checked_Expression *)new_expression;
}

Checked_Expression *Decomposer__decompose_unwrap_result_expression(Decomposer *self, Checked_Unwrap_Result_Expression *expression) {
    Checked_Expression *result_expression = Decomposer__create_temp_variable(self, Decomposer__decompose(self, (Checked_Expression *)expression->call_expression));
    if (result_expression->type->kind != CHECKED_TYPE_KIND__RESULT) {
        pWriter__begin_location_message(stderr_writer, expression->super.location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Expected result type");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    Checked_Result_Type *result_type = (Checked_Result_Type *)result_expression->type;

    Checked_Result_Success_Expression *result_success_expression = Checked_Result_Success_Expression__create(expression->super.location, self->lowerer->bool_type, result_expression);
    Checked_Expression *result_value_expression;
    if (result_type->return_type->kind != CHECKED_TYPE_KIND__NOTHING) {
        result_value_expression = (Checked_Expression *)Checked_Result_Value_Expression__create(expression->super.location, result_type->return_type, result_expression);
    } else {
        result_value_expression = (Checked_Expression *)Checked_Nothing_Expression__create(expression->super.location, result_type->return_type);
    }
    Checked_Result_Error_Expression *result_error_expression = Checked_Result_Error_Expression__create(expression->super.location, result_type->raise_type, result_expression);

    Checked_Return_Statement *return_statement = Checked_Return_Statement__create(expression->super.location, (Checked_Expression *)Checked_Result_Expression__create(expression->super.location, self->lowerer->return_type, NULL, (Checked_Expression *)result_error_expression));
    Checked_Statements__append(self->statements, (Checked_Statement *)Checked_If_Statement__create(expression->super.location, (Checked_Expression *)result_success_expression, NULL, (Checked_Statement *)return_statement));

    free(expression); // replaced by result_value_expression

    return (Checked_Expression *)result_value_expression;
}

bool Checked_Expression__needs_decomposition(Checked_Expression *self);

Checked_Expression *Decomposer__decompose(Decomposer *self, Checked_Expression *expression) {
    if (!Checked_Expression__needs_decomposition(expression)) {
        return expression;
    }
    switch (expression->kind) {
    case CHECKED_EXPRESSION_KIND__ADD:
        return Decomposer__decompose_binary_expression(self, (Checked_Binary_Expression *)expression);
    case CHECKED_EXPRESSION_KIND__ADDRESS_OF:
        return Decomposer__decompose_address_of_expression(self, (Checked_Address_Of_Expression *)expression);
    case CHECKED_EXPRESSION_KIND__ALLOC:
        return Decomposer__decompose_alloc_expression(self, (Checked_Alloc_Expression *)expression);
    case CHECKED_EXPRESSION_KIND__ARRAY_ACCESS:
        return Decomposer__decompose_array_access_expression(self, (Checked_Array_Access_Expression *)expression);
    case CHECKED_EXPRESSION_KIND__BLOCK:
        return Decomposer__decompose_block_expression(self, (Checked_Block_Expression *)expression);
    case CHECKED_EXPRESSION_KIND__BOOL:
        return expression;
    case CHECKED_EXPRESSION_KIND__CALL:
        return Decomposer__decompose_call_expression(self, (Checked_Call_Expression *)expression);
    case CHECKED_EXPRESSION_KIND__CAST:
        return Decomposer__decompose_unary_expression(self, (Checked_Unary_Expression *)expression); // Treat as unary expressions
    case CHECKED_EXPRESSION_KIND__CHARACTER:
        return expression;
    case CHECKED_EXPRESSION_KIND__DEREFERENCE:
        return Decomposer__decompose_unary_expression(self, (Checked_Unary_Expression *)expression);
    case CHECKED_EXPRESSION_KIND__DIVIDE:
        return Decomposer__decompose_binary_expression(self, (Checked_Binary_Expression *)expression);
    case CHECKED_EXPRESSION_KIND__EQUALS:
        return Decomposer__decompose_binary_expression(self, (Checked_Binary_Expression *)expression);
    case CHECKED_EXPRESSION_KIND__GREATER_OR_EQUALS:
        return Decomposer__decompose_binary_expression(self, (Checked_Binary_Expression *)expression);
    case CHECKED_EXPRESSION_KIND__GREATER:
        return Decomposer__decompose_binary_expression(self, (Checked_Binary_Expression *)expression);
    case CHECKED_EXPRESSION_KIND__GROUP:
        return Decomposer__decompose_unary_expression(self, (Checked_Unary_Expression *)expression); // Treat as unary expressions
    case CHECKED_EXPRESSION_KIND__INTEGER:
        return expression;
    case CHECKED_EXPRESSION_KIND__IS_VARIANT_CASE:
        return Decomposer__decompose_is_variant_case_expression(self, (Checked_Is_Variant_Case_Expression *)expression);
    case CHECKED_EXPRESSION_KIND__LESS_OR_EQUALS:
        return Decomposer__decompose_binary_expression(self, (Checked_Binary_Expression *)expression);
    case CHECKED_EXPRESSION_KIND__LESS:
        return Decomposer__decompose_binary_expression(self, (Checked_Binary_Expression *)expression);
    case CHECKED_EXPRESSION_KIND__LOGIC_AND:
        return Decomposer__decompose_logic_and_expression(self, (Checked_Logic_And_Expression *)expression);
    case CHECKED_EXPRESSION_KIND__LOGIC_OR:
        return Decomposer__decompose_logic_or_expression(self, (Checked_Logic_Or_Expression *)expression);
    case CHECKED_EXPRESSION_KIND__MAKE_STRUCT:
        return Decomposer__decompose_make_struct_expression(self, (Checked_Make_Struct_Expression *)expression);
    case CHECKED_EXPRESSION_KIND__MAKE_VARIANT:
        return Decomposer__decompose_make_variant_expression(self, (Checked_Make_Variant_Expression *)expression);
    case CHECKED_EXPRESSION_KIND__MEMBER_ACCESS:
        return Decomposer__decompose_member_access_expression(self, (Checked_Member_Access_Expression *)expression);
    case CHECKED_EXPRESSION_KIND__MINUS:
        return Decomposer__decompose_unary_expression(self, (Checked_Unary_Expression *)expression);
    case CHECKED_EXPRESSION_KIND__MODULO:
        return Decomposer__decompose_binary_expression(self, (Checked_Binary_Expression *)expression);
    case CHECKED_EXPRESSION_KIND__MULTIPLY:
        return Decomposer__decompose_binary_expression(self, (Checked_Binary_Expression *)expression);
    case CHECKED_EXPRESSION_KIND__NOT_EQUALS:
        return Decomposer__decompose_binary_expression(self, (Checked_Binary_Expression *)expression);
    case CHECKED_EXPRESSION_KIND__NOT:
        return Decomposer__decompose_unary_expression(self, (Checked_Unary_Expression *)expression);
    case CHECKED_EXPRESSION_KIND__NULL:
        return expression;
    case CHECKED_EXPRESSION_KIND__RESULT:
        return Decomposer__decompose_result_expression(self, (Checked_Result_Expression *)expression);
    case CHECKED_EXPRESSION_KIND__STRING_LENGTH:
        return Decomposer__decompose_unary_expression(self, (Checked_Unary_Expression *)expression); // Treat as unary expressions
    case CHECKED_EXPRESSION_KIND__STRING:
        return expression;
    case CHECKED_EXPRESSION_KIND__SUBTRACT:
        return Decomposer__decompose_binary_expression(self, (Checked_Binary_Expression *)expression);
    case CHECKED_EXPRESSION_KIND__SYMBOL:
        return expression;
    case CHECKED_EXPRESSION_KIND__TRY:
        return Decomposer__decompose_try_expression(self, (Checked_Try_Expression *)expression);
    case CHECKED_EXPRESSION_KIND__TYPE_SIZE:
        return expression;
    case CHECKED_EXPRESSION_KIND__UNWRAP_RESULT:
        return Decomposer__decompose_unwrap_result_expression(self, (Checked_Unwrap_Result_Expression *)expression);
    default:
        pWriter__begin_location_message(stderr_writer, expression->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Cannot decompose expression kind: ");
        pWriter__write__int64(stderr_writer, expression->kind);
        pWriter__end_location_message(stderr_writer);
        panic();
    }
}

bool Checked_Address_Of_Expression__needs_decomposition(Checked_Address_Of_Expression *self) {
    switch (self->super.other_expression->kind) {
    case CHECKED_EXPRESSION_KIND__CHARACTER:
    case CHECKED_EXPRESSION_KIND__INTEGER:
    case CHECKED_EXPRESSION_KIND__MAKE_STRUCT:
    case CHECKED_EXPRESSION_KIND__MINUS:
    case CHECKED_EXPRESSION_KIND__STRING:
        return true;
    default:
        return false;
    }
}

bool Checked_Array_Access_Expression__needs_decomposition(Checked_Array_Access_Expression *self) {
    return Checked_Expression__needs_decomposition(self->array_expression) || Checked_Expression__needs_decomposition(self->index_expression);
}

bool Checked_Binary_Expression__needs_decomposition(Checked_Binary_Expression *self) {
    return Checked_Expression__needs_decomposition(self->left_expression) || Checked_Expression__needs_decomposition(self->right_expression);
}

bool Checked_Call_Expression__needs_decomposition(Checked_Call_Expression *self) {
    Checked_Call_Argument *argument = self->first_argument;
    while (argument != NULL) {
        if (Checked_Expression__needs_decomposition(argument->expression)) {
            return true;
        }
        argument = argument->next_argument;
    }
    return Checked_Expression__needs_decomposition(self->callee_expression);
}

bool Checked_Is_Variant_Case_Expression__needs_decomposition(Checked_Is_Variant_Case_Expression *self) {
    return Checked_Expression__needs_decomposition(self->variant_expression);
}

bool Checked_Make_Struct_Expression__needs_decomposition(Checked_Make_Struct_Expression *self) {
    Checked_Make_Struct_Argument *argument = self->first_argument;
    while (argument != NULL) {
        if (Checked_Expression__needs_decomposition(argument->expression)) {
            return true;
        }
        argument = argument->next_argument;
    }
    return false;
}

bool Checked_Make_Variant_Expression__needs_decomposition(Checked_Make_Variant_Expression *self) {
    return Checked_Expression__needs_decomposition(self->expression);
}

bool Checked_Member_Access_Expression__needs_decomposition(Checked_Member_Access_Expression *self) {
    return Checked_Expression__needs_decomposition(self->object_expression);
}

bool Checked_Result_Expression__needs_decomposition(Checked_Result_Expression *self) {
    bool needs_decomposition = false;
    if (self->return_expression != NULL) {
        needs_decomposition = Checked_Expression__needs_decomposition(self->return_expression);
    }
    if (!needs_decomposition && self->raise_expression != NULL) {
        needs_decomposition = Checked_Expression__needs_decomposition(self->raise_expression);
    }
    return needs_decomposition;
}

bool Checked_Unary_Expression__needs_decomposition(Checked_Unary_Expression *self) {
    return Checked_Expression__needs_decomposition(self->other_expression);
}

bool Checked_Expression__needs_decomposition(Checked_Expression *self) {
    switch (self->kind) {
    case CHECKED_EXPRESSION_KIND__ADD:
        return Checked_Binary_Expression__needs_decomposition((Checked_Binary_Expression *)self);
    case CHECKED_EXPRESSION_KIND__ADDRESS_OF:
        return Checked_Address_Of_Expression__needs_decomposition((Checked_Address_Of_Expression *)self);
    case CHECKED_EXPRESSION_KIND__ALLOC:
        return true;
    case CHECKED_EXPRESSION_KIND__ARRAY_ACCESS:
        return Checked_Array_Access_Expression__needs_decomposition((Checked_Array_Access_Expression *)self);
    case CHECKED_EXPRESSION_KIND__BLOCK:
        return true;
    case CHECKED_EXPRESSION_KIND__BOOL:
        return false;
    case CHECKED_EXPRESSION_KIND__CALL:
        return Checked_Call_Expression__needs_decomposition((Checked_Call_Expression *)self);
    case CHECKED_EXPRESSION_KIND__CAST:
        return Checked_Unary_Expression__needs_decomposition((Checked_Unary_Expression *)self); // Treat as unary expressions
    case CHECKED_EXPRESSION_KIND__CHARACTER:
        return false;
    case CHECKED_EXPRESSION_KIND__DEREFERENCE:
        return Checked_Unary_Expression__needs_decomposition((Checked_Unary_Expression *)self);
    case CHECKED_EXPRESSION_KIND__DIVIDE:
        return Checked_Binary_Expression__needs_decomposition((Checked_Binary_Expression *)self);
    case CHECKED_EXPRESSION_KIND__EQUALS:
        return Checked_Binary_Expression__needs_decomposition((Checked_Binary_Expression *)self);
    case CHECKED_EXPRESSION_KIND__GREATER_OR_EQUALS:
        return Checked_Binary_Expression__needs_decomposition((Checked_Binary_Expression *)self);
    case CHECKED_EXPRESSION_KIND__GREATER:
        return Checked_Binary_Expression__needs_decomposition((Checked_Binary_Expression *)self);
    case CHECKED_EXPRESSION_KIND__GROUP:
        return Checked_Unary_Expression__needs_decomposition((Checked_Unary_Expression *)self); // Treat as unary expressions
    case CHECKED_EXPRESSION_KIND__INTEGER:
        return false;
    case CHECKED_EXPRESSION_KIND__IS_VARIANT_CASE:
        return Checked_Is_Variant_Case_Expression__needs_decomposition((Checked_Is_Variant_Case_Expression *)self);
    case CHECKED_EXPRESSION_KIND__LESS_OR_EQUALS:
        return Checked_Binary_Expression__needs_decomposition((Checked_Binary_Expression *)self);
    case CHECKED_EXPRESSION_KIND__LESS:
        return Checked_Binary_Expression__needs_decomposition((Checked_Binary_Expression *)self);
    case CHECKED_EXPRESSION_KIND__LOGIC_AND:
        return Checked_Binary_Expression__needs_decomposition((Checked_Binary_Expression *)self);
    case CHECKED_EXPRESSION_KIND__LOGIC_OR:
        return Checked_Binary_Expression__needs_decomposition((Checked_Binary_Expression *)self);
    case CHECKED_EXPRESSION_KIND__MAKE_STRUCT:
        return Checked_Make_Struct_Expression__needs_decomposition((Checked_Make_Struct_Expression *)self);
    case CHECKED_EXPRESSION_KIND__MAKE_VARIANT:
        return Checked_Make_Variant_Expression__needs_decomposition((Checked_Make_Variant_Expression *)self);
    case CHECKED_EXPRESSION_KIND__MEMBER_ACCESS:
        return Checked_Member_Access_Expression__needs_decomposition((Checked_Member_Access_Expression *)self);
    case CHECKED_EXPRESSION_KIND__MINUS:
        return Checked_Unary_Expression__needs_decomposition((Checked_Unary_Expression *)self);
    case CHECKED_EXPRESSION_KIND__MODULO:
        return Checked_Binary_Expression__needs_decomposition((Checked_Binary_Expression *)self);
    case CHECKED_EXPRESSION_KIND__MULTIPLY:
        return Checked_Binary_Expression__needs_decomposition((Checked_Binary_Expression *)self);
    case CHECKED_EXPRESSION_KIND__NOT_EQUALS:
        return Checked_Binary_Expression__needs_decomposition((Checked_Binary_Expression *)self);
    case CHECKED_EXPRESSION_KIND__NOT:
        return Checked_Unary_Expression__needs_decomposition((Checked_Unary_Expression *)self);
    case CHECKED_EXPRESSION_KIND__NULL:
        return false;
    case CHECKED_EXPRESSION_KIND__RESULT:
        return Checked_Result_Expression__needs_decomposition((Checked_Result_Expression *)self);
    case CHECKED_EXPRESSION_KIND__STRING_LENGTH:
        return Checked_Unary_Expression__needs_decomposition((Checked_Unary_Expression *)self); // Treat as unary expressions
    case CHECKED_EXPRESSION_KIND__STRING:
        return false;
    case CHECKED_EXPRESSION_KIND__SUBTRACT:
        return Checked_Binary_Expression__needs_decomposition((Checked_Binary_Expression *)self);
    case CHECKED_EXPRESSION_KIND__SYMBOL:
        return false;
    case CHECKED_EXPRESSION_KIND__TRY:
        return true;
    case CHECKED_EXPRESSION_KIND__TYPE_ALIGNMENT:
        return false;
    case CHECKED_EXPRESSION_KIND__TYPE_SIZE:
        return false;
    case CHECKED_EXPRESSION_KIND__UNWRAP_RESULT:
        return true;
    default:
        pWriter__begin_location_message(stderr_writer, self->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Unsupported expression kind: ");
        pWriter__write__int64(stderr_writer, self->kind);
        pWriter__end_location_message(stderr_writer);
        panic();
    }
}

typedef struct Decomposed_Expression {
    Checked_Expression *expression;
    Checked_Statements *statements;
} Decomposed_Expression;

Decomposed_Expression Lowerer__decompose_expression_with_temp_variable(Lowerer *self, Checked_Expression *expression, bool require_temp_variable) {
    Decomposer decomposer = {
        .lowerer = self,
        .statements = NULL,
    };
    self->symbols = Checked_Symbols__create(self->symbols);
    Checked_Expression *decomposed_expression = Decomposer__decompose(&decomposer, expression);
    if (require_temp_variable) {
        if (decomposed_expression->kind == CHECKED_EXPRESSION_KIND__SYMBOL) {
            Checked_Symbol *symbol = ((Checked_Symbol_Expression *)decomposed_expression)->symbol;
            if (symbol->kind == CHECKED_SYMBOL_KIND__VARIABLE) {
                Checked_Variable_Symbol *variable_symbol = (Checked_Variable_Symbol *)symbol;
                require_temp_variable = !variable_symbol->is_temp;
            }
        }
    }
    if (require_temp_variable) {
        decomposed_expression = Decomposer__create_temp_variable(&decomposer, decomposed_expression);
    }
    self->symbols = self->symbols->parent;
    return (Decomposed_Expression){
        .expression = decomposed_expression,
        .statements = decomposer.statements,
    };
}

Decomposed_Expression Lowerer__decompose_expression(Lowerer *self, Checked_Expression *expression) {
    return Lowerer__decompose_expression_with_temp_variable(self, expression, false);
}

Checked_Statement *Lowerer__lower_statement(Lowerer *self, Checked_Statement *statement);

void Lowerer__lower_statements(Lowerer *self, Checked_Statements *statements) {
    Checked_Statement *statement = statements->first_statement;
    statements->first_statement = NULL;
    statements->last_statement = NULL;
    while (statement != NULL) {
        Checked_Statement *next_statement = statement->next_statement;
        statement->next_statement = NULL;
        Checked_Statement *lowered_statement = Lowerer__lower_statement(self, statement);
        lowered_statement->next_statement = NULL;
        Checked_Statements__append(statements, lowered_statement);
        statement = next_statement;
    }
}

void Lowerer__lower_block_statement(Lowerer *self, Checked_Block_Statement *block_statement) {
    Lowerer__lower_statements(self, block_statement->statements);
}

Checked_Statement *Lowerer__lower_assignment_statement(Lowerer *self, Checked_Assignment_Statement *statement) {
    Decomposed_Expression object = Lowerer__decompose_expression(self, statement->object_expression);
    Decomposed_Expression value = Lowerer__decompose_expression(self, statement->value_expression);
    statement->object_expression = object.expression;
    statement->value_expression = value.expression;
    if (object.statements != NULL || value.statements != NULL) {
        Checked_Block_Statement *block_statement = Checked_Block_Statement__create(statement->super.location, object.statements);
        if (block_statement->statements == NULL) {
            block_statement->statements = value.statements;
        } else if (value.statements != NULL) {
            block_statement->statements->last_statement->next_statement = value.statements->first_statement;
            block_statement->statements->last_statement = value.statements->last_statement;
            free(value.statements);
        }
        Checked_Statements__append(block_statement->statements, (Checked_Statement *)statement);
        return (Checked_Statement *)block_statement;
    }
    return (Checked_Statement *)statement;
}

Checked_Statement *Lowerer__lower_expression_statement(Lowerer *self, Checked_Expression_Statement *statement) {
    Decomposed_Expression expression = Lowerer__decompose_expression(self, statement->expression);
    statement->expression = expression.expression;
    if (expression.statements != NULL) {
        Checked_Block_Statement *block_statement = Checked_Block_Statement__create(statement->super.location, expression.statements);
        Checked_Statements__append(block_statement->statements, (Checked_Statement *)statement);
        return (Checked_Statement *)block_statement;
    }
    return (Checked_Statement *)statement;
}

Checked_Statement *Lowerer__lower_if_statement(Lowerer *self, Checked_If_Statement *statement) {
    Decomposed_Expression condition = Lowerer__decompose_expression(self, statement->condition_expression);
    statement->condition_expression = condition.expression;
    if (statement->true_statement != NULL) {
        statement->true_statement = Lowerer__lower_statement(self, statement->true_statement);
    }
    if (statement->false_statement != NULL) {
        statement->false_statement = Lowerer__lower_statement(self, statement->false_statement);
    }
    if (condition.statements != NULL) {
        Checked_Block_Statement *block_statement = Checked_Block_Statement__create(statement->super.location, condition.statements);
        Checked_Statements__append(block_statement->statements, (Checked_Statement *)statement);
        return (Checked_Statement *)block_statement;
    }
    return (Checked_Statement *)statement;
}

Checked_Statement *Lowerer__lower_raise_statement(Lowerer *self, Checked_Raise_Statement *statement) {
    Decomposed_Expression raise_expression = Lowerer__decompose_expression_with_temp_variable(self, statement->expression, true);
    Checked_Block_Statement *block_statement = Checked_Block_Statement__create(statement->super.location, raise_expression.statements);
    Checked_Statements__append(block_statement->statements, (Checked_Statement *)Checked_Return_Statement__create(statement->super.location, (Checked_Expression *)Checked_Result_Expression__create(raise_expression.expression->location, self->return_type, NULL, raise_expression.expression)));
    return (Checked_Statement *)block_statement;
}

Checked_Statement *Lowerer__lower_return_statement(Lowerer *self, Checked_Return_Statement *statement) {
    if (statement->expression != NULL) {
        Decomposed_Expression decomposed_expression = Lowerer__decompose_expression_with_temp_variable(self, statement->expression, true);
        Checked_Block_Statement *block_statement = Checked_Block_Statement__create(statement->super.location, decomposed_expression.statements);
        Checked_Statements__append(block_statement->statements, (Checked_Statement *)Checked_Return_Statement__create(statement->super.location, decomposed_expression.expression));
        return (Checked_Statement *)block_statement;
    }
    return (Checked_Statement *)statement;
}

Checked_Statement *Lowerer__lower_variable_statement(Lowerer *self, Checked_Variable_Statement *statement) {
    Decomposed_Expression decomposed_expression = {0};
    if (statement->expression != NULL) {
        decomposed_expression = Lowerer__decompose_expression(self, statement->expression);
    }
    if (decomposed_expression.statements != NULL) {
        Checked_Decomposed_Statement *decomposed_statement = Checked_Decomposed_Statement__create(statement->super.location, Checked_Statements__create());
        Checked_Statements__append(decomposed_statement->statements, (Checked_Statement *)Checked_Variable_Statement__create(statement->super.location, statement->variable, statement->is_external, NULL));
        Checked_Block_Statement *block_statement = Checked_Block_Statement__create(statement->super.location, decomposed_expression.statements);
        Checked_Statements__append(decomposed_statement->statements, (Checked_Statement *)block_statement);
        Checked_Statements__append(block_statement->statements, (Checked_Statement *)Checked_Assignment_Statement__create(statement->super.location, (Checked_Expression *)Checked_Symbol_Expression__create(statement->variable->super.location, statement->variable->super.type, (Checked_Symbol *)statement->variable), decomposed_expression.expression));
        return (Checked_Statement *)decomposed_statement;
    }
    return (Checked_Statement *)Checked_Variable_Statement__create(statement->super.location, statement->variable, statement->is_external, decomposed_expression.expression);
}

Checked_Statement *Lowerer__lower_while_statement(Lowerer *self, Checked_While_Statement *statement) {
    Decomposed_Expression condition = Lowerer__decompose_expression(self, statement->condition_expression);
    Checked_Statement *body_statement = Lowerer__lower_statement(self, statement->body_statement);
    if (condition.statements != NULL) {
        Checked_Block_Statement *block_statement;
        if (body_statement->kind != CHECKED_STATEMENT_KIND__BLOCK) {
            todo("Wrap body statement in a block");
        } else {
            block_statement = (Checked_Block_Statement *)body_statement;
        }
        Checked_Block_Statement *condition_block_statement = Checked_Block_Statement__create(statement->super.location, condition.statements);
        Checked_Statements__append(condition_block_statement->statements, (Checked_Statement *)Checked_If_Statement__create(statement->super.location, condition.expression, NULL, (Checked_Statement *)Checked_Break_Statement__create(statement->super.location)));
        Checked_Statements__prepend(block_statement->statements, (Checked_Statement *)condition_block_statement);
        Checked_Loop_Statement *loop_statement = Checked_Loop_Statement__create(statement->super.location, (Checked_Statement *)block_statement);
        return (Checked_Statement *)loop_statement;
    }
    statement->condition_expression = condition.expression;
    statement->body_statement = body_statement;
    return (Checked_Statement *)statement;
}

Checked_Statement *Lowerer__lower_yield_statement(Lowerer *self, Checked_Yield_Statement *statement) {
    Decomposed_Expression decomposed_expression = Lowerer__decompose_expression(self, statement->expression);
    statement->expression = decomposed_expression.expression;
    if (decomposed_expression.statements != NULL) {
        Checked_Decomposed_Statement *decomposed_statement = Checked_Decomposed_Statement__create(decomposed_expression.expression->location, decomposed_expression.statements);
        Checked_Statements__append(decomposed_statement->statements, (Checked_Statement *)statement);
        return (Checked_Statement *)decomposed_statement;
    }
    return (Checked_Statement *)statement;
}

Checked_Statement *Lowerer__lower_variant_switch_statement(Lowerer *self, Checked_Variant_Switch_Statement *statement) {
    Checked_Variant_Switch_Case *variant_switch_case = statement->first_variant_switch_case;
    while (variant_switch_case != NULL) {
        variant_switch_case->statement = Lowerer__lower_statement(self, variant_switch_case->statement);
        variant_switch_case = variant_switch_case->next_switch_variant_case;
    }
    if (statement->switch_else != NULL) {
        statement->switch_else->statement = Lowerer__lower_statement(self, statement->switch_else->statement);
    }
    return (Checked_Statement *)statement;
}

Checked_Statement *Lowerer__lower_statement(Lowerer *self, Checked_Statement *statement) {
    switch (statement->kind) {
    case CHECKED_STATEMENT_KIND__ASSIGNMENT:
        return Lowerer__lower_assignment_statement(self, (Checked_Assignment_Statement *)statement);
    case CHECKED_STATEMENT_KIND__BLOCK:
        Lowerer__lower_block_statement(self, (Checked_Block_Statement *)statement);
        return statement;
    case CHECKED_STATEMENT_KIND__BREAK:
        return statement;
    case CHECKED_STATEMENT_KIND__CONSTANT:
        return statement;
    case CHECKED_STATEMENT_KIND__DECOMPOSED:
        Lowerer__lower_statements(self, ((Checked_Decomposed_Statement *)statement)->statements);
        return statement;
    case CHECKED_STATEMENT_KIND__DEFER: {
        Checked_Defer_Statement *defer_statement = (Checked_Defer_Statement *)statement;
        defer_statement->statement = Lowerer__lower_statement(self, defer_statement->statement);
        return statement;
    }
    case CHECKED_STATEMENT_KIND__EXPRESSION:
        return Lowerer__lower_expression_statement(self, (Checked_Expression_Statement *)statement);
    case CHECKED_STATEMENT_KIND__IF:
        return Lowerer__lower_if_statement(self, (Checked_If_Statement *)statement);
    case CHECKED_STATEMENT_KIND__LOOP: {
        Checked_Loop_Statement *loop_statement = (Checked_Loop_Statement *)statement;
        loop_statement->body_statement = Lowerer__lower_statement(self, loop_statement->body_statement);
        return statement;
    }
    case CHECKED_STATEMENT_KIND__RAISE:
        return Lowerer__lower_raise_statement(self, (Checked_Raise_Statement *)statement);
    case CHECKED_STATEMENT_KIND__RETURN:
        return Lowerer__lower_return_statement(self, (Checked_Return_Statement *)statement);
    case CHECKED_STATEMENT_KIND__VARIABLE:
        return Lowerer__lower_variable_statement(self, (Checked_Variable_Statement *)statement);
    case CHECKED_STATEMENT_KIND__VARIANT_IF: {
        Checked_If_Variant_Case_Statement *variant_if_statement = (Checked_If_Variant_Case_Statement *)statement;
        variant_if_statement->true_statement = Lowerer__lower_statement(self, variant_if_statement->true_statement);
        if (variant_if_statement->false_statement != NULL) {
            variant_if_statement->false_statement = Lowerer__lower_statement(self, variant_if_statement->false_statement);
        }
        return statement;
    }
    case CHECKED_STATEMENT_KIND__VARIANT_SWITCH:
        return Lowerer__lower_variant_switch_statement(self, (Checked_Variant_Switch_Statement *)statement);
    case CHECKED_STATEMENT_KIND__WHILE:
        return Lowerer__lower_while_statement(self, (Checked_While_Statement *)statement);
    case CHECKED_STATEMENT_KIND__YIELD:
        return Lowerer__lower_yield_statement(self, (Checked_Yield_Statement *)statement);
    default:
        pWriter__begin_location_message(stderr_writer, statement->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Unsupported statement kind: ");
        pWriter__write__int64(stderr_writer, statement->kind);
        pWriter__end_location_message(stderr_writer);
        panic();
    }
}

Checked_Source *lower(Checked_Source *checked_source) {
    Lowerer lowerer = (Lowerer){
        .symbols = checked_source->symbols,
        .bool_type = checked_source->bool_type,
    };

    Checked_Symbol *symbol = lowerer.symbols->first_symbol;
    while (symbol != NULL) {
        if (symbol->kind == CHECKED_SYMBOL_KIND__PROCEDURE) {
            Checked_Procedure_Symbol *procedure_symbol = (Checked_Procedure_Symbol *)symbol;
            if (!procedure_symbol->parsed_procedure_statement->is_external && procedure_symbol->checked_block_statement != NULL) {
                lowerer.checked_package = procedure_symbol->super.package;
                lowerer.return_type = procedure_symbol->procedure_type->return_type;
                lowerer.temp_variable_counter = 0;
                procedure_symbol->checked_block_statement = Lowerer__lower_statement(&lowerer, procedure_symbol->checked_block_statement);
            }
        }
        symbol = symbol->next_symbol;
    }

    return checked_source;
}
