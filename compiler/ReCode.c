// Copyright (C) 2023 Stefan Selariu

// Types

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

#define null 0

// LibC

typedef struct File File;

extern File* stdin;
extern File* stdout;
extern File* stderr;

extern int32_t fgetc(File* stream);
extern int32_t fputc(int32_t c, File* stream);
extern int32_t fputs(const char* s, File* stream);

extern void* malloc(size_t size);
extern void* realloc(void* ptr, size_t size);
extern void free(void* ptr);

extern void abort();

// String

typedef struct String {
    uint8_t* data;
    size_t data_size;
    size_t length;
} String;

String* String__create_empty(size_t data_size) {
    String* string = malloc(sizeof(String));
    string->data = malloc(data_size);
    string->data_size = data_size;
    string->length = 0;
    return string;
}

String* String__create() {
    return String__create_empty(16);
}

void String__delete(String* self) {
    free(self->data);
    free(self);
}

String* String__append_char(String* self, uint8_t ch) {
    if (self->length >= self->data_size) {
        self->data_size = self->data_size + 16;
        self->data = realloc(self->data, self->data_size);
    }
    self->data[self->length] = ch;
    self->length = self->length + 1;
    return self;
}

String* String__append_cstring(String* self, const char* s) {
    size_t index = 0;
    while (true) {
        uint8_t c = s[index];
        if (c == 0) {
            return self;
        }
        String__append_char(self, c);
        index = index + 1;
    }
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
    String *string = String__create_empty(string_length);
    String__append_cstring(string, data);
    return string;
}

String *String__append_int16_t(String *self, int16_t value) {
    if (value < 0) {
        String__append_char(self, '-');
        String__append_int16_t(self, -value);
    } else {
        if (value >= 10) {
            String__append_int16_t(self, value / 10);
        }
        String__append_char(self, value % 10 + '0');
    }
    return self;
}

