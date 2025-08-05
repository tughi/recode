#include "Parser.h"
#include "File.h"
#include "Scanner.h"

typedef struct Parser {
    String *project_dir;
    Scanner *scanner;
    Parsed_Source *parsed_source;
    uint16_t current_identation;
} Parser;

Token *Parser__peek_token(Parser *self, uint8_t offset) {
    return Scanner__peek_token(self->scanner, offset);
}

bool Parser__matches_three(Parser *self, bool (*first_is)(struct Token *token), bool first_required, bool (*second_is)(Token *token), bool second_required, bool (*third_is)(Token *token)) {
    uint8_t peek_offset = 0;
    if (first_is(Parser__peek_token(self, peek_offset))) {
        peek_offset = peek_offset + 1;
    } else if (first_required) {
        return false;
    }
    if (second_is != NULL) {
        if (second_is(Parser__peek_token(self, peek_offset))) {
            peek_offset = peek_offset + 1;
        } else if (second_required) {
            return false;
        }
    }
    if (third_is != NULL) {
        return third_is(Parser__peek_token(self, peek_offset));
    }
    return true;
}

bool Parser__matches_two(Parser *self, bool (*first_is)(Token *token), bool first_required, bool (*second_is)(Token *token)) {
    return Parser__matches_three(self, first_is, first_required, second_is, true, NULL);
}

bool Parser__matches_one(Parser *self, bool (*first_is)(Token *token)) {
    return Parser__matches_two(self, first_is, true, NULL);
}

bool Parser__matches_end_of_line(Parser *self) {
    return Parser__matches_three(self, Token__is_space, false, Token__is_comment, false, Token__is_end_of_line);
}

Token *Parser__consume_token(Parser *self, bool (*check)(Token *token)) {
    if (Parser__matches_one(self, check)) {
        Token *token = self->scanner->current_token;
        Scanner__next_token(self->scanner);
        return token;
    }
    pWriter__begin_location_message(stderr_writer, self->scanner->current_token->location, WRITER_STYLE__ERROR);
    pWriter__write__cstring(stderr_writer, "Unexpected token");
    pWriter__end_location_message(stderr_writer);
    panic();
}

void Parser__consume_comment(Parser *self) {
    Parser__consume_token(self, Token__is_comment);
}

void Parser__consume_space(Parser *self, uint16_t count) {
    if (Parser__matches_one(self, Token__is_space)) {
        Space_Token *token = (Space_Token *)Parser__consume_token(self, Token__is_space);
        if (token->count != count) {
            pWriter__begin_location_message(stderr_writer, self->scanner->current_token->location, WRITER_STYLE__WARNING);
            pWriter__write__cstring(stderr_writer, "Consumed ");
            pWriter__write__int64(stderr_writer, token->count);
            pWriter__write__cstring(stderr_writer, " spaces where ");
            pWriter__write__int64(stderr_writer, count);
            pWriter__write__cstring(stderr_writer, " were expected");
            pWriter__end_location_message(stderr_writer);
        }
    } else if (count > 0) {
        pWriter__begin_location_message(stderr_writer, self->scanner->current_token->location, WRITER_STYLE__WARNING);
        pWriter__write__cstring(stderr_writer, "Consumed 0 spaces where ");
        pWriter__write__int64(stderr_writer, count);
        pWriter__write__cstring(stderr_writer, " were expected");
        pWriter__end_location_message(stderr_writer);
    }
}

void Parser__consume_end_of_line(Parser *self) {
    if (Parser__matches_two(self, Token__is_space, false, Token__is_comment)) {
        Parser__consume_space(self, 1);
        Parser__consume_comment(self);
    } else {
        Parser__consume_space(self, 0);
    }
    Token *token = Parser__consume_token(self, Token__is_end_of_line);
    if (Token__is_end_of_file(token)) {
        pWriter__begin_location_message(stderr_writer, token->location, WRITER_STYLE__WARNING);
        pWriter__write__cstring(stderr_writer, "Unexpected end of file");
        pWriter__end_location_message(stderr_writer);
    }
}

bool Parser__consume_empty_line(Parser *self) {
    if (Parser__matches_one(self, Token__is_end_of_file)) {
        return false;
    }
    if (Parser__matches_three(self, Token__is_space, false, Token__is_comment, false, Token__is_end_of_line)) {
        if (Parser__matches_two(self, Token__is_space, false, Token__is_comment)) {
            Parser__consume_space(self, self->current_identation * 4);
            Parser__consume_comment(self);
        } else {
            Parser__consume_space(self, 0);
        }
        Parser__consume_token(self, Token__is_end_of_line);
        return true;
    }
    return false;
}

Parsed_Block_Statement *Parser__parse_block_statement(Parser *self);
Parsed_Call_Argument *Parser__parse_call_arguments(Parser *self);
Parsed_Expression *Parser__parse_expression(Parser *self);
Parsed_Type *Parser__parse_type(Parser *self);

/*
primary_expression
    | "alloc" expression
    | "false"
    | "null"
    | "true"
    | "try" expression "else" ( expression | block_statement )
    | CHARACTER
    | IDENTIFIER
    | INTEGER ( "i8" | "i16" | "i32" | "i64" | "isize" | "u8" | "u16" | "u32" | "u64" | "usize" )?
    | STRING
    | "(" expression ")"
*/
Parsed_Expression *Parser__parse_primary_expression(Parser *self) {
    if (Parser__matches_one(self, Token__is_alloc)) {
        Token *first_token = Parser__consume_token(self, Token__is_alloc);
        Parser__consume_space(self, 1);
        Parsed_Expression *expression = Parser__parse_expression(self);
        return (Parsed_Expression *)Parsed_Alloc_Expression__create(Source_Location__merge(first_token->location, expression->location), expression);
    }
    if (Parser__matches_one(self, Token__is_null)) {
        return (Parsed_Expression *)Parsed_Null_Expression__create(Parser__consume_token(self, Token__is_null));
    }
    if (Parser__matches_one(self, Token__is_false)) {
        return (Parsed_Expression *)Parsed_Bool_Expression__create(Parser__consume_token(self, Token__is_false), false);
    }
    if (Parser__matches_one(self, Token__is_true)) {
        return (Parsed_Expression *)Parsed_Bool_Expression__create(Parser__consume_token(self, Token__is_true), true);
    }
    if (Parser__matches_one(self, Token__is_try)) {
        Token *first_token = Parser__consume_token(self, Token__is_try);
        Parser__consume_space(self, 1);
        Parsed_Expression *try_expression = Parser__parse_expression(self);
        Parser__consume_space(self, 1);
        Parser__consume_token(self, Token__is_else);
        Parser__consume_space(self, 1);
        Parsed_Expression *else_expression;
        if (Parser__matches_one(self, Token__is_opening_brace)) {
            Parsed_Block_Statement *else_block = Parser__parse_block_statement(self);
            else_expression = (Parsed_Expression *)Parsed_Block_Expression__create(else_block);
        } else {
            else_expression = Parser__parse_expression(self);
        }
        return (Parsed_Expression *)Parsed_Try_Expression__create(Source_Location__merge(first_token->location, else_expression->location), try_expression, else_expression);
    }
    if (Parser__matches_one(self, Token__is_identifier)) {
        return (Parsed_Expression *)Parsed_Symbol_Expression__create(Parser__consume_token(self, Token__is_identifier));
    }
    if (Parser__matches_one(self, Token__is_integer)) {
        Integer_Token *integer_token = (Integer_Token *)Parser__consume_token(self, Token__is_integer);
        Parsed_Named_Type *integer_type = NULL;
        Token *next_token = Parser__peek_token(self, 0);
        if (Token__is_identifier(next_token)) {
            if (next_token->lexeme->data[0] == 'i' || next_token->lexeme->data[0] == 'u') {
                if (next_token->lexeme->length == 2 && next_token->lexeme->data[1] == '8') {
                    integer_type = Parsed_Named_Type__create(NULL, Parser__consume_token(self, Token__is_identifier));
                } else if (next_token->lexeme->length == 3) {
                    if (next_token->lexeme->data[1] == '1' && next_token->lexeme->data[2] == '6') {
                        integer_type = Parsed_Named_Type__create(NULL, Parser__consume_token(self, Token__is_identifier));
                    } else if (next_token->lexeme->data[1] == '3' && next_token->lexeme->data[2] == '2') {
                        integer_type = Parsed_Named_Type__create(NULL, Parser__consume_token(self, Token__is_identifier));
                    } else if (next_token->lexeme->data[1] == '6' && next_token->lexeme->data[2] == '4') {
                        integer_type = Parsed_Named_Type__create(NULL, Parser__consume_token(self, Token__is_identifier));
                    }
                } else if (next_token->lexeme->length == 5) {
                    if (next_token->lexeme->data[1] == 's' && next_token->lexeme->data[2] == 'i' && next_token->lexeme->data[3] == 'z' && next_token->lexeme->data[4] == 'e') {
                        integer_type = Parsed_Named_Type__create(NULL, Parser__consume_token(self, Token__is_identifier));
                    }
                }
            }
        }
        return (Parsed_Expression *)Parsed_Integer_Expression__create(integer_token, integer_type);
    }
    if (Parser__matches_one(self, Token__is_character)) {
        return (Parsed_Expression *)Parsed_Character_Expression__create((Character_Token *)Parser__consume_token(self, Token__is_character));
    }
    if (Parser__matches_one(self, Token__is_string)) {
        return (Parsed_Expression *)Parsed_String_Expression__create((String_Token *)Parser__consume_token(self, Token__is_string));
    }
    if (Parser__matches_one(self, Token__is_opening_paren)) {
        Token *first_token = Parser__consume_token(self, Token__is_opening_paren);
        Parser__consume_space(self, 0);
        Parsed_Expression *expression = Parser__parse_expression(self);
        Parser__consume_space(self, 0);
        Token *last_token = Parser__consume_token(self, Token__is_closing_paren);
        return (Parsed_Expression *)Parsed_Group_Expression__create(Source_Location__merge(first_token->location, last_token->location), expression);
    }
    pWriter__begin_location_message(stderr_writer, self->scanner->current_token->location, WRITER_STYLE__ERROR);
    pWriter__write__cstring(stderr_writer, "Unexpected token");
    pWriter__end_location_message(stderr_writer);
    panic();
}

