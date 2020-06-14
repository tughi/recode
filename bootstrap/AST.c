#include "AST.h"
#include "Logging.h"

static Type *type__create(int kind, Source_Location *location) {
    Type *self = malloc(sizeof(Type));
    self->kind = kind;
    self->location = location;
    return self;
}

Type *type__create_array(Source_Location *location, Type *item_type, int size) {
    Type *self = type__create(TYPE__ARRAY, location);
    self->array_data.item_type = item_type;
    self->array_data.size = size;
    return self;
}

Type *type__create_function(Source_Location *location, Type *return_type, List *parameters) {
    Type *self = type__create(TYPE__FUNCTION, location);
    self->function_data.parameters = parameters;
    self->function_data.return_type = return_type;
    return self;
}

Type *type__create_named(Source_Location *location, Token *name) {
    Type *self = type__create(TYPE__NAMED, location);
    self->named_data.name = name;
    return self;
}

Type *type__create_pointer(Source_Location *location, Type *type) {
    Type *self = type__create(TYPE__POINTER, location);
    self->pointer_data.type = type;
    return self;
}

Type *type__create_struct(Source_Location *location, Statement *statement) {
    Type *self = type__create(TYPE__STRUCT, location);
    self->struct_data.statement = statement;
    return self;
}

void type__convert(Type *self, Type *other) {
    self->kind = other->kind;
    switch (other->kind) {
    case TYPE__BOOLEAN:
    case TYPE__INT:
    case TYPE__INT8:
    case TYPE__INT16:
    case TYPE__INT32:
    case TYPE__INT64:
    case TYPE__NOTHING:
        self->name = other->name;
        break;
    case TYPE__STRUCT:
        self->location = other->location;
        self->name = other->name;
        self->struct_data.statement = other->struct_data.statement;
        break;
    default:
        PANIC(__FILE__, __LINE__, "Unsupported type kind: %s", type__get_kind_name(other));
    }
}

char *type__get_kind_name(Type *self) {
    switch (self->kind) {
    case TYPE__ARRAY:
        return "ARRAY";
    case TYPE__BOOLEAN:
        return "BOOLEAN";
    case TYPE__FUNCTION:
        return "FUNCTION";
    case TYPE__INT:
        return "INT";
    case TYPE__INT8:
        return "INT8";
    case TYPE__INT16:
        return "INT16";
    case TYPE__INT32:
        return "INT32";
    case TYPE__INT64:
        return "INT64";
    case TYPE__POINTER:
        return "POINTER";
    case TYPE__NAMED:
        return "NAMED";
    case TYPE__NOTHING:
        return "NOTHING";
    case TYPE__STRUCT:
        return "STRUCT";
    default:
        PANIC(__FILE__, __LINE__, "Unsupported type kind: %d", self->kind);
    }
}

int type__equals(Type *self, Type *other) {
    switch (self->kind) {
    case TYPE__BOOLEAN:
    case TYPE__INT:
    case TYPE__INT8:
    case TYPE__INT16:
    case TYPE__INT32:
    case TYPE__INT64:
    case TYPE__NOTHING:
        return other->kind == self->kind;
    case TYPE__NAMED:
        return other->kind == TYPE__NAMED && string__equals(self->named_data.name->lexeme, other->named_data.name->lexeme->data);
    case TYPE__POINTER:
        return other->kind == TYPE__POINTER && type__equals(self->pointer_data.type, other->pointer_data.type);
    case TYPE__STRUCT:
        return other->kind == TYPE__STRUCT && self->struct_data.statement == other->struct_data.statement;
    default:
        PANIC(__FILE__, __LINE__, "Unsupported type kind: %s", type__get_kind_name(self));
    }
}

char *expression__get_kind_name(Expression *self) {
    switch (self->kind) {
    case EXPRESSION__ARRAY_ITEM:
        return "ARRAY_ITEM";
    case EXPRESSION__BINARY:
        return "BINARY";
    case EXPRESSION__CALL:
        return "CALL";
    case EXPRESSION__CAST:
        return "CAST";
    case EXPRESSION__LITERAL:
        return "LITERAL";
    case EXPRESSION__MEMBER:
        return "MEMBER";
    case EXPRESSION__NEW:
        return "NEW";
    case EXPRESSION__POINTED_VALUE:
        return "POINTED_VALUE";
    case EXPRESSION__POINTER_TO:
        return "POINTER_TO";
    case EXPRESSION__SIZE_OF:
        return "SIZE_OF";
    case EXPRESSION__UNARY:
        return "UNARY";
    case EXPRESSION__VARIABLE:
        return "VARIABLE";
    default:
        PANIC(__FILE__, __LINE__, "Unsupported expression kind: %d", self->kind);
    }
}

