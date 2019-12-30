#include "Generator.h"
#include "Logging.h"

#include <stdlib.h>

#define FALSE 0
#define TRUE 1

typedef struct IR_Type {
    enum {
        IR_TYPE_BOOLEAN,
        IR_TYPE_CHARACTER,
        IR_TYPE_INTEGER,
        IR_TYPE_OPAQUE,
        IR_TYPE_POINTER,
    } kind;

    union {
        struct {
            struct IR_Type *type;
        } pointer;
    };

    String *name;
    String *repr;
} IR_Type;

typedef struct IR_Types_Item {
    IR_Type *type;
    struct IR_Types_Item *next;
} IR_Types_Item;

typedef struct IR_Types {
    IR_Types_Item *first;
    IR_Types_Item *last;
} IR_Types;

typedef struct IR_Value {
    enum {
        IR_VALUE_CONSTANT,
        IR_VALUE_FUNCTION,
        IR_VALUE_LABEL,
        IR_VALUE_PARAMETER,
        IR_VALUE_POINTER,
        IR_VALUE_TEMP_VARIABLE,
    } kind;

    IR_Type *type;
    String *name;
    String *repr;
} IR_Value;

#define VALUE_NAME(value) value->name->data
#define VALUE_REPR(value) value->repr->data
#define VALUE_TYPE(value) value->type->repr->data

typedef struct IR_Values_Item {
    IR_Value *value;
    struct IR_Values_Item *prev;
    struct IR_Values_Item *next;
} IR_Values_Item;

typedef struct IR_Values {
    IR_Values_Item *first;
    IR_Values_Item *last;
    struct IR_Values *parent;
} IR_Values;

typedef struct Loop {
    IR_Value *loop_end;
    int has_break;
    struct Loop *parent;
} Loop;

typedef struct Counter {
    int count;
} Counter;

typedef struct Context {
    FILE *file;
    IR_Types *types;
    IR_Values *declarations;
    IR_Values *allocas;
    Loop *loop;
    Counter *temp_variables;
} Context;

IR_Type *type__create(int kind, String *name, String *repr) {
    IR_Type *self = (IR_Type *)malloc(sizeof(IR_Type));
    self->kind = kind;
    self->name = name;
    self->repr = repr;
    return self;
}

IR_Type *type__create_pointer(IR_Type *type) {
    String *name = string__create("@");
    string__append_string(name, type->name);
    String *repr = string__create(type->repr->data);
    string__append_char(repr, '*');
    return type__create(IR_TYPE_POINTER, name, repr);
}

IR_Types *types__create() {
    IR_Types *self = (IR_Types *)malloc(sizeof(IR_Types));
    self->first = NULL;
    self->last = NULL;
    return self;
}

void types__append(IR_Types *self, IR_Type *type) {
    IR_Types_Item *item = (IR_Types_Item *)malloc(sizeof(IR_Types_Item));
    item->type = type;
    item->next = NULL;
    if (self->first == NULL) {
        self->first = item;
    } else {
        self->last->next = item;
    }
    self->last = item;
}

IR_Type *types__get_by_name(IR_Types *self, String *name) {
    if (self == NULL) {
        return NULL;
    }
    IR_Types_Item *item = self->first;
    while (item != NULL) {
        if (string__equals(item->type->name, name->data)) {
            return item->type;
        }
        item = item->next;
    }
    WARNING(__FILE__, __LINE__, "No such type: %s", name->data);
    return NULL;
}

IR_Type *types__get_by_type(IR_Types *self, Type *type) {
    switch (type->kind) {
    case TYPE_POINTER:
        return type__create_pointer(types__get_by_type(self, type->pointer.type));
    case TYPE_SIMPLE:
        return types__get_by_name(self, type->simple.name->lexeme);
    default:
        ERROR(__FILE__, __LINE__, "Unsupported type: %d", type->kind);
        exit(1);
    }
}

IR_Value *value__create(int kind, IR_Type *type, String *name, String *repr) {
    IR_Value *value = (IR_Value *)malloc(sizeof(IR_Value));
    value->kind = kind;
    value->type = type;
    value->name = name;
    value->repr = repr;
    return value;
}

