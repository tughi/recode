#pragma once

#include "String.h"
#include <stddef.h>

typedef struct Character_Token {
    String lexeme;
    size_t source_position;
} Character_Token;

typedef struct End_Of_File_Token {
    String lexeme;
    size_t source_position;
} End_Of_File_Token;

typedef struct End_Of_Line_Token {
    String lexeme;
    size_t source_position;
} End_Of_Line_Token;

typedef struct Error_Token {
    String lexeme;
    size_t source_position;
} Error_Token;

typedef struct Identifier_Token {
    String lexeme;
    size_t source_position;
} Identifier_Token;

typedef struct Integer_Token {
    String lexeme;
    size_t source_position;
} Integer_Token;

typedef struct Other_Token {
    String lexeme;
    size_t source_position;
    char value;
} Other_Token;

typedef struct Space_Token {
    String lexeme;
    size_t source_position;
    size_t count;
} Space_Token;

typedef struct String_Token {
    String lexeme;
    size_t source_position;
} String_Token;

typedef enum Token_Kind {
    TOKEN_KIND__CHARACTER,
    TOKEN_KIND__END_OF_FILE,
    TOKEN_KIND__END_OF_LINE,
    TOKEN_KIND__ERROR,
    TOKEN_KIND__IDENTIFIER,
    TOKEN_KIND__INTEGER,
    TOKEN_KIND__OTHER,
    TOKEN_KIND__SPACE,
    TOKEN_KIND__STRING
} Token_Kind;

typedef struct Token {
    Token_Kind kind;
    union {
        Character_Token character;
        End_Of_File_Token end_of_file;
        End_Of_Line_Token end_of_line;
        Error_Token error;
        Identifier_Token identifier;
        Integer_Token integer;
        Other_Token other;
        Space_Token space;
        String_Token string;
    };
} Token;
