#include "Checked_Source.h"
#include "File.h"

Checked_Type *Checked_Type__create_kind(Checked_Type_Kind kind, size_t kind_size, Source_Location location) {
    Checked_Type *type = (Checked_Type *)malloc(kind_size);
    type->kind = kind;
    type->location = location;
    type->symbol = NULL;
    type->next_type = NULL;
    type->first_dependency = NULL;
    type->has_generated_definition = false;
    return type;
}

bool Checked_Type__is_numeric_type(Checked_Type *self) {
    switch (self->kind) {
    case CHECKED_TYPE_KIND__I16:
    case CHECKED_TYPE_KIND__I32:
    case CHECKED_TYPE_KIND__I64:
    case CHECKED_TYPE_KIND__I8:
    case CHECKED_TYPE_KIND__ISIZE:
    case CHECKED_TYPE_KIND__U16:
    case CHECKED_TYPE_KIND__U32:
    case CHECKED_TYPE_KIND__U64:
    case CHECKED_TYPE_KIND__U8:
    case CHECKED_TYPE_KIND__USIZE:
        return true;
    default:
        return false;
    }
}

void String__append_mangled_type_name(String *self, Checked_Type *type) {
    switch (type->kind) {
    case CHECKED_TYPE_KIND__MULTI_POINTER: {
        Checked_Multi_Pointer_Type *multi_pointer_type = (Checked_Multi_Pointer_Type *)type;
        String__append_cstring(self, "d_");
        String__append_mangled_type_name(self, multi_pointer_type->item_type);
        String__append_cstring(self, "_b");
        break;
    }
    case CHECKED_TYPE_KIND__POINTER: {
        String__append_char(self, 'p');
        String__append_mangled_type_name(self, ((Checked_Pointer_Type *)type)->other_type);
        break;
    }
    case CHECKED_TYPE_KIND__BOOL:
    case CHECKED_TYPE_KIND__EXTERNAL:
    case CHECKED_TYPE_KIND__GENERIC:
    case CHECKED_TYPE_KIND__I16:
    case CHECKED_TYPE_KIND__I32:
    case CHECKED_TYPE_KIND__I64:
    case CHECKED_TYPE_KIND__I8:
    case CHECKED_TYPE_KIND__STR:
    case CHECKED_TYPE_KIND__STRUCT:
    case CHECKED_TYPE_KIND__TRAIT:
    case CHECKED_TYPE_KIND__U16:
    case CHECKED_TYPE_KIND__U32:
    case CHECKED_TYPE_KIND__U64:
    case CHECKED_TYPE_KIND__U8:
    case CHECKED_TYPE_KIND__UNION: {
        Checked_Named_Type *checked_named_type = (Checked_Named_Type *)type;
        if (checked_named_type->module != NULL) {
            String__append_string(self, checked_named_type->module->name);
            String__append_char(self, '_');
        }
        if (checked_named_type->generic_type != NULL) {
            String__append_string(self, checked_named_type->generic_type->super.name);
            Checked_Type_Argument *type_argument = checked_named_type->first_type_argument;
            while (type_argument != NULL) {
                String__append_cstring(self, "__");
                String__append_mangled_type_name(self, type_argument->type);
                type_argument = type_argument->next_type_argument;
            }
        } else {
            String__append_string(self, checked_named_type->name);
        }
        break;
    }
    default:
        todo("Handle unexpected Checked_Type_Kind");
    }
}

Checked_Array_Type *Checked_Array_Type__create(Source_Location location, Checked_Type *item_type, Checked_Expression *size_expression) {
    Checked_Array_Type *type = (Checked_Array_Type *)Checked_Type__create_kind(CHECKED_TYPE_KIND__ARRAY, sizeof(Checked_Array_Type), location);
    type->item_type = item_type;
    type->size_expression = size_expression;
    return type;
}

bool Checked_Array_Type__equals(Checked_Array_Type *self, Checked_Array_Type *other) {
    if (!Checked_Type__equals(self->item_type, other->item_type)) {
        return false;
    }
    if (self->size_expression == NULL) {
        return other->size_expression == NULL;
    }
    if (other->size_expression == NULL) {
        return false;
    }
    // TODO: check size expressions
    panic();
}

Checked_Named_Type *Checked_Named_Type__create_kind(Checked_Type_Kind kind, size_t kind_size, Source_Location location, String *name, Checked_Module *module) {
    Checked_Named_Type *type = (Checked_Named_Type *)Checked_Type__create_kind(kind, kind_size, location);
    type->name = name;
    type->module = module;
    return type;
}

Checked_Generic_Type *Checked_Generic_Type__create(Source_Location location, String *name, Checked_Module *module, Parsed_Type_Statement *parsed_type_statement) {
    Checked_Generic_Type *type = (Checked_Generic_Type *)Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__GENERIC, sizeof(Checked_Generic_Type), location, name, module);
    type->parsed_type_statement = parsed_type_statement;
    return type;
}

Checked_External_Type *Checked_External_Type__create(Source_Location location, String *name, Checked_Module *module) {
    Checked_External_Type *type = (Checked_External_Type *)Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__EXTERNAL, sizeof(Checked_External_Type), location, name, module);
    return type;
}

Checked_Procedure_Parameter *Checked_Procedure_Parameter__create(Source_Location location, String *label, String *name, Checked_Type *type) {
    Checked_Procedure_Parameter *parameter = (Checked_Procedure_Parameter *)malloc(sizeof(Checked_Procedure_Parameter));
    parameter->location = location;
    parameter->label = label;
    parameter->name = name;
    parameter->type = type;
    parameter->next_parameter = NULL;
    return parameter;
}

Checked_Procedure_Type *Checked_Procedure_Type__create(Source_Location location, Checked_Procedure_Parameter *first_parameter, Checked_Type *return_type) {
    Checked_Procedure_Type *type = (Checked_Procedure_Type *)Checked_Type__create_kind(CHECKED_TYPE_KIND__PROCEDURE, sizeof(Checked_Procedure_Type), location);
    type->first_parameter = first_parameter;
    type->return_type = return_type;
    return type;
}

