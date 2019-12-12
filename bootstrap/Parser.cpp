#include "Parser.h"
#include "Logging.h"
#include "Source.h"

struct Context {
    Token *next_token;
    int alignment;
};

#define ALIGNMENT_SIZE TAB_SIZE

struct Matcher {
    bool (*matches)(Token *);
    bool required;

    Matcher(bool (*matches)(Token *), bool required) {
        this->matches = matches;
        this->required = required;
    }
};

#define LOCATION(context) "(" << std::setw(3) << std::setfill('0') << context->next_token->line << "," << std::setw(3) << std::setfill('0') << context->next_token->column << ") -- "

#define NEXT_TOKEN(context) context->next_token->lexeme->data

#define DUMP_CONTEXT(context) INFO(__FILE__, __LINE__, LOCATION(context) << "Token : " << NEXT_TOKEN(context))

#define PANICK() exit(1)

bool _matches_(int source_line, Context *context, Matcher *matchers[]) {
    auto first_token = context->next_token;
    auto index = 0;
    auto token = first_token;
    while (matchers[index] != nullptr) {
        if ((*matchers[index]->matches)(token)) {
            token = token->next;
        } else if (matchers[index]->required) {
            return false;
        }
        index += 1;
    }
    return true;
}

bool _matches_(int source_line, Context *context, Matcher first_matcher) {
    Matcher *matchers[] = {&first_matcher, nullptr};
    return _matches_(source_line, context, matchers);
}

bool _matches_(int source_line, Context *context, Matcher first_matcher, Matcher second_matcher) {
    Matcher *matchers[] = {&first_matcher, &second_matcher, nullptr};
    return _matches_(source_line, context, matchers);
}

bool _matches_(int source_line, Context *context, Matcher first_matcher, Matcher second_matcher, Matcher third_matcher) {
    Matcher *matchers[] = {&first_matcher, &second_matcher, &third_matcher, nullptr};
    return _matches_(source_line, context, matchers);
}

#define matches_one(context, first_matcher) _matches_(__LINE__, context, first_matcher)
#define matches_two(context, first_matcher, second_matcher) _matches_(__LINE__, context, first_matcher, second_matcher)
#define matches_three(context, first_matcher, second_matcher, third_matcher) _matches_(__LINE__, context, first_matcher, second_matcher, third_matcher)

Token *_consume_(int source_line, Context *context, const char *expected, Matcher *matchers[]) {
    auto first_token = context->next_token;
    auto index = 0;
    auto token = first_token;
    while (matchers[index] != nullptr) {
        if ((*matchers[index]->matches)(token)) {
            token = token->next;
        } else if (matchers[index]->required) {
            if (expected != nullptr) {
                ERROR(__FILE__, source_line, LOCATION(context) << "Expected " << expected << " instead of: " << NEXT_TOKEN(context));
                PANICK();
            }
            return nullptr;
        }
        index += 1;
    }
    context->next_token = token;
    return first_token;
}

Token *_consume_(int source_line, Context *context, const char *expected, Matcher first_matcher) {
    Matcher *matchers[] = {&first_matcher, nullptr};
    return _consume_(source_line, context, expected, matchers);
}

Token *_consume_(int source_line, Context *context, const char *expected, Matcher first_matcher, Matcher second_matcher) {
    Matcher *matchers[] = {&first_matcher, &second_matcher, nullptr};
    return _consume_(source_line, context, expected, matchers);
}

Token *_consume_(int source_line, Context *context, const char *expected, Matcher first_matcher, Matcher second_matcher, Matcher third_matcher) {
    Matcher *matchers[] = {&first_matcher, &second_matcher, &third_matcher, nullptr};
    return _consume_(source_line, context, expected, matchers);
}

#define optional(matches) Matcher(matches, false)
#define required(matches) Matcher(matches, true)

