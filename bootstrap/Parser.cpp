#include "Parser.h"

#include <cstdarg>
#include <iostream>

struct Context {
    Token *next_token;
};

void dump_context(Context *context) {
    std::cout << "Context { next_token: " << context->next_token->lexeme->data << std::endl;
}

bool matches(Token *token, bool (*accepts_first)(Token *)) {
    return (*accepts_first)(token);
}

bool matches(Token *token, bool (*accepts_first)(Token *), bool (*accepts_second)(Token *)) {
    return matches(token, accepts_first) && matches(token->next, accepts_second);
}

bool matches(Token *token, bool (*accepts_first)(Token *), bool (*accepts_second)(Token *), bool (*accepts_third)(Token *)) {
    return matches(token, accepts_first, accepts_second) && matches(token->next->next, accepts_third);
}

bool matches(Token *token, bool (*accepts_first)(Token *), bool (*accepts_second)(Token *), bool (*accepts_third)(Token *), bool (*accepts_fourth)(Token *)) {
    return matches(token, accepts_first, accepts_second, accepts_third) && matches(token->next->next->next, accepts_fourth);
}

Token *consume(Context *context, bool (*accepts_first)(Token *)) {
    auto first_token = context->next_token;
    if (matches(first_token, accepts_first)) {
        context->next_token = first_token->next;
        return first_token;
    }
    return nullptr;
}

Token *consume(Context *context, bool (*accepts_first)(Token *), bool (*accepts_second)(Token *)) {
    auto first_token = context->next_token;
    if (matches(first_token, accepts_first, accepts_second)) {
        context->next_token = first_token->next->next;
        return first_token;
    }
    return nullptr;
}

bool line_contains(Context *context, bool (*accepts_first)(Token *)) {
    auto token = context->next_token;
    while (token->type != Token::END_OF_FILE && token->type != Token::END_OF_FILE) {
        if (matches(token, accepts_first)) {
            return true;
        }
        token = token->next;
    }
    return false;
}

bool is_boolean_literal(Token *token) {
    return token->type == Token::KEYWORD && (token->lexeme->equals("false") || token->lexeme->equals("true"));
}

bool is_character_literal(Token *token) {
    return token->type == Token::CHARACTER;
}

bool is_identifier(Token *token) {
    return token->type == Token::IDENTIFIER;
}

bool is_integer_literal(Token *token) {
    return token->type == Token::INTEGER;
}

bool is_string_literal(Token *token) {
    return token->type == Token::STRING;
}

bool is_open_paren(Token *token) {
    return token->type == Token::OTHER && token->lexeme->equals("(");
}

bool is_close_paren(Token *token) {
    return token->type == Token::OTHER && token->lexeme->equals(")");
}

Expression *parse_expression(Context *context);

// primary
//      : IDENTIFIER
//      | INTEGER
//      | STRING
//      | "false"
//      | "true"
//      | CHARACTER
//      | "(" expression ")"
Expression *parse_primary_expression(Context *context) {
    if (matches(context->next_token, is_identifier)) {
        auto name = context->next_token;
        context->next_token = name->next;
        return new Expression{
            kind : Expression::VARIABLE,
            variable : {
                name : name,
            },
        };
    }
    if (matches(context->next_token, is_integer_literal) || matches(context->next_token, is_string_literal) || matches(context->next_token, is_boolean_literal) || matches(context->next_token, is_character_literal)) {
        auto value = context->next_token;
        context->next_token = value->next;
        return new Expression{
            kind : Expression::LITERAL,
            literal : {
                value : value,
            },
        };
    }
    if (matches(context->next_token, is_open_paren)) {
        context->next_token = context->next_token->next;
        auto expression = parse_expression(context);
        if (expression) {
            if (matches(context->next_token, is_close_paren)) {
                context->next_token = context->next_token->next;
                return expression;
            }
            return nullptr; // TODO: report syntax error
        }
        return nullptr; // TODO: report syntax error
    }
    return nullptr; // TODO: report syntax error
}

bool is_unary_operator(Token *token) {
    return token->type == Token::OTHER && (token->lexeme->equals("!") || token->lexeme->equals("-"));
}

