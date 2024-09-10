/* Copyright (C) 2023-2024 Stefan Selariu */

#include "Checker.h"
#include "File.h"

typedef struct Checker {
    Checked_Named_Type *first_type;
    Checked_Named_Type *last_type;
    Checked_Named_Type *last_builting_type;
    Checked_Symbols *symbols;
    Checked_Type *return_type;
} Checker;

void Checker__append_type(Checker *self, Checked_Named_Type *type);

Checker *Checker__create() {
    Checker *checker = (Checker *)malloc(sizeof(Checker));
    checker->first_type = NULL;
    checker->last_type = NULL;
    checker->symbols = Checked_Symbols__create(NULL);

    Source_Location *location = Source_Location__create(NULL, 0, 1);
    Checker__append_type(checker, Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__BOOL, sizeof(Checked_Named_Type), location, String__create_from("bool")));
    Checker__append_type(checker, Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__CHAR, sizeof(Checked_Named_Type), location, String__create_from("char")));
    Checker__append_type(checker, Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__INT16_T, sizeof(Checked_Named_Type), location, String__create_from("int16_t")));
    Checker__append_type(checker, Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__INT32_T, sizeof(Checked_Named_Type), location, String__create_from("int32_t")));
    Checker__append_type(checker, Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__INT64_T, sizeof(Checked_Named_Type), location, String__create_from("int64_t")));
    Checker__append_type(checker, Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__INT8_T, sizeof(Checked_Named_Type), location, String__create_from("int8_t")));
    Checker__append_type(checker, Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__SIZE_T, sizeof(Checked_Named_Type), location, String__create_from("size_t")));
    Checker__append_type(checker, Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__UINT16_T, sizeof(Checked_Named_Type), location, String__create_from("uint16_t")));
    Checker__append_type(checker, Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__UINT32_T, sizeof(Checked_Named_Type), location, String__create_from("uint32_t")));
    Checker__append_type(checker, Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__UINT64_T, sizeof(Checked_Named_Type), location, String__create_from("uint64_t")));
    Checker__append_type(checker, Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__UINT8_T, sizeof(Checked_Named_Type), location, String__create_from("uint8_t")));
    Checker__append_type(checker, Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__VOID, sizeof(Checked_Named_Type), location, String__create_from("void")));
    Checker__append_type(checker, Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__NULL, sizeof(Checked_Named_Type), location, String__create_from("null")));
    checker->last_builting_type = checker->last_type;

    return checker;
}

void Checker__append_type(Checker *self, Checked_Named_Type *type) {
    if (self->first_type == NULL) {
        self->first_type = type;
    } else {
        self->last_type->super.next_type = (Checked_Type *)type;
    }
    self->last_type = type;

    Checked_Symbols__append_symbol(self->symbols, (Checked_Symbol *)Checked_Type_Symbol__create(type->super.location, type->name, type));
}

Checked_Named_Type *Checker__find_type(Checker *self, String *name) {
    Checked_Named_Type *type = self->first_type;
    while (type != NULL) {
        if (String__equals_string(name, type->name)) {
            break;
        }
        type = (Checked_Named_Type *)type->super.next_type;
    }
    return type;
}

Checked_Named_Type *Checker__get_builtin_type(Checker *self, Checked_Type_Kind kind) {
    Checked_Named_Type *type = self->first_type;
    Checked_Named_Type *custom_type = (Checked_Named_Type *)self->last_builting_type->super.next_type;
    while (type != custom_type) {
        if (type->super.kind == kind) {
            return type;
        }
        type = (Checked_Named_Type *)type->super.next_type;
    }
    error(String__create_from("No such builtin type"));
    abort();
}

