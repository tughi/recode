#include "Logging.h"
#include "Parser.h"
#include "Source.h"

typedef struct Context {
    List_Iterator *tokens;
    int alignment;
    Named_Functions *named_functions;
    Named_Types *named_types;
} Context;

#define ALIGNMENT_SIZE TAB_SIZE

static Context *context__create(List_Iterator *tokens) {
    Context *self = malloc(sizeof(Context));
    self->tokens = tokens;
    self->named_functions = named_functions__create();
    self->named_types = named_types__create();
    self->alignment = 0;
    list_iterator__next(self->tokens);
    return self;
}

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

#define CURRENT_TOKEN(context) ((Token *)list_iterator__current(context->tokens))

#define DUMP_CONTEXT(context) INFO(__FILE__, __LINE__, SOURCE_LOCATION "Token: %s", SOURCE(CURRENT_TOKEN(context)->location), CURRENT_TOKEN(context)->lexeme->data);

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
                PANIC(__FILE__, source_line, SOURCE_LOCATION "Expected %s instead of: %s", SOURCE(CURRENT_TOKEN(context)->location), expected, CURRENT_TOKEN(context)->lexeme->data);
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
    return token->kind == TOKEN__SPACE;
}

int consume_space(int source_line, Context *context, int expected_spaces) {
    Token *token = _consume_one_(source_line, context, NULL, required(is_space));
    int spaces = token != NULL ? token->space_data.count : 0;
    if (expected_spaces >= 0 && spaces != expected_spaces) {
        WARNING(__FILE__, source_line, SOURCE_LOCATION "Consumed %d spaces where %d are expected", SOURCE(CURRENT_TOKEN(context)->location), spaces, expected_spaces);
    }
    return spaces;
}

#define consume_space(context, expected_spaces) consume_space(__LINE__, context, expected_spaces)

int is_identifier(Token *token) {
    return token->kind == TOKEN__IDENTIFIER;
}

int is_keyword(Token *token, const char *lexeme) {
    return token->kind == TOKEN__KEYWORD && string__equals(token->lexeme, lexeme);
}

int is_integer(Token *token) {
    return token->kind == TOKEN__INTEGER;
}

int is_literal(Token *token) {
    return token->kind == TOKEN__INTEGER || token->kind == TOKEN__STRING || is_keyword(token, "true") || is_keyword(token, "false") || token->kind == TOKEN__CHARACTER;
}

int is_open_paren(Token *token) {
    return token->kind == TOKEN__OTHER && string__equals(token->lexeme, "(");
}

int is_close_paren(Token *token) {
    return token->kind == TOKEN__OTHER && string__equals(token->lexeme, ")");
}

Expression *parse_expression(Context *context);

Expression *expression__create(int kind, Source_Location *location) {
    Expression *self = malloc(sizeof(Expression));
    self->kind = kind;
    self->location = location;
    return self;
}

Expression *expression__create_literal(Token *value) {
    Expression *self = expression__create(EXPRESSION__LITERAL, value->location);
    self->literal_data.value = value;
    return self;
}

Expression *expression__create_variable(Token *name) {
    Expression *self = expression__create(EXPRESSION__VARIABLE, name->location);
    self->variable_data.name = name;
    return self;
}

int is_new_keyword(Token *token) {
    return is_keyword(token, "new");
}

int is_size_of_keyword(Token *token) {
    return is_keyword(token, "size_of");
}

Type *parse_type(Context *context);

Expression *expression__create_new(Source_Location *location, Type *type) {
    Expression *self = expression__create(EXPRESSION__NEW, location);
    self->new_data.type = type;
    return self;
}

Expression *expression__create_size_of(Source_Location *location, Type *type) {
    Expression *self = expression__create(EXPRESSION__SIZE_OF, location);
    self->size_of_data.type = type;
    return self;
}

int is_pointer_operator(Token *token) {
    return token->kind == TOKEN__OTHER && string__equals(token->lexeme, "@");
}