bool Checked_Procedure_Type__equals(Checked_Procedure_Type *self, Checked_Procedure_Type *other) {
    if (!Checked_Type__equals(self->return_type, other->return_type)) {
        return false;
    }
    Checked_Procedure_Parameter *self_parameter = self->first_parameter;
    Checked_Procedure_Parameter *other_parameter = other->first_parameter;
    while (self_parameter != NULL && other_parameter != NULL) {
        if (self_parameter->label != NULL && other_parameter->label != NULL) {
            if (!String__equals_string(self_parameter->label, other_parameter->label)) {
                return false;
            }
        } else if (self_parameter->label != NULL || other_parameter->label != NULL) {
            return false;
        }
        if (!Checked_Type__equals(self_parameter->type, other_parameter->type)) {
            return false;
        }
        self_parameter = self_parameter->next_parameter;
        other_parameter = other_parameter->next_parameter;
    }
    if (self_parameter != NULL || other_parameter != NULL) {
        return false;
    }
    return true;
}

Checked_Procedure_Pointer_Type *Checked_Procedure_Pointer_Type__create(Source_Location location, Checked_Procedure_Type *procedure_type) {
    Checked_Procedure_Pointer_Type *type = (Checked_Procedure_Pointer_Type *)Checked_Type__create_kind(CHECKED_TYPE_KIND__PROCEDURE_POINTER, sizeof(Checked_Procedure_Pointer_Type), location);
    type->procedure_type = procedure_type;
    return type;
}

bool Checked_Procedure_Pointer_Type__equals(Checked_Procedure_Pointer_Type *self, Checked_Procedure_Pointer_Type *other) {
    return Checked_Procedure_Type__equals(self->procedure_type, other->procedure_type);
}

Checked_Multi_Pointer_Type *Checked_Multi_Pointer_Type__create(Source_Location location, Checked_Type *item_type) {
    Checked_Multi_Pointer_Type *type = (Checked_Multi_Pointer_Type *)Checked_Type__create_kind(CHECKED_TYPE_KIND__MULTI_POINTER, sizeof(Checked_Multi_Pointer_Type), location);
    type->item_type = item_type;
    return type;
}

bool Checked_Multi_Pointer_Type__equals(Checked_Multi_Pointer_Type *self, Checked_Multi_Pointer_Type *other) {
    return Checked_Type__equals(self->item_type, other->item_type);
}

Checked_Pointer_Type *Checked_Pointer_Type__create(Source_Location location, Checked_Type *other_type) {
    Checked_Pointer_Type *type = (Checked_Pointer_Type *)Checked_Type__create_kind(CHECKED_TYPE_KIND__POINTER, sizeof(Checked_Pointer_Type), location);
    type->other_type = other_type;
    return type;
}

bool Checked_Pointer_Type__equals(Checked_Pointer_Type *self, Checked_Pointer_Type *other) {
    return Checked_Type__equals(self->other_type, other->other_type);
}

Checked_Type_Argument *Checked_Type_Argument__create(Source_Location location, String *name, Checked_Type *type) {
    Checked_Type_Argument *type_argument = (Checked_Type_Argument *)malloc(sizeof(Checked_Type_Argument));
    type_argument->location = location;
    type_argument->name = name;
    type_argument->type = type;
    type_argument->next_type_argument = NULL;
    return type_argument;
}

Checked_Struct_Member *Checked_Struct_Member__create(Source_Location location, String *name, Checked_Type *type) {
    Checked_Struct_Member *member = (Checked_Struct_Member *)malloc(sizeof(Checked_Struct_Member));
    member->location = location;
    member->name = name;
    member->type = type;
    member->next_member = NULL;
    return member;
}

Checked_Struct_Type *Checked_Struct_Type__create(Source_Location location, String *name, Checked_Module *module, Parsed_Struct_Type_Specifier *parsed_type_specifier) {
    Checked_Struct_Type *type = (Checked_Struct_Type *)Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__STRUCT, sizeof(Checked_Struct_Type), location, name, module);
    type->first_member = NULL;
    type->parsed_type_specifier = parsed_type_specifier;
    return type;
}

Checked_Struct_Member *Checked_Struct_Type__find_member(Checked_Struct_Type *self, String *name) {
    Checked_Struct_Member *member = self->first_member;
    while (member != NULL) {
        if (String__equals_string(name, member->name)) {
            break;
        }
        member = member->next_member;
    }
    return member;
}

bool Checked_Struct_Type__equals(Checked_Struct_Type *self, Checked_Struct_Type *other) {
    return String__equals_string(self->super.name, other->super.name);
}

bool Checked_Trait_Type__equals(Checked_Trait_Type *self, Checked_Trait_Type *other) {
    return String__equals_string(self->super.name, other->super.name);
}

bool Checked_Union_Type__equals(Checked_Union_Type *self, Checked_Union_Type *other) {
    return String__equals_string(self->super.name, other->super.name);
}

Checked_Trait_Method *Checked_Trait_Method__create(Source_Location location, String *name, Checked_Procedure_Type *procedure_type, Checked_Struct_Member *struct_member) {
    Checked_Trait_Method *method = (Checked_Trait_Method *)malloc(sizeof(Checked_Trait_Method));
    method->location = location;
    method->name = name;
    method->procedure_type = procedure_type;
    method->struct_member = struct_member;
    method->next_method = NULL;
    return method;
}

Checked_Trait_Type *Checked_Trait_Type__create(Source_Location location, String *name, Checked_Module *module) {
    Checked_Trait_Type *type = (Checked_Trait_Type *)Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__TRAIT, sizeof(Checked_Trait_Type), location, name, module);
    type->struct_type = NULL;
    type->self_struct_member = NULL;
    type->first_method = NULL;
    return type;
}

Checked_Union_Variant *Checked_Union_Variant__create(Source_Location location, Checked_Type *type, int32_t index) {
    Checked_Union_Variant *member = (Checked_Union_Variant *)malloc(sizeof(Checked_Union_Variant));
    member->type = type;
    member->next_variant = NULL;
    member->index = index;
    return member;
}

Checked_Union_Type *Checked_Union_Type__create(Source_Location location, String *name, Checked_Module *module) {
    Checked_Union_Type *type = (Checked_Union_Type *)Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__UNION, sizeof(Checked_Union_Type), location, name, module);
    type->first_variant = NULL;
    type->variant_count = 0;
    return type;
}

