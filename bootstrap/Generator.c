#include "Generator.h"

#include "Logging.h"
#include "Parser.h"
#include "Symbol_Table.h"

#include <stdlib.h>

#define Value_Holder String

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

static Counter *counter__create() {
    Counter *self = malloc(sizeof(Counter));
    self->count = 0;
    return self;
}

#define REGISTERS_COUNT 4

typedef struct Registers {
    int used[REGISTERS_COUNT];
    Value_Holder *names[REGISTERS_COUNT];
} Registers;

static Registers *registers__create() {
    Registers *self = malloc(sizeof(Registers));
    for (int i = 0; i < REGISTERS_COUNT; i++) {
        self->names[i] = string__create("%r");
        string__append_int(self->names[i], 8 + i);
        self->used[i] = 0;
    }
    return self;
}

static Value_Holder *registers__acquire(Registers *self) {
    for (int i = 0; i < REGISTERS_COUNT; i++) {
        if (self->used[i] == 0) {
            self->used[i] = 1;
            return self->names[i];
        }
    }
    PANIC(__FILE__, __LINE__, "All registers are used already%c", 0);
}

static void registers__release(Registers *self, Value_Holder *name) {
    for (int i = 0; i < REGISTERS_COUNT; i++) {
        if (self->names[i] == name) {
            if (self->used[i] != 1) {
                PANIC(__FILE__, __LINE__, "Trying to release an unused register: %s", name->data);
            }
            self->used[i] = 0;
            return;
        }
    }
    PANIC(__FILE__, __LINE__, "Trying to release an invalid register: %s", name->data);
}

typedef struct Context {
    struct Context *global_context;
    struct Context *parent_context;
    FILE *file;
    Registers *registers;
    Symbol_Table *symbols;
} Context;

#define emitf(line, ...) fprintf(context->file, line "\n", __VA_ARGS__)
#define emits(line) fprintf(context->file, line "\n")

static Context *context__create(FILE *file) {
    Context *self = malloc(sizeof(Context));
    self->global_context = self;
    self->parent_context = NULL;
    self->file = file;
    self->registers = registers__create();
    self->symbols = symbol_table__create();
    return self;
}

static Value_Holder *context__acquire_register(Context *self) {
    return registers__acquire(self->registers);
}

static void context__release_register(Context *self, Value_Holder *value_holder) {
    registers__release(self->registers, value_holder);
}

static Symbol_Table_Item *context__find_symbol(Context *self, String *name) {
    return symbol_table__find_item(self->symbols, name);
}

static Symbol_Table_Item *context__create_symbol(Context *self, String *name) {
    if (context__find_symbol(self, name)) {
        PANIC(__FILE__, __LINE__, "Trying to create a symbol that already exists: %s", name->data);
    }
    return symbol_table__find_item(self->symbols, name);
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
        Value_Holder *value_holder = context__acquire_register(context);
        emitf("  movq $%d, %s", token->integer.value, value_holder->data);
        return value_holder;
    }
    default:
        PANIC(__FILE__, __LINE__, "Unsupported token kind: %s", token__get_kind_name(token));
    }
}