#define consume_one(context, expected, first_matcher) _consume_(__LINE__, context, expected, first_matcher)
#define consume_two(context, expected, first_matcher, second_matcher) _consume_(__LINE__, context, expected, first_matcher, second_matcher)
#define consume_three(context, expected, first_matcher, second_matcher, third_matcher) _consume_(__LINE__, context, expected, first_matcher, second_matcher, third_matcher)

bool is_identifier(Token *token) {
    return token->kind == Token::IDENTIFIER;
}

bool is_keyword(Token *token, const char *lexeme) {
    return token->kind == Token::KEYWORD && token->lexeme->equals(lexeme);
}

bool is_literal(Token *token) {
    return token->kind == Token::INTEGER || token->kind == Token::STRING || is_keyword(token, "true") || is_keyword(token, "false") || token->kind == Token::CHARACTER;
}

bool is_open_paren(Token *token) {
    return token->kind == Token::OTHER && token->lexeme->equals("(");
}

bool is_close_paren(Token *token) {
    return token->kind == Token::OTHER && token->lexeme->equals(")");
}

Expression *parse_expression(Context *context);

// primary:
//      IDENTIFIER
//      | INTEGER
//      | STRING
//      | "false"
//      | "true"
//      | CHARACTER
//      | "(" expression ")"
Expression *parse_primary_expression(Context *context) {
    auto name = consume_one(context, nullptr, required(is_identifier));
    if (name != nullptr) {
        return new Expression{
            kind : Expression::VARIABLE,
            variable : {
                name : name,
            },
        };
    }
    auto literal = consume_one(context, nullptr, required(is_literal));
    if (literal != nullptr) {
        return new Expression{
            kind : Expression::LITERAL,
            literal : {
                value : literal,
            },
        };
    }
    if (consume_one(context, nullptr, required(is_open_paren))) {
        auto expression = parse_expression(context);
        consume_one(context, ")", required(is_close_paren));
        return expression; // TODO: return group
    }
    ERROR(__FILE__, __LINE__, LOCATION(context) << "Expected expression instead of: " << NEXT_TOKEN(context));
    PANICK();
}

bool is_space(Token *token) {
    return token->kind == Token::SPACE;
}

int consume_space(int source_line, Context *context, int expected_spaces) {
    auto token = _consume_(__LINE__, context, nullptr, required(is_space));
    int spaces = token != nullptr ? token->space.count : 0;
    if (expected_spaces >= 0 && spaces != expected_spaces) {
        WARNING(__FILE__, source_line, LOCATION(context) << "Consumed " << spaces << " space" << (spaces == 1 ? "" : "s") << " where " << expected_spaces << (expected_spaces == 1 ? " is" : " are") << " expected");
    }
    return spaces;
}

#define consume_space(context, expected_spaces) consume_space(__LINE__, context, expected_spaces)

bool is_assign_operator(Token *token) {
    return token->kind == Token::OTHER && token->lexeme->equals("=");
}

Argument *parse_argument(Context *context) {
    auto name = (Token *)nullptr;
    if (matches_three(context, required(is_identifier), optional(is_space), required(is_assign_operator))) {
        name = consume_one(context, nullptr, required(is_identifier));
        consume_space(context, 1);
        consume_one(context, nullptr, required(is_assign_operator));
        consume_space(context, 1);
    }
    auto value = parse_expression(context);
    return new Argument{
        name : name,
        value : value,
        next : nullptr,
    };
}

bool is_comma(Token *token) {
    return token->kind == Token::OTHER && token->lexeme->equals(",");
}

bool is_dot(Token *token) {
    return token->kind == Token::OTHER && token->lexeme->equals(".");
}

bool is_open_bracket(Token *token) {
    return token->kind == Token::OTHER && token->lexeme->equals("[");
}

bool is_close_bracket(Token *token) {
    return token->kind == Token::OTHER && token->lexeme->equals("]");
}