bool Checked_Type__equals(Checked_Type *self, Checked_Type *other) {
    if (self == other) {
        return true;
    }
    if (self->kind != other->kind) {
        return false;
    }
    switch (self->kind) {
    case CHECKED_TYPE_KIND__ARRAY:
        return Checked_Array_Type__equals((Checked_Array_Type *)self, (Checked_Array_Type *)other);
    case CHECKED_TYPE_KIND__PROCEDURE:
        return Checked_Procedure_Type__equals((Checked_Procedure_Type *)self, (Checked_Procedure_Type *)other);
    case CHECKED_TYPE_KIND__PROCEDURE_POINTER:
        return Checked_Procedure_Pointer_Type__equals((Checked_Procedure_Pointer_Type *)self, (Checked_Procedure_Pointer_Type *)other);
    case CHECKED_TYPE_KIND__MULTI_POINTER:
        return Checked_Multi_Pointer_Type__equals((Checked_Multi_Pointer_Type *)self, (Checked_Multi_Pointer_Type *)other);
    case CHECKED_TYPE_KIND__POINTER:
        return Checked_Pointer_Type__equals((Checked_Pointer_Type *)self, (Checked_Pointer_Type *)other);
    case CHECKED_TYPE_KIND__STRUCT:
        return Checked_Struct_Type__equals((Checked_Struct_Type *)self, (Checked_Struct_Type *)other);
    case CHECKED_TYPE_KIND__TRAIT:
        return Checked_Trait_Type__equals((Checked_Trait_Type *)self, (Checked_Trait_Type *)other);
    case CHECKED_TYPE_KIND__UNION:
        return Checked_Union_Type__equals((Checked_Union_Type *)self, (Checked_Union_Type *)other);
    default:
        break;
    }
    todo("Handle unexpected Checked_Type_Kind");
}

void pWriter__write__checked_type(Writer *self, Checked_Type *type) {
    switch (type->kind) {
    case CHECKED_TYPE_KIND__BOOL:
    case CHECKED_TYPE_KIND__I16:
    case CHECKED_TYPE_KIND__I32:
    case CHECKED_TYPE_KIND__I64:
    case CHECKED_TYPE_KIND__I8:
    case CHECKED_TYPE_KIND__ISIZE:
    case CHECKED_TYPE_KIND__MODULE:
    case CHECKED_TYPE_KIND__NIL:
    case CHECKED_TYPE_KIND__U16:
    case CHECKED_TYPE_KIND__U32:
    case CHECKED_TYPE_KIND__U64:
    case CHECKED_TYPE_KIND__U8:
    case CHECKED_TYPE_KIND__USIZE:
    case CHECKED_TYPE_KIND__ANY:
    case CHECKED_TYPE_KIND__EXTERNAL:
    case CHECKED_TYPE_KIND__GENERIC:
    case CHECKED_TYPE_KIND__STRUCT:
    case CHECKED_TYPE_KIND__TRAIT:
    case CHECKED_TYPE_KIND__UNION: {
        Checked_Named_Type *named_type = (Checked_Named_Type *)type;
        if (named_type->module != NULL) {
            pWriter__write__string(self, named_type->module->name);
            pWriter__write__char(self, '.');
        }
        pWriter__write__string(self, named_type->name);
        break;
    }
    case CHECKED_TYPE_KIND__PROCEDURE: {
        Checked_Procedure_Type *procedure_type = (Checked_Procedure_Type *)type;
        pWriter__write__cstring(self, "proc (");
        Checked_Procedure_Parameter *procedure_parameter = procedure_type->first_parameter;
        while (procedure_parameter != NULL) {
            if (procedure_parameter->label != NULL) {
                pWriter__write__string(self, procedure_parameter->label);
            } else {
                pWriter__write__cstring(self, "anon");
            }
            pWriter__write__cstring(self, ": ");
            pWriter__write__checked_type(self, procedure_parameter->type);
            procedure_parameter = procedure_parameter->next_parameter;
            if (procedure_parameter != NULL) {
                pWriter__write__cstring(self, ", ");
            }
        }
        if (procedure_type->return_type->kind != CHECKED_TYPE_KIND__NOTHING) {
            pWriter__write__cstring(self, ") -> ");
            pWriter__write__checked_type(self, procedure_type->return_type);
        } else {
            pWriter__write__char(self, ')');
        }
        break;
    }
    case CHECKED_TYPE_KIND__PROCEDURE_POINTER: {
        Checked_Procedure_Pointer_Type *procedure_pointer_type = (Checked_Procedure_Pointer_Type *)type;
        pWriter__write__char(self, '^');
        pWriter__write__checked_type(self, (Checked_Type *)procedure_pointer_type->procedure_type);
        break;
    }
    case CHECKED_TYPE_KIND__MULTI_POINTER: {
        Checked_Multi_Pointer_Type *multi_pointer_type = (Checked_Multi_Pointer_Type *)type;
        pWriter__write__cstring(self, "[^]");
        pWriter__write__checked_type(self, multi_pointer_type->item_type);
        break;
    }
    case CHECKED_TYPE_KIND__NULL: {
        pWriter__write__cstring(self, "null");
        break;
    }
    case CHECKED_TYPE_KIND__POINTER: {
        Checked_Pointer_Type *pointer_type = (Checked_Pointer_Type *)type;
        pWriter__write__char(self, '^');
        pWriter__write__checked_type(self, pointer_type->other_type);
        break;
    }
    case CHECKED_TYPE_KIND__STR: {
        pWriter__write__cstring(self, "str");
        break;
    }
    case CHECKED_TYPE_KIND__TYPE: {
        pWriter__write__cstring(self, "type");
        break;
    }
    default:
        panic();
    }
}

Checked_Module *Checked_Module__create(String *name, Source *source) {
    Checked_Module *module = (Checked_Module *)malloc(sizeof(Checked_Module));
    module->name = name;
    module->source = source;
    module->next_module = NULL;
    return module;
}

void Checked_Modules__append(Checked_Modules *self, Checked_Module *module) {
    if (self->first_module == NULL) {
        self->first_module = module;
    } else {
        self->last_module->next_module = module;
    }
    self->last_module = module;
}

Checked_Module *Checked_Modules__find(Checked_Modules *self, String *name) {
    Checked_Module *module = self->first_module;
    while (module != NULL) {
        if (String__equals_string(module->name, name)) {
            return module;
        }
        module = module->next_module;
    }
    return NULL;
}