/*
call_argument
    | ( IDENTIFIER ":" )? expression
*/
Parsed_Call_Argument *Parser__parse_call_argument(Parser *self) {
    Identifier_Token *argument_name = NULL;
    if (Parser__matches_three(self, Token__is_identifier, true, Token__is_space, false, Token__is_colon)) {
        argument_name = (Identifier_Token *)Parser__consume_token(self, Token__is_identifier);
        Parser__consume_space(self, 0);
        Parser__consume_token(self, Token__is_colon);
        Parser__consume_space(self, 1);
    }
    Parsed_Expression *argument_expression = Parser__parse_expression(self);
    Source_Location argument_location;
    if (argument_name != NULL) {
        argument_location = Source_Location__merge(argument_name->super.location, argument_expression->location);
    } else {
        argument_location = argument_expression->location;
    }
    return Parsed_Call_Argument__create(argument_location, argument_name, argument_expression);
}

/*
call_arguments
    | call_argument ( ( "," | <EOL> ) call_argument )*
*/
Parsed_Call_Argument *Parser__parse_call_arguments(Parser *self) {
    Parsed_Call_Argument *first_argument = NULL;
    Parsed_Call_Argument *last_argument = NULL;

    bool multiline = false;
    int space_before_argument_list = 0;

    if (Parser__matches_end_of_line(self)) {
        Parser__consume_space(self, 0);
        multiline = true;
        self->current_identation = self->current_identation + 1;
        space_before_argument_list = self->current_identation * 4;
        while (Parser__consume_empty_line(self)) {
            /* ignored */
        }
    }

    while (!Parser__matches_two(self, Token__is_space, false, Token__is_closing_paren)) {
        Parser__consume_space(self, space_before_argument_list);

        Parsed_Call_Argument *argument = Parser__parse_call_argument(self);
        if (last_argument == NULL) {
            first_argument = argument;
        } else {
            last_argument->next_argument = argument;
        }
        last_argument = argument;

        while (Parser__matches_two(self, Token__is_space, false, Token__is_comma)) {
            Parser__consume_space(self, 0);
            Parser__consume_token(self, Token__is_comma);
            Parser__consume_space(self, 1);
            argument = Parser__parse_call_argument(self);
            last_argument->next_argument = argument;
            last_argument = argument;
        }

        if (Parser__matches_end_of_line(self)) {
            Parser__consume_end_of_line(self);
            if (!multiline) {
                pWriter__begin_location_message(stderr_writer, first_argument->location, WRITER_STYLE__WARNING);
                pWriter__write__cstring(stderr_writer, "Multi-line argument list must start on a new line");
                pWriter__end_location_message(stderr_writer);
                multiline = true;
                self->current_identation = self->current_identation + 1;
                space_before_argument_list = self->current_identation * 4;
            }
        } else if (multiline && Parser__matches_two(self, Token__is_space, false, Token__is_closing_paren)) {
            pWriter__begin_location_message(stderr_writer, self->scanner->current_token->location, WRITER_STYLE__WARNING);
            pWriter__write__cstring(stderr_writer, "Multi-line argument list must end on a new line");
            pWriter__end_location_message(stderr_writer);
            multiline = false;
            self->current_identation = self->current_identation - 1;
        }

        if (multiline) {
            while (Parser__consume_empty_line(self)) {
                /* ignored */
            }
        }
    }

    if (multiline) {
        self->current_identation = self->current_identation - 1;
        Parser__consume_space(self, self->current_identation * 4);
    }

    return first_argument;
}

Parsed_Type_Argument *Parser__parse_type_arguments(Parser *self, Source_Location *type_location);

/*
access_expression
    | primary_expression (
        | "." (
            | "^"
            | "as" "(" type ")"
            | IDENTIFIER
        )
        | "(" call_arguments ")"
        | "[" expression "]"
        | "<" type_argument ( "," type_argument )* ">"
    )*
*/
Parsed_Expression *Parser__parse_access_expression(Parser *self) {
    Parsed_Expression *expression = Parser__parse_primary_expression(self);
    while (true) {
        Parsed_Expression *old_expression = expression;
        if (Parser__matches_two(self, Token__is_space, false, Token__is_dot)) {
            Parser__consume_space(self, 0);
            Parser__consume_token(self, Token__is_dot);
            Parser__consume_space(self, 0);
            if (Parser__matches_one(self, Token__is_caret)) {
                Token *last_token = Parser__consume_token(self, Token__is_caret);
                expression = (Parsed_Expression *)Parsed_Dereference_Expression__create(Source_Location__merge(expression->location, last_token->location), expression);
            } else if (Parser__matches_one(self, Token__is_as)) {
                Parser__consume_token(self, Token__is_as);
                Parser__consume_space(self, 0);
                Parser__consume_token(self, Token__is_opening_paren);
                Parser__consume_space(self, 0);
                Parsed_Type *type = Parser__parse_type(self);
                Parser__consume_space(self, 0);
                Token *last_token = Parser__consume_token(self, Token__is_closing_paren);
                expression = (Parsed_Expression *)Parsed_Cast_Expression__create(Source_Location__merge(expression->location, last_token->location), expression, type);
            } else {
                Token *name = Parser__consume_token(self, Token__is_identifier);
                expression = (Parsed_Expression *)Parsed_Member_Access_Expression__create(expression, name);
            }
        }
        if (Parser__matches_two(self, Token__is_space, false, Token__is_opening_paren)) {
            Parser__consume_space(self, 0);
            Parser__consume_token(self, Token__is_opening_paren);
            Parsed_Call_Argument *call_arguments = Parser__parse_call_arguments(self);
            Parser__consume_space(self, 0);
            Token *last_token = Parser__consume_token(self, Token__is_closing_paren);
            expression = (Parsed_Expression *)Parsed_Call_Expression__create(Source_Location__merge(expression->location, last_token->location), expression, call_arguments);
        }
        if (Parser__matches_two(self, Token__is_space, false, Token__is_opening_bracket)) {
            Parser__consume_space(self, 0);
            Parser__consume_token(self, Token__is_opening_bracket);
            Parser__consume_space(self, 0);
            Parsed_Expression *index_expression = Parser__parse_expression(self);
            Parser__consume_space(self, 0);
            Token *last_token = Parser__consume_token(self, Token__is_closing_bracket);
            expression = (Parsed_Expression *)Parsed_Array_Access_Expression__create(Source_Location__merge(expression->location, last_token->location), expression, index_expression);
        }
        if (Parser__matches_one(self, Token__is_less_than)) {
            Source_Location type_specialization_location = expression->location;
            Parsed_Type_Argument *first_type_argument = Parser__parse_type_arguments(self, &type_specialization_location);
            expression = (Parsed_Expression *)Parsed_Type_Specialization_Expression__create(Source_Location__merge(expression->location, type_specialization_location), expression, first_type_argument);
        }
        if (old_expression == expression) {
            break;
        }
    }
    return expression;
}