// call:
//      primary ("(" argument ("," argument)* ")" | "." IDENTIFIER)*
Expression *parse_call_expression(Context *context) {
    Expression *expression = parse_primary_expression(context);
    while (true) {
        if (matches_two(context, optional(is_space), required(is_open_paren))) {
            consume_space(context, 0);
            consume_one(context, nullptr, required(is_open_paren));
            auto first_argument = (Argument *)nullptr;
            if (!matches_two(context, optional(is_space), required(is_close_paren))) {
                auto last_argument = (Argument *)nullptr;
                do {
                    consume_space(context, first_argument == nullptr ? 0 : 1);
                    auto argument = parse_argument(context);
                    if (last_argument != nullptr) {
                        last_argument->next = argument;
                    } else {
                        first_argument = argument;
                    }
                    last_argument = argument;
                    if (matches_two(context, optional(is_space), required(is_comma))) {
                        consume_space(context, 0);
                        consume_one(context, nullptr, required(is_comma));
                    } else {
                        break;
                    }
                } while (true);
            }
            consume_space(context, 0);
            consume_one(context, nullptr, required(is_close_paren));
            expression = new Expression{
                kind : Expression::CALL,
                call : {
                    callee : expression,
                    first_argument : first_argument,
                },
            };
        } else if (matches_two(context, optional(is_space), required(is_dot))) {
            consume_space(context, 0);
            consume_one(context, nullptr, required(is_dot));
            consume_space(context, 0);
            auto name = consume_one(context, nullptr, required(is_identifier));
            expression = new Expression{
                kind : Expression::MEMBER,
                member : {
                    object : expression,
                    name : name,
                },
            };
        } else if (matches_two(context, optional(is_space), required(is_open_bracket))) {
            consume_space(context, 0);
            consume_one(context, nullptr, required(is_open_bracket));
            consume_space(context, 0);
            auto index = parse_expression(context);
            consume_space(context, 0);
            consume_one(context, nullptr, required(is_close_bracket));
            expression = new Expression{
                kind : Expression::ARRAY_ITEM,
                array_item : {
                    array : expression,
                    index : index,
                },
            };
        } else {
            break;
        }
    }
    return expression;
}

bool is_unary_operator(Token *token) {
    return token->kind == Token::OTHER && (token->lexeme->equals("!") || token->lexeme->equals("-"));
}

// unary:
//      ("!" | "-") unary
//      | primary
Expression *parse_unary_expression(Context *context) {
    if (matches_one(context, required(is_unary_operator))) {
        auto unary_operator = consume_one(context, nullptr, required(is_unary_operator));
        auto unary_expression = parse_unary_expression(context);
        if (unary_expression != nullptr) {
            return new Expression{
                kind : Expression::UNARY,
                unary : {
                    operator_token : unary_operator,
                    expression : unary_expression,
                },
            };
        }
        return nullptr;
    }
    return parse_call_expression(context);
}

bool is_multiplication_operator(Token *token) {
    return token->kind == Token::OTHER && (token->lexeme->equals("*") || token->lexeme->equals("/"));
}

// multiplication:
//      unary (("*" | "/") unary)*
Expression *parse_multiplication_expression(Context *context) {
    auto expression = parse_unary_expression(context);
    while (matches_two(context, optional(is_space), required(is_multiplication_operator)) && !matches_three(context, optional(is_space), required(is_multiplication_operator), required(is_assign_operator))) {
        consume_space(context, 1);
        auto operator_token = consume_one(context, nullptr, required(is_multiplication_operator));
        consume_space(context, 1);
        auto right_expression = parse_unary_expression(context);
        expression = new Expression{
            kind : Expression::BINARY,
            binary : {
                operator_token : operator_token,
                left_expression : expression,
                right_expression : right_expression,
            },
        };
    }
    return expression;
}

bool is_addition_operator(Token *token) {
    return token->kind == Token::OTHER && (token->lexeme->equals("+") || token->lexeme->equals("-"));
}

