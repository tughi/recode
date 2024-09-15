/* Copyright (C) 2024 Stefan Selariu */

#include "Header_Parser.h"
#include "File.h"
#include "Header_Scanner.h"

typedef struct Header_Parser {
    Header_Scanner *scanner;
    Parsed_Source *parsed_source;
    uint16_t current_identation;
} Header_Parser;

void Header_Parser__error(Header_Parser *self, String *message) {
    Token__error(self->scanner->current_token, message);
}

void Header_Parser__warning(Header_Parser *self, String *message) {
    Token__warning(self->scanner->current_token, message);
}

Token *Header_Parser__peek_token(Header_Parser *self, uint8_t offset) {
    return Header_Scanner__peek_token(self->scanner, offset);
}

bool Header_Parser__matches_three(Header_Parser *self, bool (*first_is)(struct Token *token), bool first_required, bool (*second_is)(Token *token), bool second_required, bool (*third_is)(Token *token)) {
    uint8_t peek_offset = 0;
    if (first_is(Header_Parser__peek_token(self, peek_offset))) {
        peek_offset = peek_offset + 1;
    } else if (first_required) {
        return false;
    }
    if (second_is != NULL) {
        if (second_is(Header_Parser__peek_token(self, peek_offset))) {
            peek_offset = peek_offset + 1;
        } else if (second_required) {
            return false;
        }
    }
    if (third_is != NULL) {
        return third_is(Header_Parser__peek_token(self, peek_offset));
    }
    return true;
}

bool Header_Parser__matches_two(Header_Parser *self, bool (*first_is)(Token *token), bool first_required, bool (*second_is)(Token *token)) {
    return Header_Parser__matches_three(self, first_is, first_required, second_is, true, NULL);
}

bool Header_Parser__matches_one(Header_Parser *self, bool (*first_is)(Token *token)) {
    return Header_Parser__matches_two(self, first_is, true, NULL);
}

Token *Header_Parser__consume_token(Header_Parser *self, bool (*check)(Token *token)) {
    if (Header_Parser__matches_one(self, check)) {
        Token *token = self->scanner->current_token;
        Scanner__next_token(self->scanner);
        return token;
    }
    Header_Parser__error(self, String__create_from("Unexpected token"));
    abort();
}

void Header_Parser__consume_comment(Header_Parser *self) {
    Header_Parser__consume_token(self, Token__is_comment);
}