Checked_Symbol *Checked_Symbol__create_kind(Checked_Symbol_Kind kind, size_t kind_size, Checked_Module *module, Source_Location location, String *name, Checked_Type *type, bool is_global) {
    Checked_Symbol *symbol = (Checked_Symbol *)malloc(kind_size);
    symbol->kind = kind;
    symbol->module = module;
    symbol->location = location;
    symbol->name = name;
    symbol->type = type;
    symbol->is_global = is_global;
    symbol->prev_symbol = NULL;
    symbol->next_symbol = NULL;
    return symbol;
}

Checked_Enum_Member_Symbol *Checked_Enum_Member_Symbol__create(Checked_Module *module, Source_Location location, String *name, Checked_Type *type) {
    return (Checked_Enum_Member_Symbol *)Checked_Symbol__create_kind(CHECKED_SYMBOL_KIND__ENUM_MEMBER, sizeof(Checked_Enum_Member_Symbol), module, location, name, type, true);
}

Checked_External_Symbol *Checked_External_Symbol__create(Source_Location location, String *name, Checked_Symbol *other_symbol) {
    Checked_External_Symbol *external_symbol = (Checked_External_Symbol *)Checked_Symbol__create_kind(CHECKED_SYMBOL_KIND__EXTERNAL, sizeof(Checked_External_Symbol), NULL, location, name, other_symbol->type, true);
    external_symbol->other_symbol = other_symbol;
    return external_symbol;
}

Checked_Generic_Procedure_Symbol *Checked_Generic_Procedure_Symbol__create(Checked_Module *module, Source_Location location, String *name, Checked_Type *receiver_type, Parsed_Procedure_Statement *parsed_procedure_statement) {
    Checked_Generic_Procedure_Symbol *symbol = (Checked_Generic_Procedure_Symbol *)Checked_Symbol__create_kind(CHECKED_SYMBOL_KIND__GENERIC_PROCEDURE, sizeof(Checked_Generic_Procedure_Symbol), module, location, name, NULL, true);
    symbol->receiver_type = receiver_type;
    symbol->parsed_procedure_statement = parsed_procedure_statement;
    return symbol;
}

Checked_Import_Symbol *Checked_Import_Symbol__create(Checked_Module *module, Source_Location location, String *name, Checked_Type *type, Checked_Module *other_module) {
    Checked_Import_Symbol *import_symbol = (Checked_Import_Symbol *)Checked_Symbol__create_kind(CHECKED_SYMBOL_KIND__IMPORT, sizeof(Checked_Import_Symbol), module, location, name, type, true);
    import_symbol->other_module = other_module;
    return import_symbol;
}

Checked_Procedure_Symbol *Checked_Procedure_Symbol__create(Checked_Module *module, Source_Location location, String *symbol_name, Source_Location procedure_location, Parsed_Procedure_Statement *parsed_procedure_statement, Checked_Procedure_Type *procedure_type, Checked_Type *receiver_type) {
    Checked_Procedure_Symbol *symbol = (Checked_Procedure_Symbol *)Checked_Symbol__create_kind(CHECKED_SYMBOL_KIND__PROCEDURE, sizeof(Checked_Procedure_Symbol), module, location, symbol_name, (Checked_Type *)Checked_Procedure_Pointer_Type__create(procedure_type->super.location, procedure_type), true);
    symbol->procedure_location = procedure_location;
    symbol->parsed_procedure_statement = parsed_procedure_statement;
    symbol->first_type_argument = NULL;
    symbol->procedure_name = parsed_procedure_statement->super.name->lexeme;
    symbol->procedure_type = procedure_type;
    symbol->receiver_type = receiver_type;
    symbol->checked_statements = NULL;
    symbol->external_name = NULL;
    return symbol;
}

void pWriter__write__checked_procedure_symbol(Writer *writer, Checked_Procedure_Symbol *procedure_symbol) {
    pWriter__write__cstring(writer, "proc ");
    Checked_Procedure_Parameter *parameter = procedure_symbol->procedure_type->first_parameter;
    if (procedure_symbol->receiver_type != NULL) {
        pWriter__write__char(writer, '(');
        pWriter__write__checked_type(writer, procedure_symbol->receiver_type);
        pWriter__write__cstring(writer, ").");
        pWriter__write__string(writer, procedure_symbol->procedure_name);
        pWriter__write__cstring(writer, "(anon");
        if (parameter != NULL) {
            if (!Checked_Type__equals(procedure_symbol->receiver_type, parameter->type) && parameter->label != NULL) {
                // Parameter type mismatch: expected the receiver type.
                panic();
            }
            parameter = parameter->next_parameter;
            if (parameter != NULL) {
                pWriter__write__cstring(writer, ", ");
            }
        }
    } else {
        pWriter__write__string(writer, procedure_symbol->procedure_name);
        pWriter__write__char(writer, '(');
    }
    while (parameter != NULL) {
        if (parameter->label != NULL) {
            pWriter__write__string(writer, parameter->label);
        } else {
            pWriter__write__cstring(writer, "anon");
        }
        pWriter__write__cstring(writer, ": ");
        pWriter__write__checked_type(writer, parameter->type);
        parameter = parameter->next_parameter;
        if (parameter != NULL) {
            pWriter__write__cstring(writer, ", ");
        }
    }
    pWriter__write__char(writer, ')');
    if (procedure_symbol->procedure_type->return_type->kind != CHECKED_TYPE_KIND__NOTHING) {
        pWriter__write__cstring(writer, " -> ");
        pWriter__write__checked_type(writer, procedure_symbol->procedure_type->return_type);
    }
}

Checked_Procedure_Parameter_Symbol *Checked_Procedure_Parameter_Symbol__create(Checked_Module *module, Source_Location location, String *name, Checked_Type *type) {
    return (Checked_Procedure_Parameter_Symbol *)Checked_Symbol__create_kind(CHECKED_SYMBOL_KIND__PROCEDURE_PARAMETER, sizeof(Checked_Procedure_Parameter_Symbol), module, location, name, type, false);
}