// addition:
//      mutliplication (("+" | "-") multiplication)*
Expression *parse_addition_expression(Context *context) {
    auto expression = parse_multiplication_expression(context);
    while (matches_two(context, optional(is_space), required(is_addition_operator)) && !matches_three(context, optional(is_space), required(is_addition_operator), required(is_assign_operator))) {
        consume_space(context, 1);
        auto operator_token = consume_one(context, nullptr, required(is_addition_operator));
        consume_space(context, 1);
        auto right_expression = parse_multiplication_expression(context);
        expression = new Expression{
            kind : Expression::BINARY,
            binary : {
                operator_token : operator_token,
                left_expression : expression,
                right_expression : right_expression,
            },
        };
    }
    return expression;
}

bool is_comparison_operator(Token *token) {
    return token->kind == Token::OTHER && (token->lexeme->equals("<") || token->lexeme->equals(">"));
}

// comparison:
//      addition (("<" | ">") "="? addition)?
Expression *parse_comparison_expression(Context *context) {
    auto expression = parse_addition_expression(context);
    if (matches_two(context, optional(is_space), required(is_comparison_operator))) {
        consume_space(context, 1);
        auto operator_token = consume_two(context, nullptr, required(is_comparison_operator), required(is_assign_operator));
        if (operator_token != nullptr) {
            operator_token->join_next();
        } else {
            operator_token = consume_one(context, nullptr, required(is_comparison_operator));
        }
        consume_space(context, 1);
        auto right_expression = parse_addition_expression(context);
        return new Expression{
            kind : Expression::BINARY,
            binary : {
                operator_token : operator_token,
                left_expression : expression,
                right_expression : right_expression,
            },
        };
    }
    return expression;
}

bool is_equality_operator(Token *token) {
    return token->kind == Token::OTHER && (token->lexeme->equals("!") || token->lexeme->equals("="));
}

// equality:
//      comparison (("!" | "=") "=" comparison)?
Expression *parse_equality_expression(Context *context) {
    auto expression = parse_comparison_expression(context);
    if (matches_three(context, optional(is_space), required(is_equality_operator), required(is_assign_operator))) {
        consume_space(context, 1);
        auto operator_token = consume_two(context, nullptr, required(is_equality_operator), required(is_assign_operator));
        operator_token->join_next();
        consume_space(context, 1);
        auto right_expression = parse_comparison_expression(context);
        return new Expression{
            kind : Expression::BINARY,
            binary : {
                operator_token : operator_token,
                left_expression : expression,
                right_expression : right_expression,
            },
        };
    }
    return expression;
}

bool is_and_operator(Token *token) {
    return token->kind == Token::OTHER && token->lexeme->equals("&");
}

// logic_and:
//      equality ("&" "&" equality)*
Expression *parse_logic_and_expression(Context *context) {
    auto expression = parse_equality_expression(context);
    while (matches_three(context, optional(is_space), required(is_and_operator), required(is_and_operator))) {
        consume_space(context, 1);
        auto operator_token = consume_two(context, nullptr, required(is_and_operator), required(is_and_operator));
        operator_token->join_next();
        consume_space(context, 1);
        auto right_expression = parse_equality_expression(context);
        expression = new Expression{
            kind : Expression::BINARY,
            binary : {
                operator_token : operator_token,
                left_expression : expression,
                right_expression : right_expression,
            },
        };
    }
    return expression;
}

bool is_or_operator(Token *token) {
    return token->kind == Token::OTHER && token->lexeme->equals("|");
}

// logic_or:
//      logic_and ("|" "|" logic_and)*
Expression *parse_logic_or_expression(Context *context) {
    auto expression = parse_logic_and_expression(context);
    while (matches_three(context, optional(is_space), required(is_or_operator), required(is_or_operator))) {
        consume_space(context, 1);
        auto operator_token = consume_two(context, nullptr, required(is_or_operator), required(is_or_operator));
        operator_token->join_next();
        consume_space(context, 1);
        auto right_expression = parse_logic_and_expression(context);
        expression = new Expression{
            kind : Expression::BINARY,
            binary : {
                operator_token : operator_token,
                left_expression : expression,
                right_expression : right_expression,
            },
        };
    }
    return expression;
}