Checked_Type *Checker__resolve_type(Checker *self, Parsed_Type *parsed_type) {
    if (parsed_type->kind == PARSED_TYPE_KIND__NAMED) {
        Checked_Named_Type *type = Checker__find_type(self, ((Parsed_Named_Type *)parsed_type)->name);
        if (type != NULL) {
            return (Checked_Type *)type;
        }

        pWriter__write__location(stderr_writer, parsed_type->location);
        pWriter__write__cstring(stderr_writer, ": ");
        pWriter__style(stderr_writer, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Undefined type: ");
        pWriter__write__string(stderr_writer, ((Parsed_Named_Type *)parsed_type)->name);
        pWriter__style(stderr_writer, WRITER_STYLE__DEFAULT);
        pWriter__end_line(stderr_writer);
        abort();
    }
    if (parsed_type->kind == PARSED_TYPE_KIND__POINTER) {
        return (Checked_Type *)Checked_Pointer_Type__create(parsed_type->location, Checker__resolve_type(self, ((Parsed_Pointer_Type *)parsed_type)->other_type));
    }
    if (parsed_type->kind == PARSED_TYPE_KIND__STRUCT) {
        Checked_Type *type = Checker__resolve_type(self, ((Parsed_Struct_Type *)parsed_type)->other_type);
        if (type->kind != CHECKED_TYPE_KIND__STRUCT) {
            pWriter__write__todo(stderr_writer, __FILE__, __LINE__, "Report unexpected type");
            abort();
        }
        return type;
    }
    if (parsed_type->kind == PARSED_TYPE_KIND__FUNCTION) {
        Parsed_Function_Type *parsed_function_type = (Parsed_Function_Type *)parsed_type;
        Checked_Function_Parameter *function_first_parameter = NULL;
        Parsed_Function_Parameter *parsed_parameter = parsed_function_type->first_parameter;
        if (parsed_parameter != NULL) {
            function_first_parameter = Checked_Function_Parameter__create(parsed_parameter->name->location, parsed_parameter->name->lexeme, Checker__resolve_type(self, parsed_parameter->type));
            Checked_Function_Parameter *function_last_parameter = function_first_parameter;
            parsed_parameter = parsed_parameter->next_parameter;
            while (parsed_parameter != NULL) {
                Checked_Function_Parameter *function_parameter = Checked_Function_Parameter__create(parsed_parameter->name->location, parsed_parameter->name->lexeme, Checker__resolve_type(self, parsed_parameter->type));
                function_last_parameter->next_parameter = function_parameter;
                function_last_parameter = function_parameter;
                parsed_parameter = parsed_parameter->next_parameter;
            }
        }
        Checked_Type *function_return_type = Checker__resolve_type(self, parsed_function_type->return_type);
        Checked_Function_Type *function_type = Checked_Function_Type__create(parsed_function_type->super.location, function_first_parameter, function_return_type);
        return (Checked_Type *)Checked_Pointer_Type__create(parsed_type->location, (Checked_Type *)function_type);
    }
    pWriter__write__todo(stderr_writer, __FILE__, __LINE__, "Report undefined type");
    abort();
}

Checked_Expression *Checker__check_expression(Checker *self, Parsed_Expression *parsed_expression);

Checked_Expression *Checker__check_add_expression(Checker *self, Parsed_Add_Expression *parsed_expression) {
    Checked_Expression *left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
    Checked_Expression *right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
    return (Checked_Expression *)Checked_Add_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

Checked_Expression *Checker__check_address_of_expression(Checker *self, Parsed_Address_Of_Expression *parsed_expression) {
    Checked_Expression *other_expression = Checker__check_expression(self, parsed_expression->super.other_expression);
    if (other_expression->kind != CHECKED_EXPRESSION_KIND__SYMBOL) {
        Source_Location__error(parsed_expression->super.super.location, String__create_from("Not a symbol"));
        abort();
    }
    return (Checked_Expression *)Checked_Address_Of_Expression__create(parsed_expression->super.super.location, (Checked_Type *)Checked_Pointer_Type__create(other_expression->location, other_expression->type), other_expression);
}

Checked_Expression *Checker__check_array_access_expression(Checker *self, Parsed_Array_Access_Expression *parsed_expression) {
    Checked_Expression *array_expression = Checker__check_expression(self, parsed_expression->array_expression);
    Checked_Type *array_type = array_expression->type;
    if (array_type->kind != CHECKED_TYPE_KIND__POINTER) {
        String *message = String__create();
        String__append_char(message, '"');
        String__append_checked_type(message, array_type);
        String__append_cstring(message, "\" is not a pointer type.");
        Source_Location__error(parsed_expression->array_expression->location, message);
        abort();
    }
    Checked_Type *type = ((Checked_Pointer_Type *)array_type)->other_type;
    Checked_Expression *index_expression = Checker__check_expression(self, parsed_expression->index_expression);
    Checked_Type__expect_same_type((Checked_Type *)Checker__get_builtin_type(self, CHECKED_TYPE_KIND__SIZE_T), index_expression->type, index_expression->location);
    return (Checked_Expression *)Checked_Array_Access_Expression__create(parsed_expression->super.location, type, array_expression, index_expression);
}

Checked_Expression *Checker__check_bool_expression(Checker *self, Parsed_Bool_Expression *parsed_expression) {
    Checked_Type *expression_type = (Checked_Type *)Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL);
    bool value = parsed_expression->value;
    return (Checked_Expression *)Checked_Bool_Expression__create(parsed_expression->super.super.location, expression_type, value);
}

Checked_Expression *Checker__check_call_expression(Checker *self, Parsed_Call_Expression *parsed_expression) {
    Checked_Expression *callee_expression = Checker__check_expression(self, parsed_expression->callee_expression);
    Checked_Type *callee_type = callee_expression->type;
    if (callee_type->kind != CHECKED_TYPE_KIND__POINTER || ((Checked_Pointer_Type *)callee_type)->other_type->kind != CHECKED_TYPE_KIND__FUNCTION) {
        Source_Location__error(parsed_expression->super.location, String__create_from("Not a function"));
        abort();
    }
    Checked_Function_Type *function_type = (Checked_Function_Type *)((Checked_Pointer_Type *)callee_type)->other_type;
    Checked_Call_Argument *first_argument = NULL;
    if (parsed_expression->first_argument != NULL) {
        Checked_Call_Argument *last_argument = NULL;
        Checked_Function_Parameter *function_parameter = function_type->first_parameter;
        Parsed_Call_Argument *parsed_argument = parsed_expression->first_argument;
        while (function_parameter != NULL && parsed_argument != NULL) {
            Checked_Expression *argument_expression = Checker__check_expression(self, parsed_argument->expression);
            Checked_Type__expect_same_type(function_parameter->type, argument_expression->type, argument_expression->location);
            Checked_Call_Argument *argument = Checked_Call_Argument__create(argument_expression);
            if (last_argument == NULL) {
                first_argument = argument;
            } else {
                last_argument->next_argument = argument;
            }
            last_argument = argument;
            function_parameter = function_parameter->next_parameter;
            parsed_argument = parsed_argument->next_argument;
        }
        if (function_parameter != NULL) {
            Source_Location__error(parsed_expression->super.location, String__create_from("Report too few arguments"));
            abort();
        }
        if (parsed_argument != NULL) {
            Source_Location__error(parsed_expression->super.location, String__create_from("Report too many arguments"));
            abort();
        }
    }
    return (Checked_Expression *)Checked_Call_Expression__create(parsed_expression->super.location, function_type->return_type, callee_expression, first_argument);
}

Checked_Expression *Checker__check_cast_expression(Checker *self, Parsed_Cast_Expression *parsed_expression) {
    Checked_Type *type = Checker__resolve_type(self, parsed_expression->type);
    Checked_Expression *other_expression = Checker__check_expression(self, parsed_expression->super.other_expression);
    Checked_Type *other_type = other_expression->type;
    bool can_cast = false;
    if (type->kind == CHECKED_TYPE_KIND__POINTER) {
        if (other_type->kind == CHECKED_TYPE_KIND__POINTER) {
            can_cast = true;
        }
    } else if (Checked_Type__is_scalar_type(type)) {
        if (Checked_Type__is_scalar_type(type)) {
            can_cast = true;
        }
    }
    if (Checked_Type__equals(type, other_type)) {
        Source_Location__warning(parsed_expression->super.super.location, String__create_from("Redundant cast"));
    }
    if (!can_cast) {
        String *message = String__create_from("Cannot cast \"");
        String__append_checked_type(message, other_expression->type);
        String__append_cstring(message, "\" to \"");
        String__append_checked_type(message, type);
        String__append_cstring(message, "\".");
        Source_Location__error(parsed_expression->super.super.location, message);
        abort();
    }
    return (Checked_Expression *)Checked_Cast_Expression__create(parsed_expression->super.super.location, type, other_expression);
}

Checked_Expression *Checker__check_character_expression(Checker *self, Parsed_Character_Expression *parsed_expression) {
    Checked_Type *expression_type = (Checked_Type *)Checker__get_builtin_type(self, CHECKED_TYPE_KIND__CHAR);
    char value = parsed_expression->value;
    return (Checked_Expression *)Checked_Character_Expression__create(parsed_expression->super.super.location, expression_type, value);
}

Checked_Expression *Checker__check_divide_expression(Checker *self, Parsed_Divide_Expression *parsed_expression) {
    Checked_Expression *left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
    Checked_Expression *right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
    return (Checked_Expression *)Checked_Divide_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

Checked_Expression *Checker__check_equals_expression(Checker *self, Parsed_Equals_Expression *parsed_expression) {
    Checked_Expression *left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
    Checked_Expression *right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
    return (Checked_Expression *)Checked_Equals_Expression__create(parsed_expression->super.super.location, (Checked_Type *)Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL), left_expression, right_expression);
}

Checked_Expression *Checker__check_greater_expression(Checker *self, Parsed_Greater_Expression *parsed_expression) {
    Checked_Expression *left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
    Checked_Expression *right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
    return (Checked_Expression *)Checked_Greater_Expression__create(parsed_expression->super.super.location, (Checked_Type *)Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL), left_expression, right_expression);
}

