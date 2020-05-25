#include "AST.h"
#include "Logging.h"

char *composite_type__get_kind_name(Composite_Type *self) {
    switch (self->kind) {
    case COMPOSITE_TYPE__ARRAY:
        return "ARRAY";
    case COMPOSITE_TYPE__FUNCTION:
        return "FUNCTION";
    case COMPOSITE_TYPE__POINTER:
        return "POINTER";
    case COMPOSITE_TYPE__NAMED:
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

Named_Type *named_type__create(int kind, String *name, Source_Location *location) {
    Named_Type *self = malloc(sizeof(Named_Type));
    self->kind = kind;
    self->name = name;
    self->location = location;
    return self;
}

char *named_type__get_kind_name(Named_Type *self) {
    switch (self->kind) {
    default:
        PANIC(__FILE__, __LINE__, "Unsupported type kind: %d", self->kind);
    }
}

Named_Type *named_type_list__find(Named_Type_List *self, String *name) {
    for (List_Iterator iterator = list__create_iterator(self); list_iterator__has_next(&iterator);) {
        Named_Type *type = list_iterator__next(&iterator);
        if (string__equals(type->name, name->data)) {
            return type;
        }
    }
    return NULL;
}

void named_type_list__add(Named_Type_List *self, Named_Type *new_type) {
    Named_Type *old_type = named_type_list__find(self, new_type->name);
    if (old_type != NULL) {
        PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Another \"%s\" type declared already here: (%04d:%04d)", new_type->location->line, new_type->location->column, new_type->name->data, old_type->location->line, old_type->location->column);
    }
    list__append(self, new_type);
}

Compilation_Unit *compilation_unit__create(Named_Type_List *named_types, Statement_List *statements) {
    Compilation_Unit *self = malloc(sizeof(Compilation_Unit));
    self->named_types = named_types;
    self->statements = statements;
    return self;
}
