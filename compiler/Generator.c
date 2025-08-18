#include "Generator.h"
#include "CDECL.h"
#include "File.h"

typedef struct Generator {
    Writer *writer;
    uint16_t indentation;
    Checked_Defer_Statement *top_defer_statement;
    Checked_Defer_Statement *loop_top_defer_statement;
} Generator;

Generator Generator__make(Writer *writer) {
    return (Generator){
        .writer = writer,
        .indentation = 0,
        .top_defer_statement = NULL,
        .loop_top_defer_statement = NULL,
    };
}

void Generator__write_source_location(Generator *self, Source_Location location) {
    pWriter__write__cstring(self->writer, "#line ");
    pWriter__write__int64(self->writer, location.start_line);
    pWriter__write__cstring(self->writer, " \"");
    pWriter__write__string(self->writer, location.source->file_path);
    pWriter__write__cstring(self->writer, "\"\n");
}

void Generator__generate_expression(Generator *self, Checked_Expression *expression);

void Generator__generate_add_expression(Generator *self, Checked_Add_Expression *expression) {
    Generator__generate_expression(self, expression->super.left_expression);
    pWriter__write__cstring(self->writer, " + ");
    Generator__generate_expression(self, expression->super.right_expression);
}

void Generator__generate_address_of_expression(Generator *self, Checked_Address_Of_Expression *expression) {
    Checked_Expression *other_expression = expression->super.other_expression;
    switch (other_expression->kind) {
    case CHECKED_EXPRESSION_KIND__MEMBER_ACCESS:
    case CHECKED_EXPRESSION_KIND__SYMBOL:
        pWriter__write__cstring(self->writer, "&");
        Generator__generate_expression(self, other_expression);
        break;
    default:
        pWriter__begin_location_message(stderr_writer, other_expression->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Address-of expression was not properly decomposed");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
}

void Generator__generate_alloc_expression(Generator *self, Checked_Alloc_Expression *expression) {
    if (expression->value_expression != NULL) {
        pWriter__begin_location_message(stderr_writer, expression->super.location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Alloc expression was not properly decomposed");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    pWriter__write__char(self->writer, '(');
    pWriter__write__cdecl(self->writer, NULL, (Checked_Type *)expression->super.type);
    pWriter__write__cstring(self->writer, ")malloc(sizeof(");
    pWriter__write__cdecl(self->writer, NULL, ((Checked_Pointer_Type *)expression->super.type)->other_type);
    pWriter__write__cstring(self->writer, "))");
}

void Generator__generate_array_access_expression(Generator *self, Checked_Array_Access_Expression *expression) {
    Generator__generate_expression(self, expression->array_expression);
    pWriter__write__cstring(self->writer, "[");
    Generator__generate_expression(self, expression->index_expression);
    pWriter__write__cstring(self->writer, "]");
}

void Generator__generate_bool_expression(Generator *self, Checked_Bool_Expression *expression) {
    if (expression->value) {
        pWriter__write__cstring(self->writer, "true");
    } else {
        pWriter__write__cstring(self->writer, "false");
    }
}

void Generator__generate_call_expression(Generator *self, Checked_Call_Expression *expression) {
    Generator__generate_expression(self, expression->callee_expression);
    pWriter__write__cstring(self->writer, "(");
    Checked_Call_Argument *argument = expression->first_argument;
    while (argument != NULL) {
        Generator__generate_expression(self, argument->expression);
        argument = argument->next_argument;
        if (argument != NULL) {
            pWriter__write__cstring(self->writer, ", ");
        }
    }
    pWriter__write__cstring(self->writer, ")");
}

void Generator__generate_cast_expression(Generator *self, Checked_Cast_Expression *expression) {
    pWriter__write__cstring(self->writer, "((");
    pWriter__write__cdecl(self->writer, NULL, expression->super.type);
    pWriter__write__cstring(self->writer, ") ");
    Generator__generate_expression(self, expression->other_expression);
    pWriter__write__char(self->writer, ')');
}

void pWriter__write__octal_escaped_char(Writer *writer, char value) {
    pWriter__write__char(writer, '\\');
    if (value > (char)64) {
        pWriter__write__char(writer, value / (char)64 % (char)8 + '0');
    }
    if (value > (char)8) {
        pWriter__write__char(writer, value / (char)8 % (char)8 + '0');
    }
    pWriter__write__char(writer, value % (char)8 + '0');
}

void pWriter__write__escaped_char(Writer *writer, char ch) {
    if (ch < (char)32) {
        if (ch == '\n') {
            pWriter__write__cstring(writer, "\\n");
        } else if (ch == '\t') {
            pWriter__write__cstring(writer, "\\t");
        } else {
            pWriter__write__octal_escaped_char(writer, ch);
        }
    } else if (ch < (char)127) {
        if (ch == '\"') {
            pWriter__write__cstring(writer, "\\\"");
        } else if (ch == '\'') {
            pWriter__write__cstring(writer, "\\'");
        } else if (ch == '\\') {
            pWriter__write__cstring(writer, "\\\\");
        } else {
            pWriter__write__char(writer, ch);
        }
    } else {
        pWriter__write__octal_escaped_char(writer, ch);
    }
}

void Generator__generate_character_expression(Generator *self, Checked_Character_Expression *expression) {
    pWriter__write__char(self->writer, '\'');
    pWriter__write__escaped_char(self->writer, expression->value);
    pWriter__write__char(self->writer, '\'');
}

void Generator__generate_dereference_expression(Generator *self, Checked_Dereference_Expression *expression) {
    pWriter__write__cstring(self->writer, "*");
    Generator__generate_expression(self, expression->super.other_expression);
}

void Generator__generate_divide_expression(Generator *self, Checked_Divide_Expression *expression) {
    Generator__generate_expression(self, expression->super.left_expression);
    pWriter__write__cstring(self->writer, " / ");
    Generator__generate_expression(self, expression->super.right_expression);
}

void Generator__generate_equals_expression(Generator *self, Checked_Equals_Expression *expression) {
    Generator__generate_expression(self, expression->super.left_expression);
    pWriter__write__cstring(self->writer, " == ");
    Generator__generate_expression(self, expression->super.right_expression);
}

void Generator__generate_greater_expression(Generator *self, Checked_Greater_Expression *expression) {
    Generator__generate_expression(self, expression->super.left_expression);
    pWriter__write__cstring(self->writer, " > ");
    Generator__generate_expression(self, expression->super.right_expression);
}

void Generator__generate_greater_or_equals_expression(Generator *self, Checked_Greater_Or_Equals_Expression *expression) {
    Generator__generate_expression(self, expression->super.left_expression);
    pWriter__write__cstring(self->writer, " >= ");
    Generator__generate_expression(self, expression->super.right_expression);
}

void Generator__generate_group_expression(Generator *self, Checked_Group_Expression *expression) {
    pWriter__write__cstring(self->writer, "(");
    Generator__generate_expression(self, expression->other_expression);
    pWriter__write__cstring(self->writer, ")");
}

void Generator__generate_integer_expression(Generator *self, Checked_Integer_Expression *expression) {
    uint8_t base = expression->base;
    switch (base) {
    case 10:
        // no prefix
        break;
    case 2:
    case 8:
        base = 16; // change base and fall through
    case 16:
        pWriter__write__cstring(self->writer, "0x");
        break;
    default:
        pWriter__begin_location_message(stderr_writer, expression->super.location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Unsupported integer base: ");
        pWriter__write__int64(stderr_writer, expression->base);
        pWriter__end_location_message(stderr_writer);
        panic();
    }

    // write value in the specified base
    uint64_t temp_value = expression->value;
    char digits[16] = "0123456789abcdef";
    char buffer[20]; // buffer filled in reverse order
    int length = 1;
    do {
        buffer[sizeof(buffer) - 1 - length] = digits[temp_value % base];
        length += 1;
        temp_value = temp_value / base;
    } while (temp_value > 0);
    buffer[sizeof(buffer) - 1] = '\0'; // null-terminate the string
    pWriter__write__cstring(self->writer, buffer + (sizeof(buffer) - length));

    // write type suffix
    switch (expression->super.type->kind) {
    case CHECKED_TYPE_KIND__U32:
    case CHECKED_TYPE_KIND__U64:
    case CHECKED_TYPE_KIND__USIZE:
        pWriter__write__cstring(self->writer, "u");
        break;
    case CHECKED_TYPE_KIND__I64:
        pWriter__write__cstring(self->writer, "l");
        break;
    default:
        // ingore
        break;
    }
}

void Generator__generate_is_variant_case_expression(Generator *self, Checked_Is_Variant_Case_Expression *expression) {
    Generator__generate_expression(self, expression->variant_expression);
    pWriter__write__cstring(self->writer, ".variant");
    if (expression->is_not) {
        pWriter__write__cstring(self->writer, " != ");
    } else {
        pWriter__write__cstring(self->writer, " == ");
    }
    pWriter__write__int64(self->writer, expression->variant_case->index);
}

void Generator__generate_less_expression(Generator *self, Checked_Less_Expression *expression) {
    Generator__generate_expression(self, expression->super.left_expression);
    pWriter__write__cstring(self->writer, " < ");
    Generator__generate_expression(self, expression->super.right_expression);
}

void Generator__generate_less_or_equals_expression(Generator *self, Checked_Less_Or_Equals_Expression *expression) {
    Generator__generate_expression(self, expression->super.left_expression);
    pWriter__write__cstring(self->writer, " <= ");
    Generator__generate_expression(self, expression->super.right_expression);
}

void Generator__generate_logic_and_expression(Generator *self, Checked_Logic_And_Expression *expression) {
    Generator__generate_expression(self, expression->super.left_expression);
    pWriter__write__cstring(self->writer, " && ");
    Generator__generate_expression(self, expression->super.right_expression);
}

void Generator__generate_logic_or_expression(Generator *self, Checked_Logic_Or_Expression *expression) {
    Generator__generate_expression(self, expression->super.left_expression);
    pWriter__write__cstring(self->writer, " || ");
    Generator__generate_expression(self, expression->super.right_expression);
}

void Generator__generate_make_struct_expression(Generator *self, Checked_Make_Struct_Expression *expression) {
    pWriter__write__char(self->writer, '(');
    pWriter__write__cdecl(self->writer, NULL, (Checked_Type *)expression->struct_type);
    pWriter__write__cstring(self->writer, "){");
    Checked_Make_Struct_Argument *argument = expression->first_argument;
    while (argument != NULL) {
        pWriter__write__char(self->writer, '.');
        pWriter__write__string(self->writer, argument->struct_member->name);
        pWriter__write__cstring(self->writer, " = ");
        Generator__generate_expression(self, argument->expression);
        argument = argument->next_argument;
        if (argument != NULL) {
            pWriter__write__cstring(self->writer, ", ");
        }
    }
    pWriter__write__char(self->writer, '}');
}

void Generator__generate_make_variant_expression(Generator *self, Checked_Make_Variant_Expression *expression) {
    pWriter__write__char(self->writer, '(');
    pWriter__write__cdecl(self->writer, NULL, (Checked_Type *)expression->variant_type);
    pWriter__write__cstring(self->writer, "){.variant = ");
    pWriter__write__int64(self->writer, expression->variant_case->index);
    if (expression->variant_case->index > 0) {
        pWriter__write__cstring(self->writer, ", .variant_");
        pWriter__write__int64(self->writer, expression->variant_case->index);
        pWriter__write__cstring(self->writer, " = ");
        Generator__generate_expression(self, expression->expression);
    }
    pWriter__write__char(self->writer, '}');
}

void Generator__generate_member_access_expression(Generator *self, Checked_Member_Access_Expression *expression) {
    Generator__generate_expression(self, expression->object_expression);
    if (expression->object_expression->type->kind == CHECKED_TYPE_KIND__POINTER) {
        pWriter__write__cstring(self->writer, "->");
    } else {
        pWriter__write__cstring(self->writer, ".");
    }
    pWriter__write__string(self->writer, expression->member->name);
}

void Generator__generate_minus_expression(Generator *self, Checked_Minus_Expression *expression) {
    pWriter__write__cstring(self->writer, "-");
    Generator__generate_expression(self, expression->super.other_expression);
}

void Generator__generate_modulo_expression(Generator *self, Checked_Modulo_Expression *expression) {
    Generator__generate_expression(self, expression->super.left_expression);
    pWriter__write__cstring(self->writer, " % ");
    Generator__generate_expression(self, expression->super.right_expression);
}

void Generator__generate_multiply_expression(Generator *self, Checked_Multiply_Expression *expression) {
    Generator__generate_expression(self, expression->super.left_expression);
    pWriter__write__cstring(self->writer, " * ");
    Generator__generate_expression(self, expression->super.right_expression);
}

void Generator__generate_not_expression(Generator *self, Checked_Not_Expression *expression) {
    pWriter__write__char(self->writer, '!');
    Generator__generate_expression(self, expression->super.other_expression);
}

void Generator__generate_not_equals_expression(Generator *self, Checked_Not_Equals_Expression *expression) {
    Generator__generate_expression(self, expression->super.left_expression);
    pWriter__write__cstring(self->writer, " != ");
    Generator__generate_expression(self, expression->super.right_expression);
}

void Generator__generate_null_expression(Generator *self, Checked_Null_Expression *expression) {
    pWriter__write__cstring(self->writer, "NULL");
}

void Generator__generate_result_expression(Generator *self, Checked_Result_Expression *expression) {
    pWriter__write__char(self->writer, '(');
    pWriter__write__cdecl(self->writer, NULL, expression->super.type);
    pWriter__write__cstring(self->writer, "){.success = ");
    if (expression->raise_expression == NULL) {
        pWriter__write__cstring(self->writer, "true");
        if (expression->return_expression != NULL && expression->return_expression->type->kind != CHECKED_TYPE_KIND__NOTHING) {
            pWriter__write__cstring(self->writer, ", .value = ");
            Generator__generate_expression(self, expression->return_expression);
        }
    } else {
        pWriter__write__cstring(self->writer, "false, .error = ");
        Generator__generate_expression(self, expression->raise_expression);
    }
    pWriter__write__cstring(self->writer, "}");
}

void Generator__generate_result_error_expression(Generator *self, Checked_Result_Error_Expression *expression) {
    Generator__generate_expression(self, expression->result_expression);
    pWriter__write__cstring(self->writer, ".error");
}

void Generator__generate_result_success_expression(Generator *self, Checked_Result_Success_Expression *expression) {
    Generator__generate_expression(self, expression->result_expression);
    pWriter__write__cstring(self->writer, ".success");
}

void Generator__generate_result_value_expression(Generator *self, Checked_Result_Value_Expression *expression) {
    Generator__generate_expression(self, expression->result_expression);
    pWriter__write__cstring(self->writer, ".value");
}

void Generator__generate_sizeof_expression(Generator *self, Checked_Sizeof_Expression *expression) {
    pWriter__write__cstring(self->writer, "sizeof(");
    pWriter__write__cdecl(self->writer, NULL, expression->sized_type);
    pWriter__write__cstring(self->writer, ")");
}

void Generator__generate_string_expression(Generator *self, Checked_String_Expression *expression) {
    pWriter__write__cstring(self->writer, "(struct String){.data = ");
    if (expression->value->length == 0) {
        pWriter__write__int64(self->writer, 0);
    } else {
        pWriter__write__char(self->writer, '"');
        size_t index = 0;
        while (index < expression->value->length) {
            pWriter__write__escaped_char(self->writer, expression->value->data[index]);
            index = index + 1;
        }
        pWriter__write__char(self->writer, '"');
    }
    pWriter__write__cstring(self->writer, ", .length = ");
    pWriter__write__int64(self->writer, expression->value->length);
    pWriter__write__char(self->writer, '}');
}

void Generator__generate_string_length_expression(Generator *self, Checked_String_Length_Expression *expression) {
    Generator__generate_expression(self, expression->string_expression);
    if (expression->string_expression->type->kind == CHECKED_TYPE_KIND__POINTER) {
        pWriter__write__cstring(self->writer, "->");
    } else {
        pWriter__write__char(self->writer, '.');
    }
    pWriter__write__cstring(self->writer, "length");
}

void Generator__generate_subtract_expression(Generator *self, Checked_Subtract_Expression *expression) {
    Generator__generate_expression(self, expression->super.left_expression);
    pWriter__write__cstring(self->writer, " - ");
    Generator__generate_expression(self, expression->super.right_expression);
}

void Generator__generate_symbol_expression(Generator *self, Checked_Symbol_Expression *expression) {
    switch (expression->symbol->kind) {
    case CHECKED_SYMBOL_KIND__PROCEDURE: {
        CDECL_Procedure_Name procedure_name = CDECL_Procedure_Name__create((Checked_Procedure_Symbol *)expression->symbol);
        procedure_name.super.write((CDECL_Name *)&procedure_name, self->writer);
        break;
    }
    case CHECKED_SYMBOL_KIND__RESULT_ERROR: {
        Checked_Result_Error_Symbol *result_error_symbol = (Checked_Result_Error_Symbol *)expression->symbol;
        Generator__generate_expression(self, result_error_symbol->expression);
        break;
    }
    case CHECKED_SYMBOL_KIND__VARIANT_SWITCH_CASE: {
        Checked_Variant_Switch_Case_Symbol *variant_symbol = (Checked_Variant_Switch_Case_Symbol *)expression->symbol;
        if (variant_symbol->variant_expression->temp_variable_name == NULL) {
            Generator__generate_expression(self, variant_symbol->variant_expression);
        } else {
            pWriter__write__string(self->writer, variant_symbol->variant_expression->temp_variable_name);
        }
        if (variant_symbol->variant_expression->type->kind == CHECKED_TYPE_KIND__POINTER) {
            pWriter__write__cstring(self->writer, "->");
        } else {
            pWriter__write__char(self->writer, '.');
        }
        pWriter__write__cstring(self->writer, "variant_");
        pWriter__write__int64(self->writer, variant_symbol->variant_case->index);
        break;
    }
    case CHECKED_SYMBOL_KIND__VARIABLE: {
        CDECL_Variable_Name variable_name = CDECL_Variable_Name__create((Checked_Variable_Symbol *)expression->symbol);
        variable_name.super.write((CDECL_Name *)&variable_name, self->writer);
        break;
    }
    default:
        pWriter__write__string(self->writer, expression->symbol->name);
    }
}

void Generator__generate_expression(Generator *self, Checked_Expression *expression) {
    switch (expression->kind) {
    case CHECKED_EXPRESSION_KIND__ADD:
        Generator__generate_add_expression(self, (Checked_Add_Expression *)expression);
        break;
    case CHECKED_EXPRESSION_KIND__ADDRESS_OF:
        Generator__generate_address_of_expression(self, (Checked_Address_Of_Expression *)expression);
        break;
    case CHECKED_EXPRESSION_KIND__ALLOC:
        Generator__generate_alloc_expression(self, (Checked_Alloc_Expression *)expression);
        break;
    case CHECKED_EXPRESSION_KIND__ARRAY_ACCESS:
        Generator__generate_array_access_expression(self, (Checked_Array_Access_Expression *)expression);
        break;
    case CHECKED_EXPRESSION_KIND__BOOL:
        Generator__generate_bool_expression(self, (Checked_Bool_Expression *)expression);
        break;
    case CHECKED_EXPRESSION_KIND__CALL:
        Generator__generate_call_expression(self, (Checked_Call_Expression *)expression);
        break;
    case CHECKED_EXPRESSION_KIND__CAST:
        Generator__generate_cast_expression(self, (Checked_Cast_Expression *)expression);
        break;
    case CHECKED_EXPRESSION_KIND__CHARACTER:
        Generator__generate_character_expression(self, (Checked_Character_Expression *)expression);
        break;
    case CHECKED_EXPRESSION_KIND__DEREFERENCE:
        Generator__generate_dereference_expression(self, (Checked_Dereference_Expression *)expression);
        break;
    case CHECKED_EXPRESSION_KIND__DIVIDE:
        Generator__generate_divide_expression(self, (Checked_Divide_Expression *)expression);
        break;
    case CHECKED_EXPRESSION_KIND__EQUALS:
        Generator__generate_equals_expression(self, (Checked_Equals_Expression *)expression);
        break;
    case CHECKED_EXPRESSION_KIND__GREATER:
        Generator__generate_greater_expression(self, (Checked_Greater_Expression *)expression);
        break;
    case CHECKED_EXPRESSION_KIND__GREATER_OR_EQUALS:
        Generator__generate_greater_or_equals_expression(self, (Checked_Greater_Or_Equals_Expression *)expression);
        break;
    case CHECKED_EXPRESSION_KIND__GROUP:
        Generator__generate_group_expression(self, (Checked_Group_Expression *)expression);
        break;
    case CHECKED_EXPRESSION_KIND__INTEGER:
        Generator__generate_integer_expression(self, (Checked_Integer_Expression *)expression);
        break;
    case CHECKED_EXPRESSION_KIND__IS_VARIANT_CASE:
        Generator__generate_is_variant_case_expression(self, (Checked_Is_Variant_Case_Expression *)expression);
        break;
    case CHECKED_EXPRESSION_KIND__LESS:
        Generator__generate_less_expression(self, (Checked_Less_Expression *)expression);
        break;
    case CHECKED_EXPRESSION_KIND__LESS_OR_EQUALS:
        Generator__generate_less_or_equals_expression(self, (Checked_Less_Or_Equals_Expression *)expression);
        break;
    case CHECKED_EXPRESSION_KIND__LOGIC_AND:
        Generator__generate_logic_and_expression(self, (Checked_Logic_And_Expression *)expression);
        break;
    case CHECKED_EXPRESSION_KIND__LOGIC_OR:
        Generator__generate_logic_or_expression(self, (Checked_Logic_Or_Expression *)expression);
        break;
    case CHECKED_EXPRESSION_KIND__MAKE_STRUCT:
        Generator__generate_make_struct_expression(self, (Checked_Make_Struct_Expression *)expression);
        break;
    case CHECKED_EXPRESSION_KIND__MAKE_VARIANT:
        Generator__generate_make_variant_expression(self, (Checked_Make_Variant_Expression *)expression);
        break;
    case CHECKED_EXPRESSION_KIND__MEMBER_ACCESS:
        Generator__generate_member_access_expression(self, (Checked_Member_Access_Expression *)expression);
        break;
    case CHECKED_EXPRESSION_KIND__MINUS:
        Generator__generate_minus_expression(self, (Checked_Minus_Expression *)expression);
        break;
    case CHECKED_EXPRESSION_KIND__MODULO:
        Generator__generate_modulo_expression(self, (Checked_Modulo_Expression *)expression);
        break;
    case CHECKED_EXPRESSION_KIND__MULTIPLY:
        Generator__generate_multiply_expression(self, (Checked_Multiply_Expression *)expression);
        break;
    case CHECKED_EXPRESSION_KIND__NOT:
        Generator__generate_not_expression(self, (Checked_Not_Expression *)expression);
        break;
    case CHECKED_EXPRESSION_KIND__NOT_EQUALS:
        Generator__generate_not_equals_expression(self, (Checked_Not_Equals_Expression *)expression);
        break;
    case CHECKED_EXPRESSION_KIND__NOTHING:
        break; // nothing to generate
    case CHECKED_EXPRESSION_KIND__NULL:
        Generator__generate_null_expression(self, (Checked_Null_Expression *)expression);
        break;
    case CHECKED_EXPRESSION_KIND__RESULT:
        Generator__generate_result_expression(self, (Checked_Result_Expression *)expression);
        break;
    case CHECKED_EXPRESSION_KIND__RESULT_ERROR:
        Generator__generate_result_error_expression(self, (Checked_Result_Error_Expression *)expression);
        break;
    case CHECKED_EXPRESSION_KIND__RESULT_SUCCESS:
        Generator__generate_result_success_expression(self, (Checked_Result_Success_Expression *)expression);
        break;
    case CHECKED_EXPRESSION_KIND__RESULT_VALUE:
        Generator__generate_result_value_expression(self, (Checked_Result_Value_Expression *)expression);
        break;
    case CHECKED_EXPRESSION_KIND__SIZEOF:
        Generator__generate_sizeof_expression(self, (Checked_Sizeof_Expression *)expression);
        break;
    case CHECKED_EXPRESSION_KIND__STRING:
        Generator__generate_string_expression(self, (Checked_String_Expression *)expression);
        break;
    case CHECKED_EXPRESSION_KIND__STRING_LENGTH:
        Generator__generate_string_length_expression(self, (Checked_String_Length_Expression *)expression);
        break;
    case CHECKED_EXPRESSION_KIND__SUBTRACT:
        Generator__generate_subtract_expression(self, (Checked_Subtract_Expression *)expression);
        break;
    case CHECKED_EXPRESSION_KIND__SYMBOL:
        Generator__generate_symbol_expression(self, (Checked_Symbol_Expression *)expression);
        break;
    default:
        pWriter__begin_location_message(stderr_writer, expression->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Unsupported expression");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
}

void Generator__write_indentation(Generator *self) {
    uint16_t indentation = self->indentation;
    while (indentation > 0) {
        pWriter__write__cstring(self->writer, "    ");
        indentation = indentation - 1;
    }
}

void Generator__generate_statement(Generator *self, Checked_Statement *statement);
void Generator__generate_statement_inlined(Generator *self, Checked_Statement *statement, bool is_inlined);

void Generator__generate_assignment_statement(Generator *self, Checked_Assignment_Statement *statement) {
    Generator__generate_expression(self, statement->object_expression);
    pWriter__write__cstring(self->writer, " = ");
    Generator__generate_expression(self, statement->value_expression);
    pWriter__write__cstring(self->writer, ";");
}

void Generator__generate_block_statement(Generator *self, Checked_Block_Statement *block_statement) {
    pWriter__write__cstring(self->writer, "{\n");

    // Save the current defer statement stack
    Checked_Defer_Statement *first_defer_statement = self->top_defer_statement;

    // Increase indentation for block statements
    self->indentation = self->indentation + 1;

    // Generate the block statements
    Checked_Statement *statement = block_statement->statements->first_statement;
    while (statement != NULL) {
        Generator__generate_statement(self, statement);
        statement = statement->next_statement;
    }

    // Generate the deferred statements
    Checked_Statement *last_statement = block_statement->statements->last_statement;
    if (last_statement != NULL && !Checked_Statement__is_terminal(last_statement) && last_statement->kind != CHECKED_STATEMENT_KIND__BREAK) {
        Checked_Defer_Statement *defer_statement = self->top_defer_statement;
        while (defer_statement != first_defer_statement) {
            Generator__generate_statement(self, defer_statement->statement);
            defer_statement = defer_statement->prev_defer_statement;
        }
    }

    // Decrease indentation for block statements
    self->indentation = self->indentation - 1;

    // Restore the previous defer statement stack
    self->top_defer_statement = first_defer_statement;

    Source_Location location = block_statement->super.location;
    location.start_line = location.end_line;
    location.start_column = location.end_column;
    Generator__write_source_location(self, location);
    Generator__write_indentation(self);
    pWriter__write__cstring(self->writer, "}");
}

void Generator__generate_break_statement(Generator *self, Checked_Break_Statement *statement) {
    pWriter__write__cstring(self->writer, "break;");
}

void Generator__generate_decomposed_statement(Generator *self, Checked_Decomposed_Statement *decomposed_statement, bool inlined) {
    Checked_Statement *statement = decomposed_statement->statements->first_statement;
    while (statement != NULL) {
        Generator__generate_statement_inlined(self, statement, inlined);
        statement = statement->next_statement;
    }
}

void Generator__generate_expression_statement(Generator *self, Checked_Expression_Statement *statement) {
    Generator__generate_expression(self, statement->expression);
    pWriter__write__cstring(self->writer, ";");
}

void Generator__generate_if_statement(Generator *self, Checked_If_Statement *statement) {
    pWriter__write__cstring(self->writer, "if (");
    Generator__generate_expression(self, statement->condition_expression);
    pWriter__write__cstring(self->writer, ") ");
    if (statement->true_statement != NULL) {
        Generator__generate_statement_inlined(self, statement->true_statement, true);
    } else {
        pWriter__write__cstring(self->writer, "{}");
    }
    if (statement->false_statement != NULL) {
        pWriter__write__cstring(self->writer, " else ");
        Generator__generate_statement_inlined(self, statement->false_statement, true);
    }
}

void Generator__generate_loop_statement(Generator *self, Checked_Loop_Statement *statement) {
    // Save the current defer statement stack
    Checked_Defer_Statement *loop_top_defer_statement = self->loop_top_defer_statement;
    self->loop_top_defer_statement = self->top_defer_statement;

    pWriter__write__cstring(self->writer, "for (;;) ");
    Generator__generate_statement_inlined(self, statement->body_statement, true);

    // Restore the previous defer statement stack
    self->loop_top_defer_statement = loop_top_defer_statement;
}

void Generator__generate_return_statement(Generator *self, Checked_Return_Statement *statement) {
    pWriter__write__cstring(self->writer, "return");
    if (statement->expression != NULL) {
        pWriter__write__cstring(self->writer, " ");
        Generator__generate_expression(self, statement->expression);
    }
    pWriter__write__cstring(self->writer, ";");
}

void Generator__generate_if_variant_case_statement(Generator *self, Checked_If_Variant_Case_Statement *statement) {
    pWriter__write__cstring(self->writer, "if (");
    Generator__generate_expression(self, statement->variant_expression);
    pWriter__write__cstring(self->writer, ".variant == ");
    pWriter__write__int64(self->writer, statement->variant_case->index);
    pWriter__write__cstring(self->writer, ") ");
    Generator__generate_statement_inlined(self, statement->true_statement, true);
    if (statement->false_statement != NULL) {
        pWriter__write__cstring(self->writer, " else ");
        Generator__generate_statement_inlined(self, statement->false_statement, true);
    }
}

void Generator__generate_variant_switch_statement(Generator *self, Checked_Variant_Switch_Statement *statement) {
    // The switch statement is generated as if-else statements to allow the use of break statements within the cases.

    // Store the expression in a variable to avoid evaluating it multiple times.
    statement->expression->temp_variable_name = String__create_from("__switch_");
    String__append_int16_t(statement->expression->temp_variable_name, statement->super.location.start_line);
    String__append_cstring(statement->expression->temp_variable_name, "_value__");
    CDECL_Local_Name temp_variable_name = CDECL_Local_Name__create(statement->expression->temp_variable_name);
    pWriter__write__cdecl(self->writer, (CDECL_Name *)&temp_variable_name, statement->expression->type);
    pWriter__write__cstring(self->writer, " = ");
    Generator__generate_expression(self, statement->expression);
    pWriter__write__char(self->writer, ';');

    Checked_Variant_Switch_Case *variant_switch_case = statement->first_variant_switch_case;
    for (; variant_switch_case != NULL; variant_switch_case = variant_switch_case->next_switch_variant_case) {
        pWriter__end_line(self->writer);
        Generator__write_source_location(self, variant_switch_case->location);
        Generator__write_indentation(self);
        if (variant_switch_case != statement->first_variant_switch_case) {
            pWriter__write__cstring(self->writer, "else ");
        }
        pWriter__write__cstring(self->writer, "if (");
        pWriter__write__string(self->writer, statement->expression->temp_variable_name);
        if (statement->expression->type->kind == CHECKED_TYPE_KIND__POINTER) {
            pWriter__write__cstring(self->writer, "->");
        } else {
            pWriter__write__char(self->writer, '.');
        }
        pWriter__write__cstring(self->writer, "variant == ");
        pWriter__write__int64(self->writer, variant_switch_case->variant_case->index);
        pWriter__write__cstring(self->writer, ") ");
        Generator__generate_statement_inlined(self, variant_switch_case->statement, true);
    }

    if (statement->switch_else) {
        pWriter__end_line(self->writer);
        Generator__write_source_location(self, statement->switch_else->location);
        Generator__write_indentation(self);
        if (statement->first_variant_switch_case != NULL) {
            pWriter__write__cstring(self->writer, "else ");
        }
        Generator__generate_statement_inlined(self, statement->switch_else->statement, true);
    }
}

void Generator__declare_variable(Generator *self, Checked_Variable_Statement *statement) {
    pWriter__write__cstring(self->writer, "extern ");
    CDECL_Variable_Name variable_name = CDECL_Variable_Name__create(statement->variable);
    pWriter__write__cdecl(self->writer, (CDECL_Name *)&variable_name, statement->variable->super.type);
    pWriter__write__char(self->writer, ';');
}

void Generator__generate_variable_statement(Generator *self, Checked_Variable_Statement *statement) {
    if (statement->is_external) {
        pWriter__write__cstring(self->writer, "extern ");
    }
    CDECL_Variable_Name variable_name = CDECL_Variable_Name__create(statement->variable);
    pWriter__write__cdecl(self->writer, (CDECL_Name *)&variable_name, statement->variable->super.type);
    if (statement->expression != NULL) {
        pWriter__write__cstring(self->writer, " = ");
        Generator__generate_expression(self, statement->expression);
    }
    pWriter__write__cstring(self->writer, ";");
}

void Generator__generate_while_statement(Generator *self, Checked_While_Statement *statement) {
    // Save the current defer statement stack
    Checked_Defer_Statement *loop_top_defer_statement = self->loop_top_defer_statement;
    self->loop_top_defer_statement = self->top_defer_statement;

    pWriter__write__cstring(self->writer, "while (");
    Generator__generate_expression(self, statement->condition_expression);
    pWriter__write__cstring(self->writer, ") ");
    Generator__generate_statement_inlined(self, statement->body_statement, true);

    // Restore the previous defer statement stack
    self->loop_top_defer_statement = loop_top_defer_statement;
}

void Generator__generate_yield_statement(Generator *self, Checked_Yield_Statement *statement) {
    if (statement->block_result_expression == NULL) {
        pWriter__begin_location_message(self->writer, statement->super.location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(self->writer, "Yield expression was not properly decomposed");
        pWriter__end_location_message(self->writer);
        panic();
    }
    Generator__generate_expression(self, statement->block_result_expression);
    pWriter__write__cstring(self->writer, " = ");
    Generator__generate_expression(self, statement->expression);
    pWriter__write__cstring(self->writer, ";");
}

void Generator__generate_statement_inlined(Generator *self, Checked_Statement *statement, bool inlined) {
    switch (statement->kind) {
    case CHECKED_STATEMENT_KIND__BREAK: {
        Checked_Defer_Statement *defer_statement = self->top_defer_statement;
        while (defer_statement != self->loop_top_defer_statement) {
            Generator__generate_statement_inlined(self, defer_statement->statement, inlined);
            defer_statement = defer_statement->prev_defer_statement;
        }
        break;
    }
    case CHECKED_STATEMENT_KIND__DECOMPOSED: {
        Generator__generate_decomposed_statement(self, (Checked_Decomposed_Statement *)statement, inlined);
        return;
    }
    case CHECKED_STATEMENT_KIND__DEFER: {
        // Push the defer statement onto the stack
        Checked_Defer_Statement *defer_statement = (Checked_Defer_Statement *)statement;
        defer_statement->prev_defer_statement = self->top_defer_statement;
        self->top_defer_statement = defer_statement;
        return;
    }
    case CHECKED_STATEMENT_KIND__RETURN: {
        Checked_Defer_Statement *defer_statement = self->top_defer_statement;
        while (defer_statement != NULL) {
            Generator__generate_statement_inlined(self, defer_statement->statement, inlined);
            defer_statement = defer_statement->prev_defer_statement;
        }
        break;
    }
    default:
        break;
    }
    if (!inlined) {
        Generator__write_source_location(self, statement->location);
        Generator__write_indentation(self);
    }
    switch (statement->kind) {
    case CHECKED_STATEMENT_KIND__ASSIGNMENT:
        Generator__generate_assignment_statement(self, (Checked_Assignment_Statement *)statement);
        break;
    case CHECKED_STATEMENT_KIND__BLOCK:
        Generator__generate_block_statement(self, (Checked_Block_Statement *)statement);
        break;
    case CHECKED_STATEMENT_KIND__BREAK:
        Generator__generate_break_statement(self, (Checked_Break_Statement *)statement);
        break;
    case CHECKED_STATEMENT_KIND__EXPRESSION:
        Generator__generate_expression_statement(self, (Checked_Expression_Statement *)statement);
        break;
    case CHECKED_STATEMENT_KIND__IF:
        Generator__generate_if_statement(self, (Checked_If_Statement *)statement);
        break;
    case CHECKED_STATEMENT_KIND__LOOP:
        Generator__generate_loop_statement(self, (Checked_Loop_Statement *)statement);
        break;
    case CHECKED_STATEMENT_KIND__RETURN:
        Generator__generate_return_statement(self, (Checked_Return_Statement *)statement);
        break;
    case CHECKED_STATEMENT_KIND__VARIANT_IF:
        Generator__generate_if_variant_case_statement(self, (Checked_If_Variant_Case_Statement *)statement);
        break;
    case CHECKED_STATEMENT_KIND__VARIANT_SWITCH:
        Generator__generate_variant_switch_statement(self, (Checked_Variant_Switch_Statement *)statement);
        break;
    case CHECKED_STATEMENT_KIND__VARIABLE:
        Generator__generate_variable_statement(self, (Checked_Variable_Statement *)statement);
        break;
    case CHECKED_STATEMENT_KIND__WHILE:
        Generator__generate_while_statement(self, (Checked_While_Statement *)statement);
        break;
    case CHECKED_STATEMENT_KIND__YIELD:
        Generator__generate_yield_statement(self, (Checked_Yield_Statement *)statement);
        break;
    default:
        pWriter__begin_location_message(stderr_writer, statement->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Unsupported statement");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    if (!inlined) {
        pWriter__end_line(self->writer);
    }
}

void Generator__generate_statement(Generator *self, Checked_Statement *statement) {
    Generator__generate_statement_inlined(self, statement, false);
}

void Generator__declare_external_type(Generator *self, Checked_External_Type *external_type) {
    pWriter__write__cdecl(self->writer, NULL, (Checked_Type *)external_type);
    pWriter__write__cstring(self->writer, ";\n");
}

void Generator__declare_procedure(Generator *self, Checked_Procedure_Symbol *procedure_symbol) {
    CDECL_Procedure_Name procedure_name = CDECL_Procedure_Name__create(procedure_symbol);
    pWriter__write__cdecl(self->writer, (CDECL_Name *)&procedure_name, (Checked_Type *)procedure_symbol->procedure_type);
    pWriter__write__cstring(self->writer, ";\n");
}

void Generator__generate_procedure(Generator *self, Checked_Procedure_Symbol *procedure_symbol) {
    if (procedure_symbol->checked_block_statement == NULL) {
        return;
    }
    Generator__write_source_location(self, procedure_symbol->super.location);
    CDECL_Procedure_Name procedure_name = CDECL_Procedure_Name__create(procedure_symbol);
    pWriter__write__cdecl(self->writer, (CDECL_Name *)&procedure_name, (Checked_Type *)procedure_symbol->procedure_type);
    pWriter__write__char(self->writer, ' ');
    Generator__generate_statement_inlined(self, procedure_symbol->checked_block_statement, true);
    pWriter__write__cstring(self->writer, "\n\n");
}

void Generator__generate_result_type(Generator *self, Checked_Result_Type *result_type) {
    pWriter__write__cdecl(self->writer, NULL, (Checked_Type *)result_type);
    pWriter__write__cstring(self->writer, " {\n");
    pWriter__write__cstring(self->writer, "    bool success;\n");
    pWriter__write__cstring(self->writer, "    union {\n");
    if (result_type->return_type->kind != CHECKED_TYPE_KIND__NOTHING) {
        pWriter__write__cstring(self->writer, "        ");
        String result_field_name = {.data = "value", .length = 5};
        CDECL_Local_Name result_name = CDECL_Local_Name__create(&result_field_name);
        pWriter__write__cdecl(self->writer, (CDECL_Name *)&result_name, result_type->return_type);
        pWriter__write__cstring(self->writer, ";\n");
    }
    if (result_type->raise_type->kind != CHECKED_TYPE_KIND__NOTHING) {
        pWriter__write__cstring(self->writer, "        ");
        String error_field_name = {.data = "error", .length = 5};
        CDECL_Local_Name error_name = CDECL_Local_Name__create(&error_field_name);
        pWriter__write__cdecl(self->writer, (CDECL_Name *)&error_name, result_type->raise_type);
        pWriter__write__cstring(self->writer, ";\n");
    }
    pWriter__write__cstring(self->writer, "    };\n");
    pWriter__write__cstring(self->writer, "};\n\n");
}

void Generator__declare_struct(Generator *self, Checked_Struct_Type *struct_type) {
    pWriter__write__cdecl(self->writer, NULL, (Checked_Type *)struct_type);
    pWriter__write__cstring(self->writer, ";\n");
}

void Generator__generate_struct(Generator *self, Checked_Struct_Type *struct_type) {
    Checked_Struct_Member *struct_member = struct_type->first_member;
    if (struct_member == NULL) {
        return;
    }
    pWriter__write__cdecl(self->writer, NULL, (Checked_Type *)struct_type);
    pWriter__write__cstring(self->writer, " {\n");
    while (struct_member != NULL) {
        pWriter__write__cstring(self->writer, "    ");
        CDECL_Local_Name struct_member_name = CDECL_Local_Name__create(struct_member->name);
        pWriter__write__cdecl(self->writer, (CDECL_Name *)&struct_member_name, struct_member->type);
        pWriter__write__cstring(self->writer, ";\n");
        struct_member = struct_member->next_member;
    }
    pWriter__write__cstring(self->writer, "};\n\n");
}

void Generator__declare_trait(Generator *self, Checked_Trait_Type *trait_type) {
    pWriter__write__cdecl(self->writer, NULL, (Checked_Type *)trait_type);
    pWriter__write__cstring(self->writer, ";\n");
}

void Generator__generate_trait(Generator *self, Checked_Trait_Type *trait_type) {
    Generator__generate_struct(self, trait_type->struct_type);
}

void Generator__declare_variant(Generator *self, Checked_Variant_Type *variant_type) {
    pWriter__write__cdecl(self->writer, NULL, (Checked_Type *)variant_type);
    pWriter__write__cstring(self->writer, ";\n");
}

typedef struct CDECL_Variant_Case_Name {
    CDECL_Name super;
    int32_t variant_index;
} CDECL_Variant_Case_Name;

void CDECL_Variant_Case_Name__write(CDECL_Variant_Case_Name *self, Writer *writer) {
    pWriter__write__cstring(writer, "variant_");
    pWriter__write__int64(writer, self->variant_index);
}

CDECL_Variant_Case_Name CDECL_Variant_Case_Name__create(int32_t variant_index) {
    CDECL_Variant_Case_Name name;
    name.super.write = (void (*)(CDECL_Name *, Writer *))CDECL_Variant_Case_Name__write;
    name.variant_index = variant_index;
    return name;
}

void Generator__generate_variant(Generator *self, Checked_Variant_Type *variant_type) {
    pWriter__write__cdecl(self->writer, NULL, (Checked_Type *)variant_type);
    pWriter__write__cstring(self->writer, " {\n");
    pWriter__write__cstring(self->writer, "    int32_t variant;\n");
    Checked_Variant_Case *variant = variant_type->first_variant_case;
    if (variant != NULL) {
        pWriter__write__cstring(self->writer, "    union {\n");
        while (variant != NULL) {
            if (variant->index != 0) {
                pWriter__write__cstring(self->writer, "        ");
                CDECL_Variant_Case_Name variant_name = CDECL_Variant_Case_Name__create(variant->index);
                pWriter__write__cdecl(self->writer, (CDECL_Name *)&variant_name, variant->type);
                pWriter__write__cstring(self->writer, ";\n");
            }
            variant = variant->next_variant;
        }
        pWriter__write__cstring(self->writer, "    };\n");
    }
    pWriter__write__cstring(self->writer, "};\n\n");
}

void Generator__declare_type(Generator *self, Checked_Type *type) {
    if (type->has_generated_declaration || type->has_generated_definition) {
        return; // Already declared
    }
    switch (type->kind) {
    case CHECKED_TYPE_KIND__EXTERNAL:
        Generator__declare_external_type(self, (Checked_External_Type *)type);
        break;
    case CHECKED_TYPE_KIND__STRUCT:
        Generator__declare_struct(self, (Checked_Struct_Type *)type);
        break;
    case CHECKED_TYPE_KIND__TRAIT:
        Generator__declare_trait(self, (Checked_Trait_Type *)type);
        break;
    case CHECKED_TYPE_KIND__VARIANT:
        Generator__declare_variant(self, (Checked_Variant_Type *)type);
        break;
    default:
        panic();
    }
    pWriter__end_line(self->writer);
    type->has_generated_declaration = true;
}

void Generator__define_type(Generator *self, Checked_Type *type) {
    if (type->has_generated_definition) {
        return; // Already defined
    }
    struct Checked_Type_Dependency *dependency = type->first_dependency;
    while (dependency != NULL) {
        if (dependency->type->symbol->super.module == type->symbol->super.module) {
            if (dependency->weak) {
                Generator__declare_type(self, dependency->type);
            } else {
                Generator__define_type(self, dependency->type);
            }
        }
        dependency = dependency->next_dependency;
    }
    switch (type->kind) {
    case CHECKED_TYPE_KIND__RESULT:
        Generator__generate_result_type(self, (Checked_Result_Type *)type);
        break;
    case CHECKED_TYPE_KIND__STRUCT:
        Generator__generate_struct(self, (Checked_Struct_Type *)type);
        break;
    case CHECKED_TYPE_KIND__TRAIT:
        Generator__generate_trait(self, (Checked_Trait_Type *)type);
        break;
    case CHECKED_TYPE_KIND__VARIANT:
        Generator__generate_variant(self, (Checked_Variant_Type *)type);
        break;
    case CHECKED_TYPE_KIND__EXTERNAL:
    case CHECKED_TYPE_KIND__GENERIC:
        break;
    default:
        panic();
    }
    type->has_generated_definition = true;
}

void generate_builtin_types_header(Checked_Symbols *builtin_symbols, String *output_dir) {
    String *output_file_path = String__create_copy(output_dir);
    if (!String__ends_with_cstring(output_file_path, "/")) {
        String__append_char(output_file_path, '/');
    }
    String__append_cstring(output_file_path, "builtin_types.h");

    Generator generator = Generator__make(File__create_writer(output_file_path));

    /* Header guard */
    pWriter__write__cstring(generator.writer, "#ifndef __BUILTIN_TYPES_H__\n");
    pWriter__write__cstring(generator.writer, "#define __BUILTIN_TYPES_H__\n\n");

    /* Standard includes */
    pWriter__write__cstring(generator.writer, "#include <inttypes.h>\n");
    pWriter__write__cstring(generator.writer, "#include <stdbool.h>\n");
    pWriter__write__cstring(generator.writer, "#include <stddef.h>\n\n");

    /* Generate all builtin types */
    Checked_Symbol *checked_symbol = builtin_symbols->first_symbol;
    while (checked_symbol != NULL) {
        if (checked_symbol->kind == CHECKED_SYMBOL_KIND__TYPE) {
            Checked_Named_Type *checked_named_type = ((Checked_Type_Symbol *)checked_symbol)->named_type;
            if (checked_named_type->super.kind == CHECKED_TYPE_KIND__STRUCT) {
                Generator__define_type(&generator, (Checked_Type *)checked_named_type);
            }
        }
        checked_symbol = checked_symbol->next_symbol;
    }

    /* Close header guard */
    pWriter__write__cstring(generator.writer, "#endif // __BUILTIN_TYPES_H__\n");
}

void generate_module_header(Checked_Source *checked_source, Checked_Module *checked_module, String *output_dir) {
    String *output_file_path = String__create_copy(output_dir);
    if (!String__ends_with_cstring(output_file_path, "/")) {
        String__append_char(output_file_path, '/');
    }
    String__append_string(output_file_path, checked_module->name);
    String__append_cstring(output_file_path, ".h");

    Generator generator = Generator__make(File__create_writer(output_file_path));

    /* Header guard */
    pWriter__write__cstring(generator.writer, "#ifndef __");
    pWriter__write__string(generator.writer, checked_module->name);
    pWriter__write__cstring(generator.writer, "_H__\n");
    pWriter__write__cstring(generator.writer, "#define __");
    pWriter__write__string(generator.writer, checked_module->name);
    pWriter__write__cstring(generator.writer, "_H__\n\n");

    /* Include builtin types header */
    pWriter__write__cstring(generator.writer, "#include \"builtin_types.h\"\n\n");

    Checked_Symbol *checked_symbol;
    Checked_Procedure_Symbol *malloc_procedure = NULL;

    /* Import all modules */
    checked_symbol = checked_source->symbols->first_symbol;
    while (checked_symbol != NULL) {
        if (checked_symbol->kind == CHECKED_SYMBOL_KIND__IMPORT && checked_symbol->module == checked_module) {
            Checked_Module *other_module = ((Checked_Import_Symbol *)checked_symbol)->other_module;
            pWriter__write__cstring(generator.writer, "#include \"");
            pWriter__write__string(generator.writer, other_module->name);
            pWriter__write__cstring(generator.writer, ".h\"\n");
        }
        checked_symbol = checked_symbol->next_symbol;
    }
    pWriter__end_line(generator.writer);

    /* Generate all defined types */
    checked_symbol = checked_source->symbols->first_symbol;
    while (checked_symbol != NULL) {
        if (checked_symbol->kind == CHECKED_SYMBOL_KIND__TYPE && checked_symbol->module == checked_module) {
            Checked_Type *type = (Checked_Type *)((Checked_Type_Symbol *)checked_symbol)->named_type;
            if (!type->has_generated_definition) {
                Generator__define_type(&generator, type);
            }
        } else if (checked_symbol->kind == CHECKED_SYMBOL_KIND__PROCEDURE && String__equals_cstring(checked_symbol->name, "malloc")) {
            malloc_procedure = (Checked_Procedure_Symbol *)checked_symbol;
        }
        checked_symbol = checked_symbol->next_symbol;
    }

    /* Declare all global variables */
    checked_symbol = checked_source->symbols->first_symbol;
    while (checked_symbol != NULL) {
        if (checked_symbol->kind == CHECKED_SYMBOL_KIND__VARIABLE && checked_symbol->module == checked_module) {
            Checked_Variable_Symbol *variable_symbol = (Checked_Variable_Symbol *)checked_symbol;
            Generator__declare_variable(&generator, variable_symbol->statement);
            pWriter__end_line(generator.writer);
            pWriter__end_line(generator.writer);
        }
        checked_symbol = checked_symbol->next_symbol;
    }

    /* Declare all defined procedures */
    checked_symbol = checked_source->symbols->first_symbol;
    while (checked_symbol != NULL) {
        if (checked_symbol->module == checked_module) {
            if (checked_symbol->kind == CHECKED_SYMBOL_KIND__PROCEDURE) {
                Generator__declare_procedure(&generator, (Checked_Procedure_Symbol *)checked_symbol);
                pWriter__end_line(generator.writer);
            } else if (checked_symbol->kind == CHECKED_SYMBOL_KIND__TYPE && malloc_procedure != NULL) {
                Checked_Named_Type *named_type = ((Checked_Type_Symbol *)checked_symbol)->named_type;
            }
        }
        checked_symbol = checked_symbol->next_symbol;
    }

    /* Close header guard */
    pWriter__write__cstring(generator.writer, "#endif // __");
    pWriter__write__string(generator.writer, checked_module->name);
    pWriter__write__cstring(generator.writer, "_H__\n");
}

void generate_module(Checked_Source *checked_source, Checked_Module *checked_module, String *output_dir, bool generate_main, Checked_Module *first_module) {
    String *output_file_path = String__create_copy(output_dir);
    if (!String__ends_with_cstring(output_file_path, "/")) {
        String__append_char(output_file_path, '/');
    }
    String__append_string(output_file_path, checked_module->name);
    String__append_cstring(output_file_path, ".c");

    Generator generator = Generator__make(File__create_writer(output_file_path));

    Checked_Symbol *checked_symbol;
    Checked_Procedure_Symbol *main_procedure = NULL;

    /* Include all headers to have all methods available */
    Checked_Module *module = first_module;
    while (module != NULL) {
        pWriter__write__cstring(generator.writer, "#include \"");
        pWriter__write__string(generator.writer, module->name);
        pWriter__write__cstring(generator.writer, ".h\"\n");
        module = module->next_module;
    }
    pWriter__end_line(generator.writer);

    /* Define all global variables */
    checked_symbol = checked_source->symbols->first_symbol;
    while (checked_symbol != NULL) {
        if (checked_symbol->kind == CHECKED_SYMBOL_KIND__VARIABLE && checked_symbol->module == checked_module) {
            Checked_Variable_Symbol *variable_symbol = (Checked_Variable_Symbol *)checked_symbol;
            if (!variable_symbol->statement->is_external) {
                Generator__generate_variable_statement(&generator, variable_symbol->statement);
                pWriter__end_line(generator.writer);
            }
        }
        checked_symbol = checked_symbol->next_symbol;
    }

    /* Declare malloc procedure */
    pWriter__write__cstring(generator.writer, "void *malloc(uintmax_t size);\n\n");

    /* Generate all defined procedures */
    checked_symbol = checked_source->symbols->first_symbol;
    while (checked_symbol != NULL) {
        if (checked_symbol->module == checked_module) {
            if (checked_symbol->kind == CHECKED_SYMBOL_KIND__PROCEDURE) {
                Checked_Procedure_Symbol *checked_procedure = (Checked_Procedure_Symbol *)checked_symbol;
                if (generate_main && String__equals_cstring(checked_procedure->procedure_name, "main")) {
                    main_procedure = checked_procedure;
                }
                Generator__generate_procedure(&generator, checked_procedure);
            }
        }
        checked_symbol = checked_symbol->next_symbol;
    }

    /* Generate main procedure */
    if (generate_main && main_procedure != NULL) {
        pWriter__write__cstring(generator.writer, "int32_t main(int argc, const char **argv) {\n");
        pWriter__write__cstring(generator.writer, "    return ");
        CDECL_Procedure_Name main_procedure_name = CDECL_Procedure_Name__create(main_procedure);
        main_procedure_name.super.write((CDECL_Name *)&main_procedure_name, generator.writer);
        if (main_procedure->procedure_type->first_parameter != NULL) {
            pWriter__write__cstring(generator.writer, "(argc, (uint8_t **)argv);\n");
        } else {
            pWriter__write__cstring(generator.writer, "();\n");
        }
        pWriter__write__cstring(generator.writer, "}\n\n");
    }
}

void generate(Checked_Source *checked_source, String *output_dir, bool generate_main) {
    generate_builtin_types_header(checked_source->symbols->parent, output_dir);

    Checked_Module *checked_module = checked_source->first_module;
    while (checked_module != NULL) {
        generate_module_header(checked_source, checked_module, output_dir);
        generate_module(checked_source, checked_module, output_dir, generate_main, checked_source->first_module);
        checked_module = checked_module->next_module;
    }
}