/*
unary_expression
    | "-" unary_expression
    | "not" unary_expression
    | "^" unary_expression
    | "sizeof" "(" type ")"
    | access_expression
*/
Parsed_Expression *Parser__parse_unary_expression(Parser *self) {
    if (Parser__matches_one(self, Token__is_minus)) {
        Token *first_token = Parser__consume_token(self, Token__is_minus);
        Parser__consume_space(self, 0);
        Parsed_Expression *expression = Parser__parse_unary_expression(self);
        return (Parsed_Expression *)Parsed_Minus_Expression__create(Source_Location__merge(first_token->location, expression->location), expression);
    }
    if (Parser__matches_one(self, Token__is_not)) {
        Token *first_token = Parser__consume_token(self, Token__is_not);
        Parser__consume_space(self, 1);
        Parsed_Expression *expression = Parser__parse_unary_expression(self);
        return (Parsed_Expression *)Parsed_Not_Expression__create(Source_Location__merge(first_token->location, expression->location), expression);
    }
    if (Parser__matches_one(self, Token__is_caret)) {
        Token *first_token = Parser__consume_token(self, Token__is_caret);
        Parser__consume_space(self, 0);
        Parsed_Expression *expression = Parser__parse_unary_expression(self);
        return (Parsed_Expression *)Parsed_Address_Of_Expression__create(Source_Location__merge(first_token->location, expression->location), expression);
    }
    if (Parser__matches_one(self, Token__is_sizeof)) {
        Token *first_token = Parser__consume_token(self, Token__is_sizeof);
        Parser__consume_space(self, 0);
        Parser__consume_token(self, Token__is_opening_paren);
        Parser__consume_space(self, 0);
        Parsed_Type *type = Parser__parse_type(self);
        Parser__consume_space(self, 0);
        Token *last_token = Parser__consume_token(self, Token__is_closing_paren);
        return (Parsed_Expression *)Parsed_Sizeof_Expression__create(Source_Location__merge(first_token->location, last_token->location), type);
    }
    return Parser__parse_access_expression(self);
}

bool Token__is_asterisk_or_slash(Token *self) {
    return Token__is_asterisk(self) || Token__is_slash(self);
}

// multiplicative_expression
//  | unary_expression ( ( "*" | "/" | "//" ) unary_expression )*
Parsed_Expression *Parser__parse_multiplicative_expression(Parser *self) {
    Parsed_Expression *expression = Parser__parse_unary_expression(self);
    while (Parser__matches_two(self, Token__is_space, false, Token__is_asterisk_or_slash)) {
        Parser__consume_space(self, 1);
        if (Parser__matches_one(self, Token__is_asterisk)) {
            Parser__consume_token(self, Token__is_asterisk);
            Parser__consume_space(self, 1);
            Parsed_Expression *right_expression = Parser__parse_unary_expression(self);
            expression = (Parsed_Expression *)Parsed_Multiply_Expression__create(expression, right_expression);
        } else {
            Parser__consume_token(self, Token__is_slash);
            if (Parser__matches_one(self, Token__is_slash)) {
                Parser__consume_token(self, Token__is_slash);
                Parser__consume_space(self, 1);
                Parsed_Expression *right_expression = Parser__parse_unary_expression(self);
                expression = (Parsed_Expression *)Parsed_Modulo_Expression__create(expression, right_expression);
            } else {
                Parser__consume_space(self, 1);
                Parsed_Expression *right_expression = Parser__parse_unary_expression(self);
                expression = (Parsed_Expression *)Parsed_Divide_Expression__create(expression, right_expression);
            }
        }
    }
    return expression;
}

bool Token__is_plus_or_minus(Token *self) {
    return Token__is_plus(self) || Token__is_minus(self);
}

// additive_expression
//  | multiplicative ( ( "+" | "-" ) multiplicative )*
Parsed_Expression *Parser__parse_additive_expression(Parser *self) {
    Parsed_Expression *expression = Parser__parse_multiplicative_expression(self);
    while (Parser__matches_two(self, Token__is_space, false, Token__is_plus_or_minus)) {
        Parser__consume_space(self, 1);
        if (Parser__matches_one(self, Token__is_plus)) {
            Parser__consume_token(self, Token__is_plus);
            Parser__consume_space(self, 1);
            Parsed_Expression *right_expression = Parser__parse_multiplicative_expression(self);
            expression = (Parsed_Expression *)Parsed_Add_Expression__create(expression, right_expression);
        } else {
            Parser__consume_token(self, Token__is_minus);
            Parser__consume_space(self, 1);
            Parsed_Expression *right_expression = Parser__parse_multiplicative_expression(self);
            expression = (Parsed_Expression *)Parsed_Subtract_Expression__create(expression, right_expression);
        }
    }
    return expression;
}

// comparison_expression
//  | additive_expression ( ( "<=" | "<" | ">" | ">=") additive_expression )*
//  | additive_expression ( "is" "not"? type )*
Parsed_Expression *Parser__parse_comparison_expression(Parser *self) {
    Parsed_Expression *expression = Parser__parse_additive_expression(self);
    if (Parser__matches_two(self, Token__is_space, false, Token__is_less_than)) {
        Parser__consume_space(self, 1);
        Parser__consume_token(self, Token__is_less_than);
        if (Parser__matches_one(self, Token__is_equals)) {
            Parser__consume_token(self, Token__is_equals);
            Parser__consume_space(self, 1);
            Parsed_Expression *right_expression = Parser__parse_additive_expression(self);
            expression = (Parsed_Expression *)Parsed_Less_Or_Equals_Expression__create(expression, right_expression);
        } else {
            Parser__consume_space(self, 1);
            Parsed_Expression *right_expression = Parser__parse_additive_expression(self);
            expression = (Parsed_Expression *)Parsed_Less_Expression__create(expression, right_expression);
        }
    } else if (Parser__matches_two(self, Token__is_space, false, Token__is_greater_than)) {
        Parser__consume_space(self, 1);
        Parser__consume_token(self, Token__is_greater_than);
        if (Parser__matches_one(self, Token__is_equals)) {
            Parser__consume_token(self, Token__is_equals);
            Parser__consume_space(self, 1);
            Parsed_Expression *right_expression = Parser__parse_additive_expression(self);
            expression = (Parsed_Expression *)Parsed_Greater_Or_Equals_Expression__create(expression, right_expression);
        } else {
            Parser__consume_space(self, 1);
            Parsed_Expression *right_expression = Parser__parse_additive_expression(self);
            expression = (Parsed_Expression *)Parsed_Greater_Expression__create(expression, right_expression);
        }
    } else if (Parser__matches_two(self, Token__is_space, false, Token__is_is)) {
        Parser__consume_space(self, 1);
        Parser__consume_token(self, Token__is_is);
        Parser__consume_space(self, 1);
        bool is_not = false;
        if (Parser__matches_one(self, Token__is_not)) {
            Parser__consume_token(self, Token__is_not);
            Parser__consume_space(self, 1);
            is_not = true;
        }
        Parsed_Type *type = Parser__parse_type(self);
        expression = (Parsed_Expression *)Parsed_Is_Expression__create(expression, type, is_not);
    }
    return expression;
}