Expression *expression__create_pointer_to(Source_Location *location, Expression *expression) {
    Expression *self = expression__create(EXPRESSION__POINTER_TO, location);
    self->pointer_to_data.expression = expression;
    return self;
}

int is_open_bracket(Token *token) {
    return token->kind == TOKEN__OTHER && string__equals(token->lexeme, "[");
}

int is_close_bracket(Token *token) {
    return token->kind == TOKEN__OTHER && string__equals(token->lexeme, "]");
}

Expression *expression__create_pointed_value(Source_Location *location, Expression *expression) {
    Expression *self = expression__create(EXPRESSION__POINTED_VALUE, location);
    self->pointed_value_data.expression = expression;
    return self;
}

// primary
//      : IDENTIFIER
//      | INTEGER
//      | STRING
//      | "false"
//      | "true"
//      | CHARACTER
//      | "(" expression ")"
//      | "new" type
//      | "size_of" type
//      | "@" primary
//      | "[" expression "]"
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
    if (matches_one(context, required(is_new_keyword))) {
        Source_Location *location = consume_one(context, NULL, required(is_new_keyword))->location;
        consume_space(context, 1);
        Type *type = parse_type(context);
        return expression__create_new(location, type);
    }
    if (matches_one(context, required(is_size_of_keyword))) {
        Source_Location *location = consume_one(context, NULL, required(is_size_of_keyword))->location;
        consume_space(context, 1);
        Type *type = parse_type(context);
        return expression__create_size_of(location, type);
    }
    if (matches_one(context, required(is_pointer_operator))) {
        Source_Location *location = consume_one(context, NULL, required(is_pointer_operator))->location;
        consume_space(context, 0);
        Expression *expression = parse_primary_expression(context);
        return expression__create_pointer_to(location, expression);
    }
    if (matches_one(context, required(is_open_bracket))) {
        Source_Location *location = consume_one(context, NULL, required(is_open_bracket))->location;
        consume_space(context, 0);
        Expression *expression = parse_expression(context);
        consume_space(context, 0);
        consume_one(context, "]", required(is_close_bracket));
        return expression__create_pointed_value(location, expression);
    }
    PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Expected expression instead of: %s", SOURCE(CURRENT_TOKEN(context)->location), CURRENT_TOKEN(context)->lexeme->data);
}

int is_assign_operator(Token *token) {
    return token->kind == TOKEN__OTHER && string__equals(token->lexeme, "=");
}

Argument *argument__create(Token *name, Expression *value) {
    Argument *self = malloc(sizeof(Argument));
    self->name = name;
    self->value = value;
    self->inferred_type = NULL;
    return self;
}

// argument
//      : (IDENTIFIER "=")? expression
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
    return token->kind == TOKEN__OTHER && string__equals(token->lexeme, ",");
}

int is_dot(Token *token) {
    return token->kind == TOKEN__OTHER && string__equals(token->lexeme, ".");
}

Expression *expression__create_call(Expression *callee, List *arguments) {
    Expression *self = expression__create(EXPRESSION__CALL, callee->location);
    self->call_data.callee = callee;
    self->call_data.arguments = arguments;
    return self;
}

Expression *expression__create_member(Expression *object, Token *name) {
    Expression *self = expression__create(EXPRESSION__MEMBER, object->location);
    self->member_data.object = object;
    self->member_data.name = name;
    return self;
}

Expression *expression__create_array_item(Expression *array, Expression *index) {
    Expression *self = expression__create(EXPRESSION__ARRAY_ITEM, array->location);
    self->array_item_data.array = array;
    self->array_item_data.index = index;
    return self;
}

int is_as_keyword(Token *token) {
    return is_keyword(token, "as");
}

Expression *expression__create_cast(Expression *expression, Type *type) {
    Expression *self = expression__create(EXPRESSION__CAST, expression->location);
    self->cast_data.expression = expression;
    self->cast_data.type = type;
    return self;
}