String *String__append_string(String *self, String *other) {
    size_t index = 0;
    while (index < other->length) {
        String__append_char(self, other->data[index]);
        index = index + 1;
    }
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

bool String__equals_string(String *self, String *other) {
    if (self->length != other->length) {
        return false;
    }

    size_t index = 0;
    while (index < self->length) {
        if (self->data[index] != other->data[index]) {
            return false;
        }
        index = index + 1;
    }

    return true;
}

// Utils

void pass() {
}

void File__write_char(File *self, uint8_t c) {
    fputc(c, self);
}

void File__write_cstring(File *self, const char *s) {
    fputs(s, self);
}

void File__write_int32_t(File *self, int32_t value) {
    if (value < 0) {
        File__write_char(self, '-');
        File__write_int32_t(self, -value);
    } else {
        if (value >= 10) {
            File__write_int32_t(self, value / 10);
        }
        File__write_char(self, value % 10 + '0');
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

// Source_Location

typedef struct {
    Source *source;
    uint16_t line;
    uint16_t column;
} Source_Location;

Source_Location *Source_Location__create(Source *source, uint16_t line, uint16_t column) {
    Source_Location *source_location = malloc(sizeof(Source_Location));
    source_location->source = source;
    source_location->line = line;
    source_location->column = column;
    return source_location;
}

void File__write_source_location(File *self, Source_Location *location) {
    File__write_cstring(self, "compiler/ReCode.c:");
    File__write_int32_t(self, location->line);
    File__write_char(self, ':');
    File__write_int32_t(self, location->column);
    File__write_cstring(self, ": ");
}

void Source_Location__panic(Source_Location *self, String *message) {
    File__write_source_location(stderr, self);
    panic(message);
}

void Source_Location__warning(Source_Location *self, String *message) {
    File__write_source_location(stderr, self);
    warning(message);
}

// Token

typedef enum {
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
    TOKEN_KIND__STRING,
} Token_Kind;

typedef struct Token {
    Token_Kind kind;
    Source_Location *location;
    String *lexeme;
    struct Token *next_token;
} Token;

void *Token__create(size_t size, uint16_t kind, Source_Location *location, String *lexeme) {
    Token *token = malloc(size);
    token->kind = kind;
    token->location = location;
    token->lexeme = lexeme;
    token->next_token = null;
    return token;
}

void Token__panic(Token *self, String *message) {
    Source_Location__panic(self->location, message);
}

void Token__warning(Token *self, String *message) {
    Source_Location__warning(self->location, message);
}

typedef struct {
    Token_Kind kind;
    Source_Location *location;
    String *lexeme;
    Token *next_token;
    uint8_t value;
} Character_Token;

Character_Token *Character_Token__create(Source_Location *location, String *lexeme, uint8_t value) {
    Character_Token *token = Token__create(sizeof(Character_Token), TOKEN_KIND__CHARACTER, location, lexeme);
    token->value = value;
    return token;
}

typedef struct {
    Token_Kind kind;
    Source_Location *location;
    String *lexeme;
    Token *next_token;
} Comment_Token;

Comment_Token *Comment_Token__create(Source_Location *location, String *lexeme) {
    return Token__create(sizeof(Comment_Token), TOKEN_KIND__COMMENT, location, lexeme);
}

typedef struct {
    Token_Kind kind;
    Source_Location *location;
    String *lexeme;
    Token *next_token;
} End_Of_File_Token;

End_Of_File_Token *End_Of_File_Token__create(Source_Location *location, String *lexeme) {
    return Token__create(sizeof(End_Of_File_Token), TOKEN_KIND__END_OF_FILE, location, lexeme);
}

typedef struct {
    Token_Kind kind;
    Source_Location *location;
    String *lexeme;
    Token *next_token;
} End_Of_Line_Token;

End_Of_Line_Token *End_Of_Line_Token__create(Source_Location *location, String *lexeme) {
    return Token__create(sizeof(End_Of_Line_Token), TOKEN_KIND__END_OF_LINE, location, lexeme);
}

typedef struct {
    Token_Kind kind;
    Source_Location *location;
    String *lexeme;
    Token *next_token;
} Error_Token;

Error_Token *Error_Token__create(Source_Location *location, String *lexeme) {
    return Token__create(sizeof(Error_Token), TOKEN_KIND__ERROR, location, lexeme);
}

typedef struct {
    Token_Kind kind;
    Source_Location *location;
    String *lexeme;
    Token *next_token;
} Identifier_Token;

Identifier_Token *Identifier_Token__create(Source_Location *location, String *lexeme) {
    return Token__create(sizeof(Identifier_Token), TOKEN_KIND__IDENTIFIER, location, lexeme);
}

typedef struct {
    Token_Kind kind;
    Source_Location *location;
    String *lexeme;
    Token *next_token;
    uint64_t value;
} Integer_Token;

Integer_Token *Integer_Token__create(Source_Location *location, String *lexeme, uint64_t value) {
    Integer_Token *token = Token__create(sizeof(Integer_Token), TOKEN_KIND__INTEGER, location, lexeme);
    token->value = value;
    return token;
}

typedef struct {
    Token_Kind kind;
    Source_Location *location;
    String *lexeme;
    Token *next_token;
} Other_Token;

Other_Token *Other_Token__create(Source_Location *location, String *lexeme) {
    return Token__create(sizeof(Other_Token), TOKEN_KIND__OTHER, location, lexeme);
}

typedef struct {
    Token_Kind kind;
    Source_Location *location;
    String *lexeme;
    Token *next_token;
    uint16_t count;
} Space_Token;

Space_Token *Space_Token__create(Source_Location *location, String *lexeme, uint16_t count) {
    Space_Token *token = Token__create(sizeof(Space_Token), TOKEN_KIND__SPACE, location, lexeme);
    token->count = count;
    return token;
}

typedef struct {
    Token_Kind kind;
    Source_Location *location;
    String *lexeme;
    Token *next_token;
    String *value;
} String_Token;

String_Token *String_Token__create(Source_Location *location, String *lexeme, String *value) {
    String_Token *token = Token__create(sizeof(String_Token), TOKEN_KIND__STRING, location, lexeme);
    token->value = value;
    return token;
}

bool Token__is_anything(Token *self) {
    return true;
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

bool Token__is_identifier(Token* self) {
    return self->kind == TOKEN_KIND__IDENTIFIER;
}

bool Token__is_integer(Token* self) {
    return self->kind == TOKEN_KIND__INTEGER;
}

bool Token__is_keyword(Token *self, const char *lexeme) {
    return self->kind == TOKEN_KIND__IDENTIFIER && String__equals_cstring(self->lexeme, lexeme);
}

bool Token__is_const(Token *self) {
    return Token__is_keyword(self, "const");
}

bool Token__is_else(Token *self) {
    return Token__is_keyword(self, "else");
}

bool Token__is_extern(Token *self) {
    return Token__is_keyword(self, "extern");
}

bool Token__is_if(Token *self) {
    return Token__is_keyword(self, "if");
}

bool Token__is_return(Token *self) {
    return Token__is_keyword(self, "return");
}

bool Token__is_struct(Token *self) {
    return Token__is_keyword(self, "struct");
}

bool Token__is_typedef(Token *self) {
    return Token__is_keyword(self, "typedef");
}

bool Token__is_other(Token *self, const char *lexeme) {
    return self->kind == TOKEN_KIND__OTHER && String__equals_cstring(self->lexeme, lexeme);
}

bool Token__is_ampersand(Token *self) {
    return Token__is_other(self, "&");
}

bool Token__is_asterisk(Token *self) {
    return Token__is_other(self, "*");
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
    return Token__is_other(self, ">");
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

void File__write_token(File *stream, Token *token) {
    bool colored = token->kind == TOKEN_KIND__COMMENT || token->kind == TOKEN_KIND__ERROR || token->kind == TOKEN_KIND__OTHER;
    if (colored) {
        if (token->kind == TOKEN_KIND__OTHER) {
            File__write_cstring(stream, "\e[2;33m");
        } else if (token->kind == TOKEN_KIND__COMMENT) {
            File__write_cstring(stream, "\e[2;37m");
        } else if (token->kind == TOKEN_KIND__ERROR) {
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

Token *Scanner__scan_character_token(Scanner *self, Source_Location *source_location, String *token_lexeme) {
    if (Scanner__next_char(self) != '\'') {
        panic(String__create_from("Unexpected char"));
    }
    String__append_char(token_lexeme, '\'');

    uint8_t next_char = Scanner__peek_char(self);
    if (char_is_end_of_line(next_char) || next_char == '\t') {
        return (Token *) Error_Token__create(source_location, token_lexeme);
    }

    String__append_char(token_lexeme, Scanner__next_char(self));
    uint8_t value = next_char;

    if (value == '\'') {
        return (Token *) Error_Token__create(source_location, token_lexeme);
    }

    if (value == '\\') {
        next_char = Scanner__peek_char(self);
        if (char_is_end_of_line(next_char) || next_char == '\t') {
            return (Token *) Error_Token__create(source_location, token_lexeme);
        }

        String__append_char(token_lexeme, Scanner__next_char(self));

        value = escape_char_value(next_char);
        if (value == ((uint8_t) -1)) {
            return (Token *) Error_Token__create(source_location, token_lexeme);
        }
    }

    if (Scanner__peek_char(self) != '\'') {
        return (Token *) Error_Token__create(source_location, token_lexeme);
    }

    String__append_char(token_lexeme, Scanner__next_char(self));
    return (Token *) Character_Token__create(source_location, token_lexeme, value);
}

Token *Scanner__scan_comment_token(Scanner *self, Source_Location *source_location, String *token_lexeme) {
    while (!char_is_end_of_line(Scanner__peek_char(self))) {
        String__append_char(token_lexeme, Scanner__next_char(self));
    }
    return (Token *) Comment_Token__create(source_location, token_lexeme);
}

bool char_is_identifier_start(uint8_t c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool char_is_identifier_letter(uint8_t c) {
    return char_is_identifier_start(c) || (c >= '0' && c <= '9');
}

Token *Scanner__scan_identifier_token(Scanner *self, Source_Location *source_location, String *token_lexeme) {
    while (char_is_identifier_letter(Scanner__peek_char(self))) {
        String__append_char(token_lexeme, Scanner__next_char(self));
    }
    return (Token *) Identifier_Token__create(source_location, token_lexeme);
}

bool char_is_digit(uint8_t c) {
    return c >= '0' && c <= '9';
}

Token *Scanner__scan_integer_token(Scanner *self, Source_Location *source_location, String *token_lexeme) {
    uint64_t value = 0;
    while (char_is_digit(Scanner__peek_char(self))) {
        uint8_t c = Scanner__next_char(self);
        value = value * 10 + (c - '0');
        String__append_char(token_lexeme, c);
    }
    return (Token *) Integer_Token__create(source_location, token_lexeme, value);
}

bool char_is_space(uint8_t c) {
    return c == ' ';
}

Token *Scanner__scan_space_token(Scanner *self, Source_Location *source_location, String *token_lexeme) {
    uint16_t count = 0;
    while (char_is_space(Scanner__peek_char(self))) {
        count = count + 1;
        String__append_char(token_lexeme, Scanner__next_char(self));
    }
    return (Token *) Space_Token__create(source_location, token_lexeme, count);
}

Token *Scanner__scan_string_token(Scanner *self, Source_Location *source_location, String *token_lexeme) {
    if (Scanner__next_char(self) != '"') {
        panic(String__create_from("Unexpected char"));
    }
    String__append_char(token_lexeme, '"');

    String *value = String__create();

    while (true) {
        uint8_t next_char = Scanner__peek_char(self);
        if (char_is_end_of_line(next_char) || next_char == '\t') {
            return (Token *) Error_Token__create(source_location, token_lexeme);
        }

        String__append_char(token_lexeme, Scanner__next_char(self));

        if (next_char == '"') {
            return (Token *) String_Token__create(source_location, token_lexeme, value);
        }

        if (next_char == '\\') {
            next_char = Scanner__peek_char(self);
            if (char_is_end_of_line(next_char) || next_char == '\t') {
                return (Token *) Error_Token__create(source_location, token_lexeme);
            }

            String__append_char(token_lexeme, Scanner__next_char(self));

            next_char = escape_char_value(next_char);
            if (next_char == ((uint8_t) -1)) {
                return (Token *) Error_Token__create(source_location, token_lexeme);
            }
        }

        String__append_char(value, next_char);
    }
}

Token *Scanner__scan_token(Scanner *self) {
    Source_Location *source_location = Source_Location__create(self->source, self->current_line, self->current_column);
    String *token_lexeme = String__create();

    uint8_t next_char = Scanner__peek_char(self);

    if (char_is_identifier_start(next_char)) {
        return Scanner__scan_identifier_token(self, source_location, token_lexeme);
    }

    if (char_is_digit(next_char)) {
        return Scanner__scan_integer_token(self, source_location, token_lexeme);
    }

    if (char_is_space(next_char)) {
        return Scanner__scan_space_token(self, source_location, token_lexeme);
    }

    if (next_char == '\'') {
        return Scanner__scan_character_token(self, source_location, token_lexeme);
    }

    if (next_char == '\"') {
        return Scanner__scan_string_token(self, source_location, token_lexeme);
    }

    if (next_char == '/') {
        String__append_char(token_lexeme, Scanner__next_char(self));
        if (Scanner__peek_char(self) == '/') {
            return Scanner__scan_comment_token(self, source_location, token_lexeme);
        }
        // not a comment
        return (Token *) Other_Token__create(source_location, token_lexeme);
    }

    if (next_char == '\n') {
        String__append_char(token_lexeme, Scanner__next_char(self));
        return (Token *) End_Of_Line_Token__create(source_location, token_lexeme);
    }

    if (next_char == '\0') {
        return (Token *) End_Of_File_Token__create(source_location, token_lexeme);
    }

    String__append_char(token_lexeme, Scanner__next_char(self));
    return (Token *) Other_Token__create(source_location, token_lexeme);
}

Token *Scanner__next_token(Scanner *self) {
    if (self->current_token->next_token == null) {
        self->current_token->next_token = Scanner__scan_token(self);
    }
    self->current_token = self->current_token->next_token;
    return self->current_token;
}

Token *Scanner__peek_token(Scanner *self, uint8_t offset) {
    Token *token = self->current_token;
    while (offset > 0) {
        if (token->next_token == null) {
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

typedef enum {
    AST_TYPE_KIND__BOOL,
    AST_TYPE_KIND__CHAR,
    AST_TYPE_KIND__CONST,
    AST_TYPE_KIND__INT16_T,
    AST_TYPE_KIND__INT32_T,
    AST_TYPE_KIND__INT64_T,
    AST_TYPE_KIND__INT8_T,
    AST_TYPE_KIND__POINTER,
    AST_TYPE_KIND__SIZE_T,
    AST_TYPE_KIND__STRUCT,
    AST_TYPE_KIND__UINT16_T,
    AST_TYPE_KIND__UINT32_T,
    AST_TYPE_KIND__UINT64_T,
    AST_TYPE_KIND__UINT8_T,
    AST_TYPE_KIND__VOID,
} AST_Type_Kind;

typedef struct AST_Statement AST_Statement;

typedef struct AST_Type {
    AST_Type_Kind kind;
    String *name;
    AST_Statement *statement;
    struct AST_Type *next_type;
} AST_Type;

AST_Type *AST_Type__create(size_t size, AST_Type_Kind kind, String *name, AST_Statement *statement) {
    AST_Type *type = malloc(size);
    type->kind = kind;
    type->name = name;
    type->statement = statement;
    type->next_type = null;
    return type;
}

typedef struct {
    AST_Type type;
    AST_Type *other_type;
} AST_Const_Type;

AST_Type *AST_Const_Type__create(AST_Type *other_type) {
    AST_Const_Type *type = (AST_Const_Type *) AST_Type__create(sizeof(AST_Const_Type), AST_TYPE_KIND__CONST, String__append_string(String__create_from("const "), other_type->name), null);
    type->other_type = other_type;
    return &type->type;
}

typedef struct {
    AST_Type type;
    AST_Type *other_type;
} AST_Pointer_Type;

AST_Type *AST_Pointer_Type__create(AST_Type *other_type) {
    AST_Pointer_Type *type = (AST_Pointer_Type *) AST_Type__create(sizeof(AST_Pointer_Type), AST_TYPE_KIND__POINTER, String__append_char(String__append_string(String__create_empty(other_type->name->length + 1), other_type->name), '*'), null);
    type->other_type = other_type;
    return &type->type;
}

typedef struct AST_Types {
    AST_Type *first_type;
    AST_Type *last_type;
} AST_Types;

AST_Types *AST_Types__create() {
    AST_Types *types = malloc(sizeof(AST_Types));
    types->first_type = null;
    types->last_type = null;
    return types;
}

typedef enum {
    AST_EXPRESSION_KIND__ADD,
    AST_EXPRESSION_KIND__ARRAY_ACCESS,
    AST_EXPRESSION_KIND__CALL,
    AST_EXPRESSION_KIND__DIVIDE,
    AST_EXPRESSION_KIND__EQUALS,
    AST_EXPRESSION_KIND__GREATER,
    AST_EXPRESSION_KIND__GREATER_OR_EQUALS,
    AST_EXPRESSION_KIND__INTEGER,
    AST_EXPRESSION_KIND__LESS,
    AST_EXPRESSION_KIND__LESS_OR_EQUALS,
    AST_EXPRESSION_KIND__LOGIC_AND,
    AST_EXPRESSION_KIND__LOGIC_OR,
    AST_EXPRESSION_KIND__MEMBER_ACCESS,
    AST_EXPRESSION_KIND__MODULO,
    AST_EXPRESSION_KIND__MULTIPLY,
    AST_EXPRESSION_KIND__NOT_EQUALS,
    AST_EXPRESSION_KIND__SIZEOF,
    AST_EXPRESSION_KIND__SUBSTRACT,
    AST_EXPRESSION_KIND__SYMBOL,
} AST_Expression_Kind;

typedef struct AST_Expression {
    AST_Expression_Kind kind;
    Source_Location *location;
} AST_Expression;

AST_Expression* AST_Expression__create(size_t size, AST_Expression_Kind kind, Source_Location *location) {
    AST_Expression* expression = malloc(size);
    expression->kind = kind;
    expression->location = location;
    return expression;
}

typedef struct AST_Binary_Expression {
    AST_Expression expression;
    AST_Expression* left_expression;
    AST_Expression* right_expression;
} AST_Binary_Expression;

AST_Binary_Expression* AST_Binary_Expression__create(AST_Expression_Kind kind, AST_Expression *left_expression, AST_Expression* right_expression) {
    AST_Binary_Expression* expression = (AST_Binary_Expression*) AST_Expression__create(sizeof(AST_Binary_Expression), kind, left_expression->location);
    expression->left_expression = left_expression;
    expression->right_expression = right_expression;
    return expression;
}

typedef struct AST_Add_Expression {
    AST_Binary_Expression binary_expression;
} AST_Add_Expression;

AST_Add_Expression* AST_Add_Expression__create(AST_Expression* left_expression, AST_Expression* right_expression) {
    return (AST_Add_Expression*) AST_Binary_Expression__create(AST_EXPRESSION_KIND__ADD, left_expression, right_expression);
}

typedef struct AST_Array_Access_Expression {
    AST_Expression expression;
    AST_Expression* array_expression;
    AST_Expression* index_expression;
} AST_Array_Access_Expression;

AST_Array_Access_Expression* AST_Array_Access_Expression__create(AST_Expression* array_expression, AST_Expression* index_expression) {
    AST_Array_Access_Expression* array_access_expression = (AST_Array_Access_Expression*) AST_Expression__create(sizeof(AST_Array_Access_Expression), AST_EXPRESSION_KIND__ARRAY_ACCESS, array_expression->location);
    array_access_expression->array_expression = array_expression;
    array_access_expression->index_expression = index_expression;
    return array_access_expression;
}

typedef struct AST_Call_Argument {
    AST_Expression *expression;
    struct AST_Call_Argument *next_argument;
} AST_Call_Argument;

AST_Call_Argument* AST_Call_Argument__create(AST_Expression *expression) {
    AST_Call_Argument* argument = malloc(sizeof(AST_Call_Argument));
    argument->expression = expression;
    argument->next_argument = null;
    return argument;
}

typedef struct AST_Call_Expression {
    AST_Expression expression;
    AST_Expression *callee_expression;
    AST_Call_Argument *first_argument;
} AST_Call_Expression;

AST_Call_Expression* AST_Call_Expression__create(AST_Expression *callee_expression) {
    AST_Call_Expression* call_expression = (AST_Call_Expression*) AST_Expression__create(sizeof(AST_Call_Expression), AST_EXPRESSION_KIND__CALL, callee_expression->location);
    call_expression->callee_expression = callee_expression;
    call_expression->first_argument = null;
    return call_expression;
}

typedef struct AST_Divide_Expression {
    AST_Binary_Expression binary_expression;
} AST_Divide_Expression;

AST_Divide_Expression* AST_Divide_Expression__create(AST_Expression* left_expression, AST_Expression* right_expression) {
    return (AST_Divide_Expression*) AST_Binary_Expression__create(AST_EXPRESSION_KIND__DIVIDE, left_expression, right_expression);
}

typedef struct AST_Equals_Expression {
    AST_Binary_Expression binary_expression;
} AST_Equals_Expression;

AST_Equals_Expression* AST_Equals_Expression__create(AST_Expression* left_expression, AST_Expression* right_expression) {
    return (AST_Equals_Expression*) AST_Binary_Expression__create(AST_EXPRESSION_KIND__EQUALS, left_expression, right_expression);
}

typedef struct AST_Greater_Expression {
    AST_Binary_Expression binary_expression;
} AST_Greater_Expression;

AST_Greater_Expression* AST_Greater_Expression__create(AST_Expression* left_expression, AST_Expression* right_expression) {
    return (AST_Greater_Expression*) AST_Binary_Expression__create(AST_EXPRESSION_KIND__GREATER, left_expression, right_expression);
}

typedef struct AST_Greater_Or_Equals_Expression {
    AST_Binary_Expression binary_expression;
} AST_Greater_Or_Equals_Expression;

AST_Greater_Or_Equals_Expression* AST_Greater_Or_Equals_Expression__create(AST_Expression* left_expression, AST_Expression* right_expression) {
    return (AST_Greater_Or_Equals_Expression*) AST_Binary_Expression__create(AST_EXPRESSION_KIND__GREATER_OR_EQUALS, left_expression, right_expression);
}

typedef struct AST_Integer_Expression {
    AST_Expression expression;
    Integer_Token *literal;
} AST_Integer_Expression;

AST_Integer_Expression* AST_Integer_Expression__create(Integer_Token *literal) {
    AST_Integer_Expression* symbol_expression = (AST_Integer_Expression*) AST_Expression__create(sizeof(AST_Integer_Expression), AST_EXPRESSION_KIND__INTEGER, literal->location);
    symbol_expression->literal = literal;
    return symbol_expression;
}

typedef struct AST_Less_Expression {
    AST_Binary_Expression binary_expression;
} AST_Less_Expression;

AST_Less_Expression* AST_Less_Expression__create(AST_Expression* left_expression, AST_Expression* right_expression) {
    return (AST_Less_Expression*) AST_Binary_Expression__create(AST_EXPRESSION_KIND__LESS, left_expression, right_expression);
}

typedef struct AST_Less_Or_Equals_Expression {
    AST_Binary_Expression binary_expression;
} AST_Less_Or_Equals_Expression;

AST_Less_Or_Equals_Expression* AST_Less_Or_Equals_Expression__create(AST_Expression* left_expression, AST_Expression* right_expression) {
    return (AST_Less_Or_Equals_Expression*) AST_Binary_Expression__create(AST_EXPRESSION_KIND__LESS_OR_EQUALS, left_expression, right_expression);
}

typedef struct AST_Logic_And_Expression {
    AST_Binary_Expression binary_expression;
} AST_Logic_And_Expression;

AST_Logic_And_Expression* AST_Logic_And_Expression__create(AST_Expression* left_expression, AST_Expression* right_expression) {
    return (AST_Logic_And_Expression*) AST_Binary_Expression__create(AST_EXPRESSION_KIND__LOGIC_AND, left_expression, right_expression);
}

typedef struct AST_Logic_Or_Expression {
    AST_Binary_Expression binary_expression;
} AST_Logic_Or_Expression;

AST_Logic_Or_Expression* AST_Logic_Or_Expression__create(AST_Expression* left_expression, AST_Expression* right_expression) {
    return (AST_Logic_Or_Expression*) AST_Binary_Expression__create(AST_EXPRESSION_KIND__LOGIC_OR, left_expression, right_expression);
}

typedef struct AST_Member_Access_Expression {
    AST_Expression expression;
    AST_Expression* value_expression;
    Token *member_name;
} AST_Member_Access_Expression;

AST_Member_Access_Expression* AST_Member_Access_Expression__create(AST_Expression* value_expression, Token *member_name) {
    AST_Member_Access_Expression* member_access_expression = (AST_Member_Access_Expression*) AST_Expression__create(sizeof(AST_Member_Access_Expression), AST_EXPRESSION_KIND__MEMBER_ACCESS, value_expression->location);
    member_access_expression->value_expression = value_expression;
    member_access_expression->member_name = member_name;
    return member_access_expression;
}

typedef struct AST_Modulo_Expression {
    AST_Binary_Expression binary_expression;
} AST_Modulo_Expression;

AST_Modulo_Expression* AST_Modulo_Expression__create(AST_Expression* left_expression, AST_Expression* right_expression) {
    return (AST_Modulo_Expression*) AST_Binary_Expression__create(AST_EXPRESSION_KIND__MODULO, left_expression, right_expression);
}

typedef struct AST_Multiply_Expression {
    AST_Binary_Expression binary_expression;
} AST_Multiply_Expression;

AST_Multiply_Expression* AST_Multiply_Expression__create(AST_Expression* left_expression, AST_Expression* right_expression) {
    return (AST_Multiply_Expression*) AST_Binary_Expression__create(AST_EXPRESSION_KIND__MULTIPLY, left_expression, right_expression);
}

typedef struct AST_Not_Equals_Expression {
    AST_Binary_Expression binary_expression;
} AST_Not_Equals_Expression;

AST_Not_Equals_Expression* AST_Not_Equals_Expression__create(AST_Expression* left_expression, AST_Expression* right_expression) {
    return (AST_Not_Equals_Expression*) AST_Binary_Expression__create(AST_EXPRESSION_KIND__NOT_EQUALS, left_expression, right_expression);
}

typedef struct AST_Sizeof_Expression {
    AST_Expression expression;
    AST_Type *type;
} AST_Sizeof_Expression;

AST_Sizeof_Expression* AST_Sizeof_Expression__create(Source_Location* location, AST_Type *type) {
    AST_Sizeof_Expression* call_expression = (AST_Sizeof_Expression*) AST_Expression__create(sizeof(AST_Sizeof_Expression), AST_EXPRESSION_KIND__SIZEOF, location);
    call_expression->type = type;
    return call_expression;
}

typedef struct AST_Substract_Expression {
    AST_Binary_Expression binary_expression;
} AST_Substract_Expression;

AST_Substract_Expression* AST_Substract_Expression__create(AST_Expression* left_expression, AST_Expression* right_expression) {
    return (AST_Substract_Expression*) AST_Binary_Expression__create(AST_EXPRESSION_KIND__SUBSTRACT, left_expression, right_expression);
}

typedef struct AST_Symbol_Expression {
    AST_Expression expression;
    Token *name;
} AST_Symbol_Expression;

AST_Symbol_Expression* AST_Symbol_Expression__create(Token *name) {
    AST_Symbol_Expression* symbol_expression = (AST_Symbol_Expression*) AST_Expression__create(sizeof(AST_Symbol_Expression), AST_EXPRESSION_KIND__SYMBOL, name->location);
    symbol_expression->name = name;
    return symbol_expression;
}

typedef enum {
    AST_STATEMENT_KIND__ASSIGNMENT,
    AST_STATEMENT_KIND__BLOCK,
    AST_STATEMENT_KIND__EXPRESSION,
    AST_STATEMENT_KIND__FUNCTION,
    AST_STATEMENT_KIND__IF,
    AST_STATEMENT_KIND__RETURN,
    AST_STATEMENT_KIND__STRUCT,
    AST_STATEMENT_KIND__VARIABLE,
} AST_Statement_Kind;

typedef struct AST_Statement {
    AST_Statement_Kind kind;
    Source_Location *location;
    struct AST_Statement *next_statement;
} AST_Statement;

void *AST_Statement__create(size_t size, AST_Statement_Kind kind, Source_Location *location) {
    AST_Statement *statement = malloc(size);
    statement->kind = kind;
    statement->location = location;
    statement->next_statement = null;
    return statement;
}

typedef struct AST_Named_Statement {
    AST_Statement statement;
    Token *name;
} AST_Named_Statement;

void *AST_Named_Statement__create(size_t size, AST_Statement_Kind kind, Source_Location *location, Token *name) {
    AST_Named_Statement *statement = AST_Statement__create(size, kind, location);
    statement->name = name;
    return statement;
}

typedef struct AST_Assignment_Statement {
    AST_Statement statement;
    AST_Expression *left_expression;
    AST_Expression *right_expression;
} AST_Assignment_Statement;

AST_Assignment_Statement* AST_Assignment_Statement__create(AST_Expression* left_expression, AST_Expression* right_expression) {
    AST_Assignment_Statement *assignment_statement = AST_Statement__create(sizeof(AST_Assignment_Statement), AST_STATEMENT_KIND__ASSIGNMENT, left_expression->location);
    assignment_statement->left_expression = left_expression;
    assignment_statement->right_expression = right_expression;
    return assignment_statement;
}

typedef struct AST_Block_Statement {
    AST_Statement statement;
    AST_Statements *statements;
} AST_Block_Statement;

AST_Block_Statement* AST_Block_Statement__create(Source_Location* location, AST_Statements* statements) {
    AST_Block_Statement *assignment_statement = AST_Statement__create(sizeof(AST_Block_Statement), AST_STATEMENT_KIND__BLOCK, location);
    assignment_statement->statements = statements;
    return assignment_statement;
}

typedef struct AST_Expression_Statement {
    AST_Statement statement;
    AST_Expression *expression;
} AST_Expression_Statement;

AST_Expression_Statement* AST_Expression_Statement__create(AST_Expression* expression) {
    AST_Expression_Statement *expression_statement = AST_Statement__create(sizeof(AST_Expression_Statement), AST_STATEMENT_KIND__EXPRESSION, expression->location);
    expression_statement->expression = expression;
    return expression_statement;
}

typedef struct AST_Function_Parameter {
    Token *name;
    AST_Type *type;
    struct AST_Function_Parameter *next_parameter;
} AST_Function_Parameter;

AST_Function_Parameter *AST_Function_Parameter__create(Token *name, AST_Type *type) {
    AST_Function_Parameter *parameter = malloc(sizeof(AST_Function_Parameter));
    parameter->name = name;
    parameter->type = type;
    parameter->next_parameter = null;
    return parameter;
}

typedef struct AST_Function_Statement {
    AST_Named_Statement named_statement;
    AST_Function_Parameter *first_parameter;
    AST_Type *return_type;
    AST_Statements* statements;
    bool is_external;
} AST_Function_Statement;

AST_Statement *AST_Function_Statement__create(Source_Location *location, Token *name, AST_Function_Parameter *first_parameter, AST_Type *resturn_type, AST_Statements* statements, bool is_external) {
    AST_Function_Statement *function_statement = AST_Named_Statement__create(sizeof(AST_Function_Statement), AST_STATEMENT_KIND__FUNCTION, location, name);
    function_statement->first_parameter = first_parameter;
    function_statement->return_type = resturn_type;
    function_statement->statements = statements;
    function_statement->is_external = is_external;
    return (AST_Statement *) function_statement;
}

typedef struct AST_If_Statement {
    AST_Statement statement;
    AST_Expression *condition_expression;
    AST_Statement* true_statement;
    AST_Statement* false_statement;
} AST_If_Statement;

AST_Statement *AST_If_Statement__create(Source_Location *location, AST_Expression *condition_expression, AST_Statement* true_statement, AST_Statement* false_statement) {
    AST_If_Statement *statement = AST_Statement__create(sizeof(AST_If_Statement), AST_STATEMENT_KIND__IF, location);
    statement->condition_expression = condition_expression;
    statement->true_statement = true_statement;
    statement->false_statement = false_statement;
    return (AST_Statement *) statement;
}

typedef struct AST_Return_Statement {
    AST_Statement statement;
    AST_Expression *expression;
} AST_Return_Statement;

AST_Statement *AST_Return_Statement__create(Source_Location *location, AST_Expression *expression) {
    AST_Return_Statement *statement = AST_Statement__create(sizeof(AST_Return_Statement), AST_STATEMENT_KIND__RETURN, location);
    statement->expression = expression;
    return (AST_Statement *) statement;
}

typedef struct AST_Struct_Member {
    Token *name;
    AST_Type *type;
    struct AST_Struct_Member *next_member;
} AST_Struct_Member;

AST_Struct_Member *AST_Struct_Member__create(Token *name, AST_Type *type) {
    AST_Struct_Member *member = malloc(sizeof(AST_Struct_Member));
    member->name = name;
    member->type = type;
    member->next_member = null;
    return member;
}

typedef struct AST_Struct_Statement {
    AST_Named_Statement named_statement;
    AST_Struct_Member *first_member;
    bool is_opaque;
} AST_Struct_Statement;

AST_Struct_Statement *AST_Struct_Statement__create(Source_Location *location, Token *name) {
    AST_Struct_Statement *statement = AST_Named_Statement__create(sizeof(AST_Struct_Statement), AST_STATEMENT_KIND__STRUCT, location, name);
    statement->first_member = null;
    statement->is_opaque = false;
    return statement;
}

typedef struct AST_Variable_Statement {
    AST_Named_Statement named_statement;
    AST_Type *type;
    AST_Expression *expression;
    bool is_external;
} AST_Variable_Statement;

AST_Variable_Statement *AST_Variable_Statement__create(Source_Location *location, Token *name, AST_Type *type, bool is_external) {
    AST_Variable_Statement *statement = AST_Named_Statement__create(sizeof(AST_Variable_Statement), AST_STATEMENT_KIND__VARIABLE, location, name);
    statement->type = type;
    statement->is_external = is_external;
    return statement;
}

typedef struct AST_Statements {
    AST_Statement *first_statement;
    AST_Statement *last_statement;
    bool has_globals;
} AST_Statements;

AST_Statements *AST_Statements__create(bool has_globals) {
    AST_Statements *statements = malloc(sizeof(AST_Statements));
    statements->first_statement = null;
    statements->last_statement = null;
    statements->has_globals = has_globals;
    return statements;
}

AST_Statement *AST_Statements__find_named_statement(AST_Statements *self, String *name) {
    AST_Statement *statement = self->first_statement;
    while (statement != null) {
        if (statement->kind == AST_STATEMENT_KIND__FUNCTION || statement->kind == AST_STATEMENT_KIND__STRUCT || statement->kind == AST_STATEMENT_KIND__VARIABLE) {
            AST_Named_Statement *named_statement = (AST_Named_Statement *) statement;
            if (String__equals_string(name, named_statement->name->lexeme)) {
                return statement;
            }
        }
        statement = statement->next_statement;
    }
    return null;
}

void AST_Statements__append(AST_Statements *self, AST_Statement *statement) {
    if (statement->kind == AST_STATEMENT_KIND__FUNCTION || statement->kind == AST_STATEMENT_KIND__STRUCT || statement->kind == AST_STATEMENT_KIND__VARIABLE) {
        AST_Named_Statement *named_statement = (AST_Named_Statement *) statement;
        if (self->has_globals) {
            AST_Statement *other_statement = AST_Statements__find_named_statement(self, named_statement->name->lexeme);
            if (other_statement != null) {
                Source_Location__panic(statement->location, String__create_from("TODO: Handle redeclaration"));
            }
        } else {
            if (statement->kind == AST_STATEMENT_KIND__FUNCTION) {
                Source_Location__panic(statement->location, String__create_from("Local functions are not supported"));
            }
            if (statement->kind == AST_STATEMENT_KIND__STRUCT) {
                Source_Location__panic(statement->location, String__create_from("Local structs are not supported"));
            }
            if (statement->kind == AST_STATEMENT_KIND__VARIABLE) {
                AST_Statement *other_statement = AST_Statements__find_named_statement(self, named_statement->name->lexeme);
                if (other_statement != null) {
                    Source_Location__panic(statement->location, String__create_from("TODO: Handle redeclaration"));
                }
            }
        }
    }

    if (self->first_statement == null) {
        self->first_statement = statement;
    } else {
        self->last_statement->next_statement = statement;
    }
    self->last_statement = statement;
}

AST_Compilation_Unit *AST_Compilation_Unit__create() {
    AST_Compilation_Unit *compilation_unit = malloc(sizeof(AST_Compilation_Unit));
    compilation_unit->statements = AST_Statements__create(true);
    return compilation_unit;
}

// Parser

typedef struct Parser {
    Scanner *scanner;
    AST_Types *types;
    AST_Compilation_Unit *compilation_unit;
    uint16_t current_identation;
} Parser;

AST_Type *Parser__create_type(Parser *self, AST_Type_Kind type_kind, String *type_name, AST_Statement *type_statement) {
    AST_Type *type = AST_Type__create(sizeof(AST_Type), type_kind, type_name, type_statement);
    if (self->types->first_type == null) {
        self->types->first_type = type;
    } else {
        self->types->last_type->next_type = type;
    }
    self->types->last_type = type;
    return type;
}

AST_Type *Parser__find_type(Parser *self, String *name) {
    AST_Type *type = self->types->first_type;
    while (type != null) {
        if (String__equals_string(name, type->name)) {
            break;
        }
        type = type->next_type;
    }
    return type;
}

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
    if (second != null) {
        if (second(Parser__peek_token(self, peek_offset))) {
            peek_offset = peek_offset + 1;
        } else if (second_required) {
            return false;
        }
    }
    if (third != null) {
        return third(Parser__peek_token(self, peek_offset));
    }
    return true;
}

bool Parser__matches_two(Parser *self, bool (*first)(Token *), bool first_required, bool (*second)(Token *)) {
    return Parser__matches_three(self, first, first_required, second, true, null);
}

bool Parser__matches_one(Parser *self, bool (*first)(Token *)) {
    return Parser__matches_two(self, first, true, null);
}

Token *Parser__consume_token(Parser *self, bool (*check)(Token *)) {
    if (Parser__matches_one(self, check)) {
        Token *token = self->scanner->current_token;
        Scanner__next_token(self->scanner);
        return token;
    }
    Parser__panic(self, String__create_from("Unexpected token"));
}

void Parser__consume_comment(Parser *self) {
    Parser__consume_token(self, Token__is_comment);
}

void Parser__consume_end_of_line(Parser *self) {
    Token *token = Parser__consume_token(self, Token__is_end_of_line);
    if (Token__is_end_of_file(token)) {
        Token__warning(token, String__create_from("Unexpected end of file"));
    }
}

void Parser__consume_space(Parser *self, uint16_t count) {
    if (Parser__matches_one(self, Token__is_space)) {
        Space_Token *token = (Space_Token *) Parser__consume_token(self, Token__is_space);
        if (token->count != count) {
            String *message = String__append_cstring(String__append_int16_t(String__append_cstring(String__append_int16_t(String__create_from("Consumed "), token->count), " spaces where "), count), " were expected");
            Token__warning((Token *) token, message);
            String__delete(message);
        }
    } else if (count > 0) {
        String *message = String__append_cstring(String__append_int16_t(String__append_cstring(String__append_int16_t(String__create_from("Consumed "), 0), " spaces where "), count), " were expected");
        Parser__warning(self, message);
        String__delete(message);
    }
}

bool Parser__consume_empty_line(Parser *self) {
    if (Parser__matches_three(self, Token__is_space, false, Token__is_comment, false, Token__is_end_of_line)) {
        if (Parser__matches_two(self, Token__is_space, false, Token__is_comment)) {
            Parser__consume_space(self, self->current_identation * 4);
            Parser__consume_comment(self);
        } else {
            Parser__consume_space(self, 0);
        }
        Parser__consume_end_of_line(self);
        return true;
    } else if (Parser__matches_two(self, Token__is_space, false, Token__is_hash)) {
        // Preprocessor directives are ignored and treated as empty lines
        Parser__consume_space(self, 0);
        Parser__consume_token(self, Token__is_hash);
        while (!Parser__matches_one(self, Token__is_end_of_line)) {
            Parser__consume_token(self, Token__is_anything);
        }
        Parser__consume_end_of_line(self);
        return true;
    }
    return false;
}

AST_Type *Parser__parse_type(Parser *self);

// primary_expression
//      | IDENTIFIER
AST_Expression* Parser__parse_primary_expression(Parser *self) {
    if (Parser__matches_one(self, Token__is_identifier)) {
        return (AST_Expression*) AST_Symbol_Expression__create(Parser__consume_token(self, Token__is_identifier));
    }
    if (Parser__matches_one(self, Token__is_integer)) {
        return (AST_Expression*) AST_Integer_Expression__create((Integer_Token*) Parser__consume_token(self, Token__is_integer));
    }
    Parser__panic(self, String__create_from("Unsupported primary expression"));
}

AST_Expression* Parser__parse_expression(Parser *self);

// access_expression
//      | primary_expression ( "." IDENTIFIER | "->" IDENTIFIER | "(" ( expression ( "," expression )* )? ")" | "[" expression "]" )*
AST_Expression* Parser__parse_access_expression(Parser *self) {
    AST_Expression* expression = Parser__parse_primary_expression(self);
    while (true) {
        AST_Expression* old_expression = expression;
        if (Parser__matches_two(self, Token__is_space, false, Token__is_dot) || Parser__matches_three(self, Token__is_space, false, Token__is_minus, true, Token__is_greater_than)) {
            Parser__consume_space(self, 0);
            if (Parser__matches_one(self, Token__is_dot)) {
                Parser__consume_token(self, Token__is_dot);
            } else {
                Parser__consume_token(self, Token__is_minus);
                Parser__consume_token(self, Token__is_greater_than);
            }
            Parser__consume_space(self, 0);
            Token* name = Parser__consume_token(self, Token__is_identifier);
            expression = (AST_Expression*) AST_Member_Access_Expression__create(expression, name);
        }
        if (Parser__matches_two(self, Token__is_space, false, Token__is_opening_paren)) {
            Parser__consume_space(self, 0);
            Parser__consume_token(self, Token__is_opening_paren);
            Parser__consume_space(self, 0);
            if (expression->kind == AST_EXPRESSION_KIND__SYMBOL && String__equals_cstring(((AST_Symbol_Expression*) expression)->name->lexeme, "sizeof")) {
                AST_Type* type = Parser__parse_type(self);
                expression = (AST_Expression*) AST_Sizeof_Expression__create(expression->location, type);
            } else {
                AST_Call_Expression* call_expression = AST_Call_Expression__create(expression);
                if (!Parser__matches_one(self, Token__is_closing_paren)) {
                    AST_Call_Argument* last_argument = AST_Call_Argument__create(Parser__parse_expression(self));
                    call_expression->first_argument = last_argument;
                    Parser__consume_space(self, 0);
                    while (Parser__matches_one(self, Token__is_comma)) {
                        Parser__consume_token(self, Token__is_comma);
                        Parser__consume_space(self, 1);
                        AST_Call_Argument* argument = AST_Call_Argument__create(Parser__parse_expression(self));
                        last_argument->next_argument = argument;
                        last_argument = argument;
                        Parser__consume_space(self, 0);
                    }
                }
                expression = (AST_Expression*) call_expression;
            }
            Parser__consume_token(self, Token__is_closing_paren);
        }
        if (Parser__matches_two(self, Token__is_space, false, Token__is_opening_bracket)) {
            Parser__consume_space(self, 0);
            Parser__consume_token(self, Token__is_opening_bracket);
            Parser__consume_space(self, 0);
            AST_Expression* index_expression = Parser__parse_expression(self);
            Parser__consume_space(self, 0);
            Parser__consume_token(self, Token__is_closing_bracket);
            expression = (AST_Expression*) AST_Array_Access_Expression__create(expression, index_expression);
        }
        if (old_expression == expression) {
            break;
        }
    }
    return expression;
}

// unary_expression
//      | "-" unary_expression
//      | "!" unary_expression
//      | "(" type ")" unary_expression
//      | "sizeof" "(" type ")"
//      | access_expression
AST_Expression* Parser__parse_unary_expression(Parser *self) {
    Parser__warning(self, String__create_from("TODO: Parse unary expression"));
    return Parser__parse_access_expression(self);
}

bool Token__is_mutliplication(Token *self) {
    return Token__is_asterisk(self) || Token__is_slash(self) || Token__is_percent(self);
}

// multiplication
//      | unary_expression ( ( "*" | "/" | "%" ) unary_expression )*
AST_Expression* Parser__parse_multiplication_expression(Parser *self) {
    AST_Expression* expression = Parser__parse_unary_expression(self);
    while (Parser__matches_two(self, Token__is_space, false, Token__is_mutliplication)) {
        Parser__consume_space(self, 1);
        if (Parser__matches_one(self, Token__is_asterisk)) {
            Parser__consume_token(self, Token__is_asterisk);
            Parser__consume_space(self, 1);
            AST_Expression* right_expression = Parser__parse_unary_expression(self);
            expression = (AST_Expression*) AST_Multiply_Expression__create(expression, right_expression);
        } else if (Parser__matches_one(self, Token__is_slash)) {
            Parser__consume_token(self, Token__is_slash);
            Parser__consume_space(self, 1);
            AST_Expression* right_expression = Parser__parse_unary_expression(self);
            expression = (AST_Expression*) AST_Divide_Expression__create(expression, right_expression);
        } else {
            Parser__consume_token(self, Token__is_percent);
            Parser__consume_space(self, 1);
            AST_Expression* right_expression = Parser__parse_unary_expression(self);
            expression = (AST_Expression*) AST_Modulo_Expression__create(expression, right_expression);
        }
    }
    return expression;
}

bool Token__is_addition(Token *self) {
    return Token__is_plus(self) || Token__is_minus(self);
}

// addition
//      | multiplication ( ( "+" | "-" ) multiplication )*
AST_Expression* Parser__parse_addition_expression(Parser *self) {
    AST_Expression* expression = Parser__parse_multiplication_expression(self);
    while (Parser__matches_two(self, Token__is_space, false, Token__is_addition)) {
        Parser__consume_space(self, 1);
        if (Parser__matches_one(self, Token__is_plus)) {
            Parser__consume_token(self, Token__is_plus);
            Parser__consume_space(self, 1);
            AST_Expression* right_expression = Parser__parse_multiplication_expression(self);
            expression = (AST_Expression*) AST_Add_Expression__create(expression, right_expression);
        } else {
            Parser__consume_token(self, Token__is_minus);
            Parser__consume_space(self, 1);
            AST_Expression* right_expression = Parser__parse_multiplication_expression(self);
            expression = (AST_Expression*) AST_Substract_Expression__create(expression, right_expression);
        }
    }
    return expression;
}

// comparison
//      | addition ( ( "<=" | "<" | ">" | ">=") addition )*
AST_Expression* Parser__parse_comparison_expression(Parser *self) {
    AST_Expression* expression = Parser__parse_addition_expression(self);
    if (Parser__matches_two(self, Token__is_space, false, Token__is_less_than)) {
        Parser__consume_space(self, 1);
        Parser__consume_token(self, Token__is_less_than);
        if (Parser__matches_one(self, Token__is_equals)) {
            Parser__consume_token(self, Token__is_equals);
            Parser__consume_space(self, 1);
            AST_Expression* right_expression = Parser__parse_addition_expression(self);
            expression = (AST_Expression*) AST_Less_Or_Equals_Expression__create(expression, right_expression);
        } else {
            Parser__consume_space(self, 1);
            AST_Expression* right_expression = Parser__parse_addition_expression(self);
            expression = (AST_Expression*) AST_Less_Expression__create(expression, right_expression);
        }
    } else if (Parser__matches_two(self, Token__is_space, false, Token__is_greater_than)) {
        Parser__consume_space(self, 1);
        Parser__consume_token(self, Token__is_greater_than);
        if (Parser__matches_one(self, Token__is_equals)) {
            Parser__consume_token(self, Token__is_equals);
            Parser__consume_space(self, 1);
            AST_Expression* right_expression = Parser__parse_addition_expression(self);
            expression = (AST_Expression*) AST_Greater_Or_Equals_Expression__create(expression, right_expression);
        } else {
            Parser__consume_space(self, 1);
            AST_Expression* right_expression = Parser__parse_addition_expression(self);
            expression = (AST_Expression*) AST_Greater_Expression__create(expression, right_expression);
        }
    }
    return expression;
}

// equality
//      | comparison ( ( "==" | "!=" ) comparison )*
AST_Expression* Parser__parse_equality_expression(Parser *self) {
    AST_Expression* expression = Parser__parse_comparison_expression(self);
    if (Parser__matches_three(self, Token__is_space, false, Token__is_equals, true, Token__is_equals)) {
        Parser__consume_space(self, 1);
        Parser__consume_token(self, Token__is_equals);
        Parser__consume_token(self, Token__is_equals);
        Parser__consume_space(self, 1);
        AST_Expression* right_expression = Parser__parse_comparison_expression(self);
        expression = (AST_Expression*) AST_Equals_Expression__create(expression, right_expression);
    } else if (Parser__matches_three(self, Token__is_space, false, Token__is_exclamation_mark, true, Token__is_equals)) {
        Parser__consume_space(self, 1);
        Parser__consume_token(self, Token__is_exclamation_mark);
        Parser__consume_token(self, Token__is_equals);
        Parser__consume_space(self, 1);
        AST_Expression* right_expression = Parser__parse_comparison_expression(self);
        expression = (AST_Expression*) AST_Not_Equals_Expression__create(expression, right_expression);
    }
    return expression;
}

// logic_and
//      | equality ( "&&" equality )*
AST_Expression* Parser__parse_logic_and_expression(Parser *self) {
    AST_Expression* expression = Parser__parse_equality_expression(self);
    while (Parser__matches_three(self, Token__is_space, false, Token__is_ampersand, true, Token__is_ampersand)) {
        Parser__consume_space(self, 1);
        Parser__consume_token(self, Token__is_ampersand);
        Parser__consume_token(self, Token__is_ampersand);
        Parser__consume_space(self, 1);
        AST_Expression* right_expression = Parser__parse_equality_expression(self);
        expression = (AST_Expression*) AST_Logic_And_Expression__create(expression, right_expression);
    }
    return expression;
}

// logic_or
//      | logic_and ( "||" logic_and )*
AST_Expression* Parser__parse_logic_or_expression(Parser *self) {
    AST_Expression* expression = Parser__parse_logic_and_expression(self);
    while (Parser__matches_three(self, Token__is_space, false, Token__is_vertical_bar, true, Token__is_vertical_bar)) {
        Parser__consume_space(self, 1);
        Parser__consume_token(self, Token__is_vertical_bar);
        Parser__consume_space(self, 1);
        AST_Expression* right_expression = Parser__parse_logic_and_expression(self);
        expression = (AST_Expression*) AST_Logic_Or_Expression__create(expression, right_expression);
    }
    return expression;
}

// expression
//      | logic_or
AST_Expression* Parser__parse_expression(Parser *self) {
    return Parser__parse_logic_or_expression(self);
}

// struct
//      | "typedef" "struct" IDENTIFIER IDENTIFIER
//      | "typedef" "struct" IDENTIFIER "{" ( type "*"? IDENTIFIER ";" )* "}" IDENTIFIER
AST_Statement *Parser__parse_struct(Parser *self) {
    Source_Location *location = Parser__consume_token(self, Token__is_typedef)->location;
    Parser__consume_space(self, 1);
    Parser__consume_token(self, Token__is_struct);
    Parser__consume_space(self, 1);
    Token *local_name = Parser__consume_token(self, Token__is_identifier);
    AST_Struct_Statement *struct_statement = AST_Struct_Statement__create(location, local_name);
    Parser__consume_space(self, 1);
    if (Parser__matches_one(self, Token__is_identifier)) {
        struct_statement->is_opaque = true;
    } else {
        AST_Struct_Member *last_member = null;
        Parser__consume_token(self, Token__is_opening_brace);
        Parser__consume_end_of_line(self);
        while (!Parser__matches_two(self, Token__is_space, false, Token__is_closing_brace)) {
            Parser__consume_space(self, (self->current_identation + 1) * 4);
            AST_Type *type = Parser__parse_type(self);
            Parser__consume_space(self, 1);
            Token *name = Parser__consume_token(self, Token__is_identifier);
            Parser__consume_space(self, 0);
            Parser__consume_token(self, Token__is_semicolon);
            Parser__consume_end_of_line(self);
            // TODO: check for duplicate members
            AST_Struct_Member *member = AST_Struct_Member__create(name, type);
            if (last_member == null) {
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
        Token__panic(final_name, String__append_string(String__create_from("Final struct name doesn't match the local name: "), local_name->lexeme));
    }
    Parser__consume_space(self, 0);
    Parser__consume_token(self, Token__is_semicolon);
    Parser__create_type(self, AST_TYPE_KIND__STRUCT, final_name->lexeme, (AST_Statement*) struct_statement);
    return (AST_Statement*) struct_statement;
}

// type
//      | "const"? IDENTIFIER "*"*
AST_Type *Parser__parse_type(Parser *self) {
    bool is_const = false;
    Source_Location *location;
    if (Parser__matches_one(self, Token__is_const)) {
        is_const = true;
        location = Parser__consume_token(self, Token__is_const)->location;
        Parser__consume_space(self, 1);
    }
    Token *name = Parser__consume_token(self, Token__is_identifier);
    AST_Type *type = Parser__find_type(self, name->lexeme);
    if (type == null) {
        Token__panic(name, String__create_from("Undefined type"));
    }
    while (Parser__matches_two(self, Token__is_space, false, Token__is_asterisk)) {
        Parser__consume_space(self, 0);
        Parser__consume_token(self, Token__is_asterisk);
        type = AST_Pointer_Type__create(type);
    }
    if (is_const) {
        return AST_Const_Type__create(type);
    }
    return type;
}

// variable
//      | "extern"? type IDENTIFIER ( "=" expression )?
AST_Statement *Parser__parse_variable(Parser *self) {
    bool is_external;
    Source_Location *location;
    if (Parser__matches_one(self, Token__is_extern)) {
        is_external = true;
        location = Parser__consume_token(self, Token__is_extern)->location;
        Parser__consume_space(self, 1);
    } else {
        is_external = false;
        location = Parser__peek_token(self, 0)->location;
    }
    AST_Type *type = Parser__parse_type(self);
    Parser__consume_space(self, 1);
    Token *name = Parser__consume_token(self, Token__is_identifier);
    AST_Variable_Statement* variable_statement = AST_Variable_Statement__create(location, name, type, is_external);
    if (Parser__matches_two(self, Token__is_space, false, Token__is_equals)) {
        Parser__consume_space(self, 1);
        Parser__consume_token(self, Token__is_equals);
        Parser__consume_space(self, 1);
        variable_statement->expression = Parser__parse_expression(self);
    }
    Parser__consume_space(self, 0);
    Parser__consume_token(self, Token__is_semicolon);
    return (AST_Statement*) variable_statement;
}

AST_Function_Parameter *Parser__parse_function_parameter(Parser *self) {
    AST_Type *type = Parser__parse_type(self);
    Parser__consume_space(self, 1);
    Token *name = Parser__consume_token(self, Token__is_identifier);
    return AST_Function_Parameter__create(name, type);
}

AST_Function_Parameter *Parser__parse_function_parameters(Parser *self) {
    AST_Function_Parameter *first_parameter = null;
    if (!Parser__matches_two(self, Token__is_space, false, Token__is_closing_paren)) {
        Parser__consume_space(self, 0);
        first_parameter = Parser__parse_function_parameter(self);
        AST_Function_Parameter *last_parameter = first_parameter;
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

void Parser__parse_statements(Parser *self, AST_Statements *statements);

// block
//      | "{" statements "}"
AST_Block_Statement* Parser__parse_block_statement(Parser *self) {
    Source_Location *location = Parser__consume_token(self, Token__is_opening_brace)->location;
    Parser__consume_end_of_line(self);
    AST_Statements* statements = AST_Statements__create(false);
    self->current_identation = self->current_identation + 1;
    Parser__parse_statements(self, statements);
    self->current_identation = self->current_identation - 1;
    Parser__consume_space(self, self->current_identation * 4);
    Parser__consume_token(self, Token__is_closing_brace);
    return AST_Block_Statement__create(location, statements);
}

// function
//      | "extern"? type IDENTIFIER "(" function_parameter* ")" ( "{" statements "}" )?
AST_Statement *Parser__parse_function(Parser *self) {
    bool is_external;
    Source_Location *location;
    if (Parser__matches_one(self, Token__is_extern)) {
        is_external = true;
        location = Parser__consume_token(self, Token__is_extern)->location;
        Parser__consume_space(self, 1);
    } else {
        is_external = false;
        location = Parser__peek_token(self, 0)->location;
    }
    AST_Type *return_type = Parser__parse_type(self);
    Parser__consume_space(self, 1);
    Token *name = Parser__consume_token(self, Token__is_identifier);
    Parser__consume_space(self, 0);
    Parser__consume_token(self, Token__is_opening_paren);
    AST_Function_Parameter *first_parameter = Parser__parse_function_parameters(self);
    Parser__consume_space(self, 0);
    Parser__consume_token(self, Token__is_closing_paren);
    AST_Statements *statements = null;
    if (Parser__matches_two(self, Token__is_space, false, Token__is_opening_brace)) {
        Parser__consume_space(self, 1);
        Parser__consume_token(self, Token__is_opening_brace);
        Parser__consume_end_of_line(self);
        statements = AST_Statements__create(false);
        self->current_identation = self->current_identation + 1;
        Parser__parse_statements(self, statements);
        self->current_identation = self->current_identation - 1;
        Parser__consume_space(self, self->current_identation * 4);
        Parser__consume_token(self, Token__is_closing_brace);
    } else {
        Parser__consume_space(self, 0);
        Parser__consume_token(self, Token__is_semicolon);
    }
    return AST_Function_Statement__create(location, name, first_parameter, return_type, statements, is_external);
}

// return
//      | "return" expression
AST_Statement* Parser__parse_return_statement(Parser *self) {
    Source_Location* location = Parser__consume_token(self, Token__is_return)->location;
    Parser__consume_space(self, 1);
    AST_Expression* expression = Parser__parse_expression(self);
    Parser__consume_space(self, 0);
    Parser__consume_token(self, Token__is_semicolon);
    return AST_Return_Statement__create(location, expression);
}

// if
//      | "if" "(" expression ")" statement ( "else" statement )?
AST_Statement* Parser__parse_if_statement(Parser *self) {
    Source_Location* location = Parser__consume_token(self, Token__is_if)->location;
    Parser__consume_space(self, 1);
    Parser__consume_token(self, Token__is_opening_paren);
    Parser__consume_space(self, 0);
    AST_Expression* condition_expression = Parser__parse_expression(self);
    Parser__consume_space(self, 0);
    Parser__consume_token(self, Token__is_closing_paren);
    Parser__consume_space(self, 1);
    AST_Statement* true_statement = (AST_Statement*) Parser__parse_block_statement(self);
    AST_Statement* false_statement = null;
    if (Parser__matches_two(self, Token__is_space, false, Token__is_else)) {
        Parser__consume_space(self, 1);
        Parser__consume_token(self, Token__is_else);
        Parser__consume_space(self, 1);
        false_statement = (AST_Statement*) Parser__parse_block_statement(self);
    }
    return AST_If_Statement__create(location, condition_expression, true_statement, false_statement);
}

// statement
//      | function
//      | if
//      | return
//      | struct
//      | variable
AST_Statement* Parser__parse_statement(Parser *self) {
    Parser__consume_space(self, self->current_identation * 4);

    if (Parser__matches_one(self, Token__is_if)) {
        return Parser__parse_if_statement(self);
    }

    if (Parser__matches_one(self, Token__is_return)) {
        return Parser__parse_return_statement(self);
    }

    if (Parser__matches_three(self, Token__is_typedef, true, Token__is_space, true, Token__is_struct)) {
        return Parser__parse_struct(self);
    }

    if (Parser__matches_one(self, Token__is_const) || Parser__matches_one(self, Token__is_extern) || Parser__matches_one(self, Token__is_identifier)) {
        uint8_t peek_offset = 0;
        if (Token__is_extern(Parser__peek_token(self, peek_offset))) {
            peek_offset = peek_offset + 1;
            if (Token__is_space(Parser__peek_token(self, peek_offset))) {
                peek_offset = peek_offset + 1;
            }
        }
        if (Token__is_const(Parser__peek_token(self, peek_offset))) {
            peek_offset = peek_offset + 1;
            if (Token__is_space(Parser__peek_token(self, peek_offset))) {
                peek_offset = peek_offset + 1;
            }
        }
        if (Token__is_identifier(Parser__peek_token(self, peek_offset))) {
            peek_offset = peek_offset + 1;
            if (Token__is_space(Parser__peek_token(self, peek_offset))) {
                peek_offset = peek_offset + 1;
            }
            while (Token__is_asterisk(Parser__peek_token(self, peek_offset)))
            {
                peek_offset = peek_offset + 1;
                if (Token__is_space(Parser__peek_token(self, peek_offset))) {
                    peek_offset = peek_offset + 1;
                }
            }
            if (Token__is_identifier(Parser__peek_token(self, peek_offset))) {
                peek_offset = peek_offset + 1;
                if (Token__is_space(Parser__peek_token(self, peek_offset))) {
                    peek_offset = peek_offset + 1;
                }
                if (Token__is_opening_paren(Parser__peek_token(self, peek_offset))) {
                    return Parser__parse_function(self);
                }
                return Parser__parse_variable(self);
            }
        }
    }

    AST_Expression* expresion = Parser__parse_access_expression(self);
    if (Parser__matches_two(self, Token__is_space, false, Token__is_equals)) {
        Parser__consume_space(self, 1);
        Parser__consume_token(self, Token__is_equals);
        Parser__consume_space(self, 1);
        AST_Expression* value_expression = Parser__parse_expression(self);
        Parser__consume_space(self, 0);
        Parser__consume_token(self, Token__is_semicolon);
        return (AST_Statement*) AST_Assignment_Statement__create(expresion, value_expression);
    }
    Parser__consume_space(self, 0);
    Parser__consume_token(self, Token__is_semicolon);
    return (AST_Statement*) AST_Expression_Statement__create(expresion);
}

// statements
//      | ( statement ";" <EOL> )*
void Parser__parse_statements(Parser *self, AST_Statements *statements) {
    while (true) {
        while (Parser__consume_empty_line(self));

        if (statements->has_globals) {
            if (Parser__matches_three(self, Token__is_space, false, Token__is_comment, false, Token__is_end_of_line)) {
                return;
            }
        } else {
            if (Parser__matches_two(self, Token__is_space, false, Token__is_closing_brace)) {
                return;
            }
        }

        AST_Statement *statement = Parser__parse_statement(self);

        Parser__consume_end_of_line(self);

        AST_Statements__append(statements, statement);
    }
}

void Parser__parse_source(Parser *self, Source *source) {
    Scanner *other_scanner = self->scanner;

    self->scanner = Scanner__create(source);

    Parser__parse_statements(self, self->compilation_unit->statements);

    if (!Token__is_end_of_file(self->scanner->current_token)) {
        Parser__panic(self, String__create_from("Scanner didn't reach end of file"));
    }

    // TODO: warn if the source doesn't end with a new line

    self->scanner = other_scanner;
}

AST_Compilation_Unit *parse(Source *source) {
    Parser parser;
    parser.scanner = null;
    parser.types = AST_Types__create();
    parser.compilation_unit = AST_Compilation_Unit__create();
    parser.current_identation = 0;

    Parser__create_type(&parser, AST_TYPE_KIND__BOOL, String__create_from("bool"), null);
    Parser__create_type(&parser, AST_TYPE_KIND__CHAR, String__create_from("char"), null);
    Parser__create_type(&parser, AST_TYPE_KIND__INT16_T, String__create_from("int16_t"), null);
    Parser__create_type(&parser, AST_TYPE_KIND__INT32_T, String__create_from("int32_t"), null);
    Parser__create_type(&parser, AST_TYPE_KIND__INT64_T, String__create_from("int64_t"), null);
    Parser__create_type(&parser, AST_TYPE_KIND__INT8_T, String__create_from("int8_t"), null);
    Parser__create_type(&parser, AST_TYPE_KIND__SIZE_T, String__create_from("size_t"), null);
    Parser__create_type(&parser, AST_TYPE_KIND__UINT16_T, String__create_from("uint16_t"), null);
    Parser__create_type(&parser, AST_TYPE_KIND__UINT32_T, String__create_from("uint32_t"), null);
    Parser__create_type(&parser, AST_TYPE_KIND__UINT64_T, String__create_from("uint64_t"), null);
    Parser__create_type(&parser, AST_TYPE_KIND__UINT8_T, String__create_from("uint8_t"), null);
    Parser__create_type(&parser, AST_TYPE_KIND__VOID, String__create_from("void"), null);

    Parser__parse_source(&parser, source);

    return parser.compilation_unit;
}

// Main

int32_t main() {
    Source *source = Source__create(stdin);

    AST_Compilation_Unit *compilation_unit = parse(source);

    return 0;
}