Checked_Type_Symbol *Checked_Type_Symbol__create(Checked_Module *module, Source_Location location, String *name, Checked_Type *type, Checked_Named_Type *named_type) {
    Checked_Type_Symbol *symbol = (Checked_Type_Symbol *)Checked_Symbol__create_kind(CHECKED_SYMBOL_KIND__TYPE, sizeof(Checked_Type_Symbol), module, location, name, type, true);
    symbol->named_type = named_type;
    return symbol;
}

Checked_Type_Argument_Symbol *Checked_Type_Argument_Symbol__create(Source_Location location, String *name, Checked_Type *type, Checked_Type *argument_type) {
    Checked_Type_Argument_Symbol *symbol = (Checked_Type_Argument_Symbol *)Checked_Symbol__create_kind(CHECKED_SYMBOL_KIND__TYPE_ARGUMENT, sizeof(Checked_Type_Argument_Symbol), NULL, location, name, type, true);
    symbol->argument_type = argument_type;
    return symbol;
}

Checked_Variable_Symbol *Checked_Variable_Symbol__create(Checked_Module *module, Source_Location location, String *name, Checked_Type *type, bool is_global) {
    Checked_Variable_Symbol *variable = (Checked_Variable_Symbol *)Checked_Symbol__create_kind(CHECKED_SYMBOL_KIND__VARIABLE, sizeof(Checked_Variable_Symbol), module, location, name, type, is_global);
    variable->external_name = NULL;
    variable->statement = NULL;
    return variable;
}

Checked_Union_Switch_Variant_Symbol *Checked_Union_Switch_Variant_Symbol__create(Checked_Module *module, Source_Location location, String *name, Checked_Expression *union_expression, Checked_Union_Variant *union_variant) {
    Checked_Union_Switch_Variant_Symbol *symbol = (Checked_Union_Switch_Variant_Symbol *)Checked_Symbol__create_kind(CHECKED_SYMBOL_KIND__UNION_SWITCH_VARIANT, sizeof(Checked_Union_Switch_Variant_Symbol), module, location, name, union_variant->type, true);
    symbol->union_expression = union_expression;
    symbol->union_variant = union_variant;
    return symbol;
}

Checked_Symbols *Checked_Symbols__create(Checked_Symbols *parent) {
    Checked_Symbols *symbols = (Checked_Symbols *)malloc(sizeof(Checked_Symbols));
    symbols->parent = parent;
    symbols->first_symbol = NULL;
    symbols->last_symbol = NULL;
    return symbols;
}

Checked_Symbol *Checked_Symbols__find_sibling_symbol(Checked_Symbols *self, Checked_Module *module, String *name) {
    Checked_Symbol *symbol = self->first_symbol;
    while (symbol != NULL) {
        if (module == symbol->module && String__equals_string(name, symbol->name)) {
            return symbol;
        }
        symbol = symbol->next_symbol;
    }
    return NULL;
}

void Checked_Symbols__append_symbol(Checked_Symbols *self, Checked_Symbol *symbol) {
    Checked_Symbol *other_symbol = Checked_Symbols__find_sibling_symbol(self, symbol->module, symbol->name);
    if (other_symbol != NULL) {
        pWriter__begin_location_message(stderr_writer, symbol->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Symbol already defined here: ");
        pWriter__write__location(stderr_writer, other_symbol->location);
        pWriter__end_location_message(stderr_writer);
        panic();
    }

    if (self->last_symbol == NULL) {
        self->first_symbol = symbol;
    } else {
        self->last_symbol->next_symbol = symbol;
        symbol->prev_symbol = self->last_symbol;
    }
    self->last_symbol = symbol;
}

Checked_Symbol *Checked_Symbols__find_symbol(Checked_Symbols *self, Checked_Module *module, String *name) {
    Checked_Symbols *symbols = self;
    while (symbols != NULL) {
        Checked_Symbol *symbol = symbols->last_symbol;
        while (symbol != NULL) {
            if (module == symbol->module && String__equals_string(name, symbol->name)) {
                return symbol;
            }
            symbol = symbol->prev_symbol;
        }
        symbols = symbols->parent;
    }
    return NULL;
}

Checked_Expression *Checked_Expression__create_kind(Checked_Expression_Kind kind, size_t kind_size, Source_Location location, Checked_Type *type) {
    Checked_Expression *expression = (Checked_Expression *)malloc(kind_size);
    expression->kind = kind;
    expression->location = location;
    expression->type = type;
    expression->temp_variable_name = NULL;
    return expression;
}

bool Checked_Expression__is_mutable(Checked_Expression *self) {
    switch (self->kind) {
    case CHECKED_EXPRESSION_KIND__ARRAY_ACCESS: {
        Checked_Array_Access_Expression *array_access_expression = (Checked_Array_Access_Expression *)self;
        Checked_Expression *array_expression = array_access_expression->array_expression;
        Checked_Type *array_type = array_expression->type;
        return array_type->kind == CHECKED_TYPE_KIND__MULTI_POINTER || Checked_Expression__is_mutable(array_expression);
    }
    case CHECKED_EXPRESSION_KIND__DEREFERENCE:
        return true;
    case CHECKED_EXPRESSION_KIND__MEMBER_ACCESS: {
        Checked_Member_Access_Expression *member_access_expression = (Checked_Member_Access_Expression *)self;
        Checked_Expression *object_expression = member_access_expression->object_expression;
        Checked_Type *object_type = object_expression->type;
        return object_type->kind == CHECKED_TYPE_KIND__POINTER || Checked_Expression__is_mutable(object_expression);
    }
    case CHECKED_EXPRESSION_KIND__SYMBOL: {
        Checked_Symbol_Expression *symbol_expression = (Checked_Symbol_Expression *)self;
        Checked_Symbol *symbol = symbol_expression->symbol;
        return symbol->kind == CHECKED_SYMBOL_KIND__VARIABLE;
    }
    default:
        return false;
    }
}

Checked_Alloc_Expression *Checked_Alloc_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *value_expression) {
    Checked_Alloc_Expression *expression = (Checked_Alloc_Expression *)Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__ALLOC, sizeof(Checked_Alloc_Expression), location, type);
    expression->value_expression = value_expression;
    return expression;
}

Checked_Binary_Expression *Checked_Binary_Expression__create_kind(Checked_Expression_Kind kind, Source_Location location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression) {
    Checked_Binary_Expression *expression = (Checked_Binary_Expression *)Checked_Expression__create_kind(kind, sizeof(Checked_Binary_Expression), location, type);
    expression->left_expression = left_expression;
    expression->right_expression = right_expression;
    return expression;
}