// equality
//  | comparison ( ( "==" | "!=" ) comparison )*
Parsed_Expression *Parser__parse_equality_expression(Parser *self) {
    Parsed_Expression *expression = Parser__parse_comparison_expression(self);
    if (Parser__matches_three(self, Token__is_space, false, Token__is_equals, true, Token__is_equals)) {
        Parser__consume_space(self, 1);
        Parser__consume_token(self, Token__is_equals);
        Parser__consume_token(self, Token__is_equals);
        Parser__consume_space(self, 1);
        Parsed_Expression *right_expression = Parser__parse_comparison_expression(self);
        expression = (Parsed_Expression *)Parsed_Equals_Expression__create(expression, right_expression);
    } else if (Parser__matches_three(self, Token__is_space, false, Token__is_exclamation_mark, true, Token__is_equals)) {
        Parser__consume_space(self, 1);
        Parser__consume_token(self, Token__is_exclamation_mark);
        Parser__consume_token(self, Token__is_equals);
        Parser__consume_space(self, 1);
        Parsed_Expression *right_expression = Parser__parse_comparison_expression(self);
        expression = (Parsed_Expression *)Parsed_Not_Equals_Expression__create(expression, right_expression);
    }
    return expression;
}

/*
logic_and
    | equality ( "and" equality )*
*/
Parsed_Expression *Parser__parse_logic_and_expression(Parser *self) {
    Parsed_Expression *expression = Parser__parse_equality_expression(self);
    while (Parser__matches_two(self, Token__is_space, false, Token__is_and)) {
        Parser__consume_space(self, 1);
        Parser__consume_token(self, Token__is_and);
        Parser__consume_space(self, 1);
        Parsed_Expression *right_expression = Parser__parse_equality_expression(self);
        expression = (Parsed_Expression *)Parsed_Logic_And_Expression__create(expression, right_expression);
    }
    return expression;
}

/*
logic_or
    | logic_and ( "or" logic_and )*
*/
Parsed_Expression *Parser__parse_logic_or_expression(Parser *self) {
    Parsed_Expression *expression = Parser__parse_logic_and_expression(self);
    while (Parser__matches_two(self, Token__is_space, false, Token__is_or)) {
        Parser__consume_space(self, 1);
        Parser__consume_token(self, Token__is_or);
        Parser__consume_space(self, 1);
        Parsed_Expression *right_expression = Parser__parse_logic_and_expression(self);
        expression = (Parsed_Expression *)Parsed_Logic_Or_Expression__create(expression, right_expression);
    }
    return expression;
}

/*
expression
    | logic_or
*/
Parsed_Expression *Parser__parse_expression(Parser *self) {
    return Parser__parse_logic_or_expression(self);
}

/*
struct_type_specifier
    | "struct" "{" ( IDENTIFIER ":" type )* "}"
*/
Parsed_Type_Specifier *Parser__parse_struct_type_specifier(Parser *self) {
    Token *first_token = Parser__consume_token(self, Token__is_struct);
    Parser__consume_space(self, 1);
    Parser__consume_token(self, Token__is_opening_brace);
    Parser__consume_end_of_line(self);
    self->current_identation = self->current_identation + 1;
    Parsed_Struct_Member *first_struct_member = NULL;
    Parsed_Struct_Member *last_struct_member = NULL;
    while (!Parser__matches_two(self, Token__is_space, false, Token__is_closing_brace)) {
        if (!Parser__consume_empty_line(self)) {
            Parser__consume_space(self, self->current_identation * 4);
            Token *struct_member_name = Parser__consume_token(self, Token__is_identifier);
            Parser__consume_space(self, 0);
            Parser__consume_token(self, Token__is_colon);
            Parser__consume_space(self, 1);
            Parsed_Type *struct_member_type = Parser__parse_type(self);
            Parser__consume_end_of_line(self);
            Parsed_Struct_Member *struct_member = Parsed_Struct_Member__create(struct_member_name, struct_member_type);
            if (first_struct_member == NULL) {
                first_struct_member = struct_member;
            } else {
                last_struct_member->next_member = struct_member;
            }
            last_struct_member = struct_member;
        }
    }
    self->current_identation = self->current_identation - 1;
    Parser__consume_space(self, self->current_identation * 4);
    Token *last_token = Parser__consume_token(self, Token__is_closing_brace);
    return (Parsed_Type_Specifier *)Parsed_Struct_Type_Specifier__create(Source_Location__merge(first_token->location, last_token->location), first_struct_member);
}

Parsed_Procedure_Parameter *Parser__parse_procedure_parameters(Parser *self, Parsed_Type *receiver_type);

/*
trait_type_specifier
    | "trait" "{" trait_method* "}"
*/
Parsed_Type_Specifier *Parser__parse_trait_type_specifier(Parser *self) {
    Token *first_token = Parser__consume_token(self, Token__is_trait);
    Parser__consume_space(self, 1);
    Parser__consume_token(self, Token__is_opening_brace);
    Parser__consume_end_of_line(self);
    self->current_identation = self->current_identation + 1;
    Parsed_Trait_Method *first_trait_method = NULL;
    Parsed_Trait_Method *last_trait_method = NULL;
    while (!Parser__matches_two(self, Token__is_space, false, Token__is_closing_brace)) {
        if (!Parser__consume_empty_line(self)) {
            Parser__consume_space(self, self->current_identation * 4);
            Source_Location method_location = Parser__consume_token(self, Token__is_proc)->location;
            Parser__consume_space(self, 1);
            Token *method_name = Parser__consume_token(self, Token__is_identifier);
            Parser__consume_space(self, 0);
            Parser__consume_token(self, Token__is_opening_paren);
            Source_Location receiver_type_location = {0}; // Default location for receiver type
            Parsed_Procedure_Parameter *first_parameter = Parser__parse_procedure_parameters(self, (Parsed_Type *)Parsed_Receiver_Type__create(receiver_type_location));
            Parser__consume_space(self, 0);
            Parser__consume_token(self, Token__is_closing_paren);
            Parsed_Type *return_type = NULL;
            if (Parser__matches_two(self, Token__is_space, false, Token__is_minus)) {
                Parser__consume_space(self, 1);
                Parser__consume_token(self, Token__is_minus);
                Parser__consume_token(self, Token__is_greater_than);
                Parser__consume_space(self, 1);
                return_type = Parser__parse_type(self);
            }
            Parser__consume_end_of_line(self);
            Parsed_Trait_Method *trait_method = Parsed_Trait_Method__create(method_location, method_name, first_parameter, return_type);
            if (last_trait_method == NULL) {
                first_trait_method = trait_method;
            } else {
                last_trait_method->next_method = trait_method;
            }
            last_trait_method = trait_method;
        }
    }
    self->current_identation = self->current_identation - 1;
    Parser__consume_space(self, self->current_identation * 4);
    Token *last_token = Parser__consume_token(self, Token__is_closing_brace);
    return (Parsed_Type_Specifier *)Parsed_Trait_Type_Specifier__create(Source_Location__merge(first_token->location, last_token->location), first_trait_method);
}

