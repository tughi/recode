#include "Generator.h"
#include "Logging.h"

#include <stdlib.h>

#define FALSE 0
#define TRUE 1

typedef struct Value {
    enum {
        VALUE_CONSTANT,
        VALUE_FUNCTION,
        VALUE_LABEL,
        VALUE_PARAMETER,
        VALUE_POINTER,
        VALUE_TEMP_VARIABLE,
    } kind;

    String *type;
    String *name;
    String *repr;
} Value;

#define VALUE_NAME(value) value->name->data
#define VALUE_REPR(value) value->repr->data
#define VALUE_TYPE(value) value->type->data

typedef struct ValuesItem {
    Value *value;
    struct ValuesItem *prev;
    struct ValuesItem *next;
} ValuesItem;

typedef struct Values {
    ValuesItem *first;
    ValuesItem *last;
    struct Values *parent;
} Values;

typedef struct Loop {
    Value *loop_end;
    int has_break;
    struct Loop *parent;
} Loop;

typedef struct Counter {
    int count;
} Counter;

typedef struct Context {
    FILE *file;
    Values *declarations;
    Values *allocas;
    Loop *loop;
    Counter *temp_variables;
} Context;

Value *value__create(int kind, String *type, String *name, String *repr) {
    Value *value = (Value *)malloc(sizeof(Value));
    value->kind = kind;
    value->type = type;
    value->name = name;
    value->repr = repr;
    return value;
}

Values *values__create() {
    Values *self = (Values *)malloc(sizeof(Values));
    self->first = NULL;
    self->last = NULL;
    self->parent = NULL;
    return self;
}