// expression:
//      logic_or
Expression *parse_expression(Context *context) {
    return parse_logic_or_expression(context);
}

bool is_colon(Token *token) {
    return token->kind == Token::OTHER && token->lexeme->equals(":");
}

bool is_open_brace(Token *token) {
    return token->kind == Token::OTHER && token->lexeme->equals("{");
}

bool is_close_brace(Token *token) {
    return token->kind == Token::OTHER && token->lexeme->equals("}");
}

bool is_hyphen(Token *token) {
    return token->kind == Token::OTHER && token->lexeme->equals("-");
}

bool is_close_angled_bracket(Token *token) {
    return token->kind == Token::OTHER && token->lexeme->equals(">");
}

Type *parse_type(Context *context);

// member:
//      IDENTIFIER ":" type ("=" expression)?
Member *parse_member(Context *context) {
    auto name = consume_one(context, "name", required(is_identifier));
    consume_space(context, 0);
    consume_one(context, ":", required(is_colon));
    consume_space(context, 1);
    auto type = parse_type(context);
    auto default_value = (Expression *)nullptr;
    if (matches_two(context, optional(is_space), required(is_assign_operator))) {
        consume_space(context, 1);
        consume_one(context, "=", required(is_assign_operator));
        consume_space(context, 1);
        default_value = parse_expression(context);
    }
    return new Member{
        name : name,
        type : type,
        default_value : default_value,
        next : nullptr,
    };
}

// comma_separated_members:
//      member ("," member)*
Member *parse_comma_separated_members(Context *context) {
    auto first_member = (Member *)nullptr;
    auto last_member = (Member *)nullptr;
    do {
        consume_space(context, first_member == nullptr ? 0 : 1);
        auto member = parse_member(context);
        if (last_member == nullptr) {
            first_member = member;
        } else {
            last_member->next = member;
        }
        last_member = member;
        consume_space(context, 0);
    } while (consume_one(context, nullptr, required(is_comma)));
    return first_member;
}

bool is_reference_operator(Token *token) {
    return token->kind == Token::OTHER && token->lexeme->equals("@");
}

// type:
//      "@"? (
//          IDENTIFIER
//          | "[" type "]"
//          | "(" comma_separated_members? ")"
//      )
Type *parse_type(Context *context) {
    auto is_reference = matches_one(context, required(is_reference_operator));
    if (is_reference) {
        consume_one(context, nullptr, required(is_reference_operator));
        consume_space(context, 0);
    }
    auto type = (Type *)nullptr;
    if (consume_one(context, nullptr, required(is_open_bracket))) {
        consume_space(context, 0);
        auto item_type = parse_type(context);
        consume_space(context, 0);
        consume_one(context, "]", required(is_close_bracket));
        consume_space(context, 0);
        type = new Type{
            kind : Type::ARRAY,
            array : {
                item_type : item_type,
            },
        };
    } else if (consume_one(context, nullptr, required(is_open_paren))) {
        consume_space(context, 0);
        auto first_member = (Member *)nullptr;
        if (consume_one(context, nullptr, required(is_close_paren)) == nullptr) {
            first_member = parse_comma_separated_members(context);
            consume_one(context, ")", required(is_close_paren));
        }
        if (matches_three(context, optional(is_space), required(is_hyphen), required(is_close_angled_bracket))) {
            consume_space(context, 1);
            consume_two(context, "->", required(is_hyphen), required(is_close_angled_bracket));
            consume_space(context, 1);
            auto return_type = parse_type(context);
            type = new Type{
                kind : Type::PROCEDURE,
                procedure : {
                    first_parameter : first_member,
                    return_type : return_type,
                },
            };
        } else {
            type = new Type{
                kind : Type::TUPLE,
                tuple : {
                    first_member : first_member,
                },
            };
        }
    } else {
        auto name = consume_one(context, "type name", required(is_identifier));
        type = new Type{
            kind : Type::SIMPLE,
            simple : {
                name : name,
            },
        };
    }
    if (is_reference) {
        type = new Type{
            kind : Type::REFERENCE,
            reference : {
                type : type,
            },
        };
    }
    return type;
}

