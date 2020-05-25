#include "Generator.h"
#include "Logging.h"
#include "Symbol_Table.h"

#define Value_Holder String

typedef struct Loop {
    int id;
    int has_exit;
    struct Loop *parent;
} Loop;

static Loop *loop__create(int id, Loop *parent) {
    Loop *self = malloc(sizeof(Loop));
    self->id = id;
    self->has_exit = 0;
    self->parent = parent;
    return self;
}

typedef struct Counter {
    int count;
} Counter;

static Counter *counter__create() {
    Counter *self = malloc(sizeof(Counter));
    self->count = 0;
    return self;
}

static int counter__inc(Counter *self) {
    self->count += 1;
    return self->count;
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
    Named_Type_List *named_types;
    Symbol_Table *symbols;
    Counter *counter;
    Loop *loop;
} Context;

#define emitf(line, ...) fprintf(context->file, line "\n", __VA_ARGS__)
#define emits(line) fprintf(context->file, line "\n")

static Context *context__create(FILE *file, Named_Type_List *named_types) {
    Context *self = malloc(sizeof(Context));
    self->global_context = self;
    self->parent_context = NULL;
    self->file = file;
    self->registers = registers__create();
    self->named_types = named_types;
    self->symbols = symbol_table__create();
    self->counter = counter__create();
    self->loop = NULL;
    return self;
}

static Value_Holder *context__acquire_register(Context *self) {
    return registers__acquire(self->registers);
}

static void context__release_register(Context *self, Value_Holder *value_holder) {
    registers__release(self->registers, value_holder);
}

Symbol_Table_Item *context__find_symbol(Context *self, String *name) {
    return symbol_table__find_item(self->symbols, name);
}

void context__create_variable(Context *self, String *name, Composite_Type *type) {
    if (context__find_symbol(self, name)) {
        PANIC(__FILE__, __LINE__, "Trying to create a variable that already exists in the same context: %s", name->data);
    }
    symbol_table__add_item(self->symbols, name, type);
}

static Composite_Type *compute_expression_type(Context *context, Expression *expression) {
    switch (expression->kind) {
    default:
        PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Unsupported expression kind: %s", expression->location->line, expression->location->column, expression__get_kind_name(expression));
    }
}

static int compute_named_type_size(Context *context, Named_Type *type) {
    switch (type->kind) {
    case NAMED_TYPE__BOOLEAN:
        return 1;
    case NAMED_TYPE__INTEGER:
        return 8;
    default:
        PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Unsupported type kind: %s", type->location->line, type->location->column, named_type__get_kind_name(type));
    }
}

static int compute_composite_type_size(Context *context, Composite_Type *type) {
    switch (type->kind) {
    case COMPOSITE_TYPE__NAMED: {
        Named_Type *named_type = named_type_list__find(context->named_types, type->named_data.name->lexeme);
        return compute_named_type_size(context, named_type);
    }
    default:
        PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Unsupported type kind: %s", type->location->line, type->location->column, composite_type__get_kind_name(type));
    }
}

static Value_Holder *emit_load_literal(Context *context, Token *token) {
    switch (token->kind) {
    case TOKEN__INTEGER: {
        Value_Holder *value_holder = context__acquire_register(context);
        emitf("  movq $%d, %s", token->integer_data.value, value_holder->data);
        return value_holder;
    }
    default:
        PANIC(__FILE__, __LINE__, "Unsupported token kind: %s", token__get_kind_name(token));
    }
}