IR_Values *values__create() {
    IR_Values *self = (IR_Values *)malloc(sizeof(IR_Values));
    self->first = NULL;
    self->last = NULL;
    self->parent = NULL;
    return self;
}

void values__append(IR_Values *self, IR_Value *value) {
    IR_Values_Item *item = (IR_Values_Item *)malloc(sizeof(IR_Values_Item));
    item->value = value;
    if (self->first == NULL) {
        item->prev = NULL;
        self->first = item;
    } else {
        item->prev = self->last;
        self->last->next = item;
    }
    item->next = NULL;
    self->last = item;
}

IR_Value *values__find(IR_Values *self, String *name) {
    if (self == NULL) {
        return NULL;
    }
    IR_Values_Item *item = self->last;
    while (item != NULL) {
        if (string__equals(item->value->name, name->data)) {
            return item->value;
        }
        item = item->prev;
    }
    return values__find(self->parent, name);
}

Counter *counter__create() {
    Counter *self = (Counter *)malloc(sizeof(Counter));
    self->count = 0;
    return self;
}

Counter *counter__clone(Counter *other) {
    Counter *self = (Counter *)malloc(sizeof(Counter));
    self->count = other->count;
    return self;
}

int counter__get(Counter *self) {
    return self->count;
}

void counter__increment(Counter *self) {
    self->count += 1;
}

Context *context__create(FILE *file) {
    Context *self = (Context *)malloc(sizeof(Context));
    self->file = file;
    self->types = types__create();
    self->declarations = values__create();
    self->allocas = values__create();
    self->loop = NULL;
    self->temp_variables = counter__create();
    return self;
}

Context *context__clone(Context *other) {
    Context *self = (Context *)malloc(sizeof(Context));
    self->file = other->file;
    self->types = other->types;
    self->declarations = other->declarations;
    self->allocas = other->allocas;
    self->loop = other->loop;
    self->temp_variables = other->temp_variables;
    return self;
}

IR_Value *value__create_function(Context *context, IR_Type *type, String *name) {
    String *repr = string__create("@");
    string__append_string(repr, name);
    IR_Value *self = value__create(IR_VALUE_FUNCTION, type, name, repr);
    values__append(context->declarations, self);
    return self;
}

IR_Value *value__create_label(Context *context, String *name) {
    string__append_char(name, '.');
    if (counter__get(context->temp_variables) < 100) {
        string__append_char(name, '0');
    }
    if (counter__get(context->temp_variables) < 10) {
        string__append_char(name, '0');
    }
    string__append_int(name, counter__get(context->temp_variables));
    String *repr = string__create("%");
    string__append_string(repr, name);
    counter__increment(context->temp_variables);
    return value__create(IR_VALUE_LABEL, NULL, name, repr);
}

IR_Value *value__create_parameter(Context *context, IR_Type *type, String *name) {
    String *repr = string__create("%");
    string__append_string(repr, name);
    IR_Value *self = value__create(IR_VALUE_PARAMETER, type, name, repr);
    values__append(context->declarations, self);
    return self;
}

IR_Value *value__create_global_variable(Context *context, IR_Type *type, String *name) {
    String *repr = string__create("@");
    string__append_string(repr, name);
    IR_Value *self = value__create(IR_VALUE_POINTER, type, name, repr);
    values__append(context->declarations, self);
    return self;
}

IR_Value *value__create_local_variable(Context *context, IR_Type *type, String *name) {
    String *repr = string__create("%");
    string__append_string(repr, name);
    IR_Value *shadowed_variable = values__find(context->declarations, name);
    if (shadowed_variable != NULL) {
        string__append_char(repr, '.');
        if (counter__get(context->temp_variables) < 100) {
            string__append_char(repr, '0');
        }
        if (counter__get(context->temp_variables) < 10) {
            string__append_char(repr, '0');
        }
        string__append_int(repr, counter__get(context->temp_variables));
        counter__increment(context->temp_variables);
    }
    IR_Value *self = value__create(IR_VALUE_POINTER, type, name, repr);
    values__append(context->declarations, self);
    return self;
}