bool is_comment(Token *token) {
    return token->kind == Token::COMMENT;
}

bool is_end_of_line(Token *token) {
    return token->kind == Token::END_OF_LINE;
}

bool is_end_of_file(Token *token) {
    return token->kind == Token::END_OF_FILE;
}

bool _consume_end_of_line_(int source_line, Context *context, bool required) {
    if (matches_three(context, optional(is_space), optional(is_comment), required(is_end_of_line)) || matches_three(context, optional(is_space), optional(is_comment), required(is_end_of_file))) {
        if (matches_two(context, optional(is_space), required(is_comment))) {
            consume_space(context, context->alignment * ALIGNMENT_SIZE);
            consume_one(context, nullptr, required(is_comment));
        } else {
            consume_space(context, 0);
        }
        return consume_one(context, nullptr, required(is_end_of_line));
    }
    if (required) {
        ERROR(__FILE__, source_line, LOCATION(context) << "Expected <EOL> instead of: " << NEXT_TOKEN(context));
        PANICK();
    }
    return false;
}

#define consume_end_of_line(context, required) _consume_end_of_line_(__LINE__, context, required)

bool is_struct_keyword(Token *token) {
    return is_keyword(token, "struct");
}

// struct:
//      "{" EOL (member EOL)* "}" EOL
Statement *parse_struct(Context *context, Expression *name) {
    consume_one(context, "struct", required(is_struct_keyword));
    consume_space(context, 1);
    auto base = (Token *)nullptr;
    if (consume_one(context, nullptr, required(is_colon))) {
        consume_space(context, 1);
        base = consume_one(context, "base struct", required(is_identifier));
        consume_space(context, 1);
    }
    consume_one(context, "{", required(is_open_brace));
    consume_end_of_line(context, true);
    auto first_member = (Member *)nullptr;
    auto last_member = (Member *)nullptr;
    while (!matches_two(context, optional(is_space), required(is_close_brace))) {
        consume_space(context, (context->alignment + 1) * ALIGNMENT_SIZE);
        auto member = parse_member(context);
        consume_end_of_line(context, true);
        if (last_member != nullptr) {
            last_member->next = member;
        } else {
            first_member = member;
        }
        last_member = member;
    }
    consume_space(context, context->alignment * ALIGNMENT_SIZE);
    consume_one(context, "}", required(is_close_brace));
    consume_end_of_line(context, true);
    return new Statement{
        kind : Statement::STRUCT_DEFINITION,
        struct_definition : {
            name : name,
            base : base,
            first_member : first_member,
        },
    };
}

Statement *parse_statement(Context *context);

Statement *parse_statements(Context *context) {
    auto first_statement = (Statement *)nullptr;
    auto last_statement = (Statement *)nullptr;
    do {
        auto statement = parse_statement(context);
        if (statement == nullptr) {
            break;
        }
        statement->next = nullptr;
        if (last_statement != nullptr) {
            last_statement->next = statement;
        } else {
            first_statement = statement;
        }
        last_statement = statement;
    } while (true);
    return first_statement;
}

