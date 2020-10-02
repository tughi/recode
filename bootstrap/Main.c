// Copyright (c) 2020, Stefan Selariu

#include "Generator.h"
#include "Logging.h"
#include "Parser.h"
#include "Scanner.h"

#include <string.h>

char *load_file(String *file_name) {
    FILE *file = fopen(file_name->data, "r");
    if (file == NULL) {
        PANIC(__FILE__, __LINE__, "Couldn't open file: %s", file_name->data);
    }
    String *content = string__create("");
    char buffer[1024];
    while (fgets(buffer, 1024, file) != NULL) {
        string__append_chars(content, buffer, strlen(buffer));
    }
    fclose(file);
    return content->data;
}

void print_token(Token *token) {
    if (token == NULL) {
        printf("%sToken::NULL%s", SGR_ERROR, SGR_RESET);
        return;
    }

    switch (token->kind) {
    case TOKEN__CHARACTER:
        printf("%s%s%s", SGR_GREEN, token->lexeme->data, SGR_RESET);
        return;
    case TOKEN__COMMENT:
        printf("%s%s%s", SGR_DEFAULT, token->lexeme->data, SGR_RESET);
        return;
    case TOKEN__END_OF_FILE:
        printf("%s%s%s\n", SGR_BLACK, token->lexeme->data, SGR_RESET);
        return;
    case TOKEN__END_OF_LINE:
        printf("%s%s%s", SGR_BLACK, token->lexeme->data, SGR_RESET);
        return;
    case TOKEN__ERROR:
        printf("%s%s%s", SGR_ERROR, token->lexeme->data, SGR_RESET);
        return;
    case TOKEN__IDENTIFIER:
        printf("%s%s%s", token->lexeme->data[0] <= 'Z' ? SGR_FAINT_YELLOW : SGR_RESET, token->lexeme->data, SGR_RESET);
        return;
    case TOKEN__INTEGER:
        printf("%s%s%s", SGR_CYAN, token->lexeme->data, SGR_RESET);
        return;
    case TOKEN__KEYWORD:
        printf("%s%s%s", SGR_YELLOW, token->lexeme->data, SGR_RESET);
        return;
    case TOKEN__OTHER:
        printf("%s%s%s", SGR_WHITE_BOLD, token->lexeme->data, SGR_RESET);
        return;
    case TOKEN__SPACE:
        printf("%s%s", SGR_RESET, token->lexeme->data);
        return;
    case TOKEN__STRING:
        printf("%s%s%s", SGR_GREEN, token->lexeme->data, SGR_RESET);
        return;
    default:
        printf("%sToken::%s%s", SGR_ERROR, token__get_kind_name(token), SGR_RESET);
    }
}

void dump_tokens(Token_List *tokens) {
    int line = 0;
    for (List_Iterator iterator = list__create_iterator(tokens); list_iterator__has_next(&iterator);) {
        Token *token = list_iterator__next(&iterator);
        if (token->location->line != line) {
            if (line > 0) {
                printf("\n");
            }
            line = token->location->line;
            printf("%03d: ", line);
        }
        print_token(token);
    }
}

void print_type(Type *type) {
    if (type == NULL) {
        printf("%sType::NULL%s", SGR_ERROR, SGR_RESET);
        return;
    }

    switch (type->kind) {
    case TYPE__ARRAY: {
        printf("%s[", SGR_WHITE_BOLD);
        print_type(type->array_data.item_type);
        printf("%s]", SGR_WHITE_BOLD);
        return;
    }
    case TYPE__FUNCTION: {
        printf("%s(", SGR_WHITE_BOLD);
        for (List_Iterator parameters = list__create_iterator(type->function_data.parameters); list_iterator__has_next(&parameters);) {
            Parameter *parameter = list_iterator__next(&parameters);
            print_token(parameter->name);
            printf("%s: ", SGR_WHITE_BOLD);
            print_type(parameter->type);
            if (list_iterator__has_next(&parameters)) {
                printf("%s, ", SGR_WHITE_BOLD);
            }
        }
        printf("%s) -> ", SGR_WHITE_BOLD);
        print_type(type->function_data.return_type);
        return;
    }
    case TYPE__POINTER: {
        printf("%s@", SGR_WHITE_BOLD);
        print_type(type->pointer_data.type);
        return;
    }
    case TYPE__NAMED: {
        print_token(type->named_data.name);
        return;
    }
    default:
        printf("%sType::%s%s", SGR_ERROR, type__get_kind_name(type), SGR_RESET);
        return;
    }
}