IR_Value *value__create_temp_variable(Context *context, IR_Type *type) {
    String *repr = string__create("%.");
    if (counter__get(context->temp_variables) < 100) {
        string__append_char(repr, '0');
    }
    if (counter__get(context->temp_variables) < 10) {
        string__append_char(repr, '0');
    }
    string__append_int(repr, counter__get(context->temp_variables));
    counter__increment(context->temp_variables);
    return value__create(IR_VALUE_TEMP_VARIABLE, type, NULL, repr);
}

IR_Value *emit_literal(Context *context, Token *token) {
    switch (token->kind) {
        case TOKEN_CHARACTER: {
            IR_Type *type = types__get_by_name(context->types, string__create("Char"));
            String *repr = string__append_int(string__create_empty(0), token->character.value);
            return value__create(IR_VALUE_CONSTANT, type, NULL, repr);
        }
        case TOKEN_INTEGER: {
            IR_Type *type = types__get_by_name(context->types, string__create("Int"));
            String *repr = string__append_int(string__create_empty(0), token->integer.value);
            return value__create(IR_VALUE_CONSTANT, type, NULL, repr);
        }
        default: {
            ERROR(__FILE__, __LINE__, "Unsupported token type: %d", token->kind);
            exit(1);
        }
    }
}

IR_Value *emit_expression(Context *context, Expression *expression);

IR_Value *emit_arithmetic_expression(Context *context, Expression *expression, const char *instruction) {
    IR_Value *left_value = emit_expression(context, expression->binary.left_expression);
    IR_Value *right_value = emit_expression(context, expression->binary.right_expression);
    IR_Value *result = value__create_temp_variable(context, left_value->type);
    fprintf(context->file, "  %s = %s %s %s, %s\n", VALUE_REPR(result), instruction, VALUE_TYPE(result), VALUE_REPR(left_value), VALUE_REPR(right_value));
    return result;
}

IR_Value *emit_comparison_expression(Context *context, Expression *expression, const char *icmp_operand) {
    IR_Value *left_value = emit_expression(context, expression->binary.left_expression);
    IR_Value *right_value = emit_expression(context, expression->binary.right_expression);
    IR_Value *result = value__create_temp_variable(context, types__get_by_name(context->types, string__create("Bool")));
    fprintf(context->file, "  %s = icmp %s %s %s, %s\n", VALUE_REPR(result), icmp_operand, VALUE_TYPE(left_value), VALUE_REPR(left_value), VALUE_REPR(right_value));
    return result;
}

