// Copyright (C) 2023 Stefan Selariu

// Types

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

// LibC

typedef struct FILE File;

extern File *stdin;
extern File *stdout;
extern File *stderr;

extern int32_t fgetc(File *stream);
extern int32_t fputc(int32_t c, File *stream);
extern int32_t fputs(const char *s, File *stream);

extern void *malloc(size_t size);
extern void *realloc(void *ptr, size_t size);
extern void free(void *ptr);

extern void abort();

// String

typedef struct {
    uint8_t *data;
    size_t data_size;
    size_t length;
} String;

String *String__create_empty(size_t data_size) {
    String *string = malloc(sizeof(String));
    string->data = malloc(data_size);
    string->data_size = data_size;
    string->length = 0;
    return string;
}

String *String__create() {
    return String__create_empty(16);
}

size_t cstring_length(const char *s) {
    size_t length = 0;
    while (true) {
        uint8_t c = s[length];
        if (c == 0) {
            break;
        }
        length += 1;
    }
    return length;
}

String *String__create_from(uint8_t *data) {
    size_t string_length = cstring_length(data);
    String *string = malloc(sizeof(String));
    string->data = data;
    string->data_size = string_length + 1;
    string->length = string_length;
    return string;
}

String *String__append_char(String *self, uint8_t ch) {
    if (self->length >= self->data_size) {
        self->data_size = self->data_size + 16;
        self->data = realloc(self->data, self->data_size);
    }
    self->data[self->length] = ch;
    self->length = self->length + 1;
    return self;
}

bool String__equals_cstring(String *self, const char *s) {
    size_t length = cstring_length(s);
    if (self->length != length) {
        return false;
    }

    size_t index = 0;
    while (index < length) {
        if (self->data[index] != s[index]) {
            return false;
        }
        index = index + 1;
    }

    return true;
}

// Utils

void pass() {
}

void File__write_char(File *stream, uint8_t c) {
    fputc(c, stream);
}

void File__write_cstring(File *stream, const char *s) {
    fputs(s, stream);
}

void File__write_int32_t(File *stream, int32_t value) {
    if (value < 0) {
        File__write_char(stream, '-');
        File__write_int32_t(stream, -value);
    } else {
        if (value >= 10) {
            File__write_int32_t(stream, value / 10);
        }
        File__write_char(stream, value % 10 + '0');
    }
}

void File__write_string(File *self, String *string) {
    size_t index = 0;
    while (index < string->length) {
        File__write_char(self, string->data[index]);
        index = index + 1;
    }
}

void panic(String *message) {
    File__write_cstring(stderr, "\e[0;91m");
    File__write_string(stderr, message);
    File__write_cstring(stderr, "\e[0m\n");
    abort();
}

void warning(String *message) {
    File__write_cstring(stderr, "\e[0;96m");
    File__write_string(stderr, message);
    File__write_cstring(stderr, "\e[0m\n");
}

// Source

typedef struct {
    String *content;
} Source;

Source *Source__create(File *stream) {
    String *source_content = String__create();

    while (true) {
        int32_t ch = fgetc(stdin);
        if (ch == -1) {
            break;
        }
        String__append_char(source_content, ch);
    }

    String__append_char(source_content, '\0'); // simplifies EOF detection

    Source *source = malloc(sizeof(Source));
    source->content = source_content;

    return source;
}

// Token

typedef struct {
    Source *source;
    uint16_t line;
    uint16_t column;
} Token_Location;

Token_Location *Token_Location__create(Source *source, uint16_t line, uint16_t column) {
    Token_Location *token_location = malloc(sizeof(Token_Location));
    token_location->source = source;
    token_location->line = line;
    token_location->column = column;
    return token_location;
}

void File__write_token_location(File *stream, Token_Location *self) {
    File__write_cstring(stream, "compiler/ReCode.c:");
    File__write_int32_t(stream, self->line);
    File__write_char(stream, ':');
    File__write_int32_t(stream, self->column);
    File__write_cstring(stream, ": ");
}