char *statement__get_kind_name(Statement *self) {
    switch (self->kind) {
    case STATEMENT__ASSIGNMENT:
        return "ASSIGNMENT";
    case STATEMENT__BLOCK:
        return "BLOCK";
    case STATEMENT__BREAK:
        return "BREAK";
    case STATEMENT__EXPRESSION:
        return "EXPRESSION";
    case STATEMENT__FUNCTION:
        return "FUNCTION";
    case STATEMENT__IF:
        return "IF";
    case STATEMENT__LOOP:
        return "LOOP";
    case STATEMENT__RETURN:
        return "RETURN";
    case STATEMENT__SKIP:
        return "SKIP";
    case STATEMENT__STRUCT:
        return "STRUCT";
    case STATEMENT__VARIABLE:
        return "VARIABLE";
    default:
        PANIC(__FILE__, __LINE__, "Unsupported statement kind: %d", self->kind);
    }
}

Named_Functions *named_functions__create() {
    return list__create();
}

void named_functions__add(Named_Functions *self, Statement *statement) {
    for (List_Iterator iterator = list__create_iterator(self); list_iterator__has_next(&iterator);) {
        Statement *item = list_iterator__next(&iterator);
        if (string__equals(item->function_data.unique_name, statement->function_data.unique_name->data)) {
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Function with the same signature was declared already here: (%04d:%04d)", statement->location->line, statement->location->column, item->location->line, item->location->column);
        }
    }

    list__append(self, statement);
}

Statement *named_functions__get(Named_Functions *self, String *name, Argument *first_argument, Argument_List *arguments) {
    for (List_Iterator iterator = list__create_iterator(self); list_iterator__has_next(&iterator);) {
        Statement *item = list_iterator__next(&iterator);
        if (string__equals(item->function_data.name->lexeme, name->data)) {
            int signature_matches = 0;
            Parameter_List *function_parameters = item->function_data.parameters;
            int function_parameters_size = list__size(function_parameters);
            if (list__size(arguments) + (first_argument ? 1 : 0) == function_parameters_size) {
                signature_matches = 1;
                if (first_argument) {
                    Parameter *first_parameter = list__get(function_parameters, 0);
                    if (!type__equals(first_argument->inferred_type, first_parameter->type)) {
                        signature_matches = 0;
                    }
                }
                for (int index = first_argument ? 1 : 0; index < function_parameters_size; index++) {
                    Argument *argument = list__get(arguments, index - (first_argument ? 1 : 0));
                    Parameter *parameter = list__get(function_parameters, index);
                    if (!type__equals(argument->inferred_type, parameter->type)) {
                        signature_matches = 0;
                        break;
                    }
                }
            }
            if (signature_matches == 1) {
                return item;
            } 
        }
    }
    return NULL;
}

typedef struct Named_Types_Item {
    String *name;
    Type *type;
} Named_Types_Item;

static Named_Types_Item *named_types__create_item(String *name, Type *type) {
    Named_Types_Item *self = malloc(sizeof(Named_Types_Item));
    self->name = name;
    self->type = type;
    type->name = name;
    return self;
}

Named_Types *named_types__create() {
    static Source_Location unkown_location;
    Named_Types *self = list__create();
    list__append(self, named_types__create_item(string__create("Boolean"), type__create(TYPE__BOOLEAN, &unkown_location)));
    list__append(self, named_types__create_item(string__create("Int"), type__create(TYPE__INT, &unkown_location)));
    list__append(self, named_types__create_item(string__create("Int8"), type__create(TYPE__INT8, &unkown_location)));
    list__append(self, named_types__create_item(string__create("Int16"), type__create(TYPE__INT16, &unkown_location)));
    list__append(self, named_types__create_item(string__create("Int32"), type__create(TYPE__INT32, &unkown_location)));
    list__append(self, named_types__create_item(string__create("Int64"), type__create(TYPE__INT64, &unkown_location)));
    list__append(self, named_types__create_item(string__create("Nothing"), type__create(TYPE__NOTHING, &unkown_location)));
    return self;
}

void named_types__add(Named_Types *self, String *name, Type *type) {
    Type *other_type = named_types__get(self, name);
    if (other_type != NULL) {
        PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Another \"%s\" type is declared already here: (%04d:%04d)", type->location->line, type->location->column, name->data, other_type->location->line, other_type->location->column);
    }

    list__append(self, named_types__create_item(name, type));
}

Type *named_types__get(Named_Types *self, String *name) {
    for (List_Iterator iterator = list__create_iterator(self); list_iterator__has_next(&iterator);) {
        Named_Types_Item *item = list_iterator__next(&iterator);
        if (string__equals(item->name, name->data)) {
            return item->type;
        }
    }
    return NULL;
}

Compilation_Unit *compilation_unit__create(Named_Functions *named_functions, Named_Types *named_types, Statement_List *statements) {
    Compilation_Unit *self = malloc(sizeof(Compilation_Unit));
    self->named_functions = named_functions;
    self->named_types = named_types;
    self->statements = statements;
    return self;
}