Checked_Unary_Expression *Checked_Unary_Expression__create_kind(Checked_Expression_Kind kind, size_t kind_size, Source_Location location, Checked_Type *type, Checked_Expression *other_expression) {
    Checked_Unary_Expression *expression = (Checked_Unary_Expression *)Checked_Expression__create_kind(kind, kind_size, location, type);
    expression->other_expression = other_expression;
    return expression;
}

Checked_Add_Expression *Checked_Add_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression) {
    return (Checked_Add_Expression *)Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__ADD, location, type, left_expression, right_expression);
}

Checked_Address_Of_Expression *Checked_Address_Of_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *other_expression) {
    return (Checked_Address_Of_Expression *)Checked_Unary_Expression__create_kind(CHECKED_EXPRESSION_KIND__ADDRESS_OF, sizeof(Checked_Address_Of_Expression), location, type, other_expression);
}

Checked_Array_Access_Expression *Checked_Array_Access_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *array_expression, Checked_Expression *index_expression) {
    Checked_Array_Access_Expression *expression = (Checked_Array_Access_Expression *)Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__ARRAY_ACCESS, sizeof(Checked_Array_Access_Expression), location, type);
    expression->array_expression = array_expression;
    expression->index_expression = index_expression;
    return expression;
}

Checked_Bool_Expression *Checked_Bool_Expression__create(Source_Location location, Checked_Type *type, bool value) {
    Checked_Bool_Expression *expression = (Checked_Bool_Expression *)Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__BOOL, sizeof(Checked_Bool_Expression), location, type);
    expression->value = value;
    return expression;
}

Checked_Call_Argument *Checked_Call_Argument__create(Checked_Expression *expression) {
    Checked_Call_Argument *argument = (Checked_Call_Argument *)malloc(sizeof(Checked_Call_Argument));
    argument->expression = expression;
    argument->next_argument = NULL;
    return argument;
}

Checked_Call_Expression *Checked_Call_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *callee_expression, Checked_Call_Argument *first_argument) {
    Checked_Call_Expression *expression = (Checked_Call_Expression *)Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__CALL, sizeof(Checked_Call_Expression), location, type);
    expression->callee_expression = callee_expression;
    expression->first_argument = first_argument;
    return expression;
}

Checked_Cast_Expression *Checked_Cast_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *other_expression) {
    Checked_Cast_Expression *expression = (Checked_Cast_Expression *)Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__CAST, sizeof(Checked_Cast_Expression), location, type);
    expression->other_expression = other_expression;
    return expression;
}

Checked_Character_Expression *Checked_Character_Expression__create(Source_Location location, Checked_Type *type, char value) {
    Checked_Character_Expression *expression = (Checked_Character_Expression *)Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__CHARACTER, sizeof(Checked_Character_Expression), location, type);
    expression->value = value;
    return expression;
}

Checked_Dereference_Expression *Checked_Dereference_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *other_expression) {
    return (Checked_Dereference_Expression *)Checked_Unary_Expression__create_kind(CHECKED_EXPRESSION_KIND__DEREFERENCE, sizeof(Checked_Dereference_Expression), location, type, other_expression);
}

Checked_Divide_Expression *Checked_Divide_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression) {
    return (Checked_Divide_Expression *)Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__DIVIDE, location, type, left_expression, right_expression);
}

Checked_Equals_Expression *Checked_Equals_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression) {
    return (Checked_Equals_Expression *)Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__EQUALS, location, type, left_expression, right_expression);
}

Checked_Greater_Expression *Checked_Greater_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression) {
    return (Checked_Greater_Expression *)Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__GREATER, location, type, left_expression, right_expression);
}

Checked_Greater_Or_Equals_Expression *Checked_Greater_Or_Equals_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression) {
    return (Checked_Greater_Or_Equals_Expression *)Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__GREATER_OR_EQUALS, location, type, left_expression, right_expression);
}

Checked_Group_Expression *Checked_Group_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *other_expression) {
    Checked_Group_Expression *expression = (Checked_Group_Expression *)Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__GROUP, sizeof(Checked_Group_Expression), location, type);
    expression->other_expression = other_expression;
    return expression;
}

Checked_Integer_Expression *Checked_Integer_Expression__create(Source_Location location, Checked_Type *type, uint64_t value, int32_t base) {
    Checked_Integer_Expression *expression = (Checked_Integer_Expression *)Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__INTEGER, sizeof(Checked_Integer_Expression), location, type);
    expression->value = value;
    expression->base = base;
    return expression;
}

Checked_Is_Union_Variant_Expression *Checked_Is_Union_Variant_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *union_expression, Checked_Union_Variant *union_variant, bool is_not) {
    Checked_Is_Union_Variant_Expression *expression = (Checked_Is_Union_Variant_Expression *)Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__IS_UNION_VARIANT, sizeof(Checked_Is_Union_Variant_Expression), location, type);
    expression->union_expression = union_expression;
    expression->union_variant = union_variant;
    expression->is_not = is_not;
    return expression;
}

Checked_Less_Expression *Checked_Less_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression) {
    return (Checked_Less_Expression *)Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__LESS, location, type, left_expression, right_expression);
}

Checked_Less_Or_Equals_Expression *Checked_Less_Or_Equals_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression) {
    return (Checked_Less_Or_Equals_Expression *)Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__LESS_OR_EQUALS, location, type, left_expression, right_expression);
}

Checked_Logic_And_Expression *Checked_Logic_And_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression) {
    return (Checked_Logic_And_Expression *)Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__LOGIC_AND, location, type, left_expression, right_expression);
}

Checked_Logic_Or_Expression *Checked_Logic_Or_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression) {
    return (Checked_Logic_Or_Expression *)Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__LOGIC_OR, location, type, left_expression, right_expression);
}

Checked_Make_Struct_Argument *Checked_Make_Struct_Argument__create(Checked_Struct_Member *struct_member, Checked_Expression *expression) {
    Checked_Make_Struct_Argument *argument = (Checked_Make_Struct_Argument *)malloc(sizeof(Checked_Make_Struct_Argument));
    argument->struct_member = struct_member;
    argument->expression = expression;
    argument->next_argument = NULL;
    return argument;
}

