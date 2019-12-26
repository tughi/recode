#include "Generator.h"
#include "Logging.h"

#include <stdlib.h>

#define FALSE 0
#define TRUE 1

typedef struct Local {
    String *name;
    int name_suffix;
    String *unique_name;
    int is_pointer;
} Local;

typedef struct LocalListItem {
    Local *local;
    struct LocalListItem *next;
} LocalListItem;


typedef struct LocalList {
    LocalListItem *first_item;
    LocalListItem *last_item;
} LocalList;

LocalList *local_list__create() {
    LocalList *self = (LocalList *)malloc(sizeof(LocalList));
    self->first_item = NULL;
    self->last_item = NULL;
    return self;
}

LocalListItem *append(LocalList *list, Local *local) {
    LocalListItem *item = (LocalListItem *)malloc(sizeof(LocalListItem));
    item->local = local;
    item->next = NULL;
    if (list->first_item == NULL) {
        list->first_item = item;
    } else {
        list->last_item->next = item;
    }
    list->last_item = item;
    return item;
}

typedef struct Loop {
    Local *loop_end;
    int has_break;
    struct Loop *parent;
} Loop;

typedef struct Context {
    FILE *file;
    LocalList *locals;
    Loop *loop;
} Context;

Context *clone(Context *context) {
    Context *new_context = (Context *)malloc(sizeof(Context));
    new_context->file = context->file;
    new_context->locals = local_list__create();
    new_context->loop = NULL;

    LocalListItem *locals_item = context->locals->first_item;
    while (locals_item != NULL) {
        append(new_context->locals, locals_item->local);
        locals_item = locals_item->next;
    }
    return new_context;
}

Local *create_suffixed_local(Context *context, String *name, int name_suffix) {
    int retry;
    do {
        retry = FALSE;
        LocalListItem *local_item = context->locals->first_item;
        while (local_item != NULL) {
            if (local_item->local->name_suffix == name_suffix && string__equals(local_item->local->name, name->data)) {
                name_suffix += 1;
                retry = TRUE;
                break;
            }
            local_item = local_item->next;
        }
    } while (retry);

    String *unique_name = string__create(name->data);
    if (name_suffix != -1) {
        string__append_char(unique_name, '.');
        if (name_suffix < 100) {
            string__append_char(unique_name, '0');
        }
        if (name_suffix < 10) {
            string__append_char(unique_name, '0');
        }
        if (name_suffix == 0) {
            string__append_char(unique_name, '0');
        }
    }
    if (name_suffix >= 0) {
        string__append_int(unique_name, name_suffix);
    }

    Local *local = (Local *)malloc(sizeof(Local));
    local->name = name;
    local->name_suffix = name_suffix,
    local->unique_name = unique_name;
    local->is_pointer = FALSE;

    append(context->locals, local);

    return local;
}

Local *create_local(Context *context, String *name) {
    return create_suffixed_local(context, name, -1);
}

Local *create_temp_local(Context *context) {
    String *name = string__create_empty(1);
    return create_suffixed_local(context, name, 0);
}

Local *get_local(Context *context, String *name) {
    LocalListItem *list_item = context->locals->first_item;
    while (list_item != NULL && !string__equals(list_item->local->name, name->data)) {
        list_item = list_item->next;
    }
    return list_item != NULL ? list_item->local : NULL;
}

#define LOCAL(local) local->unique_name->data

Local *emit_literal(Context *context, Local *destination, Token *token) {
    switch (token->kind) {
    case INTEGER:
        fprintf(context->file, "  %%%s = add i32 %d, 0\n", LOCAL(destination), token->integer.value);
        break;
    default:
        WARNING(__FILE__, __LINE__, "Unsupported token type: %d", token->kind);
        break;
    }
    return destination;
}