// call
//      : primary ("(" argument ("," argument)* ")" | "." IDENTIFIER | "[" expression "]" | "as" type)*
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
    return token->kind == TOKEN__OTHER && (string__equals(token->lexeme, "!") || string__equals(token->lexeme, "-"));
}

Expression *expression__create_unary(Token *operator_token, Expression *expression) {
    Expression *self = expression__create(EXPRESSION__UNARY, operator_token->location);
    self->unary_data.operator_token = operator_token;
    self->unary_data.expression = expression;
    return self;
}

// unary
//      : ("!" | "-") unary
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
    return token->kind == TOKEN__OTHER && string__equals(token->lexeme, "/");
}

int is_multiplication_operator(Token *token) {
    return token->kind == TOKEN__OTHER && (string__equals(token->lexeme, "*") || string__equals(token->lexeme, "/"));
}

Expression *expression__create_binary(Token *operator_token, Expression *left_expression, Expression *right_expression) {
    Expression *self = expression__create(EXPRESSION__BINARY, left_expression->location);
    self->binary_data.operator_token = operator_token;
    self->binary_data.left_expression = left_expression;
    self->binary_data.right_expression = right_expression;
    return self;
}

// multiplication
//      : unary (("*" | "/" | "//") unary)*
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
    return token->kind == TOKEN__OTHER && (string__equals(token->lexeme, "+") || string__equals(token->lexeme, "-"));
}

// addition
//      : mutliplication (("+" | "-") multiplication)*
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
    return token->kind == TOKEN__OTHER && (string__equals(token->lexeme, "<") || string__equals(token->lexeme, ">"));
}

// comparison
//      : addition (("<" | ">") "="? addition)?
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
    return token->kind == TOKEN__OTHER && (string__equals(token->lexeme, "!") || string__equals(token->lexeme, "="));
}

// equality
//      : comparison (("!" | "=") "=" comparison)?
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
    return token->kind == TOKEN__OTHER && string__equals(token->lexeme, "&");
}

// logic_and
//      : equality ("&" "&" equality)*
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
    return token->kind == TOKEN__OTHER && string__equals(token->lexeme, "|");
}

// logic_or
//      : logic_and ("||" logic_and)*
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

// expression
//      : logic_or
Expression *parse_expression(Context *context) {
    return parse_logic_or_expression(context);
}

int is_colon(Token *token) {
    return token->kind == TOKEN__OTHER && string__equals(token->lexeme, ":");
}

int is_open_brace(Token *token) {
    return token->kind == TOKEN__OTHER && string__equals(token->lexeme, "{");
}

int is_close_brace(Token *token) {
    return token->kind == TOKEN__OTHER && string__equals(token->lexeme, "}");
}

int is_hyphen(Token *token) {
    return token->kind == TOKEN__OTHER && string__equals(token->lexeme, "-");
}

int is_close_angled_bracket(Token *token) {
    return token->kind == TOKEN__OTHER && string__equals(token->lexeme, ">");
}

Member *member__create(int is_reference, Token *name, Type *type, Expression *default_value) {
    Member *self = malloc(sizeof(Member));
    self->is_reference = is_reference;
    self->name = name;
    self->type = type;
    self->default_value = default_value;
    self->struct_offset = 0;
    return self;
}

int is_reference_operator(Token *token) {
    return token->kind == TOKEN__OTHER && string__equals(token->lexeme, "@");
}

// member
//      : "@"? IDENTIFIER ":" type ("=" expression)?
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
    if (matches_two(context, optional(is_space), required(is_assign_operator))) {
        consume_space(context, 1);
        consume_one(context, "=", required(is_assign_operator));
        consume_space(context, 1);
        default_value = parse_expression(context);
    }
    return member__create(reference, name, type, default_value);
}

