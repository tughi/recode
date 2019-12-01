#include "Parser.h"

#include <cstdarg>
#include <iostream>

using namespace std;

struct Parser {
    Token *first;

    bool matches(bool (*)(Token *));
    bool matches(bool (*)(Token *), bool (*)(Token *));
    bool matches(bool (*)(Token *), bool (*)(Token *), bool (*)(Token *));
    bool matches(bool (*)(Token *), bool (*)(Token *), bool (*)(Token *), bool (*)(Token *));

    bool expect_integer();

    Expression *parse_primary_expression();
    Expression *parse_unary_expression();
    Expression *parse_multiplication_expression();
    Expression *parse_addition_expression();
    Expression *parse_comparison_expression();
    Expression *parse_equality_expression();
    Expression *parse_logic_and_expression();
    Expression *parse_logic_or_expression();
    Expression *parse_expression();
};

Expression *parse(Token *first) {
    auto parser = Parser{first : first};
    return parser.parse_expression();
}

bool Parser::matches(bool (*accepts_first)(Token *)) {
    return this->matches(accepts_first, nullptr);
}

bool Parser::matches(bool (*accepts_first)(Token *), bool (*accepts_second)(Token *)) {
    return this->matches(accepts_first, accepts_second, nullptr);
}

bool Parser::matches(bool (*accepts_first)(Token *), bool (*accepts_second)(Token *), bool (*accepts_third)(Token *)) {
    return this->matches(accepts_first, accepts_second, accepts_third, nullptr);
}