Local *emit_expression(Context *context, Local *destination, Expression *expression) {
    switch (expression->kind) {
    case BINARY: {
        Local *left_local = emit_expression(context, create_temp_local(context), expression->binary.left_expression);
        Local *right_local = emit_expression(context, create_temp_local(context), expression->binary.right_expression);
        String *operation = NULL;
        if (string__equals(expression->binary.operator_token->lexeme, "+")) {
            fprintf(context->file, "  %%%s = add i32 %%%s, %%%s\n", LOCAL(destination), LOCAL(left_local), LOCAL(right_local));
        } else if (string__equals(expression->binary.operator_token->lexeme, "-")) {
            fprintf(context->file, "  %%%s = sub i32 %%%s, %%%s\n", LOCAL(destination), LOCAL(left_local), LOCAL(right_local));
        } else if (string__equals(expression->binary.operator_token->lexeme, "*")) {
            fprintf(context->file, "  %%%s = mul i32 %%%s, %%%s\n", LOCAL(destination), LOCAL(left_local), LOCAL(right_local));
        } else if (string__equals(expression->binary.operator_token->lexeme, "/")) {
            fprintf(context->file, "  %%%s = sdiv i32 %%%s, %%%s\n", LOCAL(destination), LOCAL(left_local), LOCAL(right_local));
        } else if (string__equals(expression->binary.operator_token->lexeme, "<")) {
            fprintf(context->file, "  %%%s = icmp slt i32 %%%s, %%%s\n", LOCAL(destination), LOCAL(left_local), LOCAL(right_local));
        } else if (string__equals(expression->binary.operator_token->lexeme, ">")) {
            fprintf(context->file, "  %%%s = icmp sgt i32 %%%s, %%%s\n", LOCAL(destination), LOCAL(left_local), LOCAL(right_local));
        } else if (string__equals(expression->binary.operator_token->lexeme, "==")) {
            fprintf(context->file, "  %%%s = icmp eq i32 %%%s, %%%s\n", LOCAL(destination), LOCAL(left_local), LOCAL(right_local));
        } else {
            ERROR(__FILE__, __LINE__, "Unsupported binary expression operator: %s", expression->binary.operator_token->lexeme->data);
            exit(1);
        }
        break;
    }
    case CALL: {
        Local *procedure = get_local(context, expression->call.callee->variable.name->lexeme);
        if (procedure == NULL) {
            ERROR(__FILE__, __LINE__, "Undefined procedure: %s", expression->call.callee->variable.name->lexeme->data);
            exit(1);
        }
        LocalList *procedure_arguments = local_list__create();
        Argument *argument = expression->call.first_argument;
        while (argument != NULL) {
            Local *procedure_argument = create_temp_local(context);
            append(procedure_arguments, procedure_argument);
            emit_expression(context, procedure_argument, argument->value);
            argument = argument->next;
        }
        fprintf(context->file, "  %%%s = call i32 @%s(", LOCAL(destination), LOCAL(procedure));
        LocalListItem *procedure_arguments_item = procedure_arguments->first_item;
        while (procedure_arguments_item != NULL) {
            fprintf(context->file, "i32 %%%s", LOCAL(procedure_arguments_item->local));
            procedure_arguments_item = procedure_arguments_item->next;
            if (procedure_arguments_item != NULL) {
                fprintf(context->file, ", ");
            }
        }
        fprintf(context->file, ")\n");
        break;
    }
    case LITERAL: {
        emit_literal(context, destination, expression->literal.value);
        break;
    }
    case VARIABLE: {
        Local *variable = get_local(context, expression->variable.name->lexeme);
        if (variable->is_pointer) {
            fprintf(context->file, "  %%%s = load i32, i32* %%%s\n", LOCAL(destination), LOCAL(variable));
        } else {
            fprintf(context->file, "  %%%s = add i32 %%%s, 0\n", LOCAL(destination), LOCAL(variable));
        }
        break;
    }
    default:
        WARNING(__FILE__, __LINE__, "Unsupported expression type: %d", expression->kind);
        break;
    }

    return destination;
}

