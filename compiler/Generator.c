/* Copyright (C) 2023-2024 Stefan Selariu */

#include "Generator.h"

typedef struct Generator {
    Writer *writer;
    uint16_t identation;
} Generator;

void Generator__write_source_location(Generator *self, Source_Location *location) {
    pWriter__write__cstring(self->writer, "#line ");
    pWriter__write__int64(self->writer, (int64_t)location->line);
    pWriter__write__cstring(self->writer, " \"");
    pWriter__write__string(self->writer, location->source->file_path);
    pWriter__write__cstring(self->writer, "\"\n");
}

void Generator__generate_expression(Generator *self, Checked_Expression *expression);

void Generator__generate_add_expression(Generator *self, Checked_Add_Expression *expression) {
    Generator__generate_expression(self, expression->super.left_expression);
    pWriter__write__cstring(self->writer, " + ");
    Generator__generate_expression(self, expression->super.right_expression);
}

void Generator__generate_address_of_expression(Generator *self, Checked_Address_Of_Expression *expression) {
    pWriter__write__cstring(self->writer, "&");
    Generator__generate_expression(self, expression->super.other_expression);
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
    pWriter__write__cstring(self->writer, "(");
    pWriter__write__checked_type(self->writer, expression->super.type);
    pWriter__write__cstring(self->writer, ") ");
    Generator__generate_expression(self, expression->other_expression);
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
    pWriter__write__uint64(self->writer, expression->value);
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
    pWriter__write__cstring(self->writer, "!");
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

void Generator__generate_sizeof_expression(Generator *self, Checked_Sizeof_Expression *expression) {
    pWriter__write__cstring(self->writer, "sizeof(");
    pWriter__write__checked_type(self->writer, expression->sized_type);
    pWriter__write__cstring(self->writer, ")");
}

void Generator__generate_string_expression(Generator *self, Checked_String_Expression *expression) {
    pWriter__write__char(self->writer, '"');
    size_t index = 0;
    while (index < expression->value->length) {
        pWriter__write__escaped_char(self->writer, expression->value->data[index]);
        index = index + 1;
    }
    pWriter__write__char(self->writer, '"');
}

void Generator__generate_substract_expression(Generator *self, Checked_Substract_Expression *expression) {
    Generator__generate_expression(self, expression->super.left_expression);
    pWriter__write__cstring(self->writer, " - ");
    Generator__generate_expression(self, expression->super.right_expression);
}

void Generator__generate_symbol_expression(Generator *self, Checked_Symbol_Expression *expression) {
    pWriter__write__string(self->writer, expression->symbol->name);
}

void Generator__generate_expression(Generator *self, Checked_Expression *expression) {
    if (expression->kind == CHECKED_EXPRESSION_KIND__ADD) {
        Generator__generate_add_expression(self, (Checked_Add_Expression *)expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__ADDRESS_OF) {
        Generator__generate_address_of_expression(self, (Checked_Address_Of_Expression *)expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__ARRAY_ACCESS) {
        Generator__generate_array_access_expression(self, (Checked_Array_Access_Expression *)expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__BOOL) {
        Generator__generate_bool_expression(self, (Checked_Bool_Expression *)expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__CALL) {
        Generator__generate_call_expression(self, (Checked_Call_Expression *)expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__CAST) {
        Generator__generate_cast_expression(self, (Checked_Cast_Expression *)expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__CHARACTER) {
        Generator__generate_character_expression(self, (Checked_Character_Expression *)expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__DIVIDE) {
        Generator__generate_divide_expression(self, (Checked_Divide_Expression *)expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__EQUALS) {
        Generator__generate_equals_expression(self, (Checked_Equals_Expression *)expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__GREATER) {
        Generator__generate_greater_expression(self, (Checked_Greater_Expression *)expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__GREATER_OR_EQUALS) {
        Generator__generate_greater_or_equals_expression(self, (Checked_Greater_Or_Equals_Expression *)expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__GROUP) {
        Generator__generate_group_expression(self, (Checked_Group_Expression *)expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__INTEGER) {
        Generator__generate_integer_expression(self, (Checked_Integer_Expression *)expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__LESS) {
        Generator__generate_less_expression(self, (Checked_Less_Expression *)expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__LESS_OR_EQUALS) {
        Generator__generate_less_or_equals_expression(self, (Checked_Less_Or_Equals_Expression *)expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__LOGIC_AND) {
        Generator__generate_logic_and_expression(self, (Checked_Logic_And_Expression *)expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__LOGIC_OR) {
        Generator__generate_logic_or_expression(self, (Checked_Logic_Or_Expression *)expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__MEMBER_ACCESS) {
        Generator__generate_member_access_expression(self, (Checked_Member_Access_Expression *)expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__MINUS) {
        Generator__generate_minus_expression(self, (Checked_Minus_Expression *)expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__MODULO) {
        Generator__generate_modulo_expression(self, (Checked_Modulo_Expression *)expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__MULTIPLY) {
        Generator__generate_multiply_expression(self, (Checked_Multiply_Expression *)expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__NOT) {
        Generator__generate_not_expression(self, (Checked_Not_Expression *)expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__NOT_EQUALS) {
        Generator__generate_not_equals_expression(self, (Checked_Not_Equals_Expression *)expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__NULL) {
        Generator__generate_null_expression(self, (Checked_Null_Expression *)expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__SIZEOF) {
        Generator__generate_sizeof_expression(self, (Checked_Sizeof_Expression *)expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__STRING) {
        Generator__generate_string_expression(self, (Checked_String_Expression *)expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__SUBSTRACT) {
        Generator__generate_substract_expression(self, (Checked_Substract_Expression *)expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__SYMBOL) {
        Generator__generate_symbol_expression(self, (Checked_Symbol_Expression *)expression);
    } else {
        Source_Location__error(expression->location, String__create_from("Unsupported expression"));
        abort();
    }
}

void Generator__write_identation(Generator *self) {
    uint16_t identation = self->identation;
    while (identation > 0) {
        pWriter__write__cstring(self->writer, "    ");
        identation = identation - 1;
    }
}

void Generator__generate_statement(Generator *self, Checked_Statement *statement);
void Generator__generate_statements(Generator *self, Checked_Statements *statements);

void Generator__generate_assignment_statement(Generator *self, Checked_Assignment_Statement *statement) {
    Generator__generate_expression(self, statement->object_expression);
    pWriter__write__cstring(self->writer, " = ");
    Generator__generate_expression(self, statement->value_expression);
    pWriter__write__cstring(self->writer, ";");
}

void Generator__generate_block_statement(Generator *self, Checked_Block_Statement *statement) {
    pWriter__write__cstring(self->writer, "{\n");
    Generator__generate_statements(self, statement->statements);
    Generator__write_identation(self);
    pWriter__write__cstring(self->writer, "}");
}

void Generator__generate_break_statement(Generator *self, Checked_Break_Statement *statement) {
    pWriter__write__cstring(self->writer, "break;");
}

void Generator__generate_expression_statement(Generator *self, Checked_Expression_Statement *statement) {
    Generator__generate_expression(self, statement->expression);
    pWriter__write__cstring(self->writer, ";");
}

void Generator__generate_if_statement(Generator *self, Checked_If_Statement *statement) {
    pWriter__write__cstring(self->writer, "if (");
    Generator__generate_expression(self, statement->condition_expression);
    pWriter__write__cstring(self->writer, ") ");
    Generator__generate_statement(self, statement->true_statement);
    if (statement->false_statement != NULL) {
        pWriter__write__cstring(self->writer, " else ");
        Generator__generate_statement(self, statement->false_statement);
    }
}

void Generator__generate_return_statement(Generator *self, Checked_Return_Statement *statement) {
    pWriter__write__cstring(self->writer, "return");
    if (statement->expression != NULL) {
        pWriter__write__cstring(self->writer, " ");
        Generator__generate_expression(self, statement->expression);
    }
    pWriter__write__cstring(self->writer, ";");
}

void Generator__generate_variable_statement(Generator *self, Checked_Variable_Statement *statement) {
    if (statement->is_external) {
        pWriter__write__cstring(self->writer, "extern ");
    }
    pWriter__write__checked_type(self->writer, statement->variable->super.type);
    pWriter__write__char(self->writer, ' ');
    pWriter__write__string(self->writer, statement->variable->super.name);
    if (statement->expression != NULL) {
        pWriter__write__cstring(self->writer, " = ");
        Generator__generate_expression(self, statement->expression);
    }
    pWriter__write__cstring(self->writer, ";");
}

void Generator__generate_while_statement(Generator *self, Checked_While_Statement *statement) {
    pWriter__write__cstring(self->writer, "while (");
    Generator__generate_expression(self, statement->condition_expression);
    pWriter__write__cstring(self->writer, ") ");
    Generator__generate_statement(self, statement->body_statement);
}

void Generator__generate_statement(Generator *self, Checked_Statement *statement) {
    if (statement->kind == CHECKED_STATEMENT_KIND__ASSIGNMENT) {
        Generator__generate_assignment_statement(self, (Checked_Assignment_Statement *)statement);
    } else if (statement->kind == CHECKED_STATEMENT_KIND__BLOCK) {
        Generator__generate_block_statement(self, (Checked_Block_Statement *)statement);
    } else if (statement->kind == CHECKED_STATEMENT_KIND__BREAK) {
        Generator__generate_break_statement(self, (Checked_Break_Statement *)statement);
    } else if (statement->kind == CHECKED_STATEMENT_KIND__EXPRESSION) {
        Generator__generate_expression_statement(self, (Checked_Expression_Statement *)statement);
    } else if (statement->kind == CHECKED_STATEMENT_KIND__IF) {
        Generator__generate_if_statement(self, (Checked_If_Statement *)statement);
    } else if (statement->kind == CHECKED_STATEMENT_KIND__RETURN) {
        Generator__generate_return_statement(self, (Checked_Return_Statement *)statement);
    } else if (statement->kind == CHECKED_STATEMENT_KIND__VARIABLE) {
        Generator__generate_variable_statement(self, (Checked_Variable_Statement *)statement);
    } else if (statement->kind == CHECKED_STATEMENT_KIND__WHILE) {
        Generator__generate_while_statement(self, (Checked_While_Statement *)statement);
    } else {
        Source_Location__error(statement->location, String__create_from("Unsupported statement"));
        abort();
    }
}

void Generator__generate_statements(Generator *self, Checked_Statements *statements) {
    self->identation = self->identation + 1;

    Checked_Statement *statement = statements->first_statement;
    while (statement != NULL) {
        Generator__write_source_location(self, statement->location);

        Generator__write_identation(self);

        Generator__generate_statement(self, statement);

        pWriter__write__cstring(self->writer, "\n");

        statement = statement->next_statement;
    }

    self->identation = self->identation - 1;
}

void Generator__generate_enum(Generator *self, Checked_Enum_Type *enum_type) {
    pWriter__write__checked_type(self->writer, (Checked_Type *)enum_type);
    pWriter__write__cstring(self->writer, " {\n");
    Checked_Enum_Member *enum_member = enum_type->first_member;
    while (enum_member != NULL) {
        pWriter__write__char(self->writer, '\t');
        pWriter__write__string(self->writer, enum_member->name);
        enum_member = enum_member->next_member;
        if (enum_member != NULL) {
            pWriter__write__cstring(self->writer, ",\n");
        } else {
            pWriter__write__char(self->writer, '\n');
        }
    }
    pWriter__write__cstring(self->writer, "};\n");
}

void Generator__declare_function(Generator *self, Checked_Function_Symbol *function_symbol) {
    pWriter__write__checked_type(self->writer, function_symbol->function_type->return_type);
    if (function_symbol->function_type->return_type->kind != CHECKED_TYPE_KIND__POINTER) {
        pWriter__write__char(self->writer, ' ');
    }
    pWriter__write__string(self->writer, function_symbol->super.name);
    pWriter__write__char(self->writer, '(');
    Checked_Function_Parameter *parameter = function_symbol->function_type->first_parameter;
    while (parameter != NULL) {
        pWriter__write__checked_type(self->writer, parameter->type);
        if (parameter->type->kind != CHECKED_TYPE_KIND__POINTER) {
            pWriter__write__char(self->writer, ' ');
        }
        pWriter__write__string(self->writer, parameter->name);
        parameter = parameter->next_parameter;
        if (parameter != NULL) {
            pWriter__write__cstring(self->writer, ", ");
        }
    }
    pWriter__write__cstring(self->writer, ");\n");
}

void Generator__generate_function(Generator *self, Checked_Function_Symbol *function_symbol) {
    if (function_symbol->checked_statements == NULL) {
        return;
    }
    Generator__write_source_location(self, function_symbol->super.location);
    pWriter__write__checked_type(self->writer, (Checked_Type *)function_symbol->function_type);
    pWriter__write__cstring(self->writer, " {\n");
    Generator__generate_statements(self, function_symbol->checked_statements);
    pWriter__write__cstring(self->writer, "}\n\n");
}

void Generator__declare_struct(Generator *self, Checked_Struct_Type *struct_type) {
    pWriter__write__checked_type(self->writer, (Checked_Type *)struct_type);
    pWriter__write__cstring(self->writer, ";\n");
}

void Generator__generate_struct(Generator *self, Checked_Struct_Type *struct_type) {
    Checked_Struct_Member *struct_member = struct_type->first_member;
    if (struct_member == NULL) {
        return;
    }
    pWriter__write__checked_type(self->writer, (Checked_Type *)struct_type);
    pWriter__write__cstring(self->writer, " {\n");
    while (struct_member != NULL) {
        pWriter__write__char(self->writer, '\t');
        pWriter__write__checked_type(self->writer, struct_member->type);
        pWriter__write__char(self->writer, ' ');
        pWriter__write__string(self->writer, struct_member->name);
        pWriter__write__cstring(self->writer, ";\n");
        struct_member = struct_member->next_member;
    }
    pWriter__write__cstring(self->writer, "};\n\n");
}

void generate(Writer *writer, Checked_Source *checked_source) {
    Generator generator;
    generator.writer = writer;
    generator.identation = 0;

    Checked_Symbol *checked_symbol;

    pWriter__write__cstring(generator.writer, "#include <inttypes.h>");
    pWriter__end_line(generator.writer);
    pWriter__write__cstring(generator.writer, "#include <stdbool.h>");
    pWriter__end_line(generator.writer);
    pWriter__write__cstring(generator.writer, "#include <stddef.h>");
    pWriter__end_line(generator.writer);
    pWriter__end_line(generator.writer);

    Source *source = checked_source->first_source->next;
    while (source != NULL) {
        if (source->file_path->data[source->file_path->length - 1] == 'h') {
            pWriter__write__cstring(generator.writer, "#include \"");
            pWriter__write__string(generator.writer, source->file_path);
            pWriter__write__char(generator.writer, '"');
            pWriter__end_line(generator.writer);
            pWriter__end_line(generator.writer);
        }
        source = source->next;
    }

    /* Declare all defined types */
    checked_symbol = checked_source->first_symbol;
    while (checked_symbol != NULL) {
        if (checked_symbol->kind == CHECKED_SYMBOL_KIND__TYPE && checked_symbol->location->source == checked_source->first_source) {
            Checked_Named_Type *named_type = ((Checked_Type_Symbol *)checked_symbol)->named_type;
            if (named_type->super.kind == CHECKED_TYPE_KIND__STRUCT) {
                Generator__declare_struct(&generator, (Checked_Struct_Type *)named_type);
            } else if (named_type->super.kind == CHECKED_TYPE_KIND__ENUM) {
                Generator__generate_enum(&generator, (Checked_Enum_Type *)named_type);
            }
            pWriter__end_line(generator.writer);
        }
        checked_symbol = checked_symbol->next_symbol;
    }

    /* Generate all defined types */
    checked_symbol = checked_source->first_symbol;
    while (checked_symbol != NULL) {
        if (checked_symbol->kind == CHECKED_SYMBOL_KIND__TYPE && checked_symbol->location->source == checked_source->first_source) {
            Checked_Named_Type *named_type = ((Checked_Type_Symbol *)checked_symbol)->named_type;
            if (named_type->super.kind == CHECKED_TYPE_KIND__STRUCT) {
                Generator__generate_struct(&generator, (Checked_Struct_Type *)named_type);
            }
        }
        checked_symbol = checked_symbol->next_symbol;
    }

    /* Declare all global variables */
    Checked_Statement *checked_statement = checked_source->statements->first_statement;
    while (checked_statement != NULL) {
        if (checked_statement->kind == CHECKED_STATEMENT_KIND__VARIABLE && checked_statement->location->source == checked_source->first_source) {
            Generator__generate_variable_statement(&generator, (Checked_Variable_Statement *)checked_statement);
            pWriter__end_line(generator.writer);
        } else {
            Source_Location__error(checked_statement->location, String__create_from("Unsupported statement"));
            abort();
        }
        checked_statement = checked_statement->next_statement;
    }

    /* Declare all defined functions */
    checked_symbol = checked_source->first_symbol;
    while (checked_symbol != NULL) {
        if (checked_symbol->kind == CHECKED_SYMBOL_KIND__FUNCTION && checked_symbol->location->source == checked_source->first_source) {
            Generator__declare_function(&generator, (Checked_Function_Symbol *)checked_symbol);
            pWriter__end_line(generator.writer);
        }
        checked_symbol = checked_symbol->next_symbol;
    }

    /* Generate all defined functions */
    checked_symbol = checked_source->first_symbol;
    while (checked_symbol != NULL) {
        if (checked_symbol->kind == CHECKED_SYMBOL_KIND__FUNCTION && checked_symbol->location->source == checked_source->first_source) {
            Generator__generate_function(&generator, (Checked_Function_Symbol *)checked_symbol);
        }
        checked_symbol = checked_symbol->next_symbol;
    }
}