static Value_Holder *emit_expression(Context *context, Expression *expression) {
    switch (expression->kind) {
    case EXPRESSION_BINARY: {
        Value_Holder *left_value_holder = emit_expression(context, expression->binary_data.left_expression);
        if (string__equals(expression->binary_data.operator_token->lexeme, "+")) {
            Value_Holder *right_value_holder = emit_expression(context, expression->binary_data.right_expression);
            emitf("  addq %s, %s", left_value_holder->data, right_value_holder->data);
            context__release_register(context, left_value_holder);
            return right_value_holder;
        } else if (string__equals(expression->binary_data.operator_token->lexeme, "-")) {
            Value_Holder *right_value_holder = emit_expression(context, expression->binary_data.right_expression);
            emitf("  subq %s, %s", right_value_holder->data, left_value_holder->data);
            context__release_register(context, right_value_holder);
            return left_value_holder;
        } else if (string__equals(expression->binary_data.operator_token->lexeme, "*")) {
            Value_Holder *right_value_holder = emit_expression(context, expression->binary_data.right_expression);
            emitf("  imulq %s, %s", left_value_holder->data, right_value_holder->data);
            context__release_register(context, left_value_holder);
            return right_value_holder;
        } else if (string__equals(expression->binary_data.operator_token->lexeme, "/")) {            
            Value_Holder *right_value_holder = emit_expression(context, expression->binary_data.right_expression);
            emitf("  movq %s, %%rax", left_value_holder->data);
            emits("  cqto");
            emitf("  idivq %s", right_value_holder->data);
            emitf("  movq %%rax, %s", left_value_holder->data);
            context__release_register(context, right_value_holder);
            return left_value_holder;
        } else if (string__equals(expression->binary_data.operator_token->lexeme, "//")) {            
            Value_Holder *right_value_holder = emit_expression(context, expression->binary_data.right_expression);
            emitf("  movq %s, %%rax", left_value_holder->data);
            emits("  cqto");
            emitf("  idivq %s", right_value_holder->data);
            emitf("  movq %%rdx, %s", left_value_holder->data);
            context__release_register(context, right_value_holder);
            return left_value_holder;
        } else {
            PANIC(__FILE__, __LINE__, "Unsupported binary expression operator: %s", expression->binary_data.operator_token->lexeme->data);
        }
    }
    case EXPRESSION_LITERAL: {
        return emit_load_literal(context, expression->literal_data.value);
    }
    default:
        PANIC(__FILE__, __LINE__, "Unsupported expression kind: %s", expression__get_kind_name(expression));
    }
}

static void emit_statement(Context *context, Statement *statement) {
    switch (statement->kind) {
    case STATEMENT_FUNCTION: {
        String *function_name = statement->function_data.name->lexeme;
        emitf("  .globl %s", function_name->data);
        emitf("  .type %s, @function", function_name->data);
        emitf("%s:", function_name->data);
        emits("  pushq %%rbp");
        emits("  movq %%rsp, %%rbp");

        for (List_Iterator iterator = list__create_iterator(statement->function_data.statements); list_iterator__has_next(&iterator);) {
            Statement *body_statement = list_iterator__next(&iterator);
            emit_statement(context, body_statement);
        }

        return;
    }
    case STATEMENT_RETURN: {
        if (statement->return_data.expression != NULL) {
            Value_Holder *value_holder = emit_expression(context, statement->return_data.expression);
            emitf("  movq %s, %%rax", value_holder->data);
            emits("  movq %%rbp, %%rsp");
            emits("  popq %%rbp");
            emits("  ret");
            context__release_register(context, value_holder);
        } else {

        }
        return;
    }
    case STATEMENT_VARIABLE: {
        String *variable_name = statement->variable_data.name->lexeme;

    }
    default:
        PANIC(__FILE__, __LINE__, "Unsupported statement kind: %s", statement__get_kind_name(statement));
    }
}

void generate(List *statements) {
    FILE *file = fopen("build/code.s", "w");

    Context *context = context__create(file);

    emits("  .text");
    emits(".LC0:");
    emits("  .string \"%%d\\n\"");
    emits("printint:");
    emits("  pushq %%rbp");
    emits("  movq %%rsp, %%rbp");
    emits("  subq $16, %%rsp");
    emits("  movl %%edi, -4(%%rbp)");
    emits("  movl -4(%%rbp), %%eax");
    emits("  movl %%eax, %%esi");
    emits("  leaq .LC0(%%rip), %%rdi");
    emits("  movl $0, %%eax");
    emits("  call printf@PLT");
    emits("  nop");
    emits("  leave");
    emits("  ret");
    emits("");

    for (List_Iterator iterator = list__create_iterator(statements); list_iterator__has_next(&iterator);) {
        Statement *statement = list_iterator__next(&iterator);
        emit_statement(context, statement);
        emits("");
    }

    fclose(context->file);
}