bool Parser::matches(bool (*accepts_first)(Token *), bool (*accepts_second)(Token *), bool (*accepts_third)(Token *), bool (*accepts_fourth)(Token *)) {
    Token *first = this->first;
    if ((*accepts_first)(first)) {
        if (accepts_second == nullptr) {
            return true;
        }
        Token *second = first->next;
        if ((*accepts_second)(second)) {
            if (accepts_third == nullptr) {
                return true;
            }
            Token *third = second->next;
            if ((*accepts_third)(third)) {
                if (accepts_fourth == nullptr) {
                    return true;
                }
                Token *fourth = third->next;
                if ((*accepts_fourth)(fourth)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool is_identifier(Token *token) {
    return token->type == Token::IDENTIFIER;
}

bool is_keyword(Token *token) {
    return token->type == Token::KEYWORD;
}

bool is_space(Token *token) {
    return token->type == Token::SPACE;
}

bool is_assign_operator(Token *token) {
    return token->type == Token::OTHER && token->lexeme->equals("=");
}

// expression
//      : logic_or
Expression *Parser::parse_expression() {
    return this->parse_logic_or_expression();
}

bool is_or_operator(Token *token) {
    return token->type == Token::OTHER && token->lexeme->equals("|");
}

// logic_or
//      : logic_and ( " " "|" "|" " " logic_and )*
Expression *Parser::parse_logic_or_expression() {
    auto expression = this->parse_logic_and_expression();
    if (expression) {
        while (this->matches(is_space, is_or_operator, is_or_operator, is_space)) {
            auto operator_token = this->first->next;
            operator_token->join_next();
            this->first = operator_token->next->next;
            auto right_expression = this->parse_logic_and_expression();
            if (right_expression) {
                expression = new Expression{
                    expression_type : Expression::BINARY,
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
Expression *Parser::parse_logic_and_expression() {
    auto expression = this->parse_equality_expression();
    if (expression) {
        while (this->matches(is_space, is_and_operator, is_and_operator, is_space)) {
            auto operator_token = this->first->next;
            operator_token->join_next();
            this->first = operator_token->next->next;
            auto right_expression = this->parse_equality_expression();
            if (right_expression) {
                expression = new Expression{
                    expression_type : Expression::BINARY,
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
Expression *Parser::parse_equality_expression() {
    auto expression = this->parse_comparison_expression();
    if (expression) {
        if (this->matches(is_space, is_equality_operator, is_space) || this->matches(is_space, is_equality_operator, is_assign_operator, is_space)) {
            auto operator_token = this->first->next;
            if (is_assign_operator(operator_token->next)) {
                operator_token->join_next();
            }
            this->first = operator_token->next->next;
            auto right_expression = this->parse_comparison_expression();
            if (right_expression) {
                expression = new Expression{
                    expression_type : Expression::BINARY,
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

bool is_comparison_operator(Token *token) {
    return token->type == Token::OTHER && (token->lexeme->equals("<") || token->lexeme->equals(">"));
}

// comparison
//      : addition ( " " ( "<" | "<=" | ">" | ">=" ) " " addition )?
Expression *Parser::parse_comparison_expression() {
    auto expression = this->parse_addition_expression();
    if (expression) {
        if (this->matches(is_space, is_comparison_operator, is_space) || this->matches(is_space, is_comparison_operator, is_assign_operator, is_space)) {
            auto operator_token = this->first->next;
            if (is_assign_operator(operator_token->next)) {
                operator_token->join_next();
            }
            this->first = operator_token->next->next;
            auto right_expression = this->parse_addition_expression();
            if (right_expression) {
                expression = new Expression{
                    expression_type : Expression::BINARY,
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
Expression *Parser::parse_addition_expression() {
    auto expression = this->parse_multiplication_expression();
    if (expression) {
        while (this->matches(is_space, is_addition_operator, is_space)) {
            auto operator_token = this->first->next;
            this->first = operator_token->next->next;
            auto right_expression = this->parse_multiplication_expression();
            if (right_expression) {
                expression = new Expression{
                    expression_type : Expression::BINARY,
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

bool is_multiplication_operator(Token *token) {
    return token->type == Token::OTHER && (token->lexeme->equals("*") || token->lexeme->equals("/"));
}

// multiplication
//      : unary ( " " ( "*" | "/" ) " " unary )*
Expression *Parser::parse_multiplication_expression() {
    auto expression = this->parse_unary_expression();
    if (expression) {
        while (this->matches(is_space, is_multiplication_operator, is_space)) {
            auto operator_token = this->first->next;
            this->first = operator_token->next->next;
            auto right_expression = this->parse_unary_expression();
            if (right_expression) {
                expression = new Expression{
                    expression_type : Expression::BINARY,
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

bool is_unary_operator(Token *token) {
    return token->type == Token::OTHER && (token->lexeme->equals("!") || token->lexeme->equals("-"));
}

// unary
//      : ("!" | "-") unary
//      | primary
Expression *Parser::parse_unary_expression() {
    if (this->matches(is_unary_operator)) {
        auto unary_operator = first;
        this->first = unary_operator->next;
        auto unary_expression = this->parse_unary_expression();
        if (unary_expression != nullptr) {
            return new Expression{
                expression_type : Expression::UNARY,
                unary : {
                    operator_token : unary_operator,
                    expression : unary_expression,
                },
            };
        }
        return nullptr;
    }
    return this->parse_primary_expression();
}

bool is_boolean_literal(Token *token) {
    return token->type == Token::KEYWORD && (token->lexeme->equals("false") || token->lexeme->equals("true"));
}

bool is_char_literal(Token *token) {
    return token->type == Token::CHARACTER;
}

bool is_integer(Token *token) {
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

// primary
//      : IDENTIFIER
//      | INTEGER
//      | STRING
//      | "false"
//      | "true"
//      | CHARACTER
//      | "(" expression ")"
Expression *Parser::parse_primary_expression() {
    if (this->matches(is_identifier)) {
        auto name = this->first;
        this->first = name->next;
        return new Expression{
            expression_type : Expression::VARIABLE,
            variable : {
                name : name,
            },
        };
    }
    if (this->matches(is_integer) || this->matches(is_string_literal) || this->matches(is_boolean_literal) || this->matches(is_char_literal)) {
        auto value = this->first;
        this->first = value->next;
        return new Expression{
            expression_type : Expression::LITERAL,
            literal : {
                value : value,
            },
        };
    }
    if (this->matches(is_open_paren)) {
        this->first = this->first->next;
        auto expression = this->parse_expression();
        if (expression) {
            if (this->matches(is_close_paren)) {
                this->first = this->first->next;
                return expression;
            }
            return nullptr; // TODO: report syntax error
        }
        return nullptr; // TODO: report syntax error
    }
    return nullptr; // TODO: report syntax error
}
