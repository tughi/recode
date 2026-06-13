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
    Checked_Named_Type *package_type;
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

    builtin_types->package_type = Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__MODULE, sizeof(Checked_Named_Type), location, String__create_from("Module"), NULL);
    Checked_Symbols__append_symbol(builtin_types->symbols, (Checked_Symbol *)Checked_Type_Symbol__create(NULL, builtin_types->package_type->super.location, builtin_types->package_type->name, (Checked_Type *)builtin_types->type_type, builtin_types->package_type));

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
    Builtin_Types *builtin_types;

    Checked_Symbols *global_symbols;
    Checked_Symbols *symbols;

    Checked_Packages *packages;

    Checked_Methods *methods;
} Checker;

Checker *Checker__create(void) {
    Checker *checker = (Checker *)malloc(sizeof(Checker));

    checker->builtin_types = Builtin_Types__create();

    checker->global_symbols = checker->symbols = Checked_Symbols__create(checker->builtin_types->symbols);

    checker->packages = (Checked_Packages *)malloc(sizeof(Checked_Packages));
    checker->packages->builtin_package = NULL;
    checker->packages->first_package = NULL;
    checker->packages->last_package = NULL;

    checker->methods = (Checked_Methods *)malloc(sizeof(Checked_Methods));
    checker->methods->first_method = NULL;
    checker->methods->last_method = NULL;

    return checker;
}

typedef struct Checker_Context {
    Checked_Package *checked_package;

    Checked_Type *return_type;

    Checked_Type *receiver_type;

    bool allows_is_alias;
    bool is_deferred_statement;
    bool is_unreachable_statement;
} Checker_Context;

Checker_Context Checker_Context__make(Checker *checker, Checked_Package *package) {
    return (Checker_Context){
        .checked_package = package,
        .receiver_type = NULL,
        .allows_is_alias = false,
        .is_deferred_statement = false,
        .is_unreachable_statement = false,
    };
}

Checker_Context *Checker_Context__create(Checker *checker, Checked_Package *package) {
    Checker_Context *context = (Checker_Context *)malloc(sizeof(Checker_Context));
    *context = Checker_Context__make(checker, package);
    return context;
}

Checked_Package *Checker__create_package(Checker *self, Parsed_Package *parsed_package) {
    Checked_Package *package = Checked_Package__create(parsed_package);
    Checked_Packages__append(self->packages, package);
    if (self->packages->builtin_package != NULL) {
        Checked_Import_Symbol *builtin_import = Checked_Import_Symbol__create(package, (Source_Location){}, String__create_from("builtin"), (Checked_Type *)self->builtin_types->package_type, self->packages->builtin_package);
        Checked_Symbols__append_symbol(self->global_symbols, (Checked_Symbol *)builtin_import);
    }
    return package;
}

Checked_Type_Symbol *Checker__create_type_symbol(Checker *self, Checked_Package *package, String *symbol_name, Checked_Named_Type *type) {
    Checked_Type_Symbol *type_symbol = Checked_Type_Symbol__create(package, type->super.location, symbol_name, (Checked_Type *)self->builtin_types->type_type, type);
    Checked_Symbols__append_symbol(self->global_symbols, (Checked_Symbol *)type_symbol);
    return type_symbol;
}

Checked_Named_Type *Checked_Symbols__find_type(Checked_Symbols *symbols, Checked_Package *package, String *name) {
    while (symbols != NULL) {
        Checked_Symbol *symbol = symbols->last_symbol;
        while (symbol != NULL) {
            if (symbol->kind == CHECKED_SYMBOL_KIND__TYPE && String__equals_string(name, symbol->name)) {
                if (package == NULL || symbol->package == NULL || package == symbol->package) {
                    return ((Checked_Type_Symbol *)symbol)->named_type;
                }
            }
            symbol = symbol->prev_symbol;
        }
        symbols = symbols->parent;
    }
    return NULL;
}

Checked_Named_Type *Checker__find_type(Checker *self, Checker_Context *context, String *name) {
    Checked_Named_Type *type = Checked_Symbols__find_type(self->symbols, context->checked_package, name);
    if (type != NULL) {
        return type;
    }
    return Checked_Symbols__find_type(self->global_symbols->parent, NULL, name);
}

Checked_Named_Type *Checker__find_package_type(Checker *self, Checked_Package *package, String *name) {
    Checked_Symbol *symbol = self->global_symbols->first_symbol;
    while (symbol != NULL) {
        if (symbol->kind == CHECKED_SYMBOL_KIND__TYPE && symbol->package == package && String__equals_string(name, symbol->name)) {
            return ((Checked_Type_Symbol *)symbol)->named_type;
        }
        symbol = symbol->next_symbol;
    }
    return NULL;
}

