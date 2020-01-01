#include "Generator.h"
#include "Logging.h"
#include "Parser.h"
#include "Scanner.h"

#include <stdlib.h>
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
    case TOKEN_CHARACTER:
        printf("%s%s%s", SGR_GREEN, token->lexeme->data, SGR_RESET);
        return;
    case TOKEN_COMMENT:
        printf("%s%s%s", SGR_DEFAULT, token->lexeme->data, SGR_RESET);
        return;
    case TOKEN_END_OF_FILE:
        printf("%s%s%s\n", SGR_BLACK, token->lexeme->data, SGR_RESET);
        return;
    case TOKEN_END_OF_LINE:
        printf("%s%s%s", SGR_BLACK, token->lexeme->data, SGR_RESET);
        return;
    case TOKEN_ERROR:
        printf("%s%s%s", SGR_ERROR, token->lexeme->data, SGR_RESET);
        return;
    case TOKEN_IDENTIFIER:
        printf("%s%s%s", token->lexeme->data[0] <= 'Z' ? SGR_FAINT_YELLOW : SGR_RESET, token->lexeme->data, SGR_RESET);
        return;
    case TOKEN_INTEGER:
        printf("%s%s%s", SGR_CYAN, token->lexeme->data, SGR_RESET);
        return;
    case TOKEN_KEYWORD:
        printf("%s%s%s", SGR_YELLOW, token->lexeme->data, SGR_RESET);
        return;
    case TOKEN_OTHER:
        printf("%s%s%s", SGR_WHITE_BOLD, token->lexeme->data, SGR_RESET);
        return;
    case TOKEN_SPACE:
        printf("%s%s", SGR_RESET, token->lexeme->data);
        return;
    case TOKEN_STRING:
        printf("%s%s%s", SGR_GREEN, token->lexeme->data, SGR_RESET);
        return;
    default:
        printf("%sToken::%d%s", SGR_ERROR, token->kind, SGR_RESET);
    }
}