void emit_statement(Context *context, Statement *statement) {
    switch (statement->kind) {
    case ASSIGNMENT: {
        Local *variable = get_local(context, statement->assignment.destination->variable.name->lexeme);
        Local *value = emit_expression(context, create_temp_local(context), statement->variable_declaration.value);
        fprintf(context->file, "  store i32 %%%s, i32* %%%s\n", LOCAL(value), LOCAL(variable));
        break;
    }
    case BLOCK: {
        Statement *block_statement = statement->block.first_statement;
        while (block_statement != NULL) {
            emit_statement(context, block_statement);
            block_statement = block_statement->next;
        }
        break;
    }
    case BREAK: {
        fprintf(context->file, "  br label %%%s\n", LOCAL(context->loop->loop_end));
        context->loop->has_break = TRUE;
        break;
    }
    case IF: {
        Local *if_cond = emit_expression(context, create_suffixed_local(context, string__create("if_cond"), 0), statement->if_.condition);
        Local *if_true = create_suffixed_local(context, string__create("if_true"), 0);
        Local *if_false = create_suffixed_local(context, string__create("if_false"), 0);
        Local *if_end = create_suffixed_local(context, string__create("if_end"), 0);
        fprintf(context->file, "  br i1 %%%s, label %%%s, label %%%s\n", LOCAL(if_cond), LOCAL(if_true), statement->if_.false_block != NULL ? LOCAL(if_false) : LOCAL(if_end));

        fprintf(context->file, "%s:\n", LOCAL(if_true));
        emit_statement(context, statement->if_.true_block);
        fprintf(context->file, "  br label %%%s\n", LOCAL(if_end));

        if (statement->if_.false_block != NULL) {
            fprintf(context->file, "%s:\n", LOCAL(if_false));
            emit_statement(context, statement->if_.false_block);
            fprintf(context->file, "  br label %%%s\n", LOCAL(if_end));
        }

        fprintf(context->file, "%s:\n", LOCAL(if_end));
        break;
    }
    case LOOP: {
        Local *loop_start = create_suffixed_local(context, string__create("loop_start"), 0);
        Local *loop_end = create_suffixed_local(context, string__create("loop_end"), 0);
        fprintf(context->file, "  br label %%%s\n", LOCAL(loop_start));
        fprintf(context->file, "%s:\n", LOCAL(loop_start));
        Loop *loop = (Loop *)malloc(sizeof(Loop));
        loop->loop_end = loop_end;
        loop->has_break = FALSE;
        loop->parent = context->loop;
        context->loop = loop;
        emit_statement(context, statement->loop.block);
        context->loop = loop->parent;
        fprintf(context->file, "  br label %%%s\n", LOCAL(loop_start));
        if (loop->has_break) {
            fprintf(context->file, "%s:\n", LOCAL(loop_end));
        }
        break;
    }
    case PROCEDURE_DEFINITION: {
        Local *procedure_name = create_local(context, statement->procedure_definition.name->literal.value->lexeme);

        Context *procedure_context = clone(context);

        fprintf(context->file, "define i32 @%s(", LOCAL(procedure_name));
        Member *parameter = statement->procedure_definition.first_parameter;
        while (parameter != NULL) {
            Local *name = create_local(procedure_context, parameter->name->lexeme);
            fprintf(context->file, "i32 %%%s", LOCAL(name));
            parameter = parameter->next;
            if (parameter != NULL) {
                fprintf(context->file, ", ");
            }
        }
        fprintf(context->file, ") {\n");

        Statement *body_statement = statement->procedure_definition.first_statement;
        while (body_statement != NULL) {
            emit_statement(procedure_context, body_statement);
            body_statement = body_statement->next;
        }

        fprintf(context->file, "}\n");

        break;
    }
    case RETURN: {
        Local *result = emit_expression(context, create_temp_local(context), statement->return_expression);
        fprintf(context->file, "  ret i32 %%%s\n", LOCAL(result));
        break;
    }
    case VARIABLE_DECLARATION: {
        Local *variable = create_local(context, statement->variable_declaration.name->variable.name->lexeme);
        variable->is_pointer = TRUE;
        fprintf(context->file, "  %%%s = alloca i32\n", LOCAL(variable));
        Local *value = emit_expression(context, create_temp_local(context), statement->variable_declaration.value);
        fprintf(context->file, "  store i32 %%%s, i32* %%%s\n", LOCAL(value), LOCAL(variable));
        break;
    }
    default:
        fprintf(context->file, "  %%%s = add i1 0, 0\n", LOCAL(create_local(context, string__create("nop"))));
        WARNING(__FILE__, __LINE__, "Unsupported statement type: %d", statement->kind);
        break;
    }
}

void generate(Statement *first_statement) {
    FILE *file = fopen("build/code.ll", "w");

    Context *context = (Context *)malloc(sizeof(Context));
    context->file = file;
    context->locals = local_list__create();
    context->loop = NULL;

    Statement *statement = first_statement;
    while (statement != NULL) {
        emit_statement(context, statement);
        statement = statement->next;
    }

    fclose(context->file);
}