Checked_Expression *Checker__check_greater_or_equals_expression(Checker *self, Parsed_Greater_Or_Equals_Expression *parsed_expression) {
    Checked_Expression *left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
    Checked_Expression *right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
    return (Checked_Expression *)Checked_Greater_Or_Equals_Expression__create(parsed_expression->super.super.location, (Checked_Type *)Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL), left_expression, right_expression);
}

Checked_Expression *Checker__check_group_expression(Checker *self, Parsed_Group_Expression *parsed_expression) {
    Checked_Expression *other_expression = Checker__check_expression(self, parsed_expression->other_expression);
    return (Checked_Expression *)Checked_Group_Expression__create(parsed_expression->super.location, other_expression->type, other_expression);
}

Checked_Expression *Checker__check_integer_expression(Checker *self, Parsed_Integer_Expression *parsed_expression) {
    Checked_Type *expression_type = (Checked_Type *)Checker__get_builtin_type(self, CHECKED_TYPE_KIND__INT32_T);
    uint64_t value = parsed_expression->value;
    return (Checked_Expression *)Checked_Integer_Expression__create(parsed_expression->super.super.location, expression_type, value);
}

Checked_Expression *Checker__check_less_expression(Checker *self, Parsed_Less_Expression *parsed_expression) {
    Checked_Expression *left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
    Checked_Expression *right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
    return (Checked_Expression *)Checked_Less_Expression__create(parsed_expression->super.super.location, (Checked_Type *)Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL), left_expression, right_expression);
}

