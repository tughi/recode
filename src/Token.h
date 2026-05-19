#pragma once

#include "Source_Location.h"
#include "String.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct Character_Token {
    String lexeme;
    Source_Location location;
    uint8_t value;
} Character_Token;

typedef struct Comment_Token {
    String lexeme;
    Source_Location location;
} Comment_Token;

typedef struct End_Of_File_Token {
    String lexeme;
    Source_Location location;
} End_Of_File_Token;

typedef struct End_Of_Line_Token {
    String lexeme;
    Source_Location location;
} End_Of_Line_Token;

typedef struct Error_Token {
    String lexeme;
    Source_Location location;
} Error_Token;

typedef struct Identifier_Token {
    String lexeme;
    Source_Location location;
} Identifier_Token;

typedef struct Integer_Token {
    String lexeme;
    Source_Location location;
    uint64_t value;
    bool overflow;
} Integer_Token;

typedef struct Label_Token {
    String lexeme;
    Source_Location location;
    size_t value;
} Label_Token;

typedef struct Other_Token {
    String lexeme;
    Source_Location location;
    char value;
} Other_Token;

typedef struct Space_Token {
    String lexeme;
    Source_Location location;
    size_t count;
} Space_Token;

typedef struct String_Token {
    String lexeme;
    Source_Location location;
} String_Token;

typedef struct Variable_Token {
    String lexeme;
    Source_Location location;
    char prefix;
} Variable_Token;

typedef enum Token_Kind {
    TOKEN_KIND__CHARACTER,
    TOKEN_KIND__COMMENT,
    TOKEN_KIND__END_OF_FILE,
    TOKEN_KIND__END_OF_LINE,
    TOKEN_KIND__ERROR,
    TOKEN_KIND__IDENTIFIER,
    TOKEN_KIND__INTEGER,
    TOKEN_KIND__LABEL,
    TOKEN_KIND__OTHER,
    TOKEN_KIND__SPACE,
    TOKEN_KIND__STRING,
    TOKEN_KIND__VARIABLE,
    TOKEN_KINDS,
} Token_Kind;

typedef struct Token {
    Token_Kind kind;
    union {
        struct {
            String lexeme;
            Source_Location location;
        };
        Character_Token character;
        Comment_Token comment;
        End_Of_File_Token end_of_file;
        End_Of_Line_Token end_of_line;
        Error_Token error;
        Identifier_Token identifier;
        Integer_Token integer;
        Label_Token label;
        Other_Token other;
        Space_Token space;
        String_Token string;
        Variable_Token variable;
    };
} Token;
