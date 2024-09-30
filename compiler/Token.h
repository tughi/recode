/* Copyright (C) 2024 Stefan Selariu */

#ifndef __TOKEN_H__
#define __TOKEN_H__

#include "Source_Location.h"
#include "String.h"

typedef enum Token_Kind {
    TOKEN_KIND__CHARACTER,
    TOKEN_KIND__COMMENT,
    TOKEN_KIND__END_OF_FILE,
    TOKEN_KIND__END_OF_LINE,
    TOKEN_KIND__ERROR,
    TOKEN_KIND__IDENTIFIER,
    TOKEN_KIND__INTEGER,
    TOKEN_KIND__KEYWORD,
    TOKEN_KIND__OTHER,
    TOKEN_KIND__SPACE,
    TOKEN_KIND__STRING
} Token_Kind;

typedef struct Token {
    Token_Kind kind;
    Source_Location *location;
    String *lexeme;
    struct Token *next_token;
} Token;

Token *Token__create_kind(Token_Kind kind, size_t kind_size, Source_Location *location, String *lexeme);

typedef struct Character_Token {
    Token super;
    char value;
} Character_Token;

Character_Token *Character_Token__create(Source_Location *location, String *lexeme, char value);

typedef struct Comment_Token {
    Token super;
} Comment_Token;

Comment_Token *Comment_Token__create(Source_Location *location, String *lexeme);

typedef struct End_Of_File_Token {
    Token super;
} End_Of_File_Token;

End_Of_File_Token *End_Of_File_Token__create(Source_Location *location, String *lexeme);

typedef struct End_Of_Line_Token {
    Token super;
} End_Of_Line_Token;

End_Of_Line_Token *End_Of_Line_Token__create(Source_Location *location, String *lexeme);

typedef struct Error_Token {
    Token super;
} Error_Token;

Error_Token *Error_Token__create(Source_Location *location, String *lexeme);

typedef struct Identifier_Token {
    Token super;
} Identifier_Token;

Identifier_Token *Identifier_Token__create(Source_Location *location, String *lexeme);

typedef struct Integer_Token {
    Token super;
    uint64_t value;
} Integer_Token;

Integer_Token *Integer_Token__create(Source_Location *location, String *lexeme, uint64_t value);

typedef struct Other_Token {
    Token super;
} Other_Token;

Other_Token *Other_Token__create(Source_Location *location, String *lexeme);

typedef struct Space_Token {
    Token super;
    uint16_t count;
} Space_Token;

Space_Token *Space_Token__create(Source_Location *location, String *lexeme, uint16_t count);

typedef struct String_Token {
    Token super;
    String *value;
} String_Token;

String_Token *String_Token__create(Source_Location *location, String *lexeme, String *value);

bool Token__is_ampersand(Token *self);
bool Token__is_and(Token *self);
bool Token__is_anon(Token *self);
bool Token__is_anything(Token *self);
bool Token__is_as(Token *self);
bool Token__is_asterisk(Token *self);
bool Token__is_at(Token *self);
bool Token__is_break(Token *self);
bool Token__is_character(Token *self);
bool Token__is_closing_brace(Token *self);
bool Token__is_closing_bracket(Token *self);
bool Token__is_closing_paren(Token *self);
bool Token__is_colon(Token *self);
bool Token__is_comma(Token *self);
bool Token__is_comment(Token *self);
bool Token__is_dot(Token *self);
bool Token__is_else(Token *self);
bool Token__is_end_of_file(Token *self);
bool Token__is_end_of_line(Token *self);
bool Token__is_enum(Token *self);
bool Token__is_equals(Token *self);
bool Token__is_exclamation_mark(Token *self);
bool Token__is_extern(Token *self);
bool Token__is_external(Token *self);
bool Token__is_false(Token *self);
bool Token__is_func(Token *self);
bool Token__is_greater_than(Token *self);
bool Token__is_hash(Token *self);
bool Token__is_identifier(Token *self);
bool Token__is_if(Token *self);
bool Token__is_integer(Token *self);
bool Token__is_keyword(Token *self, char *lexeme);
bool Token__is_less_than(Token *self);
bool Token__is_let(Token *self);
bool Token__is_loop(Token *self);
bool Token__is_make(Token *self);
bool Token__is_minus(Token *self);
bool Token__is_not(Token *self);
bool Token__is_null(Token *self);
bool Token__is_opening_brace(Token *self);
bool Token__is_opening_bracket(Token *self);
bool Token__is_opening_paren(Token *self);
bool Token__is_or(Token *self);
bool Token__is_other(Token *self, char *lexeme);
bool Token__is_percent(Token *self);
bool Token__is_plus(Token *self);
bool Token__is_question_mark(Token *self);
bool Token__is_return(Token *self);
bool Token__is_semicolon(Token *self);
bool Token__is_sizeof(Token *self);
bool Token__is_slash(Token *self);
bool Token__is_space(Token *self);
bool Token__is_string(Token *self);
bool Token__is_struct(Token *self);
bool Token__is_true(Token *self);
bool Token__is_type(Token *self);
bool Token__is_typedef(Token *self);
bool Token__is_vertical_bar(Token *self);
bool Token__is_while(Token *self);

void pWriter__write__token(Writer *writer, Token *token);

#endif
