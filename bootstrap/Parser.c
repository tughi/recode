#include "Parser.h"
#include "Logging.h"
#include "Source.h"

#include <stdlib.h>

typedef struct Context {
    List_Iterator *tokens;
    int alignment;
} Context;

#define ALIGNMENT_SIZE TAB_SIZE

typedef struct Matcher {
    int (*matches)(Token *);
    int required;
} Matcher;

Matcher *matcher__create(int (*matches)(Token *), int required) {
    Matcher *self = malloc(sizeof(Matcher));
    self->matches = matches;
    self->required = required;
    return self;
}

#define LOCATION(context) ((Token*)list_iterator__current(context->tokens))->line, ((Token*)list_iterator__current(context->tokens))->column

#define CURRENT_TOKEN(context) ((Token*)list_iterator__current(context->tokens))->lexeme->data

#define DUMP_CONTEXT(context) INFO(__FILE__, __LINE__, "(%03d,%03d) -- Token: %s", LOCATION(context), CURRENT_TOKEN(context));

#define FALSE 0
#define TRUE 1

int _matches_(int source_line, Context *context, Matcher *matchers[]) {
    list_iterator__save_state(context->tokens);
    int index = 0;
    Token *token = list_iterator__current(context->tokens);
    while (matchers[index] != NULL) {
        if ((*matchers[index]->matches)(token)) {
            token = list_iterator__next(context->tokens);
        } else if (matchers[index]->required) {
            list_iterator__restore_state(context->tokens);
            return FALSE;
        }
        index += 1;
    }
    list_iterator__restore_state(context->tokens);
    return TRUE;
}

int _matches_one_(int source_line, Context *context, Matcher *first_matcher) {
    Matcher *matchers[] = {first_matcher, NULL};
    return _matches_(source_line, context, matchers);
}

int _matches_two_(int source_line, Context *context, Matcher *first_matcher, Matcher *second_matcher) {
    Matcher *matchers[] = {first_matcher, second_matcher, NULL};
    return _matches_(source_line, context, matchers);
}

int _matches_three_(int source_line, Context *context, Matcher *first_matcher, Matcher *second_matcher, Matcher *third_matcher) {
    Matcher *matchers[] = {first_matcher, second_matcher, third_matcher, NULL};
    return _matches_(source_line, context, matchers);
}

#define matches_one(context, first_matcher) _matches_one_(__LINE__, context, first_matcher)
#define matches_two(context, first_matcher, second_matcher) _matches_two_(__LINE__, context, first_matcher, second_matcher)
#define matches_three(context, first_matcher, second_matcher, third_matcher) _matches_three_(__LINE__, context, first_matcher, second_matcher, third_matcher)

Token *_consume_(int source_line, Context *context, const char *expected, Matcher *matchers[]) {
    int index = 0;
    Token *token = list_iterator__current(context->tokens);
    Token *first_token = token;
    while (matchers[index] != NULL) {
        if ((*matchers[index]->matches)(token)) {
            token = list_iterator__next(context->tokens);
        } else if (matchers[index]->required) {
            if (expected != NULL) {
                PANIC(__FILE__, source_line, "(%03d,%03d) -- Expected %s instead of: %s", LOCATION(context), expected, CURRENT_TOKEN(context));
            }
            return NULL;
        }
        index += 1;
    }
    return first_token;
}

Token *_consume_one_(int source_line, Context *context, const char *expected, Matcher *first_matcher) {
    Matcher *matchers[] = {first_matcher, NULL};
    return _consume_(source_line, context, expected, matchers);
}

Token *_consume_two_(int source_line, Context *context, const char *expected, Matcher *first_matcher, Matcher *second_matcher) {
    Matcher *matchers[] = {first_matcher, second_matcher, NULL};
    return _consume_(source_line, context, expected, matchers);
}

Token *_consume_three_(int source_line, Context *context, const char *expected, Matcher *first_matcher, Matcher *second_matcher, Matcher *third_matcher) {
    Matcher *matchers[] = {first_matcher, second_matcher, third_matcher, NULL};
    return _consume_(source_line, context, expected, matchers);
}

#define optional(matches) matcher__create(matches, FALSE)
#define required(matches) matcher__create(matches, TRUE)

#define consume_one(context, expected, first_matcher) _consume_one_(__LINE__, context, expected, first_matcher)
#define consume_two(context, expected, first_matcher, second_matcher) _consume_two_(__LINE__, context, expected, first_matcher, second_matcher)
#define consume_three(context, expected, first_matcher, second_matcher, third_matcher) _consume_three_(__LINE__, context, expected, first_matcher, second_matcher, third_matcher)

int is_identifier(Token *token) {
    return token->kind == TOKEN_IDENTIFIER;
}

int is_keyword(Token *token, const char *lexeme) {
    return token->kind == TOKEN_KEYWORD && string__equals(token->lexeme, lexeme);
}

