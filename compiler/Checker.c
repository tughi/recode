/* Copyright (C) 2024 Stefan Selariu */

#include "Checker.h"
#include "File.h"

typedef struct Checker {
    Checked_Named_Type *first_type;
    Checked_Named_Type *last_type;
    Checked_Named_Type *last_builting_type;
    Checked_Symbols *global_symbols;
    Checked_Symbols *symbols;
    Checked_Type *return_type;
} Checker;

void Checker__append_type(Checker *self, Checked_Named_Type *type);

Checker *Checker__create() {
    Checker *checker = (Checker *)malloc(sizeof(Checker));
    checker->first_type = NULL;
    checker->last_type = NULL;
    checker->global_symbols = checker->symbols = Checked_Symbols__create(NULL);

    Source_Location *location = Source_Location__create(NULL, 0, 1);
    Checker__append_type(checker, Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__BOOL, sizeof(Checked_Named_Type), location, String__create_from("bool")));
    Checker__append_type(checker, Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__I16, sizeof(Checked_Named_Type), location, String__create_from("i16")));
    Checker__append_type(checker, Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__I32, sizeof(Checked_Named_Type), location, String__create_from("i32")));
    Checker__append_type(checker, Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__I64, sizeof(Checked_Named_Type), location, String__create_from("i64")));
    Checker__append_type(checker, Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__I8, sizeof(Checked_Named_Type), location, String__create_from("i8")));
    Checker__append_type(checker, Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__ISIZE, sizeof(Checked_Named_Type), location, String__create_from("isize")));
    Checker__append_type(checker, Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__U16, sizeof(Checked_Named_Type), location, String__create_from("u16")));
    Checker__append_type(checker, Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__U32, sizeof(Checked_Named_Type), location, String__create_from("u32")));
    Checker__append_type(checker, Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__U64, sizeof(Checked_Named_Type), location, String__create_from("u64")));
    Checker__append_type(checker, Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__U8, sizeof(Checked_Named_Type), location, String__create_from("u8")));
    Checker__append_type(checker, Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__ANY, sizeof(Checked_Named_Type), location, String__create_from("Any")));
    Checker__append_type(checker, Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__NOTHING, sizeof(Checked_Named_Type), location, String__create_from("__nothing__")));
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
    pWriter__style(stderr_writer, WRITER_STYLE__ERROR);
    pWriter__write__cstring(stderr_writer, "No such builtin type");
    pWriter__style(stderr_writer, WRITER_STYLE__DEFAULT);
    pWriter__end_line(stderr_writer);
    panic();
}

Checked_Expression *Checker__check_expression(Checker *self, Parsed_Expression *parsed_expression, Checked_Type *expected_type);

