/* Copyright (C) 2024 Stefan Selariu */

#include "Token.h"

Writer *pWriter__write__token_kind(Writer *writer, enum Token_Kind token_kind) {
    switch (token_kind) {
    case TOKEN_KIND__CHARACTER:
        return pWriter__write__cstring(writer, "TOKEN_KIND__CHARACTER");
    case TOKEN_KIND__COMMENT:
        return pWriter__write__cstring(writer, "TOKEN_KIND__COMMENT");
    case TOKEN_KIND__END_OF_FILE:
        return pWriter__write__cstring(writer, "TOKEN_KIND__END_OF_FILE");
    case TOKEN_KIND__END_OF_LINE:
        return pWriter__write__cstring(writer, "TOKEN_KIND__END_OF_LINE");
    case TOKEN_KIND__ERROR:
        return pWriter__write__cstring(writer, "TOKEN_KIND__ERROR");
    case TOKEN_KIND__IDENTIFIER:
        return pWriter__write__cstring(writer, "TOKEN_KIND__IDENTIFIER");
    case TOKEN_KIND__INTEGER:
        return pWriter__write__cstring(writer, "TOKEN_KIND__INTEGER");
    case TOKEN_KIND__KEYWORD:
        return pWriter__write__cstring(writer, "TOKEN_KIND__KEYWORD");
    case TOKEN_KIND__OTHER:
        return pWriter__write__cstring(writer, "TOKEN_KIND__OTHER");
    case TOKEN_KIND__SPACE:
        return pWriter__write__cstring(writer, "TOKEN_KIND__SPACE");
    case TOKEN_KIND__STRING:
        return pWriter__write__cstring(writer, "TOKEN_KIND__STRING");
    default:
        fprintf(stderr, "Unknown token kind: %d\n", token_kind);
        panic();
    }
}

Token *Token__create_kind(Token_Kind kind, size_t kind_size, Source_Location *location, String *lexeme) {
    Token *token = (Token *)malloc(kind_size);
    token->kind = kind;
    token->location = location;
    token->lexeme = lexeme;
    token->next_token = NULL;
    return token;
}

void Token__error(Token *self, String *message) {
    Source_Location__error(self->location, message);
}

void Token__warning(Token *self, String *message) {
    Source_Location__warning(self->location, message);
}

Character_Token *Character_Token__create(Source_Location *location, String *lexeme, char value) {
    Character_Token *token = (Character_Token *)Token__create_kind(TOKEN_KIND__CHARACTER, sizeof(Character_Token), location, lexeme);
    token->value = value;
    return token;
}

Comment_Token *Comment_Token__create(Source_Location *location, String *lexeme) {
    return (Comment_Token *)Token__create_kind(TOKEN_KIND__COMMENT, sizeof(Comment_Token), location, lexeme);
}

End_Of_File_Token *End_Of_File_Token__create(Source_Location *location, String *lexeme) {
    return (End_Of_File_Token *)Token__create_kind(TOKEN_KIND__END_OF_FILE, sizeof(End_Of_File_Token), location, lexeme);
}

End_Of_Line_Token *End_Of_Line_Token__create(Source_Location *location, String *lexeme) {
    return (End_Of_Line_Token *)Token__create_kind(TOKEN_KIND__END_OF_LINE, sizeof(End_Of_Line_Token), location, lexeme);
}

Error_Token *Error_Token__create(Source_Location *location, String *lexeme) {
    return (Error_Token *)Token__create_kind(TOKEN_KIND__ERROR, sizeof(Error_Token), location, lexeme);
}

Identifier_Token *Identifier_Token__create(Source_Location *location, String *lexeme) {
    return (Identifier_Token *)Token__create_kind(TOKEN_KIND__IDENTIFIER, sizeof(Identifier_Token), location, lexeme);
}

Integer_Token *Integer_Token__create(Source_Location *location, String *lexeme, uint64_t value) {
    Integer_Token *token = (Integer_Token *)Token__create_kind(TOKEN_KIND__INTEGER, sizeof(Integer_Token), location, lexeme);
    token->value = value;
    return token;
}

Other_Token *Other_Token__create(Source_Location *location, String *lexeme) {
    return (Other_Token *)Token__create_kind(TOKEN_KIND__OTHER, sizeof(Other_Token), location, lexeme);
}

Space_Token *Space_Token__create(Source_Location *location, String *lexeme, uint16_t count) {
    Space_Token *token = (Space_Token *)Token__create_kind(TOKEN_KIND__SPACE, sizeof(Space_Token), location, lexeme);
    token->count = count;
    return token;
}

String_Token *String_Token__create(Source_Location *location, String *lexeme, String *value) {
    String_Token *token = (String_Token *)Token__create_kind(TOKEN_KIND__STRING, sizeof(String_Token), location, lexeme);
    token->value = value;
    return token;
}

bool Token__is_anything(Token *self) {
    return true;
}

bool Token__is_character(Token *self) {
    return self->kind == TOKEN_KIND__CHARACTER;
}

bool Token__is_comment(Token *self) {
    return self->kind == TOKEN_KIND__COMMENT;
}

bool Token__is_end_of_file(Token *self) {
    return self->kind == TOKEN_KIND__END_OF_FILE;
}

bool Token__is_end_of_line(Token *self) {
    return self->kind == TOKEN_KIND__END_OF_LINE || self->kind == TOKEN_KIND__END_OF_FILE;
}

bool Token__is_identifier(Token *self) {
    return self->kind == TOKEN_KIND__IDENTIFIER;
}

