#include "Parser.h"
#include "Logging.h"

struct Context {
    Token *next_token;
    int alignment;
};

#define ALIGNMENT_SIZE 4

#define LOCATION(context) "(" << std::setw(3) << std::setfill('0') << context->next_token->line << "," << std::setw(3) << std::setfill('0') << context->next_token->column << ") -- "

#define NEXT_TOKEN(context) context->next_token->lexeme->data

#define DUMP_CONTEXT(context) INFO(LOCATION(context) << std::setw(context->alignment * ALIGNMENT_SIZE) << std::setfill(' ') << "" \
                                                     << "Token : " << NEXT_TOKEN(context))

#define CONSUME_ERROR(context, expected)                                                           \
    ERROR(LOCATION(context) << "Expected " << expected << " instead of: " << NEXT_TOKEN(context)); \
    exit(1)

bool matches_one(Token *token, bool (*accepts)(Token *)) {
    return (*accepts)(token);
}

bool matches(Context *context, bool (*accepts_first)(Token *)) {
    return matches_one(context->next_token, accepts_first);
}

bool matches(Context *context, bool (*accepts_first)(Token *), bool (*accepts_second)(Token *)) {
    return matches(context, accepts_first) && matches_one(context->next_token->next, accepts_second);
}

bool matches(Context *context, bool (*accepts_first)(Token *), bool (*accepts_second)(Token *), bool (*accepts_third)(Token *)) {
    return matches(context, accepts_first, accepts_second) && matches_one(context->next_token->next->next, accepts_third);
}

bool matches(Context *context, bool (*accepts_first)(Token *), bool (*accepts_second)(Token *), bool (*accepts_third)(Token *), bool (*accepts_fourth)(Token *)) {
    return matches(context, accepts_first, accepts_second, accepts_third) && matches_one(context->next_token->next->next->next, accepts_fourth);
}

Token *consume(Context *context, bool (*accepts_first)(Token *)) {
    auto first_token = context->next_token;
    if (matches(context, accepts_first)) {
        context->next_token = first_token->next;
        return first_token;
    }
    return nullptr;
}

Token *consume(Context *context, bool (*accepts_first)(Token *), bool (*accepts_second)(Token *)) {
    auto first_token = context->next_token;
    if (matches(context, accepts_first, accepts_second)) {
        context->next_token = first_token->next->next;
        return first_token;
    }
    return nullptr;
}