/*
variant_type_specifier
    | "variant" "{" ( type )* "}"
*/
Parsed_Type_Specifier *Parser__parse_variant_type_specifier(Parser *self) {
    Token *first_token = Parser__consume_token(self, Token__is_variant);
    Parser__consume_space(self, 1);
    Parser__consume_token(self, Token__is_opening_brace);
    Parser__consume_end_of_line(self);
    self->current_identation = self->current_identation + 1;
    Parsed_Variant_Case *first_variant_case = NULL;
    Parsed_Variant_Case *last_variant_case = NULL;
    while (!Parser__matches_two(self, Token__is_space, false, Token__is_closing_brace)) {
        if (!Parser__consume_empty_line(self)) {
            Parser__consume_space(self, self->current_identation * 4);
            Parsed_Type *variant_type = Parser__parse_type(self);
            Parser__consume_end_of_line(self);
            Parsed_Variant_Case *variant_case = Parsed_Variant_Case__create(variant_type);
            if (last_variant_case == NULL) {
                first_variant_case = variant_case;
            } else {
                last_variant_case->next_variant = variant_case;
            }
            last_variant_case = variant_case;
        }
    }
    self->current_identation = self->current_identation - 1;
    Parser__consume_space(self, self->current_identation * 4);
    Token *last_token = Parser__consume_token(self, Token__is_closing_brace);
    return (Parsed_Type_Specifier *)Parsed_Variant_Type_Specifier__create(Source_Location__merge(first_token->location, last_token->location), first_variant_case);
}

/*
external_type_specifier
    | "external"
*/
Parsed_Type_Specifier *Parser__parse_external_type_specifier(Parser *self) {
    Token *last_token = Parser__consume_token(self, Token__is_external);
    return (Parsed_Type_Specifier *)Parsed_External_Type_Specifier__create(last_token->location);
}

/*
builtin_type_specifier
    | "builtin"
*/
Parsed_Type_Specifier *Parser__parse_builtin_type_specifier(Parser *self) {
    Token *token = Parser__consume_token(self, Token__is_builtin);
    return (Parsed_Type_Specifier *)Parsed_Builtin_Type_Specifier__create(token->location);
}

/*
type_parameter
    | IDENTIFIER
*/
Parsed_Type_Parameter *Parser__parse_type_parameter(Parser *self) {
    Token *name = Parser__consume_token(self, Token__is_identifier);
    return Parsed_Type_Parameter__create(name);
}

/*
type_parameters
    | "<" type_parameter ( "," type_parameter )* ">"
*/
Parsed_Type_Parameter *Parser__parse_type_parameters(Parser *self) {
    Parser__consume_token(self, Token__is_less_than);
    Parser__consume_space(self, 0);
    Parsed_Type_Parameter *first_parameter = Parser__parse_type_parameter(self);
    Parsed_Type_Parameter *last_parameter = first_parameter;
    while (Parser__matches_two(self, Token__is_space, false, Token__is_comma)) {
        Parser__consume_space(self, 0);
        Parser__consume_token(self, Token__is_comma);
        Parser__consume_space(self, 1);
        Parsed_Type_Parameter *next_parameter = Parser__parse_type_parameter(self);
        last_parameter->next_type_parameter = next_parameter;
        last_parameter = next_parameter;
    }
    Parser__consume_space(self, 0);
    Token *last_token = Parser__consume_token(self, Token__is_greater_than);
    return first_parameter;
}

/*
type_specifier
    | builtin_type_specifier
    | external_type_specifier
    | struct_type_specifier
    | trait_type_specifier
    | variant_type_specifier
*/
Parsed_Type_Specifier *Parser__parse_type_specifier(Parser *self) {
    if (Parser__matches_one(self, Token__is_builtin)) {
        return Parser__parse_builtin_type_specifier(self);
    }
    if (Parser__matches_one(self, Token__is_external)) {
        return Parser__parse_external_type_specifier(self);
    }
    if (Parser__matches_one(self, Token__is_struct)) {
        return Parser__parse_struct_type_specifier(self);
    }
    if (Parser__matches_one(self, Token__is_trait)) {
        return Parser__parse_trait_type_specifier(self);
    }
    if (Parser__matches_one(self, Token__is_variant)) {
        return Parser__parse_variant_type_specifier(self);
    }
    Token *unsupported_type = Parser__consume_token(self, Token__is_identifier);
    pWriter__begin_location_message(stderr_writer, unsupported_type->location, WRITER_STYLE__ERROR);
    pWriter__write__cstring(stderr_writer, "Unsupported type specifier: ");
    pWriter__write__token(stderr_writer, unsupported_type);
    pWriter__end_location_message(stderr_writer);
    panic();
}

/*
type_definition
    | "type" IDENTIFIER type_parameters? "=" type_specifier
*/
Parsed_Statement *Parser__parse_type_statement(Parser *self) {
    Source_Location type_location = Parser__consume_token(self, Token__is_type)->location;
    Parser__consume_space(self, 1);
    Token *name = Parser__consume_token(self, Token__is_identifier);
    Parsed_Type_Parameter *first_type_parameter = NULL;
    if (Parser__matches_two(self, Token__is_space, false, Token__is_less_than)) {
        Parser__consume_space(self, 0);
        first_type_parameter = Parser__parse_type_parameters(self);
    }
    Parser__consume_space(self, 1);
    Parser__consume_token(self, Token__is_equals);
    Parser__consume_space(self, 1);
    Parsed_Type_Specifier *type_specifier = Parser__parse_type_specifier(self);
    return (Parsed_Statement *)Parsed_Type_Statement__create(Source_Location__merge(type_location, type_specifier->location), name, type_specifier, first_type_parameter);
}

/*
procedure_parameter
    | ( "anon" | IDENTIFIER )? IDENTIFIER ":" type
*/
Parsed_Procedure_Parameter *Parser__parse_procedure_parameter(Parser *self) {
    bool anonymous = false;
    Token *label = NULL;
    Token *name = NULL;
    if (Parser__matches_three(self, Token__is_identifier, true, Token__is_space, true, Token__is_identifier)) {
        label = Parser__consume_token(self, Token__is_identifier);
        Parser__consume_space(self, 1);
        name = Parser__consume_token(self, Token__is_identifier);
        if (Token__is_anon(label)) {
            anonymous = true;
            label = NULL;
        }
    } else {
        label = name = Parser__consume_token(self, Token__is_identifier);
    }
    Parser__consume_space(self, 0);
    Parser__consume_token(self, Token__is_colon);
    Parser__consume_space(self, 1);
    Parsed_Type *type = Parser__parse_type(self);
    return Parsed_Procedure_Parameter__create(label, name, type);
}

/*
procedure_parameters
    | procedure_parameter ( "," procedure_parameter )*
*/
Parsed_Procedure_Parameter *Parser__parse_procedure_parameters(Parser *self, Parsed_Type *receiver_type) {
    Parsed_Procedure_Parameter *first_parameter = NULL;
    if (!Parser__matches_two(self, Token__is_space, false, Token__is_closing_paren)) {
        Parser__consume_space(self, 0);
        if (receiver_type != NULL) {
            Token *parameter_name = Parser__consume_token(self, Token__is_identifier);
            first_parameter = Parsed_Procedure_Parameter__create(NULL, parameter_name, receiver_type);
        } else {
            first_parameter = Parser__parse_procedure_parameter(self);
        }
        Parsed_Procedure_Parameter *last_parameter = first_parameter;
        while (Parser__matches_two(self, Token__is_space, false, Token__is_comma)) {
            Parser__consume_space(self, 0);
            Parser__consume_token(self, Token__is_comma);
            Parser__consume_space(self, 1);
            last_parameter->next_parameter = Parser__parse_procedure_parameter(self);
            last_parameter = last_parameter->next_parameter;
        }
    }
    return first_parameter;
}

/*
type_argument
    | type
*/
Parsed_Type_Argument *Parser__parse_type_argument(Parser *self) {
    Parsed_Type *type = Parser__parse_type(self);
    return Parsed_Type_Argument__create(type);
}

