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
        VALUE_NAMED_VARIABLE,
        VALUE_POINTER,
        VALUE_TEMP_VARIABLE,
    } kind;

    String *name;
    String *repr;

    struct Value *prev;
    struct Value *next;
} Value;

typedef struct Values {
    Value *first;
    Value *last;
    struct Values *parent;
} Values;

typedef struct Loop {
    Value *loop_end;
    int has_break;
    struct Loop *parent;
} Loop;

typedef struct Context {
    FILE *file;
    Values *declarations;
    Loop *loop;
    int temp_variables;
} Context;

Value *value__create(int kind, String *name, String *repr) {
    Value *value = (Value *)malloc(sizeof(Value));
    value->kind = kind;
    value->name = name;
    value->repr = repr;
    value->prev = NULL;
    value->next = NULL;
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
    if (self->first == NULL) {
        self->first = value;
    } else {
        self->last->next = value;
        value->prev = self->last;
    }
    self->last = value;
}

Value *values__find(Values *self, String *name) {
    if (self == NULL) {
        return NULL;
    }
    Value *value = self->last;
    while (value != NULL) {
        if (string__equals(value->name, name->data)) {
            return value;
        }
        value = value->prev;
    }
    return values__find(self->parent, name);
}

Context *context__create(FILE *file) {
    Context *self = (Context *)malloc(sizeof(Context));
    self->file = file;
    self->declarations = values__create();
    self->loop = NULL;
    self->temp_variables = 0;
    return self;
}

Context *context__clone(Context *other) {
    Context *self = (Context *)malloc(sizeof(Context));
    self->file = other->file;
    self->declarations = values__create();
    self->declarations->parent = other->declarations;
    self->loop = NULL;
    self->temp_variables = other->temp_variables;
    return self;
}

Value *value__create_function(Context *context, String *name) {
    String *repr = string__create("@");
    string__append_string(repr, name);
    return value__create(VALUE_FUNCTION, name, repr);
}

Value *value__create_label(Context *context, String *name) {
    string__append_char(name, '.');
    if (context->temp_variables < 100) {
        string__append_char(name, '0');
    }
    if (context->temp_variables < 10) {
        string__append_char(name, '0');
    }
    string__append_int(name, context->temp_variables);
    String *repr = string__create("%");
    string__append_string(repr, name);
    context->temp_variables += 1;
    return value__create(VALUE_LABEL, name, repr);
}

Value *value__create_named_variable(Context *context, String *name) {
    String *repr = string__create("%");
    string__append_string(repr, name);
    return value__create(VALUE_NAMED_VARIABLE, name, repr);
}

Value *value__create_temp_variable(Context *context) {
    String *repr = string__create("%.");
    if (context->temp_variables < 100) {
        string__append_char(repr, '0');
    }
    if (context->temp_variables < 10) {
        string__append_char(repr, '0');
    }
    string__append_int(repr, context->temp_variables);
    context->temp_variables += 1;
    return value__create(VALUE_TEMP_VARIABLE, NULL, repr);
}

#define VALUE(value) value->repr->data

Value *emit_literal(Context *context, Token *token) {
    switch (token->kind) {
        case TOKEN_INTEGER: {
            String *constant = string__append_int(string__create_empty(0), token->integer.value);
            return value__create(VALUE_CONSTANT, NULL, constant);
        }
        default: {
            WARNING(__FILE__, __LINE__, "Unsupported token type: %d", token->kind);
            exit(1);
        }
    }
}

