#include "Generator.h"
#include "Logging.h"

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

typedef struct Variable {
    int id;
    String *name;
    Source_Location *location;
    Type *type;
    int is_global;
} Variable;

typedef List Variables;

Variables *variables__create() {
    return list__create();
}

Variable *variables__find(Variables *self, String *name) {
    for (List_Iterator iterator = list__create_reversed_iterator(self); list_iterator__has_next(&iterator);) {
        Variable *variable = list_iterator__next(&iterator);
        if (string__equals(name, variable->name->data)) {
            return variable;
        }
    }
    return NULL;
}

Variable *variables__add(Variables *self, int id, String *name, Source_Location *location, Type *type, int is_global) {
    Variable *variable = malloc(sizeof(Variable));
    variable->id = id;
    variable->name = name;
    variable->location = location;
    variable->type = type;
    variable->is_global = is_global;
    list__append(self, variable);
    return variable;
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
    Variables *variables;
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
    self->variables = variables__create();
    self->counter = counter__create();
    self->current_function = NULL;
    self->current_loop = NULL;
    return self;
}

Variable *context__find_variable(Context *self, String *name) {
    return variables__find(self->variables, name);
}

Variable *context__create_variable(Context *self, String *name, Source_Location *location, Type *type) {
    return variables__add(self->variables, counter__inc(self->counter), name, location, type, self->current_function == NULL);
}

Type *context__find_type(Context *self, String *name) {
    return named_types__get(self->named_types, name);
}