int is_literal(Token *token) {
    return token->kind == TOKEN_INTEGER || token->kind == TOKEN_STRING || is_keyword(token, "true") || is_keyword(token, "false") || token->kind == TOKEN_CHARACTER;
}

int is_open_paren(Token *token) {
    return token->kind == TOKEN_OTHER && string__equals(token->lexeme, "(");
}

int is_close_paren(Token *token) {
    return token->kind == TOKEN_OTHER && string__equals(token->lexeme, ")");
}

Expression *parse_expression(Context *context);

Expression *expression__create_literal(Token *value) {
    Expression *self = malloc(sizeof(Expression));
    self->kind = EXPRESSION_LITERAL;
    self->literal.value = value;
    return self;
}

Expression *expression__create_variable(Token *name) {
    Expression *self = malloc(sizeof(Expression));
    self->kind = EXPRESSION_VARIABLE;
    self->variable.name = name;
    return self;
}

// primary:
//      IDENTIFIER
//      | INTEGER
//      | STRING
//      | "false"
//      | "true"
//      | CHARACTER
//      | "(" expression ")"
Expression *parse_primary_expression(Context *context) {
    Token *name = consume_one(context, NULL, required(is_identifier));
    if (name != NULL) {
        return expression__create_variable(name);
    }
    Token *literal = consume_one(context, NULL, required(is_literal));
    if (literal != NULL) {
        return expression__create_literal(literal);
    }
    if (consume_one(context, NULL, required(is_open_paren))) {
        Expression *expression = parse_expression(context);
        consume_one(context, ")", required(is_close_paren));
        return expression; // TODO: return group
    }
    PANIC(__FILE__, __LINE__, "(%03d,%03d) -- Expected expression instead of: %s", LOCATION(context), CURRENT_TOKEN(context));
}

int is_space(Token *token) {
    return token->kind == TOKEN_SPACE;
}

int consume_space(int source_line, Context *context, int expected_spaces) {
    Token *token = _consume_one_(source_line, context, NULL, required(is_space));
    int spaces = token != NULL ? token->space.count : 0;
    if (expected_spaces >= 0 && spaces != expected_spaces) {
        WARNING(__FILE__, source_line, "(%03d,%03d) -- Consumed %d spaces where %d are expected", LOCATION(context), spaces, expected_spaces);
    }
    return spaces;
}

#define consume_space(context, expected_spaces) consume_space(__LINE__, context, expected_spaces)

int is_assign_operator(Token *token) {
    return token->kind == TOKEN_OTHER && string__equals(token->lexeme, "=");
}

Argument *argument__create(Token *name, Expression *value) {
    Argument *self = malloc(sizeof(Argument));
    self->name = name;
    self->value = value;
    self->next = NULL;
    return self;
}

Argument *parse_argument(Context *context) {
    Token *name = (Token *)NULL;
    if (matches_three(context, required(is_identifier), optional(is_space), required(is_assign_operator))) {
        name = consume_one(context, NULL, required(is_identifier));
        consume_space(context, 1);
        consume_one(context, NULL, required(is_assign_operator));
        consume_space(context, 1);
    }
    Expression *value = parse_expression(context);
    return argument__create(name, value);
}

int is_comma(Token *token) {
    return token->kind == TOKEN_OTHER && string__equals(token->lexeme, ",");
}

int is_dot(Token *token) {
    return token->kind == TOKEN_OTHER && string__equals(token->lexeme, ".");
}

int is_open_bracket(Token *token) {
    return token->kind == TOKEN_OTHER && string__equals(token->lexeme, "[");
}

int is_close_bracket(Token *token) {
    return token->kind == TOKEN_OTHER && string__equals(token->lexeme, "]");
}

Expression *expression__create_call(Expression *callee, Argument *first_argument) {
    Expression *self = malloc(sizeof(Expression));
    self->kind = EXPRESSION_CALL;
    self->call.callee = callee;
    self->call.first_argument = first_argument;
    return self;
}

Expression *expression__create_member(Expression *object, Token *name) {
    Expression *self = malloc(sizeof(Expression));
    self->kind = EXPRESSION_MEMBER;
    self->member.object = object;
    self->member.name = name;
    return self;
}

Expression *expression__create_array_item(Expression *array, Expression *index) {
    Expression *self = malloc(sizeof(Expression));
    self->kind = EXPRESSION_ARRAY_ITEM;
    self->array_item.array = array;
    self->array_item.index = index;
    return self;
}

int is_as_keyword(Token *token) {
    return is_keyword(token, "as");
}

Type *parse_type(Context *context);

Expression *expression__create_cast(Expression *expression, Type *type) {
    Expression *self = malloc(sizeof(Expression));
    self->kind = EXPRESSION_CAST;
    self->cast.expression = expression;
    self->cast.type = type;
    return self;
}

