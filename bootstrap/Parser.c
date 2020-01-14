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

#define LOCATION(context) ((Token *)list_iterator__current(context->tokens))->line, ((Token *)list_iterator__current(context->tokens))->column

#define CURRENT_TOKEN(context) ((Token *)list_iterator__current(context->tokens))->lexeme->data

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
    self->location.line = value->line;
    self->location.column = value->column;
    self->literal.value = value;
    return self;
}

Expression *expression__create_variable(Token *name) {
    Expression *self = malloc(sizeof(Expression));
    self->kind = EXPRESSION_VARIABLE;
    self->location.line = name->line;
    self->location.column = name->column;
    self->variable.name = name;
    return self;
}

int is_size_of_keyword(Token *token) {
    return is_keyword(token, "size_of");
}

Type *parse_type(Context *context);

Expression *expression__create_size_of(Token *frist_token, Type *type) {
    Expression *self = malloc(sizeof(Expression));
    self->kind = EXPRESSION_SIZE_OF;
    self->location.line = frist_token->line;
    self->location.column = frist_token->column;
    self->size_of.type = type;
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
//      | "size_of" IDENTIFIER
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
        consume_space(context, 0);
        Expression *expression = parse_expression(context);
        consume_space(context, 0);
        consume_one(context, ")", required(is_close_paren));
        return expression; // TODO: return group
    }
    if (matches_one(context, required(is_size_of_keyword))) {
        Token *first_token = consume_one(context, NULL, required(is_size_of_keyword));
        consume_space(context, 1);
        Type *type = parse_type(context);
        return expression__create_size_of(first_token, type);
    }
    PANIC(__FILE__, __LINE__, "(%03d,%03d) -- Expected expression instead of: %s", LOCATION(context), CURRENT_TOKEN(context));
}

int is_assign_operator(Token *token) {
    return token->kind == TOKEN_OTHER && string__equals(token->lexeme, "=");
}