Checked_Make_Struct_Expression *Checked_Make_Struct_Expression__create(Source_Location location, Checked_Type *type, Checked_Struct_Type *struct_type, Checked_Make_Struct_Argument *first_argument) {
    Checked_Make_Struct_Expression *expression = (Checked_Make_Struct_Expression *)Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__MAKE_STRUCT, sizeof(Checked_Make_Struct_Expression), location, type);
    expression->struct_type = struct_type;
    expression->first_argument = first_argument;
    return expression;
}

Checked_Member_Access_Expression *Checked_Member_Access_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *object_expression, Checked_Struct_Member *member) {
    Checked_Member_Access_Expression *expression = (Checked_Member_Access_Expression *)Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__MEMBER_ACCESS, sizeof(Checked_Member_Access_Expression), location, type);
    expression->object_expression = object_expression;
    expression->member = member;
    return expression;
}

Checked_Receiver_Method_Expression *Checked_Receiver_Method_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *receiver_expression, Checked_Expression *procedure_expression, Checked_Procedure_Type *procedure_type) {
    Checked_Receiver_Method_Expression *expression = (Checked_Receiver_Method_Expression *)Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__RECEIVER_METHOD, sizeof(Checked_Receiver_Method_Expression), location, type);
    expression->receiver_expression = receiver_expression;
    expression->procedure_expression = procedure_expression;
    expression->procedure_type = procedure_type;
    return expression;
}

Checked_Minus_Expression *Checked_Minus_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *other_expression) {
    return (Checked_Minus_Expression *)Checked_Unary_Expression__create_kind(CHECKED_EXPRESSION_KIND__MINUS, sizeof(Checked_Minus_Expression), location, type, other_expression);
}

Checked_Modulo_Expression *Checked_Modulo_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression) {
    return (Checked_Modulo_Expression *)Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__MODULO, location, type, left_expression, right_expression);
}

Checked_Multiply_Expression *Checked_Multiply_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression) {
    return (Checked_Multiply_Expression *)Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__MULTIPLY, location, type, left_expression, right_expression);
}

Checked_Not_Expression *Checked_Not_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *other_expression) {
    return (Checked_Not_Expression *)Checked_Unary_Expression__create_kind(CHECKED_EXPRESSION_KIND__NOT, sizeof(Checked_Not_Expression), location, type, other_expression);
}

Checked_Not_Equals_Expression *Checked_Not_Equals_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression) {
    return (Checked_Not_Equals_Expression *)Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__NOT_EQUALS, location, type, left_expression, right_expression);
}

Checked_Null_Expression *Checked_Null_Expression__create(Source_Location location, Checked_Type *type) {
    return (Checked_Null_Expression *)Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__NULL, sizeof(Checked_Null_Expression), location, type);
}

Checked_Sizeof_Expression *Checked_Sizeof_Expression__create(Source_Location location, Checked_Type *type, Checked_Type *sized_type) {
    Checked_Sizeof_Expression *expression = (Checked_Sizeof_Expression *)Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__SIZEOF, sizeof(Checked_Sizeof_Expression), location, type);
    expression->sized_type = sized_type;
    return expression;
}

Checked_String_Expression *Checked_String_Expression__create(Source_Location location, Checked_Type *type, String *value) {
    Checked_String_Expression *expression = (Checked_String_Expression *)Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__STRING, sizeof(Checked_String_Expression), location, type);
    expression->value = value;
    return expression;
}

Checked_String_Length_Expression *Checked_String_Length_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *string_expression) {
    Checked_String_Length_Expression *expression = (Checked_String_Length_Expression *)Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__STRING_LENGTH, sizeof(Checked_String_Length_Expression), location, type);
    expression->string_expression = string_expression;
    return expression;
}

Checked_Subtract_Expression *Checked_Subtract_Expression__create(Source_Location location, Checked_Type *type, Checked_Expression *left_expression, Checked_Expression *right_expression) {
    return (Checked_Subtract_Expression *)Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__SUBTRACT, location, type, left_expression, right_expression);
}

Checked_Symbol_Expression *Checked_Symbol_Expression__create(Source_Location location, Checked_Type *type, Checked_Symbol *symbol) {
    Checked_Symbol_Expression *expression = (Checked_Symbol_Expression *)Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__SYMBOL, sizeof(Checked_Symbol_Expression), location, type);
    expression->symbol = symbol;
    return expression;
}

Checked_Type_Expression *Checked_Type_Expression__create(Source_Location location, Checked_Type *type, Checked_Named_Type *named_type) {
    Checked_Type_Expression *expression = (Checked_Type_Expression *)Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__TYPE, sizeof(Checked_Type_Expression), location, type);
    expression->named_type = named_type;
    return expression;
}

Checked_Make_Union_Expression *Checked_Make_Union_Expression__create(Source_Location location, Checked_Type *type, Checked_Union_Type *union_type, Checked_Union_Variant *union_variant, Checked_Expression *expression) {
    Checked_Make_Union_Expression *union_expression = (Checked_Make_Union_Expression *)Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__MAKE_UNION, sizeof(Checked_Make_Union_Expression), location, type);
    union_expression->union_type = union_type;
    union_expression->union_variant = union_variant;
    union_expression->expression = expression;
    return union_expression;
}

Checked_Statement *Checked_Statement__create_kind(Checked_Statement_Kind kind, size_t kind_size, Source_Location location) {
    Checked_Statement *statement = (Checked_Statement *)malloc(kind_size);
    statement->kind = kind;
    statement->location = location;
    statement->next_statement = NULL;
    return statement;
}

Checked_Assignment_Statement *Checked_Assignment_Statement__create(Source_Location location, Checked_Expression *object_expression, Checked_Expression *value_expression) {
    Checked_Assignment_Statement *statement = (Checked_Assignment_Statement *)Checked_Statement__create_kind(CHECKED_STATEMENT_KIND__ASSIGNMENT, sizeof(Checked_Assignment_Statement), location);
    statement->object_expression = object_expression;
    statement->value_expression = value_expression;
    return statement;
}

Checked_Block_Statement *Checked_Block_Statement__create(Source_Location location, Checked_Statements *statements) {
    Checked_Block_Statement *statement = (Checked_Block_Statement *)Checked_Statement__create_kind(CHECKED_STATEMENT_KIND__BLOCK, sizeof(Checked_Block_Statement), location);
    statement->statements = statements;
    return statement;
}