void Header_Parser__consume_space(Header_Parser *self, uint16_t count) {
    if (Header_Parser__matches_one(self, Token__is_space)) {
        Space_Token *token = (Space_Token *)Header_Parser__consume_token(self, Token__is_space);
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

void Header_Parser__consume_end_of_line(Header_Parser *self) {
    if (Header_Parser__matches_two(self, Token__is_space, false, Token__is_comment)) {
        Header_Parser__consume_space(self, 1);
        Header_Parser__consume_comment(self);
    } else {
        Header_Parser__consume_space(self, 0);
    }
    Token *token = Header_Parser__consume_token(self, Token__is_end_of_line);
    if (Token__is_end_of_file(token)) {
        Token__warning(token, String__create_from("Unexpected end of file"));
    }
}

bool Header_Parser__consume_empty_line(Header_Parser *self) {
    if (Header_Parser__matches_one(self, Token__is_end_of_file)) {
        return false;
    }
    if (Header_Parser__matches_three(self, Token__is_space, false, Token__is_comment, false, Token__is_end_of_line)) {
        if (Header_Parser__matches_two(self, Token__is_space, false, Token__is_comment)) {
            Header_Parser__consume_space(self, self->current_identation * 4);
            Header_Parser__consume_comment(self);
        } else {
            Header_Parser__consume_space(self, 0);
        }
        Header_Parser__consume_token(self, Token__is_end_of_line);
        return true;
    }
    return false;
}

Parsed_Type *Header_Parser__parse_type(Header_Parser *self);

/*
struct
    | "typedef" "struct" IDENTIFIER ( "{" ( type "*"? IDENTIFIER ";" )* "}" )? IDENTIFIER ";"
*/
Parsed_Statement *Header_Parser__parse_struct(Header_Parser *self) {
    Source_Location *location = Header_Parser__consume_token(self, Token__is_typedef)->location;
    Header_Parser__consume_space(self, 1);
    Header_Parser__consume_token(self, Token__is_struct);
    Header_Parser__consume_space(self, 1);
    Token *local_name = Header_Parser__consume_token(self, Token__is_identifier);
    Parsed_Struct_Statement *struct_statement = Parsed_Struct_Statement__create(location, local_name);
    Header_Parser__consume_space(self, 1);
    if (!Header_Parser__matches_one(self, Token__is_identifier)) {
        Parsed_Struct_Member *last_member = NULL;
        Header_Parser__consume_token(self, Token__is_opening_brace);
        Header_Parser__consume_end_of_line(self);
        while (!Header_Parser__matches_two(self, Token__is_space, false, Token__is_closing_brace)) {
            while (Header_Parser__consume_empty_line(self)) {
                /* ignored */
            }
            Header_Parser__consume_space(self, (self->current_identation + 1) * 4);
            Parsed_Type *type = Header_Parser__parse_type(self);
            Token *name;
            if (type->kind == PARSED_TYPE_KIND__FUNCTION) {
                name = ((Parsed_Function_Type *)type)->symbol_name;
            } else {
                Header_Parser__consume_space(self, type->kind == PARSED_TYPE_KIND__POINTER ? 0 : 1);
                name = Header_Parser__consume_token(self, Token__is_identifier);
            }
            Header_Parser__consume_space(self, 0);
            Header_Parser__consume_token(self, Token__is_semicolon);
            Header_Parser__consume_end_of_line(self);
            Parsed_Struct_Member *member = Parsed_Struct_Member__create(name, type);
            if (last_member == NULL) {
                struct_statement->first_member = member;
                last_member = member;
            } else {
                last_member->next_member = member;
                last_member = member;
            }
        }
        Header_Parser__consume_space(self, 0);
        Header_Parser__consume_token(self, Token__is_closing_brace);
        Header_Parser__consume_space(self, 1);
    }
    Token *final_name = Header_Parser__consume_token(self, Token__is_identifier);
    if (!String__equals_string(final_name->lexeme, local_name->lexeme)) {
        Token__error(final_name, String__append_string(String__create_from("Final struct name doesn't match the local name: "), local_name->lexeme));
        abort();
    }
    Header_Parser__consume_space(self, 0);
    Header_Parser__consume_token(self, Token__is_semicolon);
    return (Parsed_Statement *)struct_statement;
}

/*
enum
    | "typedef" "enum" IDENTIFIER "{" ( IDENTIFIER "," )* "}" IDENTIFIER ";"
*/
Parsed_Statement *Header_Parser__parse_enum(Header_Parser *self) {
    Source_Location *location = Header_Parser__consume_token(self, Token__is_typedef)->location;
    Header_Parser__consume_space(self, 1);
    Header_Parser__consume_token(self, Token__is_enum);
    Header_Parser__consume_space(self, 1);
    Token *local_name = Header_Parser__consume_token(self, Token__is_identifier);
    Parsed_Enum_Statement *enum_statement = Parsed_Enum_Statement__create(location, local_name);
    Header_Parser__consume_space(self, 1);
    Header_Parser__consume_token(self, Token__is_opening_brace);
    Header_Parser__consume_end_of_line(self);
    self->current_identation = self->current_identation + 1;
    Parsed_Enum_Member *last_member = NULL;
    while (!Header_Parser__matches_two(self, Token__is_space, false, Token__is_closing_brace)) {
        while (Header_Parser__consume_empty_line(self)) {
            /* ignored */
        }
        Header_Parser__consume_space(self, self->current_identation * 4);
        Token *name = Header_Parser__consume_token(self, Token__is_identifier);
        Header_Parser__consume_space(self, 0);
        Parsed_Enum_Member *member = Parsed_Enum_Member__create(name);
        if (last_member == NULL) {
            enum_statement->first_member = member;
            last_member = member;
        } else {
            last_member->next_member = member;
            last_member = member;
        }
        if (Header_Parser__matches_one(self, Token__is_comma)) {
            Header_Parser__consume_token(self, Token__is_comma);
            Header_Parser__consume_end_of_line(self);
        } else {
            Header_Parser__consume_end_of_line(self);
            while (Header_Parser__consume_empty_line(self)) {
                /* ignored */
            }
            break;
        }
    }
    self->current_identation = self->current_identation - 1;
    Header_Parser__consume_space(self, self->current_identation * 4);
    Header_Parser__consume_token(self, Token__is_closing_brace);
    Header_Parser__consume_space(self, 1);
    Token *final_name = Header_Parser__consume_token(self, Token__is_identifier);
    if (!String__equals_string(final_name->lexeme, local_name->lexeme)) {
        Token__error(final_name, String__append_string(String__create_from("Final enum name doesn't match the local name: "), local_name->lexeme));
        abort();
    }
    Header_Parser__consume_space(self, 0);
    Header_Parser__consume_token(self, Token__is_semicolon);
    return (Parsed_Statement *)enum_statement;
}

/*
function_parameter
    | type IDENTIFIER
*/
Parsed_Function_Parameter *Header_Parser__parse_function_parameter(Header_Parser *self) {
    Parsed_Type *type = Header_Parser__parse_type(self);
    if (type->kind == PARSED_TYPE_KIND__FUNCTION) {
        Parsed_Function_Type *function_type = (Parsed_Function_Type *)type;
        return Parsed_Function_Parameter__create(function_type->symbol_name, type);
    }
    Header_Parser__consume_space(self, type->kind == PARSED_TYPE_KIND__POINTER ? 0 : 1);
    Token *name = Header_Parser__consume_token(self, Token__is_identifier);
    return Parsed_Function_Parameter__create(name, type);
}

/*
function_parameters
    | function_parameter ( "," function_parameter )*
*/
Parsed_Function_Parameter *Header_Parser__parse_function_parameters(Header_Parser *self) {
    Parsed_Function_Parameter *first_parameter = NULL;
    if (!Header_Parser__matches_two(self, Token__is_space, false, Token__is_closing_paren)) {
        Header_Parser__consume_space(self, 0);
        first_parameter = Header_Parser__parse_function_parameter(self);
        Parsed_Function_Parameter *last_parameter = first_parameter;
        while (Header_Parser__matches_two(self, Token__is_space, false, Token__is_comma)) {
            Header_Parser__consume_space(self, 0);
            Header_Parser__consume_token(self, Token__is_comma);
            Header_Parser__consume_space(self, 1);
            last_parameter->next_parameter = Header_Parser__parse_function_parameter(self);
            last_parameter = last_parameter->next_parameter;
        }
    }
    return first_parameter;
}

/*
type
    | "struct"? IDENTIFIER "*"* ( "(" "*" IDENTIFIER ")" "(" function_parameters ")" )?
*/
Parsed_Type *Header_Parser__parse_type(Header_Parser *self) {
    Token *struct_token = NULL;
    if (Header_Parser__matches_one(self, Token__is_struct)) {
        struct_token = Header_Parser__consume_token(self, Token__is_struct);
        Header_Parser__consume_space(self, 1);
    }
    Token *name = Header_Parser__consume_token(self, Token__is_identifier);
    Parsed_Type *type = Parsed_Named_Type__create(name);
    if (struct_token != NULL) {
        type = Parsed_Struct_Type__create(struct_token->location, type);
    }
    while (Header_Parser__matches_two(self, Token__is_space, false, Token__is_asterisk)) {
        Header_Parser__consume_space(self, type->kind == PARSED_TYPE_KIND__POINTER ? 0 : 1);
        Header_Parser__consume_token(self, Token__is_asterisk);
        type = Parsed_Pointer_Type__create(type);
    }
    if (Header_Parser__matches_two(self, Token__is_space, false, Token__is_opening_paren)) {
        Header_Parser__consume_space(self, type->kind == PARSED_TYPE_KIND__POINTER ? 0 : 1);
        Header_Parser__consume_token(self, Token__is_opening_paren);
        Header_Parser__consume_space(self, 0);
        Header_Parser__consume_token(self, Token__is_asterisk);
        Header_Parser__consume_space(self, 0);
        Token *symbol_name = Header_Parser__consume_token(self, Token__is_identifier);
        Header_Parser__consume_space(self, 0);
        Header_Parser__consume_token(self, Token__is_closing_paren);
        Header_Parser__consume_space(self, 0);
        Header_Parser__consume_token(self, Token__is_opening_paren);
        Parsed_Function_Parameter *first_parameter = Header_Parser__parse_function_parameters(self);
        Header_Parser__consume_space(self, 0);
        Header_Parser__consume_token(self, Token__is_closing_paren);
        type = Parsed_Function_Type__create(symbol_name, first_parameter, type);
    }
    return type;
}

/*
external_variable
    | "extern" type IDENTIFIER";"
*/
Parsed_Statement *Header_Parser__parse_external_variable(Header_Parser *self) {
    Source_Location *location = Header_Parser__consume_token(self, Token__is_extern)->location;
    Header_Parser__consume_space(self, 1);
    Parsed_Type *type = Header_Parser__parse_type(self);
    Header_Parser__consume_space(self, type->kind == PARSED_TYPE_KIND__POINTER ? 0 : 1);
    Token *name = Header_Parser__consume_token(self, Token__is_identifier);
    Parsed_Variable_Statement *variable_statement = Parsed_Variable_Statement__create(location, name, type, true);
    Header_Parser__consume_space(self, 0);
    Header_Parser__consume_token(self, Token__is_semicolon);
    return (Parsed_Statement *)variable_statement;
}

void Header_Parser__parse_statements(Header_Parser *self, Parsed_Statements *statements);

/*
function
    | type IDENTIFIER "(" function_parameter* ")" ";"
*/
Parsed_Statement *Header_Parser__parse_function(Header_Parser *self) {
    Source_Location *location = Header_Parser__peek_token(self, 0)->location;
    Parsed_Type *return_type = Header_Parser__parse_type(self);
    Header_Parser__consume_space(self, return_type->kind == PARSED_TYPE_KIND__POINTER ? 0 : 1);
    Token *name = Header_Parser__consume_token(self, Token__is_identifier);
    Header_Parser__consume_space(self, 0);
    Header_Parser__consume_token(self, Token__is_opening_paren);
    Parsed_Function_Parameter *first_parameter = Header_Parser__parse_function_parameters(self);
    Header_Parser__consume_space(self, 0);
    Header_Parser__consume_token(self, Token__is_closing_paren);
    Header_Parser__consume_space(self, 0);
    Header_Parser__consume_token(self, Token__is_semicolon);
    return Parsed_Function_Statement__create(location, name, first_parameter, return_type, NULL, true);
}

/*
statement
    | enum
    | external_variable
    | function
    | struct
    | type_alias
*/
Parsed_Statement *Header_Parser__parse_statement(Header_Parser *self) {
    Header_Parser__consume_space(self, self->current_identation * 4);

    if (Header_Parser__matches_three(self, Token__is_typedef, true, Token__is_space, true, Token__is_struct)) {
        return Header_Parser__parse_struct(self);
    }

    if (Header_Parser__matches_three(self, Token__is_typedef, true, Token__is_space, true, Token__is_enum)) {
        return Header_Parser__parse_enum(self);
    }

    if (Header_Parser__matches_one(self, Token__is_extern) || Header_Parser__matches_one(self, Token__is_identifier)) {
        uint8_t peek_offset = 0;
        if (Token__is_extern(Header_Parser__peek_token(self, peek_offset))) {
            peek_offset = peek_offset + 1;
            if (Token__is_space(Header_Parser__peek_token(self, peek_offset))) {
                peek_offset = peek_offset + 1;
            }
        }
        if (Token__is_identifier(Header_Parser__peek_token(self, peek_offset))) {
            peek_offset = peek_offset + 1;
            if (Token__is_space(Header_Parser__peek_token(self, peek_offset))) {
                peek_offset = peek_offset + 1;
            }
            while (Token__is_asterisk(Header_Parser__peek_token(self, peek_offset))) {
                peek_offset = peek_offset + 1;
                if (Token__is_space(Header_Parser__peek_token(self, peek_offset))) {
                    peek_offset = peek_offset + 1;
                }
            }
            if (Token__is_identifier(Header_Parser__peek_token(self, peek_offset))) {
                peek_offset = peek_offset + 1;
                if (Token__is_space(Header_Parser__peek_token(self, peek_offset))) {
                    peek_offset = peek_offset + 1;
                }
                if (Token__is_opening_paren(Header_Parser__peek_token(self, peek_offset))) {
                    return Header_Parser__parse_function(self);
                }
                return Header_Parser__parse_external_variable(self);
            }
        }
    }

    Header_Parser__error(self, String__create_from("Unexpected token"));
    abort();
}

void Header_Parser__parse_source(Header_Parser *self, Source *source);

/*
statements
    | ( statement )*
*/
void Header_Parser__parse_statements(Header_Parser *self, Parsed_Statements *statements) {
    while (true) {
        while (Header_Parser__consume_empty_line(self)) {
            /* ignored */
        }

        if (Header_Parser__matches_three(self, Token__is_space, false, Token__is_comment, false, Token__is_end_of_line)) {
            return;
        }

        if (Header_Parser__matches_two(self, Token__is_space, false, Token__is_hash)) {
            Header_Parser__consume_space(self, 0);
            Header_Parser__consume_token(self, Token__is_hash);
            Header_Parser__consume_space(self, 0);
            Token *predicate = Header_Parser__consume_token(self, Token__is_identifier);
            if (String__equals_cstring(predicate->lexeme, "include") && Header_Parser__matches_two(self, Token__is_space, false, Token__is_string)) {
                Header_Parser__consume_space(self, 1);
                String_Token *path_token = (String_Token *)Header_Parser__consume_token(self, Token__is_string);

                /* Create relative path to current source */
                String *file_path = String__create_from(self->scanner->source->file_path->data);
                while (file_path->length > 0 && file_path->data[file_path->length - 1] != '/') {
                    file_path->length--;
                }
                String__append_string(file_path, path_token->value);
                String__end_with_zero(file_path);

                /* Check if source was already parsed */
                Source *source = self->scanner->source;
                while (source != NULL) {
                    if (String__equals_string(source->file_path, file_path)) {
                        break;
                    }
                    source = source->prev;
                }
                if (source == NULL) {
                    source = self->scanner->source->next;
                    while (source != NULL) {
                        if (String__equals_string(source->file_path, file_path)) {
                            break;
                        }
                        source = source->next;
                    }

                    if (source == NULL) {
                        Source *source = Source__create(file_path);

                        Source *last_source = self->scanner->source;
                        while (last_source->next != NULL) {
                            last_source = last_source->next;
                        }
                        last_source->next = source;
                        source->prev = last_source;

                        Header_Parser__parse_source(self, source);
                    }
                }
            } else {
                /* Skip preprocessor directive */
                while (!Header_Parser__matches_one(self, Token__is_end_of_line)) {
                    Header_Parser__consume_token(self, Token__is_anything);
                }
            }
        } else {
            Parsed_Statement *statement = Header_Parser__parse_statement(self);

            Parsed_Statements__append(statements, statement);
        }

        Header_Parser__consume_end_of_line(self);
    }
}

void Header_Parser__parse_source(Header_Parser *self, Source *source) {
    Header_Scanner *other_scanner = self->scanner;

    self->scanner = Header_Scanner__create(source);

    Header_Parser__parse_statements(self, self->parsed_source->statements);

    Token *last_token = Header_Parser__peek_token(self, 0);
    if (!Token__is_end_of_file(last_token)) {
        Header_Parser__error(self, String__create_from("Scanner didn't reach end of file"));
        abort();
    } else if (last_token->location->column != 1) {
        Header_Parser__warning(self, String__create_from("No new line at the end of file"));
    }

    self->scanner = other_scanner;
}

Parsed_Source *parse_header(Source *source) {
    Header_Parser parser;
    parser.scanner = NULL;
    parser.parsed_source = Parsed_Source__create();
    parser.parsed_source->first_source = source;
    parser.current_identation = 0;

    Header_Parser__parse_source(&parser, source);

    return parser.parsed_source;
}
