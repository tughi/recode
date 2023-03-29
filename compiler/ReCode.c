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

size_t cstring_length(const char* s) {
    size_t length = 0;
    while (true) {
        uint8_t c = s[length];
        if (c == 0) {
            break;
        }
        length = length + 1;
    }
    return length;
}

String* String__create_from(const char* data) {
    size_t string_length = cstring_length(data);
    String* string = String__create_empty(string_length);
    String__append_cstring(string, data);
    return string;
}

String* String__append_int16_t(String* self, int16_t value) {
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

String* String__append_string(String* self, String* other) {
    size_t index = 0;
    while (index < other->length) {
        String__append_char(self, other->data[index]);
        index = index + 1;
    }
    return self;
}

bool String__equals_cstring(String* self, const char* s) {
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

bool String__equals_string(String* self, String* other) {
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

void File__write_char(File* self, uint8_t c) {
    fputc(c, self);
}

void File__write_cstring(File* self, const char* s) {
    fputs(s, self);
}

void File__write_int32_t(File* self, int32_t value) {
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

void File__write_string(File* self, String* string) {
    size_t index = 0;
    while (index < string->length) {
        File__write_char(self, string->data[index]);
        index = index + 1;
    }
}

void panic(String* message) {
    File__write_cstring(stderr, "\e[0;91m");
    File__write_string(stderr, message);
    File__write_cstring(stderr, "\e[0m\n");
    abort();
}

void warning(String* message) {
    File__write_cstring(stderr, "\e[0;96m");
    File__write_string(stderr, message);
    File__write_cstring(stderr, "\e[0m\n");
}

// Source

typedef struct Source {
    String* content;
} Source;

Source* Source__create(File* stream) {
    String* source_content = String__create();

    while (true) {
        int32_t ch = fgetc(stream);
        if (ch == -1) {
            break;
        }
        String__append_char(source_content, ch);
    }

    String__append_char(source_content, '\0'); // simplifies EOF detection

    Source* source = malloc(sizeof(Source));
    source->content = source_content;

    return source;
}

// Source_Location

typedef struct Source_Location {
    Source* source;
    uint16_t line;
    uint16_t column;
} Source_Location;

Source_Location* Source_Location__create(Source* source, uint16_t line, uint16_t column) {
    Source_Location* source_location = malloc(sizeof(Source_Location));
    source_location->source = source;
    source_location->line = line;
    source_location->column = column;
    return source_location;
}

void File__write_source_location(File* self, Source_Location* location) {
    File__write_cstring(self, "compiler/ReCode.c:");
    File__write_int32_t(self, location->line);
    File__write_char(self, ':');
    File__write_int32_t(self, location->column);
    File__write_cstring(self, ": ");
}

void Source_Location__panic(Source_Location* self, String* message) {
    File__write_source_location(stderr, self);
    panic(message);
}

void Source_Location__warning(Source_Location* self, String* message) {
    File__write_source_location(stderr, self);
    warning(message);
}

// Token

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
    TOKEN_KIND__STRING,
} Token_Kind;

typedef struct Token {
    Token_Kind kind;
    Source_Location* location;
    String* lexeme;
    struct Token* next_token;
} Token;

void* Token__create(size_t size, uint16_t kind, Source_Location* location, String* lexeme) {
    Token* token = malloc(size);
    token->kind = kind;
    token->location = location;
    token->lexeme = lexeme;
    token->next_token = null;
    return token;
}

void Token__panic(Token* self, String* message) {
    Source_Location__panic(self->location, message);
}

void Token__warning(Token* self, String* message) {
    Source_Location__warning(self->location, message);
}

typedef struct Character_Token {
    Token super;
    uint8_t value;
} Character_Token;

Character_Token* Character_Token__create(Source_Location* location, String* lexeme, uint8_t value) {
    Character_Token* token = Token__create(sizeof(Character_Token), TOKEN_KIND__CHARACTER, location, lexeme);
    token->value = value;
    return token;
}

typedef struct Comment_Token {
    Token super;
} Comment_Token;

Comment_Token* Comment_Token__create(Source_Location* location, String* lexeme) {
    return Token__create(sizeof(Comment_Token), TOKEN_KIND__COMMENT, location, lexeme);
}

typedef struct End_Of_File_Token {
    Token super;
} End_Of_File_Token;

End_Of_File_Token* End_Of_File_Token__create(Source_Location* location, String* lexeme) {
    return Token__create(sizeof(End_Of_File_Token), TOKEN_KIND__END_OF_FILE, location, lexeme);
}

typedef struct End_Of_Line_Token {
    Token super;
} End_Of_Line_Token;

End_Of_Line_Token* End_Of_Line_Token__create(Source_Location* location, String* lexeme) {
    return Token__create(sizeof(End_Of_Line_Token), TOKEN_KIND__END_OF_LINE, location, lexeme);
}

typedef struct Error_Token {
    Token super;
} Error_Token;

Error_Token* Error_Token__create(Source_Location* location, String* lexeme) {
    return Token__create(sizeof(Error_Token), TOKEN_KIND__ERROR, location, lexeme);
}

typedef struct Identifier_Token {
    Token super;
} Identifier_Token;

Identifier_Token* Identifier_Token__create(Source_Location* location, String* lexeme) {
    return Token__create(sizeof(Identifier_Token), TOKEN_KIND__IDENTIFIER, location, lexeme);
}

typedef struct Integer_Token {
    Token super;
    uint64_t value;
} Integer_Token;

Integer_Token* Integer_Token__create(Source_Location* location, String* lexeme, uint64_t value) {
    Integer_Token* token = Token__create(sizeof(Integer_Token), TOKEN_KIND__INTEGER, location, lexeme);
    token->value = value;
    return token;
}

typedef struct Other_Token {
    Token super;
} Other_Token;

Other_Token* Other_Token__create(Source_Location* location, String* lexeme) {
    return Token__create(sizeof(Other_Token), TOKEN_KIND__OTHER, location, lexeme);
}

typedef struct Space_Token {
    Token super;
    uint16_t count;
} Space_Token;

Space_Token* Space_Token__create(Source_Location* location, String* lexeme, uint16_t count) {
    Space_Token* token = Token__create(sizeof(Space_Token), TOKEN_KIND__SPACE, location, lexeme);
    token->count = count;
    return token;
}

typedef struct String_Token {
    Token super;
    String* value;
} String_Token;

String_Token* String_Token__create(Source_Location* location, String* lexeme, String* value) {
    String_Token* token = Token__create(sizeof(String_Token), TOKEN_KIND__STRING, location, lexeme);
    token->value = value;
    return token;
}

bool Token__is_anything(Token* self) {
    return self != null;
}

bool Token__is_character(Token* self) {
    return self->kind == TOKEN_KIND__CHARACTER;
}

bool Token__is_comment(Token* self) {
    return self->kind == TOKEN_KIND__COMMENT;
}

bool Token__is_end_of_file(Token* self) {
    return self->kind == TOKEN_KIND__END_OF_FILE;
}

bool Token__is_end_of_line(Token* self) {
    return self->kind == TOKEN_KIND__END_OF_LINE || self->kind == TOKEN_KIND__END_OF_FILE;
}

bool Token__is_identifier(Token* self) {
    return self->kind == TOKEN_KIND__IDENTIFIER;
}

bool Token__is_integer(Token* self) {
    return self->kind == TOKEN_KIND__INTEGER;
}

bool Token__is_keyword(Token* self, const char* lexeme) {
    return self->kind == TOKEN_KIND__IDENTIFIER && String__equals_cstring(self->lexeme, lexeme);
}

bool Token__is_break(Token* self) {
    return Token__is_keyword(self, "break");
}

bool Token__is_const(Token* self) {
    return Token__is_keyword(self, "const");
}

bool Token__is_else(Token* self) {
    return Token__is_keyword(self, "else");
}

bool Token__is_enum(Token* self) {
    return Token__is_keyword(self, "enum");
}

bool Token__is_extern(Token* self) {
    return Token__is_keyword(self, "extern");
}

bool Token__is_false(Token* self) {
    return Token__is_keyword(self, "false");
}

bool Token__is_if(Token* self) {
    return Token__is_keyword(self, "if");
}

bool Token__is_null(Token* self) {
    return Token__is_keyword(self, "null");
}

bool Token__is_return(Token* self) {
    return Token__is_keyword(self, "return");
}

bool Token__is_sizeof(Token* self) {
    return Token__is_keyword(self, "sizeof");
}

bool Token__is_struct(Token* self) {
    return Token__is_keyword(self, "struct");
}

bool Token__is_true(Token* self) {
    return Token__is_keyword(self, "true");
}

bool Token__is_typedef(Token* self) {
    return Token__is_keyword(self, "typedef");
}

bool Token__is_while(Token* self) {
    return Token__is_keyword(self, "while");
}

bool Token__is_other(Token* self, const char* lexeme) {
    return self->kind == TOKEN_KIND__OTHER && String__equals_cstring(self->lexeme, lexeme);
}

bool Token__is_ampersand(Token* self) {
    return Token__is_other(self, "&");
}

bool Token__is_asterisk(Token* self) {
    return Token__is_other(self, "*");
}

bool Token__is_closing_brace(Token* self) {
    return Token__is_other(self, "}");
}

bool Token__is_closing_bracket(Token* self) {
    return Token__is_other(self, "]");
}

bool Token__is_closing_paren(Token* self) {
    return Token__is_other(self, ")");
}

bool Token__is_comma(Token* self) {
    return Token__is_other(self, ",");
}

bool Token__is_dot(Token* self) {
    return Token__is_other(self, ".");
}

bool Token__is_equals(Token* self) {
    return Token__is_other(self, "=");
}

bool Token__is_exclamation_mark(Token* self) {
    return Token__is_other(self, "!");
}

bool Token__is_greater_than(Token* self) {
    return Token__is_other(self, ">");
}

bool Token__is_hash(Token* self) {
    return Token__is_other(self, "#");
}

bool Token__is_less_than(Token* self) {
    return Token__is_other(self, "<");
}

bool Token__is_minus(Token* self) {
    return Token__is_other(self, "-");
}

bool Token__is_opening_brace(Token* self) {
    return Token__is_other(self, "{");
}

bool Token__is_opening_bracket(Token* self) {
    return Token__is_other(self, "[");
}

bool Token__is_opening_paren(Token* self) {
    return Token__is_other(self, "(");
}

bool Token__is_percent(Token* self) {
    return Token__is_other(self, "%");
}

bool Token__is_plus(Token* self) {
    return Token__is_other(self, "+");
}

bool Token__is_semicolon(Token* self) {
    return Token__is_other(self, ";");
}

bool Token__is_slash(Token* self) {
    return Token__is_other(self, "/");
}

bool Token__is_vertical_bar(Token* self) {
    return Token__is_other(self, "|");
}

bool Token__is_space(Token* self) {
    return self->kind == TOKEN_KIND__SPACE;
}

bool Token__is_string(Token* self) {
    return self->kind == TOKEN_KIND__STRING;
}

void File__write_token(File* stream, Token* token) {
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

typedef struct Scanner {
    Source* source;
    size_t current_char_index;
    size_t current_line;
    size_t current_column;
    Token* current_token;
} Scanner;

uint8_t Scanner__peek_char(Scanner* self) {
    return self->source->content->data[self->current_char_index];
}

uint8_t Scanner__next_char(Scanner* self) {
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
    if (c == 'n') {
        return '\n';
    }
    if (c == '"') {
        return '\"';
    }
    if (c == '\'') {
        return '\'';
    }
    if (c == '\\') {
        return '\\';
    }
    if (c == 't') {
        return '\t';
    }
    if (c == '0') {
        return '\0';
    }
    if (c == 'e') {
        return '\e';
    }
    return -1;
}

bool char_is_end_of_line(uint8_t c) {
    return c == '\n' || c == '\0';
}

Token* Scanner__scan_character_token(Scanner* self, Source_Location* source_location, String* token_lexeme) {
    if (Scanner__next_char(self) != '\'') {
        panic(String__create_from("Unexpected char"));
    }
    String__append_char(token_lexeme, '\'');

    uint8_t next_char = Scanner__peek_char(self);
    if (char_is_end_of_line(next_char) || next_char == '\t') {
        return (Token*) Error_Token__create(source_location, token_lexeme);
    }

    String__append_char(token_lexeme, Scanner__next_char(self));
    uint8_t value = next_char;

    if (value == '\'') {
        return (Token*) Error_Token__create(source_location, token_lexeme);
    }

    if (value == '\\') {
        next_char = Scanner__peek_char(self);
        if (char_is_end_of_line(next_char) || next_char == '\t') {
            return (Token*) Error_Token__create(source_location, token_lexeme);
        }

        String__append_char(token_lexeme, Scanner__next_char(self));

        value = escape_char_value(next_char);
        if (value == (uint8_t) -1) {
            return (Token*) Error_Token__create(source_location, token_lexeme);
        }
    }

    if (Scanner__peek_char(self) != '\'') {
        return (Token*) Error_Token__create(source_location, token_lexeme);
    }

    String__append_char(token_lexeme, Scanner__next_char(self));
    return (Token*) Character_Token__create(source_location, token_lexeme, value);
}

Token* Scanner__scan_comment_token(Scanner* self, Source_Location* source_location, String* token_lexeme) {
    while (!char_is_end_of_line(Scanner__peek_char(self))) {
        String__append_char(token_lexeme, Scanner__next_char(self));
    }
    return (Token*) Comment_Token__create(source_location, token_lexeme);
}

bool char_is_identifier_start(uint8_t c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool char_is_identifier_letter(uint8_t c) {
    return char_is_identifier_start(c) || (c >= '0' && c <= '9');
}

Token* Scanner__scan_identifier_token(Scanner* self, Source_Location* source_location, String* token_lexeme) {
    while (char_is_identifier_letter(Scanner__peek_char(self))) {
        String__append_char(token_lexeme, Scanner__next_char(self));
    }
    return (Token*) Identifier_Token__create(source_location, token_lexeme);
}

bool char_is_digit(uint8_t c) {
    return c >= '0' && c <= '9';
}

Token* Scanner__scan_integer_token(Scanner* self, Source_Location* source_location, String* token_lexeme) {
    uint64_t value = 0;
    while (char_is_digit(Scanner__peek_char(self))) {
        uint8_t c = Scanner__next_char(self);
        value = value * 10 + (c - '0');
        String__append_char(token_lexeme, c);
    }
    return (Token*) Integer_Token__create(source_location, token_lexeme, value);
}

bool char_is_space(uint8_t c) {
    return c == ' ';
}

Token* Scanner__scan_space_token(Scanner* self, Source_Location* source_location, String* token_lexeme) {
    uint16_t count = 0;
    while (char_is_space(Scanner__peek_char(self))) {
        count = count + 1;
        String__append_char(token_lexeme, Scanner__next_char(self));
    }
    return (Token*) Space_Token__create(source_location, token_lexeme, count);
}

Token* Scanner__scan_string_token(Scanner* self, Source_Location* source_location, String* token_lexeme) {
    if (Scanner__next_char(self) != '"') {
        panic(String__create_from("Unexpected char"));
    }
    String__append_char(token_lexeme, '"');

    String* value = String__create();

    while (true) {
        uint8_t next_char = Scanner__peek_char(self);
        if (char_is_end_of_line(next_char) || next_char == '\t') {
            return (Token*) Error_Token__create(source_location, token_lexeme);
        }

        String__append_char(token_lexeme, Scanner__next_char(self));

        if (next_char == '"') {
            return (Token*) String_Token__create(source_location, token_lexeme, value);
        }

        if (next_char == '\\') {
            next_char = Scanner__peek_char(self);
            if (char_is_end_of_line(next_char) || next_char == '\t') {
                return (Token*) Error_Token__create(source_location, token_lexeme);
            }

            String__append_char(token_lexeme, Scanner__next_char(self));

            next_char = escape_char_value(next_char);
            if (next_char == ((uint8_t) -1)) {
                return (Token*) Error_Token__create(source_location, token_lexeme);
            }
        }

        String__append_char(value, next_char);
    }
}

Token* Scanner__scan_token(Scanner* self) {
    Source_Location* source_location = Source_Location__create(self->source, self->current_line, self->current_column);
    String* token_lexeme = String__create();

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
        return (Token*) Other_Token__create(source_location, token_lexeme);
    }

    if (next_char == '\n') {
        String__append_char(token_lexeme, Scanner__next_char(self));
        return (Token*) End_Of_Line_Token__create(source_location, token_lexeme);
    }

    if (next_char == '\0') {
        return (Token*) End_Of_File_Token__create(source_location, token_lexeme);
    }

    String__append_char(token_lexeme, Scanner__next_char(self));
    return (Token*) Other_Token__create(source_location, token_lexeme);
}

Token* Scanner__next_token(Scanner* self) {
    if (self->current_token->next_token == null) {
        self->current_token->next_token = Scanner__scan_token(self);
    }
    self->current_token = self->current_token->next_token;
    return self->current_token;
}

Token* Scanner__peek_token(Scanner* self, uint8_t offset) {
    Token* token = self->current_token;
    while (offset > 0) {
        if (token->next_token == null) {
            token->next_token = Scanner__scan_token(self);
        }
        token = token->next_token;
        offset = offset - 1;
    }
    return token;
}

Scanner* Scanner__create(Source* source) {
    Scanner* scanner = malloc(sizeof(Scanner));
    scanner->source = source;
    scanner->current_char_index = 0;
    scanner->current_line = 1;
    scanner->current_column = 1;

    scanner->current_token = Scanner__scan_token(scanner);

    return scanner;
}

// Parse Tree

typedef struct Parsed_Statements Parsed_Statements;

typedef struct Parsed_Source {
    Parsed_Statements* statements;
} Parsed_Source;

typedef enum Parsed_Type_Kind {
    PARSED_TYPE_KIND__CONST,
    PARSED_TYPE_KIND__NAMED,
    PARSED_TYPE_KIND__POINTER,
    PARSED_TYPE_KIND__STRUCT,
} Parsed_Type_Kind;

typedef struct Parsed_Statement Parsed_Statement;

typedef struct Parsed_Type {
    Parsed_Type_Kind kind;
    Source_Location* location;
    String* name;
} Parsed_Type;

Parsed_Type* Parsed_Type__create(size_t size, Parsed_Type_Kind kind, Source_Location* location, String* name) {
    Parsed_Type* type = malloc(size);
    type->kind = kind;
    type->location = location;
    type->name = name;
    return type;
}

typedef struct Parsed_Const_Type {
    Parsed_Type super;
    Parsed_Type* other_type;
} Parsed_Const_Type;

Parsed_Type* Parsed_Const_Type__create(Source_Location* location, Parsed_Type* other_type) {
    Parsed_Const_Type* type = (Parsed_Const_Type*) Parsed_Type__create(sizeof(Parsed_Const_Type), PARSED_TYPE_KIND__CONST, location, String__append_string(String__create_from("const "), other_type->name));
    type->other_type = other_type;
    return (Parsed_Type*) type;
}

typedef struct Parsed_Named_Type {
    Parsed_Type super;
} Parsed_Named_Type;

Parsed_Type* Parsed_Named_Type__create(Token* name) {
    return Parsed_Type__create(sizeof(Parsed_Named_Type), PARSED_TYPE_KIND__NAMED, name->location, name->lexeme);
}

typedef struct Parsed_Pointer_Type {
    Parsed_Type super;
    Parsed_Type* other_type;
} Parsed_Pointer_Type;

Parsed_Type* Parsed_Pointer_Type__create(Parsed_Type* other_type) {
    Parsed_Pointer_Type* type = (Parsed_Pointer_Type*) Parsed_Type__create(sizeof(Parsed_Pointer_Type), PARSED_TYPE_KIND__POINTER, other_type->location, String__append_char(String__append_string(String__create_empty(other_type->name->length + 1), other_type->name), '*'));
    type->other_type = other_type;
    return (Parsed_Type*) type;
}

typedef struct Parsed_Struct_Type {
    Parsed_Type super;
    Parsed_Type* other_type;
} Parsed_Struct_Type;

Parsed_Type* Parsed_Struct_Type__create(Source_Location* location, Parsed_Type* other_type) {
    Parsed_Struct_Type* type = (Parsed_Struct_Type*) Parsed_Type__create(sizeof(Parsed_Struct_Type), PARSED_TYPE_KIND__STRUCT, location, String__append_string(String__create_from("struct "), other_type->name));
    type->other_type = other_type;
    return (Parsed_Type*) type;
}

typedef enum Parsed_Expression_Kind {
    PARSED_EXPRESSION_KIND__ADD,
    PARSED_EXPRESSION_KIND__ADDRESS_OF,
    PARSED_EXPRESSION_KIND__ARRAY_ACCESS,
    PARSED_EXPRESSION_KIND__BOOL,
    PARSED_EXPRESSION_KIND__CALL,
    PARSED_EXPRESSION_KIND__CAST,
    PARSED_EXPRESSION_KIND__CHARACTER,
    PARSED_EXPRESSION_KIND__DIVIDE,
    PARSED_EXPRESSION_KIND__EQUALS,
    PARSED_EXPRESSION_KIND__GREATER,
    PARSED_EXPRESSION_KIND__GREATER_OR_EQUALS,
    PARSED_EXPRESSION_KIND__GROUP,
    PARSED_EXPRESSION_KIND__INTEGER,
    PARSED_EXPRESSION_KIND__LESS,
    PARSED_EXPRESSION_KIND__LESS_OR_EQUALS,
    PARSED_EXPRESSION_KIND__LOGIC_AND,
    PARSED_EXPRESSION_KIND__LOGIC_OR,
    PARSED_EXPRESSION_KIND__MEMBER_ACCESS,
    PARSED_EXPRESSION_KIND__MINUS,
    PARSED_EXPRESSION_KIND__MODULO,
    PARSED_EXPRESSION_KIND__MULTIPLY,
    PARSED_EXPRESSION_KIND__NOT_EQUALS,
    PARSED_EXPRESSION_KIND__NULL,
    PARSED_EXPRESSION_KIND__SIZEOF,
    PARSED_EXPRESSION_KIND__STRING,
    PARSED_EXPRESSION_KIND__SUBSTRACT,
    PARSED_EXPRESSION_KIND__SYMBOL,
} Parsed_Expression_Kind;

typedef struct Parsed_Expression {
    Parsed_Expression_Kind kind;
    Source_Location* location;
} Parsed_Expression;

Parsed_Expression* Parsed_Expression__create(size_t size, Parsed_Expression_Kind kind, Source_Location* location) {
    Parsed_Expression* expression = malloc(size);
    expression->kind = kind;
    expression->location = location;
    return expression;
}

typedef struct Parsed_Binary_Expression {
    Parsed_Expression super;
    Parsed_Expression* left_expression;
    Parsed_Expression* right_expression;
} Parsed_Binary_Expression;

Parsed_Binary_Expression* Parsed_Binary_Expression__create(Parsed_Expression_Kind kind, Parsed_Expression* left_expression, Parsed_Expression* right_expression) {
    Parsed_Binary_Expression* expression = (Parsed_Binary_Expression*) Parsed_Expression__create(sizeof(Parsed_Binary_Expression), kind, left_expression->location);
    expression->left_expression = left_expression;
    expression->right_expression = right_expression;
    return expression;
}

typedef struct Parsed_Unary_Expression {
    Parsed_Expression super;
    Parsed_Expression* other_expression;
} Parsed_Unary_Expression;

Parsed_Unary_Expression* Parsed_Unary_Expression__create(size_t size, Parsed_Expression_Kind kind, Source_Location* location, Parsed_Expression* other_expression) {
    Parsed_Unary_Expression* expression = (Parsed_Unary_Expression*) Parsed_Expression__create(size, kind, location);
    expression->other_expression = other_expression;
    return expression;
}

typedef struct Parsed_Literal_Expression {
    Parsed_Expression super;
    Token* literal;
} Parsed_Literal_Expression;

Parsed_Literal_Expression* Parsed_Literal_Expression__create(size_t size, Parsed_Expression_Kind kind, Token* literal) {
    Parsed_Literal_Expression* expression = (Parsed_Literal_Expression*) Parsed_Expression__create(size, kind, literal->location);
    expression->literal = literal;
    return expression;
}

typedef struct Parsed_Add_Expression {
    Parsed_Binary_Expression super;
} Parsed_Add_Expression;

Parsed_Add_Expression* Parsed_Add_Expression__create(Parsed_Expression* left_expression, Parsed_Expression* right_expression) {
    return (Parsed_Add_Expression*) Parsed_Binary_Expression__create(PARSED_EXPRESSION_KIND__ADD, left_expression, right_expression);
}

typedef struct Parsed_Address_Of_Expression {
    Parsed_Binary_Expression super;
} Parsed_Address_Of_Expression;

Parsed_Address_Of_Expression* Parsed_Address_Of_Expression__create(Source_Location* location, Parsed_Expression* other_expression) {
    return (Parsed_Address_Of_Expression*) Parsed_Unary_Expression__create(sizeof(Parsed_Address_Of_Expression), PARSED_EXPRESSION_KIND__ADDRESS_OF, location, other_expression);
}

typedef struct Parsed_Array_Access_Expression {
    Parsed_Expression super;
    Parsed_Expression* array_expression;
    Parsed_Expression* index_expression;
} Parsed_Array_Access_Expression;

Parsed_Array_Access_Expression* Parsed_Array_Access_Expression__create(Parsed_Expression* array_expression, Parsed_Expression* index_expression) {
    Parsed_Array_Access_Expression* expression = (Parsed_Array_Access_Expression*) Parsed_Expression__create(sizeof(Parsed_Array_Access_Expression), PARSED_EXPRESSION_KIND__ARRAY_ACCESS, array_expression->location);
    expression->array_expression = array_expression;
    expression->index_expression = index_expression;
    return expression;
}

typedef struct Parsed_Bool_Expression {
    Parsed_Literal_Expression super;
    bool value;
} Parsed_Bool_Expression;

Parsed_Bool_Expression* Parsed_Bool_Expression__create(Token* literal, bool value) {
    Parsed_Bool_Expression* expression = (Parsed_Bool_Expression*) Parsed_Literal_Expression__create(sizeof(Parsed_Bool_Expression), PARSED_EXPRESSION_KIND__BOOL, literal);
    expression->value = value;
    return expression;
}

typedef struct Parsed_Call_Argument {
    Parsed_Expression* expression;
    struct Parsed_Call_Argument* next_argument;
} Parsed_Call_Argument;

Parsed_Call_Argument* Parsed_Call_Argument__create(Parsed_Expression* expression) {
    Parsed_Call_Argument* argument = malloc(sizeof(Parsed_Call_Argument));
    argument->expression = expression;
    argument->next_argument = null;
    return argument;
}

typedef struct Parsed_Call_Expression {
    Parsed_Expression super;
    Parsed_Expression* callee_expression;
    Parsed_Call_Argument* first_argument;
} Parsed_Call_Expression;

Parsed_Call_Expression* Parsed_Call_Expression__create(Parsed_Expression* callee_expression) {
    Parsed_Call_Expression* expression = (Parsed_Call_Expression*) Parsed_Expression__create(sizeof(Parsed_Call_Expression), PARSED_EXPRESSION_KIND__CALL, callee_expression->location);
    expression->callee_expression = callee_expression;
    expression->first_argument = null;
    return expression;
}

typedef struct Parsed_Cast_Expression {
    Parsed_Unary_Expression super;
    Parsed_Type* type;
} Parsed_Cast_Expression;

Parsed_Cast_Expression* Parsed_Cast_Expression__create(Source_Location* location, Parsed_Expression* other_expression, Parsed_Type* type) {
    Parsed_Cast_Expression* expression = (Parsed_Cast_Expression*) Parsed_Unary_Expression__create(sizeof(Parsed_Cast_Expression), PARSED_EXPRESSION_KIND__CAST, location, other_expression);
    expression->type = type;
    return expression;
}

typedef struct Parsed_Character_Expression {
    Parsed_Literal_Expression super;
    uint8_t value;
} Parsed_Character_Expression;

Parsed_Character_Expression* Parsed_Character_Expression__create(Character_Token* literal) {
    Parsed_Character_Expression* expression = (Parsed_Character_Expression*) Parsed_Expression__create(sizeof(Parsed_Character_Expression), PARSED_EXPRESSION_KIND__CHARACTER, literal->super.location);
    expression->value = literal->value;
    return expression;
}

typedef struct Parsed_Divide_Expression {
    Parsed_Binary_Expression super;
} Parsed_Divide_Expression;

Parsed_Divide_Expression* Parsed_Divide_Expression__create(Parsed_Expression* left_expression, Parsed_Expression* right_expression) {
    return (Parsed_Divide_Expression*) Parsed_Binary_Expression__create(PARSED_EXPRESSION_KIND__DIVIDE, left_expression, right_expression);
}

typedef struct Parsed_Equals_Expression {
    Parsed_Binary_Expression super;
} Parsed_Equals_Expression;

Parsed_Equals_Expression* Parsed_Equals_Expression__create(Parsed_Expression* left_expression, Parsed_Expression* right_expression) {
    return (Parsed_Equals_Expression*) Parsed_Binary_Expression__create(PARSED_EXPRESSION_KIND__EQUALS, left_expression, right_expression);
}

typedef struct Parsed_Greater_Expression {
    Parsed_Binary_Expression super;
} Parsed_Greater_Expression;

Parsed_Greater_Expression* Parsed_Greater_Expression__create(Parsed_Expression* left_expression, Parsed_Expression* right_expression) {
    return (Parsed_Greater_Expression*) Parsed_Binary_Expression__create(PARSED_EXPRESSION_KIND__GREATER, left_expression, right_expression);
}

typedef struct Parsed_Greater_Or_Equals_Expression {
    Parsed_Binary_Expression super;
} Parsed_Greater_Or_Equals_Expression;

Parsed_Greater_Or_Equals_Expression* Parsed_Greater_Or_Equals_Expression__create(Parsed_Expression* left_expression, Parsed_Expression* right_expression) {
    return (Parsed_Greater_Or_Equals_Expression*) Parsed_Binary_Expression__create(PARSED_EXPRESSION_KIND__GREATER_OR_EQUALS, left_expression, right_expression);
}

typedef struct Parsed_Group_Expression {
    Parsed_Expression super;
    Parsed_Expression* other_expression;
} Parsed_Group_Expression;

Parsed_Group_Expression* Parsed_Group_Expression__create(Source_Location* location, Parsed_Expression* other_expression) {
    Parsed_Group_Expression* expression = (Parsed_Group_Expression*) Parsed_Expression__create(sizeof(Parsed_Group_Expression), PARSED_EXPRESSION_KIND__GROUP, location);
    expression->other_expression = other_expression;
    return expression;
}

typedef struct Parsed_Integer_Expression {
    Parsed_Literal_Expression super;
    uint64_t value;
} Parsed_Integer_Expression;

Parsed_Integer_Expression* Parsed_Integer_Expression__create(Integer_Token* literal) {
    Parsed_Integer_Expression* expression = (Parsed_Integer_Expression*) Parsed_Expression__create(sizeof(Parsed_Integer_Expression), PARSED_EXPRESSION_KIND__INTEGER, literal->super.location);
    expression->value = literal->value;
    return expression;
}

typedef struct Parsed_Less_Expression {
    Parsed_Binary_Expression super;
} Parsed_Less_Expression;

Parsed_Less_Expression* Parsed_Less_Expression__create(Parsed_Expression* left_expression, Parsed_Expression* right_expression) {
    return (Parsed_Less_Expression*) Parsed_Binary_Expression__create(PARSED_EXPRESSION_KIND__LESS, left_expression, right_expression);
}

typedef struct Parsed_Less_Or_Equals_Expression {
    Parsed_Binary_Expression super;
} Parsed_Less_Or_Equals_Expression;

Parsed_Less_Or_Equals_Expression* Parsed_Less_Or_Equals_Expression__create(Parsed_Expression* left_expression, Parsed_Expression* right_expression) {
    return (Parsed_Less_Or_Equals_Expression*) Parsed_Binary_Expression__create(PARSED_EXPRESSION_KIND__LESS_OR_EQUALS, left_expression, right_expression);
}

typedef struct Parsed_Logic_And_Expression {
    Parsed_Binary_Expression super;
} Parsed_Logic_And_Expression;

Parsed_Logic_And_Expression* Parsed_Logic_And_Expression__create(Parsed_Expression* left_expression, Parsed_Expression* right_expression) {
    return (Parsed_Logic_And_Expression*) Parsed_Binary_Expression__create(PARSED_EXPRESSION_KIND__LOGIC_AND, left_expression, right_expression);
}

typedef struct Parsed_Logic_Or_Expression {
    Parsed_Binary_Expression super;
} Parsed_Logic_Or_Expression;

Parsed_Logic_Or_Expression* Parsed_Logic_Or_Expression__create(Parsed_Expression* left_expression, Parsed_Expression* right_expression) {
    return (Parsed_Logic_Or_Expression*) Parsed_Binary_Expression__create(PARSED_EXPRESSION_KIND__LOGIC_OR, left_expression, right_expression);
}

typedef struct Parsed_Member_Access_Expression {
    Parsed_Expression super;
    Parsed_Expression* value_expression;
    Token* member_name;
} Parsed_Member_Access_Expression;

Parsed_Member_Access_Expression* Parsed_Member_Access_Expression__create(Parsed_Expression* value_expression, Token* member_name) {
    Parsed_Member_Access_Expression* expression = (Parsed_Member_Access_Expression*) Parsed_Expression__create(sizeof(Parsed_Member_Access_Expression), PARSED_EXPRESSION_KIND__MEMBER_ACCESS, value_expression->location);
    expression->value_expression = value_expression;
    expression->member_name = member_name;
    return expression;
}

typedef struct Parsed_Minus_Expression {
    Parsed_Unary_Expression super;
} Parsed_Minus_Expression;

Parsed_Minus_Expression* Parsed_Minus_Expression__create(Source_Location* location, Parsed_Expression* other_expression) {
    return (Parsed_Minus_Expression*) Parsed_Unary_Expression__create(sizeof(Parsed_Minus_Expression), PARSED_EXPRESSION_KIND__MINUS, location, other_expression);
}

typedef struct Parsed_Modulo_Expression {
    Parsed_Binary_Expression super;
} Parsed_Modulo_Expression;

Parsed_Modulo_Expression* Parsed_Modulo_Expression__create(Parsed_Expression* left_expression, Parsed_Expression* right_expression) {
    return (Parsed_Modulo_Expression*) Parsed_Binary_Expression__create(PARSED_EXPRESSION_KIND__MODULO, left_expression, right_expression);
}

typedef struct Parsed_Multiply_Expression {
    Parsed_Binary_Expression super;
} Parsed_Multiply_Expression;

Parsed_Multiply_Expression* Parsed_Multiply_Expression__create(Parsed_Expression* left_expression, Parsed_Expression* right_expression) {
    return (Parsed_Multiply_Expression*) Parsed_Binary_Expression__create(PARSED_EXPRESSION_KIND__MULTIPLY, left_expression, right_expression);
}

typedef struct Parsed_Not_Expression {
    Parsed_Unary_Expression super;
} Parsed_Not_Expression;

Parsed_Not_Expression* Parsed_Not_Expression__create(Source_Location* location, Parsed_Expression* other_expression) {
    return (Parsed_Not_Expression*) Parsed_Unary_Expression__create(sizeof(Parsed_Not_Expression), PARSED_EXPRESSION_KIND__MINUS, location, other_expression);
}

typedef struct Parsed_Not_Equals_Expression {
    Parsed_Binary_Expression super;
} Parsed_Not_Equals_Expression;

Parsed_Not_Equals_Expression* Parsed_Not_Equals_Expression__create(Parsed_Expression* left_expression, Parsed_Expression* right_expression) {
    return (Parsed_Not_Equals_Expression*) Parsed_Binary_Expression__create(PARSED_EXPRESSION_KIND__NOT_EQUALS, left_expression, right_expression);
}

typedef struct Parsed_Null_Expression {
    Parsed_Literal_Expression super;
} Parsed_Null_Expression;

Parsed_Null_Expression* Parsed_Null_Expression__create(Token* literal) {
    return (Parsed_Null_Expression*) Parsed_Literal_Expression__create(sizeof(Parsed_Null_Expression), PARSED_EXPRESSION_KIND__NULL, literal);
}

typedef struct Parsed_Sizeof_Expression {
    Parsed_Expression super;
    Parsed_Type* type;
} Parsed_Sizeof_Expression;

Parsed_Sizeof_Expression* Parsed_Sizeof_Expression__create(Source_Location* location, Parsed_Type* type) {
    Parsed_Sizeof_Expression* expression = (Parsed_Sizeof_Expression*) Parsed_Expression__create(sizeof(Parsed_Sizeof_Expression), PARSED_EXPRESSION_KIND__SIZEOF, location);
    expression->type = type;
    return expression;
}

typedef struct Parsed_String_Expression {
    Parsed_Literal_Expression super;
    String* value;
} Parsed_String_Expression;

Parsed_String_Expression* Parsed_String_Expression__create(String_Token* literal) {
    Parsed_String_Expression* expression = (Parsed_String_Expression*) Parsed_Expression__create(sizeof(Parsed_String_Expression), PARSED_EXPRESSION_KIND__STRING, literal->super.location);
    expression->value = literal->value;
    return expression;
}

typedef struct Parsed_Substract_Expression {
    Parsed_Binary_Expression super;
} Parsed_Substract_Expression;

Parsed_Substract_Expression* Parsed_Substract_Expression__create(Parsed_Expression* left_expression, Parsed_Expression* right_expression) {
    return (Parsed_Substract_Expression*) Parsed_Binary_Expression__create(PARSED_EXPRESSION_KIND__SUBSTRACT, left_expression, right_expression);
}

typedef struct Parsed_Symbol_Expression {
    Parsed_Expression super;
    Token* name;
} Parsed_Symbol_Expression;

Parsed_Symbol_Expression* Parsed_Symbol_Expression__create(Token* name) {
    Parsed_Symbol_Expression* expression = (Parsed_Symbol_Expression*) Parsed_Expression__create(sizeof(Parsed_Symbol_Expression), PARSED_EXPRESSION_KIND__SYMBOL, name->location);
    expression->name = name;
    return expression;
}

typedef enum Parsed_Statement_Kind {
    PARSED_STATEMENT_KIND__ASSIGNMENT,
    PARSED_STATEMENT_KIND__BLOCK,
    PARSED_STATEMENT_KIND__BREAK,
    PARSED_STATEMENT_KIND__ENUM,
    PARSED_STATEMENT_KIND__EXPRESSION,
    PARSED_STATEMENT_KIND__FUNCTION,
    PARSED_STATEMENT_KIND__IF,
    PARSED_STATEMENT_KIND__RETURN,
    PARSED_STATEMENT_KIND__STRUCT,
    PARSED_STATEMENT_KIND__VARIABLE,
    PARSED_STATEMENT_KIND__WHILE,
} Parsed_Statement_Kind;

typedef struct Parsed_Statement {
    Parsed_Statement_Kind kind;
    Source_Location* location;
    struct Parsed_Statement* next_statement;
} Parsed_Statement;

void* Parsed_Statement__create(size_t size, Parsed_Statement_Kind kind, Source_Location* location) {
    Parsed_Statement* statement = malloc(size);
    statement->kind = kind;
    statement->location = location;
    statement->next_statement = null;
    return statement;
}

typedef struct Parsed_Named_Statement {
    Parsed_Statement super;
    Token* name;
} Parsed_Named_Statement;

void* Parsed_Named_Statement__create(size_t size, Parsed_Statement_Kind kind, Source_Location* location, Token* name) {
    Parsed_Named_Statement* statement = Parsed_Statement__create(size, kind, location);
    statement->name = name;
    return statement;
}

typedef struct Parsed_Assignment_Statement {
    Parsed_Statement super;
    Parsed_Expression* left_expression;
    Parsed_Expression* right_expression;
} Parsed_Assignment_Statement;

Parsed_Assignment_Statement* Parsed_Assignment_Statement__create(Parsed_Expression* left_expression, Parsed_Expression* right_expression) {
    Parsed_Assignment_Statement* statement = Parsed_Statement__create(sizeof(Parsed_Assignment_Statement), PARSED_STATEMENT_KIND__ASSIGNMENT, left_expression->location);
    statement->left_expression = left_expression;
    statement->right_expression = right_expression;
    return statement;
}

typedef struct Parsed_Block_Statement {
    Parsed_Statement super;
    Parsed_Statements* statements;
} Parsed_Block_Statement;

Parsed_Block_Statement* Parsed_Block_Statement__create(Source_Location* location, Parsed_Statements* statements) {
    Parsed_Block_Statement* statement = Parsed_Statement__create(sizeof(Parsed_Block_Statement), PARSED_STATEMENT_KIND__BLOCK, location);
    statement->statements = statements;
    return statement;
}

typedef struct Parsed_Break_Statement {
    Parsed_Statement super;
} Parsed_Break_Statement;

Parsed_Statement* Parsed_Break_Statement__create(Source_Location* location) {
    return (Parsed_Statement*) Parsed_Statement__create(sizeof(Parsed_Break_Statement), PARSED_STATEMENT_KIND__BREAK, location);
}

typedef struct Parsed_Enum_Member {
    Token* name;
    struct Parsed_Enum_Member* next_member;
} Parsed_Enum_Member;

Parsed_Enum_Member* Parsed_Enum_Member__create(Token* name) {
    Parsed_Enum_Member* member = malloc(sizeof(Parsed_Enum_Member));
    member->name = name;
    member->next_member = null;
    return member;
}

typedef struct Parsed_Enum_Statement {
    Parsed_Named_Statement super;
    Parsed_Enum_Member* first_member;
} Parsed_Enum_Statement;

Parsed_Enum_Statement* Parsed_Enum_Statement__create(Source_Location* location, Token* name) {
    Parsed_Enum_Statement* statement = Parsed_Named_Statement__create(sizeof(Parsed_Enum_Statement), PARSED_STATEMENT_KIND__ENUM, location, name);
    statement->first_member = null;
    return statement;
}

typedef struct Parsed_Expression_Statement {
    Parsed_Statement super;
    Parsed_Expression* expression;
} Parsed_Expression_Statement;

Parsed_Expression_Statement* Parsed_Expression_Statement__create(Parsed_Expression* expression) {
    Parsed_Expression_Statement* statement = Parsed_Statement__create(sizeof(Parsed_Expression_Statement), PARSED_STATEMENT_KIND__EXPRESSION, expression->location);
    statement->expression = expression;
    return statement;
}

typedef struct Parsed_Function_Parameter {
    Token* name;
    Parsed_Type* type;
    struct Parsed_Function_Parameter* next_parameter;
} Parsed_Function_Parameter;

Parsed_Function_Parameter* Parsed_Function_Parameter__create(Token* name, Parsed_Type* type) {
    Parsed_Function_Parameter* parameter = malloc(sizeof(Parsed_Function_Parameter));
    parameter->name = name;
    parameter->type = type;
    parameter->next_parameter = null;
    return parameter;
}

typedef struct Parsed_Function_Statement {
    Parsed_Named_Statement super;
    Parsed_Function_Parameter* first_parameter;
    Parsed_Type* return_type;
    Parsed_Statements* statements;
    bool is_external;
} Parsed_Function_Statement;

Parsed_Statement* Parsed_Function_Statement__create(Source_Location* location, Token* name, Parsed_Function_Parameter* first_parameter, Parsed_Type* resturn_type, Parsed_Statements* statements, bool is_external) {
    Parsed_Function_Statement* statement = Parsed_Named_Statement__create(sizeof(Parsed_Function_Statement), PARSED_STATEMENT_KIND__FUNCTION, location, name);
    statement->first_parameter = first_parameter;
    statement->return_type = resturn_type;
    statement->statements = statements;
    statement->is_external = is_external;
    return (Parsed_Statement*) statement;
}

typedef struct Parsed_Function_Type_Parameter {
    Parsed_Type* type;
    struct Parsed_Function_Type_Parameter* next_parameter;
} Parsed_Function_Type_Parameter;

Parsed_Function_Type_Parameter* Parsed_Function_Type_Parameter__create(Parsed_Type* type) {
    Parsed_Function_Type_Parameter* parameter = (Parsed_Function_Type_Parameter*) malloc(sizeof(Parsed_Function_Type_Parameter));
    parameter->type = type;
    parameter->next_parameter = null;
    return parameter;
}

typedef struct Parsed_Function_Type_Statement {
    Parsed_Named_Statement super;
    Parsed_Function_Type_Parameter* first_parameter;
    Parsed_Type* return_type;
} Parsed_Function_Type_Statement;

Parsed_Statement* Parsed_Function_Type_Statement__create(Source_Location* location, Token* name, Parsed_Function_Type_Parameter* first_parameter, Parsed_Type* resturn_type) {
    Parsed_Function_Type_Statement* statement = Parsed_Named_Statement__create(sizeof(Parsed_Function_Type_Statement), PARSED_STATEMENT_KIND__FUNCTION, location, name);
    statement->first_parameter = first_parameter;
    statement->return_type = resturn_type;
    return (Parsed_Statement*) statement;
}

typedef struct Parsed_If_Statement {
    Parsed_Statement super;
    Parsed_Expression* condition_expression;
    Parsed_Statement* true_statement;
    Parsed_Statement* false_statement;
} Parsed_If_Statement;

Parsed_Statement* Parsed_If_Statement__create(Source_Location* location, Parsed_Expression* condition_expression, Parsed_Statement* true_statement, Parsed_Statement* false_statement) {
    Parsed_If_Statement* statement = Parsed_Statement__create(sizeof(Parsed_If_Statement), PARSED_STATEMENT_KIND__IF, location);
    statement->condition_expression = condition_expression;
    statement->true_statement = true_statement;
    statement->false_statement = false_statement;
    return (Parsed_Statement*) statement;
}

typedef struct Parsed_Return_Statement {
    Parsed_Statement super;
    Parsed_Expression* expression;
} Parsed_Return_Statement;

Parsed_Statement* Parsed_Return_Statement__create(Source_Location* location, Parsed_Expression* expression) {
    Parsed_Return_Statement* statement = Parsed_Statement__create(sizeof(Parsed_Return_Statement), PARSED_STATEMENT_KIND__RETURN, location);
    statement->expression = expression;
    return (Parsed_Statement*) statement;
}

typedef struct Parsed_Struct_Member {
    Token* name;
    Parsed_Type* type;
    struct Parsed_Struct_Member* next_member;
} Parsed_Struct_Member;

Parsed_Struct_Member* Parsed_Struct_Member__create(Token* name, Parsed_Type* type) {
    Parsed_Struct_Member* member = malloc(sizeof(Parsed_Struct_Member));
    member->name = name;
    member->type = type;
    member->next_member = null;
    return member;
}

typedef struct Parsed_Struct_Statement {
    Parsed_Named_Statement super;
    Parsed_Struct_Member* first_member;
    bool is_opaque;
} Parsed_Struct_Statement;

Parsed_Struct_Statement* Parsed_Struct_Statement__create(Source_Location* location, Token* name) {
    Parsed_Struct_Statement* statement = Parsed_Named_Statement__create(sizeof(Parsed_Struct_Statement), PARSED_STATEMENT_KIND__STRUCT, location, name);
    statement->first_member = null;
    statement->is_opaque = false;
    return statement;
}

typedef struct Parsed_Variable_Statement {
    Parsed_Named_Statement super;
    Parsed_Type* type;
    Parsed_Expression* expression;
    bool is_external;
} Parsed_Variable_Statement;

Parsed_Variable_Statement* Parsed_Variable_Statement__create(Source_Location* location, Token* name, Parsed_Type* type, bool is_external) {
    Parsed_Variable_Statement* statement = Parsed_Named_Statement__create(sizeof(Parsed_Variable_Statement), PARSED_STATEMENT_KIND__VARIABLE, location, name);
    statement->type = type;
    statement->is_external = is_external;
    return statement;
}

typedef struct Parsed_While_Statement {
    Parsed_Statement super;
    Parsed_Expression* condition_expression;
    Parsed_Statement* body_statement;
} Parsed_While_Statement;

Parsed_Statement* Parsed_While_Statement__create(Source_Location* location, Parsed_Expression* condition_expression, Parsed_Statement* body_statement) {
    Parsed_While_Statement* statement = Parsed_Statement__create(sizeof(Parsed_While_Statement), PARSED_STATEMENT_KIND__WHILE, location);
    statement->condition_expression = condition_expression;
    statement->body_statement = body_statement;
    return (Parsed_Statement*) statement;
}

typedef struct Parsed_Statements {
    Parsed_Statement* first_statement;
    Parsed_Statement* last_statement;
    bool has_globals;
} Parsed_Statements;

Parsed_Statements* Parsed_Statements__create(bool has_globals) {
    Parsed_Statements* statements = malloc(sizeof(Parsed_Statements));
    statements->first_statement = null;
    statements->last_statement = null;
    statements->has_globals = has_globals;
    return statements;
}

void Parsed_Statements__append(Parsed_Statements* self, Parsed_Statement* statement) {
    if (self->first_statement == null) {
        self->first_statement = statement;
    } else {
        self->last_statement->next_statement = statement;
    }
    self->last_statement = statement;
}

Parsed_Source* Parsed_Compilation_Unit__create() {
    Parsed_Source* compilation_unit = malloc(sizeof(Parsed_Source));
    compilation_unit->statements = Parsed_Statements__create(true);
    return compilation_unit;
}

// Parser

typedef struct Parser {
    Scanner* scanner;
    Parsed_Source* compilation_unit;
    uint16_t current_identation;
} Parser;

void Parser__panic(Parser* self, String* message) {
    Token__panic(self->scanner->current_token, message);
}

void Parser__warning(Parser* self, String* message) {
    Token__warning(self->scanner->current_token, message);
}

Token* Parser__peek_token(Parser* self, uint8_t offset) {
    return Scanner__peek_token(self->scanner, offset);
}

typedef bool Token_Is_Function(Token*);

bool Parser__matches_three(Parser* self, Token_Is_Function* first_is, bool first_required, Token_Is_Function* second_is, bool second_required, Token_Is_Function* third_is) {
    size_t peek_offset = 0;
    if (first_is(Parser__peek_token(self, peek_offset))) {
        peek_offset = peek_offset + 1;
    } else if (first_required) {
        return false;
    }
    if (second_is != null) {
        if (second_is(Parser__peek_token(self, peek_offset))) {
            peek_offset = peek_offset + 1;
        } else if (second_required) {
            return false;
        }
    }
    if (third_is != null) {
        return third_is(Parser__peek_token(self, peek_offset));
    }
    return true;
}

bool Parser__matches_two(Parser* self, Token_Is_Function* first_is, bool first_required, Token_Is_Function* second_is) {
    return Parser__matches_three(self, first_is, first_required, second_is, true, null);
}

bool Parser__matches_one(Parser* self, Token_Is_Function* first_is) {
    return Parser__matches_two(self, first_is, true, null);
}

Token* Parser__consume_token(Parser* self, Token_Is_Function* check) {
    if (Parser__matches_one(self, check)) {
        Token* token = self->scanner->current_token;
        Scanner__next_token(self->scanner);
        return token;
    }
    Parser__panic(self, String__create_from("Unexpected token"));
    return null;
}

void Parser__consume_comment(Parser* self) {
    Parser__consume_token(self, Token__is_comment);
}

void Parser__consume_space(Parser* self, uint16_t count) {
    if (Parser__matches_one(self, Token__is_space)) {
        Space_Token* token = (Space_Token*) Parser__consume_token(self, Token__is_space);
        if (token->count != count) {
            String* message = String__append_cstring(String__append_int16_t(String__append_cstring(String__append_int16_t(String__create_from("Consumed "), token->count), " spaces where "), count), " were expected");
            Token__warning((Token*) token, message);
            String__delete(message);
        }
    } else if (count > 0) {
        String* message = String__append_cstring(String__append_int16_t(String__append_cstring(String__append_int16_t(String__create_from("Consumed "), 0), " spaces where "), count), " were expected");
        Parser__warning(self, message);
        String__delete(message);
    }
}

void Parser__consume_end_of_line(Parser* self) {
    if (Parser__matches_two(self, Token__is_space, false, Token__is_comment)) {
        Parser__consume_space(self, 1);
        Parser__consume_comment(self);
    } else {
        Parser__consume_space(self, 0);
    }
    Token* token = Parser__consume_token(self, Token__is_end_of_line);
    if (Token__is_end_of_file(token)) {
        Token__warning(token, String__create_from("Unexpected end of file"));
    }
}

bool Parser__consume_empty_line(Parser* self) {
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
    if (Parser__matches_two(self, Token__is_space, false, Token__is_hash)) {
        // Preprocessor directives are ignored and treated as empty lines
        Parser__consume_space(self, 0);
        Parser__consume_token(self, Token__is_hash);
        while (!Parser__matches_one(self, Token__is_end_of_line)) {
            Parser__consume_token(self, Token__is_anything);
        }
        Parser__consume_token(self, Token__is_end_of_line);
        return true;
    }
    return false;
}

Parsed_Expression* Parser__parse_expression(Parser* self);
Parsed_Type* Parser__parse_type(Parser* self);

// primary_expression
//      | "false"
//      | "null"
//      | "true"
//      | CHARACTER
//      | IDENTIFIER
//      | INTEGER
//      | STRING
Parsed_Expression* Parser__parse_primary_expression(Parser* self) {
    if (Parser__matches_one(self, Token__is_true)) {
        return (Parsed_Expression*) Parsed_Bool_Expression__create(Parser__consume_token(self, Token__is_true), true);
    }
    if (Parser__matches_one(self, Token__is_null)) {
        return (Parsed_Expression*) Parsed_Null_Expression__create(Parser__consume_token(self, Token__is_null));
    }
    if (Parser__matches_one(self, Token__is_false)) {
        return (Parsed_Expression*) Parsed_Bool_Expression__create(Parser__consume_token(self, Token__is_false), false);
    }
    if (Parser__matches_one(self, Token__is_identifier)) {
        return (Parsed_Expression*) Parsed_Symbol_Expression__create(Parser__consume_token(self, Token__is_identifier));
    }
    if (Parser__matches_one(self, Token__is_integer)) {
        return (Parsed_Expression*) Parsed_Integer_Expression__create((Integer_Token*) Parser__consume_token(self, Token__is_integer));
    }
    if (Parser__matches_one(self, Token__is_character)) {
        return (Parsed_Expression*) Parsed_Character_Expression__create((Character_Token*) Parser__consume_token(self, Token__is_character));
    }
    if (Parser__matches_one(self, Token__is_string)) {
        return (Parsed_Expression*) Parsed_String_Expression__create((String_Token*) Parser__consume_token(self, Token__is_string));
    }
    if (Parser__matches_one(self, Token__is_opening_paren)) {
        Source_Location* location = Parser__consume_token(self, Token__is_opening_paren)->location;
        Parser__consume_space(self, 0);
        Parsed_Expression* expression = Parser__parse_expression(self);
        Parser__consume_space(self, 0);
        Parser__consume_token(self, Token__is_closing_paren);
        return (Parsed_Expression*) Parsed_Group_Expression__create(location, expression);
    }
    Parser__panic(self, String__create_from("Unsupported primary expression"));
    return null;
}

// access_expression
//      | primary_expression ( "." IDENTIFIER | "->" IDENTIFIER | "(" ( expression ( "," expression )*)? ")" | "[" expression "]" )*
Parsed_Expression* Parser__parse_access_expression(Parser* self) {
    Parsed_Expression* expression = Parser__parse_primary_expression(self);
    while (true) {
        Parsed_Expression* old_expression = expression;
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
            expression = (Parsed_Expression*) Parsed_Member_Access_Expression__create(expression, name);
        }
        if (Parser__matches_two(self, Token__is_space, false, Token__is_opening_paren)) {
            Parser__consume_space(self, 0);
            Parser__consume_token(self, Token__is_opening_paren);
            Parser__consume_space(self, 0);
            if (expression->kind == PARSED_EXPRESSION_KIND__SYMBOL && String__equals_cstring(((Parsed_Symbol_Expression*) expression)->name->lexeme, "sizeof")) {
                Parsed_Type* type = Parser__parse_type(self);
                expression = (Parsed_Expression*) Parsed_Sizeof_Expression__create(expression->location, type);
            } else {
                Parsed_Call_Expression* call_expression = Parsed_Call_Expression__create(expression);
                if (!Parser__matches_one(self, Token__is_closing_paren)) {
                    Parsed_Call_Argument* last_argument = Parsed_Call_Argument__create(Parser__parse_expression(self));
                    call_expression->first_argument = last_argument;
                    Parser__consume_space(self, 0);
                    while (Parser__matches_one(self, Token__is_comma)) {
                        Parser__consume_token(self, Token__is_comma);
                        Parser__consume_space(self, 1);
                        Parsed_Call_Argument* argument = Parsed_Call_Argument__create(Parser__parse_expression(self));
                        last_argument->next_argument = argument;
                        last_argument = argument;
                        Parser__consume_space(self, 0);
                    }
                }
                expression = (Parsed_Expression*) call_expression;
            }
            Parser__consume_token(self, Token__is_closing_paren);
        }
        if (Parser__matches_two(self, Token__is_space, false, Token__is_opening_bracket)) {
            Parser__consume_space(self, 0);
            Parser__consume_token(self, Token__is_opening_bracket);
            Parser__consume_space(self, 0);
            Parsed_Expression* index_expression = Parser__parse_expression(self);
            Parser__consume_space(self, 0);
            Parser__consume_token(self, Token__is_closing_bracket);
            expression = (Parsed_Expression*) Parsed_Array_Access_Expression__create(expression, index_expression);
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
//      | "&" unary_expression
//      | "(" type ")" unary_expression
//      | "sizeof" "(" type ")"
//      | access_expression
Parsed_Expression* Parser__parse_unary_expression(Parser* self) {
    if (Parser__matches_one(self, Token__is_minus)) {
        Source_Location* location = Parser__consume_token(self, Token__is_minus)->location;
        Parser__consume_space(self, 0);
        Parsed_Expression* expression = Parser__parse_unary_expression(self);
        return (Parsed_Expression*) Parsed_Minus_Expression__create(location, expression);
    }
    if (Parser__matches_one(self, Token__is_exclamation_mark)) {
        Source_Location* location = Parser__consume_token(self, Token__is_exclamation_mark)->location;
        Parser__consume_space(self, 0);
        Parsed_Expression* expression = Parser__parse_unary_expression(self);
        return (Parsed_Expression*) Parsed_Not_Expression__create(location, expression);
    }
    if (Parser__matches_one(self, Token__is_ampersand)) {
        Source_Location* location = Parser__consume_token(self, Token__is_ampersand)->location;
        Parser__consume_space(self, 0);
        Parsed_Expression* expression = Parser__parse_unary_expression(self);
        return (Parsed_Expression*) Parsed_Address_Of_Expression__create(location, expression);
    }
    if (Parser__matches_three(self, Token__is_opening_paren, true, Token__is_space, false, Token__is_identifier)) {
        uint16_t peek_offset = 1;
        if (Token__is_space(Parser__peek_token(self, peek_offset))) {
            peek_offset = peek_offset + 1;
        }
        if (Token__is_identifier(Parser__peek_token(self, peek_offset))) {
            peek_offset = peek_offset + 1;
            if (Token__is_space(Parser__peek_token(self, peek_offset))) {
                peek_offset = peek_offset + 1;
            }
            while (Token__is_asterisk(Parser__peek_token(self, peek_offset))) {
                peek_offset = peek_offset + 1;
                if (Token__is_space(Parser__peek_token(self, peek_offset))) {
                    peek_offset = peek_offset + 1;
                }
            }
            if (Token__is_closing_paren(Parser__peek_token(self, peek_offset))) {
                peek_offset = peek_offset + 1;
                if (Token__is_space(Parser__peek_token(self, peek_offset))) {
                    peek_offset = peek_offset + 1;
                }
                Source_Location* location = Parser__consume_token(self, Token__is_opening_paren)->location;
                Parser__consume_space(self, 0);
                Parsed_Type* type = Parser__parse_type(self);
                Parser__consume_space(self, 0);
                Parser__consume_token(self, Token__is_closing_paren);
                Parser__consume_space(self, 1);
                Parsed_Expression* expression = Parser__parse_unary_expression(self);
                return (Parsed_Expression*) Parsed_Cast_Expression__create(location, expression, type);
            }
        }
    }
    return Parser__parse_access_expression(self);
}

bool Token__is_mutliplication(Token* self) {
    return Token__is_asterisk(self) || Token__is_slash(self) || Token__is_percent(self);
}

// multiplication
//      | unary_expression ( ( "*" | "/" | "%" ) unary_expression )*
Parsed_Expression* Parser__parse_multiplication_expression(Parser* self) {
    Parsed_Expression* expression = Parser__parse_unary_expression(self);
    while (Parser__matches_two(self, Token__is_space, false, Token__is_mutliplication)) {
        Parser__consume_space(self, 1);
        if (Parser__matches_one(self, Token__is_asterisk)) {
            Parser__consume_token(self, Token__is_asterisk);
            Parser__consume_space(self, 1);
            Parsed_Expression* right_expression = Parser__parse_unary_expression(self);
            expression = (Parsed_Expression*) Parsed_Multiply_Expression__create(expression, right_expression);
        } else if (Parser__matches_one(self, Token__is_slash)) {
            Parser__consume_token(self, Token__is_slash);
            Parser__consume_space(self, 1);
            Parsed_Expression* right_expression = Parser__parse_unary_expression(self);
            expression = (Parsed_Expression*) Parsed_Divide_Expression__create(expression, right_expression);
        } else {
            Parser__consume_token(self, Token__is_percent);
            Parser__consume_space(self, 1);
            Parsed_Expression* right_expression = Parser__parse_unary_expression(self);
            expression = (Parsed_Expression*) Parsed_Modulo_Expression__create(expression, right_expression);
        }
    }
    return expression;
}

bool Token__is_addition(Token* self) {
    return Token__is_plus(self) || Token__is_minus(self);
}

// addition
//      | multiplication ( ( "+" | "-" ) multiplication )*
Parsed_Expression* Parser__parse_addition_expression(Parser* self) {
    Parsed_Expression* expression = Parser__parse_multiplication_expression(self);
    while (Parser__matches_two(self, Token__is_space, false, Token__is_addition)) {
        Parser__consume_space(self, 1);
        if (Parser__matches_one(self, Token__is_plus)) {
            Parser__consume_token(self, Token__is_plus);
            Parser__consume_space(self, 1);
            Parsed_Expression* right_expression = Parser__parse_multiplication_expression(self);
            expression = (Parsed_Expression*) Parsed_Add_Expression__create(expression, right_expression);
        } else {
            Parser__consume_token(self, Token__is_minus);
            Parser__consume_space(self, 1);
            Parsed_Expression* right_expression = Parser__parse_multiplication_expression(self);
            expression = (Parsed_Expression*) Parsed_Substract_Expression__create(expression, right_expression);
        }
    }
    return expression;
}

// comparison
//      | addition ( ( "<=" | "<" | ">" | ">=") addition )*
Parsed_Expression* Parser__parse_comparison_expression(Parser* self) {
    Parsed_Expression* expression = Parser__parse_addition_expression(self);
    if (Parser__matches_two(self, Token__is_space, false, Token__is_less_than)) {
        Parser__consume_space(self, 1);
        Parser__consume_token(self, Token__is_less_than);
        if (Parser__matches_one(self, Token__is_equals)) {
            Parser__consume_token(self, Token__is_equals);
            Parser__consume_space(self, 1);
            Parsed_Expression* right_expression = Parser__parse_addition_expression(self);
            expression = (Parsed_Expression*) Parsed_Less_Or_Equals_Expression__create(expression, right_expression);
        } else {
            Parser__consume_space(self, 1);
            Parsed_Expression* right_expression = Parser__parse_addition_expression(self);
            expression = (Parsed_Expression*) Parsed_Less_Expression__create(expression, right_expression);
        }
    } else if (Parser__matches_two(self, Token__is_space, false, Token__is_greater_than)) {
        Parser__consume_space(self, 1);
        Parser__consume_token(self, Token__is_greater_than);
        if (Parser__matches_one(self, Token__is_equals)) {
            Parser__consume_token(self, Token__is_equals);
            Parser__consume_space(self, 1);
            Parsed_Expression* right_expression = Parser__parse_addition_expression(self);
            expression = (Parsed_Expression*) Parsed_Greater_Or_Equals_Expression__create(expression, right_expression);
        } else {
            Parser__consume_space(self, 1);
            Parsed_Expression* right_expression = Parser__parse_addition_expression(self);
            expression = (Parsed_Expression*) Parsed_Greater_Expression__create(expression, right_expression);
        }
    }
    return expression;
}

// equality
//      | comparison ( ( "==" | "!=" ) comparison )*
Parsed_Expression* Parser__parse_equality_expression(Parser* self) {
    Parsed_Expression* expression = Parser__parse_comparison_expression(self);
    if (Parser__matches_three(self, Token__is_space, false, Token__is_equals, true, Token__is_equals)) {
        Parser__consume_space(self, 1);
        Parser__consume_token(self, Token__is_equals);
        Parser__consume_token(self, Token__is_equals);
        Parser__consume_space(self, 1);
        Parsed_Expression* right_expression = Parser__parse_comparison_expression(self);
        expression = (Parsed_Expression*) Parsed_Equals_Expression__create(expression, right_expression);
    } else if (Parser__matches_three(self, Token__is_space, false, Token__is_exclamation_mark, true, Token__is_equals)) {
        Parser__consume_space(self, 1);
        Parser__consume_token(self, Token__is_exclamation_mark);
        Parser__consume_token(self, Token__is_equals);
        Parser__consume_space(self, 1);
        Parsed_Expression* right_expression = Parser__parse_comparison_expression(self);
        expression = (Parsed_Expression*) Parsed_Not_Equals_Expression__create(expression, right_expression);
    }
    return expression;
}

// logic_and
//      | equality ( "&&" equality )*
Parsed_Expression* Parser__parse_logic_and_expression(Parser* self) {
    Parsed_Expression* expression = Parser__parse_equality_expression(self);
    while (Parser__matches_three(self, Token__is_space, false, Token__is_ampersand, true, Token__is_ampersand)) {
        Parser__consume_space(self, 1);
        Parser__consume_token(self, Token__is_ampersand);
        Parser__consume_token(self, Token__is_ampersand);
        Parser__consume_space(self, 1);
        Parsed_Expression* right_expression = Parser__parse_equality_expression(self);
        expression = (Parsed_Expression*) Parsed_Logic_And_Expression__create(expression, right_expression);
    }
    return expression;
}

// logic_or
//      | logic_and ( "||" logic_and )*
Parsed_Expression* Parser__parse_logic_or_expression(Parser* self) {
    Parsed_Expression* expression = Parser__parse_logic_and_expression(self);
    while (Parser__matches_three(self, Token__is_space, false, Token__is_vertical_bar, true, Token__is_vertical_bar)) {
        Parser__consume_space(self, 1);
        Parser__consume_token(self, Token__is_vertical_bar);
        Parser__consume_token(self, Token__is_vertical_bar);
        Parser__consume_space(self, 1);
        Parsed_Expression* right_expression = Parser__parse_logic_and_expression(self);
        expression = (Parsed_Expression*) Parsed_Logic_Or_Expression__create(expression, right_expression);
    }
    return expression;
}

// expression
//      | logic_or
Parsed_Expression* Parser__parse_expression(Parser* self) {
    return Parser__parse_logic_or_expression(self);
}

// struct
//      | "typedef" "struct" IDENTIFIER ( "{" ( type "*"? IDENTIFIER ";" )* "}" )? IDENTIFIER ";"
Parsed_Statement* Parser__parse_struct(Parser* self) {
    Source_Location* location = Parser__consume_token(self, Token__is_typedef)->location;
    Parser__consume_space(self, 1);
    Parser__consume_token(self, Token__is_struct);
    Parser__consume_space(self, 1);
    Token* local_name = Parser__consume_token(self, Token__is_identifier);
    Parsed_Struct_Statement* struct_statement = Parsed_Struct_Statement__create(location, local_name);
    Parser__consume_space(self, 1);
    if (Parser__matches_one(self, Token__is_identifier)) {
        struct_statement->is_opaque = true;
    } else {
        Parsed_Struct_Member* last_member = null;
        Parser__consume_token(self, Token__is_opening_brace);
        Parser__consume_end_of_line(self);
        while (!Parser__matches_two(self, Token__is_space, false, Token__is_closing_brace)) {
            Parser__consume_space(self, (self->current_identation + 1) * 4);
            Parsed_Type* type = Parser__parse_type(self);
            Parser__consume_space(self, 1);
            Token* name = Parser__consume_token(self, Token__is_identifier);
            Parser__consume_space(self, 0);
            Parser__consume_token(self, Token__is_semicolon);
            Parser__consume_end_of_line(self);
            Parsed_Struct_Member* member = Parsed_Struct_Member__create(name, type);
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
    Token* final_name = Parser__consume_token(self, Token__is_identifier);
    if (!String__equals_string(final_name->lexeme, local_name->lexeme)) {
        Token__panic(final_name, String__append_string(String__create_from("Final struct name doesn't match the local name: "), local_name->lexeme));
    }
    Parser__consume_space(self, 0);
    Parser__consume_token(self, Token__is_semicolon);
    return (Parsed_Statement*) struct_statement;
}

// enum
//      | "typedef" "enum" IDENTIFIER "{" ( IDENTIFIER "," )* "}" IDENTIFIER ";"
Parsed_Statement* Parser__parse_enum(Parser* self) {
    Source_Location* location = Parser__consume_token(self, Token__is_typedef)->location;
    Parser__consume_space(self, 1);
    Parser__consume_token(self, Token__is_enum);
    Parser__consume_space(self, 1);
    Token* local_name = Parser__consume_token(self, Token__is_identifier);
    Parsed_Enum_Statement* enum_statement = Parsed_Enum_Statement__create(location, local_name);
    Parser__consume_space(self, 1);
    Parser__consume_token(self, Token__is_opening_brace);
    Parser__consume_end_of_line(self);
    Parsed_Enum_Member* last_member = null;
    while (!Parser__matches_two(self, Token__is_space, false, Token__is_closing_brace)) {
        Parser__consume_space(self, (self->current_identation + 1) * 4);
        Token* name = Parser__consume_token(self, Token__is_identifier);
        Parser__consume_space(self, 0);
        Parser__consume_token(self, Token__is_comma);
        Parser__consume_end_of_line(self);
        Parsed_Enum_Member* member = Parsed_Enum_Member__create(name);
        if (last_member == null) {
            enum_statement->first_member = member;
            last_member = member;
        } else {
            last_member->next_member = member;
            last_member = member;
        }
    }
    Parser__consume_space(self, 0);
    Parser__consume_token(self, Token__is_closing_brace);
    Parser__consume_space(self, 1);
    Token* final_name = Parser__consume_token(self, Token__is_identifier);
    if (!String__equals_string(final_name->lexeme, local_name->lexeme)) {
        Token__panic(final_name, String__append_string(String__create_from("Final enum name doesn't match the local name: "), local_name->lexeme));
    }
    Parser__consume_space(self, 0);
    Parser__consume_token(self, Token__is_semicolon);
    return (Parsed_Statement*) enum_statement;
}

// type
//      | "const"? "struct"? IDENTIFIER "*"*
Parsed_Type* Parser__parse_type(Parser* self) {
    Token* const_token = null;
    if (Parser__matches_one(self, Token__is_const)) {
        const_token = Parser__consume_token(self, Token__is_const);
        Parser__consume_space(self, 1);
    }
    Token* struct_token = null;
    if (Parser__matches_one(self, Token__is_struct)) {
        struct_token = Parser__consume_token(self, Token__is_struct);
        Parser__consume_space(self, 1);
    }
    Token* name = Parser__consume_token(self, Token__is_identifier);
    Parsed_Type* type = Parsed_Named_Type__create(name);
    if (struct_token != null) {
        type = Parsed_Struct_Type__create(struct_token->location, type);
    }
    while (Parser__matches_two(self, Token__is_space, false, Token__is_asterisk)) {
        Parser__consume_space(self, 0);
        Parser__consume_token(self, Token__is_asterisk);
        type = Parsed_Pointer_Type__create(type);
    }
    if (const_token) {
        type = Parsed_Const_Type__create(const_token->location, type);
    }
    return type;
}

// type_alias
//      | "typedef" type IDENTIFIER "(" ( type ( "," type )* )? ")" ";"
Parsed_Statement* Parser__parse_type_alias(Parser* self) {
    Source_Location* location = Parser__consume_token(self, Token__is_typedef)->location;
    Parser__consume_space(self, 1);
    Parsed_Type* return_type = Parser__parse_type(self);
    Parser__consume_space(self, 1);
    Token* name = Parser__consume_token(self, Token__is_identifier);
    Parser__consume_space(self, 0);
    Parser__consume_token(self, Token__is_opening_paren);
    Parsed_Function_Type_Parameter* first_parameter = null;
    if (!Parser__matches_two(self, Token__is_space, false, Token__is_closing_paren)) {
        Parser__consume_space(self, 0);
        first_parameter = Parsed_Function_Type_Parameter__create(Parser__parse_type(self));
        Parsed_Function_Type_Parameter* last_parameter = first_parameter;
        while (Parser__matches_two(self, Token__is_space, false, Token__is_comma)) {
            Parser__consume_space(self, 0);
            Parser__consume_token(self, Token__is_comma);
            Parser__consume_space(self, 1);
            Parsed_Function_Type_Parameter* parameter = Parsed_Function_Type_Parameter__create(Parser__parse_type(self));
            last_parameter->next_parameter = parameter;
            last_parameter = parameter;
        }
    }
    Parser__consume_space(self, 0);
    Parser__consume_token(self, Token__is_closing_paren);
    Parser__consume_space(self, 0);
    Parser__consume_token(self, Token__is_semicolon);
    return (Parsed_Statement*) Parsed_Function_Type_Statement__create(location, name, first_parameter, return_type);
}

// variable
//      | "extern"? type IDENTIFIER ( "=" expression )? ";"
Parsed_Statement* Parser__parse_variable(Parser* self) {
    bool is_external;
    Source_Location* location;
    if (Parser__matches_one(self, Token__is_extern)) {
        is_external = true;
        location = Parser__consume_token(self, Token__is_extern)->location;
        Parser__consume_space(self, 1);
    } else {
        is_external = false;
        location = Parser__peek_token(self, 0)->location;
    }
    Parsed_Type* type = Parser__parse_type(self);
    Parser__consume_space(self, 1);
    Token* name = Parser__consume_token(self, Token__is_identifier);
    Parsed_Variable_Statement* variable_statement = Parsed_Variable_Statement__create(location, name, type, is_external);
    if (Parser__matches_two(self, Token__is_space, false, Token__is_equals)) {
        Parser__consume_space(self, 1);
        Parser__consume_token(self, Token__is_equals);
        Parser__consume_space(self, 1);
        variable_statement->expression = Parser__parse_expression(self);
    }
    Parser__consume_space(self, 0);
    Parser__consume_token(self, Token__is_semicolon);
    return (Parsed_Statement*) variable_statement;
}

Parsed_Function_Parameter* Parser__parse_function_parameter(Parser* self) {
    Parsed_Type* type = Parser__parse_type(self);
    Parser__consume_space(self, 1);
    Token* name = Parser__consume_token(self, Token__is_identifier);
    return Parsed_Function_Parameter__create(name, type);
}

Parsed_Function_Parameter* Parser__parse_function_parameters(Parser* self) {
    Parsed_Function_Parameter* first_parameter = null;
    if (!Parser__matches_two(self, Token__is_space, false, Token__is_closing_paren)) {
        Parser__consume_space(self, 0);
        first_parameter = Parser__parse_function_parameter(self);
        Parsed_Function_Parameter* last_parameter = first_parameter;
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

void Parser__parse_statements(Parser* self, Parsed_Statements* statements);

// block
//      | "{" statements "}"
Parsed_Block_Statement* Parser__parse_block_statement(Parser* self) {
    Source_Location* location = Parser__consume_token(self, Token__is_opening_brace)->location;
    Parser__consume_end_of_line(self);
    Parsed_Statements* statements = Parsed_Statements__create(false);
    self->current_identation = self->current_identation + 1;
    Parser__parse_statements(self, statements);
    self->current_identation = self->current_identation - 1;
    Parser__consume_space(self, self->current_identation * 4);
    Parser__consume_token(self, Token__is_closing_brace);
    return Parsed_Block_Statement__create(location, statements);
}

// function
//      | "extern"? type IDENTIFIER "(" function_parameter* ")" ( "{" statements "}" | ";" )
Parsed_Statement* Parser__parse_function(Parser* self) {
    bool is_external;
    Source_Location* location;
    if (Parser__matches_one(self, Token__is_extern)) {
        is_external = true;
        location = Parser__consume_token(self, Token__is_extern)->location;
        Parser__consume_space(self, 1);
    } else {
        is_external = false;
        location = Parser__peek_token(self, 0)->location;
    }
    Parsed_Type* return_type = Parser__parse_type(self);
    Parser__consume_space(self, 1);
    Token* name = Parser__consume_token(self, Token__is_identifier);
    Parser__consume_space(self, 0);
    Parser__consume_token(self, Token__is_opening_paren);
    Parsed_Function_Parameter* first_parameter = Parser__parse_function_parameters(self);
    Parser__consume_space(self, 0);
    Parser__consume_token(self, Token__is_closing_paren);
    Parsed_Statements* statements = null;
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
    } else {
        Parser__consume_space(self, 0);
        Parser__consume_token(self, Token__is_semicolon);
    }
    return Parsed_Function_Statement__create(location, name, first_parameter, return_type, statements, is_external);
}

// return
//      | "return" expression? ";"
Parsed_Statement* Parser__parse_return_statement(Parser* self) {
    Source_Location* location = Parser__consume_token(self, Token__is_return)->location;
    Parsed_Expression* expression = null;
    if (!Parser__matches_two(self, Token__is_space, false, Token__is_semicolon)) {
        Parser__consume_space(self, 1);
        expression = Parser__parse_expression(self);
    }
    Parser__consume_space(self, 0);
    Parser__consume_token(self, Token__is_semicolon);
    return Parsed_Return_Statement__create(location, expression);
}

// break
//      | "break" ";"
Parsed_Statement* Parser__parse_break_statement(Parser* self) {
    Source_Location* location = Parser__consume_token(self, Token__is_break)->location;
    Parser__consume_space(self, 0);
    Parser__consume_token(self, Token__is_semicolon);
    return Parsed_Break_Statement__create(location);
}

// if
//      | "if" "(" expression ")" statement ( "else" statement )?
Parsed_Statement* Parser__parse_if_statement(Parser* self) {
    Source_Location* location = Parser__consume_token(self, Token__is_if)->location;
    Parser__consume_space(self, 1);
    Parser__consume_token(self, Token__is_opening_paren);
    Parser__consume_space(self, 0);
    Parsed_Expression* condition_expression = Parser__parse_expression(self);
    Parser__consume_space(self, 0);
    Parser__consume_token(self, Token__is_closing_paren);
    Parser__consume_space(self, 1);
    Parsed_Statement* true_statement = (Parsed_Statement*) Parser__parse_block_statement(self);
    Parsed_Statement* false_statement = null;
    if (Parser__matches_two(self, Token__is_space, false, Token__is_else)) {
        Parser__consume_space(self, 1);
        Parser__consume_token(self, Token__is_else);
        Parser__consume_space(self, 1);
        if (Parser__matches_one(self, Token__is_if)) {
            false_statement = (Parsed_Statement*) Parser__parse_if_statement(self);
        } else {
            false_statement = (Parsed_Statement*) Parser__parse_block_statement(self);
        }
    }
    return Parsed_If_Statement__create(location, condition_expression, true_statement, false_statement);
}

// while
//      | "while" "(" expression ")" statement
Parsed_Statement* Parser__parse_while_statement(Parser* self) {
    Source_Location* location = Parser__consume_token(self, Token__is_while)->location;
    Parser__consume_space(self, 1);
    Parser__consume_token(self, Token__is_opening_paren);
    Parser__consume_space(self, 0);
    Parsed_Expression* condition_expression = Parser__parse_expression(self);
    Parser__consume_space(self, 0);
    Parser__consume_token(self, Token__is_closing_paren);
    Parser__consume_space(self, 1);
    Parsed_Statement* body_statement = (Parsed_Statement*) Parser__parse_block_statement(self);
    return Parsed_While_Statement__create(location, condition_expression, body_statement);
}

// statement
//      | enum
//      | function
//      | if
//      | return
//      | struct
//      | type_alias
//      | variable
Parsed_Statement* Parser__parse_statement(Parser* self) {
    Parser__consume_space(self, self->current_identation * 4);

    if (Parser__matches_one(self, Token__is_if)) {
        return Parser__parse_if_statement(self);
    }
    if (Parser__matches_one(self, Token__is_while)) {
        return Parser__parse_while_statement(self);
    }
    if (Parser__matches_one(self, Token__is_return)) {
        return Parser__parse_return_statement(self);
    }
    if (Parser__matches_one(self, Token__is_break)) {
        return Parser__parse_break_statement(self);
    }

    if (Parser__matches_three(self, Token__is_typedef, true, Token__is_space, true, Token__is_struct)) {
        return Parser__parse_struct(self);
    }

    if (Parser__matches_three(self, Token__is_typedef, true, Token__is_space, true, Token__is_enum)) {
        return Parser__parse_enum(self);
    }

    if (Parser__matches_one(self, Token__is_typedef)) {
        return Parser__parse_type_alias(self);
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
            while (Token__is_asterisk(Parser__peek_token(self, peek_offset))) {
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

    Parsed_Expression* expresion = Parser__parse_access_expression(self);
    if (Parser__matches_two(self, Token__is_space, false, Token__is_equals)) {
        Parser__consume_space(self, 1);
        Parser__consume_token(self, Token__is_equals);
        Parser__consume_space(self, 1);
        Parsed_Expression* value_expression = Parser__parse_expression(self);
        Parser__consume_space(self, 0);
        Parser__consume_token(self, Token__is_semicolon);
        return (Parsed_Statement*) Parsed_Assignment_Statement__create(expresion, value_expression);
    }
    Parser__consume_space(self, 0);
    Parser__consume_token(self, Token__is_semicolon);
    return (Parsed_Statement*) Parsed_Expression_Statement__create(expresion);
}

// statements
//      | ( statement )*
void Parser__parse_statements(Parser* self, Parsed_Statements* statements) {
    while (true) {
        while (Parser__consume_empty_line(self)) {
            // ignored
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

        Parsed_Statement* statement = Parser__parse_statement(self);

        Parser__consume_end_of_line(self);

        Parsed_Statements__append(statements, statement);
    }
}

void Parser__parse_source(Parser* self, Source* source) {
    Scanner* other_scanner = self->scanner;

    self->scanner = Scanner__create(source);

    Parser__parse_statements(self, self->compilation_unit->statements);

    Token* last_token = Parser__peek_token(self, 0);
    if (!Token__is_end_of_file(last_token)) {
        Parser__panic(self, String__create_from("Scanner didn't reach end of file"));
    } else if (last_token->location->column != 1) {
        Parser__warning(self, String__create_from("No new line at the end of file"));
    }

    self->scanner = other_scanner;
}

Parsed_Source* parse(Source* source) {
    Parser parser;
    parser.scanner = null;
    parser.compilation_unit = Parsed_Compilation_Unit__create();
    parser.current_identation = 0;

    // TODO: use following types during type checking phase
    // Parser__create_type(&parser, PARSED_TYPE_KIND__BOOL, String__create_from("bool"), null);
    // Parser__create_type(&parser, PARSED_TYPE_KIND__CHAR, String__create_from("char"), null);
    // Parser__create_type(&parser, PARSED_TYPE_KIND__INT16_T, String__create_from("int16_t"), null);
    // Parser__create_type(&parser, PARSED_TYPE_KIND__INT32_T, String__create_from("int32_t"), null);
    // Parser__create_type(&parser, PARSED_TYPE_KIND__INT64_T, String__create_from("int64_t"), null);
    // Parser__create_type(&parser, PARSED_TYPE_KIND__INT8_T, String__create_from("int8_t"), null);
    // Parser__create_type(&parser, PARSED_TYPE_KIND__SIZE_T, String__create_from("size_t"), null);
    // Parser__create_type(&parser, PARSED_TYPE_KIND__UINT16_T, String__create_from("uint16_t"), null);
    // Parser__create_type(&parser, PARSED_TYPE_KIND__UINT32_T, String__create_from("uint32_t"), null);
    // Parser__create_type(&parser, PARSED_TYPE_KIND__UINT64_T, String__create_from("uint64_t"), null);
    // Parser__create_type(&parser, PARSED_TYPE_KIND__UINT8_T, String__create_from("uint8_t"), null);
    // Parser__create_type(&parser, PARSED_TYPE_KIND__VOID, String__create_from("void"), null);

    Parser__parse_source(&parser, source);

    return parser.compilation_unit;
}

// Main

int32_t main() {
    Source* source = Source__create(stdin);

    parse(source);

    return 0;
}
