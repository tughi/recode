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
};

Expression *parse(Token *first) {
    auto parser = Parser{first : first};
    return parser.parse_multiplication_expression();
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

bool is_integer(Token *token) {
    return token->type == Token::INTEGER;
}

bool is_keyword(Token *token) {
    return token->type == Token::KEYWORD;
}

bool is_space(Token *token) {
    return token->type == Token::SPACE;
}

bool is_operator_token(Token *token) {
    return token->type == Token::OTHER && (token->lexeme->data[0] == '/' || token->lexeme->data[0] == '*');
}

// multiplication
//      : unary ( " " ( "/" | "*" ) " " unary )*
Expression *Parser::parse_multiplication_expression() {
    auto expression = this->parse_unary_expression();
    if (expression) {
        while (this->matches(is_space, is_operator_token, is_space)) {
            auto operator_token = this->first->next;
            this->first = operator_token->next->next;
            auto right_expression = this->parse_unary_expression();
            if (right_expression) {
                expression = new Expression{
                    type : Expression::MULTIPLICATION,
                    multiplication : {
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
    return token->type == Token::OTHER && (token->lexeme->data[0] == '!' || token->lexeme->data[0] == '-');
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
                type : Expression::UNARY,
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

// primary
//      : IDENTIFIER
//      | INTEGER
Expression *Parser::parse_primary_expression() {
    if (this->matches(is_integer)) {
        auto value = this->first;
        this->first = value->next;
        return new Expression{
            type : Expression::LITERAL,
            literal : {
                value : value,
            },
        };
    }
    return nullptr;
}