// call:
//      primary ("(" argument ("," argument)* ")" | "." IDENTIFIER | "[" expression "]" | "as" type)*
Expression *parse_call_expression(Context *context) {
    Expression *expression = parse_primary_expression(context);
    while (TRUE) {
        if (matches_two(context, optional(is_space), required(is_open_paren))) {
            consume_space(context, 0);
            consume_one(context, NULL, required(is_open_paren));
            Argument *first_argument = NULL;
            if (!matches_two(context, optional(is_space), required(is_close_paren))) {
                Argument *last_argument = NULL;
                do {
                    consume_space(context, first_argument == NULL ? 0 : 1);
                    Argument *argument = parse_argument(context);
                    if (last_argument != NULL) {
                        last_argument->next = argument;
                    } else {
                        first_argument = argument;
                    }
                    last_argument = argument;
                    if (matches_two(context, optional(is_space), required(is_comma))) {
                        consume_space(context, 0);
                        consume_one(context, NULL, required(is_comma));
                    } else {
                        break;
                    }
                } while (TRUE);
            }
            consume_space(context, 0);
            consume_one(context, NULL, required(is_close_paren));
            expression = expression__create_call(expression, first_argument);
        } else if (matches_two(context, optional(is_space), required(is_dot))) {
            consume_space(context, 0);
            consume_one(context, NULL, required(is_dot));
            consume_space(context, 0);
            Token *name = consume_one(context, NULL, required(is_identifier));
            expression = expression__create_member(expression, name);
        } else if (matches_two(context, optional(is_space), required(is_open_bracket))) {
            consume_space(context, 0);
            consume_one(context, NULL, required(is_open_bracket));
            consume_space(context, 0);
            Expression *index = parse_expression(context);
            consume_space(context, 0);
            consume_one(context, NULL, required(is_close_bracket));
            expression = expression__create_array_item(expression, index);
        } else if (matches_two(context, optional(is_space), required(is_as_keyword))) {
            consume_space(context, 1);
            consume_one(context, NULL, required(is_as_keyword));
            consume_space(context, 1);
            Type *type = parse_type(context);
            expression = expression__create_cast(expression, type);
        } else {
            break;
        }
    }
    return expression;
}

int is_unary_operator(Token *token) {
    return token->kind == TOKEN_OTHER && (string__equals(token->lexeme, "!") || string__equals(token->lexeme, "-"));
}

Expression *expression__create_unary(Token *operator_token, Expression *expression) {
    Expression *self = malloc(sizeof(Expression));
    self->kind = EXPRESSION_UNARY;
    self->unary.operator_token = operator_token;
    self->unary.expression = expression;
    return self;
}

// unary:
//      ("!" | "-") unary
//      | primary
Expression *parse_unary_expression(Context *context) {
    if (matches_one(context, required(is_unary_operator))) {
        Token *unary_operator = consume_one(context, NULL, required(is_unary_operator));
        consume_space(context, 0);
        Expression *unary_expression = parse_unary_expression(context);
        return expression__create_unary(unary_operator, unary_expression);
    }
    return parse_call_expression(context);
}

int is_division_operator(Token *token) {
    return token->kind == TOKEN_OTHER && string__equals(token->lexeme, "/");
}

int is_multiplication_operator(Token *token) {
    return token->kind == TOKEN_OTHER && (string__equals(token->lexeme, "*") || string__equals(token->lexeme, "/"));
}

Expression *expression__create_binary(Token *operator_token, Expression *left_expression, Expression *right_expression) {
    Expression *self = malloc(sizeof(Expression));
    self->kind = EXPRESSION_BINARY;
    self->binary.operator_token = operator_token;
    self->binary.left_expression = left_expression;
    self->binary.right_expression = right_expression;
    return self;
}

// multiplication:
//      unary (("*" | "/" | "//") unary)*
Expression *parse_multiplication_expression(Context *context) {
    Expression *expression = parse_unary_expression(context);
    while (matches_two(context, optional(is_space), required(is_multiplication_operator)) && !matches_three(context, optional(is_space), required(is_multiplication_operator), required(is_assign_operator))) {
        consume_space(context, 1);
        Token *operator_token = consume_one(context, NULL, required(is_multiplication_operator));
        if (is_division_operator(operator_token)) {
            Token *operator_other_token = consume_one(context, NULL, required(is_division_operator));
            if (operator_other_token != NULL) {
                token__join(operator_token, operator_other_token);
            }
        }
        consume_space(context, 1);
        Expression *right_expression = parse_unary_expression(context);
        expression = expression__create_binary(operator_token, expression, right_expression);
    }
    return expression;
}

int is_addition_operator(Token *token) {
    return token->kind == TOKEN_OTHER && (string__equals(token->lexeme, "+") || string__equals(token->lexeme, "-"));
}