void Token_Location__panic(Token_Location *self, String *message) {
    File__write_token_location(stderr, self);
    panic(message);
}

void Token_Location__warning(Token_Location *self, String *message) {
    File__write_token_location(stderr, self);
    warning(message);
}

typedef enum {
    TOKEN_TYPE_CHARACTER,
    TOKEN_TYPE_COMMENT,
    TOKEN_TYPE_END_OF_FILE,
    TOKEN_TYPE_END_OF_LINE,
    TOKEN_TYPE_ERROR,
    TOKEN_TYPE_IDENTIFIER,
    TOKEN_TYPE_INTEGER,
    TOKEN_TYPE_KEYWORD,
    TOKEN_TYPE_OTHER,
    TOKEN_TYPE_SPACE,
    TOKEN_TYPE_STRING,
} Token_Type;

typedef struct Token {
    Token_Type type;
    Token_Location *location;
    String *lexeme;
    struct Token *next_token;
} Token;

void *Token__create(size_t size, uint16_t type, Token_Location *location, String *lexeme) {
    Token *token = malloc(size);
    token->type = type;
    token->location = location;
    token->lexeme = lexeme;
    token->next_token = 0;
    return token;
}

void Token__panic(Token *self, String *message) {
    Token_Location__panic(self->location, message);
}

void Token__warning(Token *self, String *message) {
    Token_Location__warning(self->location, message);
}

typedef struct {
    Token_Type type;
    Source *source;
    String *lexeme;
    Token *next_token;
    uint8_t value;
} Character_Token;

Character_Token *Character_Token__create(Token_Location *location, String *lexeme, uint8_t value) {
    Character_Token *token = Token__create(sizeof(Character_Token), TOKEN_TYPE_CHARACTER, location, lexeme);
    token->value = value;
    return token;
}

typedef struct {
    Token_Type type;
    Source *source;
    String *lexeme;
    Token *next_token;
} Comment_Token;

Comment_Token *Comment_Token__create(Token_Location *location, String *lexeme) {
    return Token__create(sizeof(Comment_Token), TOKEN_TYPE_COMMENT, location, lexeme);
}

typedef struct {
    Token_Type type;
    Source *source;
    String *lexeme;
    Token *next_token;
} End_Of_File_Token;

End_Of_File_Token *End_Of_File_Token__create(Token_Location *location, String *lexeme) {
    return Token__create(sizeof(End_Of_File_Token), TOKEN_TYPE_END_OF_FILE, location, lexeme);
}

typedef struct {
    Token_Type type;
    Source *source;
    String *lexeme;
    Token *next_token;
} End_Of_Line_Token;

End_Of_Line_Token *End_Of_Line_Token__create(Token_Location *location, String *lexeme) {
    return Token__create(sizeof(End_Of_Line_Token), TOKEN_TYPE_END_OF_LINE, location, lexeme);
}

typedef struct {
    Token_Type type;
    Source *source;
    String *lexeme;
    Token *next_token;
} Error_Token;

Error_Token *Error_Token__create(Token_Location *location, String *lexeme) {
    return Token__create(sizeof(Error_Token), TOKEN_TYPE_ERROR, location, lexeme);
}

typedef struct {
    Token_Type type;
    Source *source;
    String *lexeme;
    Token *next_token;
} Identifier_Token;

Identifier_Token *Identifier_Token__create(Token_Location *location, String *lexeme) {
    return Token__create(sizeof(Identifier_Token), TOKEN_TYPE_IDENTIFIER, location, lexeme);
}

typedef struct {
    Token_Type type;
    Source *source;
    String *lexeme;
    Token *next_token;
    uint64_t value;
} Integer_Token;

Integer_Token *Integer_Token__create(Token_Location *location, String *lexeme, uint64_t value) {
    Integer_Token *token = Token__create(sizeof(Integer_Token), TOKEN_TYPE_INTEGER, location, lexeme);
    token->value = value;
    return token;
}

typedef struct {
    Token_Type type;
    Source *source;
    String *lexeme;
    Token *next_token;
} Other_Token;

