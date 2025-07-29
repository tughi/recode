#include "Checker.h"
#include "File.h"

typedef struct Builtin_Types {
    Checked_Symbols *symbols;

    Checked_Named_Type *any_type;
    Checked_Named_Type *bool_type;
    Checked_Named_Type *i16_type;
    Checked_Named_Type *i32_type;
    Checked_Named_Type *i64_type;
    Checked_Named_Type *i8_type;
    Checked_Named_Type *isize_type;
    Checked_Named_Type *module_type;
    Checked_Named_Type *nil_type;
    Checked_Named_Type *nothing_type;
    Checked_Named_Type *null_type;
    Checked_Named_Type *str_type;
    Checked_Named_Type *type_type;
    Checked_Named_Type *u16_type;
    Checked_Named_Type *u32_type;
    Checked_Named_Type *u64_type;
    Checked_Named_Type *u8_type;
    Checked_Named_Type *usize_type;
} Builtin_Types;

Builtin_Types *Builtin_Types__create() {
    Builtin_Types *builtin_types = (Builtin_Types *)malloc(sizeof(Builtin_Types));
    builtin_types->symbols = Checked_Symbols__create(NULL);

    Source_Location location = {};

    builtin_types->type_type = Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__TYPE, sizeof(Checked_Named_Type), location, String__create_from("Type"), NULL);
    Checked_Symbols__append_symbol(builtin_types->symbols, (Checked_Symbol *)Checked_Type_Symbol__create(NULL, builtin_types->type_type->super.location, builtin_types->type_type->name, (Checked_Type *)builtin_types->type_type, builtin_types->type_type));

    builtin_types->any_type = NULL;

    builtin_types->bool_type = NULL;

    builtin_types->i16_type = NULL;
    builtin_types->i32_type = NULL;
    builtin_types->i64_type = NULL;
    builtin_types->i8_type = NULL;
    builtin_types->isize_type = NULL;

    builtin_types->module_type = Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__MODULE, sizeof(Checked_Named_Type), location, String__create_from("Module"), NULL);
    Checked_Symbols__append_symbol(builtin_types->symbols, (Checked_Symbol *)Checked_Type_Symbol__create(NULL, builtin_types->module_type->super.location, builtin_types->module_type->name, (Checked_Type *)builtin_types->type_type, builtin_types->module_type));

    builtin_types->nil_type = Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__NIL, sizeof(Checked_Named_Type), location, String__create_from("nil"), NULL);
    Checked_Symbols__append_symbol(builtin_types->symbols, (Checked_Symbol *)Checked_Type_Symbol__create(NULL, builtin_types->nil_type->super.location, builtin_types->nil_type->name, (Checked_Type *)builtin_types->type_type, builtin_types->nil_type));

    builtin_types->nothing_type = Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__NOTHING, sizeof(Checked_Named_Type), location, String__create_from("Nothing"), NULL);
    Checked_Symbols__append_symbol(builtin_types->symbols, (Checked_Symbol *)Checked_Type_Symbol__create(NULL, builtin_types->nothing_type->super.location, builtin_types->nothing_type->name, (Checked_Type *)builtin_types->type_type, builtin_types->nothing_type));

    builtin_types->null_type = Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__NULL, sizeof(Checked_Named_Type), location, String__create_from("Null"), NULL);
    Checked_Symbols__append_symbol(builtin_types->symbols, (Checked_Symbol *)Checked_Type_Symbol__create(NULL, builtin_types->null_type->super.location, builtin_types->null_type->name, (Checked_Type *)builtin_types->type_type, builtin_types->null_type));

    builtin_types->str_type = NULL;

    builtin_types->u16_type = NULL;
    builtin_types->u32_type = NULL;
    builtin_types->u64_type = NULL;
    builtin_types->u8_type = NULL;
    builtin_types->usize_type = NULL;

    return builtin_types;
}

typedef struct Checked_Method {
    Checked_Type *receiver_type;
    Checked_Symbol *procedure_symbol;
    struct Checked_Method *next_method;
} Checked_Method;

typedef struct Checked_Methods {
    Checked_Method *first_method;
    Checked_Method *last_method;
} Checked_Methods;

typedef struct Checker {
    Parsed_Source *parsed_source;

    Builtin_Types *builtin_types;

    Checked_Symbols *global_symbols;
    Checked_Symbols *symbols;

    Checked_Modules *modules;
    Checked_Module *checked_module;

    Checked_Methods *methods;

    Checked_Type *receiver_type;
    Checked_Type *return_type;
} Checker;

Checker *Checker__create(Parsed_Source *parsed_source) {
    Checker *checker = (Checker *)malloc(sizeof(Checker));

    checker->parsed_source = parsed_source;

    checker->builtin_types = Builtin_Types__create();

    checker->global_symbols = checker->symbols = Checked_Symbols__create(checker->builtin_types->symbols);

    checker->modules = (Checked_Modules *)malloc(sizeof(Checked_Modules));
    checker->modules->builtin_module = NULL;
    checker->modules->first_module = NULL;
    checker->modules->last_module = NULL;

    checker->checked_module = Checked_Module__create(parsed_source->package_name, parsed_source->source);
    Checked_Modules__append(checker->modules, checker->checked_module);

    checker->methods = (Checked_Methods *)malloc(sizeof(Checked_Methods));
    checker->methods->first_method = NULL;
    checker->methods->last_method = NULL;

    checker->receiver_type = NULL;
    checker->return_type = NULL;

    return checker;
}

Checked_Type_Symbol *Checker__create_type_symbol(Checker *self, String *symbol_name, Checked_Named_Type *type) {
    Checked_Type_Symbol *type_symbol = Checked_Type_Symbol__create(self->checked_module, type->super.location, symbol_name, (Checked_Type *)self->builtin_types->type_type, type);
    Checked_Symbols__append_symbol(self->global_symbols, (Checked_Symbol *)type_symbol);
    return type_symbol;
}

Checked_Named_Type *Checked_Symbols__find_type(Checked_Symbols *symbols, Checked_Module *module, String *name) {
    while (symbols != NULL) {
        Checked_Symbol *symbol = symbols->last_symbol;
        while (symbol != NULL) {
            if (symbol->kind == CHECKED_SYMBOL_KIND__TYPE && String__equals_string(name, symbol->name)) {
                if (module == NULL || symbol->module == NULL || module == symbol->module) {
                    return ((Checked_Type_Symbol *)symbol)->named_type;
                }
            }
            symbol = symbol->prev_symbol;
        }
        symbols = symbols->parent;
    }
    return NULL;
}

Checked_Named_Type *Checker__find_type(Checker *self, String *name) {
    Checked_Named_Type *type = Checked_Symbols__find_type(self->symbols, self->checked_module, name);
    if (type != NULL) {
        return type;
    }
    return Checked_Symbols__find_type(self->global_symbols->parent, NULL, name);
}

Checked_Type_Argument_Symbol *Checker__find_type_argument_symbol(Checker *self, String *alias) {
    Checked_Symbols *symbols = self->symbols;
    while (symbols != NULL) {
        Checked_Symbol *symbol = symbols->last_symbol;
        while (symbol != NULL) {
            if (symbol->kind == CHECKED_SYMBOL_KIND__TYPE_ARGUMENT && String__equals_string(alias, symbol->name)) {
                return (Checked_Type_Argument_Symbol *)symbol;
            }
            symbol = symbol->prev_symbol;
        }
        symbols = symbols->parent;
    }
    return NULL;
}

void Checker__append_method(Checker *self, Checked_Type *receiver_type, Checked_Symbol *procedure_symbol) {
    if (procedure_symbol->kind != CHECKED_SYMBOL_KIND__PROCEDURE && procedure_symbol->kind != CHECKED_SYMBOL_KIND__GENERIC_PROCEDURE) {
        panic();
    }

    Checked_Method *method = self->methods->first_method;
    while (method != NULL) {
        if (Checked_Type__equals(method->receiver_type, receiver_type) && String__equals_string(method->procedure_symbol->name, procedure_symbol->name)) {
            pWriter__begin_location_message(stderr_writer, procedure_symbol->location, WRITER_STYLE__ERROR);
            pWriter__write__cstring(stderr_writer, "Method already defined here: ");
            pWriter__write__location(stderr_writer, method->procedure_symbol->location);
            pWriter__end_location_message(stderr_writer);
            panic();
        }
        method = method->next_method;
    }

    method = (Checked_Method *)malloc(sizeof(Checked_Method));
    method->receiver_type = receiver_type;
    method->procedure_symbol = procedure_symbol;
    method->next_method = NULL;

    if (self->methods->first_method == NULL) {
        self->methods->first_method = method;
    } else {
        self->methods->last_method->next_method = method;
    }
    self->methods->last_method = method;
}

Checked_Expression *Checker__check_expression(Checker *self, Parsed_Expression *parsed_expression, Checked_Type *expected_type);

Checked_Named_Type *Checker__check_type_statement(Checker *self, Parsed_Type_Statement *parsed_type_statement);

Checked_Named_Type *Checker__specialize_type(Checker *self, Checked_Generic_Type *generic_type, Parsed_Named_Type *parsed_type);

