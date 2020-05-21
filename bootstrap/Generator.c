#include "Generator.h"

#include "Logging.h"
#include "Parser.h"

#include <stdlib.h>

typedef struct Value_Holder {
    enum {
        VALUE_HOLDER_INTEGER
    } kind;

    String *repr;
} Value_Holder;

static Value_Holder *value_holder__create(String *repr) {
    Value_Holder *self = malloc(sizeof(Value_Holder));
    self->repr = repr;
    return self;
}

typedef struct Label {
} Label;

typedef struct Loop {
    Label *loop_end;
    int has_break;
    struct Loop *parent;
} Loop;

typedef struct Counter {
    int count;
} Counter;

typedef struct Context {
    struct Context *global_context;
    struct Context *parent_context;
    FILE *file;
    List *types;
    List *locals;
    List *allocas;
    List *constants;
    Loop *loop;
    Counter *temp_variables;
} Context;

#define emitf(line, ...) fprintf(context->file, line "\n", __VA_ARGS__)
#define emits(line) fprintf(context->file, line "\n")

static Counter *counter__create() {
    Counter *self = malloc(sizeof(Counter));
    self->count = 0;
    return self;
}

static Context *context__create(FILE *file) {
    Context *self = malloc(sizeof(Context));
    self->global_context = self;
    self->parent_context = NULL;
    self->file = file;
    self->types = list__create();
    self->locals = list__create();
    self->allocas = list__create();
    self->constants = list__create();
    self->loop = NULL;
    self->temp_variables = counter__create();
    return self;
}

static Type *compute_expression_type(Context *context, Expression *expression) {
    switch (expression->kind) {
    default:
        PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Unsupported expression kind: %d", expression->location.line, expression->location.column, expression->kind);
    }
}

static Value_Holder *emit_load_literal(Context *context, Token *token) {
    switch (token->kind) {
    case TOKEN_INTEGER: {
        String *repr = string__create("$");
        string__append_int(repr, token->integer.value);
        return value_holder__create(repr);
    }
    default:
        PANIC(__FILE__, __LINE__, "Unsupported token kind: %s", token__get_kind_name(token));
    }
}

static Value_Holder *emit_expression(Context *context, Expression *expression) {
    switch (expression->kind) {
    case EXPRESSION_LITERAL: {
        return emit_load_literal(context, expression->literal_expression_data.value);
    }
    default:
        PANIC(__FILE__, __LINE__, "Unsupported expression kind: %s", expression__get_kind_name(expression));
    }
}

static void emit_statement(Context *context, Statement *statement) {
    switch (statement->kind) {
    case STATEMENT_FUNCTION: {
        String *function_name = statement->function_statement_data.name->literal_expression_data.value->lexeme;
        emitf("  .globl %s", function_name->data);
        emitf("  .type %s, @function", function_name->data);
        emitf("%s:", function_name->data);
        emits("  pushq %%rbp");
        emits("  movq %%rsp, %%rbp");

        for (List_Iterator iterator = list__create_iterator(statement->function_statement_data.statements); list_iterator__has_next(&iterator);) {
            Statement *body_statement = list_iterator__next(&iterator);
            emit_statement(context, body_statement);
        }

        return;
    }
    case STATEMENT_RETURN: {
        if (statement->return_statement_data.expression != NULL) {
            Value_Holder *result = emit_expression(context, statement->return_statement_data.expression);
            emitf("  movq %s, %%rax", result->repr->data);
            emits("  movq %%rbp, %%rsp");
            emits("  popq %%rbp");
            emits("  ret");
        } else {

        }
        return;
    }
    default:
        PANIC(__FILE__, __LINE__, "Unsupported statement kind: %s", statement__get_kind_name(statement));
    }
}

void generate(List *statements) {
    FILE *file = fopen("build/code.s", "w");

    Context *context = context__create(file);

    emits("  .text");

    for (List_Iterator iterator = list__create_iterator(statements); list_iterator__has_next(&iterator);) {
        Statement *statement = list_iterator__next(&iterator);
        emit_statement(context, statement);
        emits("");
    }

    for (List_Iterator iterator = list__create_iterator(context->constants); list_iterator__has_next(&iterator);) {
        String *constant = list_iterator__next(&iterator);
        emitf("%s", constant->data);
    }

    fclose(context->file);
}