Other_Token *Other_Token__create(Token_Location *location, String *lexeme) {
    return Token__create(sizeof(Other_Token), TOKEN_TYPE_OTHER, location, lexeme);
}

typedef struct {
    Token_Type type;
    Source *source;
    String *lexeme;
    Token *next_token;
    uint16_t count;
} Space_Token;

Space_Token *Space_Token__create(Token_Location *location, String *lexeme, uint16_t count) {
    Space_Token *token = Token__create(sizeof(Space_Token), TOKEN_TYPE_SPACE, location, lexeme);
    token->count = count;
    return token;
}

typedef struct {
    Token_Type type;
    Source *source;
    String *lexeme;
    Token *next_token;
    String *value;
} String_Token;

String_Token *String_Token__create(Token_Location *location, String *lexeme, String *value) {
    String_Token *token = Token__create(sizeof(String_Token), TOKEN_TYPE_STRING, location, lexeme);
    token->value = value;
    return token;
}

void File__write_token(File *stream, Token *token) {
    bool colored = token->type == TOKEN_TYPE_COMMENT || token->type == TOKEN_TYPE_ERROR || token->type == TOKEN_TYPE_OTHER;
    if (colored) {
        if (token->type == TOKEN_TYPE_OTHER) {
            File__write_cstring(stream, "\e[2;33m");
        } else if (token->type == TOKEN_TYPE_COMMENT) {
            File__write_cstring(stream, "\e[2;37m");
        } else if (token->type == TOKEN_TYPE_ERROR) {
            File__write_cstring(stream, "\e[2;31m");
        }
    }
    File__write_string(stream, token->lexeme);
    if (colored) {
        File__write_cstring(stream, "\e[0m");
    }
}

// Scanner

typedef struct {
    Source *source;
    size_t current_char_index;
    size_t current_line;
    size_t current_column;
    Token *current_token;
} Scanner;

uint8_t Scanner__peek_char(Scanner *self) {
    return self->source->content->data[self->current_char_index];
}

uint8_t Scanner__next_char(Scanner *self) {
    uint8_t next_char = Scanner__peek_char(self);
    if (next_char != '\0') {
        self->current_char_index = self->current_char_index + 1;
        if (next_char == '\n') {
            self->current_line = self->current_line + 1;
            self->current_column = 1;
        } else {
            self->current_column = self->current_column + 1;
        }
    }
    return next_char;
}

uint8_t escape_char_value(uint8_t c) {
    if (c == 'n') return '\n';
    if (c == '"') return '\"';
    if (c == '\'') return '\'';
    if (c == '\\') return '\\';
    if (c == 't') return '\t';
    if (c == '0') return '\0';
    if (c == 'e') return '\e';
    return -1;
}

bool char_is_end_of_line(uint8_t c) {
    return c == '\n' || c == '\0';
}

Token *Scanner__scan_character_token(Scanner *self, Token_Location *token_location, String *token_lexeme) {
    if (Scanner__next_char(self) != '\'') {
        panic(String__create_from("Unexpected char"));
    }
    String__append_char(token_lexeme, '\'');

    uint8_t next_char = Scanner__peek_char(self);
    if (char_is_end_of_line(next_char) || next_char == '\t') {
        return (Token *) Error_Token__create(token_location, token_lexeme);
    }

    String__append_char(token_lexeme, Scanner__next_char(self));
    uint8_t value = next_char;

    if (value == '\'') {
        return (Token *) Error_Token__create(token_location, token_lexeme);
    }

    if (value == '\\') {
        next_char = Scanner__peek_char(self);
        if (char_is_end_of_line(next_char) || next_char == '\t') {
            return (Token *) Error_Token__create(token_location, token_lexeme);
        }

        String__append_char(token_lexeme, Scanner__next_char(self));

        value = escape_char_value(next_char);
        if (value == ((uint8_t) -1)) {
            return (Token *) Error_Token__create(token_location, token_lexeme);
        }
    }

    if (Scanner__peek_char(self) != '\'') {
        return (Token *) Error_Token__create(token_location, token_lexeme);
    }

    String__append_char(token_lexeme, Scanner__next_char(self));
    return (Token *) Character_Token__create(token_location, token_lexeme, value);
}