// addition:
//      mutliplication (("+" | "-") multiplication)*
Expression *parse_addition_expression(Context *context) {
    Expression *expression = parse_multiplication_expression(context);
    while (matches_two(context, optional(is_space), required(is_addition_operator)) && !matches_three(context, optional(is_space), required(is_addition_operator), required(is_assign_operator))) {
        consume_space(context, 1);
        Token *operator_token = consume_one(context, NULL, required(is_addition_operator));
        consume_space(context, 1);
        Expression *right_expression = parse_multiplication_expression(context);
        expression = expression__create_binary(operator_token, expression, right_expression);
    }
    return expression;
}

int is_comparison_operator(Token *token) {
    return token->kind == TOKEN_OTHER && (string__equals(token->lexeme, "<") || string__equals(token->lexeme, ">"));
}

// comparison:
//      addition (("<" | ">") "="? addition)?
Expression *parse_comparison_expression(Context *context) {
    Expression *expression = parse_addition_expression(context);
    if (matches_two(context, optional(is_space), required(is_comparison_operator))) {
        consume_space(context, 1);
        Token *operator_token = consume_one(context, NULL, required(is_comparison_operator));
        Token *operator_other_token = consume_one(context, NULL, required(is_assign_operator));
        if (operator_other_token != NULL) {
            token__join(operator_token, operator_other_token);
        }
        consume_space(context, 1);
        Expression *right_expression = parse_addition_expression(context);
        return expression__create_binary(operator_token, expression, right_expression);
    }
    return expression;
}

int is_equality_operator(Token *token) {
    return token->kind == TOKEN_OTHER && (string__equals(token->lexeme, "!") || string__equals(token->lexeme, "="));
}

// equality:
//      comparison (("!" | "=") "=" comparison)?
Expression *parse_equality_expression(Context *context) {
    Expression *expression = parse_comparison_expression(context);
    if (matches_three(context, optional(is_space), required(is_equality_operator), required(is_assign_operator))) {
        consume_space(context, 1);
        Token *operator_token = consume_one(context, NULL, required(is_equality_operator));
        Token *operator_other_token = consume_one(context, NULL, required(is_assign_operator));
        token__join(operator_token, operator_other_token);
        consume_space(context, 1);
        Expression *right_expression = parse_comparison_expression(context);
        return expression__create_binary(operator_token, expression, right_expression);
    }
    return expression;
}

int is_and_operator(Token *token) {
    return token->kind == TOKEN_OTHER && string__equals(token->lexeme, "&");
}

// logic_and:
//      equality ("&" "&" equality)*
Expression *parse_logic_and_expression(Context *context) {
    Expression *expression = parse_equality_expression(context);
    while (matches_three(context, optional(is_space), required(is_and_operator), required(is_and_operator))) {
        consume_space(context, 1);
        Token *operator_token = consume_one(context, NULL, required(is_and_operator));
        Token *operator_other_token = consume_one(context, NULL, required(is_and_operator));
        token__join(operator_token, operator_other_token);
        consume_space(context, 1);
        Expression *right_expression = parse_equality_expression(context);
        expression = expression__create_binary(operator_token, expression, right_expression);
    }
    return expression;
}

int is_or_operator(Token *token) {
    return token->kind == TOKEN_OTHER && string__equals(token->lexeme, "|");
}

// logic_or:
//      logic_and ("|" "|" logic_and)*
Expression *parse_logic_or_expression(Context *context) {
    Expression *expression = parse_logic_and_expression(context);
    while (matches_three(context, optional(is_space), required(is_or_operator), required(is_or_operator))) {
        consume_space(context, 1);
        Token *operator_token = consume_one(context, NULL, required(is_or_operator));
        Token *operator_other_token = consume_one(context, NULL, required(is_or_operator));
        token__join(operator_token, operator_other_token);
        consume_space(context, 1);
        Expression *right_expression = parse_logic_and_expression(context);
        expression = expression__create_binary(operator_token, expression, right_expression);
    }
    return expression;
}

// expression:
//      logic_or
Expression *parse_expression(Context *context) {
    return parse_logic_or_expression(context);
}

int is_colon(Token *token) {
    return token->kind == TOKEN_OTHER && string__equals(token->lexeme, ":");
}

int is_open_brace(Token *token) {
    return token->kind == TOKEN_OTHER && string__equals(token->lexeme, "{");
}

int is_close_brace(Token *token) {
    return token->kind == TOKEN_OTHER && string__equals(token->lexeme, "}");
}

int is_hyphen(Token *token) {
    return token->kind == TOKEN_OTHER && string__equals(token->lexeme, "-");
}

int is_close_angled_bracket(Token *token) {
    return token->kind == TOKEN_OTHER && string__equals(token->lexeme, ">");
}

Type *parse_type(Context *context);