Checked_Break_Statement *Checked_Break_Statement__create(Source_Location location) {
    return (Checked_Break_Statement *)Checked_Statement__create_kind(CHECKED_STATEMENT_KIND__BREAK, sizeof(Checked_Break_Statement), location);
}

Checked_Decomposed_Statement *Checked_Decomposed_Statement__create(Source_Location location, Checked_Statements *statements) {
    Checked_Decomposed_Statement *statement = (Checked_Decomposed_Statement *)Checked_Statement__create_kind(CHECKED_STATEMENT_KIND__DECOMPOSED, sizeof(Checked_Decomposed_Statement), location);
    statement->statements = statements;
    return statement;
}

Checked_Expression_Statement *Checked_Expression_Statement__create(Source_Location location, Checked_Expression *expression) {
    Checked_Expression_Statement *statement = (Checked_Expression_Statement *)Checked_Statement__create_kind(CHECKED_STATEMENT_KIND__EXPRESSION, sizeof(Checked_Expression_Statement), location);
    statement->expression = expression;
    return statement;
}

Checked_If_Statement *Checked_If_Statement__create(Source_Location location, Checked_Expression *condition_expression, Checked_Statement *true_statement, Checked_Statement *false_statement) {
    Checked_If_Statement *statement = (Checked_If_Statement *)Checked_Statement__create_kind(CHECKED_STATEMENT_KIND__IF, sizeof(Checked_If_Statement), location);
    statement->condition_expression = condition_expression;
    statement->true_statement = true_statement;
    statement->false_statement = false_statement;
    return statement;
}

Checked_Loop_Statement *Checked_Loop_Statement__create(Source_Location location, Checked_Statement *body_statement) {
    Checked_Loop_Statement *statement = (Checked_Loop_Statement *)Checked_Statement__create_kind(CHECKED_STATEMENT_KIND__LOOP, sizeof(Checked_Loop_Statement), location);
    statement->body_statement = body_statement;
    return statement;
}

Checked_Return_Statement *Checked_Return_Statement__create(Source_Location location, Checked_Expression *expression) {
    Checked_Return_Statement *statement = (Checked_Return_Statement *)Checked_Statement__create_kind(CHECKED_STATEMENT_KIND__RETURN, sizeof(Checked_Return_Statement), location);
    statement->expression = expression;
    return statement;
}

Checked_Union_If_Statement *Checked_Union_If_Statement__create(Source_Location location, Checked_Expression *union_expression, Checked_Union_Variant *union_variant, Checked_Statement *true_statement, Checked_Statement *false_statement) {
    Checked_Union_If_Statement *statement = (Checked_Union_If_Statement *)Checked_Statement__create_kind(CHECKED_STATEMENT_KIND__UNION_IF, sizeof(Checked_Union_If_Statement), location);
    statement->union_expression = union_expression;
    statement->union_variant = union_variant;
    statement->true_statement = true_statement;
    statement->false_statement = false_statement;
    return statement;
}

Checked_Switch_Else *Checked_Switch_Else__create(Source_Location location, Checked_Statement *statement) {
    Checked_Switch_Else *switch_else = (Checked_Switch_Else *)malloc(sizeof(Checked_Switch_Else));
    switch_else->location = location;
    switch_else->statement = statement;
    return switch_else;
}

Checked_Union_Switch_Case *Checked_Union_Switch_Case__create(Source_Location location, Checked_Union_Type *union_type, Checked_Union_Variant *union_variant, Checked_Statement *statement) {
    Checked_Union_Switch_Case *union_switch_case = (Checked_Union_Switch_Case *)malloc(sizeof(Checked_Union_Switch_Case));
    union_switch_case->location = location;
    union_switch_case->union_type = union_type;
    union_switch_case->union_variant = union_variant;
    union_switch_case->statement = statement;
    union_switch_case->next_union_switch_case = NULL;
    return union_switch_case;
}

Checked_Union_Switch_Statement *Checked_Union_Switch_Statement__create(Source_Location location, Checked_Expression *expression, Checked_Union_Switch_Case *first_union_switch_case, Checked_Switch_Else *switch_else) {
    Checked_Union_Switch_Statement *statement = (Checked_Union_Switch_Statement *)Checked_Statement__create_kind(CHECKED_STATEMENT_KIND__UNION_SWITCH, sizeof(Checked_Union_Switch_Statement), location);
    statement->expression = expression;
    statement->first_union_switch_case = first_union_switch_case;
    statement->switch_else = switch_else;
    return statement;
}

Checked_Variable_Statement *Checked_Variable_Statement__create(Source_Location location, Checked_Variable_Symbol *variable, bool is_external, Checked_Expression *expression) {
    Checked_Variable_Statement *statement = (Checked_Variable_Statement *)Checked_Statement__create_kind(CHECKED_STATEMENT_KIND__VARIABLE, sizeof(Checked_Variable_Statement), location);
    statement->variable = variable;
    statement->is_external = is_external;
    statement->expression = expression;
    variable->statement = statement;
    return statement;
}

Checked_While_Statement *Checked_While_Statement__create(Source_Location location, Checked_Expression *condition_expression, Checked_Statement *body_statement) {
    Checked_While_Statement *statement = (Checked_While_Statement *)Checked_Statement__create_kind(CHECKED_STATEMENT_KIND__WHILE, sizeof(Checked_While_Statement), location);
    statement->condition_expression = condition_expression;
    statement->body_statement = body_statement;
    return statement;
}

Checked_Statements *Checked_Statements__create() {
    Checked_Statements *statements = (Checked_Statements *)malloc(sizeof(Checked_Statements));
    statements->first_statement = NULL;
    statements->last_statement = NULL;
    return statements;
}

Checked_Statements *Checked_Statements__create_copy(Checked_Statements *other) {
    Checked_Statements *statements = (Checked_Statements *)malloc(sizeof(Checked_Statements));
    statements->first_statement = other->first_statement;
    statements->last_statement = other->last_statement;
    return statements;
}

void Checked_Statements__append(Checked_Statements *self, Checked_Statement *statement) {
    if (self->first_statement == NULL) {
        self->first_statement = statement;
    } else {
        self->last_statement->next_statement = statement;
    }
    self->last_statement = statement;
}