// comma_separated_members
//      : member ("," member)*
Member_List *parse_comma_separated_members(Context *context) {
    Member_List *members = list__create();
    int space_before_next_member = 0;
    do {
        consume_space(context, space_before_next_member);
        list__append(members, parse_member(context));
        consume_space(context, 0);
        space_before_next_member = 1;
    } while (consume_one(context, NULL, required(is_comma)));
    return members;
}

int is_semicolon(Token *token) {
    return token->kind == TOKEN__OTHER && string__equals(token->lexeme, ";");
}

// type
//      : "@" type
//      | IDENTIFIER
//      | "[" type (";" INTEGER)? "]"
//      | "(" comma_separated_members? ")" "->" type
Type *parse_type(Context *context) {
    if (matches_one(context, required(is_pointer_operator))) {
        Source_Location *location = consume_one(context, NULL, required(is_pointer_operator))->location;
        consume_space(context, 0);
        return type__create_pointer(location, parse_type(context));
    }
    if (matches_one(context, required(is_open_bracket))) {
        Source_Location *location = consume_one(context, NULL, required(is_open_bracket))->location;
        consume_space(context, 0);
        Type *item_type = parse_type(context);
        consume_space(context, 0);
        int array_size = 0;
        if (consume_one(context, NULL, required(is_semicolon))) {
            consume_space(context, 1);
            Token *array_size_token = consume_one(context, "array size", required(is_integer));
            array_size = array_size_token->integer_data.value;
            if (array_size <= 0) {
                PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Invalid array size: %d", SOURCE(array_size_token->location), array_size);
            }
            consume_space(context, 0);
        }
        consume_one(context, "]", required(is_close_bracket));
        consume_space(context, 0);
        return type__create_array(location, item_type, array_size);
    }
    if (matches_one(context, required(is_open_paren))) {
        Source_Location *location = consume_one(context, NULL, required(is_open_paren))->location;
        consume_space(context, 0);
        List *members = NULL;
        if (consume_one(context, NULL, required(is_close_paren)) == NULL) {
            members = parse_comma_separated_members(context);
            consume_one(context, ")", required(is_close_paren));
        }
        consume_space(context, 1);
        consume_two(context, "->", required(is_hyphen), required(is_close_angled_bracket));
        consume_space(context, 1);
        Type *return_type = parse_type(context);
        return type__create_function(location, return_type, members);
    }
    Token *name = consume_one(context, "type name", required(is_identifier));
    return type__create_named(name->location, name);
}

int is_comment(Token *token) {
    return token->kind == TOKEN__COMMENT;
}

int is_end_of_line(Token *token) {
    return token->kind == TOKEN__END_OF_LINE;
}

int is_end_of_file(Token *token) {
    return token->kind == TOKEN__END_OF_FILE;
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
        PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Expected <EOL> instead of: %s", SOURCE(CURRENT_TOKEN(context)->location), CURRENT_TOKEN(context)->lexeme->data);
    }
    return FALSE;
}

#define consume_end_of_line(context, required) _consume_end_of_line_(__LINE__, context, required)

int is_struct_keyword(Token *token) {
    return is_keyword(token, "struct");
}

static Statement *statement__create(int kind, Source_Location *location) {
    Statement *self = malloc(sizeof(Statement));
    self->kind = kind;
    self->location = location;
    return self;
}

Statement *statement__create_struct(Source_Location *location, Token *name, Token *base, List *members) {
    Statement *self = statement__create(STATEMENT__STRUCT, location);
    self->struct_data.name = name;
    self->struct_data.base = base;
    self->struct_data.members = members;
    self->struct_data.is_declaration = members == NULL;
    return self;
}