bool line_contains(Context *context, bool (*accepts_first)(Token *)) {
    auto token = context->next_token;
    while (token->type != Token::END_OF_FILE && token->type != Token::END_OF_FILE) {
        if (matches_one(token, accepts_first)) {
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
    if (matches(context, is_identifier)) {
        auto name = context->next_token;
        context->next_token = name->next;
        return new Expression{
            kind : Expression::VARIABLE,
            variable : {
                name : name,
            },
        };
    }
    if (matches(context, is_integer_literal) || matches(context, is_string_literal) || matches(context, is_boolean_literal) || matches(context, is_character_literal)) {
        auto value = context->next_token;
        context->next_token = value->next;
        return new Expression{
            kind : Expression::LITERAL,
            literal : {
                value : value,
            },
        };
    }
    if (matches(context, is_open_paren)) {
        context->next_token = context->next_token->next;
        auto expression = parse_expression(context);
        if (expression) {
            if (matches(context, is_close_paren)) {
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
    if (matches(context, is_unary_operator)) {
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
        while (matches(context, is_space, is_multiplication_operator, is_space)) {
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
        while (matches(context, is_space, is_addition_operator, is_space)) {
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
        if (matches(context, is_space, is_comparison_operator, is_space) || matches(context, is_space, is_comparison_operator, is_assign_operator, is_space)) {
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
        if (matches(context, is_space, is_equality_operator, is_space) || matches(context, is_space, is_equality_operator, is_assign_operator, is_space)) {
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
        while (matches(context, is_space, is_and_operator, is_and_operator, is_space)) {
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
        while (matches(context, is_space, is_or_operator, is_or_operator, is_space)) {
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

int consume_space(Context *context, int expected_spaces) {
    int spaces = 0;
    while (is_space(context->next_token)) {
        spaces += 1;
        context->next_token = context->next_token->next;
    }
    if (expected_spaces >= 0 && spaces != expected_spaces) {
        WARNING(LOCATION(context) << "Consumed " << spaces << " space" << (spaces == 1 ? "" : "s") << " where " << expected_spaces << (expected_spaces == 1 ? " is" : " are") << " expected");
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

bool is_open_braket(Token *token) {
    return token->type == Token::OTHER && token->lexeme->equals("[");
}

bool is_close_braket(Token *token) {
    return token->type == Token::OTHER && token->lexeme->equals("]");
}

bool is_comma(Token *token) {
    return token->type == Token::OTHER && token->lexeme->equals(",");
}

bool is_hyphen(Token *token) {
    return token->type == Token::OTHER && token->lexeme->equals("-");
}

bool is_close_angled_bracket(Token *token) {
    return token->type == Token::OTHER && token->lexeme->equals(">");
}

Type *parse_type(Context *context);

// member
//      : IDENTIFIER ":" type ("=" expression)?
Member *parse_member(Context *context) {
    auto name = consume(context, is_identifier);
    if (name == nullptr) {
        CONSUME_ERROR(context, "name");
    }
    consume_space(context, 0);
    if (consume(context, is_colon) == nullptr) {
        CONSUME_ERROR(context, ":");
    }
    consume_space(context, 1);
    auto type = parse_type(context);
    auto lookahead_next_token = context->next_token;
    consume_space(context, -1);
    auto with_default_value = matches(context, is_assign_operator);
    context->next_token = lookahead_next_token;
    Expression *default_value = nullptr;
    if (with_default_value) {
        consume_space(context, 1);
        consume(context, is_assign_operator);
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

// comma_separated_members
//      : member ("," member)*
Member *parse_comma_separated_members(Context *context) {
    Member *first_member = nullptr;
    Member *last_member = nullptr;
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
    } while (consume(context, is_comma));
    return first_member;
}

// type
//      : IDENTIFIER
//      | "[" type "]"
//      | "(" (comma_separated_members)? ")"
Type *parse_type(Context *context) {
    if (consume(context, is_open_braket)) {
        consume_space(context, 0);
        auto item_type = parse_type(context);
        consume_space(context, 0);
        if (consume(context, is_close_braket) == nullptr) {
            CONSUME_ERROR(context, "]");
        }
        consume_space(context, 0);
        return new Type{
            kind : Type::ARRAY,
            array : {
                item_type : item_type,
            },
        };
    } else if (consume(context, is_open_paren)) {
        Member *first_member = nullptr;
        consume_space(context, 0);
        if (consume(context, is_close_paren) == nullptr) {
            first_member = parse_comma_separated_members(context);
            if (consume(context, is_close_paren) == nullptr) {
                CONSUME_ERROR(context, ")");
            }
        }
        auto lookahead_next_token = context->next_token;
        consume_space(context, -1);
        auto is_procedure = matches(context, is_hyphen, is_close_angled_bracket);
        context->next_token = lookahead_next_token;
        if (is_procedure) {
            consume_space(context, 1);
            consume(context, is_hyphen, is_close_angled_bracket);
            consume_space(context, 1);
            auto return_type = parse_type(context);
            return new Type{
                kind : Type::PROCEDURE,
                procedure : {
                    first_parameter : first_member,
                    return_type : return_type,
                },
            };
        }
        return new Type{
            kind : Type::TUPLE,
            tuple : {
                first_member : first_member,
            },
        };
    } else {
        auto name = consume(context, is_identifier);
        if (name == nullptr) {
            CONSUME_ERROR(context, "type name");
        }
        return new Type{
            kind : Type::SIMPLE,
            simple : {
                name : name,
            },
        };
    }
}

bool is_comment(Token *token) {
    return token->type == Token::COMMENT;
}

bool is_end_of_line(Token *token) {
    return token->type == Token::END_OF_LINE;
}

Token *consume_end_of_line(Context *context) {
    consume(context, is_space, is_comment);
    consume(context, is_comment);
    consume_space(context, 0);
    return consume(context, is_end_of_line);
}

// struct
//      : IDENTIFIER "::" "struct" "{" <EOL> (member <EOL>)* "}"
Statement *parse_struct(Context *context) {
    auto name = consume(context, is_identifier);
    if (name == nullptr) {
        CONSUME_ERROR(context, "struct name");
    }
    consume_space(context, 1);
    auto assign_operator = consume(context, is_colon, is_colon);
    if (assign_operator == nullptr) {
        CONSUME_ERROR(context, "::");
    }
    consume_space(context, 1);
    if (consume(context, is_struct) == nullptr) {
        CONSUME_ERROR(context, "struct");
    }
    consume_space(context, 1);
    if (consume(context, is_open_brace) == nullptr) {
        CONSUME_ERROR(context, "{");
    }
    if (consume_end_of_line(context) == nullptr) {
        CONSUME_ERROR(context, "<EOL>");
    }
    Member *first_member = nullptr;
    Member *last_member = nullptr;
    do {
        auto lookahead_next_token = context->next_token;
        consume_space(context, -1);
        auto finish = matches(context, is_close_brace);
        context->next_token = lookahead_next_token;
        if (finish) {
            break;
        }

        consume_space(context, (context->alignment + 1) * ALIGNMENT_SIZE);
        auto member = parse_member(context);
        if (last_member != nullptr) {
            last_member->next = member;
        } else {
            first_member = member;
        }
        last_member = member;
    } while (consume_end_of_line(context));
    consume_space(context, context->alignment * ALIGNMENT_SIZE);
    if (consume(context, is_close_brace) == nullptr) {
        CONSUME_ERROR(context, "}");
    }
    return new Statement{
        kind : Statement::STRUCT_DECLARATION,
        struct_declaration : {
            name : name,
            first_member : first_member,
        },
        next : nullptr,
    };
}

bool is_end_of_file(Token *token) {
    return token->type == Token::END_OF_FILE;
}

Statement *parse_statement(Context *context);

Statement *parse_statements(Context *context) {
    Statement *first_statement = nullptr;
    Statement *last_statement = nullptr;
    while (!matches(context, is_end_of_file)) {
        auto lookahead_next_token = context->next_token;
        consume_space(context, -1);
        auto finish = matches(context, is_close_brace);
        context->next_token = lookahead_next_token;
        if (finish) {
            break;
        }

        auto statement = parse_statement(context);
        if (last_statement != nullptr) {
            last_statement->next = statement;
        } else {
            first_statement = statement;
        }
        last_statement = statement;
    }
    return first_statement;
}

// procedure
//      : IDENTIFIER "::" "(" (comma_separated_members)? ")" ("->" type)? "{" <EOL> statement* "}"
Statement *parse_procedure(Context *context) {
    auto name = consume(context, is_identifier);
    if (name == nullptr) {
        CONSUME_ERROR(context, "procedure name");
    }
    consume_space(context, 1);
    auto assign_operator = consume(context, is_colon, is_colon);
    if (assign_operator == nullptr) {
        CONSUME_ERROR(context, "::");
    }
    consume_space(context, 1);
    if (consume(context, is_open_paren) == nullptr) {
        CONSUME_ERROR(context, "(");
    }
    consume_space(context, 0);
    Member *first_parameter = nullptr;
    if (consume(context, is_close_paren) == nullptr) {
        first_parameter = parse_comma_separated_members(context);
        if (consume(context, is_close_paren) == nullptr) {
            CONSUME_ERROR(context, ")");
        }
    }
    consume_space(context, 1);
    Type *return_type = nullptr;
    if (consume(context, is_hyphen, is_close_angled_bracket) != nullptr) {
        consume_space(context, 1);
        return_type = parse_type(context);
        consume_space(context, 1);
    }
    if (consume(context, is_open_brace) == nullptr) {
        CONSUME_ERROR(context, "{");
    }
    if (consume_end_of_line(context) == nullptr) {
        CONSUME_ERROR(context, "<EOL>");
    }
    context->alignment += 1;
    auto first_statement = parse_statements(context);
    context->alignment -= 1;
    consume_space(context, context->alignment * ALIGNMENT_SIZE);
    if (consume(context, is_close_brace) == nullptr) {
        CONSUME_ERROR(context, "}");
    }
    return new Statement{
        kind : Statement::PROCEDURE_DECLARATION,
        procedure_declaration : {
            name : name,
            first_parameter : first_parameter,
            return_type : return_type,
            first_statement : first_statement,
        },
        next : nullptr,
    };
}

bool is_keyword_return(Token *token) {
    return is_keyword(token, "return");
}

// return
//      : "return" expression <EOL>
Statement *parse_return_statement(Context *context) {
    if (consume(context, is_keyword_return) == nullptr) {
        CONSUME_ERROR(context, "return");
    }
    consume_space(context, 1);
    auto expression = parse_expression(context);
    if (consume_end_of_line(context) == nullptr) {
        CONSUME_ERROR(context, "<EOL>");
    }
    return new Statement{
        kind : Statement::RETURN,
        return_expression : expression,
        next : nullptr,
    };
}

// statement
//      : struct <EOL>
//      | procedure <EOL>
//      | assignment <EOL>
//      | procedure_call <EOL>
Statement *parse_statement(Context *context) {
    do {
        consume_space(context, context->alignment * ALIGNMENT_SIZE);
    } while (consume_end_of_line(context));

    if (matches(context, is_keyword_return)) {
        return parse_return_statement(context);
    }

    // TODO: parse other statements

    DUMP_CONTEXT(context);

    auto next_token = context->next_token;
    if (line_contains(context, is_struct)) {
        return parse_struct(context);
    } else if (line_contains(context, is_open_brace)) {
        return parse_procedure(context);
    }
    return nullptr;
}

Statement *parse(Token *first_token) {
    auto context = Context{
        next_token : first_token,
        alignment : 0,
    };
    auto first_statement = parse_statements(&context);
    return first_statement;
}