void dump_tokens(List *tokens) {
    int line = 0;
    for (List_Iterator *iterator = list__create_iterator(tokens); list_iterator__has_next(iterator); ) {
        Token *token = list_iterator__next(iterator);
        if (token->line != line) {
            if (line > 0) {
                printf("\n");
            }
            line = token->line;
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
    case TYPE_ARRAY: {
        printf("%s[", SGR_WHITE_BOLD);
        print_type(type->array.item_type);
        printf("%s]", SGR_WHITE_BOLD);
        return;
    }
    case TYPE_FUNCTION: {
        printf("%s(", SGR_WHITE_BOLD);
        for (List_Iterator *parameters = list__create_iterator(type->function.parameters); list_iterator__has_next(parameters); ) {
            Parameter *parameter = list_iterator__next(parameters);
            print_token(parameter->name); 
            printf("%s: ", SGR_WHITE_BOLD);
            print_type(parameter->type);
            if (list_iterator__has_next(parameters)) {
                printf("%s, ", SGR_WHITE_BOLD);
            }
        }
        printf("%s) -> ", SGR_WHITE_BOLD);
        print_type(type->function.return_type);
        return;
    }
    case TYPE_POINTER: {
        printf("%s@", SGR_WHITE_BOLD);
        print_type(type->pointer.type);
        return;
    }
    case TYPE_SIMPLE: {
        print_token(type->simple.name);
        return;
    }
    case TYPE_TUPLE: {
        printf("%s(", SGR_WHITE_BOLD);
        for (List_Iterator *members = list__create_iterator(type->tuple.members); list_iterator__has_next(members); ) {
            Member *member = list_iterator__next(members);
            print_token(member->name);
            printf("%s: ", SGR_WHITE_BOLD);
            print_type(member->type);
            if (list_iterator__has_next(members)) {
                printf("%s, ", SGR_WHITE_BOLD);
            }
        }
        printf("%s)", SGR_WHITE_BOLD);
        return;
    }
    default:
        printf("%sType::%d%s", SGR_ERROR, type->kind, SGR_RESET);
        return;
    }
}

void print_expression(Expression *expression) {
    if (expression == NULL) {
        printf("%sExpression::NULL%s", SGR_ERROR, SGR_RESET);
        return;
    }

    switch (expression->kind) {
    case EXPRESSION_ARRAY_ITEM:
        print_expression(expression->array_item.array);
        printf("[");
        print_expression(expression->array_item.index);
        printf("]");
        return;
    case EXPRESSION_BINARY: {
        printf("%s(", SGR_BLACK);
        print_expression(expression->binary.left_expression);
        printf(" ");
        print_token(expression->binary.operator_token);
        printf(" ");
        print_expression(expression->binary.right_expression);
        printf("%s)%s", SGR_BLACK, SGR_RESET);
        return;
    }
    case EXPRESSION_CALL: {
        print_expression(expression->call.callee);
        printf("%s(", SGR_WHITE_BOLD);
        for (List_Iterator *arguments = list__create_iterator(expression->call.arguments); list_iterator__has_next(arguments); ) {
            Argument *argument = list_iterator__next(arguments);
            if (argument->name != NULL) {
                print_token(argument->name);
                printf(" = ");
            }
            print_expression(argument->value);
            if (list_iterator__has_next(arguments)) {
                printf("%s, ", SGR_WHITE_BOLD);
            }
        }
        printf("%s)%s", SGR_WHITE_BOLD, SGR_RESET);
        return;
    }
    case EXPRESSION_CAST: {
        printf("%s(", SGR_BLACK);
        print_expression(expression->cast.expression);
        printf("%s as ", SGR_YELLOW);
        print_type(expression->cast.type);
        printf("%s)%s", SGR_BLACK, SGR_RESET);
        return;
    }
    case EXPRESSION_LITERAL:
        print_token(expression->literal.value);
        return;
    case EXPRESSION_MEMBER:
        print_expression(expression->member.object);
        printf(".");
        print_token(expression->member.name);
        return;
    case EXPRESSION_VARIABLE:
        print_token(expression->variable.name);
        return;
    case EXPRESSION_UNARY:
        printf("%s(", SGR_BLACK);
        print_token(expression->unary.operator_token);
        print_expression(expression->unary.expression);
        printf("%s)%s", SGR_BLACK, SGR_RESET);
        return;
    default:
        printf("%sExpression::%d%s", SGR_ERROR, expression->kind, SGR_RESET);
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
    case STATEMENT_ASSIGNMENT: {
        print_expression(statement->assignment.destination);
        printf(" ");
        print_token(statement->assignment.operator_token);
        printf(" ");
        print_expression(statement->assignment.value);
        return;
    }
    case STATEMENT_BLOCK: {
        printf("%s{\n", SGR_WHITE_BOLD);
        for (List_Iterator *block_statements = list__create_iterator(statement->block.statements); list_iterator__has_next(block_statements); ) {
            Statement *block_statement = list_iterator__next(block_statements);
            print_alignment(alignment + 1);
            print_statement(block_statement, alignment + 1);
            printf("\n");
        }
        print_alignment(alignment);
        printf("%s}", SGR_WHITE_BOLD);
        return;
    }
    case STATEMENT_BREAK: {
        printf("%sbreak", SGR_YELLOW);
        return;
    }
    case STATEMENT_EXPRESSION: {
        print_expression(statement->expression);
        return;
    }
    case STATEMENT_IF: {
        printf("%sif%s (", SGR_YELLOW, SGR_WHITE_BOLD);
        print_expression(statement->if_.condition);
        printf("%s) ", SGR_WHITE_BOLD);
        print_statement(statement->if_.true_block, alignment);
        if (statement->if_.false_block != NULL) {
            printf(" %selse%s ", SGR_YELLOW, SGR_WHITE_BOLD);
            print_statement(statement->if_.false_block, alignment);
        }
        return;
    }
    case STATEMENT_LOOP: {
        printf("%sloop%s ", SGR_YELLOW, SGR_WHITE_BOLD);
        print_statement(statement->loop.block, alignment);
        return;
    }
    case STATEMENT_FUNCTION_DECLARATION: {
        print_expression(statement->function_definition.name);
        printf("%s :: (", SGR_WHITE_BOLD);
        for (List_Iterator *parameters = list__create_iterator(statement->function_declaration.parameters); list_iterator__has_next(parameters); ) {
            Parameter *parameter = list_iterator__next(parameters);
            print_token(parameter->name);
            printf("%s: ", SGR_WHITE_BOLD);
            print_type(parameter->type);
            if (list_iterator__has_next(parameters)) {
                printf("%s, ", SGR_WHITE_BOLD);
            }
        }
        printf("%s)", SGR_WHITE_BOLD);
        if (statement->function_definition.return_type != NULL) {
            printf(" -> ");
            print_type(statement->function_definition.return_type);
        }
        printf("%s", SGR_RESET);
        return;
    }
    case STATEMENT_FUNCTION_DEFINITION: {
        print_expression(statement->function_definition.name);
        printf("%s :: (", SGR_WHITE_BOLD);
        for (List_Iterator *parameters = list__create_iterator(statement->function_definition.parameters); list_iterator__has_next(parameters); ) {
            Parameter *parameter = list_iterator__next(parameters);
            print_token(parameter->name);
            printf("%s: ", SGR_WHITE_BOLD);
            print_type(parameter->type);
            if (list_iterator__has_next(parameters)) {
                printf("%s, ", SGR_WHITE_BOLD);
            }
        }
        printf("%s)", SGR_WHITE_BOLD);
        if (statement->function_definition.return_type != NULL) {
            printf(" -> ");
            print_type(statement->function_definition.return_type);
        }
        printf("%s {\n", SGR_WHITE_BOLD);
        for (List_Iterator *function_statements = list__create_iterator(statement->function_definition.statements); list_iterator__has_next(function_statements); ) {
            print_alignment(alignment + 1);
            print_statement(list_iterator__next(function_statements), alignment + 1);
            printf("\n");
        }
        print_alignment(alignment);
        printf("%s}", SGR_WHITE_BOLD);
        return;
    }
    case STATEMENT_RETURN: {
        printf("%sreturn", SGR_YELLOW);
        if (statement->return_expression != NULL) {
            printf(" ");
            print_expression(statement->return_expression);
        }
        return;
    }
    case STATEMENT_SKIP: {
        printf("%sskip", SGR_YELLOW);
        return;
    }
    case STATEMENT_STRUCT_DECLARATION: {
        print_expression(statement->struct_definition.name);
        printf("%s :: %sstruct%s", SGR_WHITE_BOLD, SGR_YELLOW, SGR_RESET);
        return;
    }
    case STATEMENT_STRUCT_DEFINITION: {
        print_expression(statement->struct_definition.name);
        printf("%s :: %sstruct", SGR_WHITE_BOLD, SGR_YELLOW);
        if (statement->struct_definition.base != NULL) {
            printf("%s : ", SGR_WHITE_BOLD);
            print_token(statement->struct_definition.base);
        }
        printf("%s {\n", SGR_WHITE_BOLD);
        alignment += 1;
        for (List_Iterator *members = list__create_iterator(statement->struct_definition.members); list_iterator__has_next(members); ) {
            Member *member = list_iterator__next(members);
            print_alignment(alignment);
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
    case STATEMENT_VARIABLE_DECLARATION: {
        print_expression(statement->variable_declaration.name);
        if (statement->variable_declaration.type != NULL) {
            printf("%s: ", SGR_WHITE_BOLD);
            print_type(statement->variable_declaration.type);
            printf(" ");
        } else {
            printf("%s :", SGR_WHITE_BOLD);
        }
        printf("%s= ", SGR_WHITE_BOLD);
        if (statement->variable_declaration.external) {
            printf("%sexternal", SGR_YELLOW);
        } else {
            print_expression(statement->variable_declaration.value);
        }
        return;
    }
    default:
        printf("%sStatement::%d%s", SGR_ERROR, statement->kind, SGR_RESET);
        return;
    }
}

void dump_statements(List *statements) {
    for (List_Iterator *iterator = list__create_iterator(statements); list_iterator__has_next(iterator); ) {
        Statement *block_statement = list_iterator__next(iterator);
        print_statement(block_statement, 0);
        printf("\n\n");
    }
}

int main(int argc, char *argv[]) {
    // String *source_file = string__create("../src/Source.code");
    // String *source_file = string__create("../src/Visitor.code");
    String *source_file = string__create("../src/Test.code");
    Source *source = source__create(load_file(source_file));

    List *tokens = scan(source);

    // dump_tokens(tokens);

    List *statements = parse(tokens);

    dump_statements(statements);

    generate(statements);
}