// procedure:
//      "(" comma_separated_members? ")" ("->" type)? "{" EOL statement* "}" EOL
Statement *parse_procedure(Context *context, Expression *name) {
    consume_one(context, "(", required(is_open_paren));
    consume_space(context, 0);
    auto first_parameter = (Member *)nullptr;
    if (consume_one(context, nullptr, required(is_close_paren)) == nullptr) {
        first_parameter = parse_comma_separated_members(context);
        consume_one(context, ")", required(is_close_paren));
    }
    consume_space(context, 1);
    auto return_type = (Type *)nullptr;
    if (consume_two(context, nullptr, required(is_hyphen), required(is_close_angled_bracket)) != nullptr) {
        consume_space(context, 1);
        return_type = parse_type(context);
        consume_space(context, 1);
    }
    consume_one(context, "{", required(is_open_brace));
    consume_end_of_line(context, true);
    context->alignment += 1;
    auto first_statement = parse_statements(context);
    context->alignment -= 1;
    consume_space(context, context->alignment * ALIGNMENT_SIZE);
    consume_one(context, "}", required(is_close_brace));
    consume_end_of_line(context, true);
    return new Statement{
        kind : Statement::PROCEDURE_DEFINITION,
        procedure_definition : {
            name : name,
            first_parameter : first_parameter,
            return_type : return_type,
            first_statement : first_statement,
        },
    };
}

// block:
//      "{" EOL statement* "}" EOL
Statement *parse_block_statement(Context *context, bool inlined) {
    consume_one(context, "{", required(is_open_brace));
    consume_end_of_line(context, true);
    context->alignment += 1;
    auto first_statement = parse_statements(context);
    context->alignment -= 1;
    consume_space(context, context->alignment * ALIGNMENT_SIZE);
    consume_one(context, "}", required(is_close_brace));
    if (!inlined) {
        consume_end_of_line(context, true);
    }
    return new Statement{
        kind : Statement::BLOCK,
        block : {
            first_statement : first_statement,
        },
    };
}

bool is_if_keyword(Token *token) {
    return is_keyword(token, "if");
}

bool is_else_keyword(Token *token) {
    return is_keyword(token, "else");
}

// return:
//      "if" "(" expression ")" block ("else" block)? EOL
Statement *parse_if_statement(Context *context) {
    consume_one(context, "if", required(is_if_keyword));
    consume_space(context, 1);
    consume_one(context, "(", required(is_open_paren));
    consume_space(context, 0);
    auto condition = parse_expression(context);
    consume_space(context, 0);
    consume_one(context, ")", required(is_close_paren));
    consume_space(context, 1);
    auto true_block = parse_block_statement(context, true);
    auto false_block = (Statement *)nullptr;
    if (matches_two(context, optional(is_space), required(is_else_keyword))) {
        consume_space(context, 1);
        consume_one(context, nullptr, required(is_else_keyword));
        consume_space(context, 1);
        false_block = parse_block_statement(context, true);
    }
    consume_end_of_line(context, true);
    return new Statement{
        kind : Statement::IF,
        if_ : {
            condition : condition,
            true_block : true_block,
            false_block : false_block,
        },
    };
}

bool is_loop_keyword(Token *token) {
    return is_keyword(token, "loop");
}

// loop:
//      "loop" block EOL
Statement *parse_loop_statement(Context *context) {
    consume_one(context, "loop", required(is_loop_keyword));
    consume_space(context, 1);
    auto block = parse_block_statement(context, true);
    consume_end_of_line(context, true);
    return new Statement{
        kind : Statement::LOOP,
        loop : {
            block : block,
        },
    };
}

bool is_break_keyword(Token *token) {
    return is_keyword(token, "break");
}

// break:
//      "break" EOL
Statement *parse_break_statement(Context *context) {
    consume_one(context, "break", required(is_break_keyword));
    consume_end_of_line(context, true);
    return new Statement{
        kind : Statement::BREAK,
    };
}

bool is_skip_keyword(Token *token) {
    return is_keyword(token, "skip");
}