Value *emit_expression(Context *context, Expression *expression) {
    switch (expression->kind) {
    case EXPRESSION_BINARY: {
        Value *destination = value__create_temp_variable(context);
        Value *left_value = emit_expression(context, expression->binary.left_expression);
        if (string__equals(expression->binary.operator_token->lexeme, "+")) {
            Value *right_value = emit_expression(context, expression->binary.right_expression);
            fprintf(context->file, "  %s = add i32 %s, %s\n", VALUE(destination), VALUE(left_value), VALUE(right_value));
        } else if (string__equals(expression->binary.operator_token->lexeme, "-")) {
            Value *right_value = emit_expression(context, expression->binary.right_expression);
            fprintf(context->file, "  %s = sub i32 %s, %s\n", VALUE(destination), VALUE(left_value), VALUE(right_value));
        } else if (string__equals(expression->binary.operator_token->lexeme, "*")) {
            Value *right_value = emit_expression(context, expression->binary.right_expression);
            fprintf(context->file, "  %s = mul i32 %s, %s\n", VALUE(destination), VALUE(left_value), VALUE(right_value));
        } else if (string__equals(expression->binary.operator_token->lexeme, "/")) {
            Value *right_value = emit_expression(context, expression->binary.right_expression);
            fprintf(context->file, "  %s = sdiv i32 %s, %s\n", VALUE(destination), VALUE(left_value), VALUE(right_value));
        } else if (string__equals(expression->binary.operator_token->lexeme, "<")) {
            Value *right_value = emit_expression(context, expression->binary.right_expression);
            fprintf(context->file, "  %s = icmp slt i32 %s, %s\n", VALUE(destination), VALUE(left_value), VALUE(right_value));
        } else if (string__equals(expression->binary.operator_token->lexeme, ">")) {
            Value *right_value = emit_expression(context, expression->binary.right_expression);
            fprintf(context->file, "  %s = icmp sgt i32 %s, %s\n", VALUE(destination), VALUE(left_value), VALUE(right_value));
        } else if (string__equals(expression->binary.operator_token->lexeme, "==")) {
            Value *right_value = emit_expression(context, expression->binary.right_expression);
            fprintf(context->file, "  %s = icmp eq i32 %s, %s\n", VALUE(destination), VALUE(left_value), VALUE(right_value));
        } else if (string__equals(expression->binary.operator_token->lexeme, "&&")) {
            Value *and_true_label = value__create_label(context, string__create("and_true"));
            Value *and_false_label = value__create_label(context, string__create("and_false"));
            Value *and_result_label = value__create_label(context, string__create("and_result"));
            fprintf(context->file, "  br i1 %s, label %s, label %s\n", VALUE(left_value), VALUE(and_true_label), VALUE(and_false_label));
            fprintf(context->file, "%s:\n", and_true_label->name->data);
            Value *right_value = emit_expression(context, expression->binary.right_expression);
            fprintf(context->file, "  br label %s\n", VALUE(and_result_label));
            fprintf(context->file, "%s:\n", and_false_label->name->data);
            fprintf(context->file, "  br label %s\n", VALUE(and_result_label));
            fprintf(context->file, "%s:\n", and_result_label->name->data);
            fprintf(context->file, "  %s = phi i1 [ %s, %s ], [ 0, %s ]\n", VALUE(destination), VALUE(right_value), VALUE(and_true_label), VALUE(and_false_label));
        } else if (string__equals(expression->binary.operator_token->lexeme, "||")) {
            Value *or_true_label = value__create_label(context, string__create("or_true"));
            Value *or_false_label = value__create_label(context, string__create("or_false"));
            Value *or_result_label = value__create_label(context, string__create("or_result"));
            fprintf(context->file, "  br i1 %s, label %s, label %s\n", VALUE(left_value), VALUE(or_true_label), VALUE(or_false_label));
            fprintf(context->file, "%s:\n", or_true_label->name->data);
            fprintf(context->file, "  br label %s\n", VALUE(or_result_label));
            fprintf(context->file, "%s:\n", or_false_label->name->data);
            Value *right_value = emit_expression(context, expression->binary.right_expression);
            fprintf(context->file, "  br label %s\n", VALUE(or_result_label));
            fprintf(context->file, "%s:\n", or_result_label->name->data);
            fprintf(context->file, "  %s = phi i1 [ %s, %s ], [ 1, %s ]\n", VALUE(destination), VALUE(right_value), VALUE(or_false_label), VALUE(or_true_label));
        } else {
            ERROR(__FILE__, __LINE__, "Unsupported binary expression operator: %s", expression->binary.operator_token->lexeme->data);
            exit(1);
        }
        return destination;
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
        Value *destination = value__create_temp_variable(context);
        fprintf(context->file, "  %s = call i32 %s(", VALUE(destination), VALUE(function));
        Value *function_argument = function_arguments->first;
        while (function_argument != NULL) {
            fprintf(context->file, "i32 %s", VALUE(function_argument));
            function_argument = function_argument->next;
            if (function_argument != NULL) {
                fprintf(context->file, ", ");
            }
        }
        fprintf(context->file, ")\n");
        return destination;
    }
    case EXPRESSION_LITERAL: {
        return emit_literal(context, expression->literal.value);
    }
    case EXPRESSION_VARIABLE: {
        String *variable_name = expression->variable.name->lexeme;
        Value *variable = values__find(context->declarations, variable_name);
        if (variable == NULL) {
            ERROR(__FILE__, __LINE__, "Undefined variable: %s", variable_name->data);
            exit(1);
        }
        if (variable->kind == VALUE_POINTER) {
            Value *result = value__create_temp_variable(context);
            fprintf(context->file, "  %s = load i32, i32* %s\n", VALUE(result), VALUE(variable));
            return result;
        } else {
            return variable;
        }
        break;
    }
    default:
        ERROR(__FILE__, __LINE__, "Unsupported expression type: %d", expression->kind);
        exit(1);
    }
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
        Value *value = emit_expression(context, statement->variable_declaration.value);
        fprintf(context->file, "  store i32 %s, i32* %s\n", VALUE(value), VALUE(variable));
        break;
    }
    case STATEMENT_BLOCK: {
        Statement *block_statement = statement->block.first_statement;
        while (block_statement != NULL) {
            emit_statement(context, block_statement);
            block_statement = block_statement->next;
        }
        break;
    }
    case STATEMENT_BREAK: {
        fprintf(context->file, "  br label %s\n", VALUE(context->loop->loop_end));
        context->loop->has_break = TRUE;
        break;
    }
    case STATEMENT_EXPRESSION: {
        emit_expression(context, statement->expression);
        break;
    }
    case STATEMENT_IF: {
        Value *if_cond = emit_expression(context, statement->if_.condition);
        Value *if_true = value__create_label(context, string__create("if_true"));
        Value *if_false = value__create_label(context, string__create("if_false"));
        Value *if_end = value__create_label(context, string__create("if_end"));
        fprintf(context->file, "  br i1 %s, label %s, label %s\n", VALUE(if_cond), VALUE(if_true), statement->if_.false_block != NULL ? VALUE(if_false) : VALUE(if_end));

        fprintf(context->file, "%s:\n", if_true->name->data);
        emit_statement(context, statement->if_.true_block);
        fprintf(context->file, "  br label %s\n", VALUE(if_end));

        if (statement->if_.false_block != NULL) {
            fprintf(context->file, "%s:\n", if_false->name->data);
            emit_statement(context, statement->if_.false_block);
            fprintf(context->file, "  br label %s\n", VALUE(if_end));
        }

        fprintf(context->file, "%s:\n", if_end->name->data);
        break;
    }
    case STATEMENT_LOOP: {
        Value *loop_start = value__create_label(context, string__create("loop_start"));
        Value *loop_end = value__create_label(context, string__create("loop_end"));
        fprintf(context->file, "  br label %s\n", VALUE(loop_start));
        fprintf(context->file, "%s:\n", loop_start->name->data);
        Loop *loop = (Loop *)malloc(sizeof(Loop));
        loop->loop_end = loop_end;
        loop->has_break = FALSE;
        loop->parent = context->loop;
        context->loop = loop;
        emit_statement(context, statement->loop.block);
        context->loop = loop->parent;
        fprintf(context->file, "  br label %s\n", VALUE(loop_start));
        if (loop->has_break) {
            fprintf(context->file, "%s:\n", loop_end->name->data);
        }
        break;
    }
    case STATEMENT_PROCEDURE_DEFINITION: {
        Value *function = value__create_function(context, statement->procedure_definition.name->literal.value->lexeme);
        values__append(context->declarations, function);
        
        Context *function_context = context__clone(context);

        fprintf(context->file, "define i32 %s(", VALUE(function));
        Member *parameter = statement->procedure_definition.first_parameter;
        while (parameter != NULL) {
            Value *parameter_value = value__create_named_variable(function_context, parameter->name->lexeme);
            values__append(context->declarations, parameter_value);
            fprintf(context->file, "i32 %s", VALUE(parameter_value));
            parameter = parameter->next;
            if (parameter != NULL) {
                fprintf(context->file, ", ");
            }
        }
        fprintf(context->file, ") {\n");

        Statement *body_statement = statement->procedure_definition.first_statement;
        while (body_statement != NULL) {
            emit_statement(function_context, body_statement);
            body_statement = body_statement->next;
        }

        fprintf(context->file, "}\n");

        break;
    }
    case STATEMENT_RETURN: {
        Value *result = emit_expression(context, statement->return_expression);
        fprintf(context->file, "  ret i32 %s\n", VALUE(result));
        break;
    }
    case STATEMENT_VARIABLE_DECLARATION: {
        Value *variable = value__create_named_variable(context, statement->variable_declaration.name->variable.name->lexeme);
        variable->kind = VALUE_POINTER;
        values__append(context->declarations, variable);
        fprintf(context->file, "  %s = alloca i32\n", VALUE(variable));
        Value *value = emit_expression(context, statement->variable_declaration.value);
        fprintf(context->file, "  store i32 %s, i32* %s\n", VALUE(value), VALUE(variable));
        break;
    }
    default:
        WARNING(__FILE__, __LINE__, "Unsupported statement type: %d", statement->kind);
        break;
    }
}

void generate(Statement *first_statement) {
    FILE *file = fopen("build/code.ll", "w");

    Context *context = context__create(file);

    Statement *statement = first_statement;
    while (statement != NULL) {
        emit_statement(context, statement);
        statement = statement->next;
    }

    fclose(context->file);
}