IR_Value *emit_expression(Context *context, Expression *expression) {
    switch (expression->kind) {
    case EXPRESSION_BINARY: {
        if (string__equals(expression->binary.operator_token->lexeme, "+")) {
            return emit_arithmetic_expression(context, expression, "add");
        } else if (string__equals(expression->binary.operator_token->lexeme, "-")) {
            return emit_arithmetic_expression(context, expression, "sub");
        } else if (string__equals(expression->binary.operator_token->lexeme, "*")) {
            return emit_arithmetic_expression(context, expression, "mul");
        } else if (string__equals(expression->binary.operator_token->lexeme, "/")) {
            return emit_arithmetic_expression(context, expression, "sdiv");
        } else if (string__equals(expression->binary.operator_token->lexeme, "//")) {
            return emit_arithmetic_expression(context, expression, "srem");
        } else if (string__equals(expression->binary.operator_token->lexeme, "<")) {
            return emit_comparison_expression(context, expression, "slt");
        } else if (string__equals(expression->binary.operator_token->lexeme, "<=")) {
            return emit_comparison_expression(context, expression, "sle");
        } else if (string__equals(expression->binary.operator_token->lexeme, ">")) {
            return emit_comparison_expression(context, expression, "sgt");
        } else if (string__equals(expression->binary.operator_token->lexeme, ">=")) {
            return emit_comparison_expression(context, expression, "sge");
        } else if (string__equals(expression->binary.operator_token->lexeme, "==")) {
            return emit_comparison_expression(context, expression, "eq");
        } else if (string__equals(expression->binary.operator_token->lexeme, "&&")) {
            IR_Value *left_value = emit_expression(context, expression->binary.left_expression);
            IR_Value *and_true_label = value__create_label(context, string__create("and_true"));
            IR_Value *and_false_label = value__create_label(context, string__create("and_false"));
            IR_Value *and_result_label = value__create_label(context, string__create("and_result"));
            fprintf(context->file, "  br i1 %s, label %s, label %s\n", VALUE_REPR(left_value), VALUE_REPR(and_true_label), VALUE_REPR(and_false_label));
            fprintf(context->file, "%s:\n", VALUE_NAME(and_true_label));
            IR_Value *right_value = emit_expression(context, expression->binary.right_expression);
            fprintf(context->file, "  br label %s\n", VALUE_REPR(and_result_label));
            fprintf(context->file, "%s:\n", VALUE_NAME(and_false_label));
            fprintf(context->file, "  br label %s\n", VALUE_REPR(and_result_label));
            fprintf(context->file, "%s:\n", VALUE_NAME(and_result_label));
            IR_Value *result = value__create_temp_variable(context, types__get_by_name(context->types, string__create("Bool")));
            fprintf(context->file, "  %s = phi i1 [ %s, %s ], [ 0, %s ]\n", VALUE_REPR(result), VALUE_REPR(right_value), VALUE_REPR(and_true_label), VALUE_REPR(and_false_label));
            return result;
        } else if (string__equals(expression->binary.operator_token->lexeme, "||")) {
            IR_Value *left_value = emit_expression(context, expression->binary.left_expression);
            IR_Value *or_true_label = value__create_label(context, string__create("or_true"));
            IR_Value *or_false_label = value__create_label(context, string__create("or_false"));
            IR_Value *or_result_label = value__create_label(context, string__create("or_result"));
            fprintf(context->file, "  br i1 %s, label %s, label %s\n", VALUE_REPR(left_value), VALUE_REPR(or_true_label), VALUE_REPR(or_false_label));
            fprintf(context->file, "%s:\n", VALUE_NAME(or_true_label));
            fprintf(context->file, "  br label %s\n", VALUE_REPR(or_result_label));
            fprintf(context->file, "%s:\n", VALUE_NAME(or_false_label));
            IR_Value *right_value = emit_expression(context, expression->binary.right_expression);
            fprintf(context->file, "  br label %s\n", VALUE_REPR(or_result_label));
            fprintf(context->file, "%s:\n", VALUE_NAME(or_result_label));
            IR_Value *result = value__create_temp_variable(context, types__get_by_name(context->types, string__create("Bool")));
            fprintf(context->file, "  %s = phi i1 [ %s, %s ], [ 1, %s ]\n", VALUE_REPR(result), VALUE_REPR(right_value), VALUE_REPR(or_false_label), VALUE_REPR(or_true_label));
            return result;
        } else {
            ERROR(__FILE__, __LINE__, "Unsupported binary expression operator: %s", expression->binary.operator_token->lexeme->data);
            exit(1);
        }
    }
    case EXPRESSION_CALL: {
        String *function_name = expression->call.callee->variable.name->lexeme;
        IR_Value *function = values__find(context->declarations, function_name);
        if (function == NULL) {
            ERROR(__FILE__, __LINE__, "Undefined function: %s", function_name->data);
            exit(1);
        }
        IR_Values *function_arguments = values__create();
        Argument *argument = expression->call.first_argument;
        while (argument != NULL) {
            IR_Value *function_argument = emit_expression(context, argument->value);
            values__append(function_arguments, function_argument);
            argument = argument->next;
        }
        IR_Value *result = value__create_temp_variable(context, types__get_by_name(context->types, string__create("Int"))); // TODO: retrieve function return type
        fprintf(context->file, "  %s = call %s %s(", VALUE_REPR(result), VALUE_TYPE(function), VALUE_REPR(function));
        IR_Values_Item *function_argument = function_arguments->first;
        while (function_argument != NULL) {
            fprintf(context->file, "%s %s", VALUE_TYPE(function_argument->value), VALUE_REPR(function_argument->value));
            function_argument = function_argument->next;
            if (function_argument != NULL) {
                fprintf(context->file, ", ");
            }
        }
        fprintf(context->file, ")\n");
        return result;
    }
    case EXPRESSION_CAST: {
        IR_Value *operand = emit_expression(context, expression->cast.expression);
        IR_Type *type = types__get_by_type(context->types, expression->cast.type);
        if (string__equals(type->name, "Int")) {
            IR_Value *result = value__create_temp_variable(context, type);
            fprintf(context->file, "  %s = sext %s %s to %s\n", VALUE_REPR(result), VALUE_TYPE(operand), VALUE_REPR(operand), VALUE_TYPE(result));
            return result;
        } else if (string__equals(type->name, "Char")) {
            IR_Value *result = value__create_temp_variable(context, type);
            fprintf(context->file, "  %s = trunc %s %s to %s\n", VALUE_REPR(result), VALUE_TYPE(operand), VALUE_REPR(operand), VALUE_TYPE(result));
            return result;
        } else {
            ERROR(__FILE__, __LINE__, "Cannot cast to %s", type->name->data);
            exit(1);
        }
    }
    case EXPRESSION_LITERAL: {
        return emit_literal(context, expression->literal.value);
    }
    case EXPRESSION_UNARY: {
        if (string__equals(expression->unary.operator_token->lexeme, "-")) {
            IR_Value *right_value = emit_expression(context, expression->unary.expression);
            IR_Value *result = value__create_temp_variable(context, right_value->type);
            fprintf(context->file, "  %s = sub %s 0, %s\n", VALUE_REPR(result), VALUE_TYPE(result), VALUE_REPR(right_value));
            return result;
        } else {
            ERROR(__FILE__, __LINE__, "Unsupported unary expression operator: %s", expression->unary.operator_token->lexeme->data);
            exit(1);
        }
    }
    case EXPRESSION_VARIABLE: {
        String *variable_name = expression->variable.name->lexeme;
        IR_Value *variable = values__find(context->declarations, variable_name);
        if (variable == NULL) {
            ERROR(__FILE__, __LINE__, "Undefined variable: %s", variable_name->data);
            exit(1);
        }
        if (variable->kind == IR_VALUE_POINTER) {
            IR_Value *result = value__create_temp_variable(context, variable->type);
            fprintf(context->file, "  %s = load %s, %s* %s\n", VALUE_REPR(result), VALUE_TYPE(variable), VALUE_TYPE(variable), VALUE_REPR(variable));
            return result;
        } else {
            return variable;
        }
    }
    default:
        ERROR(__FILE__, __LINE__, "Unsupported expression type: %d", expression->kind);
        exit(1);
    }
}