void print_expression(Expression *expression) {
    if (expression == NULL) {
        printf("%sExpression::NULL%s", SGR_ERROR, SGR_RESET);
        return;
    }

    switch (expression->kind) {
    case EXPRESSION__ARRAY_ITEM:
        print_expression(expression->array_item_data.array);
        printf("[");
        print_expression(expression->array_item_data.index);
        printf("]");
        return;
    case EXPRESSION__BINARY: {
        printf("%s(", SGR_BLACK);
        print_expression(expression->binary_data.left_expression);
        printf(" ");
        print_token(expression->binary_data.operator_token);
        printf(" ");
        print_expression(expression->binary_data.right_expression);
        printf("%s)%s", SGR_BLACK, SGR_RESET);
        return;
    }
    case EXPRESSION__CALL: {
        print_expression(expression->call_data.callee);
        printf("%s(", SGR_WHITE_BOLD);
        for (List_Iterator arguments = list__create_iterator(expression->call_data.arguments); list_iterator__has_next(&arguments);) {
            Argument *argument = list_iterator__next(&arguments);
            if (argument->name != NULL) {
                print_token(argument->name);
                printf(" = ");
            }
            print_expression(argument->value);
            if (list_iterator__has_next(&arguments)) {
                printf("%s, ", SGR_WHITE_BOLD);
            }
        }
        printf("%s)%s", SGR_WHITE_BOLD, SGR_RESET);
        return;
    }
    case EXPRESSION__CAST: {
        printf("%s(", SGR_BLACK);
        print_expression(expression->cast_data.expression);
        printf("%s as ", SGR_YELLOW);
        print_type(expression->cast_data.type);
        printf("%s)%s", SGR_BLACK, SGR_RESET);
        return;
    }
    case EXPRESSION__LITERAL:
        print_token(expression->literal_data.value);
        return;
    case EXPRESSION__MEMBER:
        print_expression(expression->member_data.object);
        printf(".");
        print_token(expression->member_data.name);
        return;
    case EXPRESSION__SIZE_OF: {
        printf("%ssize_of ", SGR_YELLOW);
        print_type(expression->size_of_data.type);
        return;
    }
    case EXPRESSION__UNARY:
        printf("%s(", SGR_BLACK);
        print_token(expression->unary_data.operator_token);
        print_expression(expression->unary_data.expression);
        printf("%s)%s", SGR_BLACK, SGR_RESET);
        return;
    case EXPRESSION__VARIABLE:
        print_token(expression->variable_data.name);
        return;
    default:
        printf("%sExpression::%s%s", SGR_ERROR, expression__get_kind_name(expression), SGR_RESET);
    }
}

void print_alignment(int alignment) {
    for (int i = 0; i < alignment * 2; i++) {
        printf(" ");
    }
}

