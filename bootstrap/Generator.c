#include "Generator.h"

#include "Logging.h"
#include "Parser.h"

#include <stdlib.h>

typedef struct Storage {
} Storage;

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

#define emit_line(line) fprintf(context->file, line "\n")
#define emit(format, ...) fprintf(context->file, format "\n", __VA_ARGS__)

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

static Storage *emit_expression(Context *context, Expression *expression) {
    switch (expression->kind) {
    default:
        PANIC(__FILE__, __LINE__, "Unsupported expression type: %d", expression->kind);
    }
}

static void emit_statement(Context *context, Statement *statement) {
    switch (statement->kind) {
    case STATEMENT_FUNCTION: {
        String *function_name = statement->function_statement_data.name->literal_expression_data.value->lexeme;
        emit("  .globl %s", function_name->data);
        emit("  .type %s, @function", function_name->data);
        emit("%s:", function_name->data);
        emit_line("  pushq %%rbp");
        emit_line("  movq %%rsp, %%rbp");

        for (List_Iterator iterator = list__create_iterator(statement->function_statement_data.statements); list_iterator__has_next(&iterator);) {
            Statement *body_statement = list_iterator__next(&iterator);
            emit_statement(context, body_statement);
        }

        return;
    }
    case STATEMENT_RETURN: {
        if (statement->return_statement_data.expression != NULL) {
            // Storage *result = emit_expression(context, statement->return_statement_data.expression);
            emit_line("  movq %%rbp, %%rsp");
            emit_line("  popq %%rbp");
            emit_line("  ret");
        } else {

        }
        return;
    }
    default:
        PANIC(__FILE__, __LINE__, "Unsupported statement type: %s", get_statement_kind_name(statement->kind));
    }
}

void generate(List *statements) {
    FILE *file = fopen("build/code.s", "w");

    Context *context = context__create(file);

    emit_line("  .text");

    for (List_Iterator iterator = list__create_iterator(statements); list_iterator__has_next(&iterator);) {
        Statement *statement = list_iterator__next(&iterator);
        emit_statement(context, statement);
        emit_line("");
    }

    for (List_Iterator iterator = list__create_iterator(context->constants); list_iterator__has_next(&iterator);) {
        String *constant = list_iterator__next(&iterator);
        emit("%s", constant->data);
    }

    fclose(context->file);
}