void values__append(Values *self, Value *value) {
    ValuesItem *item = (ValuesItem *)malloc(sizeof(ValuesItem));
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

Value *values__find(Values *self, String *name) {
    if (self == NULL) {
        return NULL;
    }
    ValuesItem *item = self->last;
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
    self->declarations = values__create();
    self->allocas = values__create();
    self->loop = NULL;
    self->temp_variables = counter__create();
    return self;
}

Context *context__clone(Context *other) {
    Context *self = (Context *)malloc(sizeof(Context));
    self->file = other->file;
    self->declarations = other->declarations;
    self->allocas = other->allocas;
    self->loop = other->loop;
    self->temp_variables = other->temp_variables;
    return self;
}

Value *value__create_function(Context *context, String *type, String *name) {
    String *repr = string__create("@");
    string__append_string(repr, name);
    Value *self = value__create(VALUE_FUNCTION, type, name, repr);
    values__append(context->declarations, self);
    return self;
}

Value *value__create_label(Context *context, String *name) {
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
    return value__create(VALUE_LABEL, NULL, name, repr);
}

Value *value__create_parameter(Context *context, String *type, String *name) {
    String *repr = string__create("%");
    string__append_string(repr, name);
    Value *self = value__create(VALUE_PARAMETER, type, name, repr);
    values__append(context->declarations, self);
    return self;
}

Value *value__create_global_variable(Context *context, String *type, String *name) {
    String *repr = string__create("@");
    string__append_string(repr, name);
    Value *self = value__create(VALUE_POINTER, type, name, repr);
    values__append(context->declarations, self);
    return self;
}

Value *value__create_local_variable(Context *context, String *type, String *name) {
    String *repr = string__create("%");
    string__append_string(repr, name);
    Value *shadowed_variable = values__find(context->declarations, name);
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
    Value *self = value__create(VALUE_POINTER, type, name, repr);
    values__append(context->declarations, self);
    return self;
}

Value *value__create_temp_variable(Context *context, String *type) {
    String *repr = string__create("%.");
    if (counter__get(context->temp_variables) < 100) {
        string__append_char(repr, '0');
    }
    if (counter__get(context->temp_variables) < 10) {
        string__append_char(repr, '0');
    }
    string__append_int(repr, counter__get(context->temp_variables));
    counter__increment(context->temp_variables);
    return value__create(VALUE_TEMP_VARIABLE, type, NULL, repr);
}

Value *emit_literal(Context *context, Token *token) {
    switch (token->kind) {
        case TOKEN_CHARACTER: {
            String *constant = string__append_int(string__create_empty(0), token->character.value);
            return value__create(VALUE_CONSTANT, string__create("i8"), NULL, constant);
        }
        case TOKEN_INTEGER: {
            String *constant = string__append_int(string__create_empty(0), token->integer.value);
            return value__create(VALUE_CONSTANT, string__create("i32"), NULL, constant);
        }
        default: {
            ERROR(__FILE__, __LINE__, "Unsupported token type: %d", token->kind);
            exit(1);
        }
    }
}

Value *emit_expression(Context *context, Expression *expression);

Value *emit_arithmetic_expression(Context *context, Expression *expression, const char *instruction) {
    Value *left_value = emit_expression(context, expression->binary.left_expression);
    Value *right_value = emit_expression(context, expression->binary.right_expression);
    Value *result = value__create_temp_variable(context, left_value->type);
    fprintf(context->file, "  %s = %s %s %s, %s\n", VALUE_REPR(result), instruction, VALUE_TYPE(result), VALUE_REPR(left_value), VALUE_REPR(right_value));
    return result;
}

Value *emit_comparison_expression(Context *context, Expression *expression, const char *icmp_operand) {
    Value *left_value = emit_expression(context, expression->binary.left_expression);
    Value *right_value = emit_expression(context, expression->binary.right_expression);
    Value *result = value__create_temp_variable(context, string__create("i1"));
    fprintf(context->file, "  %s = icmp %s %s %s, %s\n", VALUE_REPR(result), icmp_operand, VALUE_TYPE(left_value), VALUE_REPR(left_value), VALUE_REPR(right_value));
    return result;
}

Value *emit_expression(Context *context, Expression *expression) {
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
            Value *left_value = emit_expression(context, expression->binary.left_expression);
            Value *and_true_label = value__create_label(context, string__create("and_true"));
            Value *and_false_label = value__create_label(context, string__create("and_false"));
            Value *and_result_label = value__create_label(context, string__create("and_result"));
            fprintf(context->file, "  br i1 %s, label %s, label %s\n", VALUE_REPR(left_value), VALUE_REPR(and_true_label), VALUE_REPR(and_false_label));
            fprintf(context->file, "%s:\n", VALUE_NAME(and_true_label));
            Value *right_value = emit_expression(context, expression->binary.right_expression);
            fprintf(context->file, "  br label %s\n", VALUE_REPR(and_result_label));
            fprintf(context->file, "%s:\n", VALUE_NAME(and_false_label));
            fprintf(context->file, "  br label %s\n", VALUE_REPR(and_result_label));
            fprintf(context->file, "%s:\n", VALUE_NAME(and_result_label));
            Value *result = value__create_temp_variable(context, string__create("i1"));
            fprintf(context->file, "  %s = phi i1 [ %s, %s ], [ 0, %s ]\n", VALUE_REPR(result), VALUE_REPR(right_value), VALUE_REPR(and_true_label), VALUE_REPR(and_false_label));
            return result;
        } else if (string__equals(expression->binary.operator_token->lexeme, "||")) {
            Value *left_value = emit_expression(context, expression->binary.left_expression);
            Value *or_true_label = value__create_label(context, string__create("or_true"));
            Value *or_false_label = value__create_label(context, string__create("or_false"));
            Value *or_result_label = value__create_label(context, string__create("or_result"));
            fprintf(context->file, "  br i1 %s, label %s, label %s\n", VALUE_REPR(left_value), VALUE_REPR(or_true_label), VALUE_REPR(or_false_label));
            fprintf(context->file, "%s:\n", VALUE_NAME(or_true_label));
            fprintf(context->file, "  br label %s\n", VALUE_REPR(or_result_label));
            fprintf(context->file, "%s:\n", VALUE_NAME(or_false_label));
            Value *right_value = emit_expression(context, expression->binary.right_expression);
            fprintf(context->file, "  br label %s\n", VALUE_REPR(or_result_label));
            fprintf(context->file, "%s:\n", VALUE_NAME(or_result_label));
            Value *result = value__create_temp_variable(context, string__create("i1"));
            fprintf(context->file, "  %s = phi i1 [ %s, %s ], [ 1, %s ]\n", VALUE_REPR(result), VALUE_REPR(right_value), VALUE_REPR(or_false_label), VALUE_REPR(or_true_label));
            return result;
        } else {
            ERROR(__FILE__, __LINE__, "Unsupported binary expression operator: %s", expression->binary.operator_token->lexeme->data);
            exit(1);
        }
    }
    case EXPRESSION_CALL: {
        String *function_name = expression->call.callee->variable.name->lexeme;
        Value *function = values__find(context->declarations, function_name);
        if (function == NULL) {
            ERROR(__FILE__, __LINE__, "Undefined procedure: %s", function_name->data);
            exit(1);
        }
        Values *function_arguments = values__create();
        Argument *argument = expression->call.first_argument;
        while (argument != NULL) {
            Value *function_argument = emit_expression(context, argument->value);
            values__append(function_arguments, function_argument);
            argument = argument->next;
        }
        Value *destination = value__create_temp_variable(context, string__create("i32"));
        fprintf(context->file, "  %s = call %s %s(", VALUE_REPR(destination), VALUE_TYPE(function), VALUE_REPR(function));
        ValuesItem *function_argument = function_arguments->first;
        while (function_argument != NULL) {
            fprintf(context->file, "%s %s", VALUE_TYPE(function_argument->value), VALUE_REPR(function_argument->value));
            function_argument = function_argument->next;
            if (function_argument != NULL) {
                fprintf(context->file, ", ");
            }
        }
        fprintf(context->file, ")\n");
        return destination;
    }
    case EXPRESSION_CAST: {
        Value *operand = emit_expression(context, expression->cast.expression);
        if (string__equals(expression->cast.type->lexeme, "Int")) {
            Value *result = value__create_temp_variable(context, string__create("i32"));
            fprintf(context->file, "  %s = sext %s %s to %s\n", VALUE_REPR(result), VALUE_TYPE(operand), VALUE_REPR(operand), VALUE_TYPE(result));
            return result;
        } else if (string__equals(expression->cast.type->lexeme, "Char")) {
            Value *result = value__create_temp_variable(context, string__create("i8"));
            fprintf(context->file, "  %s = trunc %s %s to %s\n", VALUE_REPR(result), VALUE_TYPE(operand), VALUE_REPR(operand), VALUE_TYPE(result));
            return result;
        } else {
            ERROR(__FILE__, __LINE__, "Cannot cast to %s", expression->cast.type->lexeme->data);
            exit(1);
        }
    }
    case EXPRESSION_LITERAL: {
        return emit_literal(context, expression->literal.value);
    }
    case EXPRESSION_UNARY: {
        if (string__equals(expression->unary.operator_token->lexeme, "-")) {
            Value *right_value = emit_expression(context, expression->unary.expression);
            Value *result = value__create_temp_variable(context, right_value->type);
            fprintf(context->file, "  %s = sub %s 0, %s\n", VALUE_REPR(result), VALUE_TYPE(result), VALUE_REPR(right_value));
            return result;
        } else {
            ERROR(__FILE__, __LINE__, "Unsupported unary expression operator: %s", expression->unary.operator_token->lexeme->data);
            exit(1);
        }
    }
    case EXPRESSION_VARIABLE: {
        String *variable_name = expression->variable.name->lexeme;
        Value *variable = values__find(context->declarations, variable_name);
        if (variable == NULL) {
            ERROR(__FILE__, __LINE__, "Undefined variable: %s", variable_name->data);
            exit(1);
        }
        if (variable->kind == VALUE_POINTER) {
            Value *result = value__create_temp_variable(context, variable->type);
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
        Value *variable = values__find(context->declarations, variable_name);
        if (variable == NULL) {
            ERROR(__FILE__, __LINE__, "Undefined variable: %s", variable_name->data);
            exit(1);
        }
        Value *value;
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
    case STATEMENT_IF: {
        Value *if_cond = emit_expression(context, statement->if_.condition);
        Value *if_true = value__create_label(context, string__create("if_true"));
        Value *if_false = value__create_label(context, string__create("if_false"));
        Value *if_end = value__create_label(context, string__create("if_end"));
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
        Value *loop_start = value__create_label(context, string__create("loop_start"));
        Value *loop_end = value__create_label(context, string__create("loop_end"));
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
    case STATEMENT_PROCEDURE_DEFINITION: {
        Value *function = value__create_function(context, string__create("i32"), statement->procedure_definition.name->literal.value->lexeme);
        
        context = create_function_context(context);

        fprintf(context->file, "define i32 %s(", VALUE_REPR(function));
        Member *parameter = statement->procedure_definition.first_parameter;
        while (parameter != NULL) {
            String *parameter_type;
            if (string__equals(parameter->type->simple.name->lexeme, "Int")) {
                parameter_type = string__create("i32");
            } else if (string__equals(parameter->type->simple.name->lexeme, "Char")) {
                parameter_type = string__create("i8");
            } else {
                ERROR(__FILE__, __LINE__, "Unsupported type: %s", parameter->type->simple.name->lexeme->data);
                exit(1);
            }
            Value *parameter_value = value__create_parameter(context, parameter_type, parameter->name->lexeme);
            fprintf(context->file, "%s %s", VALUE_TYPE(parameter_value), VALUE_REPR(parameter_value));
            parameter = parameter->next;
            if (parameter != NULL) {
                fprintf(context->file, ", ");
            }
        }
        fprintf(context->file, ") {\n");

        Value *entry_label = value__create_label(context, string__create("entry"));
        Value *variables_label = value__create_label(context, string__create("variables"));
        fprintf(context->file, "  br label %s\n", VALUE_REPR(variables_label));
        fprintf(context->file, "%s:\n", VALUE_NAME(entry_label));

        Statement *body_statement = statement->procedure_definition.first_statement;
        while (body_statement != NULL) {
            emit_statement(context, body_statement);
            body_statement = body_statement->next;
        }

        fprintf(context->file, "%s:\n", VALUE_NAME(variables_label));
        ValuesItem *alloca_item = context->allocas->first;
        while (alloca_item != NULL) {
            fprintf(context->file, "  %s = alloca i32\n", VALUE_REPR(alloca_item->value));
            alloca_item = alloca_item->next;
        }
        fprintf(context->file, "  br label %s\n", VALUE_REPR(entry_label));

        fprintf(context->file, "}\n\n");

        return;
    }
    case STATEMENT_RETURN: {
        Value *result = emit_expression(context, statement->return_expression);
        fprintf(context->file, "  ret %s %s\n", VALUE_TYPE(result), VALUE_REPR(result));
        return;
    }
    case STATEMENT_VARIABLE_DECLARATION: {
        Value *value = emit_expression(context, statement->variable_declaration.value);
        Value *variable = value__create_local_variable(context, string__create("i32"), statement->variable_declaration.name->variable.name->lexeme);
        values__append(context->allocas, variable);
        fprintf(context->file, "  store i32 %s, i32* %s\n", VALUE_REPR(value), VALUE_REPR(variable));
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

    fprintf(context->file, "%%libc.File = type opaque\n");
    fprintf(context->file, "\n");

    fprintf(context->file, "@stderr = external global %%libc.File*\n");
    value__create_global_variable(context, string__create("%libc.File*"), string__create("stderr"));
    fprintf(context->file, "@stdin = external global %%libc.File*\n");
    value__create_global_variable(context, string__create("%libc.File*"), string__create("stdin"));
    fprintf(context->file, "@stdout = external global %%libc.File*\n");
    value__create_global_variable(context, string__create("%libc.File*"), string__create("stdout"));
    fprintf(context->file, "\n");

    fprintf(context->file, "declare i32 @fputc(i32, %%libc.File*)\n");
    values__append(context->declarations, value__create_function(context, string__create("i32"), string__create("fputc")));
    fprintf(context->file, "\n");

    Statement *statement = first_statement;
    while (statement != NULL) {
        emit_statement(context, statement);
        statement = statement->next;
    }

    fclose(context->file);
}