void print_statement(Statement *statement, int alignment) {
    if (statement == NULL) {
        printf("%sStatement::NULL%s", SGR_ERROR, SGR_RESET);
        return;
    }

    switch (statement->kind) {
    case STATEMENT__ASSIGNMENT: {
        print_expression(statement->assignment_data.destination);
        printf(" ");
        print_token(statement->assignment_data.operator_token);
        printf(" ");
        print_expression(statement->assignment_data.value);
        return;
    }
    case STATEMENT__BLOCK: {
        printf("%s{\n", SGR_WHITE_BOLD);
        for (List_Iterator block_statements = list__create_iterator(statement->block_data.statements); list_iterator__has_next(&block_statements);) {
            Statement *block_statement = list_iterator__next(&block_statements);
            print_alignment(alignment + 1);
            print_statement(block_statement, alignment + 1);
            printf("\n");
        }
        print_alignment(alignment);
        printf("%s}", SGR_WHITE_BOLD);
        return;
    }
    case STATEMENT__BREAK: {
        printf("%sbreak", SGR_YELLOW);
        return;
    }
    case STATEMENT__EXPRESSION: {
        print_expression(statement->expression_data.expression);
        return;
    }
    case STATEMENT__IF: {
        printf("%sif%s (", SGR_YELLOW, SGR_WHITE_BOLD);
        print_expression(statement->if_data.condition);
        printf("%s) ", SGR_WHITE_BOLD);
        print_statement(statement->if_data.true_block, alignment);
        if (statement->if_data.false_block != NULL) {
            printf(" %selse%s ", SGR_YELLOW, SGR_WHITE_BOLD);
            print_statement(statement->if_data.false_block, alignment);
        }
        return;
    }
    case STATEMENT__LOOP: {
        printf("%sloop%s ", SGR_YELLOW, SGR_WHITE_BOLD);
        print_statement(statement->loop_data.block, alignment);
        return;
    }
    case STATEMENT__FUNCTION: {
        print_token(statement->function_data.name);
        printf("%s :: (", SGR_WHITE_BOLD);
        for (List_Iterator parameters = list__create_iterator(statement->function_data.parameters); list_iterator__has_next(&parameters);) {
            Parameter *parameter = list_iterator__next(&parameters);
            print_token(parameter->name);
            printf("%s: ", SGR_WHITE_BOLD);
            print_type(parameter->type);
            if (list_iterator__has_next(&parameters)) {
                printf("%s, ", SGR_WHITE_BOLD);
            }
        }
        printf("%s) -> ", SGR_WHITE_BOLD);
        print_type(statement->function_data.return_type);
        if (statement->function_data.is_declaration) {
            return;
        }
        printf("%s {\n", SGR_WHITE_BOLD);
        for (List_Iterator function_statements = list__create_iterator(statement->function_data.statements); list_iterator__has_next(&function_statements);) {
            print_alignment(alignment + 1);
            print_statement(list_iterator__next(&function_statements), alignment + 1);
            printf("\n");
        }
        print_alignment(alignment);
        printf("%s}", SGR_WHITE_BOLD);
        return;
    }
    case STATEMENT__RETURN: {
        printf("%sreturn", SGR_YELLOW);
        if (statement->return_data.expression != NULL) {
            printf(" ");
            print_expression(statement->return_data.expression);
        }
        return;
    }
    case STATEMENT__SKIP: {
        printf("%sskip", SGR_YELLOW);
        return;
    }
    case STATEMENT__STRUCT: {
        print_token(statement->struct_data.name);
        printf("%s :: %sstruct%s", SGR_WHITE_BOLD, SGR_YELLOW, SGR_RESET);
        if (statement->struct_data.is_declaration) {
            return;
        }
        if (statement->struct_data.base_type != NULL) {
            printf("%s : ", SGR_WHITE_BOLD);
            print_type(statement->struct_data.base_type);
        }
        printf("%s {\n", SGR_WHITE_BOLD);
        for (List_Iterator members = list__create_iterator(statement->struct_data.members); list_iterator__has_next(&members);) {
            Member *member = list_iterator__next(&members);
            print_alignment(alignment + 1);
            print_token(member->name);
            printf("%s: ", SGR_WHITE_BOLD);
            print_type(member->type);
            if (member->default_value) {
                printf("%s = ", SGR_WHITE_BOLD);
                print_expression(member->default_value);
            }
            printf("\n");
        }
        print_alignment(alignment);
        printf("%s}", SGR_WHITE_BOLD);
        return;
    }
    case STATEMENT__VARIABLE: {
        print_token(statement->variable_data.name);
        if (statement->variable_data.type != NULL) {
            printf("%s: ", SGR_WHITE_BOLD);
            print_type(statement->variable_data.type);
            if (statement->variable_data.value == NULL && !statement->variable_data.is_external) {
                return;
            }
            printf(" ");
        } else {
            printf("%s :", SGR_WHITE_BOLD);
        }
        printf("%s= ", SGR_WHITE_BOLD);
        if (statement->variable_data.is_external) {
            printf("%sexternal", SGR_YELLOW);
        } else {
            print_expression(statement->variable_data.value);
        }
        return;
    }
    default:
        printf("%sStatement::%s%s", SGR_ERROR, statement__get_kind_name(statement), SGR_RESET);
        return;
    }
}

void dump_statements(Statement_List *statements) {
    for (List_Iterator iterator = list__create_iterator(statements); list_iterator__has_next(&iterator);) {
        Statement *block_statement = list_iterator__next(&iterator);
        print_statement(block_statement, 0);
        printf("%s\n\n", SGR_RESET);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        PANIC(__FILE__, __LINE__, "Usage:\n    %s <INPUT FILE> <OUTPUT FILE>\n", argv[0]);
    }

    char *input_file = argv[1];
    int input_file_length = strlen(input_file);
    if (input_file_length < 5
        || input_file[input_file_length - 5] != '.'
        || input_file[input_file_length - 4] != 'c'
        || input_file[input_file_length - 3] != 'o'
        || input_file[input_file_length - 2] != 'd'
        || input_file[input_file_length - 1] != 'e') {
        PANIC(__FILE__, __LINE__, "'%s' doesn't end with '.code'.\n", input_file);
    }

    char *output_file = argv[2];
    int output_file_length = strlen(output_file);
    if (output_file_length < 2
        || output_file[output_file_length - 2] != '.'
        || output_file[output_file_length - 1] != 's') {
        PANIC(__FILE__, __LINE__, "'%s' doesn't end with '.s'.\n", output_file);
    }

    Source *source = source__create(input_file, load_file(string__create(input_file)));

    Token_List *tokens = scan(source);

    // dump_tokens(tokens);

    Compilation_Unit *compilation_unit = parse(tokens);

    // dump_statements(compilation_unit->statements);

    generate(output_file, compilation_unit);
}
