#include "Generator.h"
#include "Logging.h"
#include "Symbol_Table.h"

enum {
    REGISTER_RCX,
    REGISTER_R08,
    REGISTER_R09,
    REGISTER_R10,
    REGISTER_R11,
    REGISTERS_COUNT,
};

typedef struct Register {
    int id;
    int is_used;
    int size;
} Register;

char *register__name(Register *self) {
    static char *names_64bit[REGISTERS_COUNT] = { "%rcx", "%r8", "%r9", "%r10", "%r11" };
    static char *names_32bit[REGISTERS_COUNT] = { "%ecx", "%r8d", "%r9d", "%r10d", "%r11d" };
    static char *names_16bit[REGISTERS_COUNT] = { "%cx", "%r8w", "%r9w", "%r10w", "%r11w" };
    static char *names_8bit[REGISTERS_COUNT] = { "%cl", "%r8b", "%r9b", "%r10b", "%r11b" };

    switch (self->size) {
    case 8: return names_64bit[self->id];
    case 4: return names_32bit[self->id];
    case 2: return names_16bit[self->id];
    case 1: return names_8bit[self->id];
    default:
        PANIC(__FILE__, __LINE__, "Unsupported register: %d", self->id);
    }
}

void register__release(Register *self) {
    if (self->is_used != 1) {
        PANIC(__FILE__, __LINE__, "Trying to release an unused register: %s", register__name(self));
    }
    self->is_used = 0;
}

Register registers[REGISTERS_COUNT] = {
    { .id = REGISTER_RCX, .is_used = 0, .size = 0 },
    { .id = REGISTER_R08, .is_used = 0, .size = 0 },
    { .id = REGISTER_R09, .is_used = 0, .size = 0 },
    { .id = REGISTER_R10, .is_used = 0, .size = 0 },
    { .id = REGISTER_R11, .is_used = 0, .size = 0 },
};

Register *registers__acquire(int size) {
    for (int i = 0; i < REGISTERS_COUNT; i++) {
        if (registers[i].is_used == 0) {
            registers[i].is_used = 1;
            registers[i].size = size;
            return registers + i;
        }
    }
    PANIC(__FILE__, __LINE__, "All registers are used already%c", 0);
}

void registers__release_all() {
    for (int i = 0; i < REGISTERS_COUNT; i++) {
        registers[i].is_used = 0;
    }
}

typedef struct Loop {
    int id;
    int has_exit;
    struct Loop *parent;
} Loop;