Member *member__create(Token *name, Type *type, Expression *default_value) {
    Member *self = malloc(sizeof(Member));
    self->name = name;
    self->type = type;
    self->default_value = default_value;
    self->next = NULL;
    return self;
}

// member:
//      IDENTIFIER ":" type ("=" expression)?
Member *parse_member(Context *context) {
    Token *name = consume_one(context, "name", required(is_identifier));
    consume_space(context, 0);
    consume_one(context, ":", required(is_colon));
    consume_space(context, 1);
    Type *type = parse_type(context);
    Expression *default_value = NULL;
    if (matches_two(context, optional(is_space), required(is_assign_operator))) {
        consume_space(context, 1);
        consume_one(context, "=", required(is_assign_operator));
        consume_space(context, 1);
        default_value = parse_expression(context);
    }
    return member__create(name, type, default_value);
}

// comma_separated_members:
//      member ("," member)*
Member *parse_comma_separated_members(Context *context) {
    Member *first_member = NULL;
    Member *last_member = NULL;
    do {
        consume_space(context, first_member == NULL ? 0 : 1);
        Member *member = parse_member(context);
        if (last_member == NULL) {
            first_member = member;
        } else {
            last_member->next = member;
        }
        last_member = member;
        consume_space(context, 0);
    } while (consume_one(context, NULL, required(is_comma)));
    return first_member;
}

int is_pointer_operator(Token *token) {
    return token->kind == TOKEN_OTHER && string__equals(token->lexeme, "@");
}

Type *type__create_array(Type *item_type) {
    Type *self = malloc(sizeof(Type));
    self->kind = TYPE_ARRAY;
    self->array.item_type = item_type;
    return self;
}

Type *type__create_function(Member *first_parameter, Type *return_type) {
    Type *self = malloc(sizeof(Type));
    self->kind = TYPE_FUNCTION;
    self->function.first_parameter = first_parameter;
    self->function.return_type = return_type;
    return self;
}

Type *type__create_tuple(Member *first_member) {
    Type *self = malloc(sizeof(Type));
    self->kind = TYPE_TUPLE;
    self->tuple.first_member = first_member;
    return self;
}

Type *type__create_simple(Token *name) {
    Type *self = malloc(sizeof(Type));
    self->kind = TYPE_SIMPLE;
    self->simple.name = name;
    return self;
}

static Type *type__create_pointer(Type *type) {
    Type *self = malloc(sizeof(Type));
    self->kind = TYPE_POINTER;
    self->pointer.type = type;
    return self;
}

// type:
//      "@"? (
//          IDENTIFIER
//          | "[" type "]"
//          | "(" comma_separated_members? ")"
//      )
Type *parse_type(Context *context) {
    int is_pointer = matches_one(context, required(is_pointer_operator));
    if (is_pointer) {
        consume_one(context, NULL, required(is_pointer_operator));
        consume_space(context, 0);
    }
    Type *type = NULL;
    if (consume_one(context, NULL, required(is_open_bracket))) {
        consume_space(context, 0);
        Type *item_type = parse_type(context);
        consume_space(context, 0);
        consume_one(context, "]", required(is_close_bracket));
        consume_space(context, 0);
        type = type__create_array(item_type);
    } else if (consume_one(context, NULL, required(is_open_paren))) {
        consume_space(context, 0);
        Member *first_member = NULL;
        if (consume_one(context, NULL, required(is_close_paren)) == NULL) {
            first_member = parse_comma_separated_members(context);
            consume_one(context, ")", required(is_close_paren));
        }
        if (matches_three(context, optional(is_space), required(is_hyphen), required(is_close_angled_bracket))) {
            consume_space(context, 1);
            consume_two(context, "->", required(is_hyphen), required(is_close_angled_bracket));
            consume_space(context, 1);
            Type *return_type = parse_type(context);
            type = type__create_function(first_member, return_type);
        } else {
            type = type__create_tuple(first_member);
        }
    } else {
        Token *name = consume_one(context, "type name", required(is_identifier));
        type = type__create_simple(name);
    }
    if (is_pointer) {
        type = type__create_pointer(type);
    }
    return type;
}

int is_comment(Token *token) {
    return token->kind == TOKEN_COMMENT;
}

int is_end_of_line(Token *token) {
    return token->kind == TOKEN_END_OF_LINE;
}

int is_end_of_file(Token *token) {
    return token->kind == TOKEN_END_OF_FILE;
}

int _consume_end_of_line_(int source_line, Context *context, int required) {
    if (matches_three(context, optional(is_space), optional(is_comment), required(is_end_of_line)) || matches_three(context, optional(is_space), optional(is_comment), required(is_end_of_file))) {
        if (matches_two(context, optional(is_space), required(is_comment))) {
            consume_space(context, context->alignment * ALIGNMENT_SIZE);
            consume_one(context, NULL, required(is_comment));
        } else {
            consume_space(context, 0);
        }
        return consume_one(context, NULL, required(is_end_of_line)) != NULL;
    }
    if (required) {
        PANIC(__FILE__, __LINE__, "(%03d,%03d) -- Expected <EOL> instead of: %s", LOCATION(context), CURRENT_TOKEN(context));
    }
    return FALSE;
}