Type *context__resolve_type(Context *self, Type *type) {
    switch (type->kind) {
    case TYPE__BOOLEAN:
    case TYPE__INTEGER:
    case TYPE__NOTHING:
    case TYPE__POINTER:
        return type;
    case TYPE__NAMED: {
        String *type_name = type->named_data.name->lexeme;
        Type *named_type = context__find_type(self, type_name);
        if (named_type == NULL) {
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Unknown type: %s", type->location->line, type->location->column, type_name->data);
        }
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

Type *context__get_boolean_type(Context *self) {
    static String *type_name = NULL;
    if (type_name == NULL) {
        type_name = string__create("Boolean");
    }
    return context__find_type(self, type_name);
}

Type *context__get_integer_type(Context *self) {
    static String *type_name = NULL;
    if (type_name == NULL) {
        type_name = string__create("Int");
    }
    return context__find_type(self, type_name);
}

Type *compute_expression_type(Context *context, Expression *expression) {
    switch (expression->kind) {
    case EXPRESSION__BINARY: {
        Type *left_expression_type = compute_expression_type(context, expression->binary_data.left_expression);
        Type *right_expression_type = compute_expression_type(context, expression->binary_data.right_expression);
        Token *operator_token = expression->binary_data.operator_token;
        String *operator = operator_token->lexeme;
        if (string__equals(operator, "+") || string__equals(operator, "-") || string__equals(operator, "*") || string__equals(operator, "/") || string__equals(operator, "//")) {
            if (left_expression_type->kind != TYPE__INTEGER || right_expression_type->kind != TYPE__INTEGER) {
                PANIC(__FILE__, __LINE__, "(%04d:%04d) -- You can \"%s\" only integers", operator_token->location->line, operator_token->location->column, operator->data);
            }
        } else if (string__equals(operator, "<") || string__equals(operator, "<=") || string__equals(operator, ">") || string__equals(operator, ">=")) {
            if (left_expression_type->kind != TYPE__INTEGER || right_expression_type->kind != TYPE__INTEGER) {
                PANIC(__FILE__, __LINE__, "(%04d:%04d) -- You can \"%s\" only integers", operator_token->location->line, operator_token->location->column, operator->data);
            }
            return context__get_boolean_type(context);
        } else if (string__equals(operator, "==") || string__equals(operator, "!=")) {
            if (!type__equals(left_expression_type, right_expression_type)) {
                PANIC(__FILE__, __LINE__, "(%04d:%04d) -- You can \"%s\" same type only", operator_token->location->line, operator_token->location->column, operator->data);
            }
            return context__get_boolean_type(context);
        } else {
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Unsupported operator: %s", operator_token->location->line, operator_token->location->column, operator->data);
        }
        return left_expression_type;
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
        return context__resolve_type(context, function->function_data.return_type);
    }
    case EXPRESSION__LITERAL: {
        Token *literal = expression->literal_data.value;
        switch (literal->kind) {
        case TOKEN__INTEGER: {
            return context__get_integer_type(context);
        }
        case TOKEN__KEYWORD: {
            if (string__equals(literal->lexeme, "true") || string__equals(literal->lexeme, "false")) {
                return context__get_boolean_type(context);
            }
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Unsupported literal keyword: %s", literal->location->line, literal->location->column, literal->lexeme->data);
        }
        default:
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Unsupported literal expression kind: %s", literal->location->line, literal->location->column, token__get_kind_name(literal));
        }
    }
    case EXPRESSION__POINTED_VALUE: {
        Expression *pointer_expression = expression->pointed_value_data.expression;
        if (pointer_expression->kind != EXPRESSION__VARIABLE) {
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Not a variable expression", pointer_expression->location->line, pointer_expression->location->column);
        }
        String *variable_name = pointer_expression->variable_data.name->lexeme;
        Variable *variable = context__find_variable(context, variable_name);
        if (variable == NULL) {
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Undeclared variable: %s", expression->location->line, expression->location->column, variable_name->data);
        }
        Type *variable_type = variable->type;
        if (variable_type->kind != TYPE__POINTER) {
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Not a pointer variable", pointer_expression->location->line, pointer_expression->location->column);
        }
        return context__resolve_type(context, variable_type->pointer_data.type);
    }
    case EXPRESSION__POINTER_TO: {
        Expression *variable_expression = expression->pointer_to_data.expression;
        if (variable_expression->kind != EXPRESSION__VARIABLE) {
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Not a variable", variable_expression->location->line, variable_expression->location->column);
        }
        String *variable_name = variable_expression->variable_data.name->lexeme;
        Variable *variable = context__find_variable(context, variable_name);
        if (variable == NULL) {
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Undeclared variable: %s", expression->location->line, expression->location->column, variable_name->data);
        }
        Type *variable_type = variable->type; // context__resolve_type(context, variable->type);
        return type__create_pointer(expression->location, variable_type);
    }
    case EXPRESSION__VARIABLE: {
        String *variable_name = expression->variable_data.name->lexeme;
        Variable *variable = context__find_variable(context, variable_name);
        if (variable == NULL) {
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Undeclared variable: %s", expression->location->line, expression->location->column, variable_name->data);
        }
        return context__resolve_type(context, variable->type);
    }
    default:
        PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Unsupported expression kind: %s", expression->location->line, expression->location->column, expression__get_kind_name(expression));
    }
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
    Variable *variable = context__find_variable(context, variable_name->lexeme);
    if (variable == NULL) {
        PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Undeclared variable: %s", variable_name->location->line, variable_name->location->line, variable_name->lexeme->data);
    }

    // TODO: check if variable is local or global, and load it respectively

    Type *variable_type = context__resolve_type(context, variable->type);
    switch (variable_type->kind) {
    case TYPE__BOOLEAN: {
        Register *value_holder = registers__acquire(1);
        emitf("  movb %s_%03d(%%rip), %s", variable->name->data, variable->id, register__name(value_holder));
        return value_holder;
    }
    case TYPE__INTEGER: {
        Register *value_holder = registers__acquire(8);
        emitf("  movq %s_%03d(%%rip), %s", variable->name->data, variable->id, register__name(value_holder));
        return value_holder;
    }
    case TYPE__POINTER: {
        Register *value_holder = registers__acquire(8);
        emitf("  movq %s_%03d(%%rip), %s", variable->name->data, variable->id, register__name(value_holder));
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
        case TYPE__NOTHING: {
            return NULL;
        }
        default:
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Unsupported return type: %s", expression->location->line, expression->location->column, type__get_kind_name(function_return_type));
        }

        PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Expression calls are not implemented yet", expression->location->line, expression->location->column);
    }
    case EXPRESSION__LITERAL: {
        return emit_load_literal(context, expression->literal_data.value);
    }
    case EXPRESSION__POINTED_VALUE: {
        Expression *pointer_expression = expression->pointed_value_data.expression;
        if (pointer_expression->kind != EXPRESSION__VARIABLE) {
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Not a variable expression", pointer_expression->location->line, pointer_expression->location->column);
        }
        String *variable_name = pointer_expression->variable_data.name->lexeme;
        Variable *variable = context__find_variable(context, variable_name);
        if (variable == NULL) {
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Undeclared variable: %s", expression->location->line, expression->location->column, variable_name->data);
        }
        Type *variable_type = variable->type;
        if (variable_type->kind != TYPE__POINTER) {
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Not a pointer variable", pointer_expression->location->line, pointer_expression->location->column);
        }
        Register *pointer_holder = emit_load_variable(context, pointer_expression->variable_data.name);
        Type *value_type = context__resolve_type(context, variable_type->pointer_data.type);
        switch (value_type->kind) {
        case TYPE__BOOLEAN: {
            Register *value_holder = registers__acquire(1);
            emitf("  movb (%s), %s", register__name(pointer_holder), register__name(value_holder));
            register__release(pointer_holder);
            return value_holder;
        }
        case TYPE__INTEGER: {
            Register *value_holder = registers__acquire(8);
            emitf("  movq (%s), %s", register__name(pointer_holder), register__name(value_holder));
            register__release(pointer_holder);
            return value_holder;
        }
        default:
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Unsupported value type: %s", pointer_expression->location->line, pointer_expression->location->column, type__get_kind_name(value_type));
        }
    }
    case EXPRESSION__POINTER_TO: {
        Expression *variable_expression = expression->pointer_to_data.expression;
        if (variable_expression->kind != EXPRESSION__VARIABLE) {
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Not a variable", variable_expression->location->line, variable_expression->location->column);
        }
        String *variable_name = variable_expression->variable_data.name->lexeme;
        Variable *variable = context__find_variable(context, variable_name);
        if (variable == NULL) {
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Undeclared variable: %s", expression->location->line, expression->location->column, variable_name->data);
        }
        Register *value_holder = registers__acquire(8);
        if (variable->is_global) {
            emitf("  leaq %s_%03d(%%rip), %s", variable->name->data, variable->id, register__name(value_holder));
        } else {
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Local varaibles are not supported yet", variable_expression->location->line, variable_expression->location->column);
        }
        return value_holder;
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
        Variable *variable = context__find_variable(context, variable_name);
        if (variable == NULL) {
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Undeclared variable: %s", statement->location->line, statement->location->column, variable_name->data);
        }
        Type *variable_type = context__resolve_type(context, variable->type);
        Type *value_type = compute_expression_type(context, statement->assignment_data.value);
        if (!type__equals(variable_type, value_type)) {
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Destination type differs from value type. Expected %s but got %s instead.", statement->location->line, statement->location->column, type__get_kind_name(variable_type), type__get_kind_name(value_type));
        }
        Register *value_holder = emit_expression(context, statement->assignment_data.value);
        switch (variable_type->kind) {
        case TYPE__BOOLEAN: {
            if (value_holder->size != 1) {
                PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Expected expression result in a 1 byte register.", statement->location->line, statement->location->column);
            }
            emitf("  movb %s, %s_%03d(%%rip)", register__name(value_holder), variable_name->data, variable->id);
            break;
        }
        case TYPE__INTEGER:
            if (value_holder->size != 8) {
                PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Expected expression result in a 8 byte register.", statement->location->line, statement->location->column);
            }
            emitf("  movq %s, %s_%03d(%%rip)", register__name(value_holder), variable_name->data, variable->id);
            break;
        case TYPE__POINTER:
            if (value_holder->size != 8) {
                PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Expected expression result in a 8 byte register.", statement->location->line, statement->location->column);
            }
            emitf("  movq %s, %s_%03d(%%rip)", register__name(value_holder), variable_name->data, variable->id);
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
    case STATEMENT__EXPRESSION: {
        Expression *expression = statement->expression_data.expression;
        compute_expression_type(context, expression);
        Register *value_holder = emit_expression(context, expression);
        if (value_holder != NULL) {
            WARNING(__FILE__, __LINE__, "(%04d:%04d) -- The result of this expression is ignored", statement->location->line, statement->location->column);
            register__release(value_holder);
        }
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
        Expression *condition_expression = statement->if_data.condition;
        Type *condition_expression_type = compute_expression_type(context, condition_expression);
        if (condition_expression_type->kind != TYPE__BOOLEAN) {
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Not a boolean expression", condition_expression->location->line, condition_expression->location->column);
        }
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
        Type *function_return_type = context__resolve_type(context, function->function_data.return_type);
        if (statement->return_data.expression != NULL) {
            Expression *return_expression = statement->return_data.expression;
            Type *return_expression_type = compute_expression_type(context, return_expression);
            if (!type__equals(function_return_type, return_expression_type)) {
                PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Expression type doesn't match the return type", return_expression->location->line, return_expression->location->column);
            }
            Register *value_holder = emit_expression(context, return_expression);
            emitf("  movq %s, %%rax", register__name(value_holder));
            register__release(value_holder);
        } else if (function_return_type->kind != TYPE__NOTHING) {
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Expected return expression", statement->location->line, statement->location->column);
        }
        if (context->current_loop) {
            context->current_loop->has_exit = 1;
        }
        emitf("  jmp %s_end", function->function_data.name->lexeme->data);
        return;
    }
    case STATEMENT__VARIABLE: {
        Token *variable_name = statement->variable_data.name;
        if (statement->variable_data.is_external) {
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- External variables are not supported yet.", statement->location->line, statement->location->column);
        }
        Variable *variable = context__create_variable(context, variable_name->lexeme, statement->variable_data.name->location, statement->variable_data.type);
        if (!variable->is_global) {
            PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Local variables are not supported yet", statement->location->line, statement->location->column);
        }
        Type *variable_type = context__resolve_type(context, statement->variable_data.type);
        switch (variable_type->kind) {
        case TYPE__BOOLEAN: {
            emitf("  .comm %s_%03d, 1, 1", variable_name->lexeme->data, variable->id);
            break;
        }
        case TYPE__INTEGER: {
            emitf("  .comm %s_%03d, 8, 8", variable_name->lexeme->data, variable->id);
            break;
        }
        case TYPE__POINTER: {
            emitf("  .comm %s_%03d, 8, 8", variable_name->lexeme->data, variable->id);
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

        for (int i = 0; i < REGISTERS_COUNT; i++) {
            if (registers[i].is_used) {
                PANIC(__FILE__, __LINE__, "(%04d:%04d) -- Unrelease register found: %s", statement->location->line, statement->location->column, register__name(registers + i));
            }
        }
    }

    fclose(context->file);
}