Checked_Result_Type *Checker__find_result_type(Checker *self, Checker_Context *context, Checked_Type *return_type, Checked_Type *raise_type) {
    Checked_Symbol *symbol = self->global_symbols->last_symbol;
    while (symbol != NULL) {
        if (symbol->kind == CHECKED_SYMBOL_KIND__TYPE && symbol->package == context->checked_package) {
            Checked_Type_Symbol *type_symbol = (Checked_Type_Symbol *)symbol;
            if (type_symbol->named_type->super.kind == CHECKED_TYPE_KIND__RESULT) {
                Checked_Result_Type *result_type = (Checked_Result_Type *)type_symbol->named_type;
                if (Checked_Type__equals(result_type->return_type, return_type) && Checked_Type__equals(result_type->raise_type, raise_type)) {
                    return result_type;
                }
            }
        }
        symbol = symbol->prev_symbol;
    }
    return NULL;
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

bool Checked_Type__is_identical(Checked_Type *self, Checked_Type *other) {
    if (self == other) {
        return true;
    }
    if (self->kind != other->kind) {
        return false;
    }
    switch (self->kind) {
    case CHECKED_TYPE_KIND__MULTI_POINTER: {
        return Checked_Type__is_identical(((Checked_Multi_Pointer_Type *)self)->item_type, ((Checked_Multi_Pointer_Type *)other)->item_type);
    }
    case CHECKED_TYPE_KIND__POINTER: {
        return Checked_Type__is_identical(((Checked_Pointer_Type *)self)->other_type, ((Checked_Pointer_Type *)other)->other_type);
    }
    case CHECKED_TYPE_KIND__PROCEDURE_POINTER: {
        Checked_Procedure_Type *self_procedure_type = ((Checked_Procedure_Pointer_Type *)self)->procedure_type;
        Checked_Procedure_Type *other_procedure_type = ((Checked_Procedure_Pointer_Type *)other)->procedure_type;
        if (!Checked_Type__is_identical(self_procedure_type->return_type, other_procedure_type->return_type)) {
            return false;
        }
        Checked_Procedure_Parameter *self_parameter = self_procedure_type->first_parameter;
        Checked_Procedure_Parameter *other_parameter = other_procedure_type->first_parameter;
        while (self_parameter != NULL && other_parameter != NULL) {
            if (!Checked_Type__is_identical(self_parameter->type, other_parameter->type)) {
                return false;
            }
            self_parameter = self_parameter->next_parameter;
            other_parameter = other_parameter->next_parameter;
        }
        return self_parameter == NULL && other_parameter == NULL;
    }
    case CHECKED_TYPE_KIND__RESULT: {
        return false;
    }
    default:
        todo("Handle unexpected Checked_Type");
    }
}

Checked_Expression *Checker__check_expression(Checker *self, Checker_Context *context, Parsed_Expression *parsed_expression, Checked_Type *expected_type);

Checked_Named_Type *Checker__check_type_statement(Checker *self, Checker_Context *context, Parsed_Type_Statement *parsed_type_statement);

Checked_Named_Type *Checker__specialize_type(Checker *self, Checker_Context *context, Checked_Generic_Type *generic_type, Parsed_Named_Type *parsed_type);

void Checked_Type__append_dependencies(Checked_Type *self, Checked_Type *other, Source_Location location, Checker *checker);

Checked_Type *Checker__resolve_result_type(Checker *self, Checker_Context *context, Source_Location location, Checked_Type *return_type, Checked_Type *raise_type) {
    Checked_Result_Type *result_type = Checker__find_result_type(self, context, return_type, raise_type);
    if (result_type == NULL) {
        result_type = Checked_Result_Type__create(location, context->checked_package, return_type, raise_type);
        result_type->super.super.symbol = Checker__create_type_symbol(self, context->checked_package, result_type->super.name, (Checked_Named_Type *)result_type);
    }
    return (Checked_Type *)result_type;
}

Checked_Optional_Type *Checker__find_optional_type(Checker *self, Checker_Context *context, Checked_Type *inner_type) {
    Checked_Symbol *symbol = self->global_symbols->last_symbol;
    while (symbol != NULL) {
        if (symbol->kind == CHECKED_SYMBOL_KIND__TYPE) {
            Checked_Type_Symbol *type_symbol = (Checked_Type_Symbol *)symbol;
            if (type_symbol->named_type->super.kind == CHECKED_TYPE_KIND__OPTIONAL) {
                Checked_Optional_Type *optional_type = (Checked_Optional_Type *)type_symbol->named_type;
                if (Checked_Type__equals(optional_type->super.first_variant_case->next_variant->type, inner_type)) {
                    return optional_type;
                }
            }
        }
        symbol = symbol->prev_symbol;
    }
    return NULL;
}

Checked_Type *Checker__resolve_optional_type(Checker *self, Checker_Context *context, Source_Location location, Checked_Type *inner_type) {
    Checked_Optional_Type *optional_type = Checker__find_optional_type(self, context, inner_type);
    if (optional_type == NULL) {
        Checked_Package *optional_package = NULL;
        String *name = String__create();
        switch (inner_type->kind) {
        case CHECKED_TYPE_KIND__EXTERNAL:
        case CHECKED_TYPE_KIND__GENERIC:
        case CHECKED_TYPE_KIND__OPTIONAL:
        case CHECKED_TYPE_KIND__RESULT:
        case CHECKED_TYPE_KIND__STRUCT:
        case CHECKED_TYPE_KIND__TRAIT:
        case CHECKED_TYPE_KIND__VARIANT: {
            Checked_Named_Type *inner_named_type = (Checked_Named_Type *)inner_type;
            optional_package = inner_named_type->package;
            if (inner_named_type->generic_type != NULL) {
                String__append_string(name, inner_named_type->generic_type->super.name);
                Checked_Type_Argument *type_argument = inner_named_type->first_type_argument;
                while (type_argument != NULL) {
                    String__append_cstring(name, "__");
                    String__append_mangled_type_name(name, type_argument->type);
                    type_argument = type_argument->next_type_argument;
                }
            } else {
                String__append_string(name, inner_named_type->name);
            }
            break;
        }
        default:
            String__append_mangled_type_name(name, inner_type);
            break;
        }
        String__append_cstring(name, "__opt");
        optional_type = Checked_Optional_Type__create(location, optional_package, name);
        Checked_Variant_Case *nil_case = Checked_Variant_Case__create(location, (Checked_Type *)self->builtin_types->nil_type, 0);
        Checked_Variant_Case *value_case = Checked_Variant_Case__create(location, inner_type, 1);
        nil_case->next_variant = value_case;
        optional_type->super.first_variant_case = nil_case;
        optional_type->super.variant_count = 2;
        optional_type->super.super.super.symbol = Checker__create_type_symbol(self, optional_package, optional_type->super.super.name, (Checked_Named_Type *)optional_type);
        Checked_Type__append_dependencies((Checked_Type *)optional_type, inner_type, location, self);
    }
    return (Checked_Type *)optional_type;
}

Checked_Type *Checker__resolve_type(Checker *self, Checker_Context *context, Parsed_Type *parsed_type) {
    switch (parsed_type->kind) {
    case PARSED_TYPE_KIND__ARRAY: {
        Parsed_Array_Type *parsed_array_type = (Parsed_Array_Type *)parsed_type;
        Checked_Type *checked_item_type = Checker__resolve_type(self, context, parsed_array_type->item_type);
        return (Checked_Type *)Checked_Array_Type__create(parsed_type->location, checked_item_type, parsed_array_type->length_literal->value);
    }
    case PARSED_TYPE_KIND__PROCEDURE: {
        Parsed_Procedure_Type *parsed_procedure_type = (Parsed_Procedure_Type *)parsed_type;
        Checked_Procedure_Parameter *procedure_first_parameter = NULL;
        Parsed_Procedure_Parameter *parsed_parameter = parsed_procedure_type->first_parameter;
        if (parsed_parameter != NULL) {
            procedure_first_parameter = Checked_Procedure_Parameter__create(parsed_parameter->name->location, parsed_parameter->label ? parsed_parameter->label->lexeme : NULL, parsed_parameter->name->lexeme, Checker__resolve_type(self, context, parsed_parameter->type));
            Checked_Procedure_Parameter *procedure_last_parameter = procedure_first_parameter;
            parsed_parameter = parsed_parameter->next_parameter;
            while (parsed_parameter != NULL) {
                Checked_Procedure_Parameter *procedure_parameter = Checked_Procedure_Parameter__create(parsed_parameter->name->location, parsed_parameter->label ? parsed_parameter->label->lexeme : NULL, parsed_parameter->name->lexeme, Checker__resolve_type(self, context, parsed_parameter->type));
                procedure_last_parameter->next_parameter = procedure_parameter;
                procedure_last_parameter = procedure_parameter;
                parsed_parameter = parsed_parameter->next_parameter;
            }
        }
        Checked_Type *procedure_return_type;
        if (parsed_procedure_type->return_type == NULL) {
            procedure_return_type = (Checked_Type *)self->builtin_types->nothing_type;
        } else {
            procedure_return_type = Checker__resolve_type(self, context, parsed_procedure_type->return_type);
        }
        if (parsed_procedure_type->raise_type != NULL) {
            Checked_Type *procedure_raise_type = Checker__resolve_type(self, context, parsed_procedure_type->raise_type);
            procedure_return_type = Checker__resolve_result_type(self, context, parsed_procedure_type->return_type ? Source_Location__merge(parsed_procedure_type->return_type->location, parsed_procedure_type->raise_type->location) : parsed_procedure_type->raise_type->location, procedure_return_type, procedure_raise_type);
        }
        Checked_Procedure_Type *procedure_type = Checked_Procedure_Type__create(parsed_procedure_type->super.location, procedure_first_parameter, procedure_return_type);
        return (Checked_Type *)Checked_Procedure_Pointer_Type__create(parsed_type->location, procedure_type);
    }
    case PARSED_TYPE_KIND__MULTI_POINTER:
        return (Checked_Type *)Checked_Multi_Pointer_Type__create(parsed_type->location, Checker__resolve_type(self, context, ((Parsed_Multi_Pointer_Type *)parsed_type)->item_type));
    case PARSED_TYPE_KIND__NAMED: {
        Parsed_Named_Type *parsed_named_type = (Parsed_Named_Type *)parsed_type;
        Checked_Package *checked_type_package = context->checked_package;
        if (parsed_named_type->package != NULL) {
            Checked_Symbol *symbol = Checked_Symbols__find_symbol(self->global_symbols, context->checked_package, parsed_named_type->package->lexeme);
            if (symbol == NULL) {
                pWriter__begin_location_message(stderr_writer, parsed_named_type->package->location, WRITER_STYLE__ERROR);
                pWriter__write__cstring(stderr_writer, "Undefined package");
                pWriter__end_location_message(stderr_writer);
                panic();
            }
            if (symbol->kind != CHECKED_SYMBOL_KIND__IMPORT) {
                pWriter__begin_location_message(stderr_writer, parsed_named_type->package->location, WRITER_STYLE__ERROR);
                pWriter__write__cstring(stderr_writer, "Not a package");
                pWriter__end_location_message(stderr_writer);
                panic();
            }
            Checked_Import_Symbol *import_symbol = (Checked_Import_Symbol *)symbol;
            checked_type_package = import_symbol->other_package;
        }
        Checked_Named_Type *type = Checked_Symbols__find_type(self->global_symbols, checked_type_package, parsed_named_type->name);
        if (type == NULL) {
            type = Checked_Symbols__find_type(self->builtin_types->symbols, NULL, parsed_named_type->name);
        }
        if (type != NULL) {
            if (type->super.kind == CHECKED_TYPE_KIND__GENERIC) {
                if (parsed_named_type->first_type_argument != NULL) {
                    return (Checked_Type *)Checker__specialize_type(self, context, (Checked_Generic_Type *)type, parsed_named_type);
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
        Parsed_Module *parsed_module = checked_type_package->parsed_package->first_module;
        for (; parsed_module != NULL; parsed_module = parsed_module->next_module) {
            Parsed_Statement *parsed_statement = parsed_module->statements->first_statement;
            for (; parsed_statement != NULL; parsed_statement = parsed_statement->next_statement) {
                if (parsed_statement->kind == PARSED_STATEMENT_KIND__TYPE) {
                    Parsed_Type_Statement *parsed_type_statement = (Parsed_Type_Statement *)parsed_statement;
                    if (String__equals_string(parsed_type_statement->super.name->lexeme, parsed_named_type->name)) {
                        Checker_Context type_context = Checker_Context__make(self, checked_type_package);
                        return (Checked_Type *)Checker__check_type_statement(self, &type_context, parsed_type_statement);
                    }
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
    case PARSED_TYPE_KIND__OPTIONAL: {
        Parsed_Optional_Type *parsed_optional_type = (Parsed_Optional_Type *)parsed_type;
        Checked_Type *inner_type = Checker__resolve_type(self, context, parsed_optional_type->inner_type);
        return Checker__resolve_optional_type(self, context, parsed_type->location, inner_type);
    }
    case PARSED_TYPE_KIND__POINTER:
        return (Checked_Type *)Checked_Pointer_Type__create(parsed_type->location, Checker__resolve_type(self, context, ((Parsed_Pointer_Type *)parsed_type)->other_type));
    case PARSED_TYPE_KIND__RECEIVER:
        return context->receiver_type;
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
    if (actual_type->kind == CHECKED_TYPE_KIND__NULL) {
        if (expected_type->kind == CHECKED_TYPE_KIND__MULTI_POINTER) {
            return;
        }
        if (expected_type->kind == CHECKED_TYPE_KIND__POINTER) {
            return;
        }
        if (expected_type->kind == CHECKED_TYPE_KIND__PROCEDURE_POINTER) {
            return;
        }
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

Checked_Expression *Checker__assure_expression_pointer_type(Checker *self, Checked_Expression *expression, Checked_Pointer_Type *expected_pointer_type) {
    if (expression->type->kind == CHECKED_TYPE_KIND__POINTER) {
        Checked_Pointer_Type *expression_pointer_type = (Checked_Pointer_Type *)expression->type;
        if (expression_pointer_type->other_type != expected_pointer_type->other_type && expression_pointer_type->other_type->kind == CHECKED_TYPE_KIND__STRUCT && expected_pointer_type->other_type->kind == CHECKED_TYPE_KIND__STRUCT) {
            Checked_Struct_Type *expression_struct_type = (Checked_Struct_Type *)expression_pointer_type->other_type;
            Checked_Struct_Type *expected_struct_type = (Checked_Struct_Type *)expected_pointer_type->other_type;
            while (expression_struct_type->first_member != NULL && String__equals_cstring(expression_struct_type->first_member->name, "super")) {
                expression_struct_type = (Checked_Struct_Type *)expression_struct_type->first_member->type;
                if (expression_struct_type == expected_struct_type) {
                    return (Checked_Expression *)Checked_Cast_Expression__create(expression->location, (Checked_Type *)expected_pointer_type, expression);
                }
            }
        }
    }
    Checker__require_same_type(self, (Checked_Type *)expected_pointer_type, expression->type, expression->location);
    return expression;
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
    case CHECKED_TYPE_KIND__TRAIT: {
        return NULL;
    }
    default:
        todo("Handle other types for specialization check");
        break;
    }
    todo("Check if type is specialization");
}

Checked_Procedure_Symbol *Checker__specialize_method(Checker *self, Checker_Context *context, Checked_Generic_Procedure_Symbol *generic_procedure_symbol, Checked_Type_Argument *first_type_argument);

Checked_Procedure_Symbol *Checker__resolve_method_symbol(Checker *self, Checker_Context *context, Checked_Type *receiver_type, String *procedure_name, Parsed_Call_Argument *first_argument) {
    Checked_Method *method = self->methods->first_method;
    while (method != NULL) {
        switch (method->procedure_symbol->kind) {
        case CHECKED_SYMBOL_KIND__GENERIC_PROCEDURE: {
            Checked_Generic_Procedure_Symbol *generic_procedure_symbol = (Checked_Generic_Procedure_Symbol *)method->procedure_symbol;
            if (String__equals_string(generic_procedure_symbol->parsed_procedure_statement->super.name->lexeme, procedure_name)) {
                Checked_Type_Argument *first_type_argument = Checked_Type__is_specialization(receiver_type, generic_procedure_symbol->receiver_type);
                if (first_type_argument != NULL) {
                    return Checker__specialize_method(self, context, generic_procedure_symbol, first_type_argument);
                }
            }
            break;
        }
        case CHECKED_SYMBOL_KIND__PROCEDURE: {
            Checked_Procedure_Symbol *procedure_symbol = (Checked_Procedure_Symbol *)method->procedure_symbol;
            if (String__equals_string(procedure_symbol->procedure_name, procedure_name) && Checked_Type__equals(method->receiver_type, receiver_type)) {
                if (first_argument != NULL) {
                    Checked_Procedure_Parameter *procedure_parameter = procedure_symbol->procedure_type->first_parameter;
                    if (procedure_parameter == NULL) {
                        panic(); // Missing receiver parameter
                    }
                    procedure_parameter = procedure_parameter->next_parameter; // Skip receiver parameter
                    Parsed_Call_Argument *call_argument = first_argument;
                    bool labels_match = true;
                    while (labels_match && procedure_parameter != NULL && call_argument != NULL) {
                        if (procedure_parameter->label == NULL) {
                            if (call_argument->name != NULL) {
                                labels_match = false;
                            }
                        } else if (call_argument->name == NULL) {
                            labels_match = false;
                        } else {
                            labels_match = String__equals_string(procedure_parameter->label, call_argument->name->super.lexeme);
                        }
                        procedure_parameter = procedure_parameter->next_parameter;
                        call_argument = call_argument->next_argument;
                    }
                    if (!labels_match || procedure_parameter != NULL || call_argument != NULL) {
                        break;
                    }
                }
                return procedure_symbol;
            }
            break;
        }
        default:
            panic();
        }
        method = method->next_method;
    }
    if (receiver_type->kind == CHECKED_TYPE_KIND__POINTER) {
        Checked_Pointer_Type *pointer_type = (Checked_Pointer_Type *)receiver_type;
        if (pointer_type->other_type->kind == CHECKED_TYPE_KIND__STRUCT) {
            Checked_Struct_Type *struct_type = (Checked_Struct_Type *)pointer_type->other_type;
            if (struct_type->first_member != NULL && String__equals_cstring(struct_type->first_member->name, "super")) {
                Checked_Pointer_Type super_receiver_type = (Checked_Pointer_Type){
                    .super = {
                        .kind = CHECKED_TYPE_KIND__POINTER,
                        .location = receiver_type->location,
                    },
                    .other_type = struct_type->first_member->type,
                };
                return Checker__resolve_method_symbol(self, context, (Checked_Type *)&super_receiver_type, procedure_name, first_argument);
            }
        }
    }
    return NULL;
}

Checked_Procedure_Symbol *Checker__resolve_reference_method_symbol(Checker *self, Checker_Context *context, Checked_Type *receiver_type, String *procedure_name, Parsed_Call_Argument *first_argument) {
    Checked_Pointer_Type pointer_type = {
        .super = {
            .kind = CHECKED_TYPE_KIND__POINTER,
        },
        .other_type = receiver_type,
    };
    return Checker__resolve_method_symbol(self, context, (Checked_Type *)&pointer_type, procedure_name, first_argument);
}

Checked_Expression *Checker__check_add_expression(Checker *self, Checker_Context *context, Parsed_Add_Expression *parsed_expression, Checked_Type *expected_type) {
    Checked_Type *expected_numeric_type = expected_type && Checked_Type__is_numeric_type(expected_type) ? expected_type : NULL;
    Checked_Expression *left_expression = Checker__check_expression(self, context, parsed_expression->super.left_expression, expected_numeric_type);
    if (expected_numeric_type == NULL) {
        Checker__require_numeric_type(self, left_expression->type, left_expression->location);
    }
    Checked_Expression *right_expression = Checker__check_expression(self, context, parsed_expression->super.right_expression, left_expression->type);
    return (Checked_Expression *)Checked_Add_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

Checked_Expression *Checker__check_address_of_expression(Checker *self, Checker_Context *context, Parsed_Address_Of_Expression *parsed_expression) {
    Checked_Expression *other_expression = Checker__check_expression(self, context, parsed_expression->super.other_expression, NULL);
    if (!Checked_Expression__is_mutable(other_expression)) {
        pWriter__begin_location_message(stderr_writer, other_expression->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Cannot take address of this expression");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    return (Checked_Expression *)Checked_Address_Of_Expression__create(parsed_expression->super.super.location, (Checked_Type *)Checked_Pointer_Type__create(other_expression->location, other_expression->type), other_expression);
}

Checked_Expression *Checker__check_alloc_expression(Checker *self, Checker_Context *context, Parsed_Alloc_Expression *parsed_expression) {
    Checked_Expression *value_expression = Checker__check_expression(self, context, parsed_expression->value_expression, NULL);
    Checked_Type *value_type = value_expression->type;
    switch (value_type->kind) {
    case CHECKED_TYPE_KIND__STRUCT:
    case CHECKED_TYPE_KIND__TRAIT:
    case CHECKED_TYPE_KIND__VARIANT:
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

Checked_Expression *Checker__check_array_access_expression(Checker *self, Checker_Context *context, Parsed_Array_Access_Expression *parsed_expression) {
    Checked_Expression *array_expression = Checker__check_expression(self, context, parsed_expression->array_expression, NULL);
    Checked_Type *array_type = array_expression->type;
    Checked_Type *type;
    if (array_type->kind == CHECKED_TYPE_KIND__ARRAY) {
        type = ((Checked_Array_Type *)array_type)->item_type;
    } else if (array_type->kind == CHECKED_TYPE_KIND__MULTI_POINTER) {
        type = ((Checked_Pointer_Type *)array_type)->other_type;
    } else {
        pWriter__begin_location_message(stderr_writer, parsed_expression->array_expression->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Not an array");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    Checked_Expression *index_expression = Checker__check_expression(self, context, parsed_expression->index_expression, NULL);
    Checker__require_numeric_type(self, index_expression->type, index_expression->location);
    return (Checked_Expression *)Checked_Array_Access_Expression__create(parsed_expression->super.location, type, array_expression, index_expression);
}

Checked_Block_Statement *Checker__check_block_statement(Checker *self, Checker_Context *context, Parsed_Block_Statement *parsed_statement, Checked_Type *expected_type);

Checked_Expression *Checker__check_block_expression(Checker *self, Checker_Context *context, Parsed_Block_Expression *parsed_expression, Checked_Type *expected_type) {
    Checked_Block_Statement *block_statement = Checker__check_block_statement(self, context, parsed_expression->block_statement, expected_type);
    Checked_Block_Expression *block_expression = Checked_Block_Expression__create(parsed_expression->super.location, expected_type, (Checked_Statement *)block_statement);
    return (Checked_Expression *)block_expression;
}

Checked_Expression *Checker__check_bool_expression(Checker *self, Parsed_Bool_Expression *parsed_expression) {
    Checked_Type *expression_type = (Checked_Type *)self->builtin_types->bool_type;
    bool value = parsed_expression->value;
    return (Checked_Expression *)Checked_Bool_Expression__create(parsed_expression->super.super.location, expression_type, value);
}

Checked_Make_Variant_Expression *Checker__make_variant_expression(Checker *self, Source_Location location, Checked_Variant_Type *variant_type, Checked_Expression *expression) {
    Checked_Variant_Case *variant_case = variant_type->first_variant_case;
    if (expression->kind == CHECKED_EXPRESSION_KIND__SYMBOL) {
        // Check if this is the nil symbol
        Checked_Symbol *symbol = ((Checked_Symbol_Expression *)expression)->symbol;
        if (symbol->kind == CHECKED_SYMBOL_KIND__TYPE) {
            Checked_Type_Symbol *type_symbol = (Checked_Type_Symbol *)symbol;
            if (type_symbol->named_type == self->builtin_types->nil_type) {
                return Checked_Make_Variant_Expression__create(location, (Checked_Type *)variant_type, variant_type, variant_case, (Checked_Expression *)expression);
            }
        }
    }
    if (expression->type->kind == CHECKED_TYPE_KIND__NULL) {
        Checked_Variant_Case *nullable_variant_case = NULL;
        for (; variant_case != NULL; variant_case = variant_case->next_variant) {
            if (variant_case->type->kind == CHECKED_TYPE_KIND__POINTER || variant_case->type->kind == CHECKED_TYPE_KIND__MULTI_POINTER) {
                if (nullable_variant_case != NULL) {
                    pWriter__begin_location_message(stderr_writer, expression->location, WRITER_STYLE__ERROR);
                    pWriter__write__cstring(stderr_writer, "Too many variant cases accepting null value");
                    pWriter__end_location_message(stderr_writer);
                    panic();
                }
                nullable_variant_case = variant_case;
            }
        }
        variant_case = nullable_variant_case;
    } else {
        for (; variant_case != NULL; variant_case = variant_case->next_variant) {
            if (Checked_Type__equals(variant_case->type, expression->type)) {
                break;
            }
        }
    }
    if (variant_case == NULL) {
        pWriter__begin_location_message(stderr_writer, expression->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Variant type ");
        pWriter__write__checked_type(stderr_writer, (Checked_Type *)variant_type);
        pWriter__write__cstring(stderr_writer, " does not have ");
        pWriter__write__checked_type(stderr_writer, expression->type);
        pWriter__write__cstring(stderr_writer, " case");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    return Checked_Make_Variant_Expression__create(location, (Checked_Type *)variant_type, variant_type, variant_case, (Checked_Expression *)expression);
}

Checked_Expression *Checker__check_init_expression(Checker *self, Checker_Context *context, Checked_Named_Type *type, Parsed_Call_Argument *first_parsed_argument, Source_Location location);

String *Checker__build_mangled_callee_name(String *base_name, Parsed_Call_Argument *first_argument) {
    String *mangled_name = String__create();
    String__append_string(mangled_name, base_name);
    Parsed_Call_Argument *call_argument;
    for (call_argument = first_argument; call_argument != NULL; call_argument = call_argument->next_argument) {
        String__append_cstring(mangled_name, "__");
        if (call_argument->name != NULL) {
            String__append_string(mangled_name, call_argument->name->super.lexeme);
        } else {
            String__append_cstring(mangled_name, "anon");
        }
    }
    return mangled_name;
}

Checked_Expression *Checker__check_object_member_access(Checker *self, Checker_Context *context, Checked_Expression *object_expression, Token *member_name);

Checked_Expression *Checker__check_call_expression(Checker *self, Checker_Context *context, Parsed_Call_Expression *parsed_expression, bool unwarp_result) {
    Checked_Expression *callee_expression = NULL;
    if (parsed_expression->callee_expression->kind == PARSED_EXPRESSION_KIND__SYMBOL) {
        // Resolve callee using mangled name
        Parsed_Symbol_Expression *parsed_symbol_expression = (Parsed_Symbol_Expression *)parsed_expression->callee_expression;
        String *mangled_name = Checker__build_mangled_callee_name(parsed_symbol_expression->name->lexeme, parsed_expression->first_argument);
        Checked_Symbol *symbol = Checked_Symbols__find_symbol(self->symbols, context->checked_package, mangled_name);
        if (symbol == NULL) {
            symbol = Checked_Symbols__find_symbol(self->global_symbols->parent, self->packages->builtin_package, mangled_name);
        }
        String__delete(mangled_name);
        if (symbol != NULL && symbol->kind == CHECKED_SYMBOL_KIND__PROCEDURE) {
            callee_expression = (Checked_Expression *)Checked_Symbol_Expression__create(parsed_symbol_expression->super.location, symbol->type, symbol);
        }
    } else if (parsed_expression->callee_expression->kind == PARSED_EXPRESSION_KIND__MEMBER_ACCESS) {
        Parsed_Member_Access_Expression *parsed_member_access_expression = (Parsed_Member_Access_Expression *)parsed_expression->callee_expression;
        Checked_Expression *object_expression = Checker__check_expression(self, context, parsed_member_access_expression->object_expression, NULL);
        if (object_expression->type->kind == CHECKED_TYPE_KIND__MODULE) {
            // Resolve module callee using mangled name
            Checked_Symbol *import_symbol = ((Checked_Symbol_Expression *)object_expression)->symbol;
            if (import_symbol->kind == CHECKED_SYMBOL_KIND__IMPORT) {
                Checked_Package *package = ((Checked_Import_Symbol *)import_symbol)->other_package;
                String *mangled_name = Checker__build_mangled_callee_name(parsed_member_access_expression->member_name->lexeme, parsed_expression->first_argument);
                Checked_Symbol *symbol = Checked_Symbols__find_symbol(self->global_symbols, package, mangled_name);
                String__delete(mangled_name);
                if (symbol != NULL && symbol->kind == CHECKED_SYMBOL_KIND__PROCEDURE) {
                    callee_expression = (Checked_Expression *)Checked_Symbol_Expression__create(parsed_member_access_expression->super.location, symbol->type, symbol);
                }
            }
        } else {
            // Resolve method call using mangled name
            Checked_Type *object_type = object_expression->type;
            Checked_Procedure_Symbol *procedure_symbol = Checker__resolve_method_symbol(self, context, object_type, parsed_member_access_expression->member_name->lexeme, parsed_expression->first_argument);
            if (procedure_symbol == NULL && object_type->kind != CHECKED_TYPE_KIND__POINTER) {
                procedure_symbol = Checker__resolve_reference_method_symbol(self, context, object_type, parsed_member_access_expression->member_name->lexeme, parsed_expression->first_argument);
                if (procedure_symbol != NULL) {
                    object_type = (Checked_Type *)Checked_Pointer_Type__create(object_type->location, object_type);
                    object_expression = (Checked_Expression *)Checked_Address_Of_Expression__create(object_expression->location, object_type, object_expression);
                }
            }
            if (procedure_symbol != NULL) {
                Checked_Symbol_Expression *procedure_sym_expression = Checked_Symbol_Expression__create(parsed_member_access_expression->member_name->location, procedure_symbol->super.type, (Checked_Symbol *)procedure_symbol);
                callee_expression = (Checked_Expression *)Checked_Receiver_Method_Expression__create(parsed_member_access_expression->super.location, procedure_symbol->procedure_type->return_type, object_expression, (Checked_Expression *)procedure_sym_expression, procedure_symbol->procedure_type);
            }
        }
        if (callee_expression == NULL) {
            callee_expression = Checker__check_object_member_access(self, context, object_expression, parsed_member_access_expression->member_name);
        }
    }
    if (callee_expression == NULL) {
        callee_expression = Checker__check_expression(self, context, parsed_expression->callee_expression, NULL);
    }

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
            return Checker__check_init_expression(self, context, ((Checked_Type_Symbol *)callee_symbol)->named_type, parsed_expression->first_argument, parsed_expression->super.location);
        case CHECKED_SYMBOL_KIND__PROCEDURE_PARAMETER: {
            Checked_Type *parameter_type = callee_symbol->type;
            if (parameter_type->kind != CHECKED_TYPE_KIND__PROCEDURE_POINTER) {
                pWriter__begin_location_message(stderr_writer, callee_expression->location, WRITER_STYLE__ERROR);
                pWriter__write__cstring(stderr_writer, "Not a procedure pointer");
                pWriter__end_location_message(stderr_writer);
                panic();
            }
            procedure_type = ((Checked_Procedure_Pointer_Type *)parameter_type)->procedure_type;
            procedure_expression = callee_expression;
            receiver_expression = NULL;
            break;
        }
        case CHECKED_SYMBOL_KIND__VARIABLE: {
            Checked_Type *variable_type = callee_symbol->type;
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
        return Checker__check_init_expression(self, context, type_expression->named_type, parsed_expression->first_argument, parsed_expression->super.location);
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
            if (procedure_parameter->type->kind == CHECKED_TYPE_KIND__POINTER) {
                receiver_expression = Checker__assure_expression_pointer_type(self, receiver_expression, (Checked_Pointer_Type *)procedure_parameter->type);
            } else {
                Checker__require_same_type(self, procedure_parameter->type, receiver_expression->type, receiver_expression->location);
            }
            first_argument = last_argument = Checked_Call_Argument__create(receiver_expression, procedure_parameter->type);
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
            Checked_Expression *argument_expression = Checker__check_expression(self, context, parsed_argument->expression, procedure_parameter->type);
            if (!Checked_Type__is_identical(procedure_parameter->type, argument_expression->type)) {
                argument_expression = (Checked_Expression *)Checked_Cast_Expression__create(argument_expression->location, procedure_parameter->type, argument_expression);
            }
            Checked_Call_Argument *argument = Checked_Call_Argument__create(argument_expression, procedure_parameter->type);
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
            pWriter__begin_location_message(stderr_writer, procedure_expression->location, WRITER_STYLE__ERROR);
            pWriter__write__cstring(stderr_writer, "Too few arguments");
            pWriter__end_location_message(stderr_writer);
            panic();
        }
        if (parsed_argument != NULL) {
            pWriter__begin_location_message(stderr_writer, parsed_argument->expression->location, WRITER_STYLE__ERROR);
            pWriter__write__cstring(stderr_writer, "Too many arguments");
            pWriter__end_location_message(stderr_writer);
            panic();
        }
    }

    Checked_Call_Expression *call_expression = Checked_Call_Expression__create(parsed_expression->super.location, procedure_type->return_type, procedure_expression, first_argument);
    if (unwarp_result && call_expression->super.type->kind == CHECKED_TYPE_KIND__RESULT) {
        Checked_Result_Type *result_type = (Checked_Result_Type *)call_expression->super.type;
        if (context->return_type->kind != CHECKED_TYPE_KIND__RESULT || !Checked_Type__equals(result_type->raise_type, ((Checked_Result_Type *)context->return_type)->raise_type)) {
            pWriter__begin_location_message(stderr_writer, parsed_expression->super.location, WRITER_STYLE__ERROR);
            pWriter__write__cstring(stderr_writer, "Cannot unwrap result because ");
            pWriter__write__checked_type(stderr_writer, result_type->raise_type);
            pWriter__write__cstring(stderr_writer, " cannot be raised here");
            pWriter__end_location_message(stderr_writer);
            panic();
        }
        return (Checked_Expression *)Checked_Unwrap_Result_Expression__create(parsed_expression->super.location, result_type->return_type, call_expression);
    }
    return (Checked_Expression *)call_expression;
}

Checked_Expression *Checker__check_cast_expression(Checker *self, Checker_Context *context, Parsed_Cast_Expression *parsed_expression) {
    Checked_Type *expression_type = Checker__resolve_type(self, context, parsed_expression->type);
    Checked_Expression *other_expression = Checker__check_expression(self, context, parsed_expression->super.other_expression, NULL);
    Checked_Type *other_expression_type = other_expression->type;
    bool can_cast = false;
    if (expression_type->kind == CHECKED_TYPE_KIND__POINTER) {
        Checked_Pointer_Type *expression_pointer_type = (Checked_Pointer_Type *)expression_type;
        if (other_expression_type->kind == CHECKED_TYPE_KIND__NULL) {
            can_cast = true;
        } else if (other_expression_type->kind == CHECKED_TYPE_KIND__POINTER) {
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
    return (Checked_Expression *)Checked_Character_Expression__create(parsed_expression->super.super.location, expression_type, value, parsed_expression->super.literal);
}

Checked_Expression *Checker__check_dereference_expression(Checker *self, Checker_Context *context, Parsed_Dereference_Expression *parsed_expression) {
    Checked_Expression *other_expression = Checker__check_expression(self, context, parsed_expression->super.other_expression, NULL);
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

Checked_Expression *Checker__check_divide_expression(Checker *self, Checker_Context *context, Parsed_Divide_Expression *parsed_expression, Checked_Type *expected_type) {
    Checked_Type *expected_numeric_type = expected_type && Checked_Type__is_numeric_type(expected_type) ? expected_type : NULL;
    Checked_Expression *left_expression = Checker__check_expression(self, context, parsed_expression->super.left_expression, expected_numeric_type);
    if (expected_numeric_type == NULL) {
        Checker__require_numeric_type(self, left_expression->type, left_expression->location);
    }
    Checked_Expression *right_expression = Checker__check_expression(self, context, parsed_expression->super.right_expression, left_expression->type);
    return (Checked_Expression *)Checked_Divide_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

Checked_Expression *Checker__check_equals_expression(Checker *self, Checker_Context *context, Parsed_Equals_Expression *parsed_expression) {
    Checked_Expression *left_expression = Checker__check_expression(self, context, parsed_expression->super.left_expression, NULL);
    Checked_Expression *right_expression = Checker__check_expression(self, context, parsed_expression->super.right_expression, left_expression->type);
    return (Checked_Expression *)Checked_Equals_Expression__create(parsed_expression->super.super.location, (Checked_Type *)self->builtin_types->bool_type, left_expression, right_expression);
}

Checked_Expression *Checker__check_greater_expression(Checker *self, Checker_Context *context, Parsed_Greater_Expression *parsed_expression, Checked_Type *expected_type) {
    Checked_Type *expected_numeric_type = expected_type && Checked_Type__is_numeric_type(expected_type) ? expected_type : NULL;
    Checked_Expression *left_expression = Checker__check_expression(self, context, parsed_expression->super.left_expression, expected_numeric_type);
    if (expected_numeric_type == NULL) {
        Checker__require_numeric_type(self, left_expression->type, left_expression->location);
    }
    Checked_Expression *right_expression = Checker__check_expression(self, context, parsed_expression->super.right_expression, left_expression->type);
    return (Checked_Expression *)Checked_Greater_Expression__create(parsed_expression->super.super.location, (Checked_Type *)self->builtin_types->bool_type, left_expression, right_expression);
}

Checked_Expression *Checker__check_greater_or_equals_expression(Checker *self, Checker_Context *context, Parsed_Greater_Or_Equals_Expression *parsed_expression, Checked_Type *expected_type) {
    Checked_Type *expected_numeric_type = expected_type && Checked_Type__is_numeric_type(expected_type) ? expected_type : NULL;
    Checked_Expression *left_expression = Checker__check_expression(self, context, parsed_expression->super.left_expression, expected_numeric_type);
    if (expected_numeric_type == NULL) {
        Checker__require_numeric_type(self, left_expression->type, left_expression->location);
    }
    Checked_Expression *right_expression = Checker__check_expression(self, context, parsed_expression->super.right_expression, left_expression->type);
    return (Checked_Expression *)Checked_Greater_Or_Equals_Expression__create(parsed_expression->super.super.location, (Checked_Type *)self->builtin_types->bool_type, left_expression, right_expression);
}

Checked_Expression *Checker__check_group_expression(Checker *self, Checker_Context *context, Parsed_Group_Expression *parsed_expression, Checked_Type *expected_type) {
    Checked_Expression *other_expression = Checker__check_expression(self, context, parsed_expression->other_expression, expected_type);
    return (Checked_Expression *)Checked_Group_Expression__create(parsed_expression->super.location, other_expression->type, other_expression);
}

Checked_Expression *Checker__check_init_struct_expression(Checker *self, Checker_Context *context, Checked_Struct_Type *struct_type, Parsed_Call_Argument *first_parsed_argument, Source_Location location) {
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
            } else if (struct_member->struct_type != struct_type) {
                pWriter__begin_location_message(stderr_writer, parsed_argument->location, WRITER_STYLE__ERROR);
                pWriter__write__cstring(stderr_writer, "Super struct member must be initialized in super member");
                pWriter__end_location_message(stderr_writer);
                panic();
            }
            Checked_Expression *argument_expression = Checker__check_expression(self, context, parsed_argument->expression, struct_member->type);
            Checked_Make_Struct_Argument *argument = first_checked_argument;
            while (argument != NULL) {
                if (argument->struct_member == struct_member) {
                    pWriter__begin_location_message(stderr_writer, parsed_argument->location, WRITER_STYLE__ERROR);
                    pWriter__write__cstring(stderr_writer, "Struct member already initialized here: ");
                    pWriter__write__location(stderr_writer, argument->location);
                    pWriter__end_location_message(stderr_writer);
                    panic();
                }
                argument = argument->next_argument;
            }
            if (!Checked_Type__is_identical(struct_member->type, argument_expression->type)) {
                argument_expression = (Checked_Expression *)Checked_Cast_Expression__create(argument_expression->location, struct_member->type, argument_expression);
            }
            argument = Checked_Make_Struct_Argument__create(Source_Location__merge(parsed_argument->name->super.location, argument_expression->location), struct_member, argument_expression);
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

Checked_Expression *Checker__make_trait_expression(Checker *self, Checker_Context *context, Source_Location location, Checked_Trait_Type *trait_type, Checked_Expression *expression) {
    Checked_Expression *self_expression = expression;
    if (self_expression->type->kind != CHECKED_TYPE_KIND__POINTER) {
        self_expression = (Checked_Expression *)Checked_Address_Of_Expression__create(expression->location, (Checked_Type *)Checked_Pointer_Type__create(expression->location, self_expression->type), self_expression);
    }

    Checked_Type *self_type = ((Checked_Pointer_Type *)self_expression->type)->other_type;

    Checked_Expression *self_argument_expression = (Checked_Expression *)Checked_Cast_Expression__create(self_expression->location, trait_type->self_struct_member->type, self_expression);
    Checked_Make_Struct_Argument *first_make_struct_argument = Checked_Make_Struct_Argument__create(self_expression->location, trait_type->self_struct_member, self_argument_expression);

    Checked_Make_Struct_Argument *last_make_struct_argument = first_make_struct_argument;
    Checked_Trait_Method *trait_method;
    for (trait_method = trait_type->first_method; trait_method != NULL; trait_method = trait_method->next_method) {
        Checked_Type *saved_first_parameter_type = trait_method->procedure_type->first_parameter->type;
        trait_method->procedure_type->first_parameter->type = self_expression->type;
        Checked_Procedure_Symbol *procedure_symbol = Checker__resolve_method_symbol(self, context, self_expression->type, trait_method->name, NULL);
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
        }
        trait_method->procedure_type->first_parameter->type = saved_first_parameter_type;
        Checked_Symbol_Expression *procedure_symbol_expression = Checked_Symbol_Expression__create(location, procedure_symbol->super.type, (Checked_Symbol *)procedure_symbol);
        Checked_Cast_Expression *trait_struct_member_argument_expression = Checked_Cast_Expression__create(location, trait_method->struct_member->type, (Checked_Expression *)procedure_symbol_expression);
        last_make_struct_argument = last_make_struct_argument->next_argument = Checked_Make_Struct_Argument__create(location, trait_method->struct_member, (Checked_Expression *)trait_struct_member_argument_expression);
    }

    return (Checked_Expression *)Checked_Make_Struct_Expression__create(location, (Checked_Type *)trait_type, trait_type->struct_type, first_make_struct_argument);
}

Checked_Expression *Checker__check_init_trait_expression(Checker *self, Checker_Context *context, Checked_Trait_Type *trait_type, Parsed_Call_Argument *first_parsed_argument, Source_Location location) {
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

    Checked_Expression *self_expression = Checker__check_expression(self, context, parsed_argument->expression, NULL);
    return Checker__make_trait_expression(self, context, location, trait_type, self_expression);
}

Checked_Expression *Checker__check_init_variant_expression(Checker *self, Checker_Context *context, Checked_Variant_Type *variant_type, Parsed_Call_Argument *first_parsed_argument, Source_Location location) {
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

    Checked_Expression *variant_expression = Checker__check_expression(self, context, parsed_argument->expression, NULL);
    return (Checked_Expression *)Checker__make_variant_expression(self, location, variant_type, variant_expression);
}

Checked_Expression *Checker__check_init_expression(Checker *self, Checker_Context *context, Checked_Named_Type *type, Parsed_Call_Argument *first_parsed_argument, Source_Location location) {
    switch (type->super.kind) {
    case CHECKED_TYPE_KIND__STRUCT:
        return Checker__check_init_struct_expression(self, context, (Checked_Struct_Type *)type, first_parsed_argument, location);
    case CHECKED_TYPE_KIND__TRAIT:
        return Checker__check_init_trait_expression(self, context, (Checked_Trait_Type *)type, first_parsed_argument, location);
    case CHECKED_TYPE_KIND__OPTIONAL:
    case CHECKED_TYPE_KIND__VARIANT:
        return Checker__check_init_variant_expression(self, context, (Checked_Variant_Type *)type, first_parsed_argument, location);
    default:
        pWriter__begin_location_message(stderr_writer, location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Cannot initialize ");
        pWriter__write__checked_type(stderr_writer, (Checked_Type *)type);
        pWriter__write__cstring(stderr_writer, " value");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
}

Checked_Expression *Checker__check_integer_expression(Checker *self, Checker_Context *context, Parsed_Integer_Expression *parsed_expression, Checked_Type *expected_type) {
    Checked_Type *expression_type = NULL;
    if (parsed_expression->type != NULL) {
        expression_type = Checker__resolve_type(self, context, (Parsed_Type *)parsed_expression->type);
    } else if (expected_type != NULL) {
        expression_type = expected_type;
    }
    if (expression_type == NULL) {
        expression_type = (Checked_Type *)self->builtin_types->i32_type;
    }
    uint64_t expression_value = parsed_expression->value;
    int32_t expression_base = parsed_expression->base;
    return (Checked_Expression *)Checked_Integer_Expression__create(parsed_expression->super.super.location, expression_type, expression_value, expression_base, parsed_expression->super.literal);
}

Checked_Type *Checker__resolve_match_case_type(Checker *self, Checker_Context *context, Parsed_Type *parsed_type, bool through_pointer, Checked_Type **alias_type, bool *by_pointer) {
    Checked_Type *runtime_type = Checker__resolve_type(self, context, parsed_type);
    *alias_type = runtime_type;
    *by_pointer = false;
    if (through_pointer) {
        if (runtime_type->kind != CHECKED_TYPE_KIND__POINTER) {
            pWriter__begin_location_message(stderr_writer, parsed_type->location, WRITER_STYLE__ERROR);
            pWriter__write__cstring(stderr_writer, "A pointer-to-variant case must be a pointer type, such as ^");
            pWriter__write__checked_type(stderr_writer, runtime_type);
            pWriter__end_location_message(stderr_writer);
            panic();
        }
        *by_pointer = true;
        return ((Checked_Pointer_Type *)runtime_type)->other_type;
    }
    return runtime_type;
}

Checked_Expression *Checker__check_is_expression(Checker *self, Checker_Context *context, Parsed_Is_Expression *parsed_expression) {
    Checked_Expression *value_expression = Checker__check_expression(self, context, parsed_expression->value_expression, NULL);
    Checked_Type *value_type = value_expression->type;
    Checked_Type *matched_type = value_type;
    bool through_pointer = false;
    if (value_type->kind == CHECKED_TYPE_KIND__POINTER) {
        Checked_Type *pointed_type = ((Checked_Pointer_Type *)value_type)->other_type;
        if (pointed_type->kind == CHECKED_TYPE_KIND__OPTIONAL || pointed_type->kind == CHECKED_TYPE_KIND__VARIANT) {
            matched_type = pointed_type;
            through_pointer = true;
        }
    }
    Checked_Type *alias_type;
    bool case_by_pointer;
    Checked_Type *case_type = Checker__resolve_match_case_type(self, context, parsed_expression->runtime_type, through_pointer, &alias_type, &case_by_pointer);
    switch (matched_type->kind) {
    case CHECKED_TYPE_KIND__OPTIONAL:
    case CHECKED_TYPE_KIND__VARIANT: {
        Checked_Variant_Type *variant_type = (Checked_Variant_Type *)matched_type;
        Checked_Variant_Case *variant_case = variant_type->first_variant_case;
        for (; variant_case != NULL; variant_case = variant_case->next_variant) {
            if (Checked_Type__equals(variant_case->type, case_type)) {
                Checked_Variant_Alias_Symbol *alias_symbol = NULL;
                if (parsed_expression->alias != NULL) {
                    if (parsed_expression->is_not) {
                        pWriter__begin_location_message(stderr_writer, parsed_expression->super.location, WRITER_STYLE__ERROR);
                        pWriter__write__cstring(stderr_writer, "An 'is not' expression cannot declare an alias");
                        pWriter__end_location_message(stderr_writer);
                        panic();
                    }
                    if (!context->allows_is_alias) {
                        pWriter__begin_location_message(stderr_writer, parsed_expression->alias->super.location, WRITER_STYLE__ERROR);
                        pWriter__write__cstring(stderr_writer, "Variant aliases can be declared only in if and while conditions");
                        pWriter__end_location_message(stderr_writer);
                        panic();
                    }
                    if (!through_pointer) {
                        switch (value_expression->kind) {
                        case CHECKED_EXPRESSION_KIND__ARRAY_ACCESS:
                        case CHECKED_EXPRESSION_KIND__DEREFERENCE:
                        case CHECKED_EXPRESSION_KIND__MEMBER_ACCESS:
                        case CHECKED_EXPRESSION_KIND__SYMBOL:
                            break;
                        default:
                            pWriter__begin_location_message(stderr_writer, value_expression->location, WRITER_STYLE__ERROR);
                            pWriter__write__cstring(stderr_writer, "Variant aliases require an addressable expression");
                            pWriter__end_location_message(stderr_writer);
                            panic();
                        }
                    }
                    bool alias_is_mutable = case_by_pointer ? false : Checked_Expression__is_mutable(value_expression);
                    alias_symbol = Checked_Variant_Alias_Symbol__create(context->checked_package, parsed_expression->alias->super.location, parsed_expression->alias->super.lexeme, alias_type, alias_is_mutable, case_by_pointer);
                    Checked_Symbols__append_symbol(self->symbols, (Checked_Symbol *)alias_symbol);
                }
                return (Checked_Expression *)Checked_Is_Variant_Case_Expression__create(parsed_expression->super.location, (Checked_Type *)self->builtin_types->bool_type, value_expression, variant_case, alias_symbol, parsed_expression->is_not);
            }
        }
        pWriter__begin_location_message(stderr_writer, parsed_expression->value_expression->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, value_type->kind == CHECKED_TYPE_KIND__OPTIONAL ? "Optional type " : "Variant type ");
        pWriter__write__checked_type(stderr_writer, value_type);
        pWriter__write__cstring(stderr_writer, " doesn't have ");
        pWriter__write__checked_type(stderr_writer, case_type);
        pWriter__write__cstring(stderr_writer, " case");
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

Checked_Expression *Checker__check_less_expression(Checker *self, Checker_Context *context, Parsed_Less_Expression *parsed_expression, Checked_Type *expected_type) {
    Checked_Type *expected_numeric_type = expected_type && Checked_Type__is_numeric_type(expected_type) ? expected_type : NULL;
    Checked_Expression *left_expression = Checker__check_expression(self, context, parsed_expression->super.left_expression, expected_numeric_type);
    if (expected_numeric_type == NULL) {
        Checker__require_numeric_type(self, left_expression->type, left_expression->location);
    }
    Checked_Expression *right_expression = Checker__check_expression(self, context, parsed_expression->super.right_expression, left_expression->type);
    return (Checked_Expression *)Checked_Less_Expression__create(parsed_expression->super.super.location, (Checked_Type *)self->builtin_types->bool_type, left_expression, right_expression);
}

Checked_Expression *Checker__check_less_or_equals_expression(Checker *self, Checker_Context *context, Parsed_Less_Or_Equals_Expression *parsed_expression, Checked_Type *expected_type) {
    Checked_Type *expected_numeric_type = expected_type && Checked_Type__is_numeric_type(expected_type) ? expected_type : NULL;
    Checked_Expression *left_expression = Checker__check_expression(self, context, parsed_expression->super.left_expression, expected_numeric_type);
    if (expected_numeric_type == NULL) {
        Checker__require_numeric_type(self, left_expression->type, left_expression->location);
    }
    Checked_Expression *right_expression = Checker__check_expression(self, context, parsed_expression->super.right_expression, left_expression->type);
    return (Checked_Expression *)Checked_Less_Or_Equals_Expression__create(parsed_expression->super.super.location, (Checked_Type *)self->builtin_types->bool_type, left_expression, right_expression);
}

Checked_Expression *Checker__check_logic_and_expression(Checker *self, Checker_Context *context, Parsed_Logic_And_Expression *parsed_expression) {
    Checked_Expression *left_expression = Checker__check_expression(self, context, parsed_expression->super.left_expression, (Checked_Type *)self->builtin_types->bool_type);
    Checked_Expression *right_expression = Checker__check_expression(self, context, parsed_expression->super.right_expression, left_expression->type);
    return (Checked_Expression *)Checked_Logic_And_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

Checked_Expression *Checker__check_logic_or_expression(Checker *self, Checker_Context *context, Parsed_Logic_Or_Expression *parsed_expression) {
    self->symbols = Checked_Symbols__create(self->symbols);
    Checked_Expression *left_expression = Checker__check_expression(self, context, parsed_expression->super.left_expression, (Checked_Type *)self->builtin_types->bool_type);
    self->symbols = self->symbols->parent;
    self->symbols = Checked_Symbols__create(self->symbols);
    Checked_Expression *right_expression = Checker__check_expression(self, context, parsed_expression->super.right_expression, left_expression->type);
    self->symbols = self->symbols->parent;
    return (Checked_Expression *)Checked_Logic_Or_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

Checked_Expression *Checker__check_make_array_expression(Checker *self, Checker_Context *context, Parsed_Make_Array_Expression *parsed_expression) {
    Checked_Array_Type *array_type = (Checked_Array_Type *)Checker__resolve_type(self, context, parsed_expression->array_type);
    Checked_Call_Argument *first_argument = NULL;
    Checked_Call_Argument *last_argument = NULL;
    uint64_t argument_count = 0;
    for (Parsed_Call_Argument *parsed_argument = parsed_expression->first_argument; parsed_argument != NULL; parsed_argument = parsed_argument->next_argument) {
        if (parsed_argument->name != NULL) {
            pWriter__begin_location_message(stderr_writer, parsed_argument->location, WRITER_STYLE__ERROR);
            pWriter__write__cstring(stderr_writer, "Array items cannot be named");
            pWriter__end_location_message(stderr_writer);
            panic();
        }
        Checked_Expression *item_expression = Checker__check_expression(self, context, parsed_argument->expression, array_type->item_type);
        Checked_Call_Argument *argument = Checked_Call_Argument__create(item_expression, array_type->item_type);
        if (last_argument == NULL) {
            first_argument = argument;
        } else {
            last_argument->next_argument = argument;
        }
        last_argument = argument;
        argument_count++;
    }
    if (argument_count != array_type->length) {
        pWriter__begin_location_message(stderr_writer, parsed_expression->super.location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Expected ");
        pWriter__write__uint64(stderr_writer, array_type->length);
        pWriter__write__cstring(stderr_writer, " array items but got ");
        pWriter__write__uint64(stderr_writer, argument_count);
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    return (Checked_Expression *)Checked_Make_Array_Expression__create(parsed_expression->super.location, (Checked_Type *)array_type, array_type, first_argument);
}

Checked_Expression *Checker__check_package_symbol_expression(Checker *self, Checked_Package *checked_package, Source_Location expression_location, Token *symbol_name);

Checked_Expression *Checker__check_object_member_access(Checker *self, Checker_Context *context, Checked_Expression *object_expression, Token *member_name) {
    Source_Location expression_location = Source_Location__merge(object_expression->location, member_name->location);
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
            Checked_Package *package = ((Checked_Import_Symbol *)symbol_expression->symbol)->other_package;
            Checked_Symbol *pakcage_symbol = Checked_Symbols__find_symbol(self->global_symbols, package, member_name->lexeme);
            if (pakcage_symbol == NULL) {
                // Find a procedure by its procedure_name when the mangled symbol isn't found
                Checked_Symbol *candidate_symbol = self->global_symbols->first_symbol;
                Checked_Procedure_Symbol *matching_procedure_symbol = NULL;
                while (candidate_symbol != NULL) {
                    if (candidate_symbol->kind == CHECKED_SYMBOL_KIND__PROCEDURE && candidate_symbol->package == package) {
                        Checked_Procedure_Symbol *procedure_symbol = (Checked_Procedure_Symbol *)candidate_symbol;
                        if (String__equals_string(procedure_symbol->procedure_name, member_name->lexeme)) {
                            if (matching_procedure_symbol == NULL) {
                                matching_procedure_symbol = procedure_symbol;
                            } else {
                                matching_procedure_symbol = NULL; // more than one candidate
                                break;
                            }
                        }
                    }
                    candidate_symbol = candidate_symbol->next_symbol;
                }
                if (matching_procedure_symbol != NULL) {
                    pakcage_symbol = (Checked_Symbol *)matching_procedure_symbol;
                }
            }
            if (pakcage_symbol == NULL) {
                pWriter__begin_location_message(stderr_writer, expression_location, WRITER_STYLE__ERROR);
                pWriter__write__cstring(stderr_writer, "Module ");
                pWriter__write__string(stderr_writer, package->name);
                pWriter__write__cstring(stderr_writer, " has no ");
                pWriter__write__string(stderr_writer, member_name->lexeme);
                pWriter__write__cstring(stderr_writer, " symbol");
                pWriter__end_location_message(stderr_writer);
                panic();
            }
            return (Checked_Expression *)Checked_Symbol_Expression__create(expression_location, pakcage_symbol->type, pakcage_symbol);
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
        if (String__equals_cstring(member_name->lexeme, "length")) {
            return (Checked_Expression *)Checked_String_Length_Expression__create(expression_location, (Checked_Type *)self->builtin_types->usize_type, object_expression);
        }
        break;
    case CHECKED_TYPE_KIND__STRUCT: {
        Checked_Struct_Type *struct_type = (Checked_Struct_Type *)object_type;
        Checked_Struct_Member *member = Checked_Struct_Type__find_member(struct_type, member_name->lexeme);
        if (member != NULL) {
            if (member->struct_type != struct_type) {
                Checked_Struct_Type *super_struct = struct_type;
                while (super_struct != NULL) {
                    object_expression = (Checked_Expression *)Checked_Member_Access_Expression__create(expression_location, super_struct->first_member->type, object_expression, super_struct->first_member);
                    super_struct = (Checked_Struct_Type *)super_struct->first_member->type;
                    if (super_struct == member->struct_type) {
                        break;
                    }
                }
            }
            return (Checked_Expression *)Checked_Member_Access_Expression__create(expression_location, member->type, object_expression, member);
        }
        break;
    }
    case CHECKED_TYPE_KIND__TRAIT: {
        Checked_Trait_Type *trait_type = (Checked_Trait_Type *)object_type;
        Checked_Trait_Method *trait_method;
        for (trait_method = trait_type->first_method; trait_method != NULL; trait_method = trait_method->next_method) {
            if (String__equals_string(trait_method->name, member_name->lexeme)) {
                Checked_Member_Access_Expression *receiver_expression = Checked_Member_Access_Expression__create(object_expression->location, trait_type->self_struct_member->type, object_expression, trait_type->self_struct_member);
                Checked_Member_Access_Expression *procedure_expression = Checked_Member_Access_Expression__create(member_name->location, trait_method->struct_member->type, object_expression, trait_method->struct_member);
                return (Checked_Expression *)Checked_Receiver_Method_Expression__create(expression_location, trait_method->procedure_type->return_type, (Checked_Expression *)receiver_expression, (Checked_Expression *)procedure_expression, trait_method->procedure_type);
            }
        }
        break;
    }
    default:
        break;
    }

    /* Check method */
    object_type = object_expression->type;
    Checked_Procedure_Symbol *procedure_symbol = Checker__resolve_method_symbol(self, context, object_type, member_name->lexeme, NULL);
    if (procedure_symbol != NULL) {
        Checked_Symbol_Expression *procedure_expression = Checked_Symbol_Expression__create(member_name->location, procedure_symbol->super.type, (Checked_Symbol *)procedure_symbol);
        return (Checked_Expression *)Checked_Receiver_Method_Expression__create(expression_location, procedure_symbol->procedure_type->return_type, object_expression, (Checked_Expression *)procedure_expression, procedure_symbol->procedure_type);
    }

    /* Check referenced method */
    if (object_type->kind != CHECKED_TYPE_KIND__POINTER) {
        procedure_symbol = Checker__resolve_reference_method_symbol(self, context, object_type, member_name->lexeme, NULL);
        if (procedure_symbol != NULL) {
            object_type = (Checked_Type *)Checked_Pointer_Type__create(object_type->location, object_type);
            object_expression = (Checked_Expression *)Checked_Address_Of_Expression__create(object_expression->location, object_type, object_expression);
            Checked_Symbol_Expression *procedure_expression = Checked_Symbol_Expression__create(member_name->location, (Checked_Type *)procedure_symbol->super.type, (Checked_Symbol *)procedure_symbol);
            return (Checked_Expression *)Checked_Receiver_Method_Expression__create(expression_location, procedure_symbol->procedure_type->return_type, object_expression, (Checked_Expression *)procedure_expression, procedure_symbol->procedure_type);
        }
    }

    pWriter__begin_location_message(stderr_writer, member_name->location, WRITER_STYLE__ERROR);
    pWriter__write__cstring(stderr_writer, "No such struct member");
    pWriter__end_location_message(stderr_writer);
    panic();
}

Checked_Expression *Checker__check_member_access_expression(Checker *self, Checker_Context *context, Parsed_Member_Access_Expression *parsed_expression) {
    Checked_Expression *object_expression = Checker__check_expression(self, context, parsed_expression->object_expression, NULL);
    return Checker__check_object_member_access(self, context, object_expression, parsed_expression->member_name);
}

Checked_Expression *Checker__check_minus_expression(Checker *self, Checker_Context *context, Parsed_Minus_Expression *parsed_expression, Checked_Type *expected_type) {
    Checked_Expression *other_expression = Checker__check_expression(self, context, parsed_expression->super.other_expression, expected_type && Checked_Type__is_numeric_type(expected_type) ? expected_type : NULL);
    Checked_Type *other_expression_type = other_expression->type;
    Checker__require_numeric_type(self, other_expression_type, other_expression->location);
    return (Checked_Expression *)Checked_Minus_Expression__create(parsed_expression->super.super.location, other_expression_type, other_expression);
}

Checked_Expression *Checker__check_modulo_expression(Checker *self, Checker_Context *context, Parsed_Modulo_Expression *parsed_expression, Checked_Type *expected_type) {
    Checked_Type *expected_numeric_type = expected_type && Checked_Type__is_numeric_type(expected_type) ? expected_type : NULL;
    Checked_Expression *left_expression = Checker__check_expression(self, context, parsed_expression->super.left_expression, expected_numeric_type);
    if (expected_numeric_type == NULL) {
        Checker__require_numeric_type(self, left_expression->type, left_expression->location);
    }
    Checked_Expression *right_expression = Checker__check_expression(self, context, parsed_expression->super.right_expression, left_expression->type);
    return (Checked_Expression *)Checked_Modulo_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

Checked_Expression *Checker__check_multiply_expression(Checker *self, Checker_Context *context, Parsed_Multiply_Expression *parsed_expression, Checked_Type *expected_type) {
    Checked_Type *expected_numeric_type = expected_type && Checked_Type__is_numeric_type(expected_type) ? expected_type : NULL;
    Checked_Expression *left_expression = Checker__check_expression(self, context, parsed_expression->super.left_expression, expected_numeric_type);
    if (expected_numeric_type == NULL) {
        Checker__require_numeric_type(self, left_expression->type, left_expression->location);
    }
    Checked_Expression *right_expression = Checker__check_expression(self, context, parsed_expression->super.right_expression, left_expression->type);
    return (Checked_Expression *)Checked_Multiply_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

Checked_Expression *Checker__check_not_expression(Checker *self, Checker_Context *context, Parsed_Not_Expression *parsed_expression) {
    Checked_Expression *other_expression = Checker__check_expression(self, context, parsed_expression->super.other_expression, (Checked_Type *)self->builtin_types->bool_type);
    return (Checked_Expression *)Checked_Not_Expression__create(parsed_expression->super.super.location, other_expression->type, other_expression);
}

Checked_Expression *Checker__check_not_equals_expression(Checker *self, Checker_Context *context, Parsed_Not_Equals_Expression *parsed_expression) {
    Checked_Expression *left_expression = Checker__check_expression(self, context, parsed_expression->super.left_expression, NULL);
    Checked_Expression *right_expression = Checker__check_expression(self, context, parsed_expression->super.right_expression, left_expression->type);
    return (Checked_Expression *)Checked_Not_Equals_Expression__create(parsed_expression->super.super.location, (Checked_Type *)self->builtin_types->bool_type, left_expression, right_expression);
}

Checked_Expression *Checker__check_null_expression(Checker *self, Checker_Context *context, Parsed_Null_Expression *parsed_expression, Checked_Type *expected_type) {
    Checked_Type *expression_type;
    if (expected_type != NULL) {
        switch (expected_type->kind) {
        case CHECKED_TYPE_KIND__MULTI_POINTER:
        case CHECKED_TYPE_KIND__POINTER:
        case CHECKED_TYPE_KIND__PROCEDURE_POINTER:
            expression_type = expected_type;
            break;
        default:
            pWriter__begin_location_message(stderr_writer, parsed_expression->super.super.location, WRITER_STYLE__ERROR);
            pWriter__write__cstring(stderr_writer, "\"null\" cannot be used with non-pointer type: ");
            pWriter__write__checked_type(stderr_writer, expected_type);
            pWriter__end_location_message(stderr_writer);
            panic();
        }
    } else {
        expression_type = (Checked_Type *)self->builtin_types->null_type;
    }
    return (Checked_Expression *)Checked_Null_Expression__create(parsed_expression->super.literal->location, expression_type);
}

Checked_Expression *Checker__check_string_expression(Checker *self, Checker_Context *context, Parsed_String_Expression *parsed_expression) {
    Checked_Type *string_type = (Checked_Type *)self->builtin_types->str_type;
    String *string_value = parsed_expression->value;
    return (Checked_Expression *)Checked_String_Expression__create(parsed_expression->super.super.location, string_type, string_value);
}

Checked_Expression *Checker__check_subtract_expression(Checker *self, Checker_Context *context, Parsed_Subtract_Expression *parsed_expression, Checked_Type *expected_type) {
    Checked_Type *expected_numeric_type = expected_type && Checked_Type__is_numeric_type(expected_type) ? expected_type : NULL;
    Checked_Expression *left_expression = Checker__check_expression(self, context, parsed_expression->super.left_expression, expected_numeric_type);
    if (expected_numeric_type == NULL) {
        Checker__require_numeric_type(self, left_expression->type, left_expression->location);
    }
    Checked_Expression *right_expression = Checker__check_expression(self, context, parsed_expression->super.right_expression, left_expression->type);
    return (Checked_Expression *)Checked_Subtract_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

Checked_Expression *Checker__check_symbol_expression(Checker *self, Checker_Context *context, Parsed_Symbol_Expression *parsed_expression) {
    Checked_Symbol *symbol = Checked_Symbols__find_symbol(self->symbols, context->checked_package, parsed_expression->name->lexeme);
    if (symbol == NULL) {
        symbol = Checked_Symbols__find_symbol(self->global_symbols->parent, self->packages->builtin_package, parsed_expression->name->lexeme);
    }
    if (symbol == NULL) {
        symbol = Checked_Symbols__find_symbol(self->builtin_types->symbols, NULL, parsed_expression->name->lexeme);
    }
    if (symbol == NULL) {
        // Find a procedure by its procedure_name when the mangled symbol isn't found
        Checked_Symbol *candidate_symbol = self->global_symbols->first_symbol;
        Checked_Procedure_Symbol *matching_procedure_symbol = NULL;
        while (candidate_symbol != NULL) {
            if (candidate_symbol->kind == CHECKED_SYMBOL_KIND__PROCEDURE && candidate_symbol->package == context->checked_package) {
                Checked_Procedure_Symbol *procedure_symbol = (Checked_Procedure_Symbol *)candidate_symbol;
                if (String__equals_string(procedure_symbol->procedure_name, parsed_expression->name->lexeme)) {
                    if (matching_procedure_symbol == NULL) {
                        matching_procedure_symbol = procedure_symbol;
                    } else {
                        matching_procedure_symbol = NULL; // more than one candidate
                        break;
                    }
                }
            }
            candidate_symbol = candidate_symbol->next_symbol;
        }
        if (matching_procedure_symbol != NULL) {
            symbol = (Checked_Symbol *)matching_procedure_symbol;
        }
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

Checked_Expression *Checker__check_try_expression(Checker *self, Checker_Context *context, Parsed_Try_Expression *parsed_expression) {
    if (parsed_expression->expression->kind != PARSED_EXPRESSION_KIND__CALL) {
        pWriter__begin_location_message(stderr_writer, parsed_expression->expression->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Unsupported try expression");
        pWriter__end_location_message(stderr_writer);
        panic();
    }

    Checked_Expression *call_expression = Checker__check_call_expression(self, context, (Parsed_Call_Expression *)parsed_expression->expression, false);
    if (call_expression->type->kind != CHECKED_TYPE_KIND__RESULT) {
        pWriter__begin_location_message(stderr_writer, call_expression->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Call doesn't raise");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    Checked_Result_Type *result_type = (Checked_Result_Type *)call_expression->type;

    self->symbols = Checked_Symbols__create(self->symbols);
    Checked_Result_Error_Symbol *result_error_symbol = Checked_Result_Error_Symbol__create(context->checked_package, call_expression->location, String__create_from("error"), result_type->raise_type);
    Checked_Symbols__append_symbol(self->symbols, (Checked_Symbol *)result_error_symbol);
    Checked_Expression *else_expression = Checker__check_expression(self, context, parsed_expression->else_expression, result_type->return_type);
    self->symbols = self->symbols->parent;

    return (Checked_Expression *)Checked_Try_Expression__create(parsed_expression->super.location, result_type->return_type, (Checked_Call_Expression *)call_expression, else_expression, result_error_symbol);
}

Checked_Expression *Checker__check_type_alignment_expression(Checker *self, Checker_Context *context, Parsed_Type_Alignment_Expression *parsed_expression) {
    Checked_Type *expression_type = (Checked_Type *)self->builtin_types->usize_type;
    Checked_Type *aligned_type = Checker__resolve_type(self, context, parsed_expression->type);
    if (aligned_type->kind == CHECKED_TYPE_KIND__ANY) {
        pWriter__begin_location_message(stderr_writer, parsed_expression->type->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Type Any has no alignment");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    return (Checked_Expression *)Checked_Type_Alignment_Expression__create(parsed_expression->super.location, expression_type, aligned_type);
}

Checked_Expression *Checker__check_type_size_expression(Checker *self, Checker_Context *context, Parsed_Type_Size_Expression *parsed_expression) {
    Checked_Type *expression_type = (Checked_Type *)self->builtin_types->usize_type;
    Checked_Type *sized_type = Checker__resolve_type(self, context, parsed_expression->type);
    if (sized_type->kind == CHECKED_TYPE_KIND__ANY) {
        pWriter__begin_location_message(stderr_writer, parsed_expression->type->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Type Any has no size");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    return (Checked_Expression *)Checked_Type_Size_Expression__create(parsed_expression->super.location, expression_type, sized_type);
}

Checked_Expression *Checker__check_type_specialization_expression(Checker *self, Checker_Context *context, Parsed_Type_Specialization_Expression *parsed_expression) {
    Checked_Expression *type_expression = Checker__check_expression(self, context, parsed_expression->type_expression, NULL);
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
    Identifier_Token *parsed_type_package = Identifier_Token__create(parsed_expression->super.location, type->package->name);
    Identifier_Token *parsed_type_name_token = Identifier_Token__create(parsed_expression->super.location, type->name);
    Parsed_Named_Type *parsed_type = Parsed_Named_Type__create((Token *)parsed_type_package, (Token *)parsed_type_name_token);
    parsed_type->first_type_argument = parsed_expression->first_type_argument;
    Checked_Named_Type *specialized_type = Checker__specialize_type(self, context, (Checked_Generic_Type *)type, parsed_type);
    return (Checked_Expression *)Checked_Type_Expression__create(parsed_expression->super.location, (Checked_Type *)self->builtin_types->type_type, specialized_type);
}

Checked_Expression *Checker__check_expression(Checker *self, Checker_Context *context, Parsed_Expression *parsed_expression, Checked_Type *expected_type) {
    bool allows_is_alias = context->allows_is_alias;
    switch (parsed_expression->kind) {
    case PARSED_EXPRESSION_KIND__GROUP:
    case PARSED_EXPRESSION_KIND__IS:
    case PARSED_EXPRESSION_KIND__LOGIC_AND:
    case PARSED_EXPRESSION_KIND__LOGIC_OR:
        break;
    default:
        context->allows_is_alias = false;
        break;
    }
    Checked_Expression *expression;
    switch (parsed_expression->kind) {
    case PARSED_EXPRESSION_KIND__ADD:
        expression = Checker__check_add_expression(self, context, (Parsed_Add_Expression *)parsed_expression, expected_type);
        break;
    case PARSED_EXPRESSION_KIND__ADDRESS_OF:
        expression = Checker__check_address_of_expression(self, context, (Parsed_Address_Of_Expression *)parsed_expression);
        break;
    case PARSED_EXPRESSION_KIND__ALLOC:
        expression = Checker__check_alloc_expression(self, context, (Parsed_Alloc_Expression *)parsed_expression);
        break;
    case PARSED_EXPRESSION_KIND__ARRAY_ACCESS:
        expression = Checker__check_array_access_expression(self, context, (Parsed_Array_Access_Expression *)parsed_expression);
        break;
    case PARSED_EXPRESSION_KIND__BLOCK:
        expression = Checker__check_block_expression(self, context, (Parsed_Block_Expression *)parsed_expression, expected_type);
        break;
    case PARSED_EXPRESSION_KIND__BOOL:
        expression = Checker__check_bool_expression(self, (Parsed_Bool_Expression *)parsed_expression);
        break;
    case PARSED_EXPRESSION_KIND__CALL:
        expression = Checker__check_call_expression(self, context, (Parsed_Call_Expression *)parsed_expression, true);
        break;
    case PARSED_EXPRESSION_KIND__CAST:
        expression = Checker__check_cast_expression(self, context, (Parsed_Cast_Expression *)parsed_expression);
        break;
    case PARSED_EXPRESSION_KIND__CHARACTER:
        expression = Checker__check_character_expression(self, (Parsed_Character_Expression *)parsed_expression);
        break;
    case PARSED_EXPRESSION_KIND__DEREFERENCE:
        expression = Checker__check_dereference_expression(self, context, (Parsed_Dereference_Expression *)parsed_expression);
        break;
    case PARSED_EXPRESSION_KIND__DIVIDE:
        expression = Checker__check_divide_expression(self, context, (Parsed_Divide_Expression *)parsed_expression, expected_type);
        break;
    case PARSED_EXPRESSION_KIND__EQUALS:
        expression = Checker__check_equals_expression(self, context, (Parsed_Equals_Expression *)parsed_expression);
        break;
    case PARSED_EXPRESSION_KIND__GREATER:
        expression = Checker__check_greater_expression(self, context, (Parsed_Greater_Expression *)parsed_expression, expected_type);
        break;
    case PARSED_EXPRESSION_KIND__GREATER_OR_EQUALS:
        expression = Checker__check_greater_or_equals_expression(self, context, (Parsed_Greater_Or_Equals_Expression *)parsed_expression, expected_type);
        break;
    case PARSED_EXPRESSION_KIND__GROUP:
        expression = Checker__check_group_expression(self, context, (Parsed_Group_Expression *)parsed_expression, expected_type);
        break;
    case PARSED_EXPRESSION_KIND__INTEGER:
        expression = Checker__check_integer_expression(self, context, (Parsed_Integer_Expression *)parsed_expression, expected_type && Checked_Type__is_numeric_type(expected_type) ? expected_type : NULL);
        break;
    case PARSED_EXPRESSION_KIND__IS:
        expression = Checker__check_is_expression(self, context, (Parsed_Is_Expression *)parsed_expression);
        break;
    case PARSED_EXPRESSION_KIND__LESS:
        expression = Checker__check_less_expression(self, context, (Parsed_Less_Expression *)parsed_expression, expected_type);
        break;
    case PARSED_EXPRESSION_KIND__LESS_OR_EQUALS:
        expression = Checker__check_less_or_equals_expression(self, context, (Parsed_Less_Or_Equals_Expression *)parsed_expression, expected_type);
        break;
    case PARSED_EXPRESSION_KIND__LOGIC_AND:
        expression = Checker__check_logic_and_expression(self, context, (Parsed_Logic_And_Expression *)parsed_expression);
        break;
    case PARSED_EXPRESSION_KIND__LOGIC_OR:
        expression = Checker__check_logic_or_expression(self, context, (Parsed_Logic_Or_Expression *)parsed_expression);
        break;
    case PARSED_EXPRESSION_KIND__MAKE_ARRAY:
        expression = Checker__check_make_array_expression(self, context, (Parsed_Make_Array_Expression *)parsed_expression);
        break;
    case PARSED_EXPRESSION_KIND__MEMBER_ACCESS:
        expression = Checker__check_member_access_expression(self, context, (Parsed_Member_Access_Expression *)parsed_expression);
        break;
    case PARSED_EXPRESSION_KIND__MINUS:
        expression = Checker__check_minus_expression(self, context, (Parsed_Minus_Expression *)parsed_expression, expected_type);
        break;
    case PARSED_EXPRESSION_KIND__MODULO:
        expression = Checker__check_modulo_expression(self, context, (Parsed_Modulo_Expression *)parsed_expression, expected_type);
        break;
    case PARSED_EXPRESSION_KIND__MULTIPLY:
        expression = Checker__check_multiply_expression(self, context, (Parsed_Multiply_Expression *)parsed_expression, expected_type);
        break;
    case PARSED_EXPRESSION_KIND__NOT:
        expression = Checker__check_not_expression(self, context, (Parsed_Not_Expression *)parsed_expression);
        break;
    case PARSED_EXPRESSION_KIND__NOT_EQUALS:
        expression = Checker__check_not_equals_expression(self, context, (Parsed_Not_Equals_Expression *)parsed_expression);
        break;
    case PARSED_EXPRESSION_KIND__NULL:
        expression = Checker__check_null_expression(self, context, (Parsed_Null_Expression *)parsed_expression, expected_type);
        break;
    case PARSED_EXPRESSION_KIND__STRING:
        expression = Checker__check_string_expression(self, context, (Parsed_String_Expression *)parsed_expression);
        break;
    case PARSED_EXPRESSION_KIND__SUBTRACT:
        expression = Checker__check_subtract_expression(self, context, (Parsed_Subtract_Expression *)parsed_expression, expected_type);
        break;
    case PARSED_EXPRESSION_KIND__SYMBOL:
        expression = Checker__check_symbol_expression(self, context, (Parsed_Symbol_Expression *)parsed_expression);
        break;
    case PARSED_EXPRESSION_KIND__TRY:
        expression = Checker__check_try_expression(self, context, (Parsed_Try_Expression *)parsed_expression);
        break;
    case PARSED_EXPRESSION_KIND__TYPE_ALIGNMENT:
        expression = Checker__check_type_alignment_expression(self, context, (Parsed_Type_Alignment_Expression *)parsed_expression);
        break;
    case PARSED_EXPRESSION_KIND__TYPE_SIZE:
        expression = Checker__check_type_size_expression(self, context, (Parsed_Type_Size_Expression *)parsed_expression);
        break;
    case PARSED_EXPRESSION_KIND__TYPE_SPECIALIZATION:
        expression = Checker__check_type_specialization_expression(self, context, (Parsed_Type_Specialization_Expression *)parsed_expression);
        break;
    default:
        pWriter__begin_location_message(stderr_writer, parsed_expression->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Unsupported expression kind");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    context->allows_is_alias = allows_is_alias;

    if (expected_type != NULL) {
        switch (expected_type->kind) {
        case CHECKED_TYPE_KIND__POINTER: {
            expression = Checker__assure_expression_pointer_type(self, expression, (Checked_Pointer_Type *)expected_type);
            break;
        }
        case CHECKED_TYPE_KIND__TRAIT:
            if (expression->type != expected_type) {
                expression = Checker__make_trait_expression(self, context, parsed_expression->location, (Checked_Trait_Type *)expected_type, expression);
            }
            break;
        case CHECKED_TYPE_KIND__OPTIONAL:
        case CHECKED_TYPE_KIND__VARIANT:
            if (expression->type != expected_type) {
                expression = (Checked_Expression *)Checker__make_variant_expression(self, parsed_expression->location, (Checked_Variant_Type *)expected_type, expression);
            }
            break;
        default:
            break;
        }

        Checker__require_same_type(self, expected_type, expression->type, expression->location);
    }

    return expression;
}

Checked_Named_Type *Checker__check_builtin_type_statement(Checker *self, Checker_Context *context, Token *type_name) {
    Source_Location builtin_type_location = type_name->location;
    String *builtin_type_name = type_name->lexeme;
    Checked_Named_Type *type = Checker__find_type(self, context, builtin_type_name);
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

Checked_Named_Type *Checker__check_external_type_statement(Checker *self, Checker_Context *context, Token *type_name) {
    Checked_Named_Type *type = Checker__find_package_type(self, context->checked_package, type_name->lexeme);
    if (type != NULL) {
        if (type->name == type_name->lexeme) {
            return type;
        }
        pWriter__begin_location_message(stderr_writer, type_name->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Type redeclaration: ");
        pWriter__write__string(stderr_writer, type_name->lexeme);
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    Checked_External_Type *external_type = Checked_External_Type__create(type_name->location, type_name->lexeme, context->checked_package);
    external_type->super.super.symbol = Checker__create_type_symbol(self, context->checked_package, type_name->lexeme, (Checked_Named_Type *)external_type);
    return (Checked_Named_Type *)external_type;
}

struct Checked_Type_Dependency *Checked_Type_Dependency__create(Checked_Type *type, bool weak) {
    struct Checked_Type_Dependency *dependency = malloc(sizeof(struct Checked_Type_Dependency));
    dependency->type = type;
    dependency->weak = weak;
    dependency->next_dependency = NULL;
    return dependency;
}

void Checked_Type__append_dependencies(Checked_Type *self, Checked_Type *other, Source_Location location, Checker *checker);

void Checked_Type__append_weak_dependencies(Checked_Type *self, Checked_Type *other, Source_Location location, Checker *checker, bool weak) {
    if (self == other) {
        if (weak) {
            return; // Weak dependencies to self are allowed
        }
        pWriter__begin_location_message(stderr_writer, location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Type ");
        pWriter__write__checked_type(stderr_writer, self);
        pWriter__write__cstring(stderr_writer, " cannot depend on itself");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    switch (other->kind) {
    case CHECKED_TYPE_KIND__ARRAY:
        Checked_Type__append_weak_dependencies(self, ((Checked_Array_Type *)other)->item_type, location, checker, weak);
        return;
    case CHECKED_TYPE_KIND__EXTERNAL:
        if (!weak) {
            pWriter__begin_location_message(stderr_writer, location, WRITER_STYLE__ERROR);
            pWriter__write__cstring(stderr_writer, "Type ");
            pWriter__write__checked_type(stderr_writer, self);
            pWriter__write__cstring(stderr_writer, " cannot depend on external type ");
            pWriter__write__checked_type(stderr_writer, other);
            pWriter__end_location_message(stderr_writer);
            panic();
        }
        return;
    case CHECKED_TYPE_KIND__POINTER:
        Checked_Type__append_weak_dependencies(self, ((Checked_Pointer_Type *)other)->other_type, location, checker, true);
        return;
    case CHECKED_TYPE_KIND__PROCEDURE_POINTER: {
        Checked_Procedure_Pointer_Type *procedure_pointer_type = (Checked_Procedure_Pointer_Type *)other;
        Checked_Procedure_Parameter *procedure_parameter = procedure_pointer_type->procedure_type->first_parameter;
        while (procedure_parameter != NULL) {
            Checked_Type__append_weak_dependencies(self, procedure_parameter->type, location, checker, true);
            procedure_parameter = procedure_parameter->next_parameter;
        }
        Checked_Type__append_weak_dependencies(self, procedure_pointer_type->procedure_type->return_type, location, checker, true);
        return;
    }
    case CHECKED_TYPE_KIND__OPTIONAL:
    case CHECKED_TYPE_KIND__STRUCT:
    case CHECKED_TYPE_KIND__TRAIT:
    case CHECKED_TYPE_KIND__VARIANT:
        break;
    default:
        return;
    }
    struct Checked_Type_Dependency *self_dependency = self->first_dependency;
    if (self_dependency == NULL) {
        self->first_dependency = Checked_Type_Dependency__create(other, weak);
    } else {
        while (self_dependency->next_dependency != NULL) {
            if (self_dependency->type == other) {
                return;
            }
            self_dependency = self_dependency->next_dependency;
        }
        self_dependency->next_dependency = Checked_Type_Dependency__create(other, weak);
    }
    if (!weak) {
        struct Checked_Type_Dependency *other_dependency = other->first_dependency;
        while (other_dependency != NULL) {
            Checked_Type__append_weak_dependencies(self, other_dependency->type, location, checker, other_dependency->weak);
            other_dependency = other_dependency->next_dependency;
        }
    }
}

void Checked_Type__append_dependencies(Checked_Type *self, Checked_Type *other, Source_Location location, Checker *checker) {
    Checked_Type__append_weak_dependencies(self, other, location, checker, false);
}

Checked_Named_Type *Checker__create_struct_type(Checker *self, Checker_Context *context, Token *type_name, Parsed_Struct_Type_Specifier *parsed_type_specifier) {
    Checked_Package *struct_lookup_package = (self->global_symbols == self->builtin_types->symbols) ? NULL : context->checked_package;
    Checked_Named_Type *other_type = Checker__find_package_type(self, struct_lookup_package, type_name->lexeme);
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
    Checked_Package *struct_type_package = context->checked_package;
    if (self->global_symbols == self->builtin_types->symbols) {
        /* This is a builtin type */
        struct_type_package = NULL;
    }
    Checked_Struct_Type *struct_type = Checked_Struct_Type__create(type_name->location, struct_type_name, struct_type_package, parsed_type_specifier);
    struct_type->super.super.symbol = Checker__create_type_symbol(self, context->checked_package, struct_type_name, (Checked_Named_Type *)struct_type);

    return (Checked_Named_Type *)struct_type;
}

void Checker__check_struct_type(Checker *self, Checker_Context *context, Checked_Struct_Type *struct_type) {
    struct_type->super.needs_check = false;
    Parsed_Struct_Type_Specifier *parsed_type_specifier = struct_type->parsed_type_specifier;
    if (parsed_type_specifier->first_member != NULL) {
        Checked_Struct_Member *last_struct_member = NULL;
        Parsed_Struct_Member *parsed_member = parsed_type_specifier->first_member;
        while (parsed_member != NULL) {
            Checked_Struct_Member *struct_member = Checked_Struct_Type__find_member(struct_type, parsed_member->name->lexeme);
            if (struct_member != NULL) {
                pWriter__begin_location_message(stderr_writer, parsed_member->name->location, WRITER_STYLE__ERROR);
                pWriter__write__cstring(stderr_writer, "Duplicate struct member declaration");
                pWriter__end_location_message(stderr_writer);
                panic();
            }
            Checked_Type *struct_member_type = Checker__resolve_type(self, context, parsed_member->type);
            if (Checked_Type__equals(struct_member_type, (Checked_Type *)struct_type)) {
                pWriter__begin_location_message(stderr_writer, parsed_member->type->location, WRITER_STYLE__ERROR);
                pWriter__write__cstring(stderr_writer, "Struct member cannot be of its own type");
                pWriter__end_location_message(stderr_writer);
                panic();
            }
            if (parsed_member == parsed_type_specifier->first_member && String__ends_with_cstring(parsed_member->name->lexeme, "super")) {
                if (struct_member_type->kind != CHECKED_TYPE_KIND__STRUCT) {
                    pWriter__begin_location_message(stderr_writer, parsed_member->type->location, WRITER_STYLE__ERROR);
                    pWriter__write__cstring(stderr_writer, "Not a struct type");
                    pWriter__end_location_message(stderr_writer);
                    panic();
                }
            }
            Checked_Type__append_dependencies((Checked_Type *)struct_type, struct_member_type, parsed_member->type->location, self);
            struct_member = Checked_Struct_Member__create(parsed_member->name->location, struct_type, parsed_member->name->lexeme, struct_member_type);
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

Checked_Procedure_Type *Checker__check_procedure_type(Checker *self, Checker_Context *context, Source_Location location, Parsed_Procedure_Parameter *first_parsed_parameter, Parsed_Type *parsed_return_type, Parsed_Type *parsed_raise_type) {
    Checked_Type *procedure_return_type;
    if (parsed_return_type != NULL) {
        procedure_return_type = Checker__resolve_type(self, context, parsed_return_type);
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
    if (parsed_raise_type != NULL) {
        Checked_Type *procedure_raise_type = Checker__resolve_type(self, context, parsed_raise_type);
        switch (procedure_raise_type->kind) {
        case CHECKED_TYPE_KIND__ANY:
            pWriter__begin_location_message(stderr_writer, parsed_raise_type->location, WRITER_STYLE__ERROR);
            pWriter__write__cstring(stderr_writer, "Cannot use Any as raise type");
            pWriter__end_location_message(stderr_writer);
            panic();
        case CHECKED_TYPE_KIND__EXTERNAL:
            pWriter__begin_location_message(stderr_writer, parsed_raise_type->location, WRITER_STYLE__ERROR);
            pWriter__write__cstring(stderr_writer, "Cannot use external type as raise type");
            pWriter__end_location_message(stderr_writer);
            panic();
        default:
            break;
        }
        procedure_return_type = Checker__resolve_result_type(self, context, parsed_return_type ? Source_Location__merge(parsed_return_type->location, parsed_raise_type->location) : parsed_raise_type->location, procedure_return_type, procedure_raise_type);
    }
    Checked_Procedure_Parameter *procedure_first_parameter = NULL;
    Checked_Procedure_Parameter *procedure_last_parameter = NULL;
    Parsed_Procedure_Parameter *parsed_parameter = first_parsed_parameter;
    while (parsed_parameter != NULL) {
        Checked_Type *procedure_parameter_type = Checker__resolve_type(self, context, parsed_parameter->type);
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

Checked_Named_Type *Checker__check_trait_type_statement(Checker *self, Checker_Context *context, Token *type_name, Parsed_Trait_Type_Specifier *parsed_trait_type_specifier) {
    Checked_Named_Type *other_type = Checker__find_package_type(self, context->checked_package, type_name->lexeme);
    if (other_type != NULL) {
        if (other_type->super.kind == CHECKED_TYPE_KIND__TRAIT && Source_Location__equals(other_type->super.location, type_name->location)) {
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

    Checked_Trait_Type *trait_type = Checked_Trait_Type__create(type_name->location, type_name->lexeme, context->checked_package);
    trait_type->super.super.symbol = Checker__create_type_symbol(self, context->checked_package, type_name->lexeme, (Checked_Named_Type *)trait_type);

    trait_type->struct_type = Checked_Struct_Type__create(type_name->location, trait_type->super.name, context->checked_package, NULL);

    Checked_Type *trait_receiver_type = (Checked_Type *)Checked_Pointer_Type__create((Source_Location){}, (Checked_Type *)self->builtin_types->any_type);
    trait_type->self_struct_member = trait_type->struct_type->first_member = Checked_Struct_Member__create((Source_Location){}, trait_type->struct_type, String__create_from("self"), trait_receiver_type);

    Parsed_Trait_Method *parsed_method = parsed_trait_type_specifier->first_method;
    if (parsed_method != NULL) {
        context->receiver_type = trait_receiver_type;
        Checked_Struct_Member *last_struct_member = trait_type->struct_type->first_member;
        Checked_Trait_Method *last_trait_method = NULL;
        for (; parsed_method != NULL; parsed_method = parsed_method->next_method) {
            Checked_Procedure_Type *procedure_type = Checker__check_procedure_type(self, context, parsed_method->location, parsed_method->first_parameter, parsed_method->return_type, parsed_method->raise_type);
            Checked_Struct_Member *trait_method_struct_member = Checked_Struct_Member__create((Source_Location){}, trait_type->struct_type, parsed_method->name->lexeme, (Checked_Type *)Checked_Procedure_Pointer_Type__create((Source_Location){}, procedure_type));
            last_struct_member = last_struct_member->next_member = trait_method_struct_member;
            Checked_Trait_Method *trait_method = Checked_Trait_Method__create(parsed_method->location, parsed_method->name->lexeme, procedure_type, trait_method_struct_member);
            Checked_Procedure_Parameter *trait_method_parameter = trait_method->procedure_type->first_parameter;
            while (trait_method_parameter != NULL) {
                Checked_Type__append_dependencies((Checked_Type *)trait_type, trait_method_parameter->type, trait_method_parameter->location, self);
                trait_method_parameter = trait_method_parameter->next_parameter;
            }
            if (parsed_method->return_type != NULL) {
                Checked_Type__append_dependencies((Checked_Type *)trait_type, trait_method->procedure_type->return_type, parsed_method->return_type->location, self);
            }
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

Checked_Named_Type *Checker__create_variant_type(Checker *self, Checker_Context *context, Token *type_name, Parsed_Variant_Type_Specifier *parsed_variant_type_specifier) {
    Checked_Named_Type *other_type = Checker__find_package_type(self, context->checked_package, type_name->lexeme);
    if (other_type != NULL) {
        if (other_type->super.kind == CHECKED_TYPE_KIND__VARIANT && Source_Location__equals(other_type->super.location, type_name->location)) {
            /* Type checked already */
            return other_type;
        }
        if (other_type->super.location.source != NULL) {
            pWriter__begin_location_message(stderr_writer, type_name->location, WRITER_STYLE__ERROR);
            pWriter__write__cstring(stderr_writer, "Type redeclaration");
            pWriter__end_location_message(stderr_writer);
            pWriter__begin_location_message(stderr_writer, other_type->super.location, WRITER_STYLE__WARNING);
            pWriter__write__cstring(stderr_writer, "Previous declaration here");
            pWriter__end_location_message(stderr_writer);
            panic();
        }
    }

    Checked_Variant_Type *variant_type = Checked_Variant_Type__create(type_name->location, type_name->lexeme, context->checked_package, parsed_variant_type_specifier);
    variant_type->super.super.symbol = Checker__create_type_symbol(self, context->checked_package, type_name->lexeme, (Checked_Named_Type *)variant_type);

    return (Checked_Named_Type *)variant_type;
}

void Checker__check_variant_type(Checker *self, Checker_Context *context, Checked_Variant_Type *variant_type) {
    variant_type->super.needs_check = false;
    Parsed_Variant_Type_Specifier *parsed_variant_type_specifier = variant_type->parsed_variant_type_specifier;

    // Each variant has the nil variant case
    Checked_Variant_Case *nil_variant_case = Checked_Variant_Case__create(variant_type->super.super.symbol->super.location, (Checked_Type *)self->builtin_types->nil_type, 0);
    variant_type->first_variant_case = nil_variant_case;

    Checked_Variant_Case *last_variant_case = variant_type->first_variant_case;
    Parsed_Variant_Case *parsed_variant_case = parsed_variant_type_specifier->first_variant_case;
    while (parsed_variant_case != NULL) {
        Checked_Type *variant_case_type = Checker__resolve_type(self, context, parsed_variant_case->type);
        if (Checked_Type__equals(variant_case_type, (Checked_Type *)variant_type)) {
            pWriter__begin_location_message(stderr_writer, parsed_variant_case->type->location, WRITER_STYLE__ERROR);
            pWriter__write__cstring(stderr_writer, "Variant case cannot be of its own type");
            pWriter__end_location_message(stderr_writer);
            panic();
        }
        Checked_Type__append_dependencies((Checked_Type *)variant_type, variant_case_type, parsed_variant_case->type->location, self);
        Checked_Variant_Case *variant_case = Checked_Variant_Case__create(parsed_variant_case->type->location, variant_case_type, last_variant_case->index + 1);
        last_variant_case = last_variant_case->next_variant = variant_case;
        parsed_variant_case = parsed_variant_case->next_variant;
    }

    variant_type->variant_count = last_variant_case->index;
}

Checked_Statement *Checker__check_statement(Checker *self, Checker_Context *context, Parsed_Statement *parsed_statement, Checked_Type *expected_type);

Checked_Statement *Checker__check_assignment_statement(Checker *self, Checker_Context *context, Parsed_Assignment_Statement *parsed_statement) {
    Checked_Expression *object_expression = Checker__check_expression(self, context, parsed_statement->object_expression, NULL);
    if (!Checked_Expression__is_mutable(object_expression)) {
        pWriter__begin_location_message(stderr_writer, object_expression->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Cannot assign to immutable expression");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    Checked_Expression *value_expression = Checker__check_expression(self, context, parsed_statement->value_expression, object_expression->type);
    if (!Checked_Type__is_identical(object_expression->type, value_expression->type)) {
        value_expression = (Checked_Expression *)Checked_Cast_Expression__create(value_expression->location, object_expression->type, value_expression);
    }
    return (Checked_Statement *)Checked_Assignment_Statement__create(parsed_statement->super.location, object_expression, value_expression);
}

Checked_Block_Statement *Checker__check_block_statement(Checker *self, Checker_Context *context, Parsed_Block_Statement *parsed_block_statement, Checked_Type *expected_type) {
    /* Create and push block symbols */
    self->symbols = Checked_Symbols__create(self->symbols);

    Checked_Statements *checked_statements = Checked_Statements__create();
    Parsed_Statement *parsed_statement = parsed_block_statement->statements->first_statement;
    while (parsed_statement != NULL) {
        Checked_Statement *checked_statement = Checker__check_statement(self, context, parsed_statement, expected_type);
        Checked_Statements__append(checked_statements, checked_statement);
        parsed_statement = parsed_statement->next_statement;
    }

    /* Pop block symbols */
    self->symbols = self->symbols->parent;

    Checked_Block_Statement *block_statement = Checked_Block_Statement__create(parsed_block_statement->super.location, checked_statements);
    context->is_unreachable_statement = false;
    return block_statement;
}

Checked_Statement *Checker__check_break_statement(Checker *self, Checker_Context *context, Parsed_Break_Statement *parsed_statement) {
    if (context->is_deferred_statement) {
        pWriter__begin_location_message(stderr_writer, parsed_statement->super.location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Cannot defer break statements");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    context->is_unreachable_statement = true;
    return (Checked_Statement *)Checked_Break_Statement__create(parsed_statement->super.location);
}

void Checked_Expression__require_constant(Checked_Expression *self) {
    switch (self->kind) {
    case CHECKED_EXPRESSION_KIND__INTEGER:
    case CHECKED_EXPRESSION_KIND__BOOL:
    case CHECKED_EXPRESSION_KIND__CHARACTER:
    case CHECKED_EXPRESSION_KIND__STRING:
        return;
    case CHECKED_EXPRESSION_KIND__ADD:
    case CHECKED_EXPRESSION_KIND__DIVIDE:
    case CHECKED_EXPRESSION_KIND__MODULO:
    case CHECKED_EXPRESSION_KIND__MULTIPLY:
    case CHECKED_EXPRESSION_KIND__SUBTRACT: {
        Checked_Binary_Expression *binary_expression = (Checked_Binary_Expression *)self;
        Checked_Expression__require_constant(binary_expression->left_expression);
        Checked_Expression__require_constant(binary_expression->right_expression);
        return;
    }
    case CHECKED_EXPRESSION_KIND__SYMBOL: {
        Checked_Symbol *symbol = ((Checked_Symbol_Expression *)self)->symbol;
        if (symbol->kind != CHECKED_SYMBOL_KIND__CONSTANT) {
            pWriter__begin_location_message(stderr_writer, self->location, WRITER_STYLE__ERROR);
            pWriter__write__cstring(stderr_writer, "Expected constant symbol");
            pWriter__end_location_message(stderr_writer);
            panic();
        }
        return;
    }
    default:
        pWriter__begin_location_message(stderr_writer, self->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Expected constant expression");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
}

Checked_Statement *Checker__check_constant_statement(Checker *self, Checker_Context *context, Parsed_Constant_Statement *parsed_statement) {
    Checked_Expression *value_expression = Checker__check_expression(self, context, parsed_statement->value_expression, NULL);
    Checked_Expression__require_constant(value_expression);
    Checked_Constant_Symbol *constant_symbol = Checked_Constant_Symbol__create(context->checked_package, parsed_statement->super.name->location, parsed_statement->super.name->lexeme, value_expression);
    Checked_Symbols__append_symbol(self->symbols, (Checked_Symbol *)constant_symbol);
    return (Checked_Statement *)Checked_Constant_Statement__create(parsed_statement->super.super.location, constant_symbol);
}

Checked_Statement *Checker__check_defer_statement(Checker *self, Checker_Context *context, Parsed_Defer_Statement *parsed_statement) {
    bool is_deferred_statement = context->is_deferred_statement;
    context->is_deferred_statement = true;
    Checked_Statement *defered_statement = Checker__check_statement(self, context, parsed_statement->statement, NULL);
    context->is_deferred_statement = is_deferred_statement;
    return (Checked_Statement *)Checked_Defer_Statement__create(parsed_statement->super.location, defered_statement);
}

Checked_Statement *Checker__check_expression_statement(Checker *self, Checker_Context *context, Parsed_Expression_Statement *parsed_statement) {
    Checked_Expression *expression = Checker__check_expression(self, context, parsed_statement->expression, NULL);
    if (!Checked_Type__equals((Checked_Type *)self->builtin_types->nothing_type, expression->type)) {
        /* TODO: Source_Location__warning(expression->location, String__create_from("Unused result value")); */
    }
    return (Checked_Statement *)Checked_Expression_Statement__create(parsed_statement->super.location, expression);
}

Checked_Statement *Checker__check_if_statement(Checker *self, Checker_Context *context, Parsed_If_Statement *parsed_statement) {
    self->symbols = Checked_Symbols__create(self->symbols);
    bool allows_is_alias = context->allows_is_alias;
    context->allows_is_alias = true;
    Checked_Expression *condition_expression = Checker__check_expression(self, context, parsed_statement->condition_expression, (Checked_Type *)self->builtin_types->bool_type);
    context->allows_is_alias = allows_is_alias;
    Checked_Statement *true_statement = Checker__check_statement(self, context, parsed_statement->true_statement, NULL);
    self->symbols = self->symbols->parent;
    Checked_Statement *false_statement = NULL;
    if (parsed_statement->false_statement != NULL) {
        false_statement = Checker__check_statement(self, context, parsed_statement->false_statement, NULL);
    }
    return (Checked_Statement *)Checked_If_Statement__create(parsed_statement->super.location, condition_expression, true_statement, false_statement);
}

Checked_Statement *Checker__check_loop_statement(Checker *self, Checker_Context *context, Parsed_Loop_Statement *parsed_statement) {
    Checked_Statement *body_statement = Checker__check_statement(self, context, parsed_statement->body_statement, NULL);
    Checked_Loop_Statement *loop_statement = Checked_Loop_Statement__create(parsed_statement->super.location, body_statement);
    return (Checked_Statement *)loop_statement;
}

Checked_Statement *Checker__check_panic_statement(Checker *self, Checker_Context *context, Parsed_Panic_Statement *parsed_statement) {
    context->is_unreachable_statement = true;
    return (Checked_Statement *)Checked_Panic_Statement__create(parsed_statement->super.location, parsed_statement->message != NULL ? parsed_statement->message->value : NULL);
}

Checked_Statement *Checker__check_raise_statement(Checker *self, Checker_Context *context, Parsed_Raise_Statement *parsed_statement) {
    if (context->return_type->kind != CHECKED_TYPE_KIND__RESULT) {
        pWriter__begin_location_message(stderr_writer, parsed_statement->super.location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Procedure does not declare a raise type");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    Checked_Type *procedure_raise_type = ((Checked_Result_Type *)context->return_type)->raise_type;
    Checked_Expression *raise_expression = Checker__check_expression(self, context, parsed_statement->expression, procedure_raise_type);
    context->is_unreachable_statement = true;
    return (Checked_Statement *)Checked_Raise_Statement__create(parsed_statement->super.location, raise_expression);
}

Checked_Statement *Checker__check_return_statement(Checker *self, Checker_Context *context, Parsed_Return_Statement *parsed_statement) {
    if (context->is_deferred_statement) {
        pWriter__begin_location_message(stderr_writer, parsed_statement->super.location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Cannot defer return statements");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    Checked_Type *return_type = context->return_type;
    if (return_type->kind == CHECKED_TYPE_KIND__RESULT) {
        return_type = ((Checked_Result_Type *)return_type)->return_type;
    }
    Checked_Expression *result_expression = NULL;
    if (parsed_statement->expression != NULL) {
        if (return_type->kind == CHECKED_TYPE_KIND__NOTHING) {
            pWriter__begin_location_message(stderr_writer, parsed_statement->super.location, WRITER_STYLE__ERROR);
            pWriter__write__cstring(stderr_writer, "Unexpected return expression");
            pWriter__end_location_message(stderr_writer);
            panic();
        }
        result_expression = Checker__check_expression(self, context, parsed_statement->expression, return_type);
    } else if (return_type->kind != CHECKED_TYPE_KIND__NOTHING) {
        pWriter__begin_location_message(stderr_writer, parsed_statement->super.location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Missing return expression");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    if (context->return_type->kind == CHECKED_TYPE_KIND__RESULT) {
        if (result_expression != NULL) {
            result_expression = (Checked_Expression *)Checked_Result_Expression__create(result_expression->location, context->return_type, result_expression, NULL);
        } else {
            result_expression = (Checked_Expression *)Checked_Result_Expression__create(parsed_statement->super.location, context->return_type, NULL, NULL);
        }
    }

    context->is_unreachable_statement = true;

    return (Checked_Statement *)Checked_Return_Statement__create(parsed_statement->super.location, result_expression);
}

Checked_Variant_Switch_Statement *Checker__check_variant_switch_statement(Checker *self, Checker_Context *context, Parsed_Switch_Statement *parsed_statement, Checked_Expression *variant_expression, Checked_Variant_Type *variant_type, bool through_pointer);

Checked_Statement *Checker__check_switch_statement(Checker *self, Checker_Context *context, Parsed_Switch_Statement *parsed_statement) {
    Checked_Expression *expression = Checker__check_expression(self, context, parsed_statement->expression, NULL);
    if (expression->type->kind == CHECKED_TYPE_KIND__OPTIONAL || expression->type->kind == CHECKED_TYPE_KIND__VARIANT) {
        return (Checked_Statement *)Checker__check_variant_switch_statement(self, context, parsed_statement, expression, (Checked_Variant_Type *)expression->type, false);
    }
    if (expression->type->kind == CHECKED_TYPE_KIND__POINTER) {
        Checked_Type *pointed_type = ((Checked_Pointer_Type *)expression->type)->other_type;
        if (pointed_type->kind == CHECKED_TYPE_KIND__OPTIONAL || pointed_type->kind == CHECKED_TYPE_KIND__VARIANT) {
            return (Checked_Statement *)Checker__check_variant_switch_statement(self, context, parsed_statement, expression, (Checked_Variant_Type *)pointed_type, true);
        }
    }
    pWriter__begin_location_message(stderr_writer, expression->location, WRITER_STYLE__ERROR);
    pWriter__write__cstring(stderr_writer, "Switch doesn't support ");
    pWriter__write__checked_type(stderr_writer, expression->type);
    pWriter__write__cstring(stderr_writer, " expressions");
    pWriter__end_location_message(stderr_writer);
    panic();
}

Checked_Variant_Switch_Statement *Checker__check_variant_switch_statement(Checker *self, Checker_Context *context, Parsed_Switch_Statement *parsed_statement, Checked_Expression *variant_expression, Checked_Variant_Type *variant_type, bool through_pointer) {
    bool *variants_with_case = malloc(variant_type->variant_count * sizeof(bool));
    Parsed_Switch_Case *parsed_switch_case = parsed_statement->first_case;
    Checked_Variant_Switch_Case *first_variant_switch_case = NULL;
    Checked_Variant_Switch_Case *last_variant_switch_case = NULL;
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
            switch_else = Checked_Switch_Else__create(parsed_switch_case->location, Checker__check_statement(self, context, parsed_switch_case->statement, NULL));
            break;
        }
        case PARSED_SWITCH_CASE_KIND__VARIANT: {
            if (switch_else != NULL) {
                pWriter__begin_location_message(stderr_writer, parsed_switch_case->location, WRITER_STYLE__ERROR);
                pWriter__write__cstring(stderr_writer, "Switch case cannot follow else case");
                pWriter__end_location_message(stderr_writer);
                panic();
            }
            Checked_Type *alias_type;
            bool case_by_pointer;
            Checked_Type *variant_case_type = Checker__resolve_match_case_type(self, context, parsed_switch_case->variant.type, through_pointer, &alias_type, &case_by_pointer);
            Checked_Variant_Case *variant_case = variant_type->first_variant_case;
            for (; variant_case != NULL; variant_case = variant_case->next_variant) {
                if (Checked_Type__equals(variant_case->type, variant_case_type)) {
                    break;
                }
            }
            if (variant_case == NULL) {
                pWriter__begin_location_message(stderr_writer, parsed_switch_case->variant.type->location, WRITER_STYLE__ERROR);
                pWriter__write__cstring(stderr_writer, "No ");
                pWriter__write__checked_type(stderr_writer, variant_case_type);
                pWriter__write__cstring(stderr_writer, " variant case in ");
                pWriter__write__checked_type(stderr_writer, (Checked_Type *)variant_type);
                pWriter__end_location_message(stderr_writer);
                panic();
            }
            if (variants_with_case[variant_case->index]) {
                pWriter__begin_location_message(stderr_writer, parsed_switch_case->location, WRITER_STYLE__ERROR);
                pWriter__write__cstring(stderr_writer, "Duplicate case");
                pWriter__end_location_message(stderr_writer);
                panic();
            }
            variants_with_case[variant_case->index] = true;

            // Create and push switch case symbols
            self->symbols = Checked_Symbols__create(self->symbols);

            Checked_Variant_Alias_Symbol *alias_symbol = NULL;
            if (parsed_switch_case->variant.alias != NULL) {
                // Create a symbol for the variant case
                bool alias_is_mutable = case_by_pointer ? false : Checked_Expression__is_mutable(variant_expression);
                alias_symbol = Checked_Variant_Alias_Symbol__create(context->checked_package, parsed_switch_case->variant.alias->super.location, parsed_switch_case->variant.alias->super.lexeme, alias_type, alias_is_mutable, case_by_pointer);
                Checked_Symbols__append_symbol(self->symbols, (Checked_Symbol *)alias_symbol);
            }

            Checked_Statement *variant_switch_case_statement = Checker__check_statement(self, context, parsed_switch_case->statement, NULL);

            // Pop switch case symbols
            self->symbols = self->symbols->parent;

            Checked_Variant_Switch_Case *variant_switch_case = Checked_Variant_Switch_Case__create(parsed_switch_case->variant.type->location, variant_type, variant_case, alias_symbol, variant_switch_case_statement);
            if (first_variant_switch_case == NULL) {
                first_variant_switch_case = variant_switch_case;
            } else {
                last_variant_switch_case->next_switch_variant_case = variant_switch_case;
            }
            last_variant_switch_case = variant_switch_case;
            break;
        }
        default:
            pWriter__begin_location_message(stderr_writer, parsed_switch_case->location, WRITER_STYLE__ERROR);
            pWriter__write__cstring(stderr_writer, "Switch case not supported with variant type");
            pWriter__end_location_message(stderr_writer);
            panic();
            break;
        }
    }
    if (switch_else == NULL) {
        Checked_Variant_Case *variant_case = variant_type->first_variant_case;
        for (; variant_case != NULL; variant_case = variant_case->next_variant) {
            if (!variants_with_case[variant_case->index]) {
                pWriter__begin_location_message(stderr_writer, parsed_statement->super.location, WRITER_STYLE__ERROR);
                pWriter__write__cstring(stderr_writer, "Missing case for ");
                pWriter__write__checked_type(stderr_writer, variant_case->type);
                pWriter__end_location_message(stderr_writer);
                panic();
            }
        }
    }
    free(variants_with_case);
    return Checked_Variant_Switch_Statement__create(parsed_statement->super.location, variant_expression, first_variant_switch_case, switch_else);
}

Checked_Statement *Checker__check_variable_statement(Checker *self, Checker_Context *context, Parsed_Variable_Statement *parsed_statement) {
    Checked_Type *variable_type = NULL;
    if (parsed_statement->type != NULL) {
        variable_type = Checker__resolve_type(self, context, parsed_statement->type);
    } else if (parsed_statement->expression == NULL) {
        pWriter__begin_location_message(stderr_writer, parsed_statement->super.super.location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Missing type");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    Checked_Expression *expression = NULL;
    if (parsed_statement->expression != NULL) {
        expression = Checker__check_expression(self, context, parsed_statement->expression, variable_type);
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
        } else if (!Checked_Type__is_identical(variable_type, expression->type)) {
            expression = (Checked_Expression *)Checked_Cast_Expression__create(expression->location, variable_type, expression);
        }
    }
    bool is_global = self->symbols == self->global_symbols;
    Checked_Variable_Symbol *variable = Checked_Variable_Symbol__create(context->checked_package, parsed_statement->super.name->location, parsed_statement->super.name->lexeme, variable_type, is_global);
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
    return (Checked_Statement *)Checked_Variable_Statement__create(parsed_statement->super.super.location, variable, parsed_statement->is_external, expression);
}

Checked_Statement *Checker__check_while_statement(Checker *self, Checker_Context *context, Parsed_While_Statement *parsed_statement) {
    self->symbols = Checked_Symbols__create(self->symbols);
    bool allows_is_alias = context->allows_is_alias;
    context->allows_is_alias = true;
    Checked_Expression *condition_expression = Checker__check_expression(self, context, parsed_statement->condition_expression, (Checked_Type *)self->builtin_types->bool_type);
    context->allows_is_alias = allows_is_alias;
    Checked_Statement *body_statement = Checker__check_statement(self, context, parsed_statement->body_statement, NULL);
    self->symbols = self->symbols->parent;
    return (Checked_Statement *)Checked_While_Statement__create(parsed_statement->super.location, condition_expression, body_statement);
}

Checked_Statement *Checker__check_yield_statement(Checker *self, Checker_Context *context, Parsed_Yield_Statement *parsed_statement, Checked_Type *expected_type) {
    Checked_Expression *expression = Checker__check_expression(self, context, parsed_statement->expression, expected_type);
    return (Checked_Statement *)Checked_Yield_Statement__create(parsed_statement->super.location, expression);
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

void Checker__check_generic_procedure_declaration(Checker *self, Checker_Context *context, Parsed_Procedure_Statement *parsed_statement) {
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
        receiver_type = Checker__resolve_type(self, context, parsed_receiver_type);
    } else {
        Parsed_Type_Argument *first_type_argument = parsed_generic_type->first_type_argument;
        parsed_generic_type->first_type_argument = NULL; // Remove type arguments temporarily
        receiver_type = Checker__resolve_type(self, context, parsed_receiver_type);
        parsed_generic_type->first_type_argument = first_type_argument; // Restore type arguments
    }

    String *symbol_name = String__create();
    String__append_mangled_type_name(symbol_name, receiver_type);
    String__append_cstring(symbol_name, "__");
    String__append_string(symbol_name, parsed_statement->super.name->lexeme);

    Checked_Generic_Procedure_Symbol *generic_procedure_symbol = Checked_Generic_Procedure_Symbol__create(context->checked_package, parsed_statement->super.super.location, symbol_name, receiver_type, parsed_statement);
    Checked_Symbols__append_symbol(self->symbols, (Checked_Symbol *)generic_procedure_symbol);

    Checker__append_method(self, receiver_type, (Checked_Symbol *)generic_procedure_symbol);
}

Checked_Procedure_Symbol *Checker__check_procedure_declaration(Checker *self, Checker_Context *context, Parsed_Procedure_Statement *parsed_statement) {
    Checked_Procedure_Type *procedure_type = Checker__check_procedure_type(self, context, parsed_statement->super.super.location, parsed_statement->first_parameter, parsed_statement->return_type, parsed_statement->raise_type);

    String *symbol_name = String__create();
    Checked_Type *receiver_type = NULL;
    if (parsed_statement->is_method) {
        if (parsed_statement->is_external) {
            pWriter__begin_location_message(stderr_writer, parsed_statement->first_parameter->type->location, WRITER_STYLE__ERROR);
            pWriter__write__cstring(stderr_writer, "External procedures cannot have a receiver type");
            pWriter__end_location_message(stderr_writer);
            panic();
        }
        receiver_type = Checker__resolve_type(self, context, parsed_statement->first_parameter->type);
        String__append_mangled_type_name(symbol_name, receiver_type);
        String__append_cstring(symbol_name, "__");
    }
    String__append_string(symbol_name, parsed_statement->super.name->lexeme);

    if (!parsed_statement->is_external) {
        // Mangle parameter labels into symbol name to support procedure overloading
        Parsed_Procedure_Parameter *procedure_parameter = parsed_statement->first_parameter;
        if (parsed_statement->is_method && procedure_parameter != NULL) {
            procedure_parameter = procedure_parameter->next_parameter; // Skip receiver
        }
        while (procedure_parameter != NULL) {
            String__append_cstring(symbol_name, "__");
            if (procedure_parameter->label != NULL) {
                String__append_string(symbol_name, procedure_parameter->label->lexeme);
            } else {
                String__append_cstring(symbol_name, "anon");
            }
            procedure_parameter = procedure_parameter->next_parameter;
        }
    }

    Checked_Symbol *existing_symbol = Checked_Symbols__find_symbol(self->global_symbols, context->checked_package, symbol_name);
    if (existing_symbol != NULL) {
        if (existing_symbol->kind == CHECKED_SYMBOL_KIND__PROCEDURE) {
            Checked_Procedure_Symbol *procedure_symbol = (Checked_Procedure_Symbol *)existing_symbol;
            if (procedure_symbol->parsed_procedure_statement == parsed_statement) {
                String__delete(symbol_name);
                return procedure_symbol;
            }
        }
    }

    Checked_Procedure_Symbol *procedure_symbol = Checked_Procedure_Symbol__create(context->checked_package, parsed_statement->super.name->location, symbol_name, parsed_statement->super.super.location, parsed_statement, procedure_type, receiver_type);
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

Checked_Statement *Checker__check_statement(Checker *self, Checker_Context *context, Parsed_Statement *parsed_statement, Checked_Type *expected_type) {
    if (context->is_unreachable_statement) {
        pWriter__begin_location_message(stderr_writer, parsed_statement->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Unreachable statement");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    switch (parsed_statement->kind) {
    case PARSED_STATEMENT_KIND__ASSIGNMENT:
        return Checker__check_assignment_statement(self, context, (Parsed_Assignment_Statement *)parsed_statement);
    case PARSED_STATEMENT_KIND__BLOCK:
        return (Checked_Statement *)Checker__check_block_statement(self, context, (Parsed_Block_Statement *)parsed_statement, expected_type);
    case PARSED_STATEMENT_KIND__BREAK:
        return Checker__check_break_statement(self, context, (Parsed_Break_Statement *)parsed_statement);
    case PARSED_STATEMENT_KIND__DEFER:
        return Checker__check_defer_statement(self, context, (Parsed_Defer_Statement *)parsed_statement);
    case PARSED_STATEMENT_KIND__EXPRESSION:
        return Checker__check_expression_statement(self, context, (Parsed_Expression_Statement *)parsed_statement);
    case PARSED_STATEMENT_KIND__IF:
        return Checker__check_if_statement(self, context, (Parsed_If_Statement *)parsed_statement);
    case PARSED_STATEMENT_KIND__LOOP:
        return Checker__check_loop_statement(self, context, (Parsed_Loop_Statement *)parsed_statement);
    case PARSED_STATEMENT_KIND__PANIC:
        return Checker__check_panic_statement(self, context, (Parsed_Panic_Statement *)parsed_statement);
    case PARSED_STATEMENT_KIND__RAISE:
        return Checker__check_raise_statement(self, context, (Parsed_Raise_Statement *)parsed_statement);
    case PARSED_STATEMENT_KIND__RETURN:
        return Checker__check_return_statement(self, context, (Parsed_Return_Statement *)parsed_statement);
    case PARSED_STATEMENT_KIND__SWITCH:
        return Checker__check_switch_statement(self, context, (Parsed_Switch_Statement *)parsed_statement);
    case PARSED_STATEMENT_KIND__VARIABLE:
        return Checker__check_variable_statement(self, context, (Parsed_Variable_Statement *)parsed_statement);
    case PARSED_STATEMENT_KIND__WHILE:
        return Checker__check_while_statement(self, context, (Parsed_While_Statement *)parsed_statement);
    case PARSED_STATEMENT_KIND__YIELD:
        return Checker__check_yield_statement(self, context, (Parsed_Yield_Statement *)parsed_statement, expected_type);
    default:
        break;
    }
    pWriter__begin_location_message(stderr_writer, parsed_statement->location, WRITER_STYLE__ERROR);
    pWriter__write__cstring(stderr_writer, "Unsupported statement kind");
    pWriter__end_location_message(stderr_writer);
    panic();
}

void Checker__check_procedure_definition(Checker *self, Checker_Context *context, Checked_Procedure_Symbol *procedure_symbol) {
    Checked_Procedure_Type *procedure_type = procedure_symbol->procedure_type;
    context->return_type = procedure_type->return_type;

    /* Create and push procedure symbols */
    self->symbols = Checked_Symbols__create(self->symbols);

    if (procedure_type->first_parameter != NULL) {
        /* Create a symbol for each procedure parameter */
        Checked_Procedure_Parameter *parameter = procedure_type->first_parameter;
        while (parameter != NULL) {
            Checked_Symbols__append_symbol(self->symbols, (Checked_Symbol *)Checked_Procedure_Parameter_Symbol__create(context->checked_package, parameter->location, parameter->name, parameter->type));
            parameter = parameter->next_parameter;
        }
    }

    /* Check statements */
    Checked_Block_Statement *checked_block_statement = Checker__check_block_statement(self, context, procedure_symbol->parsed_procedure_statement->block_statement, NULL);
    procedure_symbol->checked_block_statement = (Checked_Statement *)checked_block_statement;

    if (context->return_type->kind != CHECKED_TYPE_KIND__NOTHING) {
        if (!Checked_Statement__is_terminal((Checked_Statement *)checked_block_statement)) {
            Source_Location location = checked_block_statement->super.location;
            location.start_line = location.end_line;
            location.start_column = location.end_column;
            pWriter__begin_location_message(stderr_writer, location, WRITER_STYLE__ERROR);
            pWriter__write__cstring(stderr_writer, "Missing return statement");
            pWriter__end_location_message(stderr_writer);
            panic();
        }
    }

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

Checked_Procedure_Symbol *Checker__specialize_method(Checker *self, Checker_Context *context, Checked_Generic_Procedure_Symbol *generic_procedure_symbol, Checked_Type_Argument *first_type_argument) {
    self->symbols = Checked_Symbols__create(self->symbols);
    Checker__create_type_argument_symbols(self, first_type_argument);

    Checker_Context generic_procedure_context = Checker_Context__make(self, generic_procedure_symbol->super.package);
    Checked_Procedure_Symbol *procedure_symbol = Checker__check_procedure_declaration(self, &generic_procedure_context, generic_procedure_symbol->parsed_procedure_statement);
    procedure_symbol->first_type_argument = first_type_argument;

    self->symbols = self->symbols->parent;

    return procedure_symbol;
}

Checked_Named_Type *Checker__check_type_statement(Checker *self, Checker_Context *context, Parsed_Type_Statement *parsed_type_statement) {
    Token *type_name = parsed_type_statement->super.name;
    if (parsed_type_statement->first_type_parameter != NULL) {
        Checked_Generic_Type *generic_type = Checked_Generic_Type__create(type_name->location, type_name->lexeme, context->checked_package, parsed_type_statement);
        generic_type->super.super.symbol = Checker__create_type_symbol(self, context->checked_package, type_name->lexeme, (Checked_Named_Type *)generic_type);
        return (Checked_Named_Type *)generic_type;
    }
    switch (parsed_type_statement->type_specifier->kind) {
    case PARSED_TYPE_SPECIFIER_KIND__BUILTIN:
        return Checker__check_builtin_type_statement(self, context, type_name);
    case PARSED_TYPE_SPECIFIER_KIND__EXTERNAL:
        return Checker__check_external_type_statement(self, context, type_name);
    case PARSED_TYPE_SPECIFIER_KIND__STRUCT:
        return Checker__create_struct_type(self, context, type_name, (Parsed_Struct_Type_Specifier *)parsed_type_statement->type_specifier);
    case PARSED_TYPE_SPECIFIER_KIND__TRAIT:
        return Checker__check_trait_type_statement(self, context, type_name, (Parsed_Trait_Type_Specifier *)parsed_type_statement->type_specifier);
    case PARSED_TYPE_SPECIFIER_KIND__VARIANT:
        return Checker__create_variant_type(self, context, type_name, (Parsed_Variant_Type_Specifier *)parsed_type_statement->type_specifier);
    default:
        pWriter__begin_location_message(stderr_writer, parsed_type_statement->type_specifier->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Unsupported type specifier");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
}

Checked_Type_Argument *Checker__check_type_arguments(Checker *self, Checker_Context *context, Parsed_Type_Parameter *first_parsed_type_parameter, Parsed_Type_Argument *first_parsed_type_argument) {
    Checked_Type_Argument *first_type_argument = Checked_Type_Argument__create(first_parsed_type_parameter->name->location, first_parsed_type_parameter->name->lexeme, Checker__resolve_type(self, context, first_parsed_type_argument->type));
    Checked_Type_Argument *last_type_argument = first_type_argument;

    Parsed_Type_Parameter *parsed_type_parameter = first_parsed_type_parameter->next_type_parameter;
    Parsed_Type_Argument *parsed_type_argument = first_parsed_type_argument->next_type_argument;
    while (parsed_type_parameter != NULL && parsed_type_argument != NULL) {
        last_type_argument->next_type_argument = Checked_Type_Argument__create(parsed_type_parameter->name->location, parsed_type_parameter->name->lexeme, Checker__resolve_type(self, context, parsed_type_argument->type));
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

Checked_Named_Type *Checker__specialize_type(Checker *self, Checker_Context *context, Checked_Generic_Type *generic_type, Parsed_Named_Type *parsed_type) {
    Checked_Type_Argument *first_type_argument = Checker__check_type_arguments(self, context, generic_type->parsed_type_statement->first_type_parameter, parsed_type->first_type_argument);

    Checked_Named_Type *type = Checked_Symbols__find_specialized_type(self->global_symbols, generic_type, first_type_argument);
    if (type != NULL) {
        // TODO: delete created types arguments
        return type;
    }

    String *type_name = String__create_copy(parsed_type->name);
    Writer type_name_writer = String__create_writer(type_name);
    pWriter__write__char(&type_name_writer, '<');
    Checked_Type_Argument *type_argument = first_type_argument;
    pWriter__write__checked_type(&type_name_writer, type_argument->type);
    type_argument = type_argument->next_type_argument;
    while (type_argument != NULL) {
        pWriter__write__cstring(&type_name_writer, ", ");
        pWriter__write__checked_type(&type_name_writer, type_argument->type);
        type_argument = type_argument->next_type_argument;
    }
    pWriter__write__char(&type_name_writer, '>');

    self->symbols = Checked_Symbols__create(self->symbols);
    Checker__create_type_argument_symbols(self, first_type_argument);

    Token *type_name_token = (Token *)Identifier_Token__create(parsed_type->super.location, type_name);
    Checker_Context generic_type_context = Checker_Context__make(self, generic_type->super.package);
    switch (generic_type->parsed_type_statement->type_specifier->kind) {
    case PARSED_TYPE_SPECIFIER_KIND__STRUCT:
        type = Checker__create_struct_type(self, &generic_type_context, type_name_token, (Parsed_Struct_Type_Specifier *)generic_type->parsed_type_statement->type_specifier);
        if (type->needs_check) {
            Checker__check_struct_type(self, &generic_type_context, (Checked_Struct_Type *)type);
        }
        break;
    default:
        pWriter__begin_location_message(stderr_writer, parsed_type->super.location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Cannot specialize type ");
        pWriter__write__string(stderr_writer, generic_type->super.name);
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    // TODO: delete type_name_token

    type->generic_type = generic_type;
    type->first_type_argument = first_type_argument;

    self->symbols = self->symbols->parent;

    return type;
}

void Checker__check_package(Checker *self, Checker_Context *context);

Checked_Package *Checker__check_imported_package(Checker *self, Checker_Context *context, Parsed_Package *parsed_package) {
    Checker package_checker;

    package_checker.builtin_types = self->builtin_types;

    package_checker.global_symbols = package_checker.symbols = self->global_symbols;

    package_checker.packages = self->packages;

    package_checker.methods = self->methods;

    Checker_Context other_package_context = Checker_Context__make(self, Checker__create_package(self, parsed_package));
    Checker__check_package(&package_checker, &other_package_context);

    return other_package_context.checked_package;
}

void Checker__check_import_statement(Checker *self, Checker_Context *context, Parsed_Import_Statement *parsed_statement) {
    Checked_Symbol *symbol = Checked_Symbols__find_symbol(self->symbols, context->checked_package, parsed_statement->import_name);
    if (symbol != NULL) {
        if (symbol->kind == CHECKED_SYMBOL_KIND__IMPORT) {
            Checked_Import_Symbol *import_symbol = (Checked_Import_Symbol *)symbol;
            if (String__equals_string(import_symbol->other_package->name, parsed_statement->parsed_package->name)) {
                return; // Import already exists
            }
        }
        pWriter__begin_location_message(stderr_writer, parsed_statement->super.location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Import symbol conflicts with existing symbol");
        pWriter__end_location_message(stderr_writer);
        panic();
    }

    Checked_Package *package = Checked_Packages__find(self->packages, parsed_statement->parsed_package->name);

    if (package == NULL) {
        package = Checker__create_package(self, parsed_statement->parsed_package);
    }

    Checked_Import_Symbol *import_symbol = Checked_Import_Symbol__create(context->checked_package, parsed_statement->super.location, parsed_statement->import_name, (Checked_Type *)self->builtin_types->package_type, package);
    Checked_Symbols__append_symbol(self->symbols, (Checked_Symbol *)import_symbol);
}

void Checker__check_module(Checker *self, Checker_Context *context, Parsed_Module *parsed_module) {
    Parsed_Statement *parsed_statement;

    /* Collect other declarations */
    parsed_statement = parsed_module->statements->first_statement;
    while (parsed_statement != NULL) {
        Checked_Statement *checked_statement = NULL;
        switch (parsed_statement->kind) {
        case PARSED_STATEMENT_KIND__TYPE:
        case PARSED_STATEMENT_KIND__IMPORT:
            /* ignored */
            break;
        case PARSED_STATEMENT_KIND__PROCEDURE:
            if (((Parsed_Procedure_Statement *)parsed_statement)->first_type_parameter != NULL) {
                Checker__check_generic_procedure_declaration(self, context, (Parsed_Procedure_Statement *)parsed_statement);
            } else {
                Checker__check_procedure_declaration(self, context, (Parsed_Procedure_Statement *)parsed_statement);
            }
            break;
        case PARSED_STATEMENT_KIND__VARIABLE:
            checked_statement = (Checked_Statement *)Checker__check_variable_statement(self, context, (Parsed_Variable_Statement *)parsed_statement);
            break;
        case PARSED_STATEMENT_KIND__CONSTANT:
            checked_statement = (Checked_Statement *)Checker__check_constant_statement(self, context, (Parsed_Constant_Statement *)parsed_statement);
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

void Checker__check_all_import_statements(Checker *self) {
    Checked_Package *checked_package = self->packages->first_package;
    while (checked_package != NULL) {
        Checker_Context context = Checker_Context__make(self, checked_package);
        Parsed_Module *parsed_module = checked_package->parsed_package->first_module;
        while (parsed_module != NULL) {
            Parsed_Statement *parsed_statement = parsed_module->statements->first_statement;
            while (parsed_statement != NULL) {
                if (parsed_statement->kind == PARSED_STATEMENT_KIND__IMPORT) {
                    Checker__check_import_statement(self, &context, (Parsed_Import_Statement *)parsed_statement);
                }
                parsed_statement = parsed_statement->next_statement;
            }
            parsed_module = parsed_module->next_module;
        }
        checked_package = checked_package->next_package;
    }
}

void Checker__check_all_types(Checker *self) {
    Checked_Package *checked_package = self->packages->first_package;
    while (checked_package != NULL) {
        Checker_Context context = Checker_Context__make(self, checked_package);
        Parsed_Module *parsed_module = checked_package->parsed_package->first_module;
        while (parsed_module != NULL) {
            Parsed_Statement *parsed_statement = parsed_module->statements->first_statement;
            while (parsed_statement != NULL) {
                if (parsed_statement->kind == PARSED_STATEMENT_KIND__TYPE) {
                    Checker__check_type_statement(self, &context, (Parsed_Type_Statement *)parsed_statement);
                }
                parsed_statement = parsed_statement->next_statement;
            }
            parsed_module = parsed_module->next_module;
        }
        checked_package = checked_package->next_package;
    }

    Checked_Symbol *symbol = self->global_symbols->first_symbol;
    while (symbol != NULL) {
        if (symbol->kind == CHECKED_SYMBOL_KIND__TYPE) {
            Checked_Type_Symbol *type_symbol = (Checked_Type_Symbol *)symbol;
            if (type_symbol->named_type->needs_check) {
                Checker_Context context = Checker_Context__make(self, symbol->package);
                switch (type_symbol->named_type->super.kind) {
                case CHECKED_TYPE_KIND__STRUCT:
                    Checker__check_struct_type(self, &context, (Checked_Struct_Type *)type_symbol->named_type);
                    break;
                case CHECKED_TYPE_KIND__VARIANT:
                    Checker__check_variant_type(self, &context, (Checked_Variant_Type *)type_symbol->named_type);
                    break;
                default:
                    pWriter__begin_location_message(stderr_writer, type_symbol->named_type->super.location, WRITER_STYLE__ERROR);
                    pWriter__write__cstring(stderr_writer, "Unexpected type kind");
                    pWriter__end_location_message(stderr_writer);
                    panic();
                }
            }
        }
        symbol = symbol->next_symbol;
    }
}

void Checker__check_package(Checker *self, Checker_Context *context) {
    Parsed_Module *parsed_module = context->checked_package->parsed_package->first_module;
    while (parsed_module != NULL) {
        Checker__check_module(self, context, parsed_module);
        parsed_module = parsed_module->next_module;
    }
}

void Checker__check_builtin_package(Checker *self, Parsed_Package *parsed_package) {
    Checker package_checker;

    package_checker.builtin_types = self->builtin_types;

    package_checker.global_symbols = package_checker.symbols = self->builtin_types->symbols;

    package_checker.packages = self->packages;

    Checker_Context context = Checker_Context__make(&package_checker, Checker__create_package(self, parsed_package));
    self->packages->builtin_package = context.checked_package;

    package_checker.methods = self->methods;

    Checker__check_all_types(&package_checker);
    Checker__check_package(&package_checker, &context);
}

Checked_Source *check(Parsed_Package *parsed_builtin_package, Parsed_Package *parsed_package) {
    Checker *checker = Checker__create();

    Checker__check_builtin_package(checker, parsed_builtin_package);
    checker->packages->first_package = checker->packages->last_package = NULL; // Reset package list

    Checked_Package *checked_package = Checker__create_package(checker, parsed_package);
    Checker__check_all_import_statements(checker);
    Checker__check_all_types(checker);

    while (checked_package != NULL) {
        Checker_Context context = Checker_Context__make(checker, checked_package);
        Checker__check_package(checker, &context);
        checked_package = checked_package->next_package;
    }

    /* Check procedure definitions from all packages */
    Checked_Symbol *symbol = checker->global_symbols->first_symbol;
    while (symbol != NULL) {
        if (symbol->kind == CHECKED_SYMBOL_KIND__PROCEDURE) {
            Checked_Procedure_Symbol *procedure_symbol = (Checked_Procedure_Symbol *)symbol;
            Parsed_Procedure_Statement *procedure_statement = procedure_symbol->parsed_procedure_statement;
            if (!procedure_statement->is_external) {
                if (procedure_statement->block_statement == NULL) {
                    pWriter__begin_location_message(stderr_writer, procedure_statement->super.name->location, WRITER_STYLE__ERROR);
                    pWriter__write__cstring(stderr_writer, "Missing procedure body");
                    pWriter__end_location_message(stderr_writer);
                    panic();
                }
                if (procedure_symbol->first_type_argument != NULL) {
                    checker->symbols = Checked_Symbols__create(checker->symbols);
                    Checker__create_type_argument_symbols(checker, procedure_symbol->first_type_argument);
                }
                Checker_Context context = Checker_Context__make(checker, procedure_symbol->super.package);
                Checker__check_procedure_definition(checker, &context, procedure_symbol);
                if (procedure_symbol->first_type_argument != NULL) {
                    checker->symbols = checker->symbols->parent;
                }
            } else if (procedure_statement->block_statement != NULL) {
                pWriter__begin_location_message(stderr_writer, procedure_statement->super.name->location, WRITER_STYLE__ERROR);
                pWriter__write__cstring(stderr_writer, "External procedure with body");
                pWriter__end_location_message(stderr_writer);
                panic();
            }
        }
        symbol = symbol->next_symbol;
    }

    Checked_Source *checked_source = (Checked_Source *)malloc(sizeof(Checked_Source));
    checked_source->first_package = checker->packages->first_package;
    checked_source->builtin_package = checker->packages->builtin_package;
    checked_source->symbols = checker->global_symbols;
    checked_source->bool_type = (Checked_Type *)checker->builtin_types->bool_type;

    return checked_source;
}