#define consume_end_of_line(context, required) _consume_end_of_line_(__LINE__, context, required)

int is_struct_keyword(Token *token) {
    return is_keyword(token, "struct");
}

Statement *statement__create_struct_declaration(Expression *name) {
    Statement *self = malloc(sizeof(Statement));
    self->kind = STATEMENT_STRUCT_DECLARATION;
    self->struct_declaration.name = name;
    return self;
}

Statement *statement__create_struct_definition(Expression *name, Token *base, Member *first_member) {
    Statement *self = malloc(sizeof(Statement));
    self->kind = STATEMENT_STRUCT_DEFINITION;
    self->struct_definition.name = name;
    self->struct_definition.base = base;
    self->struct_definition.first_member = first_member;
    return self;
}

// struct:
//      "struct" ("{" EOL (member EOL)* "}")? EOL
Statement *parse_struct(Context *context, Expression *name) {
    consume_one(context, "struct", required(is_struct_keyword));
    if (consume_end_of_line(context, FALSE) == TRUE) {
        return statement__create_struct_declaration(name);
    }
    consume_space(context, 1);
    Token *base = NULL;
    if (consume_one(context, NULL, required(is_colon))) {
        consume_space(context, 1);
        base = consume_one(context, "base struct", required(is_identifier));
        consume_space(context, 1);
    }
    consume_one(context, "{", required(is_open_brace));
    consume_end_of_line(context, TRUE);
    Member *first_member = NULL;
    Member *last_member = NULL;
    while (!matches_two(context, optional(is_space), required(is_close_brace))) {
        consume_space(context, (context->alignment + 1) * ALIGNMENT_SIZE);
        Member *member = parse_member(context);
        consume_end_of_line(context, TRUE);
        if (last_member != NULL) {
            last_member->next = member;
        } else {
            first_member = member;
        }
        last_member = member;
    }
    consume_space(context, context->alignment * ALIGNMENT_SIZE);
    consume_one(context, "}", required(is_close_brace));
    consume_end_of_line(context, TRUE);
    return statement__create_struct_definition(name, base, first_member);
}

Statement *parse_statement(Context *context);

Statement *parse_statements(Context *context) {
    Statement *first_statement = NULL;
    Statement *last_statement = NULL;
    do {
        Statement *statement = parse_statement(context);
        if (statement == NULL) {
            break;
        }
        statement->next = NULL;
        if (last_statement != NULL) {
            last_statement->next = statement;
        } else {
            first_statement = statement;
        }
        last_statement = statement;
    } while (TRUE);
    return first_statement;
}

Statement *statement__create_function_declaration(Expression *name, Member *first_parameter, Type *return_type) {
    Statement *self = malloc(sizeof(Statement));
    self->kind = STATEMENT_FUNCTION_DECLARATION;
    self->function_definition.name = name;
    self->function_definition.first_parameter = first_parameter;
    self->function_definition.return_type = return_type;
    return self;
}

Statement *statement__create_function_definition(Expression *name, Member *first_parameter, Type *return_type, Statement *first_statement) {
    Statement *self = malloc(sizeof(Statement));
    self->kind = STATEMENT_FUNCTION_DEFINITION;
    self->function_definition.name = name;
    self->function_definition.first_parameter = first_parameter;
    self->function_definition.return_type = return_type;
    self->function_definition.first_statement = first_statement;
    return self;
}

// function:
//      "(" comma_separated_members? ")" ("->" type)? ("{" EOL statement* "}")? EOL
Statement *parse_function(Context *context, Expression *name) {
    consume_one(context, "(", required(is_open_paren));
    consume_space(context, 0);
    Member *first_parameter = NULL;
    if (consume_one(context, NULL, required(is_close_paren)) == NULL) {
        first_parameter = parse_comma_separated_members(context);
        consume_one(context, ")", required(is_close_paren));
    }
    consume_space(context, 1);
    Type *return_type = NULL;
    if (consume_two(context, NULL, required(is_hyphen), required(is_close_angled_bracket)) != NULL) {
        consume_space(context, 1);
        return_type = parse_type(context);
        if (consume_end_of_line(context, FALSE) == TRUE) {
            return statement__create_function_declaration(name, first_parameter, return_type);
        } else {
            consume_space(context, 1);
        }
    } else if (consume_end_of_line(context, FALSE) == TRUE) {
        return statement__create_function_declaration(name, first_parameter, return_type);
    }
    consume_one(context, "{", required(is_open_brace));
    consume_end_of_line(context, TRUE);
    context->alignment += 1;
    Statement *first_statement = parse_statements(context);
    context->alignment -= 1;
    consume_space(context, context->alignment * ALIGNMENT_SIZE);
    consume_one(context, "}", required(is_close_brace));
    consume_end_of_line(context, TRUE);
    return statement__create_function_definition(name, first_parameter, return_type, first_statement);
}