Checked_Expression *Checker__check_less_or_equals_expression(Checker *self, Parsed_Less_Or_Equals_Expression *parsed_expression) {
    Checked_Expression *left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
    Checked_Expression *right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
    return (Checked_Expression *)Checked_Less_Or_Equals_Expression__create(parsed_expression->super.super.location, (Checked_Type *)Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL), left_expression, right_expression);
}

Checked_Expression *Checker__check_logic_and_expression(Checker *self, Parsed_Logic_And_Expression *parsed_expression) {
    Checked_Expression *left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
    Checked_Type__expect_same_type((Checked_Type *)Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL), left_expression->type, left_expression->location);
    Checked_Expression *right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
    return (Checked_Expression *)Checked_Logic_And_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

Checked_Expression *Checker__check_logic_or_expression(Checker *self, Parsed_Logic_Or_Expression *parsed_expression) {
    Checked_Expression *left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
    Checked_Type__expect_same_type((Checked_Type *)Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL), left_expression->type, left_expression->location);
    Checked_Expression *right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
    return (Checked_Expression *)Checked_Logic_Or_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

Checked_Expression *Checker__check_member_access_expression(Checker *self, Parsed_Member_Access_Expression *parsed_expression) {
    Checked_Expression *object_expression = Checker__check_expression(self, parsed_expression->object_expression);
    Checked_Type *object_type = object_expression->type;
    if (object_type->kind == CHECKED_TYPE_KIND__POINTER) {
        object_type = ((Checked_Pointer_Type *)object_type)->other_type;
    }
    if (object_type->kind != CHECKED_TYPE_KIND__STRUCT) {
        Source_Location__error(object_expression->location, String__create_from("Not a struct type"));
        abort();
    }
    Checked_Struct_Type *struct_type = (Checked_Struct_Type *)object_type;
    Checked_Struct_Member *member = Checked_Struct_Type__find_member(struct_type, parsed_expression->member_name->lexeme);
    if (member == NULL) {
        Source_Location__error(object_expression->location, String__create_from("No such struct member"));
        abort();
    }
    return (Checked_Expression *)Checked_Member_Access_Expression__create(parsed_expression->super.location, member->type, object_expression, member);
}

Checked_Expression *Checker__check_minus_expression(Checker *self, Parsed_Minus_Expression *parsed_expression) {
    Checked_Expression *other_expression = Checker__check_expression(self, parsed_expression->super.other_expression);
    Checked_Type *other_expression_type = other_expression->type;
    Checked_Type__expect_scalar_type(other_expression_type, other_expression->location);
    return (Checked_Expression *)Checked_Minus_Expression__create(parsed_expression->super.super.location, other_expression_type, other_expression);
}

Checked_Expression *Checker__check_modulo_expression(Checker *self, Parsed_Modulo_Expression *parsed_expression) {
    Checked_Expression *left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
    Checked_Expression *right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
    return (Checked_Expression *)Checked_Modulo_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

Checked_Expression *Checker__check_multiply_expression(Checker *self, Parsed_Multiply_Expression *parsed_expression) {
    Checked_Expression *left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
    Checked_Expression *right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
    return (Checked_Expression *)Checked_Multiply_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

Checked_Expression *Checker__check_not_expression(Checker *self, Parsed_Not_Expression *parsed_expression) {
    Checked_Expression *other_expression = Checker__check_expression(self, parsed_expression->super.other_expression);
    Checked_Type *other_expression_type = other_expression->type;
    Checked_Type__expect_same_type((Checked_Type *)Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL), other_expression_type, other_expression->location);
    return (Checked_Expression *)Checked_Not_Expression__create(parsed_expression->super.super.location, other_expression_type, other_expression);
}

Checked_Expression *Checker__check_not_equals_expression(Checker *self, Parsed_Not_Equals_Expression *parsed_expression) {
    Checked_Expression *left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
    Checked_Expression *right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
    return (Checked_Expression *)Checked_Not_Equals_Expression__create(parsed_expression->super.super.location, (Checked_Type *)Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL), left_expression, right_expression);
}

Checked_Expression *Checker__check_null_expression(Checker *self, Parsed_Null_Expression *parsed_expression) {
    Checked_Type *expression_type = (Checked_Type *)Checker__get_builtin_type(self, CHECKED_TYPE_KIND__NULL);
    return (Checked_Expression *)Checked_Null_Expression__create(parsed_expression->super.literal->location, expression_type);
}

Checked_Expression *Checker__check_sizeof_expression(Checker *self, Parsed_Sizeof_Expression *parsed_expression) {
    Checked_Type *expression_type = (Checked_Type *)Checker__get_builtin_type(self, CHECKED_TYPE_KIND__SIZE_T);
    Checked_Type *sized_type = Checker__resolve_type(self, parsed_expression->type);
    return (Checked_Expression *)Checked_Sizeof_Expression__create(parsed_expression->super.location, expression_type, sized_type);
}

Checked_Expression *Checker__check_string_expression(Checker *self, Parsed_String_Expression *parsed_expression) {
    Checked_Type *char_type = (Checked_Type *)Checker__get_builtin_type(self, CHECKED_TYPE_KIND__CHAR);
    Checked_Type *expression_type = (Checked_Type *)Checked_Pointer_Type__create(parsed_expression->super.literal->location, char_type);
    String *value = parsed_expression->value;
    return (Checked_Expression *)Checked_String_Expression__create(parsed_expression->super.super.location, expression_type, value);
}