/*
type_arguments
    | "<" type_argument ( "," type_argument )* ">"
*/
Parsed_Type_Argument *Parser__parse_type_arguments(Parser *self, Source_Location *type_location) {
    Parser__consume_token(self, Token__is_less_than);
    Parser__consume_space(self, 0);
    Parsed_Type_Argument *first_type_argument = Parser__parse_type_argument(self);
    Parsed_Type_Argument *last_type_argument = first_type_argument;
    while (Parser__matches_two(self, Token__is_space, false, Token__is_comma)) {
        Parser__consume_space(self, 0);
        Parser__consume_token(self, Token__is_comma);
        Parser__consume_space(self, 1);
        last_type_argument->next_type_argument = Parser__parse_type_argument(self);
        last_type_argument = last_type_argument->next_type_argument;
    }
    Parser__consume_space(self, 0);
    Token *last_token = Parser__consume_token(self, Token__is_greater_than);
    *type_location = Source_Location__merge(*type_location, last_token->location);
    return first_type_argument;
}

/*
type
    | "^" type
    | "[" ( expression | "^" ) "]" type
    | IDENTIFIER ( "." IDENTIFIER )? type_arguments?
    | proc "(" procedure_parameters? ")" ( "->" type )?
*/
Parsed_Type *Parser__parse_type(Parser *self) {
    if (Parser__matches_one(self, Token__is_caret)) {
        Token *first_token = Parser__consume_token(self, Token__is_caret);
        Parser__consume_space(self, 0);
        Parsed_Type *type = Parser__parse_type(self);
        return Parsed_Pointer_Type__create(Source_Location__merge(first_token->location, type->location), type);
    }
    if (Parser__matches_one(self, Token__is_opening_bracket)) {
        Token *first_token = Parser__consume_token(self, Token__is_opening_bracket);
        Parser__consume_space(self, 0);
        if (Parser__matches_one(self, Token__is_caret)) {
            Parser__consume_token(self, Token__is_caret);
            Parser__consume_space(self, 0);
            Parser__consume_token(self, Token__is_closing_bracket);
            Parser__consume_space(self, 0);
            Parsed_Type *item_type = Parser__parse_type(self);
            return (Parsed_Type *)Parsed_Multi_Pointer_Type__create(Source_Location__merge(first_token->location, item_type->location), item_type);
        }
        Parsed_Expression *size_expression = Parser__parse_expression(self);
        Parser__consume_space(self, 0);
        Parser__consume_token(self, Token__is_closing_bracket);
        Parser__consume_space(self, 0);
        Parsed_Type *item_type = Parser__parse_type(self);
        return (Parsed_Type *)Parsed_Array_Type__create(Source_Location__merge(first_token->location, item_type->location), item_type, size_expression);
    }
    if (Parser__matches_one(self, Token__is_proc)) {
        Token *first_token = Parser__consume_token(self, Token__is_proc);
        Parser__consume_space(self, 1);
        Parser__consume_token(self, Token__is_opening_paren);
        Parsed_Procedure_Parameter *first_parameter = Parser__parse_procedure_parameters(self, NULL);
        Parser__consume_space(self, 0);
        Token *closing_paren = Parser__consume_token(self, Token__is_closing_paren);
        Parsed_Type *return_type = NULL;
        if (Parser__matches_two(self, Token__is_space, false, Token__is_minus)) {
            Parser__consume_space(self, 1);
            Parser__consume_token(self, Token__is_minus);
            Parser__consume_token(self, Token__is_greater_than);
            Parser__consume_space(self, 1);
            return_type = Parser__parse_type(self);
        }
        return Parsed_Procedure_Type__create(Source_Location__merge(first_token->location, (return_type ? return_type->location : closing_paren->location)), first_parameter, return_type);
    }
    Token *module = NULL;
    Token *name = Parser__consume_token(self, Token__is_identifier);
    if (Parser__matches_two(self, Token__is_space, false, Token__is_dot)) {
        Parser__consume_space(self, 0);
        Parser__consume_token(self, Token__is_dot);
        Parser__consume_space(self, 0);
        module = name;
        name = Parser__consume_token(self, Token__is_identifier);
    }
    Parsed_Named_Type *named_type = Parsed_Named_Type__create(module, name);
    if (Parser__matches_two(self, Token__is_space, false, Token__is_less_than)) {
        Parser__consume_space(self, 0);
        named_type->first_type_argument = Parser__parse_type_arguments(self, &named_type->super.location);
    }
    return (Parsed_Type *)named_type;
}

/*
variable
    | "let" IDENTIFIER ":" type
    | "let" IDENTIFIER ( ":" type )? "=" "external" STRING?
    | "let" IDENTIFIER ( ":" type )? "=" expression
*/
Parsed_Statement *Parser__parse_variable(Parser *self) {
    Source_Location location = Parser__consume_token(self, Token__is_let)->location;
    Parser__consume_space(self, 1);
    Token *name = Parser__consume_token(self, Token__is_identifier);
    location = Source_Location__merge(location, name->location);
    Parsed_Type *type = NULL;
    if (Parser__matches_two(self, Token__is_space, false, Token__is_colon)) {
        Parser__consume_space(self, 0);
        Parser__consume_token(self, Token__is_colon);
        Parser__consume_space(self, 1);
        type = Parser__parse_type(self);
        location = Source_Location__merge(location, type->location);
    }
    Parsed_Expression *expression = NULL;
    String_Token *external_name = NULL;
    bool is_external = false;
    if (Parser__matches_two(self, Token__is_space, false, Token__is_equals)) {
        Parser__consume_space(self, 1);
        Parser__consume_token(self, Token__is_equals);
        Parser__consume_space(self, 1);
        if (Parser__matches_one(self, Token__is_external)) {
            is_external = true;
            location = Source_Location__merge(location, Parser__consume_token(self, Token__is_external)->location);
            if (Parser__matches_two(self, Token__is_space, false, Token__is_string)) {
                Parser__consume_space(self, 1);
                external_name = (String_Token *)Parser__consume_token(self, Token__is_string);
                location = Source_Location__merge(location, external_name->super.location);
            }
        } else {
            expression = Parser__parse_expression(self);
            location = Source_Location__merge(location, expression->location);
        }
    }
    return (Parsed_Statement *)Parsed_Variable_Statement__create(location, name, type, is_external, expression, external_name);
}

void Parser__parse_statements(Parser *self, Parsed_Statements *statements);

/*
block
    | "{" statements "}"
*/
Parsed_Block_Statement *Parser__parse_block_statement(Parser *self) {
    Token *first_token = Parser__consume_token(self, Token__is_opening_brace);
    Parser__consume_end_of_line(self);
    Parsed_Statements *statements = Parsed_Statements__create(false);
    self->current_identation = self->current_identation + 1;
    Parser__parse_statements(self, statements);
    self->current_identation = self->current_identation - 1;
    Parser__consume_space(self, self->current_identation * 4);
    Token *last_token = Parser__consume_token(self, Token__is_closing_brace);
    return Parsed_Block_Statement__create(Source_Location__merge(first_token->location, last_token->location), statements);
}