Statement *statement__create_block(Statement *first_statement) {
    Statement *self = malloc(sizeof(Statement));
    self->kind = STATEMENT_BLOCK;
    self->block.first_statement = first_statement;
    return self;
}

// block:
//      "{" EOL statement* "}" EOL
Statement *parse_block_statement(Context *context, int inlined) {
    consume_one(context, "{", required(is_open_brace));
    consume_end_of_line(context, TRUE);
    context->alignment += 1;
    Statement *first_statement = parse_statements(context);
    context->alignment -= 1;
    consume_space(context, context->alignment * ALIGNMENT_SIZE);
    consume_one(context, "}", required(is_close_brace));
    if (!inlined) {
        consume_end_of_line(context, TRUE);
    }
    return statement__create_block(first_statement);
}

int is_if_keyword(Token *token) {
    return is_keyword(token, "if");
}

int is_else_keyword(Token *token) {
    return is_keyword(token, "else");
}

Statement *statement__create_if(Expression *condition, Statement *true_block, Statement *false_block) {
    Statement *self = malloc(sizeof(Statement));
    self->kind = STATEMENT_IF;
    self->if_.condition = condition;
    self->if_.true_block = true_block;
    self->if_.false_block = false_block;
    return self;
}

// return:
//      "if" "(" expression ")" block ("else" block)? EOL
Statement *parse_if_statement(Context *context) {
    consume_one(context, "if", required(is_if_keyword));
    consume_space(context, 1);
    consume_one(context, "(", required(is_open_paren));
    consume_space(context, 0);
    Expression *condition = parse_expression(context);
    consume_space(context, 0);
    consume_one(context, ")", required(is_close_paren));
    consume_space(context, 1);
    Statement *true_block = parse_block_statement(context, TRUE);
    Statement *false_block = NULL;
    if (matches_two(context, optional(is_space), required(is_else_keyword))) {
        consume_space(context, 1);
        consume_one(context, NULL, required(is_else_keyword));
        consume_space(context, 1);
        false_block = parse_block_statement(context, TRUE);
    }
    consume_end_of_line(context, TRUE);
    return statement__create_if(condition, true_block, false_block);
}

int is_loop_keyword(Token *token) {
    return is_keyword(token, "loop");
}

Statement *statement__create_loop(Statement *block) {
    Statement *self = malloc(sizeof(Statement));
    self->kind = STATEMENT_LOOP;
    self->loop.block = block;
    return self;
}

// loop:
//      "loop" block EOL
Statement *parse_loop_statement(Context *context) {
    consume_one(context, "loop", required(is_loop_keyword));
    consume_space(context, 1);
    Statement *block = parse_block_statement(context, TRUE);
    consume_end_of_line(context, TRUE);
    return statement__create_loop(block);
}

int is_break_keyword(Token *token) {
    return is_keyword(token, "break");
}

Statement *statement__create_break() {
    Statement *self = malloc(sizeof(Statement));
    self->kind = STATEMENT_BREAK;
    return self;
}

// break:
//      "break" EOL
Statement *parse_break_statement(Context *context) {
    consume_one(context, "break", required(is_break_keyword));
    consume_end_of_line(context, TRUE);
    return statement__create_break();
}

int is_skip_keyword(Token *token) {
    return is_keyword(token, "skip");
}

Statement *statement__create_skip() {
    Statement *self = malloc(sizeof(Statement));
    self->kind = STATEMENT_SKIP;
    return self;
}

// skip:
//      "skip" EOL
Statement *parse_skip_statement(Context *context) {
    consume_one(context, "skip", required(is_skip_keyword));
    consume_end_of_line(context, TRUE);
    return statement__create_skip();
}

int is_return_keyword(Token *token) {
    return is_keyword(token, "return");
}

Statement *statement__create_return(Expression *expression) {
    Statement *self = malloc(sizeof(Statement));
    self->kind = STATEMENT_RETURN;
    self->return_expression = expression;
    return self;
}

// return:
//      "return" expression? EOL
Statement *parse_return_statement(Context *context) {
    consume_one(context, "return", required(is_return_keyword));
    if (consume_end_of_line(context, FALSE)) {
        return statement__create_return(NULL);
    }
    consume_space(context, 1);
    Expression *expression = parse_expression(context);
    consume_end_of_line(context, TRUE);
    return statement__create_return(expression);
}

int is_assign_variant(Token *token) {
    return is_addition_operator(token) || is_multiplication_operator(token);
}

