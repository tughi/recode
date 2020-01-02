#include "Generator.h"

#include "Logging.h"
#include "Parser.h"

#include <stdlib.h>

#define FALSE 0
#define TRUE 1

typedef struct IR_Type {
    enum {
        IR_TYPE_ARRAY,
        IR_TYPE_BOOLEAN,
        IR_TYPE_CHARACTER,
        IR_TYPE_INTEGER,
        IR_TYPE_OPAQUE,
        IR_TYPE_NOTHING,
        IR_TYPE_POINTER,
        IR_TYPE_STRUCT,
    } kind;

    union {
        struct {
            struct IR_Type *array_item_type;
        };
        struct {
            struct IR_Type *pointed_type;
        };
        struct {
            struct List *struct_members;
        };
    };

    String *name;
    String *repr;
} IR_Type;

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

    union {
        struct List *function_parameters;
    };
} IR_Value;

#define VALUE_NAME(value) value->name->data
#define VALUE_REPR(value) value->repr->data
#define VALUE_TYPE(value) value->type->repr->data

typedef struct Loop {
    IR_Value *loop_end;
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

IR_Type *type__create(int kind, String *name, String *repr) {
    IR_Type *self = malloc(sizeof(IR_Type));
    self->kind = kind;
    self->name = name;
    self->repr = repr;
    return self;
}

IR_Type *type__create_array(IR_Type *item_type) {
    String *name = string__create("[");
    string__append_string(name, item_type->name);
    string__append_char(name, ']');
    String *repr = string__create("{ ");
    string__append_string(repr, item_type->repr);
    string__append_string(repr, string__create("*, i32 }"));
    IR_Type *self = type__create(IR_TYPE_ARRAY, name, repr);
    self->array_item_type = item_type;
    return self;
}

IR_Type *type__create_pointer(IR_Type *type) {
    String *name = string__create("@");
    string__append_string(name, type->name);
    String *repr = string__create(type->repr->data);
    string__append_char(repr, '*');
    IR_Type *self = type__create(IR_TYPE_POINTER, name, repr);
    self->pointed_type = type;
    return self;
}

IR_Value *value__create(int kind, IR_Type *type, String *name, String *repr) {
    IR_Value *value = malloc(sizeof(IR_Value));
    value->kind = kind;
    value->type = type;
    value->name = name;
    value->repr = repr;
    return value;
}

Counter *counter__create() {
    Counter *self = malloc(sizeof(Counter));
    self->count = 0;
    return self;
}

Counter *counter__clone(Counter *other) {
    Counter *self = malloc(sizeof(Counter));
    self->count = other->count;
    return self;
}

String *counter__get(Counter *self) {
    int value = self->count++;
    String *result = string__create("");
    if (value < 100) {
        string__append_char(result, '0');
    }
    if (value < 10) {
        string__append_char(result, '0');
    }
    string__append_int(result, value);
    return result;
}

Context *context__create(FILE *file) {
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

Context *context__clone(Context *other) {
    Context *self = malloc(sizeof(Context));
    self->global_context = other->global_context;
    self->parent_context = other->parent_context;
    self->file = other->file;
    self->types = other->types;
    self->locals = other->locals;
    self->allocas = other->allocas;
    self->constants = other->constants;
    self->loop = other->loop;
    self->temp_variables = other->temp_variables;
    return self;
}

IR_Type *context__find_type(Context *self, String *name) {
    for (List_Iterator types = list__create_iterator(self->types); list_iterator__has_next(&types); ) {
        IR_Type *type = list_iterator__next(&types);
        if (string__equals(type->name, name->data)) {
            return type;
        }
    }
    WARNING(__FILE__, __LINE__, "No such type: %s", name->data);
    return NULL;
}

IR_Type *context__make_type(Context *self, Type *type) {
    switch (type->kind) {
    case TYPE_ARRAY:
        return type__create_array(context__make_type(self, type->array.item_type));
    case TYPE_POINTER:
        return type__create_pointer(context__make_type(self, type->pointer.type));
    case TYPE_SIMPLE:
        return context__find_type(self, type->simple.name->lexeme);
    default:
        PANIC(__FILE__, __LINE__, "Unsupported type: %d", type->kind);
    }
}

IR_Value *context__find_local(Context *self, String *name) {
    if (self == NULL) {
        return NULL;
    }
    for (List_Iterator iterator = list__create_reversed_iterator(self->locals); list_iterator__has_next(&iterator); ) {
        IR_Value *value = list_iterator__next(&iterator);
        if (string__equals(value->name, name->data)) {
            return value;
        }
    }
    return context__find_local(self->parent_context, name);
}

IR_Value *context__create_function(Context *self, IR_Type *type, String *name) {
    String *repr = string__create("@");
    string__append_string(repr, name);
    IR_Value *value = value__create(IR_VALUE_FUNCTION, type, name, repr);
    value->function_parameters = list__create();
    list__append(self->global_context->locals, value);
    return value;
}

IR_Value *value__create_label(Context *context, String *name) {
    string__append_char(name, '.');
    string__append_string(name, counter__get(context->temp_variables));
    String *repr = string__create("%");
    string__append_string(repr, name);
    return value__create(IR_VALUE_LABEL, NULL, name, repr);
}

IR_Value *context__create_parameter(Context *self, IR_Type *type, String *name) {
    String *repr = string__create("%");
    string__append_string(repr, name);
    IR_Value *value = value__create(IR_VALUE_PARAMETER, type, name, repr);
    list__append(self->locals, value);
    return value;
}

IR_Value *context__create_global_variable(Context *self, IR_Type *type, String *name) {
    String *repr = string__create("@");
    string__append_string(repr, name);
    IR_Value *value = value__create(IR_VALUE_POINTER, type, name, repr);
    list__append(self->global_context->locals, value);
    return value;
}

IR_Value *context__create_local_variable(Context *self, IR_Type *type, String *name) {
    String *repr = string__create("%");
    string__append_string(repr, name);
    if (context__find_local(self, name) != NULL) {
        string__append_char(repr, '.');
        string__append_string(repr, counter__get(self->temp_variables));
    }
    IR_Value *value = value__create(IR_VALUE_POINTER, type, name, repr);
    list__append(self->locals, value);
    return value;
}

IR_Value *value__create_temp_variable(Context *context, IR_Type *type) {
    String *repr = string__create("%.");
    string__append_string(repr, counter__get(context->temp_variables));
    return value__create(IR_VALUE_TEMP_VARIABLE, type, NULL, repr);
}

void string__append_byte(String *self, char value) {
    string__append_char(self, ((value >> 4) & 0xf) % 16 + (((value >> 4) & 0xf) < 10 ? '0' : 'A' - 10));
    string__append_char(self, (value & 0xf) % 16 + ((value & 0xf) < 10 ? '0' : 'A' - 10));
}

IR_Value *emit_literal(Context *context, Token *token) {
    switch (token->kind) {
        case TOKEN_CHARACTER: {
            IR_Type *type = context__find_type(context, string__create("Char"));
            String *repr = string__append_int(string__create_empty(0), token->character.value);
            return value__create(IR_VALUE_CONSTANT, type, NULL, repr);
        }
        case TOKEN_INTEGER: {
            IR_Type *type = context__find_type(context, string__create("Int"));
            String *repr = string__append_int(string__create_empty(0), token->integer.value);
            return value__create(IR_VALUE_CONSTANT, type, NULL, repr);
        }
        case TOKEN_STRING: {
            IR_Type *type = type__create_pointer(context__find_type(context, string__create("Char")));
            IR_Value *value = value__create_temp_variable(context, type);

            String *constant = string__create("@.string.");
            string__append_string(constant, counter__get(context->global_context->temp_variables));
            String *constant_name = string__create(constant->data);
            string__append_string(constant, string__create(" = private constant ["));
            string__append_int(constant, token->string.value->length + 1);
            string__append_string(constant, string__create(" x i8] c\""));
            for (int i = 0; i < token->string.value->length; i++) {
                char c = token->string.value->data[i];
                if (c > 31 && c < 127) {
                    string__append_char(constant, c);
                } else {
                    string__append_char(constant, '\\');
                    string__append_byte(constant, c);
                }
            }
            string__append_string(constant, string__create("\\00\""));
            list__append(context->global_context->constants, constant);

            fprintf(context->file, "  %s = getelementptr [%d x i8], [%d x i8]* %s, i64 0, i64 0\n", VALUE_REPR(value), token->string.value->length + 1, token->string.value->length + 1, constant_name->data);
            return value;
        }
        default: {
            PANIC(__FILE__, __LINE__, "Unsupported token type: %d", token->kind);
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
    IR_Value *result = value__create_temp_variable(context, context__find_type(context, string__create("Bool")));
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
            IR_Value *result = value__create_temp_variable(context, context__find_type(context, string__create("Bool")));
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
            IR_Value *result = value__create_temp_variable(context, context__find_type(context, string__create("Bool")));
            fprintf(context->file, "  %s = phi i1 [ %s, %s ], [ 1, %s ]\n", VALUE_REPR(result), VALUE_REPR(right_value), VALUE_REPR(or_false_label), VALUE_REPR(or_true_label));
            return result;
        } else {
            PANIC(__FILE__, __LINE__, "Unsupported binary expression operator: %s", expression->binary.operator_token->lexeme->data);
        }
    }
    case EXPRESSION_CALL: {
        String *function_name = expression->call.callee->variable.name->lexeme;
        IR_Value *function = context__find_local(context, function_name);
        if (function == NULL) {
            PANIC(__FILE__, __LINE__, "Undefined function: %s", function_name->data);
        }
        List *function_arguments = list__create();
        for (List_Iterator arguments = list__create_iterator(expression->call.arguments); list_iterator__has_next(&arguments); ) {
            Argument *argument = list_iterator__next(&arguments);
            IR_Value *function_argument = emit_expression(context, argument->value);
            list__append(function_arguments, function_argument);
        }
        IR_Value *result;
        if (function->type->kind == IR_TYPE_NOTHING) {
            result = NULL;
            fprintf(context->file, "  call %s %s(", VALUE_TYPE(function), VALUE_REPR(function));
        } else {
            result = value__create_temp_variable(context, function->type);
            fprintf(context->file, "  %s = call %s %s(", VALUE_REPR(result), VALUE_TYPE(function), VALUE_REPR(function));
        }
        for (List_Iterator iterator = list__create_iterator(function_arguments); list_iterator__has_next(&iterator); ) {
            IR_Value *function_argument = list_iterator__next(&iterator);
            fprintf(context->file, "%s %s", VALUE_TYPE(function_argument), VALUE_REPR(function_argument));
            if (list_iterator__has_next(&iterator)) {
                fprintf(context->file, ", ");
            }
        }
        fprintf(context->file, ")\n");
        return result;
    }
    case EXPRESSION_CAST: {
        IR_Value *operand = emit_expression(context, expression->cast.expression);
        IR_Type *type = context__make_type(context, expression->cast.type);
        if (string__equals(type->name, "Int")) {
            IR_Value *result = value__create_temp_variable(context, type);
            fprintf(context->file, "  %s = sext %s %s to %s\n", VALUE_REPR(result), VALUE_TYPE(operand), VALUE_REPR(operand), VALUE_TYPE(result));
            return result;
        } else if (string__equals(type->name, "Char")) {
            IR_Value *result = value__create_temp_variable(context, type);
            fprintf(context->file, "  %s = trunc %s %s to %s\n", VALUE_REPR(result), VALUE_TYPE(operand), VALUE_REPR(operand), VALUE_TYPE(result));
            return result;
        } else {
            PANIC(__FILE__, __LINE__, "Cannot cast to %s", type->name->data);
        }
    }
    case EXPRESSION_LITERAL: {
        return emit_literal(context, expression->literal.value);
    }
    case EXPRESSION_MEMBER: {
        IR_Value *object = emit_expression(context, expression->member.object);
        if (object->type->kind == IR_TYPE_POINTER) {
            IR_Type *pointed_type = object->type->pointed_type;
            if (pointed_type->kind == IR_TYPE_STRUCT) {
                IR_Type *struct_type = pointed_type;
                String *member_name = expression->member.name->lexeme;
                IR_Type *member_type = NULL;
                int member_index = -1;
                int index = -1;
                for (List_Iterator iterator = list__create_iterator(struct_type->struct_members); list_iterator__has_next(&iterator); ) {
                    Member *member = list_iterator__next(&iterator);
                    index += 1;
                    if (string__equals(member_name, member->name->lexeme->data)) {
                        member_type = context__make_type(context, member->type);
                        member_index = index;
                        break;
                    }
                }
                if (member_type == NULL) {
                    PANIC(__FILE__, __LINE__, "No such member: %s.%s", struct_type->name->data, member_name->data);
                }
                IR_Value *member_address = value__create_temp_variable(context, type__create_pointer(member_type));
                fprintf(context->file, "  %s = getelementptr %s, %s %s, i64 0, i32 %d\n", VALUE_REPR(member_address), struct_type->repr->data, VALUE_TYPE(object), VALUE_REPR(object), member_index);
                IR_Value *result = value__create_temp_variable(context, member_type);
                fprintf(context->file, "  %s = load %s, %s %s\n", VALUE_REPR(result), VALUE_TYPE(result), VALUE_TYPE(member_address), VALUE_REPR(member_address));
                return result;
            }
        }
        PANIC(__FILE__, __LINE__, "Unsupported object type: %s", VALUE_TYPE(object));
    }
    case EXPRESSION_UNARY: {
        if (string__equals(expression->unary.operator_token->lexeme, "-")) {
            IR_Value *right_value = emit_expression(context, expression->unary.expression);
            IR_Value *result = value__create_temp_variable(context, right_value->type);
            fprintf(context->file, "  %s = sub %s 0, %s\n", VALUE_REPR(result), VALUE_TYPE(result), VALUE_REPR(right_value));
            return result;
        } else {
            PANIC(__FILE__, __LINE__, "Unsupported unary expression operator: %s", expression->unary.operator_token->lexeme->data);
        }
    }
    case EXPRESSION_VARIABLE: {
        String *variable_name = expression->variable.name->lexeme;
        IR_Value *variable = context__find_local(context, variable_name);
        if (variable == NULL) {
            PANIC(__FILE__, __LINE__, "Undefined variable: %s", variable_name->data);
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
        PANIC(__FILE__, __LINE__, "Unsupported expression type: %d", expression->kind);
    }
}

Context *create_function_context(Context *parent_context) {
    Context *context = context__clone(parent_context);
    context->parent_context = parent_context;
    context->locals = list__create();
    context->allocas = list__create();
    context->temp_variables = counter__create();
    return context;
}

Context *create_block_context(Context *parent_context) {
    Context *context = context__clone(parent_context);
    context->parent_context = parent_context;
    context->locals = list__create();
    return context;
}

void emit_statement(Context *context, Statement *statement) {
    switch (statement->kind) {
    case STATEMENT_ASSIGNMENT: {
        String *variable_name = statement->assignment.destination->variable.name->lexeme;
        IR_Value *variable = context__find_local(context, variable_name);
        if (variable == NULL) {
            PANIC(__FILE__, __LINE__, "Undefined variable: %s", variable_name->data);
        }
        IR_Value *value;
        if (string__equals(statement->assignment.operator_token->lexeme, "=")) {
            value = emit_expression(context, statement->variable_declaration.value);
        } else {
            Expression *binary_expression = malloc(sizeof(Expression));
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
                PANIC(__FILE__, __LINE__, "Unsupported assignment operator: %s", statement->assignment.operator_token->lexeme->data);
            }
        }
        fprintf(context->file, "  store %s %s, %s* %s\n", VALUE_TYPE(value), VALUE_REPR(value), VALUE_TYPE(variable), VALUE_REPR(variable));
        return;
    }
    case STATEMENT_BLOCK: {
        context = create_block_context(context);
        for (List_Iterator iterator = list__create_iterator(statement->block.statements); list_iterator__has_next(&iterator); ) {
            Statement *block_statement = list_iterator__next(&iterator);
            emit_statement(context, block_statement);
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
        IR_Value *function = context__create_function(context, context__make_type(context, statement->function_declaration.return_type), statement->function_definition.name->literal.value->lexeme);
        fprintf(context->file, "declare %s %s(", VALUE_TYPE(function), VALUE_REPR(function));
        for (List_Iterator parameters = list__create_iterator(statement->function_definition.parameters); list_iterator__has_next(&parameters); ) {
            Parameter *parameter = list_iterator__next(&parameters);
            IR_Type *parameter_type = context__make_type(context, parameter->type);
            IR_Value *parameter_value = context__create_parameter(context, parameter_type, parameter->name->lexeme);
            list__append(function->function_parameters, parameter_value);
            fprintf(context->file, "%s %s", VALUE_TYPE(parameter_value), VALUE_REPR(parameter_value));
            if (list_iterator__has_next(&parameters)) {
                fprintf(context->file, ", ");
            }
        }
        fprintf(context->file, ")\n");
        return;
    }
    case STATEMENT_FUNCTION_DEFINITION: {
        IR_Value *function = context__create_function(context, context__make_type(context, statement->function_definition.return_type), statement->function_definition.name->literal.value->lexeme);
        
        context = create_function_context(context);
        fprintf(context->file, "define %s %s(", VALUE_TYPE(function), VALUE_REPR(function));
        for (List_Iterator parameters = list__create_iterator(statement->function_definition.parameters); list_iterator__has_next(&parameters); ) {
            Parameter *parameter = list_iterator__next(&parameters);
            IR_Type *parameter_type = context__make_type(context, parameter->type);
            IR_Value *parameter_value = context__create_parameter(context, parameter_type, parameter->name->lexeme);
            list__append(function->function_parameters, parameter_value);
            fprintf(context->file, "%s %s", VALUE_TYPE(parameter_value), VALUE_REPR(parameter_value));
            if (list_iterator__has_next(&parameters)) {
                fprintf(context->file, ", ");
            }
        }
        fprintf(context->file, ") {\n");

        IR_Value *entry_label = value__create_label(context, string__create("entry"));
        IR_Value *variables_label = value__create_label(context, string__create("variables"));
        fprintf(context->file, "  br label %s\n", VALUE_REPR(variables_label));
        fprintf(context->file, "%s:\n", VALUE_NAME(entry_label));

        for (List_Iterator iterator = list__create_iterator(statement->function_definition.statements); list_iterator__has_next(&iterator); ) {
            Statement *body_statement = list_iterator__next(&iterator);
            emit_statement(context, body_statement);
        }

        fprintf(context->file, "%s:\n", VALUE_NAME(variables_label));
        for (List_Iterator iterator = list__create_iterator(context->allocas); list_iterator__has_next(&iterator); ) {
            IR_Value *alloca = list_iterator__next(&iterator);
            fprintf(context->file, "  %s = alloca %s\n", VALUE_REPR(alloca), VALUE_TYPE(alloca));
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
        Loop *loop = malloc(sizeof(Loop));
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
        if (statement->return_expression != NULL) {
            IR_Value *result = emit_expression(context, statement->return_expression);
            fprintf(context->file, "  ret %s %s\n", VALUE_TYPE(result), VALUE_REPR(result));
        } else {
            fprintf(context->file, "  ret void\n");
        }
        return;
    }
    case STATEMENT_STRUCT_DECLARATION: {
        String *name = statement->struct_declaration.name->variable.name->lexeme;
        String *repr = string__create("%");
        string__append_string(repr, name);
        IR_Type *type = type__create(IR_TYPE_OPAQUE, name, repr);
        list__append(context->types, type);
        fprintf(context->file, "%s = type opaque\n", type->repr->data);
        return;
    }
    case STATEMENT_STRUCT_DEFINITION: {
        String *name = statement->struct_definition.name->variable.name->lexeme;
        String *repr = string__create("%");
        string__append_string(repr, name);
        IR_Type *type = type__create(IR_TYPE_STRUCT, name, repr);
        type->struct_members = statement->struct_definition.members;
        list__append(context->types, type);
        fprintf(context->file, "%s = type { ", type->repr->data);
        for (List_Iterator iterator = list__create_iterator(statement->struct_definition.members); list_iterator__has_next(&iterator); ) {
            Member *member = list_iterator__next(&iterator);
            fprintf(context->file, "%s", context__make_type(context, member->type)->repr->data);
            if (list_iterator__has_next(&iterator)) {
                fprintf(context->file, ", ");
            }
        }
        fprintf(context->file, " }\n");
        return;
    }
    case STATEMENT_VARIABLE_DECLARATION: {
        if (statement->variable_declaration.external == TRUE) {
            IR_Type *variable_type = context__make_type(context, statement->variable_declaration.type);
            IR_Value *variable = context__create_global_variable(context, variable_type, statement->variable_declaration.name->variable.name->lexeme);
            fprintf(context->file, "%s = external global %s\n", VALUE_REPR(variable), VALUE_TYPE(variable));
        } else {
            IR_Value *value = emit_expression(context, statement->variable_declaration.value);
            IR_Value *variable = context__create_local_variable(context, value->type, statement->variable_declaration.name->variable.name->lexeme);
            list__append(context->allocas, variable);
            fprintf(context->file, "  store %s %s, %s* %s\n", VALUE_TYPE(value), VALUE_REPR(value), VALUE_TYPE(variable), VALUE_REPR(variable));
        }
        return;
    }
    default:
        PANIC(__FILE__, __LINE__, "Unsupported statement type: %d", statement->kind);
    }
}

void generate(List *statements) {
    FILE *file = fopen("build/code.ll", "w");

    Context *context = context__create(file);

    list__append(context->types, type__create(IR_TYPE_BOOLEAN, string__create("Bool"), string__create("i1")));
    list__append(context->types, type__create(IR_TYPE_CHARACTER, string__create("Char"), string__create("i8")));
    list__append(context->types, type__create(IR_TYPE_INTEGER, string__create("Int"), string__create("i32")));
    list__append(context->types, type__create(IR_TYPE_NOTHING, string__create("Nothing"), string__create("void")));

    for (List_Iterator iterator = list__create_iterator(statements); list_iterator__has_next(&iterator); ) {
        Statement *statement = list_iterator__next(&iterator);
        emit_statement(context, statement);
        fprintf(context->file, "\n");
    }

    for (List_Iterator iterator = list__create_iterator(context->constants); list_iterator__has_next(&iterator); ) {
        String *constant = list_iterator__next(&iterator);
        fprintf(context->file, "%s\n", constant->data);
    }

    fclose(context->file);
}