static Value_Holder *emit_load_variable(Context *context, Token *variable_name) {
    Symbol_Table_Item *symbol = context__find_symbol(context, variable_name->lexeme);
    if (symbol == NULL) {
        PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Undeclared variable: %s", variable_name->location->line, variable_name->location->line, variable_name->lexeme->data);
    }

    Composite_Type *variable_type = symbol->type;

    if (variable_type->kind != COMPOSITE_TYPE__NAMED) {
        PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Unsupported variable type: %s", variable_name->location->line, variable_name->location->line, composite_type__get_kind_name(variable_type));
    }
    Named_Type *named_type = named_type_list__find(context->named_types, variable_type->named_data.name->lexeme);
    if (named_type == NULL) {
        PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Unknown type: %s", variable_name->location->line, variable_name->location->line, variable_type->named_data.name->lexeme->data);
    }

    // TODO: check if variable is local or global, and load it respectively

    Value_Holder *value_holder = context__acquire_register(context);
    switch (named_type->kind) {
    case NAMED_TYPE__BOOLEAN: {
        emitf("  movzbq %s(%%rip), %s", variable_name->lexeme->data, value_holder->data);
        return value_holder;
    }
    case NAMED_TYPE__INTEGER: {
        emitf("  movq %s(%%rip), %s", variable_name->lexeme->data, value_holder->data);
        return value_holder;
    }
    default:
        PANIC(__FILE__, __LINE__, "Unsupported named type: %s", named_type->name->data);
    }
}

Value_Holder *emit_expression(Context *context, Expression *expression);

Value_Holder *emit_comparison_expression(Context *context, Expression *expression, Value_Holder *left_value_holder, const char *flag_instruction) {
    Value_Holder *right_value_holder = emit_expression(context, expression->binary_data.right_expression);
    emitf("  cmpq %s, %s", right_value_holder->data, left_value_holder->data);
    emitf("  %s %sb", flag_instruction, right_value_holder->data);
    emitf("  movzbq %sb, %s", right_value_holder->data, right_value_holder->data);
    context__release_register(context, left_value_holder);
    return right_value_holder;
}

Value_Holder *emit_expression(Context *context, Expression *expression) {
    switch (expression->kind) {
    case EXPRESSION__BINARY: {
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
        } else if (string__equals(expression->binary_data.operator_token->lexeme, "<")) {
            return emit_comparison_expression(context, expression, left_value_holder, "setl");
        } else if (string__equals(expression->binary_data.operator_token->lexeme, "<=")) {
            return emit_comparison_expression(context, expression, left_value_holder, "setle");
        } else if (string__equals(expression->binary_data.operator_token->lexeme, ">")) {
            return emit_comparison_expression(context, expression, left_value_holder, "setg");
        } else if (string__equals(expression->binary_data.operator_token->lexeme, ">=")) {
            return emit_comparison_expression(context, expression, left_value_holder, "setge");
        } else if (string__equals(expression->binary_data.operator_token->lexeme, "==")) {
            return emit_comparison_expression(context, expression, left_value_holder, "sete");
        } else if (string__equals(expression->binary_data.operator_token->lexeme, "!=")) {
            return emit_comparison_expression(context, expression, left_value_holder, "setne");
        } else {
            PANIC(__FILE__, __LINE__, "Unsupported binary expression operator: %s", expression->binary_data.operator_token->lexeme->data);
        }
    }
    case EXPRESSION__LITERAL: {
        return emit_load_literal(context, expression->literal_data.value);
    }
    case EXPRESSION__VARIABLE: {
        return emit_load_variable(context, expression->variable_data.name);
    }
    default:
        PANIC(__FILE__, __LINE__, "Unsupported expression kind: %s", expression__get_kind_name(expression));
    }
}