Context *create_function_context(Context *global_context) {
    Context *function_context = context__clone(global_context);
    function_context->declarations = values__create();
    function_context->declarations->parent = global_context->declarations;
    function_context->allocas = values__create();
    function_context->temp_variables = counter__create();
    return function_context;
}

Context *create_block_context(Context *function_context) {
    Context *block_context = context__clone(function_context);
    block_context->declarations = values__create();
    block_context->declarations->parent = function_context->declarations;
    return block_context;
}

void emit_statement(Context *context, Statement *statement) {
    switch (statement->kind) {
    case STATEMENT_ASSIGNMENT: {
        String *variable_name = statement->assignment.destination->variable.name->lexeme;
        IR_Value *variable = values__find(context->declarations, variable_name);
        if (variable == NULL) {
            ERROR(__FILE__, __LINE__, "Undefined variable: %s", variable_name->data);
            exit(1);
        }
        IR_Value *value;
        if (string__equals(statement->assignment.operator_token->lexeme, "=")) {
            value = emit_expression(context, statement->variable_declaration.value);
        } else {
            Expression *binary_expression = (Expression *)malloc(sizeof(Expression));
            binary_expression->kind = EXPRESSION_BINARY;
            binary_expression->binary.operator_token = statement->assignment.operator_token;
            binary_expression->binary.left_expression = statement->assignment.destination;
            binary_expression->binary.right_expression = statement->variable_declaration.value;
            if (string__equals(statement->assignment.operator_token->lexeme, "+=")) {
                value = emit_arithmetic_expression(context, binary_expression, "add");
            } else if (string__equals(statement->assignment.operator_token->lexeme, "-=")) {
                value = emit_arithmetic_expression(context, binary_expression, "sub");
            } else if (string__equals(statement->assignment.operator_token->lexeme, "*=")) {
                value = emit_arithmetic_expression(context, binary_expression, "mul");
            } else if (string__equals(statement->assignment.operator_token->lexeme, "/=")) {
                value = emit_arithmetic_expression(context, binary_expression, "sdiv");
            } else {
                ERROR(__FILE__, __LINE__, "Unsupported assignment operator: %s", statement->assignment.operator_token->lexeme->data);
                exit(1);
            }
        }
        fprintf(context->file, "  store i32 %s, i32* %s\n", VALUE_REPR(value), VALUE_REPR(variable));
        return;
    }
    case STATEMENT_BLOCK: {
        context = create_block_context(context);
        Statement *block_statement = statement->block.first_statement;
        while (block_statement != NULL) {
            emit_statement(context, block_statement);
            block_statement = block_statement->next;
        }
        return;
    }
    case STATEMENT_BREAK: {
        fprintf(context->file, "  br label %s\n", VALUE_REPR(context->loop->loop_end));
        context->loop->has_break = TRUE;
        return;
    }
    case STATEMENT_EXPRESSION: {
        emit_expression(context, statement->expression);
        return;
    }
    case STATEMENT_FUNCTION_DECLARATION: {
        IR_Value *function = value__create_function(context, types__get_by_type(context->types, statement->function_declaration.return_type), statement->function_definition.name->literal.value->lexeme);
        fprintf(context->file, "declare i32 %s(", VALUE_REPR(function));
        Member *parameter = statement->function_definition.first_parameter;
        while (parameter != NULL) {
            IR_Type *parameter_type = types__get_by_type(context->types, parameter->type);
            IR_Value *parameter_value = value__create_parameter(context, parameter_type, parameter->name->lexeme);
            fprintf(context->file, "%s %s", VALUE_TYPE(parameter_value), VALUE_REPR(parameter_value));
            parameter = parameter->next;
            if (parameter != NULL) {
                fprintf(context->file, ", ");
            }
        }
        fprintf(context->file, ")\n");
        return;
    }
    case STATEMENT_FUNCTION_DEFINITION: {
        IR_Value *function = value__create_function(context, types__get_by_type(context->types, statement->function_definition.return_type), statement->function_definition.name->literal.value->lexeme);
        
        context = create_function_context(context);

        fprintf(context->file, "define i32 %s(", VALUE_REPR(function));
        Member *parameter = statement->function_definition.first_parameter;
        while (parameter != NULL) {
            IR_Type *parameter_type = types__get_by_type(context->types, parameter->type);
            IR_Value *parameter_value = value__create_parameter(context, parameter_type, parameter->name->lexeme);
            fprintf(context->file, "%s %s", VALUE_TYPE(parameter_value), VALUE_REPR(parameter_value));
            parameter = parameter->next;
            if (parameter != NULL) {
                fprintf(context->file, ", ");
            }
        }
        fprintf(context->file, ") {\n");

        IR_Value *entry_label = value__create_label(context, string__create("entry"));
        IR_Value *variables_label = value__create_label(context, string__create("variables"));
        fprintf(context->file, "  br label %s\n", VALUE_REPR(variables_label));
        fprintf(context->file, "%s:\n", VALUE_NAME(entry_label));

        Statement *body_statement = statement->function_definition.first_statement;
        while (body_statement != NULL) {
            emit_statement(context, body_statement);
            body_statement = body_statement->next;
        }

        fprintf(context->file, "%s:\n", VALUE_NAME(variables_label));
        IR_Values_Item *alloca_item = context->allocas->first;
        while (alloca_item != NULL) {
            fprintf(context->file, "  %s = alloca i32\n", VALUE_REPR(alloca_item->value));
            alloca_item = alloca_item->next;
        }
        fprintf(context->file, "  br label %s\n", VALUE_REPR(entry_label));

        fprintf(context->file, "}\n");

        return;
    }
    case STATEMENT_IF: {
        IR_Value *if_cond = emit_expression(context, statement->if_.condition);
        IR_Value *if_true = value__create_label(context, string__create("if_true"));
        IR_Value *if_false = value__create_label(context, string__create("if_false"));
        IR_Value *if_end = value__create_label(context, string__create("if_end"));
        fprintf(context->file, "  br i1 %s, label %s, label %s\n", VALUE_REPR(if_cond), VALUE_REPR(if_true), statement->if_.false_block != NULL ? VALUE_REPR(if_false) : VALUE_REPR(if_end));
        fprintf(context->file, "%s:\n", VALUE_NAME(if_true));
        emit_statement(context, statement->if_.true_block);
        fprintf(context->file, "  br label %s\n", VALUE_REPR(if_end));
        if (statement->if_.false_block != NULL) {
            fprintf(context->file, "%s:\n", VALUE_NAME(if_false));
            emit_statement(context, statement->if_.false_block);
            fprintf(context->file, "  br label %s\n", VALUE_REPR(if_end));
        }
        fprintf(context->file, "%s:\n", VALUE_NAME(if_end));
        return;
    }
    case STATEMENT_LOOP: {
        context = create_block_context(context);
        IR_Value *loop_start = value__create_label(context, string__create("loop_start"));
        IR_Value *loop_end = value__create_label(context, string__create("loop_end"));
        fprintf(context->file, "  br label %s\n", VALUE_REPR(loop_start));
        fprintf(context->file, "%s:\n", VALUE_NAME(loop_start));
        Loop *loop = (Loop *)malloc(sizeof(Loop));
        loop->loop_end = loop_end;
        loop->has_break = FALSE;
        loop->parent = context->loop;
        context->loop = loop;
        emit_statement(context, statement->loop.block);
        context->loop = loop->parent;
        fprintf(context->file, "  br label %s\n", VALUE_REPR(loop_start));
        if (loop->has_break) {
            fprintf(context->file, "%s:\n", VALUE_NAME(loop_end));
        }
        return;
    }
    case STATEMENT_RETURN: {
        IR_Value *result = emit_expression(context, statement->return_expression);
        fprintf(context->file, "  ret %s %s\n", VALUE_TYPE(result), VALUE_REPR(result));
        return;
    }
    case STATEMENT_STRUCT_DECLARATION: {
        String *name = statement->struct_declaration.name->variable.name->lexeme;
        String *repr = string__create("%");
        string__append_string(repr, name);
        IR_Type *type = type__create(IR_TYPE_OPAQUE, name, repr);
        types__append(context->types, type);
        fprintf(context->file, "%s = type opaque\n", type->repr->data);
        return;
    }
    case STATEMENT_VARIABLE_DECLARATION: {
        if (statement->variable_declaration.external == TRUE) {
            IR_Type *variable_type = types__get_by_type(context->types, statement->variable_declaration.type);
            IR_Value *variable = value__create_global_variable(context, variable_type, statement->variable_declaration.name->variable.name->lexeme);
            fprintf(context->file, "%s = external global %s\n", VALUE_REPR(variable), VALUE_TYPE(variable));
        } else {
            IR_Value *value = emit_expression(context, statement->variable_declaration.value);
            IR_Value *variable = value__create_local_variable(context, value->type, statement->variable_declaration.name->variable.name->lexeme);
            values__append(context->allocas, variable);
            fprintf(context->file, "  store i32 %s, i32* %s\n", VALUE_REPR(value), VALUE_REPR(variable));
        }
        return;
    }
    default:
        ERROR(__FILE__, __LINE__, "Unsupported statement type: %d", statement->kind);
        exit(1);
    }
}

void generate(Statement *first_statement) {
    FILE *file = fopen("build/code.ll", "w");

    Context *context = context__create(file);

    types__append(context->types, type__create(IR_TYPE_BOOLEAN, string__create("Bool"), string__create("i1")));
    types__append(context->types, type__create(IR_TYPE_CHARACTER, string__create("Char"), string__create("i8")));
    types__append(context->types, type__create(IR_TYPE_INTEGER, string__create("Int"), string__create("i32")));

    Statement *statement = first_statement;
    while (statement != NULL) {
        emit_statement(context, statement);
        statement = statement->next;
        fprintf(context->file, "\n");
    }

    fclose(context->file);
}
