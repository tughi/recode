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

String *String__create() {
    return String__create_empty(16);
}

void String__delete(String *self) {
    free(self->data);
    free(self);
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

String *String__append_cstring(String *self, const char *s) {
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
    Source *source;
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
    Source *source;
    String *lexeme;
    Token *next_token;
} Comment_Token;

Comment_Token *Comment_Token__create(Source_Location *location, String *lexeme) {
    return Token__create(sizeof(Comment_Token), TOKEN_KIND__COMMENT, location, lexeme);
}

typedef struct {
    Token_Kind kind;
    Source *source;
    String *lexeme;
    Token *next_token;
} End_Of_File_Token;

End_Of_File_Token *End_Of_File_Token__create(Source_Location *location, String *lexeme) {
    return Token__create(sizeof(End_Of_File_Token), TOKEN_KIND__END_OF_FILE, location, lexeme);
}

typedef struct {
    Token_Kind kind;
    Source *source;
    String *lexeme;
    Token *next_token;
} End_Of_Line_Token;

End_Of_Line_Token *End_Of_Line_Token__create(Source_Location *location, String *lexeme) {
    return Token__create(sizeof(End_Of_Line_Token), TOKEN_KIND__END_OF_LINE, location, lexeme);
}

typedef struct {
    Token_Kind kind;
    Source *source;
    String *lexeme;
    Token *next_token;
} Error_Token;

Error_Token *Error_Token__create(Source_Location *location, String *lexeme) {
    return Token__create(sizeof(Error_Token), TOKEN_KIND__ERROR, location, lexeme);
}

typedef struct {
    Token_Kind kind;
    Source *source;
    String *lexeme;
    Token *next_token;
} Identifier_Token;

Identifier_Token *Identifier_Token__create(Source_Location *location, String *lexeme) {
    return Token__create(sizeof(Identifier_Token), TOKEN_KIND__IDENTIFIER, location, lexeme);
}

typedef struct {
    Token_Kind kind;
    Source *source;
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
    Source *source;
    String *lexeme;
    Token *next_token;
} Other_Token;

Other_Token *Other_Token__create(Source_Location *location, String *lexeme) {
    return Token__create(sizeof(Other_Token), TOKEN_KIND__OTHER, location, lexeme);
}

typedef struct {
    Token_Kind kind;
    Source *source;
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
    Source *source;
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

bool Token__is_keyword(Token *self, const char *lexeme) {
    return self->kind == TOKEN_KIND__IDENTIFIER && String__equals_cstring(self->lexeme, lexeme);
}

bool Token__is_const(Token *self) {
    return Token__is_keyword(self, "const");
}

bool Token__is_extern(Token *self) {
    return Token__is_keyword(self, "extern");
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

bool Token__is_equals(Token *self) {
    return Token__is_other(self, "=");
}

bool Token__is_hash(Token *self) {
    return Token__is_other(self, "#");
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

bool Token__is_semicolon(Token *self) {
    return Token__is_other(self, ";");
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
    AST_STATEMENT_KIND__FUNCTION,
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
    bool is_external;
} AST_Function_Statement;

AST_Statement *AST_Function_Statement__create(Source_Location *location, Token *name, AST_Function_Parameter *first_parameter, AST_Type *resturn_type, bool is_external) {
    AST_Function_Statement *statement = AST_Named_Statement__create(sizeof(AST_Function_Statement), AST_STATEMENT_KIND__FUNCTION, location, name);
    statement->first_parameter = first_parameter;
    statement->return_type = resturn_type;
    statement->is_external = is_external;
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
    bool is_external;
} AST_Variable_Statement;

AST_Statement *AST_Variable_Statement__create(Source_Location *location, Token *name, AST_Type *type, bool is_external) {
    AST_Variable_Statement *statement = AST_Named_Statement__create(sizeof(AST_Variable_Statement), AST_STATEMENT_KIND__VARIABLE, location, name);
    statement->type = type;
    statement->is_external = is_external;
    return (AST_Statement *) statement;
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
    if (Parser__matches_two(self, Token__is_space, false, Token__is_equals)) {
        Parser__consume_space(self, 1);
        Parser__consume_token(self, Token__is_equals);
        Parser__consume_space(self, 1);
        Parser__panic(self, String__create_from("TODO: parse expression"));
    }
    return AST_Variable_Statement__create(location, name, type, is_external);
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
    if (Parser__matches_two(self, Token__is_space, false, Token__is_opening_brace)) {
        Parser__consume_space(self, 1);
        Parser__consume_token(self, Token__is_opening_brace);
        Parser__consume_end_of_line(self);
        AST_Statements *statements = AST_Statements__create(false);
        self->current_identation = self->current_identation + 1;
        Parser__parse_statements(self, statements);
        self->current_identation = self->current_identation - 1;
        Parser__consume_space(self, self->current_identation * 4);
        Parser__consume_token(self, Token__is_closing_brace);
        Parser__consume_end_of_line(self);
    }
    return AST_Function_Statement__create(location, name, first_parameter, return_type, is_external);
}

// statement
//      | struct
//      | variable
AST_Statement* Parser__parse_statement(Parser *self) {
    while (Parser__consume_empty_line(self));

    Parser__consume_space(self, self->current_identation * 4);

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

    return null;
}

// statements
//      | ( statement ";" <EOL> )*
void Parser__parse_statements(Parser *self, AST_Statements *statements) {
    while (true) {
        AST_Statement *statement = Parser__parse_statement(self);
        if (statement == null) {
            return;
        }
        Parser__consume_space(self, 0);
        Parser__consume_token(self, Token__is_semicolon);
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