Argument *argument__create(Token *name, Expression *value) {
    Argument *self = malloc(sizeof(Argument));
    self->name = name;
    self->value = value;
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

Expression *expression__create_call(Expression *callee, List *arguments) {
    Expression *self = malloc(sizeof(Expression));
    self->kind = EXPRESSION_CALL;
    self->location = callee->location;
    self->call.callee = callee;
    self->call.arguments = arguments;
    return self;
}

Expression *expression__create_member(Expression *object, Token *name) {
    Expression *self = malloc(sizeof(Expression));
    self->kind = EXPRESSION_MEMBER;
    self->location = object->location;
    self->member.object = object;
    self->member.name = name;
    return self;
}

Expression *expression__create_array_item(Expression *array, Expression *index) {
    Expression *self = malloc(sizeof(Expression));
    self->kind = EXPRESSION_ARRAY_ITEM;
    self->location = array->location;
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
    self->location = expression->location;
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
            List *arguments = list__create();
            if (!matches_two(context, optional(is_space), required(is_close_paren))) {
                int space_before_argument = 0;
                do {
                    consume_space(context, space_before_argument);
                    list__append(arguments, parse_argument(context));
                    if (matches_two(context, optional(is_space), required(is_comma))) {
                        consume_space(context, 0);
                        consume_one(context, NULL, required(is_comma));
                    } else {
                        break;
                    }
                    space_before_argument = 1;
                } while (TRUE);
            }
            consume_space(context, 0);
            consume_one(context, NULL, required(is_close_paren));
            expression = expression__create_call(expression, arguments);
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
    self->location.line = operator_token->line;
    self->location.column = operator_token->column;
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
    self->location = left_expression->location;
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

Member *member__create(int reference, Token *name, Type *type, Expression *default_value) {
    Member *self = malloc(sizeof(Member));
    self->reference = reference;
    self->name = name;
    self->type = type;
#ifdef ENABLE__MEMBER_DEFAULT_VALUE
    self->default_value = default_value;
#endif
    return self;
}

int is_reference_operator(Token *token) {
    return token->kind == TOKEN_OTHER && string__equals(token->lexeme, "@");
}

// member:
//      "@"? IDENTIFIER ":" type ("=" expression)?
Member *parse_member(Context *context) {
    int reference;
    if (consume_one(context, NULL, required(is_reference_operator))) {
        reference = TRUE;
        consume_space(context, 0);
    } else {
        reference = FALSE;
    }
    Token *name = consume_one(context, "name", required(is_identifier));
    consume_space(context, 0);
    consume_one(context, ":", required(is_colon));
    consume_space(context, 1);
    Type *type = parse_type(context);
    Expression *default_value = NULL;
#ifdef ENABLE__MEMBER_DEFAULT_VALUE
    if (matches_two(context, optional(is_space), required(is_assign_operator))) {
        consume_space(context, 1);
        consume_one(context, "=", required(is_assign_operator));
        consume_space(context, 1);
        default_value = parse_expression(context);
    }
#endif
    return member__create(reference, name, type, default_value);
}

// comma_separated_members:
//      member ("," member)*
List *parse_comma_separated_members(Context *context) {
    List *members = list__create();
    int space_before_next_member = 0;
    do {
        consume_space(context, space_before_next_member);
        list__append(members, parse_member(context));
        consume_space(context, 0);
        space_before_next_member = 1;
    } while (consume_one(context, NULL, required(is_comma)));
    return members;
}

int is_pointer_operator(Token *token) {
    return token->kind == TOKEN_OTHER && string__equals(token->lexeme, "@");
}

static Type *type__create_array(Token *first_token, Type *item_type) {
    Type *self = malloc(sizeof(Type));
    self->kind = TYPE_ARRAY;
    self->location.line = first_token->line;
    self->location.column = first_token->column;
    self->array.item_type = item_type;
    return self;
}

static Type *type__create_function(Token *first_token, Type *return_type, List *parameters) {
    Type *self = malloc(sizeof(Type));
    self->kind = TYPE_FUNCTION;
    self->location.line = first_token->line;
    self->location.column = first_token->column;
    self->function.parameters = parameters;
    self->function.return_type = return_type;
    return self;
}

Type *type__create_tuple(Token *first_token, List *members) {
    Type *self = malloc(sizeof(Type));
    self->kind = TYPE_TUPLE;
    self->location.line = first_token->line;
    self->location.column = first_token->column;
    self->tuple.members = members;
    return self;
}

Type *type__create_simple(Token *first_token, Token *name) {
    Type *self = malloc(sizeof(Type));
    self->kind = TYPE_SIMPLE;
    self->location.line = first_token->line;
    self->location.column = first_token->column;
    self->simple.name = name;
    return self;
}

static Type *type__create_pointer(Token *first_token, Type *type) {
    Type *self = malloc(sizeof(Type));
    self->kind = TYPE_POINTER;
    self->location.line = first_token->line;
    self->location.column = first_token->column;
    self->pointer.type = type;
    return self;
}

// type
//      : "@" type
//      | IDENTIFIER
//      | "[" type "]"
//      | "(" comma_separated_members? ")" ("->" type)?
Type *parse_type(Context *context) {
    if (matches_one(context, required(is_pointer_operator))) {
        Token *first_token = consume_one(context, NULL, required(is_pointer_operator));
        consume_space(context, 0);
        return type__create_pointer(first_token, parse_type(context));
    }
    if (matches_one(context, required(is_open_bracket))) {
        Token *first_token = consume_one(context, NULL, required(is_open_bracket));
        consume_space(context, 0);
        Type *item_type = parse_type(context);
        consume_space(context, 0);
        consume_one(context, "]", required(is_close_bracket));
        consume_space(context, 0);
        return type__create_array(first_token, item_type);
    }
    if (matches_one(context, required(is_open_paren))) {
        Token *first_token = consume_one(context, NULL, required(is_open_paren));
        consume_space(context, 0);
        List *members = NULL;
        if (consume_one(context, NULL, required(is_close_paren)) == NULL) {
            members = parse_comma_separated_members(context);
            consume_one(context, ")", required(is_close_paren));
        }
        if (matches_three(context, optional(is_space), required(is_hyphen), required(is_close_angled_bracket))) {
            consume_space(context, 1);
            consume_two(context, "->", required(is_hyphen), required(is_close_angled_bracket));
            consume_space(context, 1);
            Type *return_type = parse_type(context);
            return type__create_function(first_token, return_type, members);
        } else {
            return type__create_tuple(first_token, members);
        }
    }
    Token *name = consume_one(context, "type name", required(is_identifier));
    return type__create_simple(name, name);
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

Statement *statement__create_struct(Expression *name, Token *base, List *members) {
    Statement *self = malloc(sizeof(Statement));
    self->kind = STATEMENT_STRUCT;
    self->struct_.name = name;
    self->struct_.base = base;
    self->struct_.members = members;
    self->struct_.declaration = members == NULL;
    return self;
}

// struct:
//      "struct" ("{" EOL (member EOL)* "}")? EOL
Statement *parse_struct(Context *context, Expression *name) {
    consume_one(context, "struct", required(is_struct_keyword));
    if (consume_end_of_line(context, FALSE) == TRUE) {
        return statement__create_struct(name, NULL, NULL);
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
    List *members = list__create();
    while (!matches_two(context, optional(is_space), required(is_close_brace))) {
        consume_space(context, (context->alignment + 1) * ALIGNMENT_SIZE);
        list__append(members, parse_member(context));
        consume_end_of_line(context, TRUE);
    }
    consume_space(context, context->alignment * ALIGNMENT_SIZE);
    consume_one(context, "}", required(is_close_brace));
    consume_end_of_line(context, TRUE);
    return statement__create_struct(name, base, members);
}

Statement *parse_statement(Context *context);

List *parse_statements(Context *context) {
    List *statements = list__create();
    do {
        Statement *statement = parse_statement(context);
        if (statement == NULL) {
            break;
        }
        list__append(statements, statement);
    } while (TRUE);
    return statements;
}

Statement *statement__create_function(Expression *name, Type *return_type, List *parameters, List *statements) {
    Statement *self = malloc(sizeof(Statement));
    self->kind = STATEMENT_FUNCTION;
    self->function.name = name;
    self->function.return_type = return_type;
    self->function.parameters = parameters;
    self->function.statements = statements;
    self->function.declaration = statements == NULL;
    return self;
}

// function:
//      "(" comma_separated_members? ")" "->" type ("{" EOL statement* "}")? EOL
Statement *parse_function(Context *context, Expression *name) {
    consume_one(context, "(", required(is_open_paren));
    consume_space(context, 0);
    List *parameters = NULL;
    if (consume_one(context, NULL, required(is_close_paren)) == NULL) {
        parameters = parse_comma_separated_members(context);
        consume_one(context, ")", required(is_close_paren));
    } else {
        parameters = list__create();
    }
    consume_space(context, 1);
    consume_two(context, "->", required(is_hyphen), required(is_close_angled_bracket));
    consume_space(context, 1);
    Type *return_type = parse_type(context);
    if (consume_end_of_line(context, FALSE) == TRUE) {
        return statement__create_function(name, return_type, parameters, NULL);
    } else {
        consume_space(context, 1);
    }
    consume_one(context, "{", required(is_open_brace));
    consume_end_of_line(context, TRUE);
    context->alignment += 1;
    List *statements = parse_statements(context);
    context->alignment -= 1;
    consume_space(context, context->alignment * ALIGNMENT_SIZE);
    consume_one(context, "}", required(is_close_brace));
    consume_end_of_line(context, TRUE);
    return statement__create_function(name, return_type, parameters, statements);
}

Statement *statement__create_block(List *statements) {
    Statement *self = malloc(sizeof(Statement));
    self->kind = STATEMENT_BLOCK;
    self->block.statements = statements;
    return self;
}

// block:
//      "{" EOL statement* "}" EOL
Statement *parse_block_statement(Context *context, int inlined) {
    consume_one(context, "{", required(is_open_brace));
    consume_end_of_line(context, TRUE);
    context->alignment += 1;
    List *statements = parse_statements(context);
    context->alignment -= 1;
    consume_space(context, context->alignment * ALIGNMENT_SIZE);
    consume_one(context, "}", required(is_close_brace));
    if (!inlined) {
        consume_end_of_line(context, TRUE);
    }
    return statement__create_block(statements);
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

Statement *statement__create_variable(Expression *name, Type *type, Expression *value, int external) {
    Statement *self = malloc(sizeof(Statement));
    self->kind = STATEMENT_VARIABLE;
    self->variable.name = name;
    self->variable.type = type;
    self->variable.value = value;
    self->variable.external = external;
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
            return statement__create_variable(expression, NULL, value, FALSE);
        }
        consume_space(context, 0);
        consume_one(context, NULL, required(is_colon));
        consume_space(context, 1);
        Type *type = parse_type(context);
        if (consume_end_of_line(context, FALSE)) {
            return statement__create_variable(expression, type, NULL, FALSE);
        }
        consume_space(context, 1);
        consume_one(context, NULL, required(is_assign_operator));
        consume_space(context, 1);
        if (consume_one(context, NULL, required(is_external_keyword)) != NULL) {
            consume_end_of_line(context, TRUE);
            return statement__create_variable(expression, type, NULL, TRUE);
        }
        Expression *value = parse_expression(context);
        consume_end_of_line(context, TRUE);
        return statement__create_variable(expression, type, value, FALSE);
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

List *parse(List *tokens) {
    List_Iterator tokens_iterator = list__create_iterator(tokens);

    Context *context = malloc(sizeof(Context));
    context->tokens = &tokens_iterator;
    list_iterator__next(context->tokens);
    context->alignment = 0;
    return parse_statements(context);
}