Statement *statement__create_expression(Expression *expression) {
    Statement *self = malloc(sizeof(Statement));
    self->kind = STATEMENT_EXPRESSION;
    self->expression = expression;
    return self;
}

Statement *statement__create_variable_declaration(Expression *name, Type *type, Expression *value, int external) {
    Statement *self = malloc(sizeof(Statement));
    self->kind = STATEMENT_VARIABLE_DECLARATION;
    self->variable_declaration.name = name;
    self->variable_declaration.type = type;
    self->variable_declaration.value = value;
    self->variable_declaration.external = external;
    return self;
}

Statement *statement__create_assignment(Expression *destination, Token *operator_token, Expression *value) {
    Statement *self = malloc(sizeof(Statement));
    self->kind = STATEMENT_ASSIGNMENT;
    self->assignment.destination = destination;
    self->assignment.operator_token = operator_token;
    self->assignment.value = value;
    return self;
}

int is_external_keyword(Token *token) {
    return is_keyword(token, "external");
}

// statement:
//      break
//      | if
//      | loop
//      | return
//      | skip
//      | expression ((":" ":" definition) | (":" declaration) | ("=" assignment))?
Statement *parse_statement(Context *context) {
    while (consume_end_of_line(context, FALSE)) {
        // do nothing
    }
    if (matches_one(context, required(is_end_of_file)) || matches_two(context, optional(is_space), required(is_close_brace))) {
        return NULL;
    }

    consume_space(context, context->alignment * ALIGNMENT_SIZE);

    if (matches_one(context, required(is_open_brace))) {
        return parse_block_statement(context, FALSE);
    }

    if (matches_one(context, required(is_if_keyword))) {
        return parse_if_statement(context);
    }

    if (matches_one(context, required(is_loop_keyword))) {
        return parse_loop_statement(context);
    }

    if (matches_one(context, required(is_return_keyword))) {
        return parse_return_statement(context);
    }

    if (matches_one(context, required(is_break_keyword))) {
        return parse_break_statement(context);
    }

    if (matches_one(context, required(is_skip_keyword))) {
        return parse_skip_statement(context);
    }

    // TODO: parse other statements

    Expression *expression = parse_expression(context);
    if (consume_end_of_line(context, FALSE)) {
        return statement__create_expression(expression);
    }

    if (matches_three(context, optional(is_space), required(is_colon), required(is_colon))) {
        consume_space(context, 1);
        consume_two(context, NULL, required(is_colon), required(is_colon));
        consume_space(context, 1);
        if (matches_one(context, required(is_struct_keyword))) {
            return parse_struct(context, expression);
        }
        return parse_function(context, expression);
    }

    if (matches_two(context, optional(is_space), required(is_colon))) {
        if (matches_three(context, optional(is_space), required(is_colon), required(is_assign_operator))) {
            consume_space(context, 1);
            consume_two(context, NULL, required(is_colon), required(is_assign_operator));
            consume_space(context, 1);
            Expression *value = parse_expression(context);
            consume_end_of_line(context, TRUE);
            return statement__create_variable_declaration(expression, NULL, value, FALSE);
        }
        consume_space(context, 0);
        consume_one(context, NULL, required(is_colon));
        consume_space(context, 1);
        Type *type = parse_type(context);
        consume_space(context, 1);
        consume_one(context, NULL, required(is_assign_operator));
        consume_space(context, 1);
        if (consume_one(context, NULL, required(is_external_keyword)) != NULL) {
            consume_end_of_line(context, TRUE);
            return statement__create_variable_declaration(expression, type, NULL, TRUE);
        }
        Expression *value = parse_expression(context);
        consume_end_of_line(context, TRUE);
        return statement__create_variable_declaration(expression, type, value, FALSE);
    }

    if (matches_three(context, optional(is_space), optional(is_assign_variant), required(is_assign_operator))) {
        consume_space(context, 1);
        Token *operator_token = consume_one(context, NULL, required(is_assign_variant));
        if (operator_token != NULL) {
            Token *operator_other_token = consume_one(context, NULL, required(is_assign_operator));
            token__join(operator_token, operator_other_token);
        } else {
            operator_token = consume_one(context, NULL, required(is_assign_operator));
        }
        consume_space(context, 1);
        Expression *value = parse_expression(context);
        consume_end_of_line(context, TRUE);
        return statement__create_assignment(expression, operator_token, value);
    }

    consume_space(context, 0);
    PANIC(__FILE__, __LINE__, "(%03d,%03d) -- Unxpected token: %s", LOCATION(context), CURRENT_TOKEN(context));
}

Statement *parse(List *tokens) {
    Context *context = malloc(sizeof(Context));
    context->tokens = list__create_iterator(tokens);
    list_iterator__next(context->tokens);
    context->alignment = 0;
    Statement *first_statement = parse_statements(context);
    return first_statement;
}