// unary
//      : ("!" | "-") unary
//      | primary
Expression *parse_unary_expression(Context *context) {
    if (matches(context->next_token, is_unary_operator)) {
        auto unary_operator = context->next_token;
        context->next_token = unary_operator->next;
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
    return parse_primary_expression(context);
}

bool is_multiplication_operator(Token *token) {
    return token->type == Token::OTHER && (token->lexeme->equals("*") || token->lexeme->equals("/"));
}

bool is_space(Token *token) {
    return token->type == Token::SPACE;
}

// multiplication
//      : unary ( " " ( "*" | "/" ) " " unary )*
Expression *parse_multiplication_expression(Context *context) {
    auto expression = parse_unary_expression(context);
    if (expression) {
        while (matches(context->next_token, is_space, is_multiplication_operator, is_space)) {
            auto operator_token = context->next_token->next;
            context->next_token = operator_token->next->next;
            auto right_expression = parse_unary_expression(context);
            if (right_expression) {
                expression = new Expression{
                    kind : Expression::BINARY,
                    binary : {
                        operator_token : operator_token,
                        left_expression : expression,
                        right_expression : right_expression,
                    },
                };
            } else {
                return right_expression;
            }
        }
    }
    return expression;
}

bool is_addition_operator(Token *token) {
    return token->type == Token::OTHER && (token->lexeme->equals("+") || token->lexeme->equals("-"));
}

// addition
//      : mutliplication ( " " ( "+" | "-" ) " " multiplication )*
Expression *parse_addition_expression(Context *context) {
    auto expression = parse_multiplication_expression(context);
    if (expression) {
        while (matches(context->next_token, is_space, is_addition_operator, is_space)) {
            auto operator_token = context->next_token->next;
            context->next_token = operator_token->next->next;
            auto right_expression = parse_multiplication_expression(context);
            if (right_expression) {
                expression = new Expression{
                    kind : Expression::BINARY,
                    binary : {
                        operator_token : operator_token,
                        left_expression : expression,
                        right_expression : right_expression,
                    },
                };
            } else {
                return right_expression;
            }
        }
    }
    return expression;
}

bool is_assign_operator(Token *token) {
    return token->type == Token::OTHER && token->lexeme->equals("=");
}

bool is_comparison_operator(Token *token) {
    return token->type == Token::OTHER && (token->lexeme->equals("<") || token->lexeme->equals(">"));
}

// comparison
//      : addition ( " " ( "<" | "<=" | ">" | ">=" ) " " addition )?
Expression *parse_comparison_expression(Context *context) {
    auto expression = parse_addition_expression(context);
    if (expression) {
        if (matches(context->next_token, is_space, is_comparison_operator, is_space) || matches(context->next_token, is_space, is_comparison_operator, is_assign_operator, is_space)) {
            auto operator_token = context->next_token->next;
            if (is_assign_operator(operator_token->next)) {
                operator_token->join_next();
            }
            context->next_token = operator_token->next->next;
            auto right_expression = parse_addition_expression(context);
            if (right_expression) {
                expression = new Expression{
                    kind : Expression::BINARY,
                    binary : {
                        operator_token : operator_token,
                        left_expression : expression,
                        right_expression : right_expression,
                    },
                };
            } else {
                return right_expression;
            }
        }
    }
    return expression;
}

bool is_equality_operator(Token *token) {
    return token->type == Token::OTHER && (token->lexeme->equals("!") || token->lexeme->equals("="));
}

// equality
//      : comparison ( " " ( "!" | "=" ) "=" " " comparison )?
Expression *parse_equality_expression(Context *context) {
    auto expression = parse_comparison_expression(context);
    if (expression) {
        if (matches(context->next_token, is_space, is_equality_operator, is_space) || matches(context->next_token, is_space, is_equality_operator, is_assign_operator, is_space)) {
            auto operator_token = context->next_token->next;
            if (is_assign_operator(operator_token->next)) {
                operator_token->join_next();
            }
            context->next_token = operator_token->next->next;
            auto right_expression = parse_comparison_expression(context);
            if (right_expression) {
                expression = new Expression{
                    kind : Expression::BINARY,
                    binary : {
                        operator_token : operator_token,
                        left_expression : expression,
                        right_expression : right_expression,
                    },
                };
            } else {
                return right_expression;
            }
        }
    }
    return expression;
}

bool is_and_operator(Token *token) {
    return token->type == Token::OTHER && token->lexeme->equals("&");
}

// logic_and
//      : equality ( " " "&" "&" " " equality )*
Expression *parse_logic_and_expression(Context *context) {
    auto expression = parse_equality_expression(context);
    if (expression) {
        while (matches(context->next_token, is_space, is_and_operator, is_and_operator, is_space)) {
            auto operator_token = context->next_token->next;
            operator_token->join_next();
            context->next_token = operator_token->next->next;
            auto right_expression = parse_equality_expression(context);
            if (right_expression) {
                expression = new Expression{
                    kind : Expression::BINARY,
                    binary : {
                        operator_token : operator_token,
                        left_expression : expression,
                        right_expression : right_expression,
                    },
                };
            } else {
                return right_expression;
            }
        }
    }
    return expression;
}

bool is_or_operator(Token *token) {
    return token->type == Token::OTHER && token->lexeme->equals("|");
}

// logic_or
//      : logic_and ( " " "|" "|" " " logic_and )*
Expression *parse_logic_or_expression(Context *context) {
    auto expression = parse_logic_and_expression(context);
    if (expression) {
        while (matches(context->next_token, is_space, is_or_operator, is_or_operator, is_space)) {
            auto operator_token = context->next_token->next;
            operator_token->join_next();
            context->next_token = operator_token->next->next;
            auto right_expression = parse_logic_and_expression(context);
            if (right_expression) {
                expression = new Expression{
                    kind : Expression::BINARY,
                    binary : {
                        operator_token : operator_token,
                        left_expression : expression,
                        right_expression : right_expression,
                    },
                };
            } else {
                return right_expression;
            }
        }
    }
    return expression;
}

// expression
//      : logic_or
Expression *parse_expression(Context *context) {
    return parse_logic_or_expression(context);
}

int consume_space(Context *context) {
    int spaces = 0;
    while (is_space(context->next_token)) {
        spaces += 1;
        context->next_token = context->next_token->next;
    }
    if (spaces != 1) {
        // TODO: warn about incorect space count
    }
    return spaces;
}

bool is_colon(Token *token) {
    return token->type == Token::OTHER && token->lexeme->equals(":");
}

bool is_keyword(Token *token, const char *lexeme) {
    return token->type == Token::KEYWORD && token->lexeme->equals(lexeme);
}

bool is_struct(Token *token) {
    return is_keyword(token, "struct");
}

bool is_open_brace(Token *token) {
    return token->type == Token::OTHER && token->lexeme->equals("{");
}

bool is_close_brace(Token *token) {
    return token->type == Token::OTHER && token->lexeme->equals("}");
}

bool is_end_of_line(Token *token) {
    return token->type == Token::END_OF_LINE;
}

// struct
//      : IDENTIFIER " " ":" ":" "struct" " " "{" <EOL> (ALINGMENT+1 struct_member <EOL>)* ALIGNMENT "}"
Statement *parse_struct(Context *context) {
    auto name = consume(context, is_identifier);
    if (name != nullptr) {
        consume_space(context);
        auto assign_operator = consume(context, is_colon, is_colon);
        if (assign_operator != nullptr) {
            assign_operator->join_next();
            consume_space(context);
            if (consume(context, is_struct)) {
                consume_space(context);
                if (consume(context, is_open_brace)) {
                    consume_space(context);
                    if (consume(context, is_end_of_line)) {
                        // TODO: (ALINGMENT+1 struct_member <EOL>)* ALIGNMENT
                        if (consume(context, is_close_brace)) {
                            return new Statement{
                                kind : Statement::STRUCT_DECLARATION,
                                struct_declaration : {
                                    name : name,
                                }
                            };
                        }
                    }
                }
            }
        }
    }
    return nullptr;
}

// statement
//      | struct <EOL>
//      | procedure <EOL>
//      | assignment <EOL>
//      | procedure_call <EOL>
Statement *parse_statement(Context *context) {
    // TODO: consume alignment
    auto next_token = context->next_token;
    if (line_contains(context, is_struct)) {
        return parse_struct(context);
    }
    return nullptr;
}

Statement *parse(Token *first) {
    auto context = Context{next_token : first};
    return parse_statement(&context);
}