bool Token__is_integer(Token *self) {
    return self->kind == TOKEN_KIND__INTEGER;
}

bool Token__is_keyword(Token *self, char *lexeme) {
    return self->kind == TOKEN_KIND__IDENTIFIER && String__equals_cstring(self->lexeme, lexeme);
}

bool Token__is_and(Token *self) {
    return Token__is_keyword(self, "and");
}

bool Token__is_anon(Token *self) {
    return Token__is_keyword(self, "anon");
}

bool Token__is_break(Token *self) {
    return Token__is_keyword(self, "break");
}

bool Token__is_else(Token *self) {
    return Token__is_keyword(self, "else");
}

bool Token__is_enum(Token *self) {
    return Token__is_keyword(self, "enum");
}

bool Token__is_extern(Token *self) {
    return Token__is_keyword(self, "extern");
}

bool Token__is_external(Token *self) {
    return Token__is_keyword(self, "external");
}

bool Token__is_false(Token *self) {
    return Token__is_keyword(self, "false");
}

bool Token__is_func(Token *self) {
    return Token__is_keyword(self, "func");
}

bool Token__is_if(Token *self) {
    return Token__is_keyword(self, "if");
}

bool Token__is_let(Token *self) {
    return Token__is_keyword(self, "let");
}

bool Token__is_loop(Token *self) {
    return Token__is_keyword(self, "loop");
}

bool Token__is_not(Token *self) {
    return Token__is_keyword(self, "not");
}

bool Token__is_null(Token *self) {
    return Token__is_keyword(self, "null");
}

bool Token__is_or(Token *self) {
    return Token__is_keyword(self, "or");
}

bool Token__is_return(Token *self) {
    return Token__is_keyword(self, "return");
}

bool Token__is_sizeof(Token *self) {
    return Token__is_keyword(self, "sizeof");
}

bool Token__is_struct(Token *self) {
    return Token__is_keyword(self, "struct");
}

bool Token__is_true(Token *self) {
    return Token__is_keyword(self, "true");
}

bool Token__is_type(Token *self) {
    return Token__is_keyword(self, "type");
}

bool Token__is_typedef(Token *self) {
    return Token__is_keyword(self, "typedef");
}

bool Token__is_while(Token *self) {
    return Token__is_keyword(self, "while");
}

bool Token__is_other(Token *self, char *lexeme) {
    return self->kind == TOKEN_KIND__OTHER && String__equals_cstring(self->lexeme, lexeme);
}

bool Token__is_ampersand(Token *self) {
    return Token__is_other(self, "&");
}

bool Token__is_asterisk(Token *self) {
    return Token__is_other(self, "*");
}

bool Token__is_at(Token *self) {
    return Token__is_other(self, "@");
}

bool Token__is_closing_brace(Token *self) {
    return Token__is_other(self, "}");
}

bool Token__is_closing_bracket(Token *self) {
    return Token__is_other(self, "]");
}

bool Token__is_closing_paren(Token *self) {
    return Token__is_other(self, ")");
}

bool Token__is_colon(Token *self) {
    return Token__is_other(self, ":");
}

bool Token__is_comma(Token *self) {
    return Token__is_other(self, ",");
}

bool Token__is_dot(Token *self) {
    return Token__is_other(self, ".");
}

bool Token__is_equals(Token *self) {
    return Token__is_other(self, "=");
}

bool Token__is_exclamation_mark(Token *self) {
    return Token__is_other(self, "!");
}

bool Token__is_greater_than(Token *self) {
    return Token__is_other(self, ">");
}

bool Token__is_hash(Token *self) {
    return Token__is_other(self, "#");
}

bool Token__is_less_than(Token *self) {
    return Token__is_other(self, "<");
}

bool Token__is_minus(Token *self) {
    return Token__is_other(self, "-");
}

bool Token__is_opening_brace(Token *self) {
    return Token__is_other(self, "{");
}

bool Token__is_opening_bracket(Token *self) {
    return Token__is_other(self, "[");
}

bool Token__is_opening_paren(Token *self) {
    return Token__is_other(self, "(");
}

bool Token__is_percent(Token *self) {
    return Token__is_other(self, "%");
}

bool Token__is_plus(Token *self) {
    return Token__is_other(self, "+");
}

bool Token__is_semicolon(Token *self) {
    return Token__is_other(self, ";");
}

bool Token__is_slash(Token *self) {
    return Token__is_other(self, "/");
}

bool Token__is_vertical_bar(Token *self) {
    return Token__is_other(self, "|");
}

bool Token__is_space(Token *self) {
    return self->kind == TOKEN_KIND__SPACE;
}

bool Token__is_string(Token *self) {
    return self->kind == TOKEN_KIND__STRING;
}

void pWriter__write__token(Writer *writer, Token *token) {
    bool colored = token->kind == TOKEN_KIND__COMMENT || token->kind == TOKEN_KIND__ERROR || token->kind == TOKEN_KIND__OTHER;
    if (colored) {
        if (token->kind == TOKEN_KIND__OTHER) {
            pWriter__write__cstring(writer, "\033[2;33m");
        } else if (token->kind == TOKEN_KIND__COMMENT) {
            pWriter__write__cstring(writer, "\033[2;37m");
        } else if (token->kind == TOKEN_KIND__ERROR) {
            pWriter__write__cstring(writer, "\033[2;31m");
        }
    }
    pWriter__write__string(writer, token->lexeme);
    if (colored) {
        pWriter__write__cstring(writer, "\033[0m");
    }
}
