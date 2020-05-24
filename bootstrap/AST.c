#include "AST.h"
#include "Logging.h"

char *type__get_kind_name(Type *self) {
    switch (self->kind) {
    case TYPE_ARRAY:
        return "ARRAY";
    case TYPE_FUNCTION:
        return "FUNCTION";
    case TYPE_POINTER:
        return "POINTER";
    case TYPE_SIMPLE:
        return "SIMPLE";
    case TYPE_TUPLE:
        return "TUPLE";
    default:
        PANIC(__FILE__, __LINE__, "Unsupported type kind: %d", self->kind);
    }
}

char *expression__get_kind_name(Expression *self) {
    switch (self->kind) {
    case EXPRESSION_ARRAY_ITEM:
        return "ARRAY_ITEM";
    case EXPRESSION_BINARY:
        return "BINARY";
    case EXPRESSION_CALL:
        return "CALL";
    case EXPRESSION_CAST:
        return "CAST";
    case EXPRESSION_LITERAL:
        return "LITERAL";
    case EXPRESSION_MEMBER:
        return "MEMBER";
    case EXPRESSION_SIZE_OF:
        return "SIZE_OF";
    case EXPRESSION_UNARY:
        return "UNARY";
    case EXPRESSION_VARIABLE:
        return "VARIABLE";
    default:
        PANIC(__FILE__, __LINE__, "Unsupported statement kind: %d", self->kind);
    }
}

char *statement__get_kind_name(Statement *self) {
    switch (self->kind) {
    case STATEMENT_ASSIGNMENT:
        return "ASSIGNMENT";
    case STATEMENT_BLOCK:
        return "BLOCK";
    case STATEMENT_BREAK:
        return "BREAK";
    case STATEMENT_EXPRESSION:
        return "EXPRESSION";
    case STATEMENT_FUNCTION:
        return "FUNCTION";
    case STATEMENT_IF:
        return "IF";
    case STATEMENT_LOOP:
        return "LOOP";
    case STATEMENT_RETURN:
        return "RETURN";
    case STATEMENT_SKIP:
        return "SKIP";
    case STATEMENT_STRUCT:
        return "STRUCT";
    case STATEMENT_VARIABLE:
        return "VARIABLE";
    default:
        PANIC(__FILE__, __LINE__, "Unsupported statement kind: %d", self->kind);
    }
}