Checked_Type *Checker__resolve_type(Checker *self, Parsed_Type *parsed_type) {
    if (parsed_type->kind == PARSED_TYPE_KIND__NAMED) {
        Checked_Named_Type *type = Checker__find_type(self, ((Parsed_Named_Type *)parsed_type)->name);
        if (type != NULL) {
            return (Checked_Type *)type;
        }

        pWriter__begin_location_message(stderr_writer, parsed_type->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Undefined type: ");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    if (parsed_type->kind == PARSED_TYPE_KIND__POINTER) {
        return (Checked_Type *)Checked_Pointer_Type__create(parsed_type->location, Checker__resolve_type(self, ((Parsed_Pointer_Type *)parsed_type)->other_type));
    }
    if (parsed_type->kind == PARSED_TYPE_KIND__ARRAY) {
        Parsed_Array_Type *parsed_array_type = (Parsed_Array_Type *)parsed_type;
        Checked_Type *checked_item_type = Checker__resolve_type(self, parsed_array_type->item_type);
        Checked_Expression *checked_size_expression = NULL;
        if (parsed_array_type->size_expression != NULL) {
            checked_size_expression = Checker__check_expression(self, parsed_array_type->size_expression, (Checked_Type *)Checker__get_builtin_type(self, CHECKED_TYPE_KIND__ISIZE));
        }
        return (Checked_Type *)Checked_Array_Type__create(parsed_type->location, checked_item_type, parsed_array_type->is_checked, checked_size_expression);
    }
    if (parsed_type->kind == PARSED_TYPE_KIND__FUNCTION) {
        Parsed_Function_Type *parsed_function_type = (Parsed_Function_Type *)parsed_type;
        Checked_Function_Parameter *function_first_parameter = NULL;
        Parsed_Function_Parameter *parsed_parameter = parsed_function_type->first_parameter;
        if (parsed_parameter != NULL) {
            function_first_parameter = Checked_Function_Parameter__create(parsed_parameter->name->location, parsed_parameter->label ? parsed_parameter->label->lexeme : NULL, parsed_parameter->name->lexeme, Checker__resolve_type(self, parsed_parameter->type));
            Checked_Function_Parameter *function_last_parameter = function_first_parameter;
            parsed_parameter = parsed_parameter->next_parameter;
            while (parsed_parameter != NULL) {
                Checked_Function_Parameter *function_parameter = Checked_Function_Parameter__create(parsed_parameter->name->location, parsed_parameter->label ? parsed_parameter->label->lexeme : NULL, parsed_parameter->name->lexeme, Checker__resolve_type(self, parsed_parameter->type));
                function_last_parameter->next_parameter = function_parameter;
                function_last_parameter = function_parameter;
                parsed_parameter = parsed_parameter->next_parameter;
            }
        }
        Checked_Type *function_return_type;
        if (parsed_function_type->return_type == NULL) {
            function_return_type = (Checked_Type *)Checker__get_builtin_type(self, CHECKED_TYPE_KIND__NOTHING);
        } else {
            function_return_type = Checker__resolve_type(self, parsed_function_type->return_type);
        }
        Checked_Function_Type *function_type = Checked_Function_Type__create(parsed_function_type->super.location, function_first_parameter, function_return_type);
        return (Checked_Type *)Checked_Function_Pointer_Type__create(parsed_type->location, function_type);
    }
    pWriter__write__todo(stderr_writer, __FILE__, __LINE__, "Report undefined type");
    panic();
}

void Checker__require_numeric_type(Checker *self, Checked_Type *type, Source_Location *location) {
    if (!Checked_Type__is_numeric_type(type)) {
        pWriter__begin_location_message(stderr_writer, location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Expected numeric type");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
}

void Checker__require_same_type(Checker *self, Checked_Type *expected_type, Checked_Type *actual_type, Source_Location *location) {
    if (expected_type->kind == CHECKED_TYPE_KIND__POINTER && actual_type->kind == CHECKED_TYPE_KIND__NULL) {
        return;
    }
    if (!Checked_Type__equals(expected_type, actual_type)) {
        pWriter__begin_location_message(stderr_writer, location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Expected type ");
        pWriter__write__checked_type(stderr_writer, expected_type);
        pWriter__write__cstring(stderr_writer, " but got ");
        pWriter__write__checked_type(stderr_writer, actual_type);
        pWriter__end_location_message(stderr_writer);
        panic();
    }
}

Checked_Expression *Checker__check_add_expression(Checker *self, Parsed_Add_Expression *parsed_expression, Checked_Type *expected_type) {
    Checked_Expression *left_expression = Checker__check_expression(self, parsed_expression->super.left_expression, expected_type);
    Checker__require_numeric_type(self, left_expression->type, left_expression->location);
    Checked_Expression *right_expression = Checker__check_expression(self, parsed_expression->super.right_expression, left_expression->type);
    Checker__require_same_type(self, left_expression->type, right_expression->type, right_expression->location);
    return (Checked_Expression *)Checked_Add_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

Checked_Expression *Checker__check_address_of_expression(Checker *self, Parsed_Address_Of_Expression *parsed_expression) {
    Checked_Expression *other_expression = Checker__check_expression(self, parsed_expression->super.other_expression, NULL);
    switch (other_expression->kind) {
    case CHECKED_EXPRESSION_KIND__MEMBER_ACCESS:
    case CHECKED_EXPRESSION_KIND__SYMBOL:
        return (Checked_Expression *)Checked_Address_Of_Expression__create(parsed_expression->super.super.location, (Checked_Type *)Checked_Pointer_Type__create(other_expression->location, other_expression->type), other_expression);
    }
    pWriter__begin_location_message(stderr_writer, other_expression->location, WRITER_STYLE__ERROR);
    pWriter__write__cstring(stderr_writer, "Cannot take address of this expression");
    pWriter__end_location_message(stderr_writer);
    panic();
}

Checked_Expression *Checker__check_array_access_expression(Checker *self, Parsed_Array_Access_Expression *parsed_expression) {
    Checked_Expression *array_expression = Checker__check_expression(self, parsed_expression->array_expression, NULL);
    Checked_Type *array_type = array_expression->type;
    if (array_type->kind != CHECKED_TYPE_KIND__ARRAY) {
        pWriter__begin_location_message(stderr_writer, parsed_expression->array_expression->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Not an array");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    Checked_Type *type = ((Checked_Pointer_Type *)array_type)->other_type;
    Checked_Expression *index_expression = Checker__check_expression(self, parsed_expression->index_expression, (Checked_Type *)Checker__get_builtin_type(self, CHECKED_TYPE_KIND__ISIZE));
    Checker__require_numeric_type(self, index_expression->type, index_expression->location);
    return (Checked_Expression *)Checked_Array_Access_Expression__create(parsed_expression->super.location, type, array_expression, index_expression);
}

Checked_Expression *Checker__check_bool_expression(Checker *self, Parsed_Bool_Expression *parsed_expression) {
    Checked_Type *expression_type = (Checked_Type *)Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL);
    bool value = parsed_expression->value;
    return (Checked_Expression *)Checked_Bool_Expression__create(parsed_expression->super.super.location, expression_type, value);
}

Checked_Function_Symbol *Checker__find_function_symbol(Checker *self, String *function_name, Parsed_Call_Argument *first_call_argument, Checked_Type *receiver_type, int *similars) {
    Checked_Symbol *symbol = self->global_symbols->first_symbol;
    for (; symbol != NULL; symbol = symbol->next_symbol) {
        if (symbol->kind == CHECKED_SYMBOL_KIND__FUNCTION) {
            Checked_Function_Symbol *function_symbol = (Checked_Function_Symbol *)symbol;
            if (String__equals_string(function_symbol->function_name, function_name)) {
                (*similars)++;
                Checked_Function_Parameter *function_parameter = function_symbol->function_type->first_parameter;
                if (receiver_type != NULL) {
                    if (function_symbol->receiver_type == NULL || !Checked_Type__equals(function_symbol->receiver_type, receiver_type)) {
                        continue;
                    }
                    if (function_parameter == NULL || !Checked_Type__equals(function_parameter->type, receiver_type)) {
                        panic();
                    }
                    function_parameter = function_parameter->next_parameter;
                }
                Parsed_Call_Argument *call_argument = first_call_argument;
                while (function_parameter != NULL && call_argument != NULL) {
                    if (function_parameter->label == NULL) {
                        if (call_argument->name != NULL) {
                            break;
                        }
                    } else if (call_argument->name == NULL || !String__equals_string(function_parameter->label, call_argument->name->super.lexeme)) {
                        break;
                    }
                    function_parameter = function_parameter->next_parameter;
                    call_argument = call_argument->next_argument;
                }
                if (function_parameter == NULL && call_argument == NULL) {
                    return function_symbol;
                }
            }
        }
    }
    return NULL;
}

typedef struct Checked_Callable {
    Checked_Function_Type *function_type;
    Checked_Expression *callee_expression;
    Checked_Expression *receiver_expression;
} Checked_Callable;

Checked_Callable Checker__check_callable_symbol(Checker *self, Token *symbol_name, Parsed_Call_Argument *first_parsed_argument, Checked_Expression *receiver_expression) {
    if (receiver_expression == NULL) {
        Checked_Symbol *symbol = Checked_Symbols__find_symbol(self->symbols, symbol_name->lexeme);
        if (symbol != NULL) {
            if (symbol->type->kind != CHECKED_TYPE_KIND__FUNCTION_POINTER) {
                pWriter__begin_location_message(stderr_writer, symbol_name->location, WRITER_STYLE__ERROR);
                pWriter__write__cstring(stderr_writer, "Not a function pointer");
                pWriter__end_location_message(stderr_writer);
                panic();
            }
            return (Checked_Callable){
                .function_type = ((Checked_Function_Pointer_Type *)symbol->type)->function_type,
                .callee_expression = (Checked_Expression *)Checked_Symbol_Expression__create(symbol_name->location, symbol->type, (Checked_Symbol *)symbol),
                .receiver_expression = NULL,
            };
        }
    }

    int similar_function_symbols = 0;
    Checked_Function_Symbol *function_symbol = Checker__find_function_symbol(self, symbol_name->lexeme, first_parsed_argument, receiver_expression != NULL ? receiver_expression->type : NULL, &similar_function_symbols);
    if (function_symbol == NULL) {
        pWriter__begin_location_message(stderr_writer, symbol_name->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Undefined function: ");
        pWriter__write__token(stderr_writer, symbol_name);
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    return (Checked_Callable){
        .function_type = function_symbol->function_type,
        .callee_expression = (Checked_Expression *)Checked_Symbol_Expression__create(symbol_name->location, function_symbol->super.type, (Checked_Symbol *)function_symbol),
        .receiver_expression = receiver_expression,
    };
}

Checked_Callable Checker__check_callable_member(Checker *self, Parsed_Member_Access_Expression *parsed_callee_expression, Parsed_Call_Argument *first_parsed_argument) {
    Checked_Expression *object_expression = Checker__check_expression(self, parsed_callee_expression->object_expression, NULL);
    Checked_Type *object_type = object_expression->type;
    if (object_type->kind == CHECKED_TYPE_KIND__STRUCT || object_type->kind == CHECKED_TYPE_KIND__POINTER && ((Checked_Pointer_Type *)object_type)->other_type->kind == CHECKED_TYPE_KIND__STRUCT) {
        Checked_Struct_Type *struct_type;
        if (object_type->kind == CHECKED_TYPE_KIND__STRUCT) {
            struct_type = (Checked_Struct_Type *)object_type;
        } else {
            struct_type = (Checked_Struct_Type *)((Checked_Pointer_Type *)object_type)->other_type;
        }
        Checked_Struct_Member *struct_member = Checked_Struct_Type__find_member(struct_type, parsed_callee_expression->member_name->lexeme);
        if (struct_member != NULL) {
            if (struct_member->type->kind != CHECKED_TYPE_KIND__FUNCTION_POINTER) {
                pWriter__begin_location_message(stderr_writer, parsed_callee_expression->member_name->location, WRITER_STYLE__ERROR);
                pWriter__write__cstring(stderr_writer, "Not a function pointer");
                pWriter__end_location_message(stderr_writer);
                panic();
            }
            return (Checked_Callable){
                .function_type = ((Checked_Function_Pointer_Type *)struct_member->type)->function_type,
                .callee_expression = (Checked_Expression *)Checked_Member_Access_Expression__create(parsed_callee_expression->super.location, struct_member->type, object_expression, struct_member),
                .receiver_expression = NULL,
            };
        }
        if (object_type->kind == CHECKED_TYPE_KIND__STRUCT) {
            /* auto reference */
            object_type = (Checked_Type *)Checked_Pointer_Type__create(object_type->location, object_type);
            object_expression = (Checked_Expression *)Checked_Address_Of_Expression__create(parsed_callee_expression->object_expression->location, object_type, object_expression);
        }
    }
    return Checker__check_callable_symbol(self, parsed_callee_expression->member_name, first_parsed_argument, object_expression);
}

Checked_Expression *Checker__check_call_expression(Checker *self, Parsed_Call_Expression *parsed_expression) {
    Checked_Callable checked_callable;
    switch (parsed_expression->callee_expression->kind) {
    case PARSED_EXPRESSION_KIND__MEMBER_ACCESS:
        checked_callable = Checker__check_callable_member(self, (Parsed_Member_Access_Expression *)parsed_expression->callee_expression, parsed_expression->first_argument);
        break;
    case PARSED_EXPRESSION_KIND__SYMBOL:
        checked_callable = Checker__check_callable_symbol(self, ((Parsed_Symbol_Expression *)parsed_expression->callee_expression)->name, parsed_expression->first_argument, NULL);
        break;
    default:
        pWriter__begin_location_message(stderr_writer, parsed_expression->callee_expression->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Unsupported callee expression");
        pWriter__end_location_message(stderr_writer);
        panic();
    }

    Checked_Call_Argument *first_argument = NULL;
    if (parsed_expression->first_argument != NULL || checked_callable.receiver_expression != NULL) {
        Checked_Call_Argument *last_argument = NULL;
        Checked_Function_Parameter *function_parameter = checked_callable.function_type->first_parameter;
        if (function_parameter == NULL) {
            pWriter__begin_location_message(stderr_writer, checked_callable.callee_expression->location, WRITER_STYLE__ERROR);
            pWriter__write__cstring(stderr_writer, "Function has no parameters");
            pWriter__end_location_message(stderr_writer);
            panic();
        }
        if (checked_callable.receiver_expression != NULL) {
            Checker__require_same_type(self, function_parameter->type, checked_callable.receiver_expression->type, checked_callable.receiver_expression->location);
            first_argument = last_argument = Checked_Call_Argument__create(checked_callable.receiver_expression);
            function_parameter = function_parameter->next_parameter;
        }
        Parsed_Call_Argument *parsed_argument = parsed_expression->first_argument;
        while (function_parameter != NULL && parsed_argument != NULL) {
            Checked_Expression *argument_expression = Checker__check_expression(self, parsed_argument->expression, function_parameter->type);
            Checker__require_same_type(self, function_parameter->type, argument_expression->type, argument_expression->location);
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
            pWriter__begin_location_message(stderr_writer, checked_callable.callee_expression->location, WRITER_STYLE__TODO);
            pWriter__write__cstring(stderr_writer, "Report too few arguments");
            pWriter__end_location_message(stderr_writer);
            panic();
        }
        if (parsed_argument != NULL) {
            pWriter__begin_location_message(stderr_writer, checked_callable.callee_expression->location, WRITER_STYLE__TODO);
            pWriter__write__cstring(stderr_writer, "Report too many arguments");
            pWriter__end_location_message(stderr_writer);
            panic();
        }
    }
    return (Checked_Expression *)Checked_Call_Expression__create(checked_callable.callee_expression->location, checked_callable.function_type->return_type, checked_callable.callee_expression, first_argument);
}

Checked_Expression *Checker__check_cast_expression(Checker *self, Parsed_Cast_Expression *parsed_expression) {
    Checked_Type *expression_type = Checker__resolve_type(self, parsed_expression->type);
    Checked_Expression *other_expression = Checker__check_expression(self, parsed_expression->super.other_expression, NULL);
    Checked_Type *other_expression_type = other_expression->type;
    bool can_cast = false;
    if (expression_type->kind == CHECKED_TYPE_KIND__POINTER) {
        Checked_Pointer_Type *expression_pointer_type = (Checked_Pointer_Type *)expression_type;
        if (other_expression_type->kind == CHECKED_TYPE_KIND__POINTER) {
            can_cast = true;
        } else if (expression_pointer_type->other_type->kind == CHECKED_TYPE_KIND__ANY) {
            if (other_expression_type->kind == CHECKED_TYPE_KIND__ARRAY) {
                can_cast = true;
            }
        }
    } else if (Checked_Type__is_numeric_type(expression_type)) {
        can_cast = true;
    } else if (expression_type->kind == CHECKED_TYPE_KIND__ARRAY) {
        if (other_expression_type->kind == CHECKED_TYPE_KIND__POINTER) {
            can_cast = true;
        }
    }
    if (Checked_Type__equals(expression_type, other_expression_type)) {
        pWriter__begin_location_message(stderr_writer, parsed_expression->super.super.location, WRITER_STYLE__WARNING);
        pWriter__write__cstring(stderr_writer, "Redundant cast");
        pWriter__end_location_message(stderr_writer);
    }
    if (!can_cast) {
        pWriter__begin_location_message(stderr_writer, parsed_expression->super.super.location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Cannot cast ");
        pWriter__write__checked_type(stderr_writer, other_expression_type);
        pWriter__write__cstring(stderr_writer, " to ");
        pWriter__write__checked_type(stderr_writer, expression_type);
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    return (Checked_Expression *)Checked_Cast_Expression__create(parsed_expression->super.super.location, expression_type, other_expression);
}

Checked_Expression *Checker__check_character_expression(Checker *self, Parsed_Character_Expression *parsed_expression) {
    Checked_Type *expression_type = (Checked_Type *)Checker__get_builtin_type(self, CHECKED_TYPE_KIND__U8);
    char value = parsed_expression->value;
    return (Checked_Expression *)Checked_Character_Expression__create(parsed_expression->super.super.location, expression_type, value);
}

Checked_Expression *Checker__check_dereference_expression(Checker *self, Parsed_Dereference_Expression *parsed_expression) {
    Checked_Expression *other_expression = Checker__check_expression(self, parsed_expression->super.other_expression, NULL);
    Checked_Type *other_type = other_expression->type;
    if (other_type->kind != CHECKED_TYPE_KIND__POINTER) {
        pWriter__begin_location_message(stderr_writer, parsed_expression->super.super.location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Not a pointer");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    Checked_Pointer_Type *pointer_type = (Checked_Pointer_Type *)other_type;
    Checked_Type *type = pointer_type->other_type;
    return (Checked_Expression *)Checked_Dereference_Expression__create(parsed_expression->super.super.location, type, other_expression);
}

Checked_Expression *Checker__check_divide_expression(Checker *self, Parsed_Divide_Expression *parsed_expression, Checked_Type *expected_type) {
    Checked_Expression *left_expression = Checker__check_expression(self, parsed_expression->super.left_expression, expected_type);
    Checker__require_numeric_type(self, left_expression->type, left_expression->location);
    Checked_Expression *right_expression = Checker__check_expression(self, parsed_expression->super.right_expression, left_expression->type);
    Checker__require_same_type(self, left_expression->type, right_expression->type, right_expression->location);
    return (Checked_Expression *)Checked_Divide_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

Checked_Expression *Checker__check_equals_expression(Checker *self, Parsed_Equals_Expression *parsed_expression, Checked_Type *expected_type) {
    Checked_Expression *left_expression = Checker__check_expression(self, parsed_expression->super.left_expression, expected_type);
    Checked_Expression *right_expression = Checker__check_expression(self, parsed_expression->super.right_expression, left_expression->type);
    Checker__require_same_type(self, left_expression->type, right_expression->type, right_expression->location);
    return (Checked_Expression *)Checked_Equals_Expression__create(parsed_expression->super.super.location, (Checked_Type *)Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL), left_expression, right_expression);
}

Checked_Expression *Checker__check_greater_expression(Checker *self, Parsed_Greater_Expression *parsed_expression, Checked_Type *expected_type) {
    Checked_Expression *left_expression = Checker__check_expression(self, parsed_expression->super.left_expression, expected_type);
    Checker__require_numeric_type(self, left_expression->type, left_expression->location);
    Checked_Expression *right_expression = Checker__check_expression(self, parsed_expression->super.right_expression, left_expression->type);
    Checker__require_same_type(self, left_expression->type, right_expression->type, right_expression->location);
    return (Checked_Expression *)Checked_Greater_Expression__create(parsed_expression->super.super.location, (Checked_Type *)Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL), left_expression, right_expression);
}

Checked_Expression *Checker__check_greater_or_equals_expression(Checker *self, Parsed_Greater_Or_Equals_Expression *parsed_expression, Checked_Type *expected_type) {
    Checked_Expression *left_expression = Checker__check_expression(self, parsed_expression->super.left_expression, expected_type);
    Checker__require_numeric_type(self, left_expression->type, left_expression->location);
    Checked_Expression *right_expression = Checker__check_expression(self, parsed_expression->super.right_expression, left_expression->type);
    Checker__require_same_type(self, left_expression->type, right_expression->type, right_expression->location);
    return (Checked_Expression *)Checked_Greater_Or_Equals_Expression__create(parsed_expression->super.super.location, (Checked_Type *)Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL), left_expression, right_expression);
}

Checked_Expression *Checker__check_group_expression(Checker *self, Parsed_Group_Expression *parsed_expression, Checked_Type *expected_type) {
    Checked_Expression *other_expression = Checker__check_expression(self, parsed_expression->other_expression, expected_type);
    return (Checked_Expression *)Checked_Group_Expression__create(parsed_expression->super.location, other_expression->type, other_expression);
}

Checked_Expression *Checker__check_integer_expression(Checker *self, Parsed_Integer_Expression *parsed_expression, Checked_Type *expected_type) {
    Checked_Type *expression_type;
    if (parsed_expression->type != NULL) {
        expression_type = Checker__resolve_type(self, (Parsed_Type *)parsed_expression->type);
    } else if (expected_type != NULL) {
        expression_type = expected_type;
    } else {
        expression_type = (Checked_Type *)Checker__get_builtin_type(self, CHECKED_TYPE_KIND__I32);
    }
    uint64_t value = parsed_expression->value;
    return (Checked_Expression *)Checked_Integer_Expression__create(parsed_expression->super.super.location, expression_type, value);
}

Checked_Expression *Checker__check_less_expression(Checker *self, Parsed_Less_Expression *parsed_expression, Checked_Type *expected_type) {
    Checked_Expression *left_expression = Checker__check_expression(self, parsed_expression->super.left_expression, expected_type);
    Checker__require_numeric_type(self, left_expression->type, left_expression->location);
    Checked_Expression *right_expression = Checker__check_expression(self, parsed_expression->super.right_expression, left_expression->type);
    Checker__require_same_type(self, left_expression->type, right_expression->type, right_expression->location);
    return (Checked_Expression *)Checked_Less_Expression__create(parsed_expression->super.super.location, (Checked_Type *)Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL), left_expression, right_expression);
}

Checked_Expression *Checker__check_less_or_equals_expression(Checker *self, Parsed_Less_Or_Equals_Expression *parsed_expression, Checked_Type *expected_type) {
    Checked_Expression *left_expression = Checker__check_expression(self, parsed_expression->super.left_expression, expected_type);
    Checker__require_numeric_type(self, left_expression->type, left_expression->location);
    Checked_Expression *right_expression = Checker__check_expression(self, parsed_expression->super.right_expression, left_expression->type);
    Checker__require_same_type(self, left_expression->type, right_expression->type, right_expression->location);
    return (Checked_Expression *)Checked_Less_Or_Equals_Expression__create(parsed_expression->super.super.location, (Checked_Type *)Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL), left_expression, right_expression);
}

Checked_Expression *Checker__check_logic_and_expression(Checker *self, Parsed_Logic_And_Expression *parsed_expression) {
    Checked_Expression *left_expression = Checker__check_expression(self, parsed_expression->super.left_expression, (Checked_Type *)Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL));
    Checker__require_same_type(self, (Checked_Type *)Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL), left_expression->type, left_expression->location);
    Checked_Expression *right_expression = Checker__check_expression(self, parsed_expression->super.right_expression, left_expression->type);
    Checker__require_same_type(self, left_expression->type, right_expression->type, right_expression->location);
    return (Checked_Expression *)Checked_Logic_And_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

Checked_Expression *Checker__check_logic_or_expression(Checker *self, Parsed_Logic_Or_Expression *parsed_expression) {
    Checked_Expression *left_expression = Checker__check_expression(self, parsed_expression->super.left_expression, (Checked_Type *)Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL));
    Checker__require_same_type(self, (Checked_Type *)Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL), left_expression->type, left_expression->location);
    Checked_Expression *right_expression = Checker__check_expression(self, parsed_expression->super.right_expression, left_expression->type);
    Checker__require_same_type(self, left_expression->type, right_expression->type, right_expression->location);
    return (Checked_Expression *)Checked_Logic_Or_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

Checked_Expression *Checker__check_make_expression(Checker *self, Parsed_Make_Expression *parsed_expression) {
    Checked_Type *expression_type = Checker__resolve_type(self, parsed_expression->type);
    Checked_Struct_Type *struct_type = NULL;
    if (expression_type->kind == CHECKED_TYPE_KIND__POINTER) {
        Checked_Type *other_type = ((Checked_Pointer_Type *)expression_type)->other_type;
        if (other_type->kind == CHECKED_TYPE_KIND__STRUCT) {
            struct_type = (Checked_Struct_Type *)other_type;
        } else {
            pWriter__begin_location_message(stderr_writer, parsed_expression->super.location, WRITER_STYLE__ERROR);
            pWriter__write__cstring(stderr_writer, "Not a struct pointer type");
            pWriter__end_location_message(stderr_writer);
            panic();
        }
    } else if (expression_type->kind == CHECKED_TYPE_KIND__STRUCT) {
        struct_type = (Checked_Struct_Type *)expression_type;
    } else {
        pWriter__begin_location_message(stderr_writer, parsed_expression->super.location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Not a struct type");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    Checked_Make_Struct_Argument *first_argument = NULL;
    if (parsed_expression->first_argument != NULL) {
        Checked_Make_Struct_Argument *last_argument = NULL;
        Parsed_Call_Argument *parsed_argument = parsed_expression->first_argument;
        while (parsed_argument != NULL) {
            if (parsed_argument->name == NULL) {
                pWriter__begin_location_message(stderr_writer, parsed_argument->expression->location, WRITER_STYLE__ERROR);
                pWriter__write__cstring(stderr_writer, "Expected named argument");
                pWriter__end_location_message(stderr_writer);
                panic();
            }
            Checked_Struct_Member *struct_member = Checked_Struct_Type__find_member(struct_type, parsed_argument->name->super.lexeme);
            if (struct_member == NULL) {
                pWriter__begin_location_message(stderr_writer, parsed_argument->location, WRITER_STYLE__ERROR);
                pWriter__write__cstring(stderr_writer, "No such struct member");
                pWriter__end_location_message(stderr_writer);
                panic();
            }
            Checked_Expression *argument_expression = Checker__check_expression(self, parsed_argument->expression, struct_member->type);
            Checker__require_same_type(self, struct_member->type, argument_expression->type, argument_expression->location);
            Checked_Make_Struct_Argument *argument = first_argument;
            while (argument != NULL) {
                if (argument->struct_member == struct_member) {
                    pWriter__begin_location_message(stderr_writer, parsed_argument->location, WRITER_STYLE__ERROR);
                    pWriter__write__cstring(stderr_writer, "Struct member already initialized here: ");
                    pWriter__write__location(stderr_writer, argument->struct_member->location);
                    pWriter__end_location_message(stderr_writer);
                    panic();
                }
                argument = argument->next_argument;
            }
            argument = Checked_Make_Struct_Argument__create(struct_member, argument_expression);
            if (last_argument == NULL) {
                first_argument = argument;
            } else {
                last_argument->next_argument = argument;
            }
            last_argument = argument;
            parsed_argument = parsed_argument->next_argument;
        }
    }
    return (Checked_Expression *)Checked_Make_Struct_Expression__create(parsed_expression->super.location, expression_type, struct_type, first_argument);
}

Checked_Expression *Checker__check_member_access_expression(Checker *self, Parsed_Member_Access_Expression *parsed_expression) {
    Checked_Expression *object_expression = Checker__check_expression(self, parsed_expression->object_expression, NULL);
    Checked_Type *object_type = object_expression->type;
    if (object_type->kind == CHECKED_TYPE_KIND__POINTER) {
        object_type = ((Checked_Pointer_Type *)object_type)->other_type;
    }
    if (object_type->kind != CHECKED_TYPE_KIND__STRUCT) {
        pWriter__begin_location_message(stderr_writer, object_expression->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Not a struct type");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    Checked_Struct_Type *struct_type = (Checked_Struct_Type *)object_type;
    Checked_Struct_Member *member = Checked_Struct_Type__find_member(struct_type, parsed_expression->member_name->lexeme);
    if (member == NULL) {
        pWriter__begin_location_message(stderr_writer, parsed_expression->member_name->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "No such struct member");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    return (Checked_Expression *)Checked_Member_Access_Expression__create(parsed_expression->super.location, member->type, object_expression, member);
}

Checked_Expression *Checker__check_minus_expression(Checker *self, Parsed_Minus_Expression *parsed_expression, Checked_Type *expected_type) {
    Checked_Expression *other_expression = Checker__check_expression(self, parsed_expression->super.other_expression, expected_type);
    Checked_Type *other_expression_type = other_expression->type;
    Checker__require_numeric_type(self, other_expression_type, other_expression->location);
    return (Checked_Expression *)Checked_Minus_Expression__create(parsed_expression->super.super.location, other_expression_type, other_expression);
}

Checked_Expression *Checker__check_modulo_expression(Checker *self, Parsed_Modulo_Expression *parsed_expression, Checked_Type *expected_type) {
    Checked_Expression *left_expression = Checker__check_expression(self, parsed_expression->super.left_expression, expected_type);
    Checker__require_numeric_type(self, left_expression->type, left_expression->location);
    Checked_Expression *right_expression = Checker__check_expression(self, parsed_expression->super.right_expression, left_expression->type);
    Checker__require_same_type(self, left_expression->type, right_expression->type, right_expression->location);
    return (Checked_Expression *)Checked_Modulo_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

Checked_Expression *Checker__check_multiply_expression(Checker *self, Parsed_Multiply_Expression *parsed_expression, Checked_Type *expected_type) {
    Checked_Expression *left_expression = Checker__check_expression(self, parsed_expression->super.left_expression, expected_type);
    Checker__require_numeric_type(self, left_expression->type, left_expression->location);
    Checked_Expression *right_expression = Checker__check_expression(self, parsed_expression->super.right_expression, left_expression->type);
    Checker__require_same_type(self, left_expression->type, right_expression->type, right_expression->location);
    return (Checked_Expression *)Checked_Multiply_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

Checked_Expression *Checker__check_not_expression(Checker *self, Parsed_Not_Expression *parsed_expression) {
    Checked_Expression *other_expression = Checker__check_expression(self, parsed_expression->super.other_expression, (Checked_Type *)Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL));
    Checked_Type *other_expression_type = other_expression->type;
    Checker__require_same_type(self, (Checked_Type *)Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL), other_expression_type, other_expression->location);
    return (Checked_Expression *)Checked_Not_Expression__create(parsed_expression->super.super.location, other_expression_type, other_expression);
}

Checked_Expression *Checker__check_not_equals_expression(Checker *self, Parsed_Not_Equals_Expression *parsed_expression) {
    Checked_Expression *left_expression = Checker__check_expression(self, parsed_expression->super.left_expression, NULL);
    Checked_Expression *right_expression = Checker__check_expression(self, parsed_expression->super.right_expression, left_expression->type);
    Checker__require_same_type(self, left_expression->type, right_expression->type, right_expression->location);
    return (Checked_Expression *)Checked_Not_Equals_Expression__create(parsed_expression->super.super.location, (Checked_Type *)Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL), left_expression, right_expression);
}

Checked_Expression *Checker__check_null_expression(Checker *self, Parsed_Null_Expression *parsed_expression) {
    Checked_Type *expression_type = (Checked_Type *)Checker__get_builtin_type(self, CHECKED_TYPE_KIND__NULL);
    return (Checked_Expression *)Checked_Null_Expression__create(parsed_expression->super.literal->location, expression_type);
}

Checked_Expression *Checker__check_sizeof_expression(Checker *self, Parsed_Sizeof_Expression *parsed_expression) {
    Checked_Type *expression_type = (Checked_Type *)Checker__get_builtin_type(self, CHECKED_TYPE_KIND__ISIZE);
    Checked_Type *sized_type = Checker__resolve_type(self, parsed_expression->type);
    return (Checked_Expression *)Checked_Sizeof_Expression__create(parsed_expression->super.location, expression_type, sized_type);
}

Checked_Expression *Checker__check_string_expression(Checker *self, Parsed_String_Expression *parsed_expression) {
    Checked_Type *char_type = (Checked_Type *)Checker__get_builtin_type(self, CHECKED_TYPE_KIND__U8);
    Checked_Type *expression_type = (Checked_Type *)Checked_Pointer_Type__create(parsed_expression->super.literal->location, char_type);
    String *value = parsed_expression->value;
    return (Checked_Expression *)Checked_String_Expression__create(parsed_expression->super.super.location, expression_type, value);
}

Checked_Expression *Checker__check_substract_expression(Checker *self, Parsed_Substract_Expression *parsed_expression, Checked_Type *expected_type) {
    Checked_Expression *left_expression = Checker__check_expression(self, parsed_expression->super.left_expression, expected_type);
    Checker__require_numeric_type(self, left_expression->type, left_expression->location);
    Checked_Expression *right_expression = Checker__check_expression(self, parsed_expression->super.right_expression, left_expression->type);
    Checker__require_same_type(self, left_expression->type, right_expression->type, right_expression->location);
    return (Checked_Expression *)Checked_Substract_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

Checked_Expression *Checker__check_symbol_expression(Checker *self, Parsed_Symbol_Expression *parsed_expression, Checked_Type *expected_type) {
    if (expected_type != NULL && expected_type->kind == CHECKED_TYPE_KIND__FUNCTION_POINTER) {
        Checked_Symbol *symbol = self->global_symbols->first_symbol;
        for (; symbol != NULL; symbol = symbol->next_symbol) {
            if (symbol->kind == CHECKED_SYMBOL_KIND__FUNCTION) {
                Checked_Function_Symbol *function_symbol = (Checked_Function_Symbol *)symbol;
                if (String__equals_string(function_symbol->function_name, parsed_expression->name->lexeme) && Checked_Type__equals(symbol->type, expected_type)) {
                    return (Checked_Expression *)Checked_Symbol_Expression__create(parsed_expression->super.location, expected_type, symbol);
                }
            }
        }
        pWriter__begin_location_message(stderr_writer, parsed_expression->name->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Undefined function: ");
        pWriter__write__string(stderr_writer, parsed_expression->name->lexeme);
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    Checked_Symbol *symbol = Checked_Symbols__find_symbol(self->symbols, parsed_expression->name->lexeme);
    if (symbol == NULL) {
        if (expected_type == NULL) {
            Checked_Symbol *function_symbol = NULL;
            int function_simbols = 0;
            symbol = self->global_symbols->first_symbol;
            for (; symbol != NULL; symbol = symbol->next_symbol) {
                if (symbol->kind == CHECKED_SYMBOL_KIND__FUNCTION && String__equals_string(((Checked_Function_Symbol *)symbol)->function_name, parsed_expression->name->lexeme)) {
                    function_symbol = symbol;
                    function_simbols++;
                }
            }
            if (function_simbols == 1) {
                return (Checked_Expression *)Checked_Symbol_Expression__create(parsed_expression->super.location, function_symbol->type, function_symbol);
            } else if (function_simbols > 1) {
                pWriter__begin_location_message(stderr_writer, parsed_expression->name->location, WRITER_STYLE__ERROR);
                pWriter__write__cstring(stderr_writer, "Found ");
                pWriter__write__int64(stderr_writer, function_simbols);
                pWriter__write__cstring(stderr_writer, " functions named: ");
                pWriter__write__string(stderr_writer, parsed_expression->name->lexeme);
                pWriter__end_location_message(stderr_writer);
                panic();
            }
        }
        pWriter__begin_location_message(stderr_writer, parsed_expression->name->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Undefined symbol: ");
        pWriter__write__string(stderr_writer, parsed_expression->name->lexeme);
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    if (symbol->type == NULL) {
        pWriter__begin_location_message(stderr_writer, parsed_expression->name->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Symbol without type");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    return (Checked_Expression *)Checked_Symbol_Expression__create(parsed_expression->super.location, symbol->type, symbol);
}

Checked_Expression *Checker__check_expression(Checker *self, Parsed_Expression *parsed_expression, Checked_Type *expected_type) {
    switch (parsed_expression->kind) {
    case PARSED_EXPRESSION_KIND__ADD:
        return Checker__check_add_expression(self, (Parsed_Add_Expression *)parsed_expression, expected_type);
    case PARSED_EXPRESSION_KIND__ADDRESS_OF:
        return Checker__check_address_of_expression(self, (Parsed_Address_Of_Expression *)parsed_expression);
    case PARSED_EXPRESSION_KIND__ARRAY_ACCESS:
        return Checker__check_array_access_expression(self, (Parsed_Array_Access_Expression *)parsed_expression);
    case PARSED_EXPRESSION_KIND__BOOL:
        return Checker__check_bool_expression(self, (Parsed_Bool_Expression *)parsed_expression);
    case PARSED_EXPRESSION_KIND__CALL:
        return Checker__check_call_expression(self, (Parsed_Call_Expression *)parsed_expression);
    case PARSED_EXPRESSION_KIND__CAST:
        return Checker__check_cast_expression(self, (Parsed_Cast_Expression *)parsed_expression);
    case PARSED_EXPRESSION_KIND__CHARACTER:
        return Checker__check_character_expression(self, (Parsed_Character_Expression *)parsed_expression);
    case PARSED_EXPRESSION_KIND__DEREFERENCE:
        return Checker__check_dereference_expression(self, (Parsed_Dereference_Expression *)parsed_expression);
    case PARSED_EXPRESSION_KIND__DIVIDE:
        return Checker__check_divide_expression(self, (Parsed_Divide_Expression *)parsed_expression, expected_type);
    case PARSED_EXPRESSION_KIND__EQUALS:
        return Checker__check_equals_expression(self, (Parsed_Equals_Expression *)parsed_expression, expected_type);
    case PARSED_EXPRESSION_KIND__GREATER:
        return Checker__check_greater_expression(self, (Parsed_Greater_Expression *)parsed_expression, expected_type);
    case PARSED_EXPRESSION_KIND__GREATER_OR_EQUALS:
        return Checker__check_greater_or_equals_expression(self, (Parsed_Greater_Or_Equals_Expression *)parsed_expression, expected_type);
    case PARSED_EXPRESSION_KIND__GROUP:
        return Checker__check_group_expression(self, (Parsed_Group_Expression *)parsed_expression, expected_type);
    case PARSED_EXPRESSION_KIND__INTEGER:
        return Checker__check_integer_expression(self, (Parsed_Integer_Expression *)parsed_expression, expected_type);
    case PARSED_EXPRESSION_KIND__LESS:
        return Checker__check_less_expression(self, (Parsed_Less_Expression *)parsed_expression, expected_type);
    case PARSED_EXPRESSION_KIND__LESS_OR_EQUALS:
        return Checker__check_less_or_equals_expression(self, (Parsed_Less_Or_Equals_Expression *)parsed_expression, expected_type);
    case PARSED_EXPRESSION_KIND__LOGIC_AND:
        return Checker__check_logic_and_expression(self, (Parsed_Logic_And_Expression *)parsed_expression);
    case PARSED_EXPRESSION_KIND__LOGIC_OR:
        return Checker__check_logic_or_expression(self, (Parsed_Logic_Or_Expression *)parsed_expression);
    case PARSED_EXPRESSION_KIND__MAKE:
        return Checker__check_make_expression(self, (Parsed_Make_Expression *)parsed_expression);
    case PARSED_EXPRESSION_KIND__MEMBER_ACCESS:
        return Checker__check_member_access_expression(self, (Parsed_Member_Access_Expression *)parsed_expression);
    case PARSED_EXPRESSION_KIND__MINUS:
        return Checker__check_minus_expression(self, (Parsed_Minus_Expression *)parsed_expression, expected_type);
    case PARSED_EXPRESSION_KIND__MODULO:
        return Checker__check_modulo_expression(self, (Parsed_Modulo_Expression *)parsed_expression, expected_type);
    case PARSED_EXPRESSION_KIND__MULTIPLY:
        return Checker__check_multiply_expression(self, (Parsed_Multiply_Expression *)parsed_expression, expected_type);
    case PARSED_EXPRESSION_KIND__NOT:
        return Checker__check_not_expression(self, (Parsed_Not_Expression *)parsed_expression);
    case PARSED_EXPRESSION_KIND__NOT_EQUALS:
        return Checker__check_not_equals_expression(self, (Parsed_Not_Equals_Expression *)parsed_expression);
    case PARSED_EXPRESSION_KIND__NULL:
        return Checker__check_null_expression(self, (Parsed_Null_Expression *)parsed_expression);
    case PARSED_EXPRESSION_KIND__SIZEOF:
        return Checker__check_sizeof_expression(self, (Parsed_Sizeof_Expression *)parsed_expression);
    case PARSED_EXPRESSION_KIND__STRING:
        return Checker__check_string_expression(self, (Parsed_String_Expression *)parsed_expression);
    case PARSED_EXPRESSION_KIND__SUBSTRACT:
        return Checker__check_substract_expression(self, (Parsed_Substract_Expression *)parsed_expression, expected_type);
    case PARSED_EXPRESSION_KIND__SYMBOL:
        return Checker__check_symbol_expression(self, (Parsed_Symbol_Expression *)parsed_expression, expected_type);
    }
    pWriter__begin_location_message(stderr_writer, parsed_expression->location, WRITER_STYLE__ERROR);
    pWriter__write__cstring(stderr_writer, "Unsupported expression kind");
    pWriter__end_location_message(stderr_writer);
    panic();
}

void Checker__check_external_type_statement(Checker *self, Parsed_External_Type_Statement *parsed_statement) {
    Checked_Named_Type *type = Checker__find_type(self, parsed_statement->super.name->lexeme);
    if (type != NULL) {
        pWriter__write__todo(stderr_writer, __FILE__, __LINE__, "Report type redeclaration");
        panic();
    }
    Checked_External_Type *external_type = Checked_External_Type__create(parsed_statement->super.name->location, parsed_statement->super.name->lexeme);
    Checker__append_type(self, (Checked_Named_Type *)external_type);
}

void Checker__check_struct_statement(Checker *self, Parsed_Struct_Statement *parsed_statement) {
    Checked_Named_Type *other_type = Checker__find_type(self, parsed_statement->super.name->lexeme);
    Checked_Struct_Type *struct_type;
    if (other_type != NULL) {
        if (other_type->super.kind != CHECKED_TYPE_KIND__STRUCT || (((Checked_Struct_Type *)other_type)->first_member != NULL)) {
            pWriter__write__todo(stderr_writer, __FILE__, __LINE__, "Report type redeclaration");
            panic();
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
                panic();
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
    Checked_Expression *object_expression = Checker__check_expression(self, parsed_statement->object_expression, NULL);
    Checked_Expression *value_expression = Checker__check_expression(self, parsed_statement->value_expression, object_expression->type);
    Checker__require_same_type(self, object_expression->type, value_expression->type, value_expression->location);
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
    Checked_Expression *expression = Checker__check_expression(self, parsed_statement->expression, NULL);
    if (!Checked_Type__equals((Checked_Type *)Checker__get_builtin_type(self, CHECKED_TYPE_KIND__NOTHING), expression->type)) {
        /* TODO: Source_Location__warning(expression->location, String__create_from("Unused result value")); */
    }
    return Checked_Expression_Statement__create(parsed_statement->super.location, expression);
}

Checked_If_Statement *Checker__check_if_statement(Checker *self, Parsed_If_Statement *parsed_statement) {
    Checked_Expression *considition_expression = Checker__check_expression(self, parsed_statement->condition_expression, (Checked_Type *)Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL));
    Checker__require_same_type(self, (Checked_Type *)Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL), considition_expression->type, considition_expression->location);
    Checked_Statement *true_statement = Checker__check_statement(self, parsed_statement->true_statement);
    Checked_Statement *false_statement = NULL;
    if (parsed_statement->false_statement != NULL) {
        false_statement = Checker__check_statement(self, parsed_statement->false_statement);
    }
    return Checked_If_Statement__create(parsed_statement->super.location, considition_expression, true_statement, false_statement);
}

Checked_Loop_Statement *Checker__check_loop_statement(Checker *self, Parsed_Loop_Statement *parsed_statement) {
    Checked_Statement *body_statement = Checker__check_statement(self, parsed_statement->body_statement);
    return Checked_Loop_Statement__create(parsed_statement->super.location, body_statement);
}

Checked_Return_Statement *Checker__check_return_statement(Checker *self, Parsed_Return_Statement *parsed_statement) {
    Checked_Expression *expression = NULL;
    if (parsed_statement->expression != NULL) {
        expression = Checker__check_expression(self, parsed_statement->expression, self->return_type);
        Checker__require_same_type(self, self->return_type, expression->type, expression->location);
    } else if (self->return_type->kind != CHECKED_TYPE_KIND__NOTHING) {
        pWriter__begin_location_message(stderr_writer, parsed_statement->super.location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Missing expression");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    return Checked_Return_Statement__create(parsed_statement->super.location, expression);
}

Checked_Variable_Statement *Checker__check_variable_statement(Checker *self, Parsed_Variable_Statement *parsed_statement) {
    Checked_Type *type = NULL;
    if (parsed_statement->type != NULL) {
        type = Checker__resolve_type(self, parsed_statement->type);
    } else if (parsed_statement->expression == NULL) {
        pWriter__begin_location_message(stderr_writer, parsed_statement->super.super.location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Missing type");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    Checked_Expression *expression = NULL;
    if (parsed_statement->expression != NULL) {
        expression = Checker__check_expression(self, parsed_statement->expression, type);
        if (type == NULL) {
            type = expression->type;
        } else {
            Checker__require_same_type(self, type, expression->type, expression->location);
        }
    }
    Checked_Variable_Symbol *variable = Checked_Variable_Symbol__create(parsed_statement->super.name->location, parsed_statement->super.name->lexeme, type);
    Checked_Symbols__append_symbol(self->symbols, (Checked_Symbol *)variable);
    return Checked_Variable_Statement__create(parsed_statement->super.super.location, variable, expression, parsed_statement->is_external);
}

Checked_While_Statement *Checker__check_while_statement(Checker *self, Parsed_While_Statement *parsed_statement) {
    Checked_Expression *considition_expression = Checker__check_expression(self, parsed_statement->condition_expression, (Checked_Type *)Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL));
    Checker__require_same_type(self, (Checked_Type *)Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL), considition_expression->type, considition_expression->location);
    Checked_Statement *body_statement = Checker__check_statement(self, parsed_statement->body_statement);
    return Checked_While_Statement__create(parsed_statement->super.location, considition_expression, body_statement);
}

static void String__append_receiver_type(String *symbol_name, Checked_Type *receiver_type) {
    switch (receiver_type->kind) {
    case CHECKED_TYPE_KIND__ARRAY: {
        Checked_Array_Type *array_type = (Checked_Array_Type *)receiver_type;
        if (array_type->is_checked) {
            panic();
        }
        String__append_cstring(symbol_name, "d_");
        String__append_receiver_type(symbol_name, array_type->item_type);
        String__append_cstring(symbol_name, "_b");
        break;
    }
    case CHECKED_TYPE_KIND__POINTER: {
        String__append_char(symbol_name, 'p');
        String__append_receiver_type(symbol_name, ((Checked_Pointer_Type *)receiver_type)->other_type);
        break;
    }
    case CHECKED_TYPE_KIND__I32:
    case CHECKED_TYPE_KIND__EXTERNAL:
    case CHECKED_TYPE_KIND__STRUCT:
    case CHECKED_TYPE_KIND__U8: {
        String__append_string(symbol_name, ((Checked_Named_Type *)receiver_type)->name);
        break;
    }
    default:
        panic();
    }
}

void Checker__check_function_declaration(Checker *self, Parsed_Function_Statement *parsed_statement) {
    Checked_Type *function_return_type;
    if (parsed_statement->return_type != NULL) {
        function_return_type = Checker__resolve_type(self, parsed_statement->return_type);
    } else {
        function_return_type = (Checked_Type *)Checker__get_builtin_type(self, CHECKED_TYPE_KIND__NOTHING);
    }
    Checked_Function_Parameter *function_first_parameter = NULL;
    Parsed_Function_Parameter *parsed_parameter = parsed_statement->first_parameter;
    if (parsed_parameter != NULL) {
        function_first_parameter = Checked_Function_Parameter__create(parsed_parameter->name->location, parsed_parameter->label ? parsed_parameter->label->lexeme : NULL, parsed_parameter->name->lexeme, Checker__resolve_type(self, parsed_parameter->type));
        Checked_Function_Parameter *function_last_parameter = function_first_parameter;
        parsed_parameter = parsed_parameter->next_parameter;
        while (parsed_parameter != NULL) {
            Checked_Function_Parameter *function_parameter = Checked_Function_Parameter__create(parsed_parameter->name->location, parsed_parameter->label ? parsed_parameter->label->lexeme : NULL, parsed_parameter->name->lexeme, Checker__resolve_type(self, parsed_parameter->type));
            function_last_parameter->next_parameter = function_parameter;
            function_last_parameter = function_parameter;
            parsed_parameter = parsed_parameter->next_parameter;
        }
    }
    Checked_Function_Type *function_type = Checked_Function_Type__create(parsed_statement->super.super.location, function_first_parameter, function_return_type);

    String *function_name = parsed_statement->super.name->lexeme;

    String *symbol_name = String__create();
    Checked_Type *receiver_type = NULL;
    if (parsed_statement->receiver_type != NULL) {
        receiver_type = Checker__resolve_type(self, parsed_statement->receiver_type);
        String__append_receiver_type(symbol_name, receiver_type);
        String__append_cstring(symbol_name, "__");
    }
    String__append_string(symbol_name, function_name);
    Checked_Function_Parameter *function_parameter = function_first_parameter;
    int function_parameter_index = 0;
    while (function_parameter != NULL) {
        if (function_parameter->label != NULL) {
            String__append_cstring(symbol_name, "__");
            String__append_int16_t(symbol_name, function_parameter_index);
            String__append_cstring(symbol_name, "_");
            String__append_string(symbol_name, function_parameter->label);
        }
        function_parameter = function_parameter->next_parameter;
        function_parameter_index++;
    }

    Checked_Symbols__append_symbol(self->symbols, (Checked_Symbol *)Checked_Function_Symbol__create(parsed_statement->super.name->location, symbol_name, function_name, function_type, receiver_type));
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
    } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__LOOP) {
        return (Checked_Statement *)Checker__check_loop_statement(self, (Parsed_Loop_Statement *)parsed_statement);
    } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__RETURN) {
        return (Checked_Statement *)Checker__check_return_statement(self, (Parsed_Return_Statement *)parsed_statement);
    } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__VARIABLE) {
        return (Checked_Statement *)Checker__check_variable_statement(self, (Parsed_Variable_Statement *)parsed_statement);
    } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__WHILE) {
        return (Checked_Statement *)Checker__check_while_statement(self, (Parsed_While_Statement *)parsed_statement);
    }
    pWriter__begin_location_message(stderr_writer, parsed_statement->location, WRITER_STYLE__ERROR);
    pWriter__write__cstring(stderr_writer, "Unsupported statement kind");
    pWriter__end_location_message(stderr_writer);
    panic();
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
    Checked_Symbol *symbol = self->symbols->first_symbol;
    while (symbol != NULL) {
        if (symbol->kind == CHECKED_SYMBOL_KIND__FUNCTION) {
            Checked_Function_Symbol *function_symbol = (Checked_Function_Symbol *)symbol;
            if (function_symbol->function_name == parsed_statement->super.name->lexeme) {
                break;
            }
        }
        symbol = symbol->next_symbol;
    }
    if (symbol == NULL) {
        // Function symbol should exist
        panic();
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
        } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__EXTERNAL_TYPE) {
            Checker__check_external_type_statement(self, (Parsed_External_Type_Statement *)parsed_statement);
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
            Parsed_Struct_Statement *parsed_struct_statement = (Parsed_Struct_Statement *)parsed_statement;
            Parsed_Struct_Method *parsed_struct_method = parsed_struct_statement->first_method;
            while (parsed_struct_method != NULL) {
                Checker__check_function_declaration(self, parsed_struct_method->function_statement);
                parsed_struct_method = parsed_struct_method->next_method;
            }
        } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__EXTERNAL_TYPE) {
            /* ignored */
        } else {
            pWriter__begin_location_message(stderr_writer, parsed_statement->location, WRITER_STYLE__ERROR);
            pWriter__write__cstring(stderr_writer, "Unsupported statement");
            pWriter__end_location_message(stderr_writer);
            panic();
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
            Parsed_Struct_Statement *parsed_struct_statement = (Parsed_Struct_Statement *)parsed_statement;
            Parsed_Struct_Method *parsed_struct_method = parsed_struct_statement->first_method;
            while (parsed_struct_method != NULL) {
                Checker__check_function_definition(self, parsed_struct_method->function_statement);
                parsed_struct_method = parsed_struct_method->next_method;
            }

        } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__EXTERNAL_TYPE) {
            /* ignored */
        } else {
            pWriter__begin_location_message(stderr_writer, parsed_statement->location, WRITER_STYLE__ERROR);
            pWriter__write__cstring(stderr_writer, "Unsupported statement");
            pWriter__end_location_message(stderr_writer);
            panic();
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