// skip:
//      "skip" EOL
Statement *parse_skip_statement(Context *context) {
    consume_one(context, "skip", required(is_skip_keyword));
    consume_end_of_line(context, true);
    return new Statement{
        kind : Statement::SKIP,
    };
}

bool is_return_keyword(Token *token) {
    return is_keyword(token, "return");
}

// return:
//      "return" expression EOL
Statement *parse_return_statement(Context *context) {
    consume_one(context, "return", required(is_return_keyword));
    consume_space(context, 1);
    auto expression = parse_expression(context);
    consume_end_of_line(context, true);
    return new Statement{
        kind : Statement::RETURN,
        return_expression : expression,
    };
}

bool is_assign_variant(Token *token) {
    return is_addition_operator(token) || is_multiplication_operator(token);
}

// statement:
//      break
//      | if
//      | loop
//      | return
//      | skip
//      | expression ((":" ":" definition) | (":" declaration) | ("=" assignment))?
Statement *parse_statement(Context *context) {
    while (consume_end_of_line(context, false)) {
        // do nothing
    }
    if (matches_one(context, required(is_end_of_file)) || matches_two(context, optional(is_space), required(is_close_brace))) {
        return nullptr;
    }

    consume_space(context, context->alignment * ALIGNMENT_SIZE);

    if (matches_one(context, required(is_open_brace))) {
        return parse_block_statement(context, false);
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

    auto expression = parse_expression(context);
    if (consume_end_of_line(context, false)) {
        return new Statement{
            kind : Statement::EXPRESSION,
            expression : expression,
        };
    }

    if (matches_three(context, optional(is_space), required(is_colon), required(is_colon))) {
        consume_space(context, 1);
        consume_two(context, nullptr, required(is_colon), required(is_colon));
        consume_space(context, 1);
        if (matches_one(context, required(is_struct_keyword))) {
            return parse_struct(context, expression);
        }
        return parse_procedure(context, expression);
    }

    if (matches_two(context, optional(is_space), required(is_colon))) {
        if (matches_three(context, optional(is_space), required(is_colon), required(is_assign_operator))) {
            consume_space(context, 1);
            consume_two(context, nullptr, required(is_colon), required(is_assign_operator));
            consume_space(context, 1);
            auto value = parse_expression(context);
            consume_end_of_line(context, true);
            return new Statement{
                kind : Statement::VARIABLE_DECLARATION,
                variable_declaration : {
                    name : expression,
                    type : nullptr,
                    value : value,
                },
            };
        }
        consume_space(context, 0);
        consume_one(context, nullptr, required(is_colon));
        consume_space(context, 1);
        auto type = parse_type(context);
        consume_space(context, 1);
        consume_one(context, nullptr, required(is_assign_operator));
        consume_space(context, 1);
        auto value = parse_expression(context);
        consume_end_of_line(context, true);
        return new Statement{
            kind : Statement::VARIABLE_DECLARATION,
            variable_declaration : {
                name : expression,
                type : type,
                value : value,
            },
        };
    }

    if (matches_three(context, optional(is_space), optional(is_assign_variant), required(is_assign_operator))) {
        consume_space(context, 1);
        auto operator_token = consume_two(context, nullptr, optional(is_assign_variant), required(is_assign_operator));
        if (is_assign_variant(operator_token)) {
            operator_token->join_next();
        }
        consume_space(context, 1);
        auto value = parse_expression(context);
        consume_end_of_line(context, true);
        return new Statement{
            kind : Statement::ASSIGNMENT,
            assignment : {
                destination : expression,
                operator_token : operator_token,
                value : value,
            },
        };
    }

    consume_space(context, 0);
    ERROR(__FILE__, __LINE__, LOCATION(context) << "Unxpected token: " << NEXT_TOKEN(context));
    PANICK();
}

Statement *parse(Token *first_token) {
    auto context = Context{
        next_token : first_token,
        alignment : 0,
    };
    auto first_statement = parse_statements(&context);
    return first_statement;
}