Token *Scanner__scan_comment_token(Scanner *self, Token_Location *token_location, String *token_lexeme) {
    while (!char_is_end_of_line(Scanner__peek_char(self))) {
        String__append_char(token_lexeme, Scanner__next_char(self));
    }
    return (Token *) Comment_Token__create(token_location, token_lexeme);
}

bool char_is_identifier_start(uint8_t c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool char_is_identifier_letter(uint8_t c) {
    return char_is_identifier_start(c) || (c >= '0' && c <= '9');
}

Token *Scanner__scan_identifier_token(Scanner *self, Token_Location *token_location, String *token_lexeme) {
    while (char_is_identifier_letter(Scanner__peek_char(self))) {
        String__append_char(token_lexeme, Scanner__next_char(self));
    }
    return (Token *) Identifier_Token__create(token_location, token_lexeme);
}

bool char_is_digit(uint8_t c) {
    return c >= '0' && c <= '9';
}

Token *Scanner__scan_integer_token(Scanner *self, Token_Location *token_location, String *token_lexeme) {
    uint64_t value = 0;
    while (char_is_digit(Scanner__peek_char(self))) {
        uint8_t c = Scanner__next_char(self);
        value = value * 10 + (c - '0');
        String__append_char(token_lexeme, c);
    }
    return (Token *) Integer_Token__create(token_location, token_lexeme, value);
}

bool char_is_space(uint8_t c) {
    return c == ' ';
}

Token *Scanner__scan_space_token(Scanner *self, Token_Location *token_location, String *token_lexeme) {
    uint16_t count = 0;
    while (char_is_space(Scanner__peek_char(self))) {
        count = count + 1;
        String__append_char(token_lexeme, Scanner__next_char(self));
    }
    return (Token *) Space_Token__create(token_location, token_lexeme, count);
}

Token *Scanner__scan_string_token(Scanner *self, Token_Location *token_location, String *token_lexeme) {
    if (Scanner__next_char(self) != '"') {
        panic(String__create_from("Unexpected char"));
    }
    String__append_char(token_lexeme, '"');

    String *value = String__create();

    while (true) {
        uint8_t next_char = Scanner__peek_char(self);
        if (char_is_end_of_line(next_char) || next_char == '\t') {
            return (Token *) Error_Token__create(token_location, token_lexeme);
        }

        String__append_char(token_lexeme, Scanner__next_char(self));

        if (next_char == '"') {
            return (Token *) String_Token__create(token_location, token_lexeme, value);
        }

        if (next_char == '\\') {
            next_char = Scanner__peek_char(self);
            if (char_is_end_of_line(next_char) || next_char == '\t') {
                return (Token *) Error_Token__create(token_location, token_lexeme);
            }

            String__append_char(token_lexeme, Scanner__next_char(self));

            next_char = escape_char_value(next_char);
            if (next_char == ((uint8_t) -1)) {
                return (Token *) Error_Token__create(token_location, token_lexeme);
            }
        }

        String__append_char(value, next_char);
    }
}

Token *Scanner__scan_token(Scanner *self) {
    Token_Location *token_location = Token_Location__create(self->source, self->current_line, self->current_column);
    String *token_lexeme = String__create();

    uint8_t next_char = Scanner__peek_char(self);

    if (char_is_identifier_start(next_char)) {
        return Scanner__scan_identifier_token(self, token_location, token_lexeme);
    }

    if (char_is_digit(next_char)) {
        return Scanner__scan_integer_token(self, token_location, token_lexeme);
    }

    if (char_is_space(next_char)) {
        return Scanner__scan_space_token(self, token_location, token_lexeme);
    }

    if (next_char == '\'') {
        return Scanner__scan_character_token(self, token_location, token_lexeme);
    }

    if (next_char == '\"') {
        return Scanner__scan_string_token(self, token_location, token_lexeme);
    }

    if (next_char == '/') {
        String__append_char(token_lexeme, Scanner__next_char(self));
        if (Scanner__peek_char(self) == '/') {
            return Scanner__scan_comment_token(self, token_location, token_lexeme);
        }
        // not a comment
        return (Token *) Other_Token__create(token_location, token_lexeme);
    }

    if (next_char == '\n') {
        String__append_char(token_lexeme, Scanner__next_char(self));
        return (Token *) End_Of_Line_Token__create(token_location, token_lexeme);
    }

    if (next_char == '\0') {
        return (Token *) End_Of_File_Token__create(token_location, token_lexeme);
    }

    String__append_char(token_lexeme, Scanner__next_char(self));
    return (Token *) Other_Token__create(token_location, token_lexeme);
}

Token *Scanner__next_token(Scanner *self) {
    if (self->current_token->next_token == 0) {
        self->current_token->next_token = Scanner__scan_token(self);
    }
    self->current_token = self->current_token->next_token;
    return self->current_token;
}

Token *Scanner__peek_token(Scanner *self, uint8_t offset) {
    Token *token = self->current_token;
    while (offset > 0) {
        if (token->next_token == 0) {
            token->next_token = Scanner__scan_token(self);
        }
        token = token->next_token;
        offset = offset - 1;
    }
    return token;
}

Scanner *Scanner__create(Source *source) {
    Scanner *scanner = malloc(sizeof(Scanner));
    scanner->source = source;
    scanner->current_char_index = 0;
    scanner->current_line = 1;
    scanner->current_column = 1;

    scanner->current_token = Scanner__scan_token(scanner);

    return scanner;
}

// AST

typedef struct AST_Statements AST_Statements;

typedef struct {
    AST_Statements *statements;
} AST_Compilation_Unit;

typedef struct AST_Statement {
    struct AST_Statement *next_statement;
} AST_Statement;

typedef struct AST_Statements {
    AST_Statement *first_statement;
    AST_Statement *last_statement;
} AST_Statements;

AST_Statements *AST_Statements__create() {
    AST_Statements *statements = malloc(sizeof(AST_Statements));
    statements->first_statement = 0;
    statements->last_statement = 0;
    return statements;
}

AST_Compilation_Unit *AST_Compilation_Unit__create() {
    AST_Compilation_Unit *compilation_unit = malloc(sizeof(AST_Compilation_Unit));
    compilation_unit->statements = AST_Statements__create();
    return compilation_unit;
}

// Parser

typedef struct Parser {
    Scanner *scanner;
    AST_Compilation_Unit *compilation_unit;
    uint16_t current_identation;
} Parser;

void Parser__panic(Parser *self, String *message) {
    Token__panic(self->scanner->current_token, message);
}

void Parser__warning(Parser *self, String *message) {
    Token__warning(self->scanner->current_token, message);
}

Token *Parser__peek_token(Parser *self, uint8_t offset) {
    return Scanner__peek_token(self->scanner, offset);
}

bool Parser__matches_three(Parser *self, bool (*first)(Token *), bool first_required, bool (*second)(Token *), bool second_required, bool (*third)(Token *)) {
    size_t peek_offset = 0;
    if (first(Parser__peek_token(self, peek_offset))) {
        peek_offset = peek_offset + 1;
    } else if (first_required) {
        return false;
    }
    if (second != 0) {
        if (second(Parser__peek_token(self, peek_offset))) {
            peek_offset = peek_offset + 1;
        } else if (second_required) {
            return false;
        }
    }
    if (third != 0) {
        return third(Parser__peek_token(self, peek_offset));
    }
    return true;
}

bool Parser__matches_two(Parser *self, bool (*first)(Token *), bool first_required, bool (*second)(Token *)) {
    return Parser__matches_three(self, first, first_required, second, true, 0);
}

bool Parser__matches_one(Parser *self, bool (*first)(Token *)) {
    return Parser__matches_two(self, first, true, 0);
}

Token *Parser__consume_token(Parser *self, bool (*check)(Token *)) {
    if (Parser__matches_one(self, check)) {
        Token *token = self->scanner->current_token;
        Scanner__next_token(self->scanner);
        return token;
    }
    Parser__panic(self, String__create_from("Unexpected token"));
}

bool Token__is_comment(Token *self) {
    return self->type == TOKEN_TYPE_COMMENT;
}

void Parser__consume_comment(Parser *self) {
    Parser__consume_token(self, Token__is_comment);
}

bool Token__is_end_of_line(Token *self) {
    return self->type == TOKEN_TYPE_END_OF_LINE || self->type == TOKEN_TYPE_END_OF_FILE;
}

void Parser__consume_end_of_line(Parser *self) {
    Token *token = Parser__consume_token(self, Token__is_end_of_line);
    if (token->type == TOKEN_TYPE_END_OF_FILE) {
        Token__warning(token, String__create_from("Unexpected end of file"));
    }
}

bool Token__is_space(Token *self) {
    return self->type == TOKEN_TYPE_SPACE;
}

void Parser__consume_space(Parser *self, uint16_t identation) {
    if (Parser__matches_one(self, Token__is_space)) {
        Space_Token *token = (Space_Token *) Parser__consume_token(self, Token__is_space);
        if (token->count != identation * 4) {
            Token__warning((Token *) token, String__create_from("Wrong identation"));
        }
    } else if (identation > 0) {
        Parser__warning(self, String__create_from("Missing identation"));
    }
}

bool Parser__consume_empty_line(Parser *self) {
    if (Parser__matches_three(self, Token__is_space, false, Token__is_comment, false, Token__is_end_of_line)) {
        if (Parser__matches_two(self, Token__is_space, false, Token__is_comment)) {
            Parser__consume_space(self, self->current_identation);
            Parser__consume_comment(self);
        } else {
            Parser__consume_space(self, 0);
        }
        Parser__consume_end_of_line(self);
        return true;
    }
    return false;
}

bool Token__is_keyword(Token *self, const char *lexeme) {
    return self->type == TOKEN_TYPE_IDENTIFIER && String__equals_cstring(self->lexeme, lexeme);
}

bool Token__is_typedef(Token *self) {
    return Token__is_keyword(self, "typedef");
}

AST_Statement *Parser__parse_typedef(Parser *self) {
    Token__panic(self->scanner->current_token, String__create_from("DUCK!"));
}

// statement
//      | typedef
AST_Statement *Parser__parse_statement(Parser *self) {
    while (Parser__consume_empty_line(self));

    Parser__consume_space(self, self->current_identation);

    if (Parser__matches_one(self, Token__is_typedef)) {
        return Parser__parse_typedef(self);
    }

    return 0;
}

// statements
//      | ( statement <EOL> )*
void Parser__parse_statements(Parser *self, AST_Statements *statements) {
    while (true) {
        AST_Statement *statement = Parser__parse_statement(self);
        if (statement == 0) {
            break;
        }
    }
}

void Parser__parse_source(Parser *self, Source *source) {
    Scanner *other_scanner = self->scanner;

    self->scanner = Scanner__create(source);

    Parser__parse_statements(self, self->compilation_unit->statements);

    if (self->scanner->current_token->type != TOKEN_TYPE_END_OF_FILE) {
        Token__panic(self->scanner->current_token, String__create_from("Scanner didn't reach end of file"));
    }

    // TODO: warn if the source doesn't end with a new line

    self->scanner = other_scanner;
}

AST_Compilation_Unit *parse(Source *source) {
    Parser parser;
    parser.scanner = 0;
    parser.compilation_unit = AST_Compilation_Unit__create();
    parser.current_identation = 0;

    Parser__parse_source(&parser, source);

    return parser.compilation_unit;
}

// Main

int32_t main() {
    Source *source = Source__create(stdin);

    AST_Compilation_Unit *compilation_unit = parse(source);

    return 0;
}
