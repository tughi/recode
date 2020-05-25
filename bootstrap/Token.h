#ifndef __recode__token_h__
#define __recode__token_h__

#include "List.h"
#include "Source.h"
#include "String.h"

typedef struct Token {
    enum {
        TOKEN__CHARACTER,
        TOKEN__COMMENT,
        TOKEN__END_OF_FILE,
        TOKEN__END_OF_LINE,
        TOKEN__ERROR,
        TOKEN__IDENTIFIER,
        TOKEN__INTEGER,
        TOKEN__KEYWORD,
        TOKEN__OTHER,
        TOKEN__SPACE,
        TOKEN__STRING,
    } kind;

    Source_Location *location;
    String *lexeme;

    union {
        struct {
            char value;
        } character_data;
        struct {
            int value;
        } integer_data;
        struct {
            int count;
        } space_data;
        struct {
            String *value;
        } string_data;
    };
} Token;

typedef List Token_List;

Token *token__create_character(Source_Location *location, String *lexeme, char value);
Token *token__create_comment(Source_Location *location, String *lexeme);
Token *token__create_end_of_file(Source_Location *location, String *lexeme);
Token *token__create_end_of_line(Source_Location *location, String *lexeme);
Token *token__create_error(Source_Location *location, String *lexeme);
Token *token__create_identifier(Source_Location *location, String *lexeme);
Token *token__create_integer(Source_Location *location, String *lexeme, int value);
Token *token__create_keyword(Source_Location *location, String *lexeme);
Token *token__create_other(Source_Location *location, String *lexeme);
Token *token__create_space(Source_Location *location, String *lexeme, int count);
Token *token__create_string(Source_Location *location, String *lexeme, String *value);

char *token__get_kind_name(Token *self);
void token__join(Token *self, Token *other);

#endif