void emit_statement(Context *context, Statement *statement) {
    // INFO(__FILE__, __LINE__, "(%04d:%04d) -- %s", statement->location->line, statement->location->column, statement__get_kind_name(statement));
    switch (statement->kind) {
    case STATEMENT__ASSIGNMENT: {
        Expression *assignment_destination = statement->assignment_data.destination;
        if (assignment_destination->kind != EXPRESSION__VARIABLE) {
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Assignment to non-variables are not supported yet.", statement->location->line, statement->location->column);
        }
        String *variable_name = assignment_destination->variable_data.name->lexeme;
        Symbol_Table_Item *symbol = context__find_symbol(context, variable_name);
        if (symbol == NULL) {
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Undeclared variable: %s", statement->location->line, statement->location->column, variable_name->data);
        }
        Value_Holder *value = emit_expression(context, statement->assignment_data.value);
        emitf("  movq %s, %s(%%rip)", value->data, variable_name->data);
        context__release_register(context, value);
        return;
    }
    case STATEMENT__BLOCK: {
        // TODO: create block context
        for (List_Iterator iterator = list__create_iterator(statement->block_data.statements); list_iterator__has_next(&iterator);) {
            Statement *block_statement = list_iterator__next(&iterator);
            emit_statement(context, block_statement);
        }
        return;
    }
    case STATEMENT__BREAK: {
        Loop *loop = context->loop;
        if (loop == NULL) {
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- This break is not inside of a loop", statement->location->line, statement->location->column);
        }
        emitf("  jmp loop_%03d_end", loop->id);
        loop->has_exit = 1;
        return;
    }
    case STATEMENT__FUNCTION: {
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
    case STATEMENT__IF: {
        int label = counter__inc(context->counter);
        emitf("if_%03d_cond:", label);
        Value_Holder *condition = emit_expression(context, statement->if_data.condition);
        emitf("  dec %s", condition->data);
        context__release_register(context, condition);
        emitf("  jnz if_%03d_false", label);
        emitf("if_%03d_true:", label);
        emit_statement(context, statement->if_data.true_block);
        if (statement->if_data.false_block) {
            emitf("  jmp if_%03d_end", label);
        }
        emitf("if_%03d_false:", label);
        if (statement->if_data.false_block) {
            emit_statement(context, statement->if_data.false_block);
        }
        emitf("if_%03d_end:", label);
        break;
    }
    case STATEMENT__LOOP: {
        int label = counter__inc(context->counter);
        emitf("loop_%03d_start:", label);
        context->loop = loop__create(label, context->loop);
        emit_statement(context, statement->loop_data.block);
        if (!context->loop->has_exit) {
            WARNING(__FILE__, __LINE__, "(%04d:%04d) -- Infinite loop detected.", statement->location->line, statement->location->column);
        }
        context->loop = context->loop->parent;
        emitf("  jmp loop_%03d_start", label);
        emitf("loop_%03d_end:", label);
        break;
    }
    case STATEMENT__RETURN: {
        if (statement->return_data.expression != NULL) {
            Value_Holder *value_holder = emit_expression(context, statement->return_data.expression);
            emitf("  movq %s, %%rax", value_holder->data);
            context__release_register(context, value_holder);
        }
        if (context->loop) {
            context->loop->has_exit = 1;
        }
        emits("  movq %%rbp, %%rsp");
        emits("  popq %%rbp");
        emits("  ret");
        return;
    }
    case STATEMENT__VARIABLE: {
        // TODO: distiguish between global and local variables
        Token *variable_name = statement->variable_data.name;
        if (statement->variable_data.is_external) {
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- External variables are not supported yet.", statement->location->line, statement->location->column);
        }
        context__create_variable(context, variable_name->lexeme, statement->variable_data.type);
        Composite_Type *variable_type = statement->variable_data.type;
        int variable_type_size = compute_composite_type_size(context, variable_type);
        emitf("  .comm %s,  %d, 8", variable_name->lexeme->data, variable_type_size);
        Expression *variable_value = statement->variable_data.value;
        if (variable_value) {
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Variables with assignment are not supported yet.", statement->location->line, statement->location->column);
        }
        return;
    }
    default:
        PANIC(__FILE__, __LINE__, "Unsupported statement kind: %s", statement__get_kind_name(statement));
    }
}

void generate(char *file, Compilation_Unit *compilation_unit) {
    Context *context = context__create(fopen(file, "w"), compilation_unit->named_types);

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

    for (List_Iterator iterator = list__create_iterator(compilation_unit->statements); list_iterator__has_next(&iterator);) {
        Statement *statement = list_iterator__next(&iterator);
        emit_statement(context, statement);
        emits("");
    }

    fclose(context->file);
}