Checked_Expression *Checker__check_substract_expression(Checker *self, Parsed_Substract_Expression *parsed_expression) {
    Checked_Expression *left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
    Checked_Expression *right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
    return (Checked_Expression *)Checked_Substract_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

Checked_Expression *Checker__check_symbol_expression(Checker *self, Parsed_Symbol_Expression *parsed_expression) {
    Checked_Symbol *symbol = Checked_Symbols__find_symbol(self->symbols, parsed_expression->name->lexeme);
    if (symbol == NULL) {
        Token__error(parsed_expression->name, String__create_from("Undefined symbol"));
        abort();
    }
    if (symbol->type == NULL) {
        Token__error(parsed_expression->name, String__create_from("Symbol without type"));
        abort();
    }
    return (Checked_Expression *)Checked_Symbol_Expression__create(parsed_expression->super.location, symbol->type, symbol);
}

Checked_Expression *Checker__check_expression(Checker *self, Parsed_Expression *parsed_expression) {
    if (parsed_expression->kind == PARSED_EXPRESSION_KIND__ADD) {
        return Checker__check_add_expression(self, (Parsed_Add_Expression *)parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__ADDRESS_OF) {
        return Checker__check_address_of_expression(self, (Parsed_Address_Of_Expression *)parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__ARRAY_ACCESS) {
        return Checker__check_array_access_expression(self, (Parsed_Array_Access_Expression *)parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__BOOL) {
        return Checker__check_bool_expression(self, (Parsed_Bool_Expression *)parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__CALL) {
        return Checker__check_call_expression(self, (Parsed_Call_Expression *)parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__CAST) {
        return Checker__check_cast_expression(self, (Parsed_Cast_Expression *)parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__CHARACTER) {
        return Checker__check_character_expression(self, (Parsed_Character_Expression *)parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__DIVIDE) {
        return Checker__check_divide_expression(self, (Parsed_Divide_Expression *)parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__EQUALS) {
        return Checker__check_equals_expression(self, (Parsed_Equals_Expression *)parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__GREATER) {
        return Checker__check_greater_expression(self, (Parsed_Greater_Expression *)parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__GREATER_OR_EQUALS) {
        return Checker__check_greater_or_equals_expression(self, (Parsed_Greater_Or_Equals_Expression *)parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__GROUP) {
        return Checker__check_group_expression(self, (Parsed_Group_Expression *)parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__INTEGER) {
        return Checker__check_integer_expression(self, (Parsed_Integer_Expression *)parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__LESS) {
        return Checker__check_less_expression(self, (Parsed_Less_Expression *)parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__LESS_OR_EQUALS) {
        return Checker__check_less_or_equals_expression(self, (Parsed_Less_Or_Equals_Expression *)parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__LOGIC_AND) {
        return Checker__check_logic_and_expression(self, (Parsed_Logic_And_Expression *)parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__LOGIC_OR) {
        return Checker__check_logic_or_expression(self, (Parsed_Logic_Or_Expression *)parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__MEMBER_ACCESS) {
        return Checker__check_member_access_expression(self, (Parsed_Member_Access_Expression *)parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__MINUS) {
        return Checker__check_minus_expression(self, (Parsed_Minus_Expression *)parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__MODULO) {
        return Checker__check_modulo_expression(self, (Parsed_Modulo_Expression *)parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__MULTIPLY) {
        return Checker__check_multiply_expression(self, (Parsed_Multiply_Expression *)parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__NOT) {
        return Checker__check_not_expression(self, (Parsed_Not_Expression *)parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__NOT_EQUALS) {
        return Checker__check_not_equals_expression(self, (Parsed_Not_Equals_Expression *)parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__NULL) {
        return Checker__check_null_expression(self, (Parsed_Null_Expression *)parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__SIZEOF) {
        return Checker__check_sizeof_expression(self, (Parsed_Sizeof_Expression *)parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__STRING) {
        return Checker__check_string_expression(self, (Parsed_String_Expression *)parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__SUBSTRACT) {
        return Checker__check_substract_expression(self, (Parsed_Substract_Expression *)parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__SYMBOL) {
        return Checker__check_symbol_expression(self, (Parsed_Symbol_Expression *)parsed_expression);
    }
    Source_Location__error(parsed_expression->location, String__create_from("Unsupported expression kind"));
    abort();
}

void Checker__check_enum_statement(Checker *self, Parsed_Enum_Statement *parsed_statement) {
    Checked_Enum_Type *enum_type = Checked_Enum_Type__create(parsed_statement->super.name->location, parsed_statement->super.name->lexeme);
    Checker__append_type(self, (Checked_Named_Type *)enum_type);

    Checked_Enum_Member *last_enum_member = NULL;
    Parsed_Enum_Member *parsed_enum_member = parsed_statement->first_member;
    while (parsed_enum_member != NULL) {
        Checked_Enum_Member *enum_member = Checked_Enum_Type__find_member(enum_type, parsed_enum_member->name->lexeme);
        if (enum_member != NULL) {
            pWriter__write__todo(stderr_writer, __FILE__, __LINE__, "Report enum member duplicate");
            abort();
        }
        enum_member = Checked_Enum_Member__create(parsed_enum_member->name->location, parsed_enum_member->name->lexeme);
        if (last_enum_member == NULL) {
            enum_type->first_member = enum_member;
        } else {
            last_enum_member->next_member = enum_member;
        }
        last_enum_member = enum_member;
        Checked_Symbols__append_symbol(self->symbols, (Checked_Symbol *)Checked_Enum_Member_Symbol__create(enum_member->location, enum_member->name, (Checked_Type *)enum_type));
        parsed_enum_member = parsed_enum_member->next_member;
    }
}

void Checker__check_struct_statement(Checker *self, Parsed_Struct_Statement *parsed_statement) {
    Checked_Named_Type *other_type = Checker__find_type(self, parsed_statement->super.name->lexeme);
    Checked_Struct_Type *struct_type;
    if (other_type != NULL) {
        if (other_type->super.kind != CHECKED_TYPE_KIND__STRUCT || (((Checked_Struct_Type *)other_type)->first_member != NULL)) {
            pWriter__write__todo(stderr_writer, __FILE__, __LINE__, "Report type redeclaration");
            abort();
        }
        struct_type = (Checked_Struct_Type *)other_type;
    } else {
        struct_type = Checked_Struct_Type__create(parsed_statement->super.name->location, parsed_statement->super.name->lexeme);
        Checker__append_type(self, (Checked_Named_Type *)struct_type);
    }

    if (parsed_statement->first_member != NULL) {
        Checked_Struct_Member *last_struct_member = NULL;
        Parsed_Struct_Member *parsed_member = parsed_statement->first_member;
        while (parsed_member != NULL) {
            Checked_Struct_Member *struct_member = Checked_Struct_Type__find_member(struct_type, parsed_member->name->lexeme);
            if (struct_member != NULL) {
                pWriter__write__todo(stderr_writer, __FILE__, __LINE__, "Report struct member duplicate");
                abort();
            }
            Checked_Type *struct_member_type = Checker__resolve_type(self, parsed_member->type);
            struct_member = Checked_Struct_Member__create(parsed_member->name->location, parsed_member->name->lexeme, struct_member_type);
            if (last_struct_member == NULL) {
                struct_type->first_member = struct_member;
            } else {
                last_struct_member->next_member = struct_member;
            }
            last_struct_member = struct_member;
            parsed_member = parsed_member->next_member;
        }
    }
}

Checked_Statement *Checker__check_statement(Checker *self, Parsed_Statement *parsed_statement);

Checked_Assignment_Statement *Checker__check_assignment_statement(Checker *self, Parsed_Assignment_Statement *parsed_statement) {
    Checked_Expression *object_expression = Checker__check_expression(self, parsed_statement->object_expression);
    Checked_Expression *value_expression = Checker__check_expression(self, parsed_statement->value_expression);
    Checked_Type__expect_same_type(object_expression->type, value_expression->type, value_expression->location);
    return Checked_Assignment_Statement__create(parsed_statement->super.location, object_expression, value_expression);
}

Checked_Statements *Checker__check_statements(Checker *self, Parsed_Statements *parsed_statements);

Checked_Block_Statement *Checker__check_block_statement(Checker *self, Parsed_Block_Statement *parsed_statement) {
    Checked_Statements *statements = Checker__check_statements(self, parsed_statement->statements);
    return Checked_Block_Statement__create(parsed_statement->super.location, statements);
}

Checked_Break_Statement *Checker__check_break_statement(Checker *self, Parsed_Break_Statement *parsed_statement) {
    return Checked_Break_Statement__create(parsed_statement->super.location);
}

Checked_Expression_Statement *Checker__check_expression_statement(Checker *self, Parsed_Expression_Statement *parsed_statement) {
    Checked_Expression *expression = Checker__check_expression(self, parsed_statement->expression);
    if (!Checked_Type__equals((Checked_Type *)Checker__get_builtin_type(self, CHECKED_TYPE_KIND__VOID), expression->type)) {
        /* TODO: Source_Location__warning(expression->location, String__create_from("Unused result value")); */
    }
    return Checked_Expression_Statement__create(parsed_statement->super.location, expression);
}

Checked_If_Statement *Checker__check_if_statement(Checker *self, Parsed_If_Statement *parsed_statement) {
    Checked_Expression *considition_expression = Checker__check_expression(self, parsed_statement->condition_expression);
    Checked_Type__expect_same_type((Checked_Type *)Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL), considition_expression->type, considition_expression->location);
    Checked_Statement *true_statement = Checker__check_statement(self, parsed_statement->true_statement);
    Checked_Statement *false_statement = NULL;
    if (parsed_statement->false_statement != NULL) {
        false_statement = Checker__check_statement(self, parsed_statement->false_statement);
    }
    return Checked_If_Statement__create(parsed_statement->super.location, considition_expression, true_statement, false_statement);
}

Checked_Return_Statement *Checker__check_return_statement(Checker *self, Parsed_Return_Statement *parsed_statement) {
    Checked_Expression *expression = NULL;
    if (parsed_statement->expression != NULL) {
        expression = Checker__check_expression(self, parsed_statement->expression);
        Checked_Type__expect_same_type(self->return_type, expression->type, expression->location);
    } else if (self->return_type->kind != CHECKED_TYPE_KIND__VOID) {
        Source_Location__error(parsed_statement->super.location, String__create_from("Missing expression"));
        abort();
    }
    return Checked_Return_Statement__create(parsed_statement->super.location, expression);
}

Checked_Variable_Statement *Checker__check_variable_statement(Checker *self, Parsed_Variable_Statement *parsed_statement) {
    Checked_Type *type = Checker__resolve_type(self, parsed_statement->type);
    Checked_Expression *expression = NULL;
    if (parsed_statement->expression != NULL) {
        expression = Checker__check_expression(self, parsed_statement->expression);
        Checked_Type__expect_same_type(type, expression->type, expression->location);
    }
    Checked_Variable_Symbol *variable = Checked_Variable__create(parsed_statement->super.name->location, parsed_statement->super.name->lexeme, type);
    Checked_Symbols__append_symbol(self->symbols, (Checked_Symbol *)variable);
    return Checked_Variable_Statement__create(parsed_statement->super.super.location, variable, expression, parsed_statement->is_external);
}

Checked_While_Statement *Checker__check_while_statement(Checker *self, Parsed_While_Statement *parsed_statement) {
    Checked_Expression *considition_expression = Checker__check_expression(self, parsed_statement->condition_expression);
    Checked_Type__expect_same_type((Checked_Type *)Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL), considition_expression->type, considition_expression->location);
    Checked_Statement *body_statement = Checker__check_statement(self, parsed_statement->body_statement);
    return Checked_While_Statement__create(parsed_statement->super.location, considition_expression, body_statement);
}

void Checker__check_function_declaration(Checker *self, Parsed_Function_Statement *parsed_statement) {
    String *function_name = parsed_statement->super.name->lexeme;
    Checked_Type *function_return_type = Checker__resolve_type(self, parsed_statement->return_type);
    Checked_Function_Parameter *function_first_parameter = NULL;
    Parsed_Function_Parameter *parsed_parameter = parsed_statement->first_parameter;
    if (parsed_parameter != NULL) {
        function_first_parameter = Checked_Function_Parameter__create(parsed_parameter->name->location, parsed_parameter->name->lexeme, Checker__resolve_type(self, parsed_parameter->type));
        Checked_Function_Parameter *function_last_parameter = function_first_parameter;
        parsed_parameter = parsed_parameter->next_parameter;
        while (parsed_parameter != NULL) {
            Checked_Function_Parameter *function_parameter = Checked_Function_Parameter__create(parsed_parameter->name->location, parsed_parameter->name->lexeme, Checker__resolve_type(self, parsed_parameter->type));
            function_last_parameter->next_parameter = function_parameter;
            function_last_parameter = function_parameter;
            parsed_parameter = parsed_parameter->next_parameter;
        }
    }
    Checked_Function_Type *function_type = Checked_Function_Type__create(parsed_statement->super.super.location, function_first_parameter, function_return_type);

    Checked_Symbol *other_symbol = Checked_Symbols__find_sibling_symbol(self->symbols, function_name);
    if (other_symbol != NULL) {
        if (other_symbol->kind != CHECKED_SYMBOL_KIND__FUNCTION || !Checked_Type__equals((Checked_Type *)function_type, (Checked_Type *)((Checked_Function_Symbol *)other_symbol)->function_type)) {
            pWriter__write__todo(stderr_writer, __FILE__, __LINE__, "Report function redeclaration");
            abort();
        }
    } else {
        Checked_Symbols__append_symbol(self->symbols, (Checked_Symbol *)Checked_Function_Symbol__create(parsed_statement->super.name->location, function_name, function_type));
    }
}

Checked_Statement *Checker__check_statement(Checker *self, Parsed_Statement *parsed_statement) {
    if (parsed_statement->kind == PARSED_STATEMENT_KIND__ASSIGNMENT) {
        return (Checked_Statement *)Checker__check_assignment_statement(self, (Parsed_Assignment_Statement *)parsed_statement);
    } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__BLOCK) {
        return (Checked_Statement *)Checker__check_block_statement(self, (Parsed_Block_Statement *)parsed_statement);
    } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__BREAK) {
        return (Checked_Statement *)Checker__check_break_statement(self, (Parsed_Break_Statement *)parsed_statement);
    } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__EXPRESSION) {
        return (Checked_Statement *)Checker__check_expression_statement(self, (Parsed_Expression_Statement *)parsed_statement);
    } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__IF) {
        return (Checked_Statement *)Checker__check_if_statement(self, (Parsed_If_Statement *)parsed_statement);
    } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__RETURN) {
        return (Checked_Statement *)Checker__check_return_statement(self, (Parsed_Return_Statement *)parsed_statement);
    } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__VARIABLE) {
        return (Checked_Statement *)Checker__check_variable_statement(self, (Parsed_Variable_Statement *)parsed_statement);
    } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__WHILE) {
        return (Checked_Statement *)Checker__check_while_statement(self, (Parsed_While_Statement *)parsed_statement);
    }
    Source_Location__error(parsed_statement->location, String__create_from("Unsupported statement"));
    abort();
}

Checked_Statements *Checker__check_statements(Checker *self, Parsed_Statements *parsed_statements) {
    /* Create and push block symbols */
    self->symbols = Checked_Symbols__create(self->symbols);

    Checked_Statements *checked_statements = Checked_Statements__create();
    Parsed_Statement *parsed_statement = parsed_statements->first_statement;
    while (parsed_statement != NULL) {
        Checked_Statement *checked_statement = Checker__check_statement(self, parsed_statement);
        Checked_Statements__append(checked_statements, checked_statement);
        parsed_statement = parsed_statement->next_statement;
    }

    /* Pop block symbols */
    self->symbols = self->symbols->parent;

    return checked_statements;
}

void Checker__check_function_definition(Checker *self, Parsed_Function_Statement *parsed_statement) {
    Checked_Symbol *symbol = Checked_Symbols__find_sibling_symbol(self->symbols, parsed_statement->super.name->lexeme);
    if (symbol == NULL || symbol->kind != CHECKED_SYMBOL_KIND__FUNCTION) {
        pWriter__write__todo(stderr_writer, __FILE__, __LINE__, "Report missing function symbol");
        abort();
    }
    Checked_Function_Symbol *function_symbol = (Checked_Function_Symbol *)symbol;
    Checked_Function_Type *function_type = function_symbol->function_type;
    self->return_type = function_type->return_type;

    /* Create and push function symbols */
    self->symbols = Checked_Symbols__create(self->symbols);

    if (function_type->first_parameter != NULL) {
        /* Create a symbol for each function parameter */
        Checked_Function_Parameter *parameter = function_type->first_parameter;
        while (parameter != NULL) {
            Checked_Symbols__append_symbol(self->symbols, (Checked_Symbol *)Checked_Function_Parameter_Symbol__create(parameter->location, parameter->name, parameter->type));
            parameter = parameter->next_parameter;
        }
    }

    /* Check statements */
    function_symbol->checked_statements = Checker__check_statements(self, parsed_statement->statements);

    /* Pop function symbols */
    self->symbols = self->symbols->parent;
}

Checked_Source *Checker__check_source(Checker *self, Parsed_Source *parsed_source) {
    Checked_Statements *checked_statements = Checked_Statements__create();

    Parsed_Statement *parsed_statement;

    /* Check all declared types */
    parsed_statement = parsed_source->statements->first_statement;
    while (parsed_statement != NULL) {
        if (parsed_statement->kind == PARSED_STATEMENT_KIND__STRUCT) {
            Checker__check_struct_statement(self, (Parsed_Struct_Statement *)parsed_statement);
        } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__ENUM) {
            Checker__check_enum_statement(self, (Parsed_Enum_Statement *)parsed_statement);
        }
        parsed_statement = parsed_statement->next_statement;
    }

    /* Collect other declarations */
    parsed_statement = parsed_source->statements->first_statement;
    while (parsed_statement != NULL) {
        Checked_Statement *checked_statement = NULL;
        if (parsed_statement->kind == PARSED_STATEMENT_KIND__FUNCTION) {
            Checker__check_function_declaration(self, (Parsed_Function_Statement *)parsed_statement);
        } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__VARIABLE) {
            checked_statement = (Checked_Statement *)Checker__check_variable_statement(self, (Parsed_Variable_Statement *)parsed_statement);
        } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__STRUCT) {
            /* ignored */
        } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__ENUM) {
            /* ignored */
        } else {
            Source_Location__error(parsed_statement->location, String__create_from("Unsupported statement"));
            abort();
        }
        if (checked_statement != NULL) {
            Checked_Statements__append(checked_statements, checked_statement);
        }
        parsed_statement = parsed_statement->next_statement;
    }

    /* Check function definitions */
    parsed_statement = parsed_source->statements->first_statement;
    while (parsed_statement != NULL) {
        if (parsed_statement->kind == PARSED_STATEMENT_KIND__FUNCTION) {
            Parsed_Function_Statement *function_statement = (Parsed_Function_Statement *)parsed_statement;
            if (function_statement->statements != NULL) {
                Checker__check_function_definition(self, function_statement);
            }
        } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__VARIABLE) {
            /* ignored */
        } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__STRUCT) {
            /* ignored */
        } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__ENUM) {
            /* ignored */
        } else {
            Source_Location__error(parsed_statement->location, String__create_from("Unsupported statement"));
            abort();
        }
        parsed_statement = parsed_statement->next_statement;
    }

    Checked_Source *checked_source = (Checked_Source *)malloc(sizeof(Checked_Source));
    checked_source->first_source = parsed_source->first_source;
    checked_source->first_symbol = self->symbols->first_symbol;
    checked_source->statements = checked_statements;
    return checked_source;
}

Checked_Source *check(Parsed_Source *parsed_source) {
    Checker *type_checker = Checker__create();

    return Checker__check_source(type_checker, parsed_source);
}