/*
procedure
    | "proc" ( "(" type ")" "." )? IDENTIFIER type_parameters? "(" procedure_parameter* ")" ( "->" type )? ( "!>" type )? ( "=" "external" STRING? | block )
*/
Parsed_Statement *Parser__parse_procedure(Parser *self, Parsed_Type *receiver_type) {
    Source_Location location = Parser__consume_token(self, Token__is_proc)->location;
    Parser__consume_space(self, 1);
    Token *name = NULL;
    if (receiver_type == NULL && Parser__matches_one(self, Token__is_opening_paren)) {
        Parser__consume_token(self, Token__is_opening_paren);
        Parser__consume_space(self, 0);
        receiver_type = Parser__parse_type(self);
        Parser__consume_space(self, 0);
        Parser__consume_token(self, Token__is_closing_paren);
        Parser__consume_space(self, 0);
        Parser__consume_token(self, Token__is_dot);
        Parser__consume_space(self, 0);
    }
    name = Parser__consume_token(self, Token__is_identifier);
    Parser__consume_space(self, 0);
    Parsed_Type_Parameter *first_type_parameter = NULL;
    if (Parser__matches_one(self, Token__is_less_than)) {
        first_type_parameter = Parser__parse_type_parameters(self);
        Parser__consume_space(self, 0);
    }
    Parser__consume_token(self, Token__is_opening_paren);
    Parsed_Procedure_Parameter *first_parameter = Parser__parse_procedure_parameters(self, receiver_type);
    Parser__consume_space(self, 0);
    Token *closing_paren = Parser__consume_token(self, Token__is_closing_paren);
    location = Source_Location__merge(location, closing_paren->location);
    Parsed_Type *return_type = NULL;
    if (Parser__matches_two(self, Token__is_space, false, Token__is_minus)) {
        Parser__consume_space(self, 1);
        Parser__consume_token(self, Token__is_minus);
        Parser__consume_token(self, Token__is_greater_than);
        Parser__consume_space(self, 1);
        return_type = Parser__parse_type(self);
        location = Source_Location__merge(location, return_type->location);
    }
    Parsed_Type *raise_type = NULL;
    if (Parser__matches_two(self, Token__is_space, false, Token__is_exclamation_mark)) {
        Parser__consume_space(self, 1);
        Parser__consume_token(self, Token__is_exclamation_mark);
        Parser__consume_token(self, Token__is_greater_than);
        Parser__consume_space(self, 1);
        raise_type = Parser__parse_type(self);
        location = Source_Location__merge(location, raise_type->location);
    }
    if (Parser__matches_two(self, Token__is_space, false, Token__is_equals)) {
        Parser__consume_space(self, 1);
        Parser__consume_token(self, Token__is_equals);
        Parser__consume_space(self, 1);
        Parser__consume_token(self, Token__is_external);
        String_Token *external_name = NULL;
        if (Parser__matches_two(self, Token__is_space, false, Token__is_string)) {
            Parser__consume_space(self, 1);
            external_name = (String_Token *)Parser__consume_token(self, Token__is_string);
        }
        return Parsed_Procedure_Statement__create(location, name, first_type_parameter, receiver_type != NULL, first_parameter, return_type, raise_type, true, NULL, external_name);
    }
    if (!Parser__matches_two(self, Token__is_space, false, Token__is_opening_brace)) {
        pWriter__begin_location_message(stderr_writer, self->scanner->current_token->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Missing procedure body");
        pWriter__end_location_message(stderr_writer);
        panic();
    }
    Parser__consume_space(self, 1);
    Parser__consume_token(self, Token__is_opening_brace);
    Parser__consume_end_of_line(self);
    Parsed_Statements *statements = Parsed_Statements__create(false);
    self->current_identation = self->current_identation + 1;
    Parser__parse_statements(self, statements);
    self->current_identation = self->current_identation - 1;
    Parser__consume_space(self, self->current_identation * 4);
    Token *closing_brace = Parser__consume_token(self, Token__is_closing_brace);
    location = Source_Location__merge(location, closing_brace->location);
    return Parsed_Procedure_Statement__create(location, name, first_type_parameter, receiver_type != NULL, first_parameter, return_type, raise_type, false, statements, NULL);
}

/*
raise
    | "raise" expression
*/
Parsed_Statement *Parser__parse_raise_statement(Parser *self) {
    Source_Location location = Parser__consume_token(self, Token__is_raise)->location;
    Parser__consume_space(self, 1);
    Parsed_Expression *expression = Parser__parse_expression(self);
    location = Source_Location__merge(location, expression->location);
    return (Parsed_Statement *)Parsed_Raise_Statement__create(location, expression);
}

/*
return
    | "return" expression?
*/
Parsed_Statement *Parser__parse_return_statement(Parser *self) {
    Source_Location location = Parser__consume_token(self, Token__is_return)->location;
    Parsed_Expression *expression = NULL;
    if (!Parser__matches_end_of_line(self)) {
        Parser__consume_space(self, 1);
        expression = Parser__parse_expression(self);
        location = Source_Location__merge(location, expression->location);
    }
    return Parsed_Return_Statement__create(location, expression);
}

// switch
//  : "switch" expression "{"
//      ( "case" expression block
//      | "is" type ( "as" IDENTIFIER )? block
//      )*
//      ( "else" block )?
//  "}"
Parsed_Statement *Parser__parse_switch_statement(Parser *self) {
    Token *first_token = Parser__consume_token(self, Token__is_switch);
    Parser__consume_space(self, 1);
    Parsed_Expression *switch_expression = Parser__parse_expression(self);
    Parser__consume_space(self, 1);
    Parser__consume_token(self, Token__is_opening_brace);
    self->current_identation = self->current_identation + 1;
    Parsed_Switch_Case *first_case = NULL;
    Parsed_Switch_Case *last_case = NULL;
    while (!Parser__matches_two(self, Token__is_space, false, Token__is_closing_brace)) {
        if (!Parser__consume_empty_line(self)) {
            Parser__consume_space(self, self->current_identation * 4);
            Token *first_token;
            Parsed_Switch_Case *switch_case = NULL;
            if (Parser__matches_one(self, Token__is_case)) {
                first_token = Parser__consume_token(self, Token__is_case);
                Parser__consume_space(self, 1);
                Parsed_Expression *case_expression = Parser__parse_expression(self);
                Parser__consume_space(self, 1);
                switch_case = Parsed_Switch_Expression__create(first_token->location, case_expression);
            } else if (Parser__matches_one(self, Token__is_is)) {
                first_token = Parser__consume_token(self, Token__is_is);
                Parser__consume_space(self, 1);
                Parsed_Type *variant_type = Parser__parse_type(self);
                Parser__consume_space(self, 1);
                Identifier_Token *variant_alias = NULL;
                if (Parser__matches_one(self, Token__is_as)) {
                    Parser__consume_token(self, Token__is_as);
                    Parser__consume_space(self, 1);
                    variant_alias = (Identifier_Token *)Parser__consume_token(self, Token__is_identifier);
                    Parser__consume_space(self, 1);
                }
                switch_case = Parsed_Switch_Variant__create(first_token->location, variant_type, variant_alias);
            } else if (Parser__matches_one(self, Token__is_else)) {
                first_token = Parser__consume_token(self, Token__is_else);
                Parser__consume_space(self, 1);
                switch_case = Parsed_Switch_Else__create(first_token->location);
            }
            switch_case->statement = (Parsed_Statement *)Parser__parse_block_statement(self);
            switch_case->location = Source_Location__merge(switch_case->location, switch_case->statement->location);
            if (first_case == NULL) {
                first_case = switch_case;
            } else {
                last_case->next_case = switch_case;
            }
            last_case = switch_case;
        }
    }
    self->current_identation = self->current_identation - 1;
    Parser__consume_space(self, self->current_identation * 4);
    Token *last_token = Parser__consume_token(self, Token__is_closing_brace);
    return (Parsed_Statement *)Parsed_Switch_Statement__create(Source_Location__merge(first_token->location, last_token->location), switch_expression, first_case);
}

/*
break
    | "break" ";"
*/
Parsed_Statement *Parser__parse_break_statement(Parser *self) {
    Source_Location location = Parser__consume_token(self, Token__is_break)->location;
    return Parsed_Break_Statement__create(location);
}

// if
//  | "if" expression ( "as" IDENTIFIER )? block ( "else" ( if |  block ) )?
Parsed_Statement *Parser__parse_if_statement(Parser *self) {
    Source_Location location = Parser__consume_token(self, Token__is_if)->location;
    Parser__consume_space(self, 1);
    Parsed_Expression *condition_expression = Parser__parse_expression(self);
    Parser__consume_space(self, 1);
    Identifier_Token *variant_alias = NULL;
    if (Parser__matches_one(self, Token__is_as)) {
        Parser__consume_token(self, Token__is_as);
        Parser__consume_space(self, 1);
        variant_alias = (Identifier_Token *)Parser__consume_token(self, Token__is_identifier);
        Parser__consume_space(self, 1);
    }
    Parsed_Statement *true_statement = (Parsed_Statement *)Parser__parse_block_statement(self);
    Parsed_Statement *false_statement = NULL;
    if (Parser__matches_two(self, Token__is_space, false, Token__is_else)) {
        Parser__consume_space(self, 1);
        Parser__consume_token(self, Token__is_else);
        Parser__consume_space(self, 1);
        if (Parser__matches_one(self, Token__is_if)) {
            false_statement = Parser__parse_if_statement(self);
        } else {
            false_statement = (Parsed_Statement *)Parser__parse_block_statement(self);
        }
        location = Source_Location__merge(location, false_statement->location);
    } else {
        location = Source_Location__merge(location, true_statement->location);
    }
    return Parsed_If_Statement__create(location, condition_expression, variant_alias, true_statement, false_statement);
}

/*
loop
    | "loop" block
*/
Parsed_Statement *Parser__parse_loop_statement(Parser *self) {
    Token *first_token = Parser__consume_token(self, Token__is_loop);
    Parser__consume_space(self, 1);
    Parsed_Statement *body_statement = (Parsed_Statement *)Parser__parse_block_statement(self);
    return Parsed_Loop_Statement__create(Source_Location__merge(first_token->location, body_statement->location), body_statement);
}

/*
while
    | "while" expression block
*/
Parsed_Statement *Parser__parse_while_statement(Parser *self) {
    Token *first_token = Parser__consume_token(self, Token__is_while);
    Parser__consume_space(self, 1);
    Parsed_Expression *condition_expression = Parser__parse_expression(self);
    Parser__consume_space(self, 1);
    Parsed_Statement *body_statement = (Parsed_Statement *)Parser__parse_block_statement(self);
    return Parsed_While_Statement__create(Source_Location__merge(first_token->location, body_statement->location), condition_expression, body_statement);
}

/*
import
    | "import" IDENTIFIER ( "." IDENTIFIER )* ( "as" IDENTIFIER )?
*/
Parsed_Statement *Parser__parse_import_statement(Parser *self) {
    Source_Location first_location = Parser__consume_token(self, Token__is_import)->location;
    Parser__consume_space(self, 1);
    Token *token = Parser__consume_token(self, Token__is_identifier);
    Source_Location last_location = token->location;
    String *module_name = token->lexeme;
    String *module_path = String__create_copy(token->lexeme);
    while (Parser__matches_two(self, Token__is_space, false, Token__is_dot)) {
        Parser__consume_space(self, 0);
        Parser__consume_token(self, Token__is_dot);
        Parser__consume_space(self, 0);
        token = Parser__consume_token(self, Token__is_identifier);
        last_location = token->location;
        module_name = token->lexeme;
        String__append_char(module_path, '/');
        String__append_string(module_path, token->lexeme);
    }
    if (Parser__matches_two(self, Token__is_space, false, Token__is_as)) {
        Parser__consume_space(self, 1);
        Parser__consume_token(self, Token__is_as);
        Parser__consume_space(self, 1);
        token = Parser__consume_token(self, Token__is_identifier);
        last_location = token->location;
        module_name = token->lexeme;
    }

    String__append_cstring(module_path, ".code");
    Parsed_Source *parsed_source = parse(self->project_dir, module_path);

    return Parsed_Import_Statement__create(Source_Location__merge(first_location, last_location), module_name, parsed_source);
}

/*
yield
    | "yield" expression
*/
Parsed_Statement *Parser__parse_yield_statement(Parser *self) {
    Source_Location location = Parser__consume_token(self, Token__is_yield)->location;
    Parser__consume_space(self, 1);
    Parsed_Expression *expression = Parser__parse_expression(self);
    location = Source_Location__merge(location, expression->location);
    return (Parsed_Statement *)Parsed_Yield_Statement__create(location, expression);
}

/*
statement
    | assignment
    | break
    | expression
    | if
    | import
    | loop
    | procedure
    | raise
    | return
    | type
    | variable
    | while
    | yield
*/
Parsed_Statement *Parser__parse_statement(Parser *self) {
    Parser__consume_space(self, self->current_identation * 4);

    if (Parser__matches_one(self, Token__is_proc)) {
        return Parser__parse_procedure(self, NULL);
    }

    if (Parser__matches_one(self, Token__is_let)) {
        return Parser__parse_variable(self);
    }

    if (Parser__matches_one(self, Token__is_type)) {
        return Parser__parse_type_statement(self);
    }

    if (Parser__matches_one(self, Token__is_import)) {
        return Parser__parse_import_statement(self);
    }

    if (Parser__matches_one(self, Token__is_if)) {
        return Parser__parse_if_statement(self);
    }

    if (Parser__matches_one(self, Token__is_loop)) {
        return Parser__parse_loop_statement(self);
    }

    if (Parser__matches_one(self, Token__is_return)) {
        return Parser__parse_return_statement(self);
    }

    if (Parser__matches_one(self, Token__is_while)) {
        return Parser__parse_while_statement(self);
    }

    if (Parser__matches_one(self, Token__is_break)) {
        return Parser__parse_break_statement(self);
    }

    if (Parser__matches_one(self, Token__is_switch)) {
        return Parser__parse_switch_statement(self);
    }

    if (Parser__matches_one(self, Token__is_raise)) {
        return Parser__parse_raise_statement(self);
    }

    if (Parser__matches_one(self, Token__is_yield)) {
        return Parser__parse_yield_statement(self);
    }

    Parsed_Expression *expression = Parser__parse_expression(self);

    if (Parser__matches_two(self, Token__is_space, false, Token__is_equals)) {
        Parser__consume_space(self, 1);
        Parser__consume_token(self, Token__is_equals);
        Parser__consume_space(self, 1);
        Parsed_Expression *value_expression = Parser__parse_expression(self);
        return (Parsed_Statement *)Parsed_Assignment_Statement__create(expression, value_expression);
    }

    return (Parsed_Statement *)Parsed_Expression_Statement__create(expression);
}

/*
statements
    | ( statement )*
*/
void Parser__parse_statements(Parser *self, Parsed_Statements *statements) {
    while (true) {
        while (Parser__consume_empty_line(self)) {
            /* ignored */
        }

        if (statements->has_globals) {
            if (Parser__matches_three(self, Token__is_space, false, Token__is_comment, false, Token__is_end_of_line)) {
                return;
            }
        } else {
            if (Parser__matches_two(self, Token__is_space, false, Token__is_closing_brace)) {
                return;
            }
        }

        Parsed_Statement *statement = Parser__parse_statement(self);

        Parsed_Statements__append(statements, statement);

        Parser__consume_end_of_line(self);
    }
}

void Parser__parse_source(Parser *self, Source *source) {
    Scanner *other_scanner = self->scanner;

    self->scanner = Scanner__create(source);

    Parser__parse_statements(self, self->parsed_source->statements);

    Token *last_token = Parser__peek_token(self, 0);
    if (!Token__is_end_of_file(last_token)) {
        pWriter__begin_location_message(stderr_writer, last_token->location, WRITER_STYLE__ERROR);
        pWriter__write__cstring(stderr_writer, "Scanner didn't reach end of file");
        pWriter__end_location_message(stderr_writer);
        panic();
    } else if (last_token->location.start_column != 1) {
        pWriter__begin_location_message(stderr_writer, last_token->location, WRITER_STYLE__WARNING);
        pWriter__write__cstring(stderr_writer, "No new line at the end of file");
        pWriter__end_location_message(stderr_writer);
    }

    self->scanner = other_scanner;
}

String *make_package_name(String *file_path) {
    String *package_name = String__create();

    size_t index = 0;
    while (index < file_path->length - 5) {
        char c = file_path->data[index];
        if (c == '/') {
            String__append_cstring(package_name, "__");
        } else {
            String__append_char(package_name, c);
        }
        index++;
    }

    return package_name;
}

Parsed_Source *parse(String *project_dir, String *file_path) {
    String *source_path = String__append_string(String__create_copy(project_dir), file_path);
    Source *source = Source__create(source_path);

    Parser parser;
    parser.project_dir = project_dir;
    parser.scanner = NULL;
    parser.parsed_source = Parsed_Source__create();
    parser.parsed_source->package_name = make_package_name(file_path);
    parser.parsed_source->source = source;
    parser.current_identation = 0;

    Parser__parse_source(&parser, source);

    return parser.parsed_source;
}
