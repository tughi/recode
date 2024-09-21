/* Copyright (C) 2024 Stefan Selariu */

#include "Parser.h"
#include "File.h"

typedef struct Parser {
    Scanner *scanner;
    Parsed_Source *parsed_source;
    uint16_t current_identation;
} Parser;

void Parser__error(Parser *self, String *message) {
    Token__error(self->scanner->current_token, message);
}

void Parser__warning(Parser *self, String *message) {
    Token__warning(self->scanner->current_token, message);
}

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
    Parser__error(self, String__create_from("Unexpected token"));
    panic();
}

void Parser__consume_comment(Parser *self) {
    Parser__consume_token(self, Token__is_comment);
}

void Parser__consume_space(Parser *self, uint16_t count) {
    if (Parser__matches_one(self, Token__is_space)) {
        Space_Token *token = (Space_Token *)Parser__consume_token(self, Token__is_space);
        if (token->count != count) {
            pWriter__write__location(stderr_writer, token->super.location);
            pWriter__write__cstring(stderr_writer, ": ");
            pWriter__style(stderr_writer, WRITER_STYLE__WARNING);
            pWriter__write__cstring(stderr_writer, "Consumed: ");
            pWriter__write__int64(stderr_writer, token->count);
            pWriter__write__cstring(stderr_writer, " spaces where ");
            pWriter__write__int64(stderr_writer, count);
            pWriter__write__cstring(stderr_writer, " were expected");
            pWriter__style(stderr_writer, WRITER_STYLE__DEFAULT);
            pWriter__end_line(stderr_writer);
        }
    } else if (count > 0) {
        pWriter__write__location(stderr_writer, self->scanner->current_token->location);
        pWriter__write__cstring(stderr_writer, ": ");
        pWriter__style(stderr_writer, WRITER_STYLE__WARNING);
        pWriter__write__cstring(stderr_writer, "Consumed 0 spaces where ");
        pWriter__write__int64(stderr_writer, count);
        pWriter__write__cstring(stderr_writer, " were expected");
        pWriter__style(stderr_writer, WRITER_STYLE__DEFAULT);
        pWriter__end_line(stderr_writer);
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
        Token__warning(token, String__create_from("Unexpected end of file"));
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

Parsed_Expression *Parser__parse_expression(Parser *self);
Parsed_Type *Parser__parse_type(Parser *self);

/*
primary_expression
    | "false"
    | "null"
    | "true"
    | CHARACTER
    | IDENTIFIER ( "i8" | "i16" | "i32" | "i64" | "isize" | "u8" | "u16" | "u32" | "u64" | "usize" )?
    | INTEGER
    | STRING
*/
Parsed_Expression *Parser__parse_primary_expression(Parser *self) {
    if (Parser__matches_one(self, Token__is_true)) {
        return (Parsed_Expression *)Parsed_Bool_Expression__create(Parser__consume_token(self, Token__is_true), true);
    }
    if (Parser__matches_one(self, Token__is_null)) {
        return (Parsed_Expression *)Parsed_Null_Expression__create(Parser__consume_token(self, Token__is_null));
    }
    if (Parser__matches_one(self, Token__is_false)) {
        return (Parsed_Expression *)Parsed_Bool_Expression__create(Parser__consume_token(self, Token__is_false), false);
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
                    integer_type = (Parsed_Named_Type *)Parsed_Named_Type__create(Parser__consume_token(self, Token__is_identifier));
                } else if (next_token->lexeme->length == 3) {
                    if (next_token->lexeme->data[1] == '1' && next_token->lexeme->data[2] == '6') {
                        integer_type = (Parsed_Named_Type *)Parsed_Named_Type__create(Parser__consume_token(self, Token__is_identifier));
                    } else if (next_token->lexeme->data[1] == '3' && next_token->lexeme->data[2] == '2') {
                        integer_type = (Parsed_Named_Type *)Parsed_Named_Type__create(Parser__consume_token(self, Token__is_identifier));
                    } else if (next_token->lexeme->data[1] == '6' && next_token->lexeme->data[2] == '4') {
                        integer_type = (Parsed_Named_Type *)Parsed_Named_Type__create(Parser__consume_token(self, Token__is_identifier));
                    }
                } else if (next_token->lexeme->length == 5) {
                    if (next_token->lexeme->data[1] == 's' && next_token->lexeme->data[2] == 'i' && next_token->lexeme->data[3] == 'z' && next_token->lexeme->data[4] == 'e') {
                        integer_type = (Parsed_Named_Type *)Parsed_Named_Type__create(Parser__consume_token(self, Token__is_identifier));
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
        Source_Location *location = Parser__consume_token(self, Token__is_opening_paren)->location;
        Parser__consume_space(self, 0);
        Parsed_Expression *expression = Parser__parse_expression(self);
        Parser__consume_space(self, 0);
        Parser__consume_token(self, Token__is_closing_paren);
        return (Parsed_Expression *)Parsed_Group_Expression__create(location, expression);
    }
    Parser__error(self, String__create_from("Unsupported primary expression"));
    panic();
}

/*
call_argument
    | ( IDENTIFIER ":" )? expression
*/
Parsed_Call_Argument *Parser__parse_call_argument(Parser *self) {
    Token *label = NULL;
    if (Parser__matches_three(self, Token__is_identifier, true, Token__is_space, false, Token__is_colon)) {
        label = Parser__consume_token(self, Token__is_identifier);
        Parser__consume_space(self, 0);
        Parser__consume_token(self, Token__is_colon);
        Parser__consume_space(self, 1);
    }
    Parsed_Expression *expression = Parser__parse_expression(self);
    return Parsed_Call_Argument__create(expression);
}

/*
call_arguments
    | call_argument ( ( "," | <EOL> ) call_argument )*
*/
Parsed_Call_Argument *Parser__parse_call_arguments(Parser *self) {
    Parsed_Call_Argument *first_argument = NULL;
    Parsed_Call_Argument *last_argument = NULL;
    if (Parser__matches_end_of_line(self)) {
        self->current_identation = self->current_identation + 1;
        while (Parser__consume_empty_line(self)) {
            /* ignored */
        }
        while (!Parser__matches_two(self, Token__is_space, false, Token__is_closing_paren)) {
            Parser__consume_space(self, self->current_identation * 4);
            Parsed_Call_Argument *argument = Parser__parse_call_argument(self);
            if (last_argument == NULL) {
                first_argument = argument;
            } else {
                last_argument->next_argument = argument;
            }
            last_argument = argument;

            while (Parser__consume_empty_line(self)) {
                /* ignored */
            }
        }
        self->current_identation = self->current_identation - 1;
        Parser__consume_space(self, self->current_identation * 4);
    } else if (!Parser__matches_two(self, Token__is_space, false, Token__is_closing_paren)) {
        first_argument = Parser__parse_call_argument(self);
        last_argument = first_argument;
        while (Parser__matches_one(self, Token__is_comma)) {
            Parser__consume_token(self, Token__is_comma);
            Parser__consume_space(self, 1);
            Parsed_Call_Argument *argument = Parser__parse_call_argument(self);
            last_argument->next_argument = argument;
            last_argument = argument;
            Parser__consume_space(self, 0);
        }
    }
    return first_argument;
}

/*
access_expression
    | primary_expression ( "." ( "@" | IDENTIFIER ) | "(" call_arguments ")" | "[" expression "]" )*
*/
Parsed_Expression *Parser__parse_access_expression(Parser *self) {
    Parsed_Expression *expression = Parser__parse_primary_expression(self);
    while (true) {
        Parsed_Expression *old_expression = expression;
        if (Parser__matches_two(self, Token__is_space, false, Token__is_dot)) {
            Parser__consume_space(self, 0);
            Parser__consume_token(self, Token__is_dot);
            Parser__consume_space(self, 0);
            if (Parser__matches_one(self, Token__is_at)) {
                Source_Location *location = Parser__consume_token(self, Token__is_at)->location;
                expression = (Parsed_Expression *)Parsed_Dereference_Expression__create(location, expression);
            } else {
                Token *name = Parser__consume_token(self, Token__is_identifier);
                expression = (Parsed_Expression *)Parsed_Member_Access_Expression__create(expression, name);
            }
        }
        if (Parser__matches_two(self, Token__is_space, false, Token__is_opening_paren)) {
            Parser__consume_space(self, 0);
            Parser__consume_token(self, Token__is_opening_paren);
            Parser__consume_space(self, 0);
            Parsed_Call_Argument *call_arguments = Parser__parse_call_arguments(self);
            Parser__consume_token(self, Token__is_closing_paren);
            expression = (Parsed_Expression *)Parsed_Call_Expression__create(expression, call_arguments);
        }
        if (Parser__matches_two(self, Token__is_space, false, Token__is_opening_bracket)) {
            Parser__consume_space(self, 0);
            Parser__consume_token(self, Token__is_opening_bracket);
            Parser__consume_space(self, 0);
            Parsed_Expression *index_expression = Parser__parse_expression(self);
            Parser__consume_space(self, 0);
            Parser__consume_token(self, Token__is_closing_bracket);
            expression = (Parsed_Expression *)Parsed_Array_Access_Expression__create(expression, index_expression);
        }
        if (old_expression == expression) {
            break;
        }
    }
    return expression;
}

/* unary_expression */
/*      | "-" unary_expression */
/*      | "not" unary_expression */
/*      | "@" unary_expression */
/*      | "sizeof" "(" type ")" */
/*      | access_expression */
Parsed_Expression *Parser__parse_unary_expression(Parser *self) {
    if (Parser__matches_one(self, Token__is_minus)) {
        Source_Location *location = Parser__consume_token(self, Token__is_minus)->location;
        Parser__consume_space(self, 0);
        Parsed_Expression *expression = Parser__parse_unary_expression(self);
        return (Parsed_Expression *)Parsed_Minus_Expression__create(location, expression);
    }
    if (Parser__matches_one(self, Token__is_not)) {
        Source_Location *location = Parser__consume_token(self, Token__is_not)->location;
        Parser__consume_space(self, 1);
        Parsed_Expression *expression = Parser__parse_unary_expression(self);
        return (Parsed_Expression *)Parsed_Not_Expression__create(location, expression);
    }
    if (Parser__matches_one(self, Token__is_at)) {
        Source_Location *location = Parser__consume_token(self, Token__is_at)->location;
        Parser__consume_space(self, 0);
        Parsed_Expression *expression = Parser__parse_unary_expression(self);
        return (Parsed_Expression *)Parsed_Address_Of_Expression__create(location, expression);
    }
    if (Parser__matches_one(self, Token__is_sizeof)) {
        Source_Location *location = Parser__consume_token(self, Token__is_sizeof)->location;
        Parser__consume_space(self, 0);
        Parser__consume_token(self, Token__is_opening_paren);
        Parser__consume_space(self, 0);
        Parsed_Type *type = Parser__parse_type(self);
        Parser__consume_space(self, 0);
        Parser__consume_token(self, Token__is_closing_paren);
        return (Parsed_Expression *)Parsed_Sizeof_Expression__create(location, type);
    }
    return Parser__parse_access_expression(self);
}

bool Token__is_mutliplication(Token *self) {
    return Token__is_asterisk(self) || Token__is_slash(self);
}

/*
multiplication
    | unary_expression ( ( "*" | "/" | "//" ) unary_expression )*
 */
Parsed_Expression *Parser__parse_multiplication_expression(Parser *self) {
    Parsed_Expression *expression = Parser__parse_unary_expression(self);
    while (Parser__matches_two(self, Token__is_space, false, Token__is_mutliplication)) {
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

bool Token__is_addition(Token *self) {
    return Token__is_plus(self) || Token__is_minus(self);
}

/* addition */
/*      | multiplication ( ( "+" | "-" ) multiplication )* */
Parsed_Expression *Parser__parse_addition_expression(Parser *self) {
    Parsed_Expression *expression = Parser__parse_multiplication_expression(self);
    while (Parser__matches_two(self, Token__is_space, false, Token__is_addition)) {
        Parser__consume_space(self, 1);
        if (Parser__matches_one(self, Token__is_plus)) {
            Parser__consume_token(self, Token__is_plus);
            Parser__consume_space(self, 1);
            Parsed_Expression *right_expression = Parser__parse_multiplication_expression(self);
            expression = (Parsed_Expression *)Parsed_Add_Expression__create(expression, right_expression);
        } else {
            Parser__consume_token(self, Token__is_minus);
            Parser__consume_space(self, 1);
            Parsed_Expression *right_expression = Parser__parse_multiplication_expression(self);
            expression = (Parsed_Expression *)Parsed_Substract_Expression__create(expression, right_expression);
        }
    }
    return expression;
}

/* comparison */
/*      | addition ( ( "<=" | "<" | ">" | ">=") addition )* */
Parsed_Expression *Parser__parse_comparison_expression(Parser *self) {
    Parsed_Expression *expression = Parser__parse_addition_expression(self);
    if (Parser__matches_two(self, Token__is_space, false, Token__is_less_than)) {
        Parser__consume_space(self, 1);
        Parser__consume_token(self, Token__is_less_than);
        if (Parser__matches_one(self, Token__is_equals)) {
            Parser__consume_token(self, Token__is_equals);
            Parser__consume_space(self, 1);
            Parsed_Expression *right_expression = Parser__parse_addition_expression(self);
            expression = (Parsed_Expression *)Parsed_Less_Or_Equals_Expression__create(expression, right_expression);
        } else {
            Parser__consume_space(self, 1);
            Parsed_Expression *right_expression = Parser__parse_addition_expression(self);
            expression = (Parsed_Expression *)Parsed_Less_Expression__create(expression, right_expression);
        }
    } else if (Parser__matches_two(self, Token__is_space, false, Token__is_greater_than)) {
        Parser__consume_space(self, 1);
        Parser__consume_token(self, Token__is_greater_than);
        if (Parser__matches_one(self, Token__is_equals)) {
            Parser__consume_token(self, Token__is_equals);
            Parser__consume_space(self, 1);
            Parsed_Expression *right_expression = Parser__parse_addition_expression(self);
            expression = (Parsed_Expression *)Parsed_Greater_Or_Equals_Expression__create(expression, right_expression);
        } else {
            Parser__consume_space(self, 1);
            Parsed_Expression *right_expression = Parser__parse_addition_expression(self);
            expression = (Parsed_Expression *)Parsed_Greater_Expression__create(expression, right_expression);
        }
    }
    return expression;
}

/* equality */
/*      | comparison ( ( "==" | "!=" ) comparison )* */
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

/* struct */
/*      | "typedef" "struct" IDENTIFIER ( "{" ( type "*"? IDENTIFIER ";" )* "}" )? IDENTIFIER ";" */
Parsed_Statement *Parser__parse_struct(Parser *self) {
    Source_Location *location = Parser__consume_token(self, Token__is_typedef)->location;
    Parser__consume_space(self, 1);
    Parser__consume_token(self, Token__is_struct);
    Parser__consume_space(self, 1);
    Token *local_name = Parser__consume_token(self, Token__is_identifier);
    Parsed_Struct_Statement *struct_statement = Parsed_Struct_Statement__create(location, local_name);
    Parser__consume_space(self, 1);
    if (!Parser__matches_one(self, Token__is_identifier)) {
        Parsed_Struct_Member *last_member = NULL;
        Parser__consume_token(self, Token__is_opening_brace);
        Parser__consume_end_of_line(self);
        while (!Parser__matches_two(self, Token__is_space, false, Token__is_closing_brace)) {
            while (Parser__consume_empty_line(self)) {
                /* ignored */
            }
            Parser__consume_space(self, (self->current_identation + 1) * 4);
            Parsed_Type *type = Parser__parse_type(self);
            Parser__consume_space(self, type->kind == PARSED_TYPE_KIND__POINTER ? 0 : 1);
            Token *name = Parser__consume_token(self, Token__is_identifier);
            Parser__consume_space(self, 0);
            Parser__consume_token(self, Token__is_semicolon);
            Parser__consume_end_of_line(self);
            Parsed_Struct_Member *member = Parsed_Struct_Member__create(name, type);
            if (last_member == NULL) {
                struct_statement->first_member = member;
                last_member = member;
            } else {
                last_member->next_member = member;
                last_member = member;
            }
        }
        Parser__consume_space(self, 0);
        Parser__consume_token(self, Token__is_closing_brace);
        Parser__consume_space(self, 1);
    }
    Token *final_name = Parser__consume_token(self, Token__is_identifier);
    if (!String__equals_string(final_name->lexeme, local_name->lexeme)) {
        Token__error(final_name, String__append_string(String__create_from("Final struct name doesn't match the local name: "), local_name->lexeme));
        panic();
    }
    Parser__consume_space(self, 0);
    Parser__consume_token(self, Token__is_semicolon);
    return (Parsed_Statement *)struct_statement;
}

/* enum */
/*      | "typedef" "enum" IDENTIFIER "{" ( IDENTIFIER "," )* "}" IDENTIFIER ";" */
Parsed_Statement *Parser__parse_enum(Parser *self) {
    Source_Location *location = Parser__consume_token(self, Token__is_typedef)->location;
    Parser__consume_space(self, 1);
    Parser__consume_token(self, Token__is_enum);
    Parser__consume_space(self, 1);
    Token *local_name = Parser__consume_token(self, Token__is_identifier);
    Parsed_Enum_Statement *enum_statement = Parsed_Enum_Statement__create(location, local_name);
    Parser__consume_space(self, 1);
    Parser__consume_token(self, Token__is_opening_brace);
    Parser__consume_end_of_line(self);
    self->current_identation = self->current_identation + 1;
    Parsed_Enum_Member *last_member = NULL;
    while (!Parser__matches_two(self, Token__is_space, false, Token__is_closing_brace)) {
        while (Parser__consume_empty_line(self)) {
            /* ignored */
        }
        Parser__consume_space(self, self->current_identation * 4);
        Token *name = Parser__consume_token(self, Token__is_identifier);
        Parser__consume_space(self, 0);
        Parsed_Enum_Member *member = Parsed_Enum_Member__create(name);
        if (last_member == NULL) {
            enum_statement->first_member = member;
            last_member = member;
        } else {
            last_member->next_member = member;
            last_member = member;
        }
        if (Parser__matches_one(self, Token__is_comma)) {
            Parser__consume_token(self, Token__is_comma);
            Parser__consume_end_of_line(self);
        } else {
            Parser__consume_end_of_line(self);
            while (Parser__consume_empty_line(self)) {
                /* ignored */
            }
            break;
        }
    }
    self->current_identation = self->current_identation - 1;
    Parser__consume_space(self, self->current_identation * 4);
    Parser__consume_token(self, Token__is_closing_brace);
    Parser__consume_space(self, 1);
    Token *final_name = Parser__consume_token(self, Token__is_identifier);
    if (!String__equals_string(final_name->lexeme, local_name->lexeme)) {
        Token__error(final_name, String__append_string(String__create_from("Final enum name doesn't match the local name: "), local_name->lexeme));
        panic();
    }
    Parser__consume_space(self, 0);
    Parser__consume_token(self, Token__is_semicolon);
    return (Parsed_Statement *)enum_statement;
}

/*
external_type
    | "external" "type" IDENTIFIER
*/
Parsed_Statement *Parser__parse_external_type(Parser *self) {
    Source_Location *location = Parser__consume_token(self, Token__is_external)->location;
    Parser__consume_space(self, 1);
    Parser__consume_token(self, Token__is_type);
    Parser__consume_space(self, 1);
    Token *name = Parser__consume_token(self, Token__is_identifier);
    return (Parsed_Statement *)Parsed_External_Type_Statement__create(location, name);
}

/*
function_parameter
    | ( "anon" | IDENTIFIER )? IDENTIFIER ":" type
*/
Parsed_Function_Parameter *Parser__parse_function_parameter(Parser *self) {
    bool anonymous = false;
    Token *label = NULL;
    Token *name = NULL;
    if (Parser__matches_three(self, Token__is_identifier, true, Token__is_space, true, Token__is_identifier)) {
        label = Parser__consume_token(self, Token__is_identifier);
        Parser__consume_space(self, 1);
        name = Parser__consume_token(self, Token__is_identifier);
        if (Token__is_anon(label)) {
            anonymous = true;
            label = name;
        }
    } else {
        label = name = Parser__consume_token(self, Token__is_identifier);
    }
    Parser__consume_space(self, 0);
    Parser__consume_token(self, Token__is_colon);
    Parser__consume_space(self, 1);
    Parsed_Type *type = Parser__parse_type(self);
    return Parsed_Function_Parameter__create(name, type);
}

/*
function_parameters
    | function_parameter ( "," function_parameter )*
*/
Parsed_Function_Parameter *Parser__parse_function_parameters(Parser *self) {
    Parsed_Function_Parameter *first_parameter = NULL;
    if (!Parser__matches_two(self, Token__is_space, false, Token__is_closing_paren)) {
        Parser__consume_space(self, 0);
        first_parameter = Parser__parse_function_parameter(self);
        Parsed_Function_Parameter *last_parameter = first_parameter;
        while (Parser__matches_two(self, Token__is_space, false, Token__is_comma)) {
            Parser__consume_space(self, 0);
            Parser__consume_token(self, Token__is_comma);
            Parser__consume_space(self, 1);
            last_parameter->next_parameter = Parser__parse_function_parameter(self);
            last_parameter = last_parameter->next_parameter;
        }
    }
    return first_parameter;
}

/*
type
    | "@" type
    | IDENTIFIER
    | func "(" function_parameters? ")" "->" type
*/
Parsed_Type *Parser__parse_type(Parser *self) {
    if (Parser__matches_one(self, Token__is_at)) {
        Source_Location *location = Parser__consume_token(self, Token__is_at)->location;
        Parser__consume_space(self, 0);
        Parsed_Type *type = Parser__parse_type(self);
        return Parsed_Pointer_Type__create(type);
    }
    if (Parser__matches_one(self, Token__is_func)) {
        Source_Location *location = Parser__consume_token(self, Token__is_func)->location;
        Parser__consume_space(self, 1);
        Parser__consume_token(self, Token__is_opening_paren);
        Parsed_Function_Parameter *first_parameter = Parser__parse_function_parameters(self);
        Parser__consume_space(self, 0);
        Parser__consume_token(self, Token__is_closing_paren);
        Parser__consume_space(self, 1);
        Parser__consume_token(self, Token__is_minus);
        Parser__consume_token(self, Token__is_greater_than);
        Parser__consume_space(self, 1);
        Parsed_Type *return_type = Parser__parse_type(self);
        return Parsed_Function_Type__create(location, first_parameter, return_type);
    }
    Token *name = Parser__consume_token(self, Token__is_identifier);
    return Parsed_Named_Type__create(name);
}

/*
variable
    | ( "external" | "let") IDENTIFIER ( ":" type )? ( "=" expression )?
*/
Parsed_Statement *Parser__parse_variable(Parser *self) {
    bool is_external;
    Source_Location *location;
    if (Parser__matches_one(self, Token__is_external)) {
        is_external = true;
        location = Parser__consume_token(self, Token__is_external)->location;
    } else {
        is_external = false;
        location = Parser__consume_token(self, Token__is_let)->location;
    }
    Parser__consume_space(self, 1);
    Token *name = Parser__consume_token(self, Token__is_identifier);
    Parsed_Type *type = NULL;
    if (Parser__matches_two(self, Token__is_space, false, Token__is_colon)) {
        Parser__consume_space(self, 0);
        Parser__consume_token(self, Token__is_colon);
        Parser__consume_space(self, 1);
        type = Parser__parse_type(self);
    }
    Parsed_Expression *expression = NULL;
    if (Parser__matches_two(self, Token__is_space, false, Token__is_equals)) {
        Parser__consume_space(self, 1);
        Parser__consume_token(self, Token__is_equals);
        Parser__consume_space(self, 1);
        expression = Parser__parse_expression(self);
    }
    return (Parsed_Statement *)Parsed_Variable_Statement__create(location, name, type, expression, is_external);
}

void Parser__parse_statements(Parser *self, Parsed_Statements *statements);

/*
block
    | "{" statements "}"
*/
Parsed_Block_Statement *Parser__parse_block_statement(Parser *self) {
    Source_Location *location = Parser__consume_token(self, Token__is_opening_brace)->location;
    Parser__consume_end_of_line(self);
    Parsed_Statements *statements = Parsed_Statements__create(false);
    self->current_identation = self->current_identation + 1;
    Parser__parse_statements(self, statements);
    self->current_identation = self->current_identation - 1;
    Parser__consume_space(self, self->current_identation * 4);
    Parser__consume_token(self, Token__is_closing_brace);
    return Parsed_Block_Statement__create(location, statements);
}

/*
function
    | "external"? "func" IDENTIFIER "(" function_parameter* ")" "->" type block?
*/
Parsed_Statement *Parser__parse_function(Parser *self) {
    bool is_external = false;
    if (Parser__matches_one(self, Token__is_external)) {
        is_external = true;
        Parser__consume_token(self, Token__is_external);
        Parser__consume_space(self, 1);
    }
    Source_Location *location = Parser__consume_token(self, Token__is_func)->location;
    Parser__consume_space(self, 1);
    Token *name = Parser__consume_token(self, Token__is_identifier);
    Parser__consume_space(self, 0);
    Parser__consume_token(self, Token__is_opening_paren);
    Parsed_Function_Parameter *first_parameter = Parser__parse_function_parameters(self);
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
    Parsed_Statements *statements = NULL;
    if (Parser__matches_two(self, Token__is_space, false, Token__is_opening_brace)) {
        Parser__consume_space(self, 1);
        Parser__consume_token(self, Token__is_opening_brace);
        Parser__consume_end_of_line(self);
        statements = Parsed_Statements__create(false);
        self->current_identation = self->current_identation + 1;
        Parser__parse_statements(self, statements);
        self->current_identation = self->current_identation - 1;
        Parser__consume_space(self, self->current_identation * 4);
        Parser__consume_token(self, Token__is_closing_brace);
    }
    return Parsed_Function_Statement__create(location, name, first_parameter, return_type, statements, is_external);
}

/*
return
    | "return" expression?
*/
Parsed_Statement *Parser__parse_return_statement(Parser *self) {
    Source_Location *location = Parser__consume_token(self, Token__is_return)->location;
    Parsed_Expression *expression = NULL;
    if (!Parser__matches_end_of_line(self)) {
        Parser__consume_space(self, 1);
        expression = Parser__parse_expression(self);
    }
    return Parsed_Return_Statement__create(location, expression);
}

/*
break
    | "break" ";"
*/
Parsed_Statement *Parser__parse_break_statement(Parser *self) {
    Source_Location *location = Parser__consume_token(self, Token__is_break)->location;
    return Parsed_Break_Statement__create(location);
}

/*
if
    | "if" expression block ( "else" ( if |  block ) )?
*/
Parsed_Statement *Parser__parse_if_statement(Parser *self) {
    Source_Location *location = Parser__consume_token(self, Token__is_if)->location;
    Parser__consume_space(self, 1);
    Parsed_Expression *condition_expression = Parser__parse_expression(self);
    Parser__consume_space(self, 1);
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
    }
    return Parsed_If_Statement__create(location, condition_expression, true_statement, false_statement);
}

/*
loop
    | "loop" block
*/
Parsed_Statement *Parser__parse_loop_statement(Parser *self) {
    Source_Location *location = Parser__consume_token(self, Token__is_loop)->location;
    Parser__consume_space(self, 1);
    Parsed_Statement *body_statement = (Parsed_Statement *)Parser__parse_block_statement(self);
    return Parsed_Loop_Statement__create(location, body_statement);
}

/*
while
    | "while" expression block
*/
Parsed_Statement *Parser__parse_while_statement(Parser *self) {
    Source_Location *location = Parser__consume_token(self, Token__is_while)->location;
    Parser__consume_space(self, 1);
    Parsed_Expression *condition_expression = Parser__parse_expression(self);
    Parser__consume_space(self, 1);
    Parsed_Statement *body_statement = (Parsed_Statement *)Parser__parse_block_statement(self);
    return Parsed_While_Statement__create(location, condition_expression, body_statement);
}

/*
statement
    | assignment
    | break
    | expression
    | external_type
    | function
    | if
    | loop
    | return
    | struct
    | variable
    | while
*/
Parsed_Statement *Parser__parse_statement(Parser *self) {
    Parser__consume_space(self, self->current_identation * 4);

    if (Parser__matches_two(self, Token__is_external, true, Token__is_space)) {
        if (Token__is_func(Parser__peek_token(self, 2))) {
            return Parser__parse_function(self);
        }

        if (Token__is_type(Parser__peek_token(self, 2))) {
            return Parser__parse_external_type(self);
        }

        return Parser__parse_variable(self);
    }

    if (Parser__matches_one(self, Token__is_func)) {
        return Parser__parse_function(self);
    }

    if (Parser__matches_one(self, Token__is_let)) {
        return Parser__parse_variable(self);
    }

    if (Parser__matches_one(self, Token__is_struct)) {
        return Parser__parse_struct(self);
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

    Parsed_Expression *expresion = Parser__parse_access_expression(self);

    if (Parser__matches_two(self, Token__is_space, false, Token__is_equals)) {
        Parser__consume_space(self, 1);
        Parser__consume_token(self, Token__is_equals);
        Parser__consume_space(self, 1);
        Parsed_Expression *value_expression = Parser__parse_expression(self);
        return (Parsed_Statement *)Parsed_Assignment_Statement__create(expresion, value_expression);
    }

    return (Parsed_Statement *)Parsed_Expression_Statement__create(expresion);
}

/* statements */
/*      | ( statement )* */
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
        Parser__error(self, String__create_from("Scanner didn't reach end of file"));
        panic();
    } else if (last_token->location->column != 1) {
        Parser__warning(self, String__create_from("No new line at the end of file"));
    }

    self->scanner = other_scanner;
}

Parsed_Source *parse(Source *source) {
    Parser parser;
    parser.scanner = NULL;
    parser.parsed_source = Parsed_Source__create();
    parser.parsed_source->first_source = source;
    parser.current_identation = 0;

    Parser__parse_source(&parser, source);

    return parser.parsed_source;
}