// struct
//      : "struct" ("{" EOL (member EOL)* "}")? EOL
Statement *parse_struct(Context *context, Token *name) {
    Source_Location *location = name->location;
    consume_one(context, "struct", required(is_struct_keyword));
    if (consume_end_of_line(context, FALSE) == TRUE) {
        return statement__create_struct(location, name, NULL, NULL);
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
    return statement__create_struct(location, name, base, members);
}

Statement *parse_statement(Context *context);

Statement_List *parse_statements(Context *context) {
    Statement_List *statements = list__create();
    do {
        Statement *statement = parse_statement(context);
        if (statement == NULL) {
            break;
        }
        list__append(statements, statement);
    } while (TRUE);
    return statements;
}

void string__append_type_name(String *self, Type *type) {
    switch (type->kind) {
    case TYPE__NAMED:
        string__append_string(self, type->named_data.name->lexeme);
        return;
    case TYPE__POINTER:
        string__append_char(self, 'p');
        string__append_type_name(self, type->pointer_data.type);
        return;
    }
    PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Unsupported type kind %s", SOURCE(type->location), type__get_kind_name(type));
}

Statement *statement__create_function(Source_Location *location, Token *name, Type *return_type, List *parameters, List *statements) {
    Statement *self = statement__create(STATEMENT__FUNCTION, location);
    self->function_data.name = name;
    self->function_data.return_type = return_type;
    self->function_data.parameters = parameters;
    self->function_data.statements = statements;
    self->function_data.is_declaration = statements == NULL;

    String *unique_name = string__create(name->lexeme->data);
    if (!string__equals(name->lexeme, "main") && statements != NULL) {
        string__append_chars(unique_name, "__", 2);
        string__append_type_name(unique_name, return_type);
        if (list__size(parameters) > 0) {
            string__append_chars(unique_name, "__", 2);
            for (List_Iterator iterator = list__create_iterator(parameters); list_iterator__has_next(&iterator);) {
                Parameter *parameter = list_iterator__next(&iterator);
                string__append_type_name(unique_name, parameter->type);
                if (list_iterator__has_next(&iterator)) {
                    string__append_char(unique_name, '_');
                }
            }
        }
    }
    self->function_data.unique_name = unique_name;

    return self;
}

// function
//      : "(" comma_separated_members? ")" "->" type ("{" EOL statement* "}")? EOL
Statement *parse_function(Context *context, Token *name) {
    Source_Location *location = consume_one(context, "(", required(is_open_paren))->location;
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
        return statement__create_function(location, name, return_type, parameters, NULL);
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
    return statement__create_function(location, name, return_type, parameters, statements);
}

Statement *statement__create_block(Source_Location *location, List *statements) {
    Statement *self = statement__create(STATEMENT__BLOCK, location);
    self->block_data.statements = statements;
    return self;
}

// block
//      : "{" EOL statement* "}" EOL
Statement *parse_block_statement(Context *context, int inlined) {
    Source_Location *location = consume_one(context, "{", required(is_open_brace))->location;
    consume_end_of_line(context, TRUE);
    context->alignment += 1;
    List *statements = parse_statements(context);
    context->alignment -= 1;
    consume_space(context, context->alignment * ALIGNMENT_SIZE);
    consume_one(context, "}", required(is_close_brace));
    if (!inlined) {
        consume_end_of_line(context, TRUE);
    }
    return statement__create_block(location, statements);
}

int is_if_keyword(Token *token) {
    return is_keyword(token, "if");
}

int is_else_keyword(Token *token) {
    return is_keyword(token, "else");
}

Statement *statement__create_if(Source_Location *location, Expression *condition, Statement *true_block, Statement *false_block) {
    Statement *self = statement__create(STATEMENT__IF, location);
    self->if_data.condition = condition;
    self->if_data.true_block = true_block;
    self->if_data.false_block = false_block;
    return self;
}

// return
//      : "if" "(" expression ")" block ("else" block)? EOL
Statement *parse_if_statement(Context *context) {
    Source_Location *location = consume_one(context, "if", required(is_if_keyword))->location;
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
    return statement__create_if(location, condition, true_block, false_block);
}

int is_loop_keyword(Token *token) {
    return is_keyword(token, "loop");
}

Statement *statement__create_loop(Source_Location *location, Statement *block) {
    Statement *self = statement__create(STATEMENT__LOOP, location);
    self->loop_data.block = block;
    return self;
}

// loop
//      : "loop" block EOL
Statement *parse_loop_statement(Context *context) {
    Source_Location *location = consume_one(context, "loop", required(is_loop_keyword))->location;
    consume_space(context, 1);
    Statement *block = parse_block_statement(context, TRUE);
    consume_end_of_line(context, TRUE);
    return statement__create_loop(location, block);
}

int is_while_keyword(Token *token) {
    return is_keyword(token, "while");
}

Statement *statement__create_while(Source_Location *location, Expression *condition, Statement *block) {
    Statement *self = statement__create(STATEMENT__WHILE, location);
    self->while_data.condition = condition;
    self->while_data.block = block;
    return self;
}

// return
//      : "while" "(" expression ")" block EOL
Statement *parse_while_statement(Context *context) {
    Source_Location *location = consume_one(context, "while", required(is_while_keyword))->location;
    consume_space(context, 1);
    consume_one(context, "(", required(is_open_paren));
    consume_space(context, 0);
    Expression *condition = parse_expression(context);
    consume_space(context, 0);
    consume_one(context, ")", required(is_close_paren));
    consume_space(context, 1);
    Statement *block = parse_block_statement(context, TRUE);
    consume_end_of_line(context, TRUE);
    return statement__create_while(location, condition, block);
}

int is_break_keyword(Token *token) {
    return is_keyword(token, "break");
}

Statement *statement__create_break(Source_Location *location) {
    Statement *self = statement__create(STATEMENT__BREAK, location);
    return self;
}

// break
//      : "break" EOL
Statement *parse_break_statement(Context *context) {
    Source_Location *location = consume_one(context, "break", required(is_break_keyword))->location;
    consume_end_of_line(context, TRUE);
    return statement__create_break(location);
}

int is_skip_keyword(Token *token) {
    return is_keyword(token, "skip");
}

Statement *statement__create_skip(Source_Location *location) {
    Statement *self = statement__create(STATEMENT__SKIP, location);
    return self;
}

// skip
//      : "skip" EOL
Statement *parse_skip_statement(Context *context) {
    Source_Location *location = consume_one(context, "skip", required(is_skip_keyword))->location;
    consume_end_of_line(context, TRUE);
    return statement__create_skip(location);
}

int is_return_keyword(Token *token) {
    return is_keyword(token, "return");
}

Statement *statement__create_return(Source_Location *location, Expression *expression) {
    Statement *self = statement__create(STATEMENT__RETURN, location);
    self->return_data.expression = expression;
    return self;
}

// return
//      : "return" expression? EOL
Statement *parse_return_statement(Context *context) {
    Source_Location *location = consume_one(context, "return", required(is_return_keyword))->location;
    if (consume_end_of_line(context, FALSE)) {
        return statement__create_return(location, NULL);
    }
    consume_space(context, 1);
    Expression *expression = parse_expression(context);
    consume_end_of_line(context, TRUE);
    return statement__create_return(location, expression);
}

int is_assign_variant(Token *token) {
    return is_addition_operator(token) || is_multiplication_operator(token);
}

Statement *statement__create_expression(Source_Location *location, Expression *expression) {
    Statement *self = statement__create(STATEMENT__EXPRESSION, location);
    self->expression_data.expression = expression;
    return self;
}

Statement *statement__create_variable(Source_Location *location, Token *name, Type *type, Expression *value, int is_external) {
    Statement *self = statement__create(STATEMENT__VARIABLE, location);
    self->variable_data.name = name;
    self->variable_data.type = type;
    self->variable_data.value = value;
    self->variable_data.is_external = is_external;
    return self;
}

Statement *statement__create_assignment(Source_Location *location, Expression *destination, Token *operator_token, Expression *value) {
    Statement *self = statement__create(STATEMENT__ASSIGNMENT, location);
    self->assignment_data.destination = destination;
    self->assignment_data.operator_token = operator_token;
    self->assignment_data.value = value;
    return self;
}

int is_external_keyword(Token *token) {
    return is_keyword(token, "external");
}

// statement
//      : break
//      | if
//      | loop
//      | while
//      | return
//      | skip
//      | expression ((":" ":" definition) | (":" declaration) | ("=" ("external" | assignment)))?
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

    if (matches_one(context, required(is_while_keyword))) {
        return parse_while_statement(context);
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
        return statement__create_expression(expression->location, expression);
    }

    if (matches_three(context, optional(is_space), required(is_colon), required(is_colon))) {
        consume_space(context, 1);
        consume_two(context, NULL, required(is_colon), required(is_colon));
        consume_space(context, 1);
        if (matches_one(context, required(is_struct_keyword))) {
            if (expression->kind != EXPRESSION__VARIABLE) {
                PANIC(__FILE__, __LINE__, "(%03d,%03d) -- Cannot use expression as struct name", expression->location->line, expression->location->column);
            }
            Token *struct_name = expression->variable_data.name;
            Statement *struct_statement = parse_struct(context, struct_name);
            Type *struct_type = type__create_struct(struct_name->location, struct_statement);
            named_types__add(context->named_types, struct_name->lexeme, struct_type);
            return struct_statement;
        }
        if (expression->kind != EXPRESSION__VARIABLE) {
            PANIC(__FILE__, __LINE__, "(%03d,%03d) -- Cannot use expression as function name", expression->location->line, expression->location->column);
        }
        Token *function_name = expression->variable_data.name;
        Statement *function_statement = parse_function(context, function_name);
        named_functions__add(context->named_functions, function_statement);
        return function_statement;
    }

    if (matches_two(context, optional(is_space), required(is_colon))) {
        Token *variable_name = expression->variable_data.name;
        if (matches_three(context, optional(is_space), required(is_colon), required(is_assign_operator))) {
            consume_space(context, 1);
            consume_two(context, NULL, required(is_colon), required(is_assign_operator));
            consume_space(context, 1);
            Expression *value = parse_expression(context);
            consume_end_of_line(context, TRUE);
            return statement__create_variable(variable_name->location, variable_name, NULL, value, FALSE);
        }
        consume_space(context, 0);
        consume_one(context, NULL, required(is_colon));
        consume_space(context, 1);
        Type *type = parse_type(context);
        if (consume_end_of_line(context, FALSE)) {
            return statement__create_variable(variable_name->location, variable_name, type, NULL, FALSE);
        }
        consume_space(context, 1);
        consume_one(context, NULL, required(is_assign_operator));
        consume_space(context, 1);
        if (consume_one(context, NULL, required(is_external_keyword)) != NULL) {
            consume_end_of_line(context, TRUE);
            return statement__create_variable(variable_name->location, variable_name, type, NULL, TRUE);
        }
        Expression *value = parse_expression(context);
        consume_end_of_line(context, TRUE);
        return statement__create_variable(variable_name->location, variable_name, type, value, FALSE);
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
        return statement__create_assignment(expression->location, expression, operator_token, value);
    }

    consume_space(context, 0);
    PANIC(__FILE__, __LINE__, SOURCE_LOCATION "Unxpected token: %s", SOURCE(CURRENT_TOKEN(context)->location), CURRENT_TOKEN(context)->lexeme->data);
}

Compilation_Unit *parse(Token_List *tokens) {
    List_Iterator tokens_iterator = list__create_iterator(tokens);
    Context *context = context__create(&tokens_iterator);

    Statement_List *statements = parse_statements(context);

    Token *last_token = list__last(tokens);
    return compilation_unit__create(last_token->location->source, context->named_functions, context->named_types, statements);
}
