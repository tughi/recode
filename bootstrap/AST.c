#include "AST.h"
#include "Logging.h"

static Type *type__create(int kind, Source_Location *location) {
    Type *self = malloc(sizeof(Type));
    self->kind = kind;
    self->location = location;
    return self;
}

Type *type__create_array(Source_Location *location, Type *item_type) {
    Type *self = type__create(TYPE__ARRAY, location);
    self->array_data.item_type = item_type;
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

char *type__get_kind_name(Type *self) {
    switch (self->kind) {
    case TYPE__ARRAY:
        return "ARRAY";
    case TYPE__FUNCTION:
        return "FUNCTION";
    case TYPE__POINTER:
        return "POINTER";
    case TYPE__NAMED:
        return "NAMED";
    default:
        PANIC(__FILE__, __LINE__, "Unsupported type kind: %d", self->kind);
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
    case EXPRESSION__SIZE_OF:
        return "SIZE_OF";
    case EXPRESSION__UNARY:
        return "UNARY";
    case EXPRESSION__VARIABLE:
        return "VARIABLE";
    default:
        PANIC(__FILE__, __LINE__, "Unsupported statement kind: %d", self->kind);
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

typedef struct Named_Types_Item {
    String *name;
    Type *type;
} Named_Types_Item;

static Named_Types_Item *named_types__create_item(String *name, Type *type) {
    Named_Types_Item *self = malloc(sizeof(Named_Types_Item));
    self->name = name;
    self->type = type;
    return self;
}

Named_Types *named_types__create() {
    static Source_Location unkown_location;
    Named_Types *self = list__create();
    list__append(self, named_types__create_item(string__create("Int"), type__create(TYPE__INTEGER, &unkown_location)));
    list__append(self, named_types__create_item(string__create("Boolean"), type__create(TYPE__BOOLEAN, &unkown_location)));
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
        Named_Types_Item *named_type = list_iterator__next(&iterator);
        if (string__equals(named_type->name, name->data)) {
            return named_type->type;
        }
    }
    return NULL;
}

Compilation_Unit *compilation_unit__create(Named_Types *named_types, Statement_List *statements) {
    Compilation_Unit *self = malloc(sizeof(Compilation_Unit));
    self->named_types = named_types;
    self->statements = statements;
    return self;
}