Checked_Type *Checker__resolve_type(Checker *self, Parsed_Type *parsed_type) {
    switch (parsed_type->kind) {
    case PARSED_TYPE_KIND__ARRAY: {
        Parsed_Array_Type *parsed_array_type = (Parsed_Array_Type *)parsed_type;
        Checked_Type *checked_item_type = Checker__resolve_type(self, parsed_array_type->item_type);
        Checked_Expression *checked_size_expression = NULL;
        if (parsed_array_type->size_expression != NULL) {
            checked_size_expression = Checker__check_expression(self, parsed_array_type->size_expression, (Checked_Type *)self->builtin_types->isize_type);
        }
        return (Checked_Type *)Checked_Array_Type__create(parsed_type->location, checked_item_type, checked_size_expression);
    }
    case PARSED_TYPE_KIND__PROCEDURE: {
        Parsed_Procedure_Type *parsed_procedure_type = (Parsed_Procedure_Type *)parsed_type;
        Checked_Procedure_Parameter *procedure_first_parameter = NULL;
        Parsed_Procedure_Parameter *parsed_parameter = parsed_procedure_type->first_parameter;
        if (parsed_parameter != NULL) {
            procedure_first_parameter = Checked_Procedure_Parameter__create(parsed_parameter->name->location, parsed_parameter->label ? parsed_parameter->label->lexeme : NULL, parsed_parameter->name->lexeme, Checker__resolve_type(self, parsed_parameter->type));
            Checked_Procedure_Parameter *procedure_last_parameter = procedure_first_parameter;
            parsed_parameter = parsed_parameter->next_parameter;
            while (parsed_parameter != NULL) {
                Checked_Procedure_Parameter *procedure_parameter = Checked_Procedure_Parameter__create(parsed_parameter->name->location, parsed_parameter->label ? parsed_parameter->label->lexeme : NULL, parsed_parameter->name->lexeme, Checker__resolve_type(self, parsed_parameter->type));
                procedure_last_parameter->next_parameter = procedure_parameter;
                procedure_last_parameter = procedure_parameter;
                parsed_parameter = parsed_parameter->next_parameter;
            }
        }
        Checked_Type *procedure_return_type;
        if (parsed_procedure_type->return_type == NULL) {
            procedure_return_type = (Checked_Type *)self->builtin_types->nothing_type;
        } else {
            procedure_return_type = Checker__resolve_type(self, parsed_procedure_type->return_type);
        }
        Checked_Procedure_Type *procedure_type = Checked_Procedure_Type__create(parsed_procedure_type->super.location, procedure_first_parameter, procedure_return_type);
        return (Checked_Type *)Checked_Procedure_Pointer_Type__create(parsed_type->location, procedure_type);
    }
    case PARSED_TYPE_KIND__MULTI_POINTER:
        return (Checked_Type *)Checked_Multi_Pointer_Type__create(parsed_type->location, Checker__resolve_type(self, ((Parsed_Multi_Pointer_Type *)parsed_type)->item_type));
    case PARSED_TYPE_KIND__NAMED: {
        Parsed_Named_Type *parsed_named_type = (Parsed_Named_Type *)parsed_type;
        if (parsed_named_type->module != NULL) {
            Checked_Symbol *symbol = Checked_Symbols__find_symbol(self->global_symbols, self->checked_module, parsed_named_type->module->lexeme);
            if (symbol == NULL) {
                pWriter__begin_location_message(stderr_writer, parsed_named_type->module->location, WRITER_STYLE__ERROR);
                pWriter__write__cstring(stderr_writer, "Undefined module");
                pWriter__end_location_message(stderr_writer);
                panic();
            }
            if (symbol->kind != CHECKED_SYMBOL_KIND__IMPORT) {
                pWriter__begin_location_message(stderr_writer, parsed_named_type->module->location, WRITER_STYLE__ERROR);
                pWriter__write__cstring(stderr_writer, "Not a module");
                pWriter__end_location_message(stderr_writer);
                panic();
            }
            Checked_Import_Symbol *import_symbol = (Checked_Import_Symbol *)symbol;
            Checked_Module *other_module = import_symbol->other_module;
            Checked_Named_Type *type = Checked_Symbols__find_type(self->global_symbols, other_module, parsed_named_type->name);
            if (type == NULL) {
                pWriter__begin_location_message(stderr_writer, parsed_named_type->super.location, WRITER_STYLE__ERROR);
                pWriter__write__cstring(stderr_writer, "Undefined type");
                pWriter__end_location_message(stderr_writer);
                panic();
            }
            if (type->super.kind == CHECKED_TYPE_KIND__GENERIC && parsed_named_type->first_type_argument != NULL) {
                return (Checked_Type *)Checker__specialize_type(self, (Checked_Generic_Type *)type, parsed_named_type);
            }
            return (Checked_Type *)type;
        }
        Checked_Named_Type *type = Checker__find_type(self, parsed_named_type->name);
        if (type != NULL) {
            if (type->super.kind == CHECKED_TYPE_KIND__GENERIC) {
                if (parsed_named_type->first_type_argument != NULL) {
                    return (Checked_Type *)Checker__specialize_type(self, (Checked_Generic_Type *)type, parsed_named_type);
                }
            } else if (parsed_named_type->first_type_argument != NULL) {
                pWriter__begin_location_message(stderr_writer, parsed_named_type->super.location, WRITER_STYLE__ERROR);
                pWriter__write__checked_type(stderr_writer, (Checked_Type *)type);
                pWriter__write__cstring(stderr_writer, " is not a generic type");
                pWriter__end_location_message(stderr_writer);
                panic();
            }
            return (Checked_Type *)type;
        }
        Parsed_Statement *parsed_statement = self->parsed_source->statements->first_statement;
        for (; parsed_statement != NULL; parsed_statement = parsed_statement->next_statement) {
            if (parsed_statement->kind == PARSED_STATEMENT_KIND__TYPE) {
                Parsed_Type_Statement *parsed_type_statement = (Parsed_Type_Statement *)parsed_statement;
                if (String__equals_string(parsed_type_statement->super.name->lexeme, parsed_named_type->name)) {
                    return (Checked_Type *)Checker__check_type_statement(self, parsed_type_statement);
                }
            }
        }
        Checked_Type_Argument_Symbol *type_argument_symbol = Checker__find_type_argument_symbol(self, parsed_named_type->name);
        if (type_argument_symbol != NULL) {
            return type_argument_symbol->argument_type;
        }
        pWriter__begin_location_message(stderr_writer, parsed_type->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Undefined type: ");
        pWriter__write__string(stderr_writer, parsed_named_type->name);
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    case PARSED_TYPE_KIND__POINTER:
        return (Checked_Type *)Checked_Pointer_Type__create(parsed_type->location, Checker__resolve_type(self, ((Parsed_Pointer_Type *)parsed_type)->other_type));
    case PARSED_TYPE_KIND__RECEIVER:
        return self->receiver_type;
    }
    todo("Handle unexpected Parsed_Type_Kind");
}

void Checker__require_numeric_type(Checker *self, Checked_Type *type, Source_Location location) {
    if (!Checked_Type__is_numeric_type(type)) {
        pWriter__begin_location_message(stderr_writer, location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Expected numeric type");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
}

void Checker__require_same_type(Checker *self, Checked_Type *expected_type, Checked_Type *actual_type, Source_Location location) {
    if (expected_type->kind == CHECKED_TYPE_KIND__MULTI_POINTER && actual_type->kind == CHECKED_TYPE_KIND__NULL) {
        return;
    }
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

/**
 * Checks if `self` is a specialization of the another type.
 */
Checked_Type_Argument *Checked_Type__is_specialization(Checked_Type *self, Checked_Type *other_type) {
    switch (self->kind) {
    case CHECKED_TYPE_KIND__POINTER:
        if (other_type->kind != CHECKED_TYPE_KIND__POINTER) {
            return NULL;
        }
        return Checked_Type__is_specialization(((Checked_Pointer_Type *)self)->other_type, ((Checked_Pointer_Type *)other_type)->other_type);
    case CHECKED_TYPE_KIND__STRUCT: {
        if (other_type->kind == CHECKED_TYPE_KIND__GENERIC) {
            Checked_Struct_Type *struct_type = (Checked_Struct_Type *)self;
            if ((Checked_Type *)struct_type->super.generic_type == other_type) {
                if (other_type->kind != CHECKED_TYPE_KIND__GENERIC) {
                    panic();
                }
                Checked_Generic_Type *generic_type = (Checked_Generic_Type *)other_type;
                return struct_type->super.first_type_argument;
            }
        }
        return NULL;
    }
    default:
        todo("Handle other types for specialization check");
        break;
    }
    todo("Check if type is specialization");
}

Checked_Procedure_Symbol *Checker__specialize_method(Checker *self, Checked_Generic_Procedure_Symbol *generic_procedure_symbol, Checked_Type_Argument *first_type_argument);

Checked_Procedure_Symbol *Checker__resolve_method_symbol(Checker *self, Checked_Type *receiver_type, String *procedure_name) {
    Checked_Method *method = self->methods->first_method;
    while (method != NULL) {
        switch (method->procedure_symbol->kind) {
        case CHECKED_SYMBOL_KIND__GENERIC_PROCEDURE: {
            Checked_Generic_Procedure_Symbol *generic_procedure_symbol = (Checked_Generic_Procedure_Symbol *)method->procedure_symbol;
            if (String__equals_string(generic_procedure_symbol->parsed_procedure_statement->super.name->lexeme, procedure_name)) {
                Checked_Type_Argument *first_type_argument = Checked_Type__is_specialization(receiver_type, generic_procedure_symbol->receiver_type);
                if (first_type_argument != NULL) {
                    return Checker__specialize_method(self, generic_procedure_symbol, first_type_argument);
                }
            }
            break;
        }
        case CHECKED_SYMBOL_KIND__PROCEDURE: {
            Checked_Procedure_Symbol *procedure_symbol = (Checked_Procedure_Symbol *)method->procedure_symbol;
            if (String__equals_string(procedure_symbol->procedure_name, procedure_name) && Checked_Type__equals(method->receiver_type, receiver_type)) {
                return procedure_symbol;
            }
            break;
        }
        default:
            panic();
        }
        method = method->next_method;
    }
    return NULL;
}

Checked_Procedure_Symbol *Checker__resolve_reference_method_symbol(Checker *self, Checked_Type *receiver_type, String *procedure_name) {
    Checked_Pointer_Type pointer_type = {
        .super = {
            .kind = CHECKED_TYPE_KIND__POINTER,
        },
        .other_type = receiver_type,
    };
    return Checker__resolve_method_symbol(self, (Checked_Type *)&pointer_type, procedure_name);
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
    if (!Checked_Expression__is_mutable(other_expression)) {
        pWriter__begin_location_message(stderr_writer, other_expression->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Cannot take address of this expression");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    return (Checked_Expression *)Checked_Address_Of_Expression__create(parsed_expression->super.super.location, (Checked_Type *)Checked_Pointer_Type__create(other_expression->location, other_expression->type), other_expression);
}

Checked_Expression *Checker__check_alloc_expression(Checker *self, Parsed_Alloc_Expression *parsed_expression) {
    Checked_Expression *value_expression = Checker__check_expression(self, parsed_expression->value_expression, NULL);
    Checked_Type *value_type = value_expression->type;
    switch (value_type->kind) {
    case CHECKED_TYPE_KIND__STRUCT:
    case CHECKED_TYPE_KIND__TRAIT:
    case CHECKED_TYPE_KIND__UNION:
        return (Checked_Expression *)Checked_Alloc_Expression__create(parsed_expression->super.location, (Checked_Type *)Checked_Pointer_Type__create(parsed_expression->super.location, value_type), value_expression);
    default:
        break;
    }
    pWriter__begin_location_message(stderr_writer, parsed_expression->value_expression->location, WRITER_STYLE__ERROR);
    pWriter__write__cstring(stderr_writer, "Cannot allocate ");
    pWriter__write__checked_type(stderr_writer, value_type);
    pWriter__write__cstring(stderr_writer, " value");
    pWriter__end_location_message(stderr_writer);
    panic();
}

Checked_Expression *Checker__check_array_access_expression(Checker *self, Parsed_Array_Access_Expression *parsed_expression) {
    Checked_Expression *array_expression = Checker__check_expression(self, parsed_expression->array_expression, NULL);
    Checked_Type *array_type = array_expression->type;
    if (array_type->kind != CHECKED_TYPE_KIND__MULTI_POINTER) {
        pWriter__begin_location_message(stderr_writer, parsed_expression->array_expression->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Not an array");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    Checked_Type *type = ((Checked_Pointer_Type *)array_type)->other_type;
    Checked_Expression *index_expression = Checker__check_expression(self, parsed_expression->index_expression, NULL);
    Checker__require_numeric_type(self, index_expression->type, index_expression->location);
    return (Checked_Expression *)Checked_Array_Access_Expression__create(parsed_expression->super.location, type, array_expression, index_expression);
}

Checked_Expression *Checker__check_bool_expression(Checker *self, Parsed_Bool_Expression *parsed_expression) {
    Checked_Type *expression_type = (Checked_Type *)self->builtin_types->bool_type;
    bool value = parsed_expression->value;
    return (Checked_Expression *)Checked_Bool_Expression__create(parsed_expression->super.super.location, expression_type, value);
}

Checked_Make_Union_Expression *Checker__make_union_expression(Checker *self, Source_Location location, Checked_Union_Type *union_type, Checked_Expression *expression) {
    Checked_Union_Variant *union_variant = union_type->first_variant;
    if (expression->kind == CHECKED_EXPRESSION_KIND__SYMBOL) {
        Checked_Symbol *symbol = ((Checked_Symbol_Expression *)expression)->symbol;
        if (symbol->kind == CHECKED_SYMBOL_KIND__TYPE) {
            Checked_Type_Symbol *type_symbol = (Checked_Type_Symbol *)symbol;
            if (type_symbol->named_type == self->builtin_types->nil_type) {
                return Checked_Make_Union_Expression__create(location, (Checked_Type *)union_type, union_type, union_variant, (Checked_Expression *)expression);
            }
        }
    }
    for (; union_variant != NULL; union_variant = union_variant->next_variant) {
        if (Checked_Type__equals(union_variant->type, expression->type)) {
            break;
        }
    }
    if (union_variant == NULL) {
        pWriter__begin_location_message(stderr_writer, expression->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Union type ");
        pWriter__write__checked_type(stderr_writer, (Checked_Type *)union_type);
        pWriter__write__cstring(stderr_writer, " does not have ");
        pWriter__write__checked_type(stderr_writer, expression->type);
        pWriter__write__cstring(stderr_writer, " variant");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    return Checked_Make_Union_Expression__create(location, (Checked_Type *)union_type, union_type, union_variant, (Checked_Expression *)expression);
}

Checked_Expression *Checker__check_init_expression(Checker *self, Checked_Named_Type *type, Parsed_Call_Argument *first_parsed_argument, Source_Location location);

Checked_Expression *Checker__check_call_expression(Checker *self, Parsed_Call_Expression *parsed_expression) {
    Checked_Expression *callee_expression = Checker__check_expression(self, parsed_expression->callee_expression, NULL);

    Checked_Expression *procedure_expression = NULL;
    Checked_Procedure_Type *procedure_type = NULL;
    Checked_Expression *receiver_expression = NULL;

    switch (callee_expression->kind) {
    case CHECKED_EXPRESSION_KIND__MEMBER_ACCESS: {
        Checked_Member_Access_Expression *member_access_expression = (Checked_Member_Access_Expression *)callee_expression;
        if (member_access_expression->member->type->kind != CHECKED_TYPE_KIND__PROCEDURE_POINTER) {
            pWriter__begin_location_message(stderr_writer, callee_expression->location, WRITER_STYLE__ERROR);
            pWriter__write__cstring(stderr_writer, "Not a procedure pointer");
            pWriter__end_location_message(stderr_writer);
            panic();
        }
        procedure_expression = (Checked_Expression *)member_access_expression;
        procedure_type = ((Checked_Procedure_Pointer_Type *)member_access_expression->member->type)->procedure_type;
        receiver_expression = NULL;
        break;
    }
    case CHECKED_EXPRESSION_KIND__RECEIVER_METHOD: {
        Checked_Receiver_Method_Expression *receiver_method_expression = (Checked_Receiver_Method_Expression *)callee_expression;
        procedure_expression = receiver_method_expression->procedure_expression;
        procedure_type = receiver_method_expression->procedure_type;
        receiver_expression = receiver_method_expression->receiver_expression;
        free(receiver_method_expression);
        break;
    }
    case CHECKED_EXPRESSION_KIND__SYMBOL: {
        Checked_Symbol *callee_symbol = ((Checked_Symbol_Expression *)callee_expression)->symbol;
        switch (callee_symbol->kind) {
        case CHECKED_SYMBOL_KIND__PROCEDURE: {
            Checked_Procedure_Symbol *procedure_symbol = (Checked_Procedure_Symbol *)callee_symbol;
            procedure_expression = callee_expression;
            procedure_type = procedure_symbol->procedure_type;
            receiver_expression = NULL;
            break;
        }
        case CHECKED_SYMBOL_KIND__TYPE:
            return Checker__check_init_expression(self, ((Checked_Type_Symbol *)callee_symbol)->named_type, parsed_expression->first_argument, parsed_expression->super.location);
        case CHECKED_SYMBOL_KIND__VARIABLE: {
            Checked_Variable_Symbol *variable_symbol = (Checked_Variable_Symbol *)callee_symbol;
            Checked_Type *variable_type = variable_symbol->super.type;
            if (variable_type->kind != CHECKED_TYPE_KIND__PROCEDURE_POINTER) {
                pWriter__begin_location_message(stderr_writer, callee_expression->location, WRITER_STYLE__ERROR);
                pWriter__write__cstring(stderr_writer, "Not a procedure pointer");
                pWriter__end_location_message(stderr_writer);
                panic();
            }
            procedure_type = ((Checked_Procedure_Pointer_Type *)variable_type)->procedure_type;
            procedure_expression = callee_expression;
            receiver_expression = NULL;
            break;
        }
        default:
            pWriter__begin_location_message(stderr_writer, callee_expression->location, WRITER_STYLE__ERROR);
            pWriter__write__cstring(stderr_writer, "Cannot call symbol of kind: ");
            pWriter__write__int64(stderr_writer, callee_symbol->kind);
            pWriter__end_location_message(stderr_writer);
            panic();
        }
        break;
    }
    case CHECKED_EXPRESSION_KIND__TYPE: {
        Checked_Type_Expression *type_expression = (Checked_Type_Expression *)callee_expression;
        return Checker__check_init_expression(self, type_expression->named_type, parsed_expression->first_argument, parsed_expression->super.location);
    }
    default:
        pWriter__begin_location_message(stderr_writer, parsed_expression->callee_expression->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Not a callable");
        pWriter__end_location_message(stderr_writer);
        panic();
    }

    if (procedure_type == NULL) {
        panic();
    }

    Checked_Call_Argument *first_argument = NULL;
    if (parsed_expression->first_argument != NULL || receiver_expression != NULL) {
        Checked_Call_Argument *last_argument = NULL;
        Checked_Procedure_Parameter *procedure_parameter = procedure_type->first_parameter;
        if (procedure_parameter == NULL) {
            pWriter__begin_location_message(stderr_writer, procedure_expression->location, WRITER_STYLE__ERROR);
            pWriter__write__cstring(stderr_writer, "Procedure has no parameters");
            pWriter__end_location_message(stderr_writer);
            panic();
        }
        if (receiver_expression != NULL) {
            Checker__require_same_type(self, procedure_parameter->type, receiver_expression->type, receiver_expression->location);
            first_argument = last_argument = Checked_Call_Argument__create(receiver_expression);
            procedure_parameter = procedure_parameter->next_parameter;
        }
        Parsed_Call_Argument *parsed_argument = parsed_expression->first_argument;
        while (procedure_parameter != NULL && parsed_argument != NULL) {
            if (parsed_argument->name != NULL) {
                if (procedure_parameter->label == NULL) {
                    pWriter__begin_location_message(stderr_writer, parsed_argument->name->super.location, WRITER_STYLE__ERROR);
                    pWriter__write__cstring(stderr_writer, "Unexpected argument name for annonymous parameter");
                    pWriter__end_location_message(stderr_writer);
                    panic();
                } else if (!String__equals_string(procedure_parameter->label, parsed_argument->name->super.lexeme)) {
                    pWriter__begin_location_message(stderr_writer, parsed_argument->name->super.location, WRITER_STYLE__ERROR);
                    pWriter__write__cstring(stderr_writer, "Expected argument name: ");
                    pWriter__write__string(stderr_writer, procedure_parameter->label);
                    pWriter__end_location_message(stderr_writer);
                    panic();
                }
            } else if (procedure_parameter->label != NULL) {
                pWriter__begin_location_message(stderr_writer, parsed_argument->expression->location, WRITER_STYLE__ERROR);
                pWriter__write__cstring(stderr_writer, "Missing argument name: ");
                pWriter__write__string(stderr_writer, procedure_parameter->label);
                pWriter__end_location_message(stderr_writer);
                panic();
            }
            Checked_Expression *argument_expression = Checker__check_expression(self, parsed_argument->expression, procedure_parameter->type);
            if (procedure_parameter->type->kind == CHECKED_TYPE_KIND__UNION && !Checked_Type__equals(procedure_parameter->type, argument_expression->type)) {
                argument_expression = (Checked_Expression *)Checker__make_union_expression(self, argument_expression->location, (Checked_Union_Type *)procedure_parameter->type, argument_expression);
            }
            Checker__require_same_type(self, procedure_parameter->type, argument_expression->type, argument_expression->location);
            Checked_Call_Argument *argument = Checked_Call_Argument__create(argument_expression);
            if (last_argument == NULL) {
                first_argument = argument;
            } else {
                last_argument->next_argument = argument;
            }
            last_argument = argument;
            procedure_parameter = procedure_parameter->next_parameter;
            parsed_argument = parsed_argument->next_argument;
        }
        if (procedure_parameter != NULL) {
            todo("Report too few arguments");
        }
        if (parsed_argument != NULL) {
            todo("Report too many arguments");
        }
    }
    return (Checked_Expression *)Checked_Call_Expression__create(parsed_expression->super.location, procedure_type->return_type, procedure_expression, first_argument);
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
            if (other_expression_type->kind == CHECKED_TYPE_KIND__MULTI_POINTER) {
                can_cast = true;
            }
        }
    } else if (Checked_Type__is_numeric_type(expression_type)) {
        can_cast = true;
    } else if (expression_type->kind == CHECKED_TYPE_KIND__MULTI_POINTER) {
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
    Checked_Type *expression_type = (Checked_Type *)self->builtin_types->u8_type;
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
    return (Checked_Expression *)Checked_Equals_Expression__create(parsed_expression->super.super.location, (Checked_Type *)self->builtin_types->bool_type, left_expression, right_expression);
}

Checked_Expression *Checker__check_greater_expression(Checker *self, Parsed_Greater_Expression *parsed_expression, Checked_Type *expected_type) {
    Checked_Expression *left_expression = Checker__check_expression(self, parsed_expression->super.left_expression, NULL);
    Checker__require_numeric_type(self, left_expression->type, left_expression->location);
    Checked_Expression *right_expression = Checker__check_expression(self, parsed_expression->super.right_expression, left_expression->type);
    Checker__require_same_type(self, left_expression->type, right_expression->type, right_expression->location);
    return (Checked_Expression *)Checked_Greater_Expression__create(parsed_expression->super.super.location, (Checked_Type *)self->builtin_types->bool_type, left_expression, right_expression);
}

Checked_Expression *Checker__check_greater_or_equals_expression(Checker *self, Parsed_Greater_Or_Equals_Expression *parsed_expression, Checked_Type *expected_type) {
    Checked_Expression *left_expression = Checker__check_expression(self, parsed_expression->super.left_expression, NULL);
    Checker__require_numeric_type(self, left_expression->type, left_expression->location);
    Checked_Expression *right_expression = Checker__check_expression(self, parsed_expression->super.right_expression, left_expression->type);
    Checker__require_same_type(self, left_expression->type, right_expression->type, right_expression->location);
    return (Checked_Expression *)Checked_Greater_Or_Equals_Expression__create(parsed_expression->super.super.location, (Checked_Type *)self->builtin_types->bool_type, left_expression, right_expression);
}

Checked_Expression *Checker__check_group_expression(Checker *self, Parsed_Group_Expression *parsed_expression, Checked_Type *expected_type) {
    Checked_Expression *other_expression = Checker__check_expression(self, parsed_expression->other_expression, expected_type);
    return (Checked_Expression *)Checked_Group_Expression__create(parsed_expression->super.location, other_expression->type, other_expression);
}

Checked_Expression *Checker__check_init_struct_expression(Checker *self, Checked_Struct_Type *struct_type, Parsed_Call_Argument *first_parsed_argument, Source_Location location) {
    Checked_Make_Struct_Argument *first_checked_argument = NULL;
    if (first_parsed_argument != NULL) {
        Checked_Make_Struct_Argument *last_checked_argument = NULL;
        Parsed_Call_Argument *parsed_argument = first_parsed_argument;
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
            Checked_Make_Struct_Argument *argument = first_checked_argument;
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
            if (last_checked_argument == NULL) {
                first_checked_argument = argument;
            } else {
                last_checked_argument->next_argument = argument;
            }
            last_checked_argument = argument;
            parsed_argument = parsed_argument->next_argument;
        }
    }
    return (Checked_Expression *)Checked_Make_Struct_Expression__create(location, (Checked_Type *)struct_type, struct_type, first_checked_argument);
}

Checked_Expression *Checker__check_init_trait_expression(Checker *self, Checked_Trait_Type *trait_type, Parsed_Call_Argument *first_parsed_argument, Source_Location location) {
    Parsed_Call_Argument *parsed_argument = first_parsed_argument;
    if (parsed_argument == NULL) {
        pWriter__begin_location_message(stderr_writer, location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Missing argument");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    if (parsed_argument->name != NULL) {
        pWriter__begin_location_message(stderr_writer, parsed_argument->name->super.location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Unexpected argument name");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    if (parsed_argument->next_argument != NULL) {
        pWriter__begin_location_message(stderr_writer, parsed_argument->next_argument->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Unexpected argument");
        pWriter__end_location_message(stderr_writer);
        panic();
    }

    Checked_Expression *self_expression = Checker__check_expression(self, parsed_argument->expression, NULL);
    if (self_expression->type->kind != CHECKED_TYPE_KIND__POINTER) {
        pWriter__begin_location_message(stderr_writer, self_expression->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Expected pointer but got ");
        pWriter__write__checked_type(stderr_writer, self_expression->type);
        pWriter__write__cstring(stderr_writer, " value instead");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    Checked_Type *self_type = ((Checked_Pointer_Type *)self_expression->type)->other_type;
    Checked_Make_Struct_Argument *first_make_struct_argument = Checked_Make_Struct_Argument__create(trait_type->self_struct_member, self_expression);

    Checked_Make_Struct_Argument *last_make_struct_argument = first_make_struct_argument;
    Checked_Trait_Method *trait_method;
    for (trait_method = trait_type->first_method; trait_method != NULL; trait_method = trait_method->next_method) {
        Checked_Type *saved_first_parameter_type = trait_method->procedure_type->first_parameter->type;
        trait_method->procedure_type->first_parameter->type = self_expression->type;
        Checked_Procedure_Symbol *procedure_symbol = Checker__resolve_method_symbol(self, self_expression->type, trait_method->name);
        if (procedure_symbol == NULL) {
            pWriter__begin_location_message(stderr_writer, location, WRITER_STYLE__ERROR);
            pWriter__write__cstring(stderr_writer, "The ");
            pWriter__write__checked_type(stderr_writer, self_type);
            pWriter__write__cstring(stderr_writer, " type does not implement ");
            pWriter__write__checked_type(stderr_writer, (Checked_Type *)trait_type);
            pWriter__write__cstring(stderr_writer, " trait.");
            pWriter__end_location_message(stderr_writer);
            pWriter__begin_location_message(stderr_writer, location, WRITER_STYLE__ERROR);
            pWriter__write__cstring(stderr_writer, "Missing procedure: ");
            Checked_Procedure_Symbol missing_procedure_symbol = {.procedure_name = trait_method->name, .procedure_type = trait_method->procedure_type};
            trait_method->procedure_type->first_parameter->type = self_expression->type;
            pWriter__write__checked_procedure_symbol(stderr_writer, &missing_procedure_symbol);
            trait_method->procedure_type->first_parameter->type = saved_first_parameter_type;
            pWriter__end_location_message(stderr_writer);
            panic();
        } else if (!Checked_Procedure_Type__equals(procedure_symbol->procedure_type, trait_method->procedure_type)) {
            pWriter__begin_location_message(stderr_writer, procedure_symbol->super.location, WRITER_STYLE__ERROR);
            pWriter__write__cstring(stderr_writer, "Procedure type does not match: ");
            pWriter__write__checked_type(stderr_writer, (Checked_Type *)trait_method->procedure_type);
            pWriter__end_location_message(stderr_writer);
            panic();
        }
        trait_method->procedure_type->first_parameter->type = saved_first_parameter_type;
        Checked_Symbol_Expression *procedure_symbol_expression = Checked_Symbol_Expression__create(location, procedure_symbol->super.type, (Checked_Symbol *)procedure_symbol);
        Checked_Cast_Expression *trait_struct_member_argument_expression = Checked_Cast_Expression__create(location, trait_method->struct_member->type, (Checked_Expression *)procedure_symbol_expression);
        last_make_struct_argument = last_make_struct_argument->next_argument = Checked_Make_Struct_Argument__create(trait_method->struct_member, (Checked_Expression *)trait_struct_member_argument_expression);
    }

    return (Checked_Expression *)Checked_Make_Struct_Expression__create(location, (Checked_Type *)trait_type, trait_type->struct_type, first_make_struct_argument);
}

Checked_Expression *Checker__check_init_union_expression(Checker *self, Checked_Union_Type *union_type, Parsed_Call_Argument *first_parsed_argument, Source_Location location) {
    Parsed_Call_Argument *parsed_argument = first_parsed_argument;
    if (parsed_argument == NULL) {
        pWriter__begin_location_message(stderr_writer, location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Missing argument");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    if (parsed_argument->name != NULL) {
        pWriter__begin_location_message(stderr_writer, parsed_argument->name->super.location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Unexpected argument name");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    if (parsed_argument->next_argument != NULL) {
        pWriter__begin_location_message(stderr_writer, parsed_argument->next_argument->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Unexpected argument");
        pWriter__end_location_message(stderr_writer);
        panic();
    }

    Checked_Expression *variant_expression = Checker__check_expression(self, parsed_argument->expression, NULL);
    return (Checked_Expression *)Checker__make_union_expression(self, location, union_type, variant_expression);
}

Checked_Expression *Checker__check_init_expression(Checker *self, Checked_Named_Type *type, Parsed_Call_Argument *first_parsed_argument, Source_Location location) {
    switch (type->super.kind) {
    case CHECKED_TYPE_KIND__STRUCT:
        return Checker__check_init_struct_expression(self, (Checked_Struct_Type *)type, first_parsed_argument, location);
    case CHECKED_TYPE_KIND__TRAIT:
        return Checker__check_init_trait_expression(self, (Checked_Trait_Type *)type, first_parsed_argument, location);
    case CHECKED_TYPE_KIND__UNION:
        return Checker__check_init_union_expression(self, (Checked_Union_Type *)type, first_parsed_argument, location);
    default:
        pWriter__begin_location_message(stderr_writer, location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Cannot initialize ");
        pWriter__write__checked_type(stderr_writer, (Checked_Type *)type);
        pWriter__write__cstring(stderr_writer, " value");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
}

Checked_Expression *Checker__check_integer_expression(Checker *self, Parsed_Integer_Expression *parsed_expression, Checked_Type *expected_type) {
    Checked_Type *expression_type = NULL;
    if (parsed_expression->type != NULL) {
        expression_type = Checker__resolve_type(self, (Parsed_Type *)parsed_expression->type);
    } else if (expected_type != NULL) {
        if (Checked_Type__is_numeric_type(expected_type)) {
            expression_type = expected_type;
        } else if (expected_type->kind == CHECKED_TYPE_KIND__UNION) {
            Checked_Union_Type *union_type = (Checked_Union_Type *)expected_type;
            Checked_Union_Variant *union_variant = union_type->first_variant;
            for (; union_variant != NULL; union_variant = union_variant->next_variant) {
                if (Checked_Type__is_numeric_type(union_variant->type)) {
                    if (expression_type != NULL) {
                        pWriter__begin_location_message(stderr_writer, parsed_expression->super.super.location, WRITER_STYLE__ERROR);
                        pWriter__write__cstring(stderr_writer, "Union type ");
                        pWriter__write__checked_type(stderr_writer, expected_type);
                        pWriter__write__cstring(stderr_writer, " requires to specify the integer type");
                        pWriter__end_location_message(stderr_writer);
                        panic();
                    }
                    expression_type = union_variant->type;
                }
            }
        } else {
            pWriter__begin_location_message(stderr_writer, parsed_expression->super.super.location, WRITER_STYLE__ERROR);
            pWriter__write__cstring(stderr_writer, "Expected numeric type");
            pWriter__end_location_message(stderr_writer);
            panic();
        }
    }
    if (expression_type == NULL) {
        expression_type = (Checked_Type *)self->builtin_types->i32_type;
    }
    uint64_t expression_value = parsed_expression->value;
    int32_t expression_base = parsed_expression->base;
    return (Checked_Expression *)Checked_Integer_Expression__create(parsed_expression->super.super.location, expression_type, expression_value, expression_base);
}

Checked_Expression *Checker__check_is_expression(Checker *self, Parsed_Is_Expression *parsed_expression) {
    Checked_Expression *value_expression = Checker__check_expression(self, parsed_expression->value_expression, NULL);
    Checked_Type *value_type = value_expression->type;
    Checked_Type *runtime_type = Checker__resolve_type(self, parsed_expression->runtime_type);
    switch (value_type->kind) {
    case CHECKED_TYPE_KIND__UNION: {
        Checked_Union_Type *union_type = (Checked_Union_Type *)value_type;
        Checked_Union_Variant *union_variant = union_type->first_variant;
        for (; union_variant != NULL; union_variant = union_variant->next_variant) {
            if (Checked_Type__equals(union_variant->type, runtime_type)) {
                return (Checked_Expression *)Checked_Is_Union_Variant_Expression__create(parsed_expression->super.location, (Checked_Type *)self->builtin_types->bool_type, value_expression, union_variant, parsed_expression->is_not);
            }
        }
        pWriter__begin_location_message(stderr_writer, parsed_expression->value_expression->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Union type ");
        pWriter__write__checked_type(stderr_writer, value_type);
        pWriter__write__cstring(stderr_writer, " doesn't have ");
        pWriter__write__checked_type(stderr_writer, runtime_type);
        pWriter__write__cstring(stderr_writer, " variant");
        pWriter__end_location_message(stderr_writer);
        panic();
        break;
    }
    default:
        break;
    }
    pWriter__begin_location_message(stderr_writer, parsed_expression->super.location, WRITER_STYLE__ERROR);
    pWriter__write__cstring(stderr_writer, "The is opearator doesn't work with ");
    pWriter__write__checked_type(stderr_writer, value_type);
    pWriter__write__cstring(stderr_writer, " values");
    pWriter__end_location_message(stderr_writer);
    panic();
}

Checked_Expression *Checker__check_less_expression(Checker *self, Parsed_Less_Expression *parsed_expression, Checked_Type *expected_type) {
    Checked_Expression *left_expression = Checker__check_expression(self, parsed_expression->super.left_expression, NULL);
    Checker__require_numeric_type(self, left_expression->type, left_expression->location);
    Checked_Expression *right_expression = Checker__check_expression(self, parsed_expression->super.right_expression, left_expression->type);
    Checker__require_same_type(self, left_expression->type, right_expression->type, right_expression->location);
    return (Checked_Expression *)Checked_Less_Expression__create(parsed_expression->super.super.location, (Checked_Type *)self->builtin_types->bool_type, left_expression, right_expression);
}

Checked_Expression *Checker__check_less_or_equals_expression(Checker *self, Parsed_Less_Or_Equals_Expression *parsed_expression, Checked_Type *expected_type) {
    Checked_Expression *left_expression = Checker__check_expression(self, parsed_expression->super.left_expression, NULL);
    Checker__require_numeric_type(self, left_expression->type, left_expression->location);
    Checked_Expression *right_expression = Checker__check_expression(self, parsed_expression->super.right_expression, left_expression->type);
    Checker__require_same_type(self, left_expression->type, right_expression->type, right_expression->location);
    return (Checked_Expression *)Checked_Less_Or_Equals_Expression__create(parsed_expression->super.super.location, (Checked_Type *)self->builtin_types->bool_type, left_expression, right_expression);
}

Checked_Expression *Checker__check_logic_and_expression(Checker *self, Parsed_Logic_And_Expression *parsed_expression) {
    Checked_Expression *left_expression = Checker__check_expression(self, parsed_expression->super.left_expression, (Checked_Type *)self->builtin_types->bool_type);
    Checker__require_same_type(self, (Checked_Type *)self->builtin_types->bool_type, left_expression->type, left_expression->location);
    Checked_Expression *right_expression = Checker__check_expression(self, parsed_expression->super.right_expression, left_expression->type);
    Checker__require_same_type(self, left_expression->type, right_expression->type, right_expression->location);
    return (Checked_Expression *)Checked_Logic_And_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

Checked_Expression *Checker__check_logic_or_expression(Checker *self, Parsed_Logic_Or_Expression *parsed_expression) {
    Checked_Expression *left_expression = Checker__check_expression(self, parsed_expression->super.left_expression, (Checked_Type *)self->builtin_types->bool_type);
    Checker__require_same_type(self, (Checked_Type *)self->builtin_types->bool_type, left_expression->type, left_expression->location);
    Checked_Expression *right_expression = Checker__check_expression(self, parsed_expression->super.right_expression, left_expression->type);
    Checker__require_same_type(self, left_expression->type, right_expression->type, right_expression->location);
    return (Checked_Expression *)Checked_Logic_Or_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

Checked_Expression *Checker__check_module_symbol_expression(Checker *self, Checked_Module *checked_module, Source_Location expression_location, Token *symbol_name);

Checked_Expression *Checker__check_member_access_expression(Checker *self, Parsed_Member_Access_Expression *parsed_expression) {
    Checked_Expression *object_expression = Checker__check_expression(self, parsed_expression->object_expression, NULL);
    Checked_Type *object_type = object_expression->type;

    if (object_type->kind == CHECKED_TYPE_KIND__MODULE) {
        if (object_expression->kind == CHECKED_EXPRESSION_KIND__SYMBOL) {
            Checked_Symbol_Expression *symbol_expression = (Checked_Symbol_Expression *)object_expression;
            if (symbol_expression->symbol->kind != CHECKED_SYMBOL_KIND__IMPORT) {
                pWriter__begin_location_message(stderr_writer, object_expression->location, WRITER_STYLE__ERROR);
                pWriter__write__cstring(stderr_writer, "Not an import");
                pWriter__end_location_message(stderr_writer);
                panic();
            }
            Checked_Module *module = ((Checked_Import_Symbol *)symbol_expression->symbol)->other_module;
            Checked_Symbol *module_symbol = Checked_Symbols__find_symbol(self->global_symbols, module, parsed_expression->member_name->lexeme);
            if (module_symbol == NULL) {
                pWriter__begin_location_message(stderr_writer, parsed_expression->super.location, WRITER_STYLE__ERROR);
                pWriter__write__cstring(stderr_writer, "Module ");
                pWriter__write__string(stderr_writer, module->name);
                pWriter__write__cstring(stderr_writer, " has no ");
                pWriter__write__string(stderr_writer, parsed_expression->member_name->lexeme);
                pWriter__write__cstring(stderr_writer, " symbol");
                pWriter__end_location_message(stderr_writer);
                panic();
            }
            return (Checked_Expression *)Checked_Symbol_Expression__create(parsed_expression->super.location, module_symbol->type, module_symbol);
        }
        pWriter__begin_location_message(stderr_writer, object_expression->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Not an import");
        pWriter__end_location_message(stderr_writer);
        panic();
    }

    /* Check struct member expression */
    if (object_type->kind == CHECKED_TYPE_KIND__POINTER) {
        object_type = ((Checked_Pointer_Type *)object_type)->other_type;
    }
    switch (object_type->kind) {
    case CHECKED_TYPE_KIND__STR:
        if (String__equals_cstring(parsed_expression->member_name->lexeme, "length")) {
            return (Checked_Expression *)Checked_String_Length_Expression__create(parsed_expression->super.location, (Checked_Type *)self->builtin_types->usize_type, object_expression);
        }
        break;
    case CHECKED_TYPE_KIND__STRUCT: {
        Checked_Struct_Type *struct_type = (Checked_Struct_Type *)object_type;
        Checked_Struct_Member *member = Checked_Struct_Type__find_member(struct_type, parsed_expression->member_name->lexeme);
        if (member != NULL) {
            return (Checked_Expression *)Checked_Member_Access_Expression__create(parsed_expression->super.location, member->type, object_expression, member);
        }
        break;
    }
    case CHECKED_TYPE_KIND__TRAIT: {
        Checked_Trait_Type *trait_type = (Checked_Trait_Type *)object_type;
        Checked_Trait_Method *trait_method;
        for (trait_method = trait_type->first_method; trait_method != NULL; trait_method = trait_method->next_method) {
            if (String__equals_string(trait_method->name, parsed_expression->member_name->lexeme)) {
                Checked_Member_Access_Expression *receiver_expression = Checked_Member_Access_Expression__create(object_expression->location, trait_type->self_struct_member->type, object_expression, trait_type->self_struct_member);
                Checked_Member_Access_Expression *procedure_expression = Checked_Member_Access_Expression__create(parsed_expression->member_name->location, trait_method->struct_member->type, object_expression, trait_method->struct_member);
                return (Checked_Expression *)Checked_Receiver_Method_Expression__create(parsed_expression->super.location, trait_method->procedure_type->return_type, (Checked_Expression *)receiver_expression, (Checked_Expression *)procedure_expression, trait_method->procedure_type);
            }
        }
        break;
    }
    default:
        break;
    }

    /* Check method */
    object_type = object_expression->type;
    Checked_Procedure_Symbol *procedure_symbol = Checker__resolve_method_symbol(self, object_type, parsed_expression->member_name->lexeme);
    if (procedure_symbol != NULL) {
        Checked_Symbol_Expression *procedure_expression = Checked_Symbol_Expression__create(parsed_expression->member_name->location, procedure_symbol->super.type, (Checked_Symbol *)procedure_symbol);
        return (Checked_Expression *)Checked_Receiver_Method_Expression__create(parsed_expression->super.location, procedure_symbol->procedure_type->return_type, object_expression, (Checked_Expression *)procedure_expression, procedure_symbol->procedure_type);
    }

    /* Check referenced method */
    if (object_type->kind != CHECKED_TYPE_KIND__POINTER) {
        procedure_symbol = Checker__resolve_reference_method_symbol(self, object_type, parsed_expression->member_name->lexeme);
        if (procedure_symbol != NULL) {
            object_type = (Checked_Type *)Checked_Pointer_Type__create(object_type->location, object_type);
            object_expression = (Checked_Expression *)Checked_Address_Of_Expression__create(object_expression->location, object_type, object_expression);
            Checked_Symbol_Expression *procedure_expression = Checked_Symbol_Expression__create(parsed_expression->member_name->location, (Checked_Type *)procedure_symbol->super.type, (Checked_Symbol *)procedure_symbol);
            return (Checked_Expression *)Checked_Receiver_Method_Expression__create(parsed_expression->super.location, procedure_symbol->procedure_type->return_type, object_expression, (Checked_Expression *)procedure_expression, procedure_symbol->procedure_type);
        }
    }

    pWriter__begin_location_message(stderr_writer, parsed_expression->member_name->location, WRITER_STYLE__ERROR);
    pWriter__write__cstring(stderr_writer, "No such struct member");
    pWriter__end_location_message(stderr_writer);
    panic();
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
    Checked_Expression *other_expression = Checker__check_expression(self, parsed_expression->super.other_expression, (Checked_Type *)self->builtin_types->bool_type);
    Checked_Type *other_expression_type = other_expression->type;
    Checker__require_same_type(self, (Checked_Type *)self->builtin_types->bool_type, other_expression_type, other_expression->location);
    return (Checked_Expression *)Checked_Not_Expression__create(parsed_expression->super.super.location, other_expression_type, other_expression);
}

Checked_Expression *Checker__check_not_equals_expression(Checker *self, Parsed_Not_Equals_Expression *parsed_expression) {
    Checked_Expression *left_expression = Checker__check_expression(self, parsed_expression->super.left_expression, NULL);
    Checked_Expression *right_expression = Checker__check_expression(self, parsed_expression->super.right_expression, left_expression->type);
    Checker__require_same_type(self, left_expression->type, right_expression->type, right_expression->location);
    return (Checked_Expression *)Checked_Not_Equals_Expression__create(parsed_expression->super.super.location, (Checked_Type *)self->builtin_types->bool_type, left_expression, right_expression);
}

Checked_Expression *Checker__check_null_expression(Checker *self, Parsed_Null_Expression *parsed_expression) {
    Checked_Type *expression_type = (Checked_Type *)self->builtin_types->null_type;
    return (Checked_Expression *)Checked_Null_Expression__create(parsed_expression->super.literal->location, expression_type);
}

Checked_Expression *Checker__check_sizeof_expression(Checker *self, Parsed_Sizeof_Expression *parsed_expression) {
    Checked_Type *expression_type = (Checked_Type *)self->builtin_types->isize_type;
    Checked_Type *sized_type = Checker__resolve_type(self, parsed_expression->type);
    return (Checked_Expression *)Checked_Sizeof_Expression__create(parsed_expression->super.location, expression_type, sized_type);
}

Checked_Expression *Checker__check_string_expression(Checker *self, Parsed_String_Expression *parsed_expression) {
    Checked_Type *string_type = (Checked_Type *)self->builtin_types->str_type;
    String *string_value = parsed_expression->value;
    return (Checked_Expression *)Checked_String_Expression__create(parsed_expression->super.super.location, string_type, string_value);
}

Checked_Expression *Checker__check_subtract_expression(Checker *self, Parsed_Subtract_Expression *parsed_expression, Checked_Type *expected_type) {
    Checked_Expression *left_expression = Checker__check_expression(self, parsed_expression->super.left_expression, expected_type);
    Checker__require_numeric_type(self, left_expression->type, left_expression->location);
    Checked_Expression *right_expression = Checker__check_expression(self, parsed_expression->super.right_expression, left_expression->type);
    Checker__require_same_type(self, left_expression->type, right_expression->type, right_expression->location);
    return (Checked_Expression *)Checked_Subtract_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

Checked_Expression *Checker__check_symbol_expression(Checker *self, Parsed_Symbol_Expression *parsed_expression) {
    Checked_Symbol *symbol = Checked_Symbols__find_symbol(self->symbols, self->checked_module, parsed_expression->name->lexeme);
    if (symbol == NULL) {
        symbol = Checked_Symbols__find_symbol(self->global_symbols->parent, self->modules->builtin_module, parsed_expression->name->lexeme);
    }
    if (symbol == NULL) {
        symbol = Checked_Symbols__find_symbol(self->builtin_types->symbols, NULL, parsed_expression->name->lexeme);
    }
    Source_Location expression_location = parsed_expression->name->location;
    if (symbol == NULL || symbol->kind == CHECKED_SYMBOL_KIND__EXTERNAL) {
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

Checked_Expression *Checker__check_type_specialization_expression(Checker *self, Parsed_Type_Specialization_Expression *parsed_expression) {
    Checked_Expression *type_expression = Checker__check_expression(self, parsed_expression->type_expression, NULL);
    if (type_expression->kind != CHECKED_EXPRESSION_KIND__SYMBOL) {
        pWriter__begin_location_message(stderr_writer, parsed_expression->type_expression->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Expected type symbol");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    Checked_Symbol *type_symbol = ((Checked_Symbol_Expression *)type_expression)->symbol;
    if (type_symbol->kind != CHECKED_SYMBOL_KIND__TYPE) {
        pWriter__begin_location_message(stderr_writer, parsed_expression->type_expression->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Expected type symbol");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    Checked_Named_Type *type = ((Checked_Type_Symbol *)type_symbol)->named_type;
    if (type->super.kind != CHECKED_TYPE_KIND__GENERIC) {
        pWriter__begin_location_message(stderr_writer, parsed_expression->type_expression->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Expected generic type symbol");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    Identifier_Token *parsed_type_module = Identifier_Token__create(parsed_expression->super.location, type->module->name);
    Identifier_Token *parsed_type_name_token = Identifier_Token__create(parsed_expression->super.location, type->name);
    Parsed_Named_Type *parsed_type = Parsed_Named_Type__create((Token *)parsed_type_module, (Token *)parsed_type_name_token);
    parsed_type->first_type_argument = parsed_expression->first_type_argument;
    Checked_Named_Type *specialized_type = Checker__specialize_type(self, (Checked_Generic_Type *)type, parsed_type);
    return (Checked_Expression *)Checked_Type_Expression__create(parsed_expression->super.location, (Checked_Type *)self->builtin_types->type_type, specialized_type);
}

Checked_Expression *Checker__check_expression(Checker *self, Parsed_Expression *parsed_expression, Checked_Type *expected_type) {
    switch (parsed_expression->kind) {
    case PARSED_EXPRESSION_KIND__ADD:
        return Checker__check_add_expression(self, (Parsed_Add_Expression *)parsed_expression, expected_type);
    case PARSED_EXPRESSION_KIND__ADDRESS_OF:
        return Checker__check_address_of_expression(self, (Parsed_Address_Of_Expression *)parsed_expression);
    case PARSED_EXPRESSION_KIND__ALLOC:
        return Checker__check_alloc_expression(self, (Parsed_Alloc_Expression *)parsed_expression);
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
    case PARSED_EXPRESSION_KIND__IS:
        return Checker__check_is_expression(self, (Parsed_Is_Expression *)parsed_expression);
    case PARSED_EXPRESSION_KIND__LESS:
        return Checker__check_less_expression(self, (Parsed_Less_Expression *)parsed_expression, expected_type);
    case PARSED_EXPRESSION_KIND__LESS_OR_EQUALS:
        return Checker__check_less_or_equals_expression(self, (Parsed_Less_Or_Equals_Expression *)parsed_expression, expected_type);
    case PARSED_EXPRESSION_KIND__LOGIC_AND:
        return Checker__check_logic_and_expression(self, (Parsed_Logic_And_Expression *)parsed_expression);
    case PARSED_EXPRESSION_KIND__LOGIC_OR:
        return Checker__check_logic_or_expression(self, (Parsed_Logic_Or_Expression *)parsed_expression);
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
    case PARSED_EXPRESSION_KIND__SUBTRACT:
        return Checker__check_subtract_expression(self, (Parsed_Subtract_Expression *)parsed_expression, expected_type);
    case PARSED_EXPRESSION_KIND__SYMBOL:
        return Checker__check_symbol_expression(self, (Parsed_Symbol_Expression *)parsed_expression);
    case PARSED_EXPRESSION_KIND__TYPE_SPECIALIZATION:
        return Checker__check_type_specialization_expression(self, (Parsed_Type_Specialization_Expression *)parsed_expression);
    }
    pWriter__begin_location_message(stderr_writer, parsed_expression->location, WRITER_STYLE__ERROR);
    pWriter__write__cstring(stderr_writer, "Unsupported expression kind");
    pWriter__end_location_message(stderr_writer);
    panic();
}

typedef struct Checked_Expression_Decomposer {
    Checker *checker;
    Checked_Statements temp_statements;
    int32_t temp_counter;
} Checked_Expression_Decomposer;

Checked_Expression *Checked_Expression_Decomposer__decompose(Checked_Expression_Decomposer *self, Checked_Expression *expression);

Checked_Expression *Checked_Expression_Decomposer__create_temp_variable(Checked_Expression_Decomposer *self, Checked_Expression *expression) {
    String *temp_variable_name = String__create_from("__");
    self->temp_counter++;
    if (self->temp_counter < 100) {
        String__append_char(temp_variable_name, '0');
        if (self->temp_counter < 10) {
            String__append_char(temp_variable_name, '0');
        }
    }
    String__append_int16_t(temp_variable_name, self->temp_counter);
    String__append_cstring(temp_variable_name, "__");

    Checked_Variable_Symbol *temp_variable_symbol = Checked_Variable_Symbol__create(self->checker->checked_module, expression->location, temp_variable_name, expression->type, false);
    Checked_Symbols__append_symbol(self->checker->symbols, (Checked_Symbol *)temp_variable_symbol);

    Checked_Variable_Statement *temp_variable_statement = Checked_Variable_Statement__create(expression->location, temp_variable_symbol, false, expression);
    Checked_Statements__append(&self->temp_statements, (Checked_Statement *)temp_variable_statement);

    return (Checked_Expression *)Checked_Symbol_Expression__create(expression->location, expression->type, (Checked_Symbol *)temp_variable_symbol);
}

Checked_Expression *Checked_Expression_Decomposer__decompose_binary_expression(Checked_Expression_Decomposer *self, Checked_Binary_Expression *expression) {
    expression->left_expression = Checked_Expression_Decomposer__decompose(self, expression->left_expression);
    expression->right_expression = Checked_Expression_Decomposer__decompose(self, expression->right_expression);
    return (Checked_Expression *)expression;
}

Checked_Expression *Checked_Expression_Decomposer__decompose_unary_expression(Checked_Expression_Decomposer *self, Checked_Unary_Expression *expression) {
    expression->other_expression = Checked_Expression_Decomposer__decompose(self, expression->other_expression);
    return (Checked_Expression *)expression;
}

Checked_Expression *Checked_Expression_Decomposer__decompose(Checked_Expression_Decomposer *self, Checked_Expression *expression) {
    switch (expression->kind) {
    case CHECKED_EXPRESSION_KIND__ADD:
    case CHECKED_EXPRESSION_KIND__DIVIDE:
    case CHECKED_EXPRESSION_KIND__EQUALS:
    case CHECKED_EXPRESSION_KIND__GREATER:
    case CHECKED_EXPRESSION_KIND__GREATER_OR_EQUALS:
    case CHECKED_EXPRESSION_KIND__LESS:
    case CHECKED_EXPRESSION_KIND__LESS_OR_EQUALS:
    case CHECKED_EXPRESSION_KIND__MODULO:
    case CHECKED_EXPRESSION_KIND__MULTIPLY:
    case CHECKED_EXPRESSION_KIND__NOT_EQUALS:
    case CHECKED_EXPRESSION_KIND__SUBTRACT:
        return Checked_Expression_Decomposer__decompose_binary_expression(self, (Checked_Binary_Expression *)expression);
    case CHECKED_EXPRESSION_KIND__ADDRESS_OF:
    case CHECKED_EXPRESSION_KIND__DEREFERENCE:
    case CHECKED_EXPRESSION_KIND__GROUP: // Handle group expressions as unary expressions
    case CHECKED_EXPRESSION_KIND__MINUS:
    case CHECKED_EXPRESSION_KIND__NOT:
        return Checked_Expression_Decomposer__decompose_unary_expression(self, (Checked_Unary_Expression *)expression);
    case CHECKED_EXPRESSION_KIND__ALLOC:
    case CHECKED_EXPRESSION_KIND__ARRAY_ACCESS:
    case CHECKED_EXPRESSION_KIND__BOOL:
    case CHECKED_EXPRESSION_KIND__CALL:
    case CHECKED_EXPRESSION_KIND__CAST:
    case CHECKED_EXPRESSION_KIND__CHARACTER:
    case CHECKED_EXPRESSION_KIND__INTEGER:
    case CHECKED_EXPRESSION_KIND__IS_UNION_VARIANT:
    case CHECKED_EXPRESSION_KIND__LOGIC_AND:
    case CHECKED_EXPRESSION_KIND__LOGIC_OR:
    case CHECKED_EXPRESSION_KIND__MAKE_STRUCT:
    case CHECKED_EXPRESSION_KIND__MAKE_UNION:
    case CHECKED_EXPRESSION_KIND__MEMBER_ACCESS:
    case CHECKED_EXPRESSION_KIND__NULL:
    case CHECKED_EXPRESSION_KIND__RECEIVER_METHOD:
    case CHECKED_EXPRESSION_KIND__SIZEOF:
    case CHECKED_EXPRESSION_KIND__STRING_LENGTH:
    case CHECKED_EXPRESSION_KIND__STRING:
    case CHECKED_EXPRESSION_KIND__SYMBOL:
    case CHECKED_EXPRESSION_KIND__TYPE:
        return expression;
    default:
        pWriter__begin_location_message(stderr_writer, expression->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Cannot decompose expression kind: ");
        pWriter__write__int64(stderr_writer, expression->kind);
        pWriter__end_location_message(stderr_writer);
        panic();
    }
}

typedef struct Decomposed_Expression {
    Checked_Expression *expression;
    Checked_Statements *temp_statements;
} Decomposed_Expression;

Decomposed_Expression Checker__decompose_expression(Checker *self, Checked_Expression *expression) {
    Checked_Expression_Decomposer decomposer = {
        .checker = self,
        .temp_statements = {0},
        .temp_counter = 0,
    };
    self->symbols = Checked_Symbols__create(self->symbols);
    Checked_Expression *decomposed_expression = Checked_Expression_Decomposer__decompose(&decomposer, expression);
    self->symbols = self->symbols->parent;
    Checked_Statements *temp_statements;
    if (decomposer.temp_statements.first_statement != NULL) {
        temp_statements = Checked_Statements__create_copy(&decomposer.temp_statements);
    } else {
        temp_statements = NULL;
    }
    return (Decomposed_Expression){
        .expression = decomposed_expression,
        .temp_statements = temp_statements,
    };
}

Checked_Named_Type *Checker__check_builtin_type_statement(Checker *self, Token *type_name) {
    Source_Location builtin_type_location = type_name->location;
    String *builtin_type_name = type_name->lexeme;
    Checked_Named_Type *type = Checker__find_type(self, builtin_type_name);
    if (type != NULL) {
        pWriter__begin_location_message(stderr_writer, builtin_type_location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Type redeclaration: ");
        pWriter__write__string(stderr_writer, builtin_type_name);
        pWriter__end_location_message(stderr_writer);
        panic();
    }

    Checked_Named_Type *builtin_type = NULL;
    switch (builtin_type_name->data[0]) {
    case 'A':
        if (String__equals_cstring(builtin_type_name, "Any")) {
            builtin_type = self->builtin_types->any_type = Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__ANY, sizeof(Checked_Named_Type), builtin_type_location, builtin_type_name, NULL);
        }
        break;
    case 'b':
        if (String__equals_cstring(builtin_type_name, "bool")) {
            builtin_type = self->builtin_types->bool_type = Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__BOOL, sizeof(Checked_Named_Type), builtin_type_location, builtin_type_name, NULL);
        }
        break;
    case 'i':
        if (String__equals_cstring(builtin_type_name, "i8")) {
            builtin_type = self->builtin_types->i8_type = Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__I8, sizeof(Checked_Named_Type), builtin_type_location, builtin_type_name, NULL);
        } else if (String__equals_cstring(builtin_type_name, "i16")) {
            builtin_type = self->builtin_types->i16_type = Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__I16, sizeof(Checked_Named_Type), builtin_type_location, builtin_type_name, NULL);
        } else if (String__equals_cstring(builtin_type_name, "i32")) {
            builtin_type = self->builtin_types->i32_type = Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__I32, sizeof(Checked_Named_Type), builtin_type_location, builtin_type_name, NULL);
        } else if (String__equals_cstring(builtin_type_name, "i64")) {
            builtin_type = self->builtin_types->i64_type = Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__I64, sizeof(Checked_Named_Type), builtin_type_location, builtin_type_name, NULL);
        } else if (String__equals_cstring(builtin_type_name, "isize")) {
            builtin_type = self->builtin_types->isize_type = Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__ISIZE, sizeof(Checked_Named_Type), builtin_type_location, builtin_type_name, NULL);
        }
        break;
    case 's':
        if (String__equals_cstring(builtin_type_name, "str")) {
            builtin_type = self->builtin_types->str_type = Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__STR, sizeof(Checked_Named_Type), builtin_type_location, builtin_type_name, NULL);
        }
        break;
    case 'u':
        if (String__equals_cstring(builtin_type_name, "u8")) {
            builtin_type = self->builtin_types->u8_type = Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__U8, sizeof(Checked_Named_Type), builtin_type_location, builtin_type_name, NULL);
        } else if (String__equals_cstring(builtin_type_name, "u16")) {
            builtin_type = self->builtin_types->u16_type = Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__U16, sizeof(Checked_Named_Type), builtin_type_location, builtin_type_name, NULL);
        } else if (String__equals_cstring(builtin_type_name, "u32")) {
            builtin_type = self->builtin_types->u32_type = Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__U32, sizeof(Checked_Named_Type), builtin_type_location, builtin_type_name, NULL);
        } else if (String__equals_cstring(builtin_type_name, "u64")) {
            builtin_type = self->builtin_types->u64_type = Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__U64, sizeof(Checked_Named_Type), builtin_type_location, builtin_type_name, NULL);
        } else if (String__equals_cstring(builtin_type_name, "usize")) {
            builtin_type = self->builtin_types->usize_type = Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__USIZE, sizeof(Checked_Named_Type), builtin_type_location, builtin_type_name, NULL);
        }
        break;
    }

    if (builtin_type == NULL) {
        pWriter__begin_location_message(stderr_writer, builtin_type_location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Unknown builtin type: ");
        pWriter__write__string(stderr_writer, builtin_type_name);
        pWriter__end_location_message(stderr_writer);
        panic();
    }

    Checked_Symbols__append_symbol(self->builtin_types->symbols, (Checked_Symbol *)Checked_Type_Symbol__create(NULL, builtin_type_location, builtin_type->name, (Checked_Type *)self->builtin_types->type_type, builtin_type));
    return builtin_type;
}

Checked_Named_Type *Checker__check_external_type_statement(Checker *self, Token *type_name) {
    Checked_Named_Type *type = Checker__find_type(self, type_name->lexeme);
    if (type != NULL) {
        pWriter__begin_location_message(stderr_writer, type_name->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Type redeclaration: ");
        pWriter__write__string(stderr_writer, type_name->lexeme);
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    Checked_External_Type *external_type = Checked_External_Type__create(type_name->location, type_name->lexeme, self->checked_module);
    external_type->super.super.symbol = Checker__create_type_symbol(self, type_name->lexeme, (Checked_Named_Type *)external_type);
    return (Checked_Named_Type *)external_type;
}

struct Checked_Type_Dependency *Checked_Type_Dependency__create(Checked_Type *type) {
    struct Checked_Type_Dependency *dependency = malloc(sizeof(struct Checked_Type_Dependency));
    dependency->type = type;
    dependency->next_dependency = NULL;
    return dependency;
}

void Checked_Type__append_dependencies(Checked_Type *self, Checked_Type *other, Source_Location location, Checker *checker) {
    if (self == other) {
        pWriter__begin_location_message(stderr_writer, location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Type ");
        pWriter__write__checked_type(stderr_writer, self);
        pWriter__write__cstring(stderr_writer, " cannot depend on itself");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    switch (other->kind) {
    case CHECKED_TYPE_KIND__ARRAY:
        Checked_Type__append_dependencies(self, ((Checked_Array_Type *)other)->item_type, location, checker);
        return;
    case CHECKED_TYPE_KIND__EXTERNAL:
        pWriter__begin_location_message(stderr_writer, location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Type ");
        pWriter__write__checked_type(stderr_writer, self);
        pWriter__write__cstring(stderr_writer, " cannot depend on external type ");
        pWriter__write__checked_type(stderr_writer, other);
        pWriter__end_location_message(stderr_writer);
        panic();
    case CHECKED_TYPE_KIND__STRUCT:
    case CHECKED_TYPE_KIND__UNION:
        break;
    default:
        return;
    }
    struct Checked_Type_Dependency *self_dependency = self->first_dependency;
    if (self_dependency == NULL) {
        self->first_dependency = Checked_Type_Dependency__create(other);
    } else {
        while (self_dependency->next_dependency != NULL) {
            if (self_dependency->type == other) {
                return;
            }
            self_dependency = self_dependency->next_dependency;
        }
        self_dependency->next_dependency = Checked_Type_Dependency__create(other);
    }
    struct Checked_Type_Dependency *other_dependency = other->first_dependency;
    while (other_dependency != NULL) {
        Checked_Type__append_dependencies(self, other_dependency->type, location, checker);
        other_dependency = other_dependency->next_dependency;
    }
}

Checked_Named_Type *Checker__check_struct_type_statement(Checker *self, Token *type_name, Parsed_Struct_Type_Specifier *parsed_type_specifier) {
    Checked_Named_Type *other_type = Checked_Symbols__find_type(self->global_symbols, self->checked_module, type_name->lexeme);
    if (other_type != NULL) {
        if (other_type->super.kind == CHECKED_TYPE_KIND__STRUCT && ((Checked_Struct_Type *)other_type)->parsed_type_specifier == parsed_type_specifier) {
            /* Type checked already */
            return other_type;
        }
        pWriter__begin_location_message(stderr_writer, type_name->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Type redeclaration");
        pWriter__end_location_message(stderr_writer);
        if (other_type->super.location.source != NULL) {
            pWriter__begin_location_message(stderr_writer, other_type->super.location, WRITER_STYLE__WARNING);
            pWriter__write__cstring(stderr_writer, "Previous declaration here");
            pWriter__end_location_message(stderr_writer);
        }
        panic();
    }

    String *struct_type_name = type_name->lexeme;
    Checked_Module *struct_type_module = self->checked_module;
    if (self->global_symbols == self->builtin_types->symbols) {
        /* This is a builtin type */
        struct_type_module = NULL;
    }
    Checked_Struct_Type *struct_type = Checked_Struct_Type__create(type_name->location, struct_type_name, struct_type_module, parsed_type_specifier);
    struct_type->super.super.symbol = Checker__create_type_symbol(self, struct_type_name, (Checked_Named_Type *)struct_type);

    if (parsed_type_specifier->first_member != NULL) {
        Checked_Struct_Member *last_struct_member = NULL;
        Parsed_Struct_Member *parsed_member = parsed_type_specifier->first_member;
        while (parsed_member != NULL) {
            Checked_Struct_Member *struct_member = Checked_Struct_Type__find_member(struct_type, parsed_member->name->lexeme);
            if (struct_member != NULL) {
                todo("Report duplicate struct member declaration");
            }
            Checked_Type *struct_member_type = Checker__resolve_type(self, parsed_member->type);
            if (Checked_Type__equals(struct_member_type, (Checked_Type *)struct_type)) {
                pWriter__begin_location_message(stderr_writer, parsed_member->type->location, WRITER_STYLE__ERROR);
                pWriter__write__cstring(stderr_writer, "Struct member cannot be of its own type");
                pWriter__end_location_message(stderr_writer);
                panic();
            }
            Checked_Type__append_dependencies((Checked_Type *)struct_type, struct_member_type, parsed_member->type->location, self);
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

    return (Checked_Named_Type *)struct_type;
}

Checked_Procedure_Type *Checker__check_procedure_type(Checker *self, Source_Location location, Parsed_Procedure_Parameter *first_parsed_parameter, Parsed_Type *parsed_return_type) {
    Checked_Type *procedure_return_type;
    if (parsed_return_type != NULL) {
        procedure_return_type = Checker__resolve_type(self, parsed_return_type);
        switch (procedure_return_type->kind) {
        case CHECKED_TYPE_KIND__ANY:
            pWriter__begin_location_message(stderr_writer, parsed_return_type->location, WRITER_STYLE__ERROR);
            pWriter__write__cstring(stderr_writer, "Cannot use Any as return type");
            pWriter__end_location_message(stderr_writer);
            panic();
        case CHECKED_TYPE_KIND__EXTERNAL:
            pWriter__begin_location_message(stderr_writer, parsed_return_type->location, WRITER_STYLE__ERROR);
            pWriter__write__cstring(stderr_writer, "Cannot use external type as return type");
            pWriter__end_location_message(stderr_writer);
            panic();
        default:
            break;
        }
    } else {
        procedure_return_type = (Checked_Type *)self->builtin_types->nothing_type;
    }
    Checked_Procedure_Parameter *procedure_first_parameter = NULL;
    Checked_Procedure_Parameter *procedure_last_parameter = NULL;
    Parsed_Procedure_Parameter *parsed_parameter = first_parsed_parameter;
    while (parsed_parameter != NULL) {
        Checked_Type *procedure_parameter_type = Checker__resolve_type(self, parsed_parameter->type);
        switch (procedure_parameter_type->kind) {
        case CHECKED_TYPE_KIND__ANY:
            pWriter__begin_location_message(stderr_writer, parsed_parameter->type->location, WRITER_STYLE__ERROR);
            pWriter__write__cstring(stderr_writer, "Cannot use Any as parameter type");
            pWriter__end_location_message(stderr_writer);
            panic();
        case CHECKED_TYPE_KIND__EXTERNAL:
            pWriter__begin_location_message(stderr_writer, parsed_parameter->type->location, WRITER_STYLE__ERROR);
            pWriter__write__cstring(stderr_writer, "Cannot use external types as procedure parameters");
            pWriter__end_location_message(stderr_writer);
            panic();
        default:
            break;
        }
        Checked_Procedure_Parameter *procedure_parameter = Checked_Procedure_Parameter__create(parsed_parameter->name->location, parsed_parameter->label ? parsed_parameter->label->lexeme : NULL, parsed_parameter->name->lexeme, procedure_parameter_type);
        if (procedure_first_parameter == NULL) {
            procedure_first_parameter = procedure_parameter;
        } else {
            procedure_last_parameter->next_parameter = procedure_parameter;
        }
        procedure_last_parameter = procedure_parameter;
        parsed_parameter = parsed_parameter->next_parameter;
    }
    return Checked_Procedure_Type__create(location, procedure_first_parameter, procedure_return_type);
}

Checked_Named_Type *Checker__check_trait_type_statement(Checker *self, Token *type_name, Parsed_Trait_Type_Specifier *parsed_trait_type_specifier) {
    Checked_Named_Type *other_type = Checker__find_type(self, type_name->lexeme);
    if (other_type != NULL) {
        pWriter__begin_location_message(stderr_writer, type_name->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Type redeclaration");
        pWriter__end_location_message(stderr_writer);
        panic();
    }

    Checked_Trait_Type *trait_type = Checked_Trait_Type__create(type_name->location, type_name->lexeme, self->checked_module);
    trait_type->super.super.symbol = Checker__create_type_symbol(self, type_name->lexeme, (Checked_Named_Type *)trait_type);

    trait_type->struct_type = Checked_Struct_Type__create(type_name->location, trait_type->super.name, self->checked_module, NULL);

    Checked_Type *trait_receiver_type = (Checked_Type *)Checked_Pointer_Type__create((Source_Location){}, (Checked_Type *)self->builtin_types->any_type);
    trait_type->self_struct_member = trait_type->struct_type->first_member = Checked_Struct_Member__create((Source_Location){}, String__create_from("self"), trait_receiver_type);

    Parsed_Trait_Method *parsed_method = parsed_trait_type_specifier->first_method;
    if (parsed_method != NULL) {
        self->receiver_type = trait_receiver_type;
        Checked_Struct_Member *last_struct_member = trait_type->struct_type->first_member;
        Checked_Trait_Method *last_trait_method = NULL;
        for (; parsed_method != NULL; parsed_method = parsed_method->next_method) {
            Checked_Procedure_Type *procedure_type = Checker__check_procedure_type(self, parsed_method->location, parsed_method->first_parameter, parsed_method->return_type);
            Checked_Struct_Member *trait_method_struct_member = Checked_Struct_Member__create((Source_Location){}, parsed_method->name->lexeme, (Checked_Type *)Checked_Procedure_Pointer_Type__create((Source_Location){}, procedure_type));
            last_struct_member = last_struct_member->next_member = trait_method_struct_member;
            Checked_Trait_Method *trait_method = Checked_Trait_Method__create(parsed_method->location, parsed_method->name->lexeme, procedure_type, trait_method_struct_member);
            if (last_trait_method == NULL) {
                trait_type->first_method = trait_method;
            } else {
                last_trait_method->next_method = trait_method;
            }
            last_trait_method = trait_method;
        }
    }

    return (Checked_Named_Type *)trait_type;
}

Checked_Named_Type *Checker__check_union_type_statement(Checker *self, Token *type_name, Parsed_Union_Type_Specifier *parsed_union_type_specifier) {
    Checked_Named_Type *other_type = Checker__find_type(self, type_name->lexeme);
    if (other_type != NULL) {
        if (other_type->super.kind == CHECKED_TYPE_KIND__UNION && Source_Location__equals(other_type->super.location, type_name->location)) {
            /* Type checked already */
            return other_type;
        }
        pWriter__begin_location_message(stderr_writer, type_name->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Type redeclaration");
        pWriter__end_location_message(stderr_writer);
        if (other_type->super.location.source != NULL) {
            pWriter__begin_location_message(stderr_writer, other_type->super.location, WRITER_STYLE__WARNING);
            pWriter__write__cstring(stderr_writer, "Previous declaration here");
            pWriter__end_location_message(stderr_writer);
        }
        panic();
    }

    Checked_Union_Type *union_type = Checked_Union_Type__create(type_name->location, type_name->lexeme, self->checked_module);
    union_type->super.super.symbol = Checker__create_type_symbol(self, type_name->lexeme, (Checked_Named_Type *)union_type);

    // Each union has the nil variant
    Checked_Union_Variant *nil_variant = Checked_Union_Variant__create(type_name->location, (Checked_Type *)self->builtin_types->nil_type, 0);
    union_type->first_variant = nil_variant;

    Checked_Union_Variant *last_union_variant = union_type->first_variant;
    Parsed_Union_Variant *parsed_variant = parsed_union_type_specifier->first_variant;
    while (parsed_variant != NULL) {
        Checked_Type *union_variant_type = Checker__resolve_type(self, parsed_variant->type);
        if (Checked_Type__equals(union_variant_type, (Checked_Type *)union_type)) {
            pWriter__begin_location_message(stderr_writer, parsed_variant->type->location, WRITER_STYLE__ERROR);
            pWriter__write__cstring(stderr_writer, "Union variant cannot be of its own type");
            pWriter__end_location_message(stderr_writer);
            panic();
        }
        Checked_Type__append_dependencies((Checked_Type *)union_type, union_variant_type, parsed_variant->type->location, self);
        Checked_Union_Variant *union_variant = Checked_Union_Variant__create(parsed_variant->type->location, union_variant_type, last_union_variant->index + 1);
        last_union_variant = last_union_variant->next_variant = union_variant;
        parsed_variant = parsed_variant->next_variant;
    }

    union_type->variant_count = last_union_variant->index;

    return (Checked_Named_Type *)union_type;
}

Checked_Statement *Checker__check_statement(Checker *self, Parsed_Statement *parsed_statement);

Checked_Assignment_Statement *Checker__check_assignment_statement(Checker *self, Parsed_Assignment_Statement *parsed_statement) {
    Checked_Expression *object_expression = Checker__check_expression(self, parsed_statement->object_expression, NULL);
    if (!Checked_Expression__is_mutable(object_expression)) {
        pWriter__begin_location_message(stderr_writer, object_expression->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Cannot assign to immutable expression");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    Checked_Expression *value_expression = Checker__check_expression(self, parsed_statement->value_expression, object_expression->type);
    if (object_expression->type->kind == CHECKED_TYPE_KIND__UNION && !Checked_Type__equals(object_expression->type, value_expression->type)) {
        value_expression = (Checked_Expression *)Checker__make_union_expression(self, value_expression->location, (Checked_Union_Type *)object_expression->type, value_expression);
    }
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
    if (!Checked_Type__equals((Checked_Type *)self->builtin_types->nothing_type, expression->type)) {
        /* TODO: Source_Location__warning(expression->location, String__create_from("Unused result value")); */
    }
    return Checked_Expression_Statement__create(parsed_statement->super.location, expression);
}

Checked_If_Statement *Checker__check_if_statement(Checker *self, Parsed_If_Statement *parsed_statement) {
    Checked_Expression *condition_expression = Checker__check_expression(self, parsed_statement->condition_expression, (Checked_Type *)self->builtin_types->bool_type);
    Checker__require_same_type(self, (Checked_Type *)self->builtin_types->bool_type, condition_expression->type, condition_expression->location);
    Checked_Statement *true_statement;
    if (parsed_statement->variant_alias) {
        if (condition_expression->kind != CHECKED_EXPRESSION_KIND__IS_UNION_VARIANT) {
            pWriter__begin_location_message(stderr_writer, condition_expression->location, WRITER_STYLE__ERROR);
            pWriter__write__cstring(stderr_writer, "If condition cannot have a variant alias");
            pWriter__end_location_message(stderr_writer);
            panic();
        }
        Checked_Is_Union_Variant_Expression *is_union_variant_expression = (Checked_Is_Union_Variant_Expression *)condition_expression;
        if (is_union_variant_expression->is_not) {
            pWriter__begin_location_message(stderr_writer, is_union_variant_expression->super.location, WRITER_STYLE__ERROR);
            pWriter__write__cstring(stderr_writer, "If condition cannot have a variant alias");
            pWriter__end_location_message(stderr_writer);
            panic();
        }
        if (is_union_variant_expression->union_expression->kind != CHECKED_EXPRESSION_KIND__SYMBOL) {
            pWriter__begin_location_message(stderr_writer, is_union_variant_expression->union_expression->location, WRITER_STYLE__ERROR);
            pWriter__write__cstring(stderr_writer, "Only symbol expressions are currently supported in if-is-as statements");
            pWriter__end_location_message(stderr_writer);
            panic();
        }
        self->symbols = Checked_Symbols__create(self->symbols);
        Checked_Union_Switch_Variant_Symbol *variant_symbol = Checked_Union_Switch_Variant_Symbol__create(self->checked_module, parsed_statement->variant_alias->super.location, parsed_statement->variant_alias->super.lexeme, is_union_variant_expression->union_expression, is_union_variant_expression->union_variant);
        Checked_Symbols__append_symbol(self->symbols, (Checked_Symbol *)variant_symbol);
        true_statement = Checker__check_statement(self, parsed_statement->true_statement);
        self->symbols = self->symbols->parent;
    } else {
        true_statement = Checker__check_statement(self, parsed_statement->true_statement);
    }
    Checked_Statement *false_statement = NULL;
    if (parsed_statement->false_statement != NULL) {
        false_statement = Checker__check_statement(self, parsed_statement->false_statement);
    }
    return Checked_If_Statement__create(parsed_statement->super.location, condition_expression, true_statement, false_statement);
}

Checked_Loop_Statement *Checker__check_loop_statement(Checker *self, Parsed_Loop_Statement *parsed_statement) {
    Checked_Statement *body_statement = Checker__check_statement(self, parsed_statement->body_statement);
    return Checked_Loop_Statement__create(parsed_statement->super.location, body_statement);
}

Checked_Statement *Checker__check_return_statement(Checker *self, Parsed_Return_Statement *parsed_statement) {
    Checked_Expression *expression = NULL;
    if (parsed_statement->expression != NULL) {
        expression = Checker__check_expression(self, parsed_statement->expression, self->return_type);
        if (self->return_type->kind == CHECKED_TYPE_KIND__UNION && !Checked_Type__equals(self->return_type, expression->type)) {
            expression = (Checked_Expression *)Checker__make_union_expression(self, expression->location, (Checked_Union_Type *)self->return_type, expression);
        }
        Checker__require_same_type(self, self->return_type, expression->type, expression->location);
        Decomposed_Expression decomposed_expression = Checker__decompose_expression(self, expression);
        if (decomposed_expression.temp_statements != NULL) {
            // Wrap the return expression in a block statement
            Checked_Block_Statement *block_statement = Checked_Block_Statement__create(parsed_statement->super.location, decomposed_expression.temp_statements);
            Checked_Statements__append(block_statement->statements, (Checked_Statement *)Checked_Return_Statement__create(parsed_statement->super.location, decomposed_expression.expression));
            return (Checked_Statement *)block_statement;
        }
    } else if (self->return_type->kind != CHECKED_TYPE_KIND__NOTHING) {
        pWriter__begin_location_message(stderr_writer, parsed_statement->super.location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Missing return expression");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    return (Checked_Statement *)Checked_Return_Statement__create(parsed_statement->super.location, expression);
}

Checked_Union_Switch_Statement *Checker__check_union_switch_statement(Checker *self, Parsed_Switch_Statement *parsed_statement, Checked_Expression *union_expression, Checked_Union_Type *union_type);

Checked_Statement *Checker__check_switch_statement(Checker *self, Parsed_Switch_Statement *parsed_statement) {
    Checked_Expression *expression = Checker__check_expression(self, parsed_statement->expression, NULL);
    if (expression->type->kind == CHECKED_TYPE_KIND__UNION) {
        return (Checked_Statement *)Checker__check_union_switch_statement(self, parsed_statement, expression, (Checked_Union_Type *)expression->type);
    }
    if (expression->type->kind == CHECKED_TYPE_KIND__POINTER) {
        Checked_Type *pointed_type = ((Checked_Pointer_Type *)expression->type)->other_type;
        if (pointed_type->kind == CHECKED_TYPE_KIND__UNION) {
            return (Checked_Statement *)Checker__check_union_switch_statement(self, parsed_statement, expression, (Checked_Union_Type *)pointed_type);
        }
    }
    pWriter__begin_location_message(stderr_writer, expression->location, WRITER_STYLE__ERROR);
    pWriter__write__cstring(stderr_writer, "Switch doesn't support ");
    pWriter__write__checked_type(stderr_writer, expression->type);
    pWriter__write__cstring(stderr_writer, " expressions");
    pWriter__end_location_message(stderr_writer);
    panic();
}

Checked_Union_Switch_Statement *Checker__check_union_switch_statement(Checker *self, Parsed_Switch_Statement *parsed_statement, Checked_Expression *union_expression, Checked_Union_Type *union_type) {
    bool *variants_with_case = malloc(union_type->variant_count * sizeof(bool));
    Parsed_Switch_Case *parsed_switch_case = parsed_statement->first_case;
    Checked_Union_Switch_Case *first_union_switch_case = NULL;
    Checked_Union_Switch_Case *last_union_switch_case = NULL;
    Checked_Switch_Else *switch_else = NULL;
    for (; parsed_switch_case != NULL; parsed_switch_case = parsed_switch_case->next_case) {
        switch (parsed_switch_case->kind) {
        case PARSED_SWITCH_CASE_KIND__ELSE: {
            if (switch_else != NULL) {
                pWriter__begin_location_message(stderr_writer, parsed_switch_case->location, WRITER_STYLE__ERROR);
                pWriter__write__cstring(stderr_writer, "Switch statement already has an else case");
                pWriter__end_location_message(stderr_writer);
                panic();
            }
            switch_else = Checked_Switch_Else__create(parsed_switch_case->location, Checker__check_statement(self, parsed_switch_case->statement));
            break;
        }
        case PARSED_SWITCH_CASE_KIND__VARIANT: {
            if (switch_else != NULL) {
                pWriter__begin_location_message(stderr_writer, parsed_switch_case->location, WRITER_STYLE__ERROR);
                pWriter__write__cstring(stderr_writer, "Switch case cannot follow else case");
                pWriter__end_location_message(stderr_writer);
                panic();
            }
            Checked_Type *variant_type = Checker__resolve_type(self, parsed_switch_case->variant.type);
            Checked_Union_Variant *union_variant = union_type->first_variant;
            for (; union_variant != NULL; union_variant = union_variant->next_variant) {
                if (Checked_Type__equals(union_variant->type, variant_type)) {
                    break;
                }
            }
            if (union_variant == NULL) {
                pWriter__begin_location_message(stderr_writer, parsed_switch_case->variant.type->location, WRITER_STYLE__ERROR);
                pWriter__write__cstring(stderr_writer, "No ");
                pWriter__write__checked_type(stderr_writer, variant_type);
                pWriter__write__cstring(stderr_writer, " variant in ");
                pWriter__write__checked_type(stderr_writer, (Checked_Type *)union_type);
                pWriter__write__cstring(stderr_writer, " union");
                pWriter__end_location_message(stderr_writer);
                panic();
            }
            if (variants_with_case[union_variant->index]) {
                pWriter__begin_location_message(stderr_writer, parsed_switch_case->location, WRITER_STYLE__ERROR);
                pWriter__write__cstring(stderr_writer, "Duplicate case");
                pWriter__end_location_message(stderr_writer);
                panic();
            }
            variants_with_case[union_variant->index] = true;

            // Create and push switch case symbols
            self->symbols = Checked_Symbols__create(self->symbols);

            if (parsed_switch_case->variant.alias != NULL) {
                // Create a symbol for the union variant
                Checked_Union_Switch_Variant_Symbol *variant_symbol = Checked_Union_Switch_Variant_Symbol__create(self->checked_module, parsed_switch_case->variant.alias->super.location, parsed_switch_case->variant.alias->super.lexeme, union_expression, union_variant);
                Checked_Symbols__append_symbol(self->symbols, (Checked_Symbol *)variant_symbol);
            }

            Checked_Statement *union_switch_case_statement = Checker__check_statement(self, parsed_switch_case->statement);

            // Pop switch case symbols
            self->symbols = self->symbols->parent;

            Checked_Union_Switch_Case *union_switch_case = Checked_Union_Switch_Case__create(parsed_switch_case->variant.type->location, union_type, union_variant, union_switch_case_statement);
            if (first_union_switch_case == NULL) {
                first_union_switch_case = union_switch_case;
            } else {
                last_union_switch_case->next_union_switch_case = union_switch_case;
            }
            last_union_switch_case = union_switch_case;
            break;
        }
        default:
            pWriter__begin_location_message(stderr_writer, parsed_switch_case->location, WRITER_STYLE__ERROR);
            pWriter__write__cstring(stderr_writer, "Swicth case not supported with union type");
            pWriter__end_location_message(stderr_writer);
            panic();
            break;
        }
    }
    if (switch_else == NULL) {
        Checked_Union_Variant *union_variant = union_type->first_variant;
        for (; union_variant != NULL; union_variant = union_variant->next_variant) {
            if (!variants_with_case[union_variant->index]) {
                pWriter__begin_location_message(stderr_writer, parsed_statement->super.location, WRITER_STYLE__ERROR);
                pWriter__write__cstring(stderr_writer, "Missing case for ");
                pWriter__write__checked_type(stderr_writer, union_variant->type);
                pWriter__end_location_message(stderr_writer);
                panic();
            }
        }
    }
    free(variants_with_case);
    return Checked_Union_Switch_Statement__create(parsed_statement->super.location, union_expression, first_union_switch_case, switch_else);
}

Checked_Variable_Statement *Checker__check_variable_statement(Checker *self, Parsed_Variable_Statement *parsed_statement) {
    Checked_Type *variable_type = NULL;
    if (parsed_statement->type != NULL) {
        variable_type = Checker__resolve_type(self, parsed_statement->type);
    } else if (parsed_statement->expression == NULL) {
        pWriter__begin_location_message(stderr_writer, parsed_statement->super.super.location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Missing type");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    Checked_Expression *expression = NULL;
    if (parsed_statement->expression != NULL) {
        expression = Checker__check_expression(self, parsed_statement->expression, variable_type);
        if (variable_type == NULL) {
            switch (expression->type->kind) {
            case CHECKED_TYPE_KIND__NULL:
                pWriter__begin_location_message(stderr_writer, parsed_statement->expression->location, WRITER_STYLE__ERROR);
                pWriter__write__cstring(stderr_writer, "Cannot infer type from null expression");
                pWriter__end_location_message(stderr_writer);
                panic();
            default:
                break;
            }
            variable_type = expression->type;
        } else if (variable_type->kind == CHECKED_TYPE_KIND__UNION && !Checked_Type__equals(variable_type, expression->type)) {
            expression = (Checked_Expression *)Checker__make_union_expression(self, expression->location, (Checked_Union_Type *)variable_type, expression);
        } else {
            Checker__require_same_type(self, variable_type, expression->type, expression->location);
        }
    }
    bool is_global = self->symbols == self->global_symbols;
    Checked_Variable_Symbol *variable = Checked_Variable_Symbol__create(self->checked_module, parsed_statement->super.name->location, parsed_statement->super.name->lexeme, variable_type, is_global);
    Checked_Symbols__append_symbol(self->symbols, (Checked_Symbol *)variable);
    if (parsed_statement->is_external) {
        if (!is_global) {
            pWriter__begin_location_message(stderr_writer, parsed_statement->super.super.location, WRITER_STYLE__ERROR);
            pWriter__write__cstring(stderr_writer, "External variables can only be declared in the global scope");
            pWriter__end_location_message(stderr_writer);
            panic();
        }
        Checked_External_Symbol *external_symbol;
        if (parsed_statement->external_name != NULL) {
            external_symbol = Checked_External_Symbol__create(parsed_statement->external_name->super.location, parsed_statement->external_name->value, (Checked_Symbol *)variable);
            variable->external_name = parsed_statement->external_name->value;
        } else {
            external_symbol = Checked_External_Symbol__create(parsed_statement->super.name->location, parsed_statement->super.name->lexeme, (Checked_Symbol *)variable);
        }
        Checked_Symbols__append_symbol(self->global_symbols, (Checked_Symbol *)external_symbol);
    }
    return Checked_Variable_Statement__create(parsed_statement->super.super.location, variable, parsed_statement->is_external, expression);
}

Checked_While_Statement *Checker__check_while_statement(Checker *self, Parsed_While_Statement *parsed_statement) {
    Checked_Expression *condition_expression = Checker__check_expression(self, parsed_statement->condition_expression, (Checked_Type *)self->builtin_types->bool_type);
    Checker__require_same_type(self, (Checked_Type *)self->builtin_types->bool_type, condition_expression->type, condition_expression->location);
    Checked_Statement *body_statement = Checker__check_statement(self, parsed_statement->body_statement);
    return Checked_While_Statement__create(parsed_statement->super.location, condition_expression, body_statement);
}

Parsed_Named_Type *Parsed_Type__get_generic_dependency(Parsed_Type *self, Parsed_Type_Parameter *first_type_parameter) {
    switch (self->kind) {
    case PARSED_TYPE_KIND__NAMED: {
        Parsed_Named_Type *named_type = (Parsed_Named_Type *)self;
        // Check if the named type has a type argument that matches one of the type parameters
        Parsed_Type_Argument *type_argument = named_type->first_type_argument;
        while (type_argument != NULL) {
            if (type_argument->type->kind != PARSED_TYPE_KIND__NAMED) {
                todo("Check if type argument is the generic dependency itself");
            }
            Parsed_Named_Type *type_argument_type = (Parsed_Named_Type *)type_argument->type;
            Parsed_Type_Parameter *type_parameter = first_type_parameter;
            while (type_parameter != NULL) {
                if (String__equals_string(type_argument_type->name, type_parameter->name->lexeme)) {
                    // Found a matching type parameter
                    return named_type;
                }
                type_parameter = type_parameter->next_type_parameter;
            }
            type_argument = type_argument->next_type_argument;
        }
        return NULL;
    }
    case PARSED_TYPE_KIND__POINTER:
        return Parsed_Type__get_generic_dependency(((Parsed_Pointer_Type *)self)->other_type, first_type_parameter);
    default:
        todo("Check other parsed type kinds for generic dependencies");
    }
    return NULL;
}

void Checker__check_generic_procedure_declaration(Checker *self, Parsed_Procedure_Statement *parsed_statement) {
    if (parsed_statement->is_external) {
        pWriter__begin_location_message(stderr_writer, parsed_statement->super.super.location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "External procedures cannot have type parameters");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    if (!parsed_statement->is_method) {
        pWriter__begin_location_message(stderr_writer, parsed_statement->super.super.location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Type parameters can only be used in methods");
        pWriter__end_location_message(stderr_writer);
        panic();
    }

    Checked_Type *receiver_type;
    Parsed_Type *parsed_receiver_type = parsed_statement->first_parameter->type;
    if (parsed_receiver_type == NULL) {
        pWriter__begin_location_message(stderr_writer, parsed_statement->first_parameter->name->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Method must have a receiver type");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    Parsed_Named_Type *parsed_generic_type = Parsed_Type__get_generic_dependency(parsed_receiver_type, parsed_statement->first_type_parameter);
    if (parsed_generic_type == NULL) {
        receiver_type = Checker__resolve_type(self, parsed_receiver_type);
    } else {
        Parsed_Type_Argument *first_type_argument = parsed_generic_type->first_type_argument;
        parsed_generic_type->first_type_argument = NULL; // Remove type arguments temporarily
        receiver_type = Checker__resolve_type(self, parsed_receiver_type);
        parsed_generic_type->first_type_argument = first_type_argument; // Restore type arguments
    }

    String *symbol_name = String__create();
    String__append_mangled_type_name(symbol_name, receiver_type);
    String__append_cstring(symbol_name, "__");
    String__append_string(symbol_name, parsed_statement->super.name->lexeme);

    Checked_Generic_Procedure_Symbol *generic_procedure_symbol = Checked_Generic_Procedure_Symbol__create(self->checked_module, parsed_statement->super.super.location, symbol_name, receiver_type, parsed_statement);
    Checked_Symbols__append_symbol(self->symbols, (Checked_Symbol *)generic_procedure_symbol);

    Checker__append_method(self, receiver_type, (Checked_Symbol *)generic_procedure_symbol);
}

Checked_Procedure_Symbol *Checker__check_procedure_declaration(Checker *self, Parsed_Procedure_Statement *parsed_statement) {
    Checked_Procedure_Type *procedure_type = Checker__check_procedure_type(self, parsed_statement->super.super.location, parsed_statement->first_parameter, parsed_statement->return_type);

    String *symbol_name = String__create();
    Checked_Type *receiver_type = NULL;
    if (parsed_statement->is_method) {
        if (parsed_statement->is_external) {
            pWriter__begin_location_message(stderr_writer, parsed_statement->first_parameter->type->location, WRITER_STYLE__ERROR);
            pWriter__write__cstring(stderr_writer, "External procedures cannot have a receiver type");
            pWriter__end_location_message(stderr_writer);
            panic();
        }
        receiver_type = Checker__resolve_type(self, parsed_statement->first_parameter->type);
        String__append_mangled_type_name(symbol_name, receiver_type);
        String__append_cstring(symbol_name, "__");
    }
    String__append_string(symbol_name, parsed_statement->super.name->lexeme);

    Checked_Procedure_Symbol *procedure_symbol = Checked_Procedure_Symbol__create(self->checked_module, parsed_statement->super.name->location, symbol_name, parsed_statement->super.super.location, parsed_statement, procedure_type, receiver_type);
    Checked_Symbols__append_symbol(self->global_symbols, (Checked_Symbol *)procedure_symbol);

    if (parsed_statement->is_external) {
        Checked_Procedure_Parameter *procedure_parameter = procedure_type->first_parameter;
        while (procedure_parameter != NULL) {
            if (procedure_parameter->label != NULL) {
                pWriter__begin_location_message(stderr_writer, procedure_parameter->location, WRITER_STYLE__ERROR);
                pWriter__write__cstring(stderr_writer, "External procedures can have only anon parameters");
                pWriter__end_location_message(stderr_writer);
                panic();
            }
            procedure_parameter = procedure_parameter->next_parameter;
        }

        Checked_External_Symbol *external_symbol;
        if (parsed_statement->external_name != NULL) {
            external_symbol = Checked_External_Symbol__create(parsed_statement->external_name->super.location, parsed_statement->external_name->value, (Checked_Symbol *)procedure_symbol);
            procedure_symbol->external_name = parsed_statement->external_name->value;
        } else {
            external_symbol = Checked_External_Symbol__create(parsed_statement->super.name->location, parsed_statement->super.name->lexeme, (Checked_Symbol *)procedure_symbol);
        }
        Checked_Symbols__append_symbol(self->global_symbols, (Checked_Symbol *)external_symbol);
    }

    if (parsed_statement->is_method) {
        Checker__append_method(self, receiver_type, (Checked_Symbol *)procedure_symbol);
    }

    return procedure_symbol;
}

Checked_Statement *Checker__check_statement(Checker *self, Parsed_Statement *parsed_statement) {
    switch (parsed_statement->kind) {
    case PARSED_STATEMENT_KIND__ASSIGNMENT:
        return (Checked_Statement *)Checker__check_assignment_statement(self, (Parsed_Assignment_Statement *)parsed_statement);
    case PARSED_STATEMENT_KIND__BLOCK:
        return (Checked_Statement *)Checker__check_block_statement(self, (Parsed_Block_Statement *)parsed_statement);
    case PARSED_STATEMENT_KIND__BREAK:
        return (Checked_Statement *)Checker__check_break_statement(self, (Parsed_Break_Statement *)parsed_statement);
    case PARSED_STATEMENT_KIND__EXPRESSION:
        return (Checked_Statement *)Checker__check_expression_statement(self, (Parsed_Expression_Statement *)parsed_statement);
    case PARSED_STATEMENT_KIND__IF:
        return (Checked_Statement *)Checker__check_if_statement(self, (Parsed_If_Statement *)parsed_statement);
    case PARSED_STATEMENT_KIND__LOOP:
        return (Checked_Statement *)Checker__check_loop_statement(self, (Parsed_Loop_Statement *)parsed_statement);
    case PARSED_STATEMENT_KIND__RETURN:
        return Checker__check_return_statement(self, (Parsed_Return_Statement *)parsed_statement);
    case PARSED_STATEMENT_KIND__SWITCH:
        return Checker__check_switch_statement(self, (Parsed_Switch_Statement *)parsed_statement);
    case PARSED_STATEMENT_KIND__VARIABLE:
        return (Checked_Statement *)Checker__check_variable_statement(self, (Parsed_Variable_Statement *)parsed_statement);
    case PARSED_STATEMENT_KIND__WHILE:
        return (Checked_Statement *)Checker__check_while_statement(self, (Parsed_While_Statement *)parsed_statement);
    default:
        break;
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

void Checker__check_procedure_definition(Checker *self, Checked_Procedure_Symbol *procedure_symbol) {
    Checked_Procedure_Type *procedure_type = procedure_symbol->procedure_type;
    self->return_type = procedure_type->return_type;

    /* Create and push procedure symbols */
    self->symbols = Checked_Symbols__create(self->symbols);

    if (procedure_type->first_parameter != NULL) {
        /* Create a symbol for each procedure parameter */
        Checked_Procedure_Parameter *parameter = procedure_type->first_parameter;
        while (parameter != NULL) {
            Checked_Symbols__append_symbol(self->symbols, (Checked_Symbol *)Checked_Procedure_Parameter_Symbol__create(self->checked_module, parameter->location, parameter->name, parameter->type));
            parameter = parameter->next_parameter;
        }
    }

    /* Check statements */
    procedure_symbol->checked_statements = Checker__check_statements(self, procedure_symbol->parsed_procedure_statement->statements);

    /* Pop procedure symbols */
    self->symbols = self->symbols->parent;
}

void Checker__create_type_argument_symbols(Checker *self, Checked_Type_Argument *first_type_argument) {
    Checked_Type_Argument *type_argument = first_type_argument;
    while (type_argument != NULL) {
        Checked_Type_Argument_Symbol *type_argument_symbol = Checked_Type_Argument_Symbol__create(type_argument->location, type_argument->name, (Checked_Type *)self->builtin_types->type_type, type_argument->type);
        Checked_Symbols__append_symbol(self->symbols, (Checked_Symbol *)type_argument_symbol);
        type_argument = type_argument->next_type_argument;
    }
}

Checked_Procedure_Symbol *Checker__specialize_method(Checker *self, Checked_Generic_Procedure_Symbol *generic_procedure_symbol, Checked_Type_Argument *first_type_argument) {
    self->symbols = Checked_Symbols__create(self->symbols);
    Checker__create_type_argument_symbols(self, first_type_argument);

    Checked_Module *checked_module = self->checked_module;
    self->checked_module = generic_procedure_symbol->super.module;

    Checked_Procedure_Symbol *procedure_symbol = Checker__check_procedure_declaration(self, generic_procedure_symbol->parsed_procedure_statement);
    procedure_symbol->first_type_argument = first_type_argument;

    self->checked_module = checked_module;

    self->symbols = self->symbols->parent;

    return procedure_symbol;
}

Checked_Named_Type *Checker__check_type_statement(Checker *self, Parsed_Type_Statement *parsed_type_statement) {
    Token *type_name = parsed_type_statement->super.name;
    if (parsed_type_statement->first_type_parameter != NULL) {
        Checked_Generic_Type *generic_type = Checked_Generic_Type__create(type_name->location, type_name->lexeme, self->checked_module, parsed_type_statement);
        generic_type->super.super.symbol = Checker__create_type_symbol(self, type_name->lexeme, (Checked_Named_Type *)generic_type);
        return (Checked_Named_Type *)generic_type;
    }
    switch (parsed_type_statement->type_specifier->kind) {
    case PARSED_TYPE_SPECIFIER_KIND__BUILTIN:
        return Checker__check_builtin_type_statement(self, type_name);
    case PARSED_TYPE_SPECIFIER_KIND__EXTERNAL:
        return Checker__check_external_type_statement(self, type_name);
    case PARSED_TYPE_SPECIFIER_KIND__STRUCT:
        return Checker__check_struct_type_statement(self, type_name, (Parsed_Struct_Type_Specifier *)parsed_type_statement->type_specifier);
    case PARSED_TYPE_SPECIFIER_KIND__TRAIT:
        return Checker__check_trait_type_statement(self, type_name, (Parsed_Trait_Type_Specifier *)parsed_type_statement->type_specifier);
    case PARSED_TYPE_SPECIFIER_KIND__UNION:
        return Checker__check_union_type_statement(self, type_name, (Parsed_Union_Type_Specifier *)parsed_type_statement->type_specifier);
    default:
        pWriter__begin_location_message(stderr_writer, parsed_type_statement->type_specifier->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Unsupported type specifier");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
}

Checked_Type_Argument *Checker__check_type_arguments(Checker *self, Parsed_Type_Parameter *first_parsed_type_parameter, Parsed_Type_Argument *first_parsed_type_argument) {
    Checked_Type_Argument *first_type_argument = Checked_Type_Argument__create(first_parsed_type_parameter->name->location, first_parsed_type_parameter->name->lexeme, Checker__resolve_type(self, first_parsed_type_argument->type));
    Checked_Type_Argument *last_type_argument = first_type_argument;

    Parsed_Type_Parameter *parsed_type_parameter = first_parsed_type_parameter->next_type_parameter;
    Parsed_Type_Argument *parsed_type_argument = first_parsed_type_argument->next_type_argument;
    while (parsed_type_parameter != NULL && parsed_type_argument != NULL) {
        last_type_argument->next_type_argument = Checked_Type_Argument__create(parsed_type_parameter->name->location, parsed_type_parameter->name->lexeme, Checker__resolve_type(self, parsed_type_argument->type));
        last_type_argument = last_type_argument->next_type_argument;
        parsed_type_parameter = parsed_type_parameter->next_type_parameter;
        parsed_type_argument = parsed_type_argument->next_type_argument;
    }
    if (parsed_type_parameter != NULL) {
        todo("Report too few arguments")
    }
    if (parsed_type_argument != NULL) {
        todo("Report too many arguments")
    }

    return first_type_argument;
}

Checked_Named_Type *Checked_Symbols__find_specialized_type(Checked_Symbols *self, Checked_Generic_Type *generic_type, Checked_Type_Argument *first_type_argument) {
    Checked_Symbols *symbols = self;
    while (symbols != NULL) {
        Checked_Symbol *symbol = symbols->last_symbol;
        while (symbol != NULL) {
            if (symbol->kind == CHECKED_SYMBOL_KIND__TYPE) {
                Checked_Named_Type *type = ((Checked_Type_Symbol *)symbol)->named_type;
                if (type->generic_type == generic_type) {
                    Checked_Type_Argument *type_argument = type->first_type_argument;
                    Checked_Type_Argument *required_type_argument = first_type_argument;
                    while (type_argument != NULL && required_type_argument != NULL) {
                        if (!Checked_Type__equals(type_argument->type, required_type_argument->type)) {
                            break;
                        }
                        type_argument = type_argument->next_type_argument;
                        required_type_argument = required_type_argument->next_type_argument;
                    }
                    if (type_argument == NULL && required_type_argument == NULL) {
                        // Found a specialized type
                        return type;
                    }
                }
            }
            symbol = symbol->prev_symbol;
        }
        symbols = symbols->parent;
    }
    return NULL;
}

Checked_Named_Type *Checker__specialize_type(Checker *self, Checked_Generic_Type *generic_type, Parsed_Named_Type *parsed_type) {
    Checked_Type_Argument *first_type_argument = Checker__check_type_arguments(self, generic_type->parsed_type_statement->first_type_parameter, parsed_type->first_type_argument);

    Checked_Named_Type *type = Checked_Symbols__find_specialized_type(self->global_symbols, generic_type, first_type_argument);
    if (type != NULL) {
        // TODO: delete created types arguments
        return type;
    }

    String *type_name = String__create_copy(parsed_type->name);
    Writer *type_name_writer = String__create_writer(type_name);
    pWriter__write__char(type_name_writer, '<');
    Checked_Type_Argument *type_argument = first_type_argument;
    pWriter__write__checked_type(type_name_writer, type_argument->type);
    type_argument = type_argument->next_type_argument;
    while (type_argument != NULL) {
        pWriter__write__cstring(type_name_writer, ", ");
        pWriter__write__checked_type(type_name_writer, type_argument->type);
        type_argument = type_argument->next_type_argument;
    }
    pWriter__write__char(type_name_writer, '>');
    pWriter__destroy(type_name_writer);

    self->symbols = Checked_Symbols__create(self->symbols);
    Checker__create_type_argument_symbols(self, first_type_argument);

    Token *type_name_token = (Token *)Identifier_Token__create(parsed_type->super.location, type_name);
    Checked_Module *current_module = self->checked_module;
    self->checked_module = generic_type->super.module;
    switch (generic_type->parsed_type_statement->type_specifier->kind) {
    case PARSED_TYPE_SPECIFIER_KIND__STRUCT:
        type = Checker__check_struct_type_statement(self, type_name_token, (Parsed_Struct_Type_Specifier *)generic_type->parsed_type_statement->type_specifier);
        break;
    default:
        pWriter__begin_location_message(stderr_writer, parsed_type->super.location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Cannot specialize type ");
        pWriter__write__string(stderr_writer, generic_type->super.name);
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    self->checked_module = current_module;
    // TODO: delete type_name_token

    type->generic_type = generic_type;
    type->first_type_argument = first_type_argument;

    self->symbols = self->symbols->parent;

    return type;
}

void Checker__check_module(Checker *self);

Checked_Module *Checker__check_imported_module(Checker *self, Parsed_Source *parsed_source) {
    Checker module_checker;

    module_checker.parsed_source = parsed_source;

    module_checker.builtin_types = self->builtin_types;

    module_checker.global_symbols = module_checker.symbols = self->global_symbols;

    module_checker.modules = self->modules;

    module_checker.checked_module = Checked_Module__create(parsed_source->package_name, parsed_source->source);
    Checked_Modules__append(self->modules, module_checker.checked_module);

    module_checker.methods = self->methods;

    module_checker.receiver_type = NULL;
    module_checker.return_type = NULL;

    Checker__check_module(&module_checker);

    return module_checker.checked_module;
}

void Checker__check_import_statement(Checker *self, Parsed_Import_Statement *parsed_statement) {
    Checked_Symbol *symbol = Checked_Symbols__find_symbol(self->symbols, self->checked_module, parsed_statement->import_name);
    if (symbol != NULL) {
        pWriter__begin_location_message(stderr_writer, parsed_statement->super.location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Import symbol conflicts with existing symbol");
        pWriter__end_location_message(stderr_writer);
        panic();
    }

    Checked_Module *module = Checked_Modules__find(self->modules, parsed_statement->parsed_source->package_name);

    if (module == NULL) {
        module = Checker__check_imported_module(self, parsed_statement->parsed_source);
    }

    Checked_Import_Symbol *import_symbol = Checked_Import_Symbol__create(self->checked_module, parsed_statement->super.location, parsed_statement->import_name, (Checked_Type *)self->builtin_types->module_type, module);
    Checked_Symbols__append_symbol(self->symbols, (Checked_Symbol *)import_symbol);
}

void Checker__check_module(Checker *self) {
    Parsed_Statement *parsed_statement;

    /* Check all imported modules */
    parsed_statement = self->parsed_source->statements->first_statement;
    while (parsed_statement != NULL) {
        if (parsed_statement->kind == PARSED_STATEMENT_KIND__IMPORT) {
            Checker__check_import_statement(self, (Parsed_Import_Statement *)parsed_statement);
        }
        parsed_statement = parsed_statement->next_statement;
    }

    /* Check all declared types */
    parsed_statement = self->parsed_source->statements->first_statement;
    while (parsed_statement != NULL) {
        if (parsed_statement->kind == PARSED_STATEMENT_KIND__TYPE) {
            Checker__check_type_statement(self, (Parsed_Type_Statement *)parsed_statement);
        }
        parsed_statement = parsed_statement->next_statement;
    }

    /* Collect other declarations */
    parsed_statement = self->parsed_source->statements->first_statement;
    while (parsed_statement != NULL) {
        Checked_Statement *checked_statement = NULL;
        switch (parsed_statement->kind) {
        case PARSED_STATEMENT_KIND__TYPE:
        case PARSED_STATEMENT_KIND__IMPORT:
            /* ignored */
            break;
        case PARSED_STATEMENT_KIND__PROCEDURE:
            if (((Parsed_Procedure_Statement *)parsed_statement)->first_type_parameter != NULL) {
                Checker__check_generic_procedure_declaration(self, (Parsed_Procedure_Statement *)parsed_statement);
            } else {
                Checker__check_procedure_declaration(self, (Parsed_Procedure_Statement *)parsed_statement);
            }
            break;
        case PARSED_STATEMENT_KIND__VARIABLE:
            checked_statement = (Checked_Statement *)Checker__check_variable_statement(self, (Parsed_Variable_Statement *)parsed_statement);
            break;
        default:
            pWriter__begin_location_message(stderr_writer, parsed_statement->location, WRITER_STYLE__ERROR);
            pWriter__write__cstring(stderr_writer, "Unsupported statement");
            pWriter__end_location_message(stderr_writer);
            panic();
        }
        parsed_statement = parsed_statement->next_statement;
    }
}

void Checker__check_builtin_module(Checker *self, Parsed_Source *parsed_source) {
    Checker module_checker;

    module_checker.parsed_source = parsed_source;

    module_checker.builtin_types = self->builtin_types;

    module_checker.global_symbols = module_checker.symbols = self->builtin_types->symbols;

    module_checker.modules = self->modules;

    module_checker.checked_module = self->modules->builtin_module = Checked_Module__create(parsed_source->package_name, parsed_source->source);

    module_checker.methods = self->methods;

    module_checker.receiver_type = NULL;
    module_checker.return_type = NULL;

    Checker__check_module(&module_checker);
}

Checked_Source *check(Parsed_Source *parsed_builtin_source, Parsed_Source *parsed_source) {
    Checker *checker = Checker__create(parsed_source);
    Checker__check_builtin_module(checker, parsed_builtin_source);
    Checker__check_module(checker);

    /* Check procedure definitions from all modules */
    Checked_Symbol *symbol = checker->global_symbols->first_symbol;
    while (symbol != NULL) {
        if (symbol->kind == CHECKED_SYMBOL_KIND__PROCEDURE) {
            Checked_Procedure_Symbol *procedure_symbol = (Checked_Procedure_Symbol *)symbol;
            Parsed_Procedure_Statement *procedure_statement = procedure_symbol->parsed_procedure_statement;
            if (!procedure_statement->is_external) {
                if (procedure_statement->statements == NULL) {
                    pWriter__begin_location_message(stderr_writer, procedure_statement->super.name->location, WRITER_STYLE__ERROR);
                    pWriter__write__cstring(stderr_writer, "Missing procedure body");
                    pWriter__end_location_message(stderr_writer);
                    panic();
                }
                if (procedure_symbol->first_type_argument != NULL) {
                    checker->symbols = Checked_Symbols__create(checker->symbols);
                    Checker__create_type_argument_symbols(checker, procedure_symbol->first_type_argument);
                }
                // Checked_Module *current_module = checker->checked_module;
                checker->checked_module = procedure_symbol->super.module;
                Checker__check_procedure_definition(checker, procedure_symbol);
                // checker->checked_module = current_module;
                if (procedure_symbol->first_type_argument != NULL) {
                    checker->symbols = checker->symbols->parent;
                }
            } else if (procedure_statement->statements != NULL) {
                pWriter__begin_location_message(stderr_writer, procedure_statement->super.name->location, WRITER_STYLE__ERROR);
                pWriter__write__cstring(stderr_writer, "External procedure with body");
                pWriter__end_location_message(stderr_writer);
                panic();
            }
        }
        symbol = symbol->next_symbol;
    }

    Checked_Source *checked_source = (Checked_Source *)malloc(sizeof(Checked_Source));
    checked_source->first_module = checker->modules->first_module;
    checked_source->symbols = checker->global_symbols;

    return checked_source;
}