Loop *loop__create(int id, Loop *parent) {
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

typedef struct Context {
    struct Context *global_context;
    struct Context *parent_context;
    FILE *file;
    Named_Functions *named_functions;
    Named_Types *named_types;
    Symbol_Table *symbols;
    Counter *counter;
    Statement *current_function;
    Loop *current_loop;
} Context;

#define emitf(line, ...) fprintf(context->file, line "\n", __VA_ARGS__)
#define emits(line) fprintf(context->file, line "\n")

static Context *context__create(FILE *file, Named_Functions *named_functions, Named_Types *named_types) {
    Context *self = malloc(sizeof(Context));
    self->global_context = self;
    self->parent_context = NULL;
    self->file = file;
    self->named_functions = named_functions;
    self->named_types = named_types;
    self->symbols = symbol_table__create();
    self->counter = counter__create();
    self->current_function = NULL;
    self->current_loop = NULL;
    return self;
}

Symbol *context__find_symbol(Context *self, String *name) {
    return symbol_table__find(self->symbols, name);
}

void context__create_variable(Context *self, String *name, Type *type) {
    if (context__find_symbol(self, name)) {
        PANIC(__FILE__, __LINE__, "Trying to create a variable that already exists in the same context: %s", name->data);
    }
    symbol_table__add(self->symbols, name, type);
}

static Type *context__resolve_type(Context *self, Type *type) {
    switch (type->kind) {
    case TYPE__BOOLEAN:
    case TYPE__INTEGER:
        return type;
    case TYPE__NAMED: {
        Type *named_type = named_types__get(self->named_types, type->named_data.name->lexeme);
        return context__resolve_type(self, named_type);
    }
    default:
        PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Unsupported type kind: %s", type->location->line, type->location->column, type__get_kind_name(type));
    }
}

int context__is_primitive_type(Context *self, Type *type) {
    Type *resolved_type = context__resolve_type(self, type);
    return resolved_type->kind == TYPE__INTEGER || resolved_type->kind == TYPE__BOOLEAN;
}

Register *emit_load_literal(Context *context, Token *token) {
    switch (token->kind) {
    case TOKEN__INTEGER: {
        Register *value_holder = registers__acquire(8);
        emitf("  movq $%d, %s", token->integer_data.value, register__name(value_holder));
        return value_holder;
    }
    case TOKEN__KEYWORD: {
        if (string__equals(token->lexeme, "false")) {
            Register *value_holder = registers__acquire(1);
            emitf("  movb $0, %s", register__name(value_holder));
            return value_holder;
        } else if (string__equals(token->lexeme, "true")) {
            Register *value_holder = registers__acquire(1);
            emitf("  movb $1, %s", register__name(value_holder));
            return value_holder;
        } else {
            PANIC(__FILE__, __LINE__, "Unsupported keyword: %s", token->lexeme->data);
        }
    }
    default:
        PANIC(__FILE__, __LINE__, "Unsupported token kind: %s", token__get_kind_name(token));
    }
}

Register *emit_load_variable(Context *context, Token *variable_name) {
    Symbol *symbol = context__find_symbol(context, variable_name->lexeme);
    if (symbol == NULL) {
        PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Undeclared variable: %s", variable_name->location->line, variable_name->location->line, variable_name->lexeme->data);
    }

    // TODO: check if variable is local or global, and load it respectively

    Type *variable_type = context__resolve_type(context, symbol->type);
    switch (variable_type->kind) {
    case TYPE__BOOLEAN: {
        Register *value_holder = registers__acquire(1);
        emitf("  movb %s(%%rip), %s", variable_name->lexeme->data, register__name(value_holder));
        return value_holder;
    }
    case TYPE__INTEGER: {
        Register *value_holder = registers__acquire(8);
        emitf("  movq %s(%%rip), %s", variable_name->lexeme->data, register__name(value_holder));
        return value_holder;
    }
    default:
        PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Unsupported variable type: %s", variable_name->location->line, variable_name->location->line, type__get_kind_name(variable_type));
    }
}

Register *emit_expression(Context *context, Expression *expression);

Register *emit_comparison_expression(Context *context, Expression *expression, Register *left_value_holder, const char *flag_instruction) {
    Register *right_value_holder = emit_expression(context, expression->binary_data.right_expression);
    if (left_value_holder->size != right_value_holder->size) {
        PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Cannot compare values of different type.", expression->location->line, expression->location->column);
    }
    switch (left_value_holder->size) {
    case 1: {
        emitf("  cmpb %s, %s", register__name(right_value_holder), register__name(left_value_holder));
        break;
    }
    case 8: {
        emitf("  cmpq %s, %s", register__name(right_value_holder), register__name(left_value_holder));
        break;
    }
    default:
        PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Unsupported value size: %d.", expression->location->line, expression->location->column, left_value_holder->size);
    }
    register__release(left_value_holder);
    register__release(right_value_holder);
    Register *result_value_holder = registers__acquire(1);
    emitf("  %s %s", flag_instruction, register__name(result_value_holder));
    return result_value_holder;
}

Register *emit_expression(Context *context, Expression *expression) {
    switch (expression->kind) {
    case EXPRESSION__BINARY: {
        Register *left_value_holder = emit_expression(context, expression->binary_data.left_expression);
        if (string__equals(expression->binary_data.operator_token->lexeme, "+")) {
            Register *right_value_holder = emit_expression(context, expression->binary_data.right_expression);
            emitf("  addq %s, %s", register__name(left_value_holder), register__name(right_value_holder));
            register__release(left_value_holder);
            return right_value_holder;
        } else if (string__equals(expression->binary_data.operator_token->lexeme, "-")) {
            Register *right_value_holder = emit_expression(context, expression->binary_data.right_expression);
            emitf("  subq %s, %s", register__name(right_value_holder), register__name(left_value_holder));
            register__release(right_value_holder);
            return left_value_holder;
        } else if (string__equals(expression->binary_data.operator_token->lexeme, "*")) {
            Register *right_value_holder = emit_expression(context, expression->binary_data.right_expression);
            emitf("  imulq %s, %s", register__name(left_value_holder), register__name(right_value_holder));
            register__release(left_value_holder);
            return right_value_holder;
        } else if (string__equals(expression->binary_data.operator_token->lexeme, "/")) {            
            Register *right_value_holder = emit_expression(context, expression->binary_data.right_expression);
            emitf("  movq %s, %%rax", register__name(left_value_holder));
            emits("  cqto");
            emitf("  idivq %s", register__name(right_value_holder));
            emitf("  movq %%rax, %s", register__name(left_value_holder));
            register__release(right_value_holder);
            return left_value_holder;
        } else if (string__equals(expression->binary_data.operator_token->lexeme, "//")) {            
            Register *right_value_holder = emit_expression(context, expression->binary_data.right_expression);
            emitf("  movq %s, %%rax", register__name(left_value_holder));
            emits("  cqto");
            emitf("  idivq %s", register__name(right_value_holder));
            emitf("  movq %%rdx, %s", register__name(left_value_holder));
            register__release(right_value_holder);
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
    case EXPRESSION__CALL: {
        Expression *callee = expression->call_data.callee;
        Argument_List *arguments = expression->call_data.arguments;
        if (callee->kind != EXPRESSION__VARIABLE) {
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Only simple function calls like \"example()\" are supported", expression->location->line, expression->location->column);
        }
        String *function_name = callee->variable_data.name->lexeme;
        Statement *function = named_functions__get(context->named_functions, function_name, arguments);
        if (function == NULL) {
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Unknown function: %s", expression->location->line, expression->location->column, function_name->data);
        }
        if (list__size(arguments) > 0) {
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Only function calls without arguments are supported", expression->location->line, expression->location->column);
        }
        
        emitf("  call %s", function_name->data);

        Type *function_return_type = context__resolve_type(context, function->function_data.return_type);
        switch (function_return_type->kind) {
        case TYPE__INTEGER: {
            Register *value_holder = registers__acquire(8);
            emitf("  movq %%rax, %s", register__name(value_holder));
            return value_holder;
        }
        default:
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Unsupported return type: %s", expression->location->line, expression->location->column, type__get_kind_name(function_return_type));
        }

        PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Expression calls are not implemented yet", expression->location->line, expression->location->column);
    }
    case EXPRESSION__LITERAL: {
        return emit_load_literal(context, expression->literal_data.value);
    }
    case EXPRESSION__VARIABLE: {
        return emit_load_variable(context, expression->variable_data.name);
    }
    default:
        PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Unsupported expression kind: %s", expression->location->line, expression->location->column, expression__get_kind_name(expression));
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
        Symbol *symbol = context__find_symbol(context, variable_name);
        if (symbol == NULL) {
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Undeclared variable: %s", statement->location->line, statement->location->column, variable_name->data);
        }
        Type *variable_type = context__resolve_type(context, symbol->type);
        // TODO: make sure value expression has the same type as the variable
        Register *value_holder = emit_expression(context, statement->assignment_data.value);
        switch (variable_type->kind) {
        case TYPE__BOOLEAN: {
            if (value_holder->size != 1) {
                PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Expected expression result in a 1 byte register.", statement->location->line, statement->location->column);
            }
            emitf("  movb %s, %s(%%rip)", register__name(value_holder), variable_name->data);
            break;
        }
        case TYPE__INTEGER:
            if (value_holder->size != 8) {
                PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Expected expression result in a 8 byte register.", statement->location->line, statement->location->column);
            }
            emitf("  movq %s, %s(%%rip)", register__name(value_holder), variable_name->data);
            break;
        default:
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Unsupported variable type: %s.", statement->location->line, statement->location->column, type__get_kind_name(variable_type));
        }
        register__release(value_holder);
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
        Loop *loop = context->current_loop;
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

        context->current_function = statement;
        for (List_Iterator iterator = list__create_iterator(statement->function_data.statements); list_iterator__has_next(&iterator);) {
            Statement *body_statement = list_iterator__next(&iterator);
            emit_statement(context, body_statement);
        }
        context->current_function = NULL;

        emitf("%s_end:", function_name->data);
        emits("  movq %%rbp, %%rsp");
        emits("  popq %%rbp");
        emits("  ret");
        return;
    }
    case STATEMENT__IF: {
        int label = counter__inc(context->counter);
        emitf("if_%03d_cond:", label);
        Register *condition_value_holder = emit_expression(context, statement->if_data.condition);
        emitf("  dec %s", register__name(condition_value_holder));
        register__release(condition_value_holder);
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
        context->current_loop = loop__create(label, context->current_loop);
        emit_statement(context, statement->loop_data.block);
        if (!context->current_loop->has_exit) {
            WARNING(__FILE__, __LINE__, "(%04d:%04d) -- Infinite loop detected.", statement->location->line, statement->location->column);
        }
        context->current_loop = context->current_loop->parent;
        emitf("  jmp loop_%03d_start", label);
        emitf("loop_%03d_end:", label);
        break;
    }
    case STATEMENT__RETURN: {
        Statement *function = context->current_function;
        if (function == NULL) {
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Found return statement outside of a function.", statement->location->line, statement->location->column);
        }
        if (statement->return_data.expression != NULL) {
            Register *value_holder = emit_expression(context, statement->return_data.expression);
            emitf("  movq %s, %%rax", register__name(value_holder));
            register__release(value_holder);
        }
        if (context->current_loop) {
            context->current_loop->has_exit = 1;
        }
        emitf("  jmp %s_end", function->function_data.name->lexeme->data);
        return;
    }
    case STATEMENT__VARIABLE: {
        // TODO: distiguish between global and local variables
        Token *variable_name = statement->variable_data.name;
        if (statement->variable_data.is_external) {
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- External variables are not supported yet.", statement->location->line, statement->location->column);
        }
        context__create_variable(context, variable_name->lexeme, statement->variable_data.type);
        Type *variable_type = context__resolve_type(context, statement->variable_data.type);
        switch (variable_type->kind) {
        case TYPE__BOOLEAN: {
            emitf("  .comm %s, 1, 1", variable_name->lexeme->data);
            break;
        }
        case TYPE__INTEGER: {
            emitf("  .comm %s, 8, 8", variable_name->lexeme->data);
            break;
        }
        default:
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Unsupported variable type: %s", statement->location->line, statement->location->column, type__get_kind_name(variable_type));
        }
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
    Context *context = context__create(fopen(file, "w"), compilation_unit->named_functions, compilation_unit->named_types);

    emits("  .text");

    for (List_Iterator iterator = list__create_iterator(compilation_unit->statements); list_iterator__has_next(&iterator);) {
        Statement *statement = list_iterator__next(&iterator);
        emits("");
        emit_statement(context, statement);
    }

    fclose(context->file);
}
