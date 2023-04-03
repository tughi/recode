// Copyright (C) 2023 Stefan Selariu

#pragma region Builtins

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

#define null 0

#pragma endregion
#pragma region LibC

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

#pragma endregion
#pragma region String

typedef struct String {
    char* data;
    size_t data_size;
    size_t length;
} String;

String* String__create_empty(size_t data_size) {
    String* string = (String*) malloc(sizeof(String));
    string->data = (char*) malloc(data_size);
    string->data_size = data_size;
    string->length = (size_t) 0;
    return string;
}

String* String__create() {
    return String__create_empty((size_t) 16);
}

void String__delete(String* self) {
    free((void*) self->data);
    free((void*) self);
}

String* String__append_char(String* self, char ch) {
    if (self->length >= self->data_size) {
        self->data_size = self->data_size + (size_t) 16;
        self->data = (char*) realloc((void*) self->data, self->data_size);
    }
    self->data[self->length] = ch;
    self->length = self->length + (size_t) 1;
    return self;
}

String* String__append_cstring(String* self, const char* s) {
    size_t index = (size_t) 0;
    while (true) {
        char c = s[index];
        if (c == '\0') {
            return self;
        }
        String__append_char(self, c);
        index = index + (size_t) 1;
    }
}

size_t cstring_length(const char* s) {
    size_t length = (size_t) 0;
    while (true) {
        uint8_t c = (uint8_t) s[length];
        if (c == (uint8_t) 0) {
            break;
        }
        length = length + (size_t) 1;
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
    if (value < (int16_t) 0) {
        String__append_char(self, '-');
        String__append_int16_t(self, -value);
    } else {
        if (value >= (int16_t) 10) {
            String__append_int16_t(self, value / (int16_t) 10);
        }
        String__append_char(self, (char) (value % (int16_t) 10) + '0');
    }
    return self;
}

String* String__append_string(String* self, String* other) {
    size_t index = (size_t) 0;
    while (index < other->length) {
        String__append_char(self, other->data[index]);
        index = index + (size_t) 1;
    }
    return self;
}

bool String__equals_cstring(String* self, const char* s) {
    size_t length = cstring_length(s);
    if (self->length != length) {
        return false;
    }

    size_t index = (size_t) 0;
    while (index < length) {
        if (self->data[index] != s[index]) {
            return false;
        }
        index = index + (size_t) 1;
    }

    return true;
}

bool String__equals_string(String* self, String* other) {
    if (self->length != other->length) {
        return false;
    }

    size_t index = (size_t) 0;
    while (index < self->length) {
        if (self->data[index] != other->data[index]) {
            return false;
        }
        index = index + (size_t) 1;
    }

    return true;
}

#pragma endregion
#pragma region Utils

void pass() {
}

void File__write_char(File* self, char c) {
    fputc((int32_t) c, self);
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
        File__write_char(self, (char) (value % 10) + '0');
    }
}

void File__write_uint64_t(File* self, uint64_t value) {
    if (value >= (uint64_t) 10) {
        File__write_uint64_t(self, value / (uint64_t) 10);
    }
    File__write_char(self, (char) (value % (uint64_t) 10) + '0');
}

void File__write_string(File* self, String* string) {
    size_t index = (size_t) 0;
    while (index < string->length) {
        File__write_char(self, string->data[index]);
        index = index + (size_t) 1;
    }
}

void error(String* message) {
    File__write_cstring(stderr, "\e[0;91m");
    File__write_string(stderr, message);
    File__write_cstring(stderr, "\e[0m\n");
}

void warning(String* message) {
    File__write_cstring(stderr, "\e[0;93m");
    File__write_string(stderr, message);
    File__write_cstring(stderr, "\e[0m\n");
}

void TODO(const char* message) {
    File__write_cstring(stderr, "\e[0;95mTODO: ");
    File__write_cstring(stderr, message);
    File__write_cstring(stderr, "\e[0m\n");
}

#pragma endregion
#pragma region Source

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
        String__append_char(source_content, (char) ch);
    }

    String__append_char(source_content, '\0'); // simplifies EOF detection

    Source* source = (Source*) malloc(sizeof(Source));
    source->content = source_content;

    return source;
}

#pragma endregion
#pragma region Source Location

typedef struct Source_Location {
    Source* source;
    uint16_t line;
    uint16_t column;
} Source_Location;

Source_Location* Source_Location__create(Source* source, uint16_t line, uint16_t column) {
    Source_Location* source_location = (Source_Location*) malloc(sizeof(Source_Location));
    source_location->source = source;
    source_location->line = line;
    source_location->column = column;
    return source_location;
}

void File__write_source_location(File* self, Source_Location* location) {
    File__write_cstring(self, "compiler/ReCode.c:");
    File__write_int32_t(self, (int32_t) location->line);
    File__write_char(self, ':');
    File__write_int32_t(self, (int32_t) location->column);
    File__write_cstring(self, ": ");
}

void Source_Location__error(Source_Location* self, String* message) {
    File__write_source_location(stderr, self);
    error(message);
}

void Source_Location__warning(Source_Location* self, String* message) {
    File__write_source_location(stderr, self);
    warning(message);
}

#pragma endregion
#pragma region Tokens

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

Token* Token__create_kind(Token_Kind kind, size_t kind_size, Source_Location* location, String* lexeme) {
    Token* token = (Token*) malloc(kind_size);
    token->kind = kind;
    token->location = location;
    token->lexeme = lexeme;
    token->next_token = null;
    return token;
}

void Token__error(Token* self, String* message) {
    Source_Location__error(self->location, message);
}

void Token__warning(Token* self, String* message) {
    Source_Location__warning(self->location, message);
}

typedef struct Character_Token {
    Token super;
    char value;
} Character_Token;

Character_Token* Character_Token__create(Source_Location* location, String* lexeme, char value) {
    Character_Token* token = (Character_Token*) Token__create_kind(TOKEN_KIND__CHARACTER, sizeof(Character_Token), location, lexeme);
    token->value = value;
    return token;
}

typedef struct Comment_Token {
    Token super;
} Comment_Token;

Comment_Token* Comment_Token__create(Source_Location* location, String* lexeme) {
    return (Comment_Token*) Token__create_kind(TOKEN_KIND__COMMENT, sizeof(Comment_Token), location, lexeme);
}

typedef struct End_Of_File_Token {
    Token super;
} End_Of_File_Token;

End_Of_File_Token* End_Of_File_Token__create(Source_Location* location, String* lexeme) {
    return (End_Of_File_Token*) Token__create_kind(TOKEN_KIND__END_OF_FILE, sizeof(End_Of_File_Token), location, lexeme);
}

typedef struct End_Of_Line_Token {
    Token super;
} End_Of_Line_Token;

End_Of_Line_Token* End_Of_Line_Token__create(Source_Location* location, String* lexeme) {
    return (End_Of_Line_Token*) Token__create_kind(TOKEN_KIND__END_OF_LINE, sizeof(End_Of_Line_Token), location, lexeme);
}

typedef struct Error_Token {
    Token super;
} Error_Token;

Error_Token* Error_Token__create(Source_Location* location, String* lexeme) {
    return (Error_Token*) Token__create_kind(TOKEN_KIND__ERROR, sizeof(Error_Token), location, lexeme);
}

typedef struct Identifier_Token {
    Token super;
} Identifier_Token;

Identifier_Token* Identifier_Token__create(Source_Location* location, String* lexeme) {
    return (Identifier_Token*) Token__create_kind(TOKEN_KIND__IDENTIFIER, sizeof(Identifier_Token), location, lexeme);
}

typedef struct Integer_Token {
    Token super;
    uint64_t value;
} Integer_Token;

Integer_Token* Integer_Token__create(Source_Location* location, String* lexeme, uint64_t value) {
    Integer_Token* token = (Integer_Token*) Token__create_kind(TOKEN_KIND__INTEGER, sizeof(Integer_Token), location, lexeme);
    token->value = value;
    return token;
}

typedef struct Other_Token {
    Token super;
} Other_Token;

Other_Token* Other_Token__create(Source_Location* location, String* lexeme) {
    return (Other_Token*) Token__create_kind(TOKEN_KIND__OTHER, sizeof(Other_Token), location, lexeme);
}

typedef struct Space_Token {
    Token super;
    uint16_t count;
} Space_Token;

Space_Token* Space_Token__create(Source_Location* location, String* lexeme, uint16_t count) {
    Space_Token* token = (Space_Token*) Token__create_kind(TOKEN_KIND__SPACE, sizeof(Space_Token), location, lexeme);
    token->count = count;
    return token;
}

typedef struct String_Token {
    Token super;
    String* value;
} String_Token;

String_Token* String_Token__create(Source_Location* location, String* lexeme, String* value) {
    String_Token* token = (String_Token*) Token__create_kind(TOKEN_KIND__STRING, sizeof(String_Token), location, lexeme);
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

#pragma endregion
#pragma region Scanner

typedef struct Scanner {
    Source* source;
    size_t current_char_index;
    uint16_t current_line;
    uint16_t current_column;
    Token* current_token;
} Scanner;

char Scanner__peek_char(Scanner* self) {
    return self->source->content->data[self->current_char_index];
}

char Scanner__next_char(Scanner* self) {
    char next_char = Scanner__peek_char(self);
    if (next_char != '\0') {
        self->current_char_index = self->current_char_index + (size_t) 1;
        if (next_char == '\n') {
            self->current_line = self->current_line + (uint16_t) 1;
            self->current_column = (uint16_t) 1;
        } else {
            self->current_column = self->current_column + (uint16_t) 1;
        }
    }
    return next_char;
}

char escape_char_value(char c) {
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
    return (char) -1;
}

bool char_is_end_of_line(char c) {
    return c == '\n' || c == '\0';
}

Token* Scanner__scan_character_token(Scanner* self, Source_Location* source_location, String* token_lexeme) {
    if (Scanner__next_char(self) != '\'') {
        Source_Location__error(source_location, String__create_from("Unexpected char"));
        abort();
    }
    String__append_char(token_lexeme, '\'');

    char next_char = Scanner__peek_char(self);
    if (char_is_end_of_line(next_char) || next_char == '\t') {
        return (Token*) Error_Token__create(source_location, token_lexeme);
    }

    String__append_char(token_lexeme, Scanner__next_char(self));
    char value = next_char;

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
        if (value == (char) -1) {
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

bool char_is_identifier_start(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool char_is_identifier_letter(char c) {
    return char_is_identifier_start(c) || (c >= '0' && c <= '9');
}

Token* Scanner__scan_identifier_token(Scanner* self, Source_Location* source_location, String* token_lexeme) {
    while (char_is_identifier_letter(Scanner__peek_char(self))) {
        String__append_char(token_lexeme, Scanner__next_char(self));
    }
    return (Token*) Identifier_Token__create(source_location, token_lexeme);
}

bool char_is_digit(char c) {
    return c >= '0' && c <= '9';
}

Token* Scanner__scan_integer_token(Scanner* self, Source_Location* source_location, String* token_lexeme) {
    uint64_t value = (uint64_t) 0;
    while (char_is_digit(Scanner__peek_char(self))) {
        char c = Scanner__next_char(self);
        value = value * (uint64_t) 10 + (uint64_t) (c - '0');
        String__append_char(token_lexeme, c);
    }
    return (Token*) Integer_Token__create(source_location, token_lexeme, value);
}

bool char_is_space(char c) {
    return c == ' ';
}

Token* Scanner__scan_space_token(Scanner* self, Source_Location* source_location, String* token_lexeme) {
    uint16_t count = (uint16_t) 0;
    while (char_is_space(Scanner__peek_char(self))) {
        count = count + (uint16_t) 1;
        String__append_char(token_lexeme, Scanner__next_char(self));
    }
    return (Token*) Space_Token__create(source_location, token_lexeme, count);
}

Token* Scanner__scan_string_token(Scanner* self, Source_Location* source_location, String* token_lexeme) {
    if (Scanner__next_char(self) != '"') {
        Source_Location__error(source_location, String__create_from("Unexpected char"));
        abort();
    }
    String__append_char(token_lexeme, '"');

    String* value = String__create();

    while (true) {
        char next_char = Scanner__peek_char(self);
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
            if (next_char == ((char) -1)) {
                return (Token*) Error_Token__create(source_location, token_lexeme);
            }
        }

        String__append_char(value, next_char);
    }
}

Token* Scanner__scan_token(Scanner* self) {
    Source_Location* source_location = Source_Location__create(self->source, self->current_line, self->current_column);
    String* token_lexeme = String__create();

    char next_char = Scanner__peek_char(self);

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
    while (offset > (uint8_t) 0) {
        if (token->next_token == null) {
            token->next_token = Scanner__scan_token(self);
        }
        token = token->next_token;
        offset = offset - (uint8_t) 1;
    }
    return token;
}

Scanner* Scanner__create(Source* source) {
    Scanner* scanner = (Scanner*) malloc(sizeof(Scanner));
    scanner->source = source;
    scanner->current_char_index = (size_t) 0;
    scanner->current_line = (uint16_t) 1;
    scanner->current_column = (uint16_t) 1;

    scanner->current_token = Scanner__scan_token(scanner);

    return scanner;
}

#pragma endregion
#pragma region Parsed Source

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
} Parsed_Type;

Parsed_Type* Parsed_Type__create_kind(Parsed_Type_Kind kind, size_t kind_size, Source_Location* location) {
    Parsed_Type* type = (Parsed_Type*) malloc(kind_size);
    type->kind = kind;
    type->location = location;
    return type;
}

typedef struct Parsed_Const_Type {
    Parsed_Type super;
    Parsed_Type* other_type;
} Parsed_Const_Type;

Parsed_Type* Parsed_Const_Type__create(Source_Location* location, Parsed_Type* other_type) {
    Parsed_Const_Type* type = (Parsed_Const_Type*) Parsed_Type__create_kind(PARSED_TYPE_KIND__CONST, sizeof(Parsed_Const_Type), location);
    type->other_type = other_type;
    return (Parsed_Type*) type;
}

typedef struct Parsed_Named_Type {
    Parsed_Type super;
    String* name;
} Parsed_Named_Type;

Parsed_Type* Parsed_Named_Type__create(Token* name) {
    Parsed_Named_Type* type = (Parsed_Named_Type*) Parsed_Type__create_kind(PARSED_TYPE_KIND__NAMED, sizeof(Parsed_Named_Type), name->location);
    type->name = name->lexeme;
    return (Parsed_Type*) type;
}

typedef struct Parsed_Pointer_Type {
    Parsed_Type super;
    Parsed_Type* other_type;
} Parsed_Pointer_Type;

Parsed_Type* Parsed_Pointer_Type__create(Parsed_Type* other_type) {
    Parsed_Pointer_Type* type = (Parsed_Pointer_Type*) Parsed_Type__create_kind(PARSED_TYPE_KIND__POINTER, sizeof(Parsed_Pointer_Type), other_type->location);
    type->other_type = other_type;
    return (Parsed_Type*) type;
}

typedef struct Parsed_Struct_Type {
    Parsed_Type super;
    Parsed_Type* other_type;
} Parsed_Struct_Type;

Parsed_Type* Parsed_Struct_Type__create(Source_Location* location, Parsed_Type* other_type) {
    Parsed_Struct_Type* type = (Parsed_Struct_Type*) Parsed_Type__create_kind(PARSED_TYPE_KIND__STRUCT, sizeof(Parsed_Struct_Type), location);
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
    PARSED_EXPRESSION_KIND__NOT,
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

Parsed_Expression* Parsed_Expression__create_kind(Parsed_Expression_Kind kind, size_t kind_size, Source_Location* location) {
    Parsed_Expression* expression = (Parsed_Expression*) malloc(kind_size);
    expression->kind = kind;
    expression->location = location;
    return expression;
}

typedef struct Parsed_Binary_Expression {
    Parsed_Expression super;
    Parsed_Expression* left_expression;
    Parsed_Expression* right_expression;
} Parsed_Binary_Expression;

Parsed_Binary_Expression* Parsed_Binary_Expression__create_kind(Parsed_Expression_Kind kind, Parsed_Expression* left_expression, Parsed_Expression* right_expression) {
    Parsed_Binary_Expression* expression = (Parsed_Binary_Expression*) Parsed_Expression__create_kind(kind, sizeof(Parsed_Binary_Expression), left_expression->location);
    expression->left_expression = left_expression;
    expression->right_expression = right_expression;
    return expression;
}

typedef struct Parsed_Unary_Expression {
    Parsed_Expression super;
    Parsed_Expression* other_expression;
} Parsed_Unary_Expression;

Parsed_Unary_Expression* Parsed_Unary_Expression__create_kind(Parsed_Expression_Kind kind, size_t kind_size, Source_Location* location, Parsed_Expression* other_expression) {
    Parsed_Unary_Expression* expression = (Parsed_Unary_Expression*) Parsed_Expression__create_kind(kind, kind_size, location);
    expression->other_expression = other_expression;
    return expression;
}

typedef struct Parsed_Literal_Expression {
    Parsed_Expression super;
    Token* literal;
} Parsed_Literal_Expression;

Parsed_Literal_Expression* Parsed_Literal_Expression__create_kind(Parsed_Expression_Kind kind, size_t kind_size, Token* literal) {
    Parsed_Literal_Expression* expression = (Parsed_Literal_Expression*) Parsed_Expression__create_kind(kind, kind_size, literal->location);
    expression->literal = literal;
    return expression;
}

typedef struct Parsed_Add_Expression {
    Parsed_Binary_Expression super;
} Parsed_Add_Expression;

Parsed_Add_Expression* Parsed_Add_Expression__create(Parsed_Expression* left_expression, Parsed_Expression* right_expression) {
    return (Parsed_Add_Expression*) Parsed_Binary_Expression__create_kind(PARSED_EXPRESSION_KIND__ADD, left_expression, right_expression);
}

typedef struct Parsed_Address_Of_Expression {
    Parsed_Unary_Expression super;
} Parsed_Address_Of_Expression;

Parsed_Address_Of_Expression* Parsed_Address_Of_Expression__create(Source_Location* location, Parsed_Expression* other_expression) {
    return (Parsed_Address_Of_Expression*) Parsed_Unary_Expression__create_kind(PARSED_EXPRESSION_KIND__ADDRESS_OF, sizeof(Parsed_Address_Of_Expression), location, other_expression);
}

typedef struct Parsed_Array_Access_Expression {
    Parsed_Expression super;
    Parsed_Expression* array_expression;
    Parsed_Expression* index_expression;
} Parsed_Array_Access_Expression;

Parsed_Array_Access_Expression* Parsed_Array_Access_Expression__create(Parsed_Expression* array_expression, Parsed_Expression* index_expression) {
    Parsed_Array_Access_Expression* expression = (Parsed_Array_Access_Expression*) Parsed_Expression__create_kind(PARSED_EXPRESSION_KIND__ARRAY_ACCESS, sizeof(Parsed_Array_Access_Expression), array_expression->location);
    expression->array_expression = array_expression;
    expression->index_expression = index_expression;
    return expression;
}

typedef struct Parsed_Bool_Expression {
    Parsed_Literal_Expression super;
    bool value;
} Parsed_Bool_Expression;

Parsed_Bool_Expression* Parsed_Bool_Expression__create(Token* literal, bool value) {
    Parsed_Bool_Expression* expression = (Parsed_Bool_Expression*) Parsed_Literal_Expression__create_kind(PARSED_EXPRESSION_KIND__BOOL, sizeof(Parsed_Bool_Expression), literal);
    expression->value = value;
    return expression;
}

typedef struct Parsed_Call_Argument {
    Parsed_Expression* expression;
    struct Parsed_Call_Argument* next_argument;
} Parsed_Call_Argument;

Parsed_Call_Argument* Parsed_Call_Argument__create(Parsed_Expression* expression) {
    Parsed_Call_Argument* argument = (Parsed_Call_Argument*) malloc(sizeof(Parsed_Call_Argument));
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
    Parsed_Call_Expression* expression = (Parsed_Call_Expression*) Parsed_Expression__create_kind(PARSED_EXPRESSION_KIND__CALL, sizeof(Parsed_Call_Expression), callee_expression->location);
    expression->callee_expression = callee_expression;
    expression->first_argument = null;
    return expression;
}

typedef struct Parsed_Cast_Expression {
    Parsed_Unary_Expression super;
    Parsed_Type* type;
} Parsed_Cast_Expression;

Parsed_Cast_Expression* Parsed_Cast_Expression__create(Source_Location* location, Parsed_Expression* other_expression, Parsed_Type* type) {
    Parsed_Cast_Expression* expression = (Parsed_Cast_Expression*) Parsed_Unary_Expression__create_kind(PARSED_EXPRESSION_KIND__CAST, sizeof(Parsed_Cast_Expression), location, other_expression);
    expression->type = type;
    return expression;
}

typedef struct Parsed_Character_Expression {
    Parsed_Literal_Expression super;
    char value;
} Parsed_Character_Expression;

Parsed_Character_Expression* Parsed_Character_Expression__create(Character_Token* literal) {
    Parsed_Character_Expression* expression = (Parsed_Character_Expression*) Parsed_Literal_Expression__create_kind(PARSED_EXPRESSION_KIND__CHARACTER, sizeof(Parsed_Character_Expression), (Token*) literal);
    expression->value = literal->value;
    return expression;
}

typedef struct Parsed_Divide_Expression {
    Parsed_Binary_Expression super;
} Parsed_Divide_Expression;

Parsed_Divide_Expression* Parsed_Divide_Expression__create(Parsed_Expression* left_expression, Parsed_Expression* right_expression) {
    return (Parsed_Divide_Expression*) Parsed_Binary_Expression__create_kind(PARSED_EXPRESSION_KIND__DIVIDE, left_expression, right_expression);
}

typedef struct Parsed_Equals_Expression {
    Parsed_Binary_Expression super;
} Parsed_Equals_Expression;

Parsed_Equals_Expression* Parsed_Equals_Expression__create(Parsed_Expression* left_expression, Parsed_Expression* right_expression) {
    return (Parsed_Equals_Expression*) Parsed_Binary_Expression__create_kind(PARSED_EXPRESSION_KIND__EQUALS, left_expression, right_expression);
}

typedef struct Parsed_Greater_Expression {
    Parsed_Binary_Expression super;
} Parsed_Greater_Expression;

Parsed_Greater_Expression* Parsed_Greater_Expression__create(Parsed_Expression* left_expression, Parsed_Expression* right_expression) {
    return (Parsed_Greater_Expression*) Parsed_Binary_Expression__create_kind(PARSED_EXPRESSION_KIND__GREATER, left_expression, right_expression);
}

typedef struct Parsed_Greater_Or_Equals_Expression {
    Parsed_Binary_Expression super;
} Parsed_Greater_Or_Equals_Expression;

Parsed_Greater_Or_Equals_Expression* Parsed_Greater_Or_Equals_Expression__create(Parsed_Expression* left_expression, Parsed_Expression* right_expression) {
    return (Parsed_Greater_Or_Equals_Expression*) Parsed_Binary_Expression__create_kind(PARSED_EXPRESSION_KIND__GREATER_OR_EQUALS, left_expression, right_expression);
}

typedef struct Parsed_Group_Expression {
    Parsed_Expression super;
    Parsed_Expression* other_expression;
} Parsed_Group_Expression;

Parsed_Group_Expression* Parsed_Group_Expression__create(Source_Location* location, Parsed_Expression* other_expression) {
    Parsed_Group_Expression* expression = (Parsed_Group_Expression*) Parsed_Expression__create_kind(PARSED_EXPRESSION_KIND__GROUP, sizeof(Parsed_Group_Expression), location);
    expression->other_expression = other_expression;
    return expression;
}

typedef struct Parsed_Integer_Expression {
    Parsed_Literal_Expression super;
    uint64_t value;
} Parsed_Integer_Expression;

Parsed_Integer_Expression* Parsed_Integer_Expression__create(Integer_Token* literal) {
    Parsed_Integer_Expression* expression = (Parsed_Integer_Expression*) Parsed_Literal_Expression__create_kind(PARSED_EXPRESSION_KIND__INTEGER, sizeof(Parsed_Integer_Expression), (Token*) literal);
    expression->value = literal->value;
    return expression;
}

typedef struct Parsed_Less_Expression {
    Parsed_Binary_Expression super;
} Parsed_Less_Expression;

Parsed_Less_Expression* Parsed_Less_Expression__create(Parsed_Expression* left_expression, Parsed_Expression* right_expression) {
    return (Parsed_Less_Expression*) Parsed_Binary_Expression__create_kind(PARSED_EXPRESSION_KIND__LESS, left_expression, right_expression);
}

typedef struct Parsed_Less_Or_Equals_Expression {
    Parsed_Binary_Expression super;
} Parsed_Less_Or_Equals_Expression;

Parsed_Less_Or_Equals_Expression* Parsed_Less_Or_Equals_Expression__create(Parsed_Expression* left_expression, Parsed_Expression* right_expression) {
    return (Parsed_Less_Or_Equals_Expression*) Parsed_Binary_Expression__create_kind(PARSED_EXPRESSION_KIND__LESS_OR_EQUALS, left_expression, right_expression);
}

typedef struct Parsed_Logic_And_Expression {
    Parsed_Binary_Expression super;
} Parsed_Logic_And_Expression;

Parsed_Logic_And_Expression* Parsed_Logic_And_Expression__create(Parsed_Expression* left_expression, Parsed_Expression* right_expression) {
    return (Parsed_Logic_And_Expression*) Parsed_Binary_Expression__create_kind(PARSED_EXPRESSION_KIND__LOGIC_AND, left_expression, right_expression);
}

typedef struct Parsed_Logic_Or_Expression {
    Parsed_Binary_Expression super;
} Parsed_Logic_Or_Expression;

Parsed_Logic_Or_Expression* Parsed_Logic_Or_Expression__create(Parsed_Expression* left_expression, Parsed_Expression* right_expression) {
    return (Parsed_Logic_Or_Expression*) Parsed_Binary_Expression__create_kind(PARSED_EXPRESSION_KIND__LOGIC_OR, left_expression, right_expression);
}

typedef struct Parsed_Member_Access_Expression {
    Parsed_Expression super;
    Parsed_Expression* object_expression;
    Token* member_name;
} Parsed_Member_Access_Expression;

Parsed_Member_Access_Expression* Parsed_Member_Access_Expression__create(Parsed_Expression* object_expression, Token* member_name) {
    Parsed_Member_Access_Expression* expression = (Parsed_Member_Access_Expression*) Parsed_Expression__create_kind(PARSED_EXPRESSION_KIND__MEMBER_ACCESS, sizeof(Parsed_Member_Access_Expression), object_expression->location);
    expression->object_expression = object_expression;
    expression->member_name = member_name;
    return expression;
}

typedef struct Parsed_Minus_Expression {
    Parsed_Unary_Expression super;
} Parsed_Minus_Expression;

Parsed_Minus_Expression* Parsed_Minus_Expression__create(Source_Location* location, Parsed_Expression* other_expression) {
    return (Parsed_Minus_Expression*) Parsed_Unary_Expression__create_kind(PARSED_EXPRESSION_KIND__MINUS, sizeof(Parsed_Minus_Expression), location, other_expression);
}

typedef struct Parsed_Modulo_Expression {
    Parsed_Binary_Expression super;
} Parsed_Modulo_Expression;

Parsed_Modulo_Expression* Parsed_Modulo_Expression__create(Parsed_Expression* left_expression, Parsed_Expression* right_expression) {
    return (Parsed_Modulo_Expression*) Parsed_Binary_Expression__create_kind(PARSED_EXPRESSION_KIND__MODULO, left_expression, right_expression);
}

typedef struct Parsed_Multiply_Expression {
    Parsed_Binary_Expression super;
} Parsed_Multiply_Expression;

Parsed_Multiply_Expression* Parsed_Multiply_Expression__create(Parsed_Expression* left_expression, Parsed_Expression* right_expression) {
    return (Parsed_Multiply_Expression*) Parsed_Binary_Expression__create_kind(PARSED_EXPRESSION_KIND__MULTIPLY, left_expression, right_expression);
}

typedef struct Parsed_Not_Expression {
    Parsed_Unary_Expression super;
} Parsed_Not_Expression;

Parsed_Not_Expression* Parsed_Not_Expression__create(Source_Location* location, Parsed_Expression* other_expression) {
    return (Parsed_Not_Expression*) Parsed_Unary_Expression__create_kind(PARSED_EXPRESSION_KIND__NOT, sizeof(Parsed_Not_Expression), location, other_expression);
}

typedef struct Parsed_Not_Equals_Expression {
    Parsed_Binary_Expression super;
} Parsed_Not_Equals_Expression;

Parsed_Not_Equals_Expression* Parsed_Not_Equals_Expression__create(Parsed_Expression* left_expression, Parsed_Expression* right_expression) {
    return (Parsed_Not_Equals_Expression*) Parsed_Binary_Expression__create_kind(PARSED_EXPRESSION_KIND__NOT_EQUALS, left_expression, right_expression);
}

typedef struct Parsed_Null_Expression {
    Parsed_Literal_Expression super;
} Parsed_Null_Expression;

Parsed_Null_Expression* Parsed_Null_Expression__create(Token* literal) {
    return (Parsed_Null_Expression*) Parsed_Literal_Expression__create_kind(PARSED_EXPRESSION_KIND__NULL, sizeof(Parsed_Null_Expression), literal);
}

typedef struct Parsed_Sizeof_Expression {
    Parsed_Expression super;
    Parsed_Type* type;
} Parsed_Sizeof_Expression;

Parsed_Sizeof_Expression* Parsed_Sizeof_Expression__create(Source_Location* location, Parsed_Type* type) {
    Parsed_Sizeof_Expression* expression = (Parsed_Sizeof_Expression*) Parsed_Expression__create_kind(PARSED_EXPRESSION_KIND__SIZEOF, sizeof(Parsed_Sizeof_Expression), location);
    expression->type = type;
    return expression;
}

typedef struct Parsed_String_Expression {
    Parsed_Literal_Expression super;
    String* value;
} Parsed_String_Expression;

Parsed_String_Expression* Parsed_String_Expression__create(String_Token* literal) {
    Parsed_String_Expression* expression = (Parsed_String_Expression*) Parsed_Literal_Expression__create_kind(PARSED_EXPRESSION_KIND__STRING, sizeof(Parsed_String_Expression), (Token*) literal);
    expression->value = literal->value;
    return expression;
}

typedef struct Parsed_Substract_Expression {
    Parsed_Binary_Expression super;
} Parsed_Substract_Expression;

Parsed_Substract_Expression* Parsed_Substract_Expression__create(Parsed_Expression* left_expression, Parsed_Expression* right_expression) {
    return (Parsed_Substract_Expression*) Parsed_Binary_Expression__create_kind(PARSED_EXPRESSION_KIND__SUBSTRACT, left_expression, right_expression);
}

typedef struct Parsed_Symbol_Expression {
    Parsed_Expression super;
    Token* name;
} Parsed_Symbol_Expression;

Parsed_Symbol_Expression* Parsed_Symbol_Expression__create(Token* name) {
    Parsed_Symbol_Expression* expression = (Parsed_Symbol_Expression*) Parsed_Expression__create_kind(PARSED_EXPRESSION_KIND__SYMBOL, sizeof(Parsed_Symbol_Expression), name->location);
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
    PARSED_STATEMENT_KIND__FUNCTION_TYPE,
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

Parsed_Statement* Parsed_Statement__create_kind(Parsed_Statement_Kind kind, size_t kind_size, Source_Location* location) {
    Parsed_Statement* statement = (Parsed_Statement*) malloc(kind_size);
    statement->kind = kind;
    statement->location = location;
    statement->next_statement = null;
    return statement;
}

typedef struct Parsed_Named_Statement {
    Parsed_Statement super;
    Token* name;
} Parsed_Named_Statement;

Parsed_Named_Statement* Parsed_Named_Statement__create_kind(Parsed_Statement_Kind kind, size_t kind_size, Source_Location* location, Token* name) {
    Parsed_Named_Statement* statement = (Parsed_Named_Statement*) Parsed_Statement__create_kind(kind, kind_size, location);
    statement->name = name;
    return statement;
}

typedef struct Parsed_Assignment_Statement {
    Parsed_Statement super;
    Parsed_Expression* object_expression;
    Parsed_Expression* value_expression;
} Parsed_Assignment_Statement;

Parsed_Assignment_Statement* Parsed_Assignment_Statement__create(Parsed_Expression* object_expression, Parsed_Expression* value_expression) {
    Parsed_Assignment_Statement* statement = (Parsed_Assignment_Statement*) Parsed_Statement__create_kind(PARSED_STATEMENT_KIND__ASSIGNMENT, sizeof(Parsed_Assignment_Statement), object_expression->location);
    statement->object_expression = object_expression;
    statement->value_expression = value_expression;
    return statement;
}

typedef struct Parsed_Block_Statement {
    Parsed_Statement super;
    Parsed_Statements* statements;
} Parsed_Block_Statement;

Parsed_Block_Statement* Parsed_Block_Statement__create(Source_Location* location, Parsed_Statements* statements) {
    Parsed_Block_Statement* statement = (Parsed_Block_Statement*) Parsed_Statement__create_kind(PARSED_STATEMENT_KIND__BLOCK, sizeof(Parsed_Block_Statement), location);
    statement->statements = statements;
    return statement;
}

typedef struct Parsed_Break_Statement {
    Parsed_Statement super;
} Parsed_Break_Statement;

Parsed_Statement* Parsed_Break_Statement__create(Source_Location* location) {
    return Parsed_Statement__create_kind(PARSED_STATEMENT_KIND__BREAK, sizeof(Parsed_Break_Statement), location);
}

typedef struct Parsed_Enum_Member {
    Token* name;
    struct Parsed_Enum_Member* next_member;
} Parsed_Enum_Member;

Parsed_Enum_Member* Parsed_Enum_Member__create(Token* name) {
    Parsed_Enum_Member* member = (Parsed_Enum_Member*) malloc(sizeof(Parsed_Enum_Member));
    member->name = name;
    member->next_member = null;
    return member;
}

typedef struct Parsed_Enum_Statement {
    Parsed_Named_Statement super;
    Parsed_Enum_Member* first_member;
} Parsed_Enum_Statement;

Parsed_Enum_Statement* Parsed_Enum_Statement__create(Source_Location* location, Token* name) {
    Parsed_Enum_Statement* statement = (Parsed_Enum_Statement*) Parsed_Named_Statement__create_kind(PARSED_STATEMENT_KIND__ENUM, sizeof(Parsed_Enum_Statement), location, name);
    statement->first_member = null;
    return statement;
}

typedef struct Parsed_Expression_Statement {
    Parsed_Statement super;
    Parsed_Expression* expression;
} Parsed_Expression_Statement;

Parsed_Expression_Statement* Parsed_Expression_Statement__create(Parsed_Expression* expression) {
    Parsed_Expression_Statement* statement = (Parsed_Expression_Statement*) Parsed_Statement__create_kind(PARSED_STATEMENT_KIND__EXPRESSION, sizeof(Parsed_Expression_Statement), expression->location);
    statement->expression = expression;
    return statement;
}

typedef struct Parsed_Function_Parameter {
    Token* name;
    Parsed_Type* type;
    struct Parsed_Function_Parameter* next_parameter;
} Parsed_Function_Parameter;

Parsed_Function_Parameter* Parsed_Function_Parameter__create(Token* name, Parsed_Type* type) {
    Parsed_Function_Parameter* parameter = (Parsed_Function_Parameter*) malloc(sizeof(Parsed_Function_Parameter));
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
    Parsed_Function_Statement* statement = (Parsed_Function_Statement*) Parsed_Named_Statement__create_kind(PARSED_STATEMENT_KIND__FUNCTION, sizeof(Parsed_Function_Statement), location, name);
    statement->first_parameter = first_parameter;
    statement->return_type = resturn_type;
    statement->statements = statements;
    statement->is_external = is_external;
    return (Parsed_Statement*) statement;
}

typedef struct Parsed_Function_Type_Parameter {
    Token* name;
    Parsed_Type* type;
    struct Parsed_Function_Type_Parameter* next_parameter;
} Parsed_Function_Type_Parameter;

Parsed_Function_Type_Parameter* Parsed_Function_Type_Parameter__create(Token* name, Parsed_Type* type) {
    Parsed_Function_Type_Parameter* parameter = (Parsed_Function_Type_Parameter*) malloc(sizeof(Parsed_Function_Type_Parameter));
    parameter->name = name;
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
    Parsed_Function_Type_Statement* statement = (Parsed_Function_Type_Statement*) Parsed_Named_Statement__create_kind(PARSED_STATEMENT_KIND__FUNCTION_TYPE, sizeof(Parsed_Function_Type_Statement), location, name);
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
    Parsed_If_Statement* statement = (Parsed_If_Statement*) Parsed_Statement__create_kind(PARSED_STATEMENT_KIND__IF, sizeof(Parsed_If_Statement), location);
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
    Parsed_Return_Statement* statement = (Parsed_Return_Statement*) Parsed_Statement__create_kind(PARSED_STATEMENT_KIND__RETURN, sizeof(Parsed_Return_Statement), location);
    statement->expression = expression;
    return (Parsed_Statement*) statement;
}

typedef struct Parsed_Struct_Member {
    Token* name;
    Parsed_Type* type;
    struct Parsed_Struct_Member* next_member;
} Parsed_Struct_Member;

Parsed_Struct_Member* Parsed_Struct_Member__create(Token* name, Parsed_Type* type) {
    Parsed_Struct_Member* member = (Parsed_Struct_Member*) malloc(sizeof(Parsed_Struct_Member));
    member->name = name;
    member->type = type;
    member->next_member = null;
    return member;
}

typedef struct Parsed_Struct_Statement {
    Parsed_Named_Statement super;
    Parsed_Struct_Member* first_member;
} Parsed_Struct_Statement;

Parsed_Struct_Statement* Parsed_Struct_Statement__create(Source_Location* location, Token* name) {
    Parsed_Struct_Statement* statement = (Parsed_Struct_Statement*) Parsed_Named_Statement__create_kind(PARSED_STATEMENT_KIND__STRUCT, sizeof(Parsed_Struct_Statement), location, name);
    statement->first_member = null;
    return statement;
}

typedef struct Parsed_Variable_Statement {
    Parsed_Named_Statement super;
    Parsed_Type* type;
    Parsed_Expression* expression;
    bool is_external;
} Parsed_Variable_Statement;

Parsed_Variable_Statement* Parsed_Variable_Statement__create(Source_Location* location, Token* name, Parsed_Type* type, bool is_external) {
    Parsed_Variable_Statement* statement = (Parsed_Variable_Statement*) Parsed_Named_Statement__create_kind(PARSED_STATEMENT_KIND__VARIABLE, sizeof(Parsed_Variable_Statement), location, name);
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
    Parsed_While_Statement* statement = (Parsed_While_Statement*) Parsed_Statement__create_kind(PARSED_STATEMENT_KIND__WHILE, sizeof(Parsed_While_Statement), location);
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
    Parsed_Statements* statements = (Parsed_Statements*) malloc(sizeof(Parsed_Statements));
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
    Parsed_Source* compilation_unit = (Parsed_Source*) malloc(sizeof(Parsed_Source));
    compilation_unit->statements = Parsed_Statements__create(true);
    return compilation_unit;
}

#pragma endregion
#pragma region Parser

typedef struct Parser {
    Scanner* scanner;
    Parsed_Source* compilation_unit;
    uint16_t current_identation;
} Parser;

void Parser__error(Parser* self, String* message) {
    Token__error(self->scanner->current_token, message);
}

void Parser__warning(Parser* self, String* message) {
    Token__warning(self->scanner->current_token, message);
}

Token* Parser__peek_token(Parser* self, uint8_t offset) {
    return Scanner__peek_token(self->scanner, offset);
}

typedef bool Token_Is_Function(Token* self);

bool Parser__matches_three(Parser* self, Token_Is_Function* first_is, bool first_required, Token_Is_Function* second_is, bool second_required, Token_Is_Function* third_is) {
    uint8_t peek_offset = (uint8_t) 0;
    if (first_is(Parser__peek_token(self, peek_offset))) {
        peek_offset = peek_offset + (uint8_t) 1;
    } else if (first_required) {
        return false;
    }
    if (second_is != null) {
        if (second_is(Parser__peek_token(self, peek_offset))) {
            peek_offset = peek_offset + (uint8_t) 1;
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
    Parser__error(self, String__create_from("Unexpected token"));
    abort();
}

void Parser__consume_comment(Parser* self) {
    Parser__consume_token(self, Token__is_comment);
}

void Parser__consume_space(Parser* self, uint16_t count) {
    if (Parser__matches_one(self, Token__is_space)) {
        Space_Token* token = (Space_Token*) Parser__consume_token(self, Token__is_space);
        if (token->count != count) {
            String* message = String__append_cstring(String__append_int16_t(String__append_cstring(String__append_int16_t(String__create_from("Consumed "), (int16_t) token->count), " spaces where "), (int16_t) count), " were expected");
            Token__warning((Token*) token, message);
            String__delete(message);
        }
    } else if (count > (uint16_t) 0) {
        String* message = String__append_cstring(String__append_int16_t(String__append_cstring(String__append_int16_t(String__create_from("Consumed "), (int16_t) 0), " spaces where "), (int16_t) count), " were expected");
        Parser__warning(self, message);
        String__delete(message);
    }
}

void Parser__consume_end_of_line(Parser* self) {
    if (Parser__matches_two(self, Token__is_space, false, Token__is_comment)) {
        Parser__consume_space(self, (uint16_t) 1);
        Parser__consume_comment(self);
    } else {
        Parser__consume_space(self, (uint16_t) 0);
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
            Parser__consume_space(self, self->current_identation * (uint16_t) 4);
            Parser__consume_comment(self);
        } else {
            Parser__consume_space(self, (uint16_t) 0);
        }
        Parser__consume_token(self, Token__is_end_of_line);
        return true;
    }
    if (Parser__matches_two(self, Token__is_space, false, Token__is_hash)) {
        // Preprocessor directives are ignored and treated as empty lines
        Parser__consume_space(self, (uint16_t) 0);
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
        Parser__consume_space(self, (uint16_t) 0);
        Parsed_Expression* expression = Parser__parse_expression(self);
        Parser__consume_space(self, (uint16_t) 0);
        Parser__consume_token(self, Token__is_closing_paren);
        return (Parsed_Expression*) Parsed_Group_Expression__create(location, expression);
    }
    Parser__error(self, String__create_from("Unsupported primary expression"));
    abort();
}

// access_expression
//      | primary_expression ( "." IDENTIFIER | "->" IDENTIFIER | "(" ( expression ( "," expression )*)? ")" | "[" expression "]" )*
Parsed_Expression* Parser__parse_access_expression(Parser* self) {
    Parsed_Expression* expression = Parser__parse_primary_expression(self);
    while (true) {
        Parsed_Expression* old_expression = expression;
        if (Parser__matches_two(self, Token__is_space, false, Token__is_dot) || Parser__matches_three(self, Token__is_space, false, Token__is_minus, true, Token__is_greater_than)) {
            Parser__consume_space(self, (uint16_t) 0);
            if (Parser__matches_one(self, Token__is_dot)) {
                Parser__consume_token(self, Token__is_dot);
            } else {
                Parser__consume_token(self, Token__is_minus);
                Parser__consume_token(self, Token__is_greater_than);
            }
            Parser__consume_space(self, (uint16_t) 0);
            Token* name = Parser__consume_token(self, Token__is_identifier);
            expression = (Parsed_Expression*) Parsed_Member_Access_Expression__create(expression, name);
        }
        if (Parser__matches_two(self, Token__is_space, false, Token__is_opening_paren)) {
            Parser__consume_space(self, (uint16_t) 0);
            Parser__consume_token(self, Token__is_opening_paren);
            Parser__consume_space(self, (uint16_t) 0);
            Parsed_Call_Expression* call_expression = Parsed_Call_Expression__create(expression);
            if (!Parser__matches_one(self, Token__is_closing_paren)) {
                Parsed_Call_Argument* last_argument = Parsed_Call_Argument__create(Parser__parse_expression(self));
                call_expression->first_argument = last_argument;
                Parser__consume_space(self, (uint16_t) 0);
                while (Parser__matches_one(self, Token__is_comma)) {
                    Parser__consume_token(self, Token__is_comma);
                    Parser__consume_space(self, (uint16_t) 1);
                    Parsed_Call_Argument* argument = Parsed_Call_Argument__create(Parser__parse_expression(self));
                    last_argument->next_argument = argument;
                    last_argument = argument;
                    Parser__consume_space(self, (uint16_t) 0);
                }
            }
            expression = (Parsed_Expression*) call_expression;
            Parser__consume_token(self, Token__is_closing_paren);
        }
        if (Parser__matches_two(self, Token__is_space, false, Token__is_opening_bracket)) {
            Parser__consume_space(self, (uint16_t) 0);
            Parser__consume_token(self, Token__is_opening_bracket);
            Parser__consume_space(self, (uint16_t) 0);
            Parsed_Expression* index_expression = Parser__parse_expression(self);
            Parser__consume_space(self, (uint16_t) 0);
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
        Parser__consume_space(self, (uint16_t) 0);
        Parsed_Expression* expression = Parser__parse_unary_expression(self);
        return (Parsed_Expression*) Parsed_Minus_Expression__create(location, expression);
    }
    if (Parser__matches_one(self, Token__is_exclamation_mark)) {
        Source_Location* location = Parser__consume_token(self, Token__is_exclamation_mark)->location;
        Parser__consume_space(self, (uint16_t) 0);
        Parsed_Expression* expression = Parser__parse_unary_expression(self);
        return (Parsed_Expression*) Parsed_Not_Expression__create(location, expression);
    }
    if (Parser__matches_one(self, Token__is_ampersand)) {
        Source_Location* location = Parser__consume_token(self, Token__is_ampersand)->location;
        Parser__consume_space(self, (uint16_t) 0);
        Parsed_Expression* expression = Parser__parse_unary_expression(self);
        return (Parsed_Expression*) Parsed_Address_Of_Expression__create(location, expression);
    }
    if (Parser__matches_three(self, Token__is_opening_paren, true, Token__is_space, false, Token__is_identifier)) {
        uint8_t peek_offset = (uint8_t) 1;
        if (Token__is_space(Parser__peek_token(self, peek_offset))) {
            peek_offset = peek_offset + (uint8_t) 1;
        }
        if (Token__is_identifier(Parser__peek_token(self, peek_offset))) {
            peek_offset = peek_offset + (uint8_t) 1;
            if (Token__is_space(Parser__peek_token(self, peek_offset))) {
                peek_offset = peek_offset + (uint8_t) 1;
            }
            while (Token__is_asterisk(Parser__peek_token(self, peek_offset))) {
                peek_offset = peek_offset + (uint8_t) 1;
                if (Token__is_space(Parser__peek_token(self, peek_offset))) {
                    peek_offset = peek_offset + (uint8_t) 1;
                }
            }
            if (Token__is_closing_paren(Parser__peek_token(self, peek_offset))) {
                peek_offset = peek_offset + (uint8_t) 1;
                if (Token__is_space(Parser__peek_token(self, peek_offset))) {
                    peek_offset = peek_offset + (uint8_t) 1;
                }
                Source_Location* location = Parser__consume_token(self, Token__is_opening_paren)->location;
                Parser__consume_space(self, (uint16_t) 0);
                Parsed_Type* type = Parser__parse_type(self);
                Parser__consume_space(self, (uint16_t) 0);
                Parser__consume_token(self, Token__is_closing_paren);
                Parser__consume_space(self, (uint16_t) 1);
                Parsed_Expression* expression = Parser__parse_unary_expression(self);
                return (Parsed_Expression*) Parsed_Cast_Expression__create(location, expression, type);
            }
        }
    }
    if (Parser__matches_one(self, Token__is_sizeof)) {
        Source_Location* location = Parser__consume_token(self, Token__is_sizeof)->location;
        Parser__consume_space(self, (uint16_t) 0);
        Parser__consume_token(self, Token__is_opening_paren);
        Parser__consume_space(self, (uint16_t) 0);
        Parsed_Type* type = Parser__parse_type(self);
        Parser__consume_space(self, (uint16_t) 0);
        Parser__consume_token(self, Token__is_closing_paren);
        return (Parsed_Expression*) Parsed_Sizeof_Expression__create(location, type);
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
        Parser__consume_space(self, (uint16_t) 1);
        if (Parser__matches_one(self, Token__is_asterisk)) {
            Parser__consume_token(self, Token__is_asterisk);
            Parser__consume_space(self, (uint16_t) 1);
            Parsed_Expression* right_expression = Parser__parse_unary_expression(self);
            expression = (Parsed_Expression*) Parsed_Multiply_Expression__create(expression, right_expression);
        } else if (Parser__matches_one(self, Token__is_slash)) {
            Parser__consume_token(self, Token__is_slash);
            Parser__consume_space(self, (uint16_t) 1);
            Parsed_Expression* right_expression = Parser__parse_unary_expression(self);
            expression = (Parsed_Expression*) Parsed_Divide_Expression__create(expression, right_expression);
        } else {
            Parser__consume_token(self, Token__is_percent);
            Parser__consume_space(self, (uint16_t) 1);
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
        Parser__consume_space(self, (uint16_t) 1);
        if (Parser__matches_one(self, Token__is_plus)) {
            Parser__consume_token(self, Token__is_plus);
            Parser__consume_space(self, (uint16_t) 1);
            Parsed_Expression* right_expression = Parser__parse_multiplication_expression(self);
            expression = (Parsed_Expression*) Parsed_Add_Expression__create(expression, right_expression);
        } else {
            Parser__consume_token(self, Token__is_minus);
            Parser__consume_space(self, (uint16_t) 1);
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
        Parser__consume_space(self, (uint16_t) 1);
        Parser__consume_token(self, Token__is_less_than);
        if (Parser__matches_one(self, Token__is_equals)) {
            Parser__consume_token(self, Token__is_equals);
            Parser__consume_space(self, (uint16_t) 1);
            Parsed_Expression* right_expression = Parser__parse_addition_expression(self);
            expression = (Parsed_Expression*) Parsed_Less_Or_Equals_Expression__create(expression, right_expression);
        } else {
            Parser__consume_space(self, (uint16_t) 1);
            Parsed_Expression* right_expression = Parser__parse_addition_expression(self);
            expression = (Parsed_Expression*) Parsed_Less_Expression__create(expression, right_expression);
        }
    } else if (Parser__matches_two(self, Token__is_space, false, Token__is_greater_than)) {
        Parser__consume_space(self, (uint16_t) 1);
        Parser__consume_token(self, Token__is_greater_than);
        if (Parser__matches_one(self, Token__is_equals)) {
            Parser__consume_token(self, Token__is_equals);
            Parser__consume_space(self, (uint16_t) 1);
            Parsed_Expression* right_expression = Parser__parse_addition_expression(self);
            expression = (Parsed_Expression*) Parsed_Greater_Or_Equals_Expression__create(expression, right_expression);
        } else {
            Parser__consume_space(self, (uint16_t) 1);
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
        Parser__consume_space(self, (uint16_t) 1);
        Parser__consume_token(self, Token__is_equals);
        Parser__consume_token(self, Token__is_equals);
        Parser__consume_space(self, (uint16_t) 1);
        Parsed_Expression* right_expression = Parser__parse_comparison_expression(self);
        expression = (Parsed_Expression*) Parsed_Equals_Expression__create(expression, right_expression);
    } else if (Parser__matches_three(self, Token__is_space, false, Token__is_exclamation_mark, true, Token__is_equals)) {
        Parser__consume_space(self, (uint16_t) 1);
        Parser__consume_token(self, Token__is_exclamation_mark);
        Parser__consume_token(self, Token__is_equals);
        Parser__consume_space(self, (uint16_t) 1);
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
        Parser__consume_space(self, (uint16_t) 1);
        Parser__consume_token(self, Token__is_ampersand);
        Parser__consume_token(self, Token__is_ampersand);
        Parser__consume_space(self, (uint16_t) 1);
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
        Parser__consume_space(self, (uint16_t) 1);
        Parser__consume_token(self, Token__is_vertical_bar);
        Parser__consume_token(self, Token__is_vertical_bar);
        Parser__consume_space(self, (uint16_t) 1);
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
    Parser__consume_space(self, (uint16_t) 1);
    Parser__consume_token(self, Token__is_struct);
    Parser__consume_space(self, (uint16_t) 1);
    Token* local_name = Parser__consume_token(self, Token__is_identifier);
    Parsed_Struct_Statement* struct_statement = Parsed_Struct_Statement__create(location, local_name);
    Parser__consume_space(self, (uint16_t) 1);
    if (!Parser__matches_one(self, Token__is_identifier)) {
        Parsed_Struct_Member* last_member = null;
        Parser__consume_token(self, Token__is_opening_brace);
        Parser__consume_end_of_line(self);
        while (!Parser__matches_two(self, Token__is_space, false, Token__is_closing_brace)) {
            Parser__consume_space(self, (self->current_identation + (uint16_t) 1) * (uint16_t) 4);
            Parsed_Type* type = Parser__parse_type(self);
            Parser__consume_space(self, (uint16_t) 1);
            Token* name = Parser__consume_token(self, Token__is_identifier);
            Parser__consume_space(self, (uint16_t) 0);
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
        Parser__consume_space(self, (uint16_t) 0);
        Parser__consume_token(self, Token__is_closing_brace);
        Parser__consume_space(self, (uint16_t) 1);
    }
    Token* final_name = Parser__consume_token(self, Token__is_identifier);
    if (!String__equals_string(final_name->lexeme, local_name->lexeme)) {
        Token__error(final_name, String__append_string(String__create_from("Final struct name doesn't match the local name: "), local_name->lexeme));
        abort();
    }
    Parser__consume_space(self, (uint16_t) 0);
    Parser__consume_token(self, Token__is_semicolon);
    return (Parsed_Statement*) struct_statement;
}

// enum
//      | "typedef" "enum" IDENTIFIER "{" ( IDENTIFIER "," )* "}" IDENTIFIER ";"
Parsed_Statement* Parser__parse_enum(Parser* self) {
    Source_Location* location = Parser__consume_token(self, Token__is_typedef)->location;
    Parser__consume_space(self, (uint16_t) 1);
    Parser__consume_token(self, Token__is_enum);
    Parser__consume_space(self, (uint16_t) 1);
    Token* local_name = Parser__consume_token(self, Token__is_identifier);
    Parsed_Enum_Statement* enum_statement = Parsed_Enum_Statement__create(location, local_name);
    Parser__consume_space(self, (uint16_t) 1);
    Parser__consume_token(self, Token__is_opening_brace);
    Parser__consume_end_of_line(self);
    self->current_identation = self->current_identation + (uint16_t) 1;
    Parsed_Enum_Member* last_member = null;
    while (!Parser__matches_two(self, Token__is_space, false, Token__is_closing_brace)) {
        while (Parser__consume_empty_line(self)) {
            // ignored
        }
        Parser__consume_space(self, self->current_identation * (uint16_t) 4);
        Token* name = Parser__consume_token(self, Token__is_identifier);
        Parser__consume_space(self, (uint16_t) 0);
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
    self->current_identation = self->current_identation - (uint16_t) 1;
    Parser__consume_space(self, self->current_identation * (uint16_t) 4);
    Parser__consume_token(self, Token__is_closing_brace);
    Parser__consume_space(self, (uint16_t) 1);
    Token* final_name = Parser__consume_token(self, Token__is_identifier);
    if (!String__equals_string(final_name->lexeme, local_name->lexeme)) {
        Token__error(final_name, String__append_string(String__create_from("Final enum name doesn't match the local name: "), local_name->lexeme));
        abort();
    }
    Parser__consume_space(self, (uint16_t) 0);
    Parser__consume_token(self, Token__is_semicolon);
    return (Parsed_Statement*) enum_statement;
}

// type
//      | "const"? "struct"? IDENTIFIER "*"*
Parsed_Type* Parser__parse_type(Parser* self) {
    Token* const_token = null;
    if (Parser__matches_one(self, Token__is_const)) {
        const_token = Parser__consume_token(self, Token__is_const);
        Parser__consume_space(self, (uint16_t) 1);
    }
    Token* struct_token = null;
    if (Parser__matches_one(self, Token__is_struct)) {
        struct_token = Parser__consume_token(self, Token__is_struct);
        Parser__consume_space(self, (uint16_t) 1);
    }
    Token* name = Parser__consume_token(self, Token__is_identifier);
    Parsed_Type* type = Parsed_Named_Type__create(name);
    if (struct_token != null) {
        type = Parsed_Struct_Type__create(struct_token->location, type);
    }
    while (Parser__matches_two(self, Token__is_space, false, Token__is_asterisk)) {
        Parser__consume_space(self, (uint16_t) 0);
        Parser__consume_token(self, Token__is_asterisk);
        type = Parsed_Pointer_Type__create(type);
    }
    if (const_token != null) {
        type = Parsed_Const_Type__create(const_token->location, type);
    }
    return type;
}

// type_alias
//      | "typedef" type IDENTIFIER "(" ( type IDENTIFIER ( "," type IDENTIFIER )* )? ")" ";"
Parsed_Statement* Parser__parse_type_alias(Parser* self) {
    Source_Location* location = Parser__consume_token(self, Token__is_typedef)->location;
    Parser__consume_space(self, (uint16_t) 1);
    Parsed_Type* return_type = Parser__parse_type(self);
    Parser__consume_space(self, (uint16_t) 1);
    Token* name = Parser__consume_token(self, Token__is_identifier);
    Parser__consume_space(self, (uint16_t) 0);
    Parser__consume_token(self, Token__is_opening_paren);
    Parsed_Function_Type_Parameter* first_parameter = null;
    if (!Parser__matches_two(self, Token__is_space, false, Token__is_closing_paren)) {
        Parser__consume_space(self, (uint16_t) 0);
        Parsed_Type* parameter_type = Parser__parse_type(self);
        Parser__consume_space(self, (uint16_t) 1);
        Token* parameter_name = Parser__consume_token(self, Token__is_identifier);
        first_parameter = Parsed_Function_Type_Parameter__create(parameter_name, parameter_type);
        Parsed_Function_Type_Parameter* last_parameter = first_parameter;
        while (Parser__matches_two(self, Token__is_space, false, Token__is_comma)) {
            Parser__consume_space(self, (uint16_t) 0);
            Parser__consume_token(self, Token__is_comma);
            Parser__consume_space(self, (uint16_t) 1);
            Parsed_Type* parameter_type = Parser__parse_type(self);
            Parser__consume_space(self, (uint16_t) 1);
            Token* parameter_name = Parser__consume_token(self, Token__is_identifier);
            Parsed_Function_Type_Parameter* parameter = Parsed_Function_Type_Parameter__create(parameter_name, parameter_type);
            last_parameter->next_parameter = parameter;
            last_parameter = parameter;
        }
    }
    Parser__consume_space(self, (uint16_t) 0);
    Parser__consume_token(self, Token__is_closing_paren);
    Parser__consume_space(self, (uint16_t) 0);
    Parser__consume_token(self, Token__is_semicolon);
    return Parsed_Function_Type_Statement__create(location, name, first_parameter, return_type);
}

// variable
//      | "extern"? type IDENTIFIER ( "=" expression )? ";"
Parsed_Statement* Parser__parse_variable(Parser* self) {
    bool is_external;
    Source_Location* location;
    if (Parser__matches_one(self, Token__is_extern)) {
        is_external = true;
        location = Parser__consume_token(self, Token__is_extern)->location;
        Parser__consume_space(self, (uint16_t) 1);
    } else {
        is_external = false;
        location = Parser__peek_token(self, (uint8_t) 0)->location;
    }
    Parsed_Type* type = Parser__parse_type(self);
    Parser__consume_space(self, (uint16_t) 1);
    Token* name = Parser__consume_token(self, Token__is_identifier);
    Parsed_Variable_Statement* variable_statement = Parsed_Variable_Statement__create(location, name, type, is_external);
    if (Parser__matches_two(self, Token__is_space, false, Token__is_equals)) {
        Parser__consume_space(self, (uint16_t) 1);
        Parser__consume_token(self, Token__is_equals);
        Parser__consume_space(self, (uint16_t) 1);
        variable_statement->expression = Parser__parse_expression(self);
    }
    Parser__consume_space(self, (uint16_t) 0);
    Parser__consume_token(self, Token__is_semicolon);
    return (Parsed_Statement*) variable_statement;
}

Parsed_Function_Parameter* Parser__parse_function_parameter(Parser* self) {
    Parsed_Type* type = Parser__parse_type(self);
    Parser__consume_space(self, (uint16_t) 1);
    Token* name = Parser__consume_token(self, Token__is_identifier);
    return Parsed_Function_Parameter__create(name, type);
}

Parsed_Function_Parameter* Parser__parse_function_parameters(Parser* self) {
    Parsed_Function_Parameter* first_parameter = null;
    if (!Parser__matches_two(self, Token__is_space, false, Token__is_closing_paren)) {
        Parser__consume_space(self, (uint16_t) 0);
        first_parameter = Parser__parse_function_parameter(self);
        Parsed_Function_Parameter* last_parameter = first_parameter;
        while (Parser__matches_two(self, Token__is_space, false, Token__is_comma)) {
            Parser__consume_space(self, (uint16_t) 0);
            Parser__consume_token(self, Token__is_comma);
            Parser__consume_space(self, (uint16_t) 1);
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
    self->current_identation = self->current_identation + (uint16_t) 1;
    Parser__parse_statements(self, statements);
    self->current_identation = self->current_identation - (uint16_t) 1;
    Parser__consume_space(self, self->current_identation * (uint16_t) 4);
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
        Parser__consume_space(self, (uint16_t) 1);
    } else {
        is_external = false;
        location = Parser__peek_token(self, (uint8_t) 0)->location;
    }
    Parsed_Type* return_type = Parser__parse_type(self);
    Parser__consume_space(self, (uint16_t) 1);
    Token* name = Parser__consume_token(self, Token__is_identifier);
    Parser__consume_space(self, (uint16_t) 0);
    Parser__consume_token(self, Token__is_opening_paren);
    Parsed_Function_Parameter* first_parameter = Parser__parse_function_parameters(self);
    Parser__consume_space(self, (uint16_t) 0);
    Parser__consume_token(self, Token__is_closing_paren);
    Parsed_Statements* statements = null;
    if (Parser__matches_two(self, Token__is_space, false, Token__is_opening_brace)) {
        Parser__consume_space(self, (uint16_t) 1);
        Parser__consume_token(self, Token__is_opening_brace);
        Parser__consume_end_of_line(self);
        statements = Parsed_Statements__create(false);
        self->current_identation = self->current_identation + (uint16_t) 1;
        Parser__parse_statements(self, statements);
        self->current_identation = self->current_identation - (uint16_t) 1;
        Parser__consume_space(self, self->current_identation * (uint16_t) 4);
        Parser__consume_token(self, Token__is_closing_brace);
    } else {
        Parser__consume_space(self, (uint16_t) 0);
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
        Parser__consume_space(self, (uint16_t) 1);
        expression = Parser__parse_expression(self);
    }
    Parser__consume_space(self, (uint16_t) 0);
    Parser__consume_token(self, Token__is_semicolon);
    return Parsed_Return_Statement__create(location, expression);
}

// break
//      | "break" ";"
Parsed_Statement* Parser__parse_break_statement(Parser* self) {
    Source_Location* location = Parser__consume_token(self, Token__is_break)->location;
    Parser__consume_space(self, (uint16_t) 0);
    Parser__consume_token(self, Token__is_semicolon);
    return Parsed_Break_Statement__create(location);
}

// if
//      | "if" "(" expression ")" statement ( "else" statement )?
Parsed_Statement* Parser__parse_if_statement(Parser* self) {
    Source_Location* location = Parser__consume_token(self, Token__is_if)->location;
    Parser__consume_space(self, (uint16_t) 1);
    Parser__consume_token(self, Token__is_opening_paren);
    Parser__consume_space(self, (uint16_t) 0);
    Parsed_Expression* condition_expression = Parser__parse_expression(self);
    Parser__consume_space(self, (uint16_t) 0);
    Parser__consume_token(self, Token__is_closing_paren);
    Parser__consume_space(self, (uint16_t) 1);
    Parsed_Statement* true_statement = (Parsed_Statement*) Parser__parse_block_statement(self);
    Parsed_Statement* false_statement = null;
    if (Parser__matches_two(self, Token__is_space, false, Token__is_else)) {
        Parser__consume_space(self, (uint16_t) 1);
        Parser__consume_token(self, Token__is_else);
        Parser__consume_space(self, (uint16_t) 1);
        if (Parser__matches_one(self, Token__is_if)) {
            false_statement = Parser__parse_if_statement(self);
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
    Parser__consume_space(self, (uint16_t) 1);
    Parser__consume_token(self, Token__is_opening_paren);
    Parser__consume_space(self, (uint16_t) 0);
    Parsed_Expression* condition_expression = Parser__parse_expression(self);
    Parser__consume_space(self, (uint16_t) 0);
    Parser__consume_token(self, Token__is_closing_paren);
    Parser__consume_space(self, (uint16_t) 1);
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
    Parser__consume_space(self, self->current_identation * (uint16_t) 4);

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
        uint8_t peek_offset = (uint8_t) 0;
        if (Token__is_extern(Parser__peek_token(self, peek_offset))) {
            peek_offset = peek_offset + (uint8_t) 1;
            if (Token__is_space(Parser__peek_token(self, peek_offset))) {
                peek_offset = peek_offset + (uint8_t) 1;
            }
        }
        if (Token__is_const(Parser__peek_token(self, peek_offset))) {
            peek_offset = peek_offset + (uint8_t) 1;
            if (Token__is_space(Parser__peek_token(self, peek_offset))) {
                peek_offset = peek_offset + (uint8_t) 1;
            }
        }
        if (Token__is_identifier(Parser__peek_token(self, peek_offset))) {
            peek_offset = peek_offset + (uint8_t) 1;
            if (Token__is_space(Parser__peek_token(self, peek_offset))) {
                peek_offset = peek_offset + (uint8_t) 1;
            }
            while (Token__is_asterisk(Parser__peek_token(self, peek_offset))) {
                peek_offset = peek_offset + (uint8_t) 1;
                if (Token__is_space(Parser__peek_token(self, peek_offset))) {
                    peek_offset = peek_offset + (uint8_t) 1;
                }
            }
            if (Token__is_identifier(Parser__peek_token(self, peek_offset))) {
                peek_offset = peek_offset + (uint8_t) 1;
                if (Token__is_space(Parser__peek_token(self, peek_offset))) {
                    peek_offset = peek_offset + (uint8_t) 1;
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
        Parser__consume_space(self, (uint16_t) 1);
        Parser__consume_token(self, Token__is_equals);
        Parser__consume_space(self, (uint16_t) 1);
        Parsed_Expression* value_expression = Parser__parse_expression(self);
        Parser__consume_space(self, (uint16_t) 0);
        Parser__consume_token(self, Token__is_semicolon);
        return (Parsed_Statement*) Parsed_Assignment_Statement__create(expresion, value_expression);
    }
    Parser__consume_space(self, (uint16_t) 0);
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

    Token* last_token = Parser__peek_token(self, (uint8_t) 0);
    if (!Token__is_end_of_file(last_token)) {
        Parser__error(self, String__create_from("Scanner didn't reach end of file"));
        abort();
    } else if (last_token->location->column != (uint16_t) 1) {
        Parser__warning(self, String__create_from("No new line at the end of file"));
    }

    self->scanner = other_scanner;
}

Parsed_Source* parse(Source* source) {
    Parser parser;
    parser.scanner = null;
    parser.compilation_unit = Parsed_Compilation_Unit__create();
    parser.current_identation = (uint16_t) 0;

    Parser__parse_source(&parser, source);

    return parser.compilation_unit;
}

#pragma endregion
#pragma region Checked Types

typedef enum Checked_Type_Kind {
    // Builtins
    CHECKED_TYPE_KIND__BOOL,
    CHECKED_TYPE_KIND__CHAR,
    CHECKED_TYPE_KIND__INT16_T,
    CHECKED_TYPE_KIND__INT32_T,
    CHECKED_TYPE_KIND__INT64_T,
    CHECKED_TYPE_KIND__INT8_T,
    CHECKED_TYPE_KIND__SIZE_T,
    CHECKED_TYPE_KIND__UINT16_T,
    CHECKED_TYPE_KIND__UINT32_T,
    CHECKED_TYPE_KIND__UINT64_T,
    CHECKED_TYPE_KIND__UINT8_T,
    CHECKED_TYPE_KIND__VOID,
    CHECKED_TYPE_KIND__NULL, // Pseudo type
    // Defined
    CHECKED_TYPE_KIND__ENUM,
    CHECKED_TYPE_KIND__FUNCTION,
    CHECKED_TYPE_KIND__STRUCT,
    // Dynamic
    CHECKED_TYPE_KIND__CONST,
    CHECKED_TYPE_KIND__POINTER,
} Checked_Type_Kind;

typedef struct Checked_Type {
    Checked_Type_Kind kind;
    Source_Location* location;
    struct Checked_Type* next_type;
} Checked_Type;

Checked_Type* Checked_Type__create_kind(Checked_Type_Kind kind, size_t kind_size, Source_Location* location) {
    Checked_Type* type = (Checked_Type*) malloc(kind_size);
    type->kind = kind;
    type->location = location;
    type->next_type = null;
    return type;
}

bool Checked_Type__equals(Checked_Type* self, Checked_Type* other_type);

String* String__append_checked_type(String* self, Checked_Type* type);

void Checked_Type__expect_same_type(Checked_Type* self, Checked_Type* other_type, Source_Location* location) {
    if (self->kind == CHECKED_TYPE_KIND__POINTER && other_type->kind == CHECKED_TYPE_KIND__NULL) {
        return;
    }
    if (!Checked_Type__equals(self, other_type)) {
        String* message = String__create_from("Unexpected type. Got \"");
        String__append_checked_type(message, other_type);
        String__append_cstring(message, "\" instead of \"");
        String__append_checked_type(message, self);
        String__append_char(message, '"');
        Source_Location__error(location, message);
        abort();
    }
}

bool Checked_Type__is_scalar_type(Checked_Type* self) {
    if (self->kind == CHECKED_TYPE_KIND__CHAR) {
        return true;
    } else if (self->kind == CHECKED_TYPE_KIND__INT16_T) {
        return true;
    } else if (self->kind == CHECKED_TYPE_KIND__INT32_T) {
        return true;
    } else if (self->kind == CHECKED_TYPE_KIND__INT64_T) {
        return true;
    } else if (self->kind == CHECKED_TYPE_KIND__INT8_T) {
        return true;
    } else if (self->kind == CHECKED_TYPE_KIND__SIZE_T) {
        return true;
    } else if (self->kind == CHECKED_TYPE_KIND__UINT16_T) {
        return true;
    } else if (self->kind == CHECKED_TYPE_KIND__UINT32_T) {
        return true;
    } else if (self->kind == CHECKED_TYPE_KIND__UINT64_T) {
        return true;
    } else if (self->kind == CHECKED_TYPE_KIND__UINT8_T) {
        return true;
    } else if (self->kind == CHECKED_TYPE_KIND__ENUM) {
        return true;
    }
    return false;
}

void Checked_Type__expect_scalar_type(Checked_Type* self, Source_Location* location) {
    if (!Checked_Type__is_scalar_type(self)) {
        String* message = String__create_from("Type \"");
        String__append_checked_type(message, self);
        String__append_cstring(message, "\" is not a scalar type");
        Source_Location__error(location, message);
        abort();
    }
}

typedef struct Checked_Named_Type {
    Checked_Type super;
    String* name;
} Checked_Named_Type;

Checked_Named_Type* Checked_Named_Type__create_kind(Checked_Type_Kind kind, size_t kind_size, Source_Location* location, String* name) {
    Checked_Named_Type* type = (Checked_Named_Type*) Checked_Type__create_kind(kind, kind_size, location);
    type->name = name;
    return type;
}

typedef struct Checked_Const_Type {
    Checked_Type super;
    Checked_Type* other_type;
} Checked_Const_Type;

Checked_Const_Type* Checked_Const_Type__create(Source_Location* location, Checked_Type* other_type) {
    Checked_Const_Type* type = (Checked_Const_Type*) Checked_Type__create_kind(CHECKED_TYPE_KIND__CONST, sizeof(Checked_Const_Type), location);
    type->other_type = other_type;
    return type;
}

bool Checked_Const_Type__equals(Checked_Const_Type* self, Checked_Type* other_type) {
    if (other_type->kind != self->super.kind) {
        return false;
    }
    return Checked_Type__equals(self->other_type, ((Checked_Const_Type*) other_type)->other_type);
}

typedef struct Checked_Enum_Member {
    Source_Location* location;
    String* name;
    struct Checked_Enum_Member* next_member;
} Checked_Enum_Member;

Checked_Enum_Member* Checked_Enum_Member__create(Source_Location* location, String* name) {
    Checked_Enum_Member* member = (Checked_Enum_Member*) malloc(sizeof(Checked_Enum_Member));
    member->location = location;
    member->name = name;
    member->next_member = null;
    return member;
}

typedef struct Checked_Enum_Type {
    Checked_Named_Type super;
    Checked_Enum_Member* first_member;
} Checked_Enum_Type;

Checked_Enum_Type* Checked_Enum_Type__create(Source_Location* location, String* name) {
    Checked_Enum_Type* type = (Checked_Enum_Type*) Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__ENUM, sizeof(Checked_Enum_Type), location, name);
    type->first_member = null;
    return type;
}

Checked_Enum_Member* Checked_Enum_Type__find_member(Checked_Enum_Type* self, String* name) {
    Checked_Enum_Member* member = self->first_member;
    while (member != null) {
        if (String__equals_string(name, member->name)) {
            break;
        }
        member = member->next_member;
    }
    return member;
}

typedef struct Checked_Function_Parameter {
    Source_Location* location;
    String* name;
    Checked_Type* type;
    struct Checked_Function_Parameter* next_parameter;
} Checked_Function_Parameter;

Checked_Function_Parameter* Checked_Function_Parameter__create(Source_Location* location, String* name, Checked_Type* type) {
    Checked_Function_Parameter* parameter = (Checked_Function_Parameter*) malloc(sizeof(Checked_Function_Parameter));
    parameter->location = location;
    parameter->name = name;
    parameter->type = type;
    parameter->next_parameter = null;
    return parameter;
}

typedef struct Checked_Function_Type {
    Checked_Named_Type super;
    Checked_Type* return_type;
    Checked_Function_Parameter* first_parameter;
} Checked_Function_Type;

Checked_Function_Type* Checked_Function_Type__create(Source_Location* location, String* name, Checked_Type* return_type) {
    Checked_Function_Type* type = (Checked_Function_Type*) Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__FUNCTION, sizeof(Checked_Function_Type), location, name);
    type->return_type = return_type;
    type->first_parameter = null;
    return type;
}

bool Checked_Function_Type__equals(Checked_Function_Type* self, Checked_Type* other_type) {
    if (other_type->kind != self->super.super.kind) {
        return false;
    }
    Checked_Function_Type* function_type = (Checked_Function_Type*) other_type;
    if (!Checked_Type__equals(self->return_type, function_type->return_type)) {
        return false;
    }
    Checked_Function_Parameter* self_parameter = self->first_parameter;
    Checked_Function_Parameter* function_parameter = function_type->first_parameter;
    while (self_parameter != null && function_parameter != null) {
        if (!Checked_Type__equals(self_parameter->type, function_parameter->type)) {
            return false;
        }
        self_parameter = self_parameter->next_parameter;
        function_parameter = function_parameter->next_parameter;
    }
    if (self_parameter != null || function_parameter != null) {
        return false;
    }
    return true;
}

typedef struct Checked_Pointer_Type {
    Checked_Type super;
    Checked_Type* other_type;
} Checked_Pointer_Type;

Checked_Pointer_Type* Checked_Pointer_Type__create(Source_Location* location, Checked_Type* other_type) {
    Checked_Pointer_Type* type = (Checked_Pointer_Type*) Checked_Type__create_kind(CHECKED_TYPE_KIND__POINTER, sizeof(Checked_Pointer_Type), location);
    type->other_type = other_type;
    return type;
}

bool Checked_Pointer_Type__equals(Checked_Pointer_Type* self, Checked_Type* other_type) {
    if (other_type->kind != self->super.kind) {
        return false;
    }
    return Checked_Type__equals(self->other_type, ((Checked_Pointer_Type*) other_type)->other_type);
}

typedef struct Checked_Struct_Member {
    Source_Location* location;
    String* name;
    Checked_Type* type;
    struct Checked_Struct_Member* next_member;
} Checked_Struct_Member;

Checked_Struct_Member* Checked_Struct_Member__create(Source_Location* location, String* name, Checked_Type* type) {
    Checked_Struct_Member* member = (Checked_Struct_Member*) malloc(sizeof(Checked_Struct_Member));
    member->location = location;
    member->name = name;
    member->type = type;
    member->next_member = null;
    return member;
}

typedef struct Checked_Struct_Type {
    Checked_Named_Type super;
    Checked_Struct_Member* first_member;
} Checked_Struct_Type;

Checked_Struct_Type* Checked_Struct_Type__create(Source_Location* location, String* name) {
    Checked_Struct_Type* type = (Checked_Struct_Type*) Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__STRUCT, sizeof(Checked_Struct_Type), location, name);
    type->first_member = null;
    return type;
}

Checked_Struct_Member* Checked_Struct_Type__find_member(Checked_Struct_Type* self, String* name) {
    Checked_Struct_Member* member = self->first_member;
    while (member != null) {
        if (String__equals_string(name, member->name)) {
            break;
        }
        member = member->next_member;
    }
    return member;
}

bool Checked_Struct_Type__equals(Checked_Struct_Type* self, Checked_Type* other_type) {
    if (self->super.super.kind != other_type->kind) {
        return false;
    }
    return String__equals_string(self->super.name, ((Checked_Struct_Type*) other_type)->super.name);
}

bool Checked_Type__equals(Checked_Type* self, Checked_Type* other_type) {
    if (self == other_type) {
        return true;
    }
    if (self->kind != other_type->kind) {
        return false;
    }
    if (self->kind == CHECKED_TYPE_KIND__CONST) {
        return Checked_Const_Type__equals((Checked_Const_Type*) self, other_type);
    }
    if (self->kind == CHECKED_TYPE_KIND__FUNCTION) {
        return Checked_Function_Type__equals((Checked_Function_Type*) self, other_type);
    }
    if (self->kind == CHECKED_TYPE_KIND__POINTER) {
        return Checked_Pointer_Type__equals((Checked_Pointer_Type*) self, other_type);
    }
    if (self->kind == CHECKED_TYPE_KIND__STRUCT) {
        return Checked_Struct_Type__equals((Checked_Struct_Type*) self, other_type);
    }
    error(String__create_from("TODO: Compare unsupported type"));
    abort();
}

String* String__append_checked_type(String* self, Checked_Type* type) {
    if (type->kind <= CHECKED_TYPE_KIND__NULL) {
        Checked_Named_Type* named_type = (Checked_Named_Type*) type;
        String__append_string(self, named_type->name);
    } else if (type->kind == CHECKED_TYPE_KIND__STRUCT) {
        Checked_Struct_Type* struct_type = (Checked_Struct_Type*) type;
        String__append_cstring(self, "struct ");
        String__append_string(self, struct_type->super.name);
    } else if (type->kind == CHECKED_TYPE_KIND__FUNCTION) {
        Checked_Function_Type* function_type = (Checked_Function_Type*) type;
        String__append_checked_type(self, function_type->return_type);
        String__append_char(self, ' ');
        String__append_string(self, function_type->super.name);
        String__append_char(self, '(');
        Checked_Function_Parameter* function_parameter = function_type->first_parameter;
        while (function_parameter != null) {
            String__append_checked_type(self, function_parameter->type);
            String__append_char(self, ' ');
            String__append_string(self, function_parameter->name);
            function_parameter = function_parameter->next_parameter;
            if (function_parameter != null) {
                String__append_cstring(self, ", ");
            }
        }
        String__append_char(self, ')');
    } else if (type->kind == CHECKED_TYPE_KIND__ENUM) {
        Checked_Enum_Type* enum_type = (Checked_Enum_Type*) type;
        String__append_cstring(self, "enum ");
        String__append_string(self, enum_type->super.name);
    } else if (type->kind == CHECKED_TYPE_KIND__POINTER) {
        Checked_Pointer_Type* pointer_type = (Checked_Pointer_Type*) type;
        String__append_checked_type(self, pointer_type->other_type);
        String__append_char(self, '*');
    } else if (type->kind == CHECKED_TYPE_KIND__CONST) {
        Checked_Const_Type* const_type = (Checked_Const_Type*) type;
        String__append_cstring(self, "const ");
        String__append_checked_type(self, const_type->other_type);
    } else {
        Source_Location__error(type->location, String__create_from("Unsupported type"));
        abort();
    }
    return self;
}

void File__write_checked_type(File* self, Checked_Type* type);

void File__write_checked_function_parameter(File* self, Checked_Function_Parameter* parameter) {
    if (parameter->type->kind == CHECKED_TYPE_KIND__POINTER && ((Checked_Pointer_Type*) parameter->type)->other_type->kind == CHECKED_TYPE_KIND__FUNCTION) {
        Checked_Function_Type* function_type = (Checked_Function_Type*) ((Checked_Pointer_Type*) parameter->type)->other_type;
        File__write_checked_type(self, function_type->return_type);
        File__write_cstring(self, " (*");
        File__write_string(self, parameter->name);
        File__write_cstring(self, ")(");
        Checked_Function_Parameter* function_parameter = function_type->first_parameter;
        while (function_parameter != null) {
            File__write_checked_function_parameter(self, function_parameter);
            function_parameter = function_parameter->next_parameter;
            if (function_parameter != null) {
                File__write_cstring(self, ", ");
            }
        }
        File__write_char(self, ')');
    } else {
        File__write_checked_type(self, parameter->type);
        File__write_char(self, ' ');
        File__write_string(self, parameter->name);
    }
}

void File__write_checked_type(File* self, Checked_Type* type) {
    if (type == null) {
        File__write_cstring(self, "null");
    } else if (type->kind <= CHECKED_TYPE_KIND__NULL) {
        Checked_Named_Type* named_type = (Checked_Named_Type*) type;
        File__write_string(self, named_type->name);
    } else if (type->kind == CHECKED_TYPE_KIND__STRUCT) {
        Checked_Struct_Type* struct_type = (Checked_Struct_Type*) type;
        File__write_cstring(self, "struct ");
        File__write_string(self, struct_type->super.name);
    } else if (type->kind == CHECKED_TYPE_KIND__FUNCTION) {
        Checked_Function_Type* function_type = (Checked_Function_Type*) type;
        File__write_checked_type(self, function_type->return_type);
        File__write_char(self, ' ');
        File__write_string(self, function_type->super.name);
        File__write_char(self, '(');
        Checked_Function_Parameter* function_parameter = function_type->first_parameter;
        while (function_parameter != null) {
            File__write_checked_function_parameter(self, function_parameter);
            function_parameter = function_parameter->next_parameter;
            if (function_parameter != null) {
                File__write_cstring(self, ", ");
            }
        }
        File__write_char(self, ')');
    } else if (type->kind == CHECKED_TYPE_KIND__ENUM) {
        Checked_Enum_Type* enum_type = (Checked_Enum_Type*) type;
        File__write_cstring(self, "enum ");
        File__write_string(self, enum_type->super.name);
    } else if (type->kind == CHECKED_TYPE_KIND__POINTER) {
        Checked_Pointer_Type* pointer_type = (Checked_Pointer_Type*) type;
        File__write_checked_type(self, pointer_type->other_type);
        File__write_char(self, '*');
    } else if (type->kind == CHECKED_TYPE_KIND__CONST) {
        Checked_Const_Type* const_type = (Checked_Const_Type*) type;
        File__write_cstring(self, "const ");
        File__write_checked_type(self, const_type->other_type);
    } else {
        Source_Location__error(type->location, String__create_from("Unsupported type"));
        abort();
    }
}

#pragma endregion
#pragma region Checked Symbols

typedef enum Checked_Symbol_Kind {
    CHECKED_SYMBOL_KIND__ENUM_MEMBER,
    CHECKED_SYMBOL_KIND__FUNCTION,
    CHECKED_SYMBOL_KIND__FUNCTION_PARAMETER,
    CHECKED_SYMBOL_KIND__TYPE,
    CHECKED_SYMBOL_KIND__VARIABLE,
} Checked_Symbol_Kind;

typedef struct Checked_Symbol {
    Checked_Symbol_Kind kind;
    Source_Location* location;
    String* name;
    Checked_Type* type;
    struct Checked_Symbol* prev_symbol;
    struct Checked_Symbol* next_symbol;
} Checked_Symbol;

Checked_Symbol* Checked_Symbol__create_kind(Checked_Symbol_Kind kind, size_t kind_size, Source_Location* location, String* name, Checked_Type* type) {
    Checked_Symbol* symbol = (Checked_Symbol*) malloc(kind_size);
    symbol->kind = kind;
    symbol->location = location;
    symbol->name = name;
    symbol->type = type;
    symbol->prev_symbol = null;
    symbol->next_symbol = null;
    return symbol;
}

typedef struct Checked_Enum_Member_Symbol {
    Checked_Symbol super;
} Checked_Enum_Member_Symbol;

Checked_Enum_Member_Symbol* Checked_Enum_Member_Symbol__create(Source_Location* location, String* name, Checked_Type* type) {
    return (Checked_Enum_Member_Symbol*) Checked_Symbol__create_kind(CHECKED_SYMBOL_KIND__ENUM_MEMBER, sizeof(Checked_Enum_Member_Symbol), location, name, type);
}

typedef struct Checked_Statements Checked_Statements;

typedef struct Checked_Function_Symbol {
    Checked_Symbol super;
    Checked_Function_Type* function_type;
    Checked_Statements* checked_statements;
} Checked_Function_Symbol;

Checked_Function_Symbol* Checked_Function_Symbol__create(Source_Location* location, String* name, Checked_Function_Type* function_type) {
    Checked_Function_Symbol* symbol = (Checked_Function_Symbol*) Checked_Symbol__create_kind(CHECKED_SYMBOL_KIND__FUNCTION, sizeof(Checked_Function_Symbol), location, name, (Checked_Type*) Checked_Pointer_Type__create(function_type->super.super.location, (Checked_Type*) function_type));
    symbol->function_type = function_type;
    symbol->checked_statements = null;
    return symbol;
}

typedef struct Checked_Function_Parameter_Symbol {
    Checked_Symbol super;
} Checked_Function_Parameter_Symbol;

Checked_Function_Parameter_Symbol* Checked_Function_Parameter_Symbol__create(Source_Location* location, String* name, Checked_Type* type) {
    return (Checked_Function_Parameter_Symbol*) Checked_Symbol__create_kind(CHECKED_SYMBOL_KIND__FUNCTION_PARAMETER, sizeof(Checked_Function_Parameter_Symbol), location, name, type);
}

typedef struct Checked_Type_Symbol {
    Checked_Symbol super;
    Checked_Named_Type* named_type;
} Checked_Type_Symbol;

Checked_Type_Symbol* Checked_Type_Symbol__create(Source_Location* location, String* name, Checked_Named_Type* named_type) {
    Checked_Type_Symbol* symbol = (Checked_Type_Symbol*) Checked_Symbol__create_kind(CHECKED_SYMBOL_KIND__TYPE, sizeof(Checked_Type_Symbol), location, name, null);
    symbol->named_type = named_type;
    return symbol;
}

typedef struct Checked_Variable_Symbol {
    Checked_Symbol super;
} Checked_Variable_Symbol;

Checked_Variable_Symbol* Checked_Variable__create(Source_Location* location, String* name, Checked_Type* type) {
    return (Checked_Variable_Symbol*) Checked_Symbol__create_kind(CHECKED_SYMBOL_KIND__VARIABLE, sizeof(Checked_Variable_Symbol), location, name, type);
}

typedef struct Checked_Symbols {
    struct Checked_Symbols* parent;
    Checked_Symbol* first_symbol;
    Checked_Symbol* last_symbol;
} Checked_Symbols;

Checked_Symbols* Checked_Symbols__create(Checked_Symbols* parent) {
    Checked_Symbols* symbols = (Checked_Symbols*) malloc(sizeof(Checked_Symbols));
    symbols->parent = parent;
    symbols->first_symbol = null;
    symbols->last_symbol = null;
    return symbols;
}

Checked_Symbol* Checked_Symbols__find_sibling_symbol(Checked_Symbols* self, String* name) {
    Checked_Symbol* symbol = self->first_symbol;
    while (symbol != null) {
        if (String__equals_string(name, symbol->name)) {
            return symbol;
        }
        symbol = symbol->next_symbol;
    }
    return null;
}

void Checked_Symbols__append_symbol(Checked_Symbols* self, Checked_Symbol* symbol) {
    if (Checked_Symbols__find_sibling_symbol(self, symbol->name) != null) {
        error(String__create_from("TODO: Report symbol redeclaration"));
        abort();
    }

    if (self->last_symbol == null) {
        self->first_symbol = symbol;
    } else {
        self->last_symbol->next_symbol = symbol;
        symbol->prev_symbol = self->last_symbol;
    }
    self->last_symbol = symbol;
}

Checked_Symbol* Checked_Symbols__find_symbol(Checked_Symbols* self, String* name) {
    Checked_Symbol* symbol = self->last_symbol;
    while (symbol != null) {
        if (String__equals_string(name, symbol->name)) {
            return symbol;
        }
        symbol = symbol->prev_symbol;
    }
    if (self->parent != null) {
        return Checked_Symbols__find_symbol(self->parent, name);
    }
    return null;
}

#pragma endregion
#pragma region Checked Expressions

typedef enum Checked_Expression_Kind {
    CHECKED_EXPRESSION_KIND__ADD,
    CHECKED_EXPRESSION_KIND__ADDRESS_OF,
    CHECKED_EXPRESSION_KIND__ARRAY_ACCESS,
    CHECKED_EXPRESSION_KIND__BOOL,
    CHECKED_EXPRESSION_KIND__CALL,
    CHECKED_EXPRESSION_KIND__CAST,
    CHECKED_EXPRESSION_KIND__CHARACTER,
    CHECKED_EXPRESSION_KIND__DIVIDE,
    CHECKED_EXPRESSION_KIND__EQUALS,
    CHECKED_EXPRESSION_KIND__GREATER,
    CHECKED_EXPRESSION_KIND__GREATER_OR_EQUALS,
    CHECKED_EXPRESSION_KIND__GROUP,
    CHECKED_EXPRESSION_KIND__INTEGER,
    CHECKED_EXPRESSION_KIND__LESS,
    CHECKED_EXPRESSION_KIND__LESS_OR_EQUALS,
    CHECKED_EXPRESSION_KIND__LOGIC_AND,
    CHECKED_EXPRESSION_KIND__LOGIC_OR,
    CHECKED_EXPRESSION_KIND__MEMBER_ACCESS,
    CHECKED_EXPRESSION_KIND__MINUS,
    CHECKED_EXPRESSION_KIND__MODULO,
    CHECKED_EXPRESSION_KIND__MULTIPLY,
    CHECKED_EXPRESSION_KIND__NOT,
    CHECKED_EXPRESSION_KIND__NOT_EQUALS,
    CHECKED_EXPRESSION_KIND__NULL,
    CHECKED_EXPRESSION_KIND__SIZEOF,
    CHECKED_EXPRESSION_KIND__STRING,
    CHECKED_EXPRESSION_KIND__SUBSTRACT,
    CHECKED_EXPRESSION_KIND__SYMBOL,
} Checked_Expression_Kind;

typedef struct Checked_Expression {
    Checked_Expression_Kind kind;
    Source_Location* location;
    Checked_Type* type;
} Checked_Expression;

Checked_Expression* Checked_Expression__create_kind(Checked_Expression_Kind kind, size_t kind_size, Source_Location* location, Checked_Type* type) {
    Checked_Expression* expression = (Checked_Expression*) malloc(kind_size);
    expression->kind = kind;
    expression->location = location;
    expression->type = type;
    return expression;
}

typedef struct Checked_Binary_Expression {
    Checked_Expression super;
    Checked_Expression* left_expression;
    Checked_Expression* right_expression;
} Checked_Binary_Expression;

Checked_Binary_Expression* Checked_Binary_Expression__create_kind(Checked_Expression_Kind kind, Source_Location* location, Checked_Type* type, Checked_Expression* left_expression, Checked_Expression* right_expression) {
    Checked_Binary_Expression* expression = (Checked_Binary_Expression*) Checked_Expression__create_kind(kind, sizeof(Checked_Binary_Expression), location, type);
    expression->left_expression = left_expression;
    expression->right_expression = right_expression;
    return expression;
}

typedef struct Checked_Unary_Expression {
    Checked_Expression super;
    Checked_Expression* other_expression;
} Checked_Unary_Expression;

Checked_Unary_Expression* Checked_Unary_Expression__create_kind(Checked_Expression_Kind kind, size_t kind_size, Source_Location* location, Checked_Type* type, Checked_Expression* other_expression) {
    Checked_Unary_Expression* expression = (Checked_Unary_Expression*) Checked_Expression__create_kind(kind, kind_size, location, type);
    expression->other_expression = other_expression;
    return expression;
}

typedef struct Checked_Add_Expression {
    Checked_Binary_Expression super;
} Checked_Add_Expression;

Checked_Add_Expression* Checked_Add_Expression__create(Source_Location* location, Checked_Type* type, Checked_Expression* left_expression, Checked_Expression* right_expression) {
    return (Checked_Add_Expression*) Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__ADD, location, type, left_expression, right_expression);
}

typedef struct Checked_Address_Of_Expression {
    Checked_Unary_Expression super;
} Checked_Address_Of_Expression;

Checked_Address_Of_Expression* Checked_Address_Of_Expression__create(Source_Location* location, Checked_Type* type, Checked_Expression* other_expression) {
    return (Checked_Address_Of_Expression*) Checked_Unary_Expression__create_kind(CHECKED_EXPRESSION_KIND__ADDRESS_OF, sizeof(Checked_Address_Of_Expression), location, type, other_expression);
}

typedef struct Checked_Array_Access_Expression {
    Checked_Expression super;
    Checked_Expression* array_expression;
    Checked_Expression* index_expression;
} Checked_Array_Access_Expression;

Checked_Array_Access_Expression* Checked_Array_Access_Expression__create(Source_Location* location, Checked_Type* type, Checked_Expression* array_expression, Checked_Expression* index_expression) {
    Checked_Array_Access_Expression* expression = (Checked_Array_Access_Expression*) Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__ARRAY_ACCESS, sizeof(Checked_Array_Access_Expression), location, type);
    expression->array_expression = array_expression;
    expression->index_expression = index_expression;
    return expression;
}

typedef struct Checked_Bool_Expression {
    Checked_Expression super;
    bool value;
} Checked_Bool_Expression;

Checked_Bool_Expression* Checked_Bool_Expression__create(Source_Location* location, Checked_Type* type, bool value) {
    Checked_Bool_Expression* expression = (Checked_Bool_Expression*) Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__BOOL, sizeof(Checked_Bool_Expression), location, type);
    expression->value = value;
    return expression;
}

typedef struct Checked_Call_Argument {
    Checked_Expression* expression;
    struct Checked_Call_Argument* next_argument;
} Checked_Call_Argument;

Checked_Call_Argument* Checked_Call_Argument__create(Checked_Expression* expression) {
    Checked_Call_Argument* argument = (Checked_Call_Argument*) malloc(sizeof(Checked_Call_Argument));
    argument->expression = expression;
    argument->next_argument = null;
    return argument;
}

typedef struct Checked_Call_Expression {
    Checked_Expression super;
    Checked_Expression* callee_expression;
    Checked_Call_Argument* first_argument;
} Checked_Call_Expression;

Checked_Call_Expression* Checked_Call_Expression__create(Source_Location* location, Checked_Type* type, Checked_Expression* callee_expression, Checked_Call_Argument* first_argument) {
    Checked_Call_Expression* expression = (Checked_Call_Expression*) Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__CALL, sizeof(Checked_Call_Expression), location, type);
    expression->callee_expression = callee_expression;
    expression->first_argument = first_argument;
    return expression;
}

typedef struct Checked_Cast_Expression {
    Checked_Expression super;
    Checked_Expression* other_expression;
} Checked_Cast_Expression;

Checked_Cast_Expression* Checked_Cast_Expression__create(Source_Location* location, Checked_Type* type, Checked_Expression* other_expression) {
    Checked_Cast_Expression* expression = (Checked_Cast_Expression*) Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__CAST, sizeof(Checked_Cast_Expression), location, type);
    expression->other_expression = other_expression;
    return expression;
}

typedef struct Checked_Character_Expression {
    Checked_Expression super;
    char value;
} Checked_Character_Expression;

Checked_Character_Expression* Checked_Character_Expression__create(Source_Location* location, Checked_Type* type, char value) {
    Checked_Character_Expression* expression = (Checked_Character_Expression*) Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__CHARACTER, sizeof(Checked_Character_Expression), location, type);
    expression->value = value;
    return expression;
}

typedef struct Checked_Divide_Expression {
    Checked_Binary_Expression super;
} Checked_Divide_Expression;

Checked_Divide_Expression* Checked_Divide_Expression__create(Source_Location* location, Checked_Type* type, Checked_Expression* left_expression, Checked_Expression* right_expression) {
    return (Checked_Divide_Expression*) Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__DIVIDE, location, type, left_expression, right_expression);
}

typedef struct Checked_Equals_Expression {
    Checked_Binary_Expression super;
} Checked_Equals_Expression;

Checked_Equals_Expression* Checked_Equals_Expression__create(Source_Location* location, Checked_Type* type, Checked_Expression* left_expression, Checked_Expression* right_expression) {
    return (Checked_Equals_Expression*) Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__EQUALS, location, type, left_expression, right_expression);
}

typedef struct Checked_Greater_Expression {
    Checked_Binary_Expression super;
} Checked_Greater_Expression;

Checked_Greater_Expression* Checked_Greater_Expression__create(Source_Location* location, Checked_Type* type, Checked_Expression* left_expression, Checked_Expression* right_expression) {
    return (Checked_Greater_Expression*) Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__GREATER, location, type, left_expression, right_expression);
}

typedef struct Checked_Greater_Or_Equals_Expression {
    Checked_Binary_Expression super;
} Checked_Greater_Or_Equals_Expression;

Checked_Greater_Or_Equals_Expression* Checked_Greater_Or_Equals_Expression__create(Source_Location* location, Checked_Type* type, Checked_Expression* left_expression, Checked_Expression* right_expression) {
    return (Checked_Greater_Or_Equals_Expression*) Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__GREATER_OR_EQUALS, location, type, left_expression, right_expression);
}

typedef struct Checked_Group_Expression {
    Checked_Expression super;
    Checked_Expression* other_expression;
} Checked_Group_Expression;

Checked_Group_Expression* Checked_Group_Expression__create(Source_Location* location, Checked_Type* type, Checked_Expression* other_expression) {
    Checked_Group_Expression* expression = (Checked_Group_Expression*) Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__GROUP, sizeof(Checked_Group_Expression), location, type);
    expression->other_expression = other_expression;
    return expression;
}

typedef struct Checked_Integer_Expression {
    Checked_Expression super;
    uint64_t value;
} Checked_Integer_Expression;

Checked_Integer_Expression* Checked_Integer_Expression__create(Source_Location* location, Checked_Type* type, uint64_t value) {
    Checked_Integer_Expression* expression = (Checked_Integer_Expression*) Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__INTEGER, sizeof(Checked_Integer_Expression), location, type);
    expression->value = value;
    return expression;
}

typedef struct Checked_Less_Expression {
    Checked_Binary_Expression super;
} Checked_Less_Expression;

Checked_Less_Expression* Checked_Less_Expression__create(Source_Location* location, Checked_Type* type, Checked_Expression* left_expression, Checked_Expression* right_expression) {
    return (Checked_Less_Expression*) Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__LESS, location, type, left_expression, right_expression);
}

typedef struct Checked_Less_Or_Equals_Expression {
    Checked_Binary_Expression super;
} Checked_Less_Or_Equals_Expression;

Checked_Less_Or_Equals_Expression* Checked_Less_Or_Equals_Expression__create(Source_Location* location, Checked_Type* type, Checked_Expression* left_expression, Checked_Expression* right_expression) {
    return (Checked_Less_Or_Equals_Expression*) Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__LESS_OR_EQUALS, location, type, left_expression, right_expression);
}

typedef struct Checked_Logic_And_Expression {
    Checked_Binary_Expression super;
} Checked_Logic_And_Expression;

Checked_Logic_And_Expression* Checked_Logic_And_Expression__create(Source_Location* location, Checked_Type* type, Checked_Expression* left_expression, Checked_Expression* right_expression) {
    return (Checked_Logic_And_Expression*) Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__LOGIC_AND, location, type, left_expression, right_expression);
}

typedef struct Checked_Logic_Or_Expression {
    Checked_Binary_Expression super;
} Checked_Logic_Or_Expression;

Checked_Logic_Or_Expression* Checked_Logic_Or_Expression__create(Source_Location* location, Checked_Type* type, Checked_Expression* left_expression, Checked_Expression* right_expression) {
    return (Checked_Logic_Or_Expression*) Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__LOGIC_OR, location, type, left_expression, right_expression);
}

typedef struct Checked_Member_Access_Expression {
    Checked_Expression super;
    Checked_Expression* object_expression;
    Checked_Struct_Member* member;
} Checked_Member_Access_Expression;

Checked_Member_Access_Expression* Checked_Member_Access_Expression__create(Source_Location* location, Checked_Type* type, Checked_Expression* object_expression, Checked_Struct_Member* member) {
    Checked_Member_Access_Expression* expression = (Checked_Member_Access_Expression*) Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__MEMBER_ACCESS, sizeof(Checked_Member_Access_Expression), location, type);
    expression->object_expression = object_expression;
    expression->member = member;
    return expression;
}

typedef struct Checked_Minus_Expression {
    Checked_Unary_Expression super;
} Checked_Minus_Expression;

Checked_Minus_Expression* Checked_Minus_Expression__create(Source_Location* location, Checked_Type* type, Checked_Expression* other_expression) {
    return (Checked_Minus_Expression*) Checked_Unary_Expression__create_kind(CHECKED_EXPRESSION_KIND__MINUS, sizeof(Checked_Minus_Expression), location, type, other_expression);
}

typedef struct Checked_Modulo_Expression {
    Checked_Binary_Expression super;
} Checked_Modulo_Expression;

Checked_Modulo_Expression* Checked_Modulo_Expression__create(Source_Location* location, Checked_Type* type, Checked_Expression* left_expression, Checked_Expression* right_expression) {
    return (Checked_Modulo_Expression*) Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__MODULO, location, type, left_expression, right_expression);
}

typedef struct Checked_Multiply_Expression {
    Checked_Binary_Expression super;
} Checked_Multiply_Expression;

Checked_Multiply_Expression* Checked_Multiply_Expression__create(Source_Location* location, Checked_Type* type, Checked_Expression* left_expression, Checked_Expression* right_expression) {
    return (Checked_Multiply_Expression*) Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__MULTIPLY, location, type, left_expression, right_expression);
}

typedef struct Checked_Not_Expression {
    Checked_Unary_Expression super;
} Checked_Not_Expression;

Checked_Not_Expression* Checked_Not_Expression__create(Source_Location* location, Checked_Type* type, Checked_Expression* other_expression) {
    return (Checked_Not_Expression*) Checked_Unary_Expression__create_kind(CHECKED_EXPRESSION_KIND__NOT, sizeof(Checked_Not_Expression), location, type, other_expression);
}

typedef struct Checked_Not_Equals_Expression {
    Checked_Binary_Expression super;
} Checked_Not_Equals_Expression;

Checked_Not_Equals_Expression* Checked_Not_Equals_Expression__create(Source_Location* location, Checked_Type* type, Checked_Expression* left_expression, Checked_Expression* right_expression) {
    return (Checked_Not_Equals_Expression*) Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__NOT_EQUALS, location, type, left_expression, right_expression);
}

typedef struct Checked_Null_Expression {
    Checked_Expression super;
} Checked_Null_Expression;

Checked_Null_Expression* Checked_Null_Expression__create(Source_Location* location, Checked_Type* type) {
    return (Checked_Null_Expression*) Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__NULL, sizeof(Checked_Null_Expression), location, type);
}

typedef struct Checked_Sizeof_Expression {
    Checked_Expression super;
    Checked_Type* sized_type;
} Checked_Sizeof_Expression;

Checked_Sizeof_Expression* Checked_Sizeof_Expression__create(Source_Location* location, Checked_Type* type, Checked_Type* sized_type) {
    Checked_Sizeof_Expression* expression = (Checked_Sizeof_Expression*) Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__SIZEOF, sizeof(Checked_Sizeof_Expression), location, type);
    expression->sized_type = sized_type;
    return expression;
}

typedef struct Checked_String_Expression {
    Checked_Expression super;
    String* value;
} Checked_String_Expression;

Checked_String_Expression* Checked_String_Expression__create(Source_Location* location, Checked_Type* type, String* value) {
    Checked_String_Expression* expression = (Checked_String_Expression*) Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__STRING, sizeof(Checked_String_Expression), location, type);
    expression->value = value;
    return expression;
}

typedef struct Checked_Substract_Expression {
    Checked_Binary_Expression super;
} Checked_Substract_Expression;

Checked_Substract_Expression* Checked_Substract_Expression__create(Source_Location* location, Checked_Type* type, Checked_Expression* left_expression, Checked_Expression* right_expression) {
    return (Checked_Substract_Expression*) Checked_Binary_Expression__create_kind(CHECKED_EXPRESSION_KIND__SUBSTRACT, location, type, left_expression, right_expression);
}

typedef struct Checked_Symbol_Expression {
    Checked_Expression super;
    Checked_Symbol* symbol;
} Checked_Symbol_Expression;

Checked_Symbol_Expression* Checked_Symbol_Expression__create(Source_Location* location, Checked_Type* type, Checked_Symbol* symbol) {
    Checked_Symbol_Expression* expression = (Checked_Symbol_Expression*) Checked_Expression__create_kind(CHECKED_EXPRESSION_KIND__SYMBOL, sizeof(Checked_Symbol_Expression), location, type);
    expression->symbol = symbol;
    return expression;
}

#pragma endregion
#pragma region Checked Statements

typedef enum Checked_Statement_Kind {
    CHECKED_STATEMENT_KIND__ASSIGNMENT,
    CHECKED_STATEMENT_KIND__BLOCK,
    CHECKED_STATEMENT_KIND__BREAK,
    CHECKED_STATEMENT_KIND__EXPRESSION,
    CHECKED_STATEMENT_KIND__IF,
    CHECKED_STATEMENT_KIND__RETURN,
    CHECKED_STATEMENT_KIND__VARIABLE,
    CHECKED_STATEMENT_KIND__WHILE,
} Checked_Statement_Kind;

typedef struct Checked_Statement {
    Checked_Statement_Kind kind;
    Source_Location* location;
    struct Checked_Statement* next_statement;
} Checked_Statement;

Checked_Statement* Checked_Statement__create_kind(Checked_Statement_Kind kind, size_t kind_size, Source_Location* location) {
    Checked_Statement* statement = (Checked_Statement*) malloc(kind_size);
    statement->kind = kind;
    statement->location = location;
    statement->next_statement = null;
    return statement;
}

typedef struct Checked_Assignment_Statement {
    Checked_Statement super;
    Checked_Expression* object_expression;
    Checked_Expression* value_expression;
} Checked_Assignment_Statement;

Checked_Assignment_Statement* Checked_Assignment_Statement__create(Source_Location* location, Checked_Expression* object_expression, Checked_Expression* value_expression) {
    Checked_Assignment_Statement* statement = (Checked_Assignment_Statement*) Checked_Statement__create_kind(CHECKED_STATEMENT_KIND__ASSIGNMENT, sizeof(Checked_Assignment_Statement), location);
    statement->object_expression = object_expression;
    statement->value_expression = value_expression;
    return statement;
}

typedef struct Checked_Block_Statement {
    Checked_Statement super;
    Checked_Statements* statements;
} Checked_Block_Statement;

Checked_Block_Statement* Checked_Block_Statement__create(Source_Location* location, Checked_Statements* statements) {
    Checked_Block_Statement* statement = (Checked_Block_Statement*) Checked_Statement__create_kind(CHECKED_STATEMENT_KIND__BLOCK, sizeof(Checked_Block_Statement), location);
    statement->statements = statements;
    return statement;
}

typedef struct Checked_Break_Statement {
    Checked_Statement super;
} Checked_Break_Statement;

Checked_Break_Statement* Checked_Break_Statement__create(Source_Location* location) {
    return (Checked_Break_Statement*) Checked_Statement__create_kind(CHECKED_STATEMENT_KIND__BREAK, sizeof(Checked_Break_Statement), location);
}

typedef struct Checked_Expression_Statement {
    Checked_Statement super;
    Checked_Expression* expression;
} Checked_Expression_Statement;

Checked_Expression_Statement* Checked_Expression_Statement__create(Source_Location* location, Checked_Expression* expression) {
    Checked_Expression_Statement* statement = (Checked_Expression_Statement*) Checked_Statement__create_kind(CHECKED_STATEMENT_KIND__EXPRESSION, sizeof(Checked_Expression_Statement), location);
    statement->expression = expression;
    return statement;
}

typedef struct Checked_If_Statement {
    Checked_Statement super;
    Checked_Expression* condition_expression;
    Checked_Statement* true_statement;
    Checked_Statement* false_statement;
} Checked_If_Statement;

Checked_If_Statement* Checked_If_Statement__create(Source_Location* location, Checked_Expression* condition_expression, Checked_Statement* true_statement, Checked_Statement* false_statement) {
    Checked_If_Statement* statement = (Checked_If_Statement*) Checked_Statement__create_kind(CHECKED_STATEMENT_KIND__IF, sizeof(Checked_If_Statement), location);
    statement->condition_expression = condition_expression;
    statement->true_statement = true_statement;
    statement->false_statement = false_statement;
    return statement;
}

typedef struct Checked_Return_Statement {
    Checked_Statement super;
    Checked_Expression* expression;
} Checked_Return_Statement;

Checked_Return_Statement* Checked_Return_Statement__create(Source_Location* location, Checked_Expression* expression) {
    Checked_Return_Statement* statement = (Checked_Return_Statement*) Checked_Statement__create_kind(CHECKED_STATEMENT_KIND__RETURN, sizeof(Checked_Return_Statement), location);
    statement->expression = expression;
    return statement;
}

typedef struct Checked_Variable_Statement {
    Checked_Statement super;
    Checked_Variable_Symbol* variable;
    Checked_Expression* expression;
    bool is_external;
} Checked_Variable_Statement;

Checked_Variable_Statement* Checked_Variable_Statement__create(Source_Location* location, Checked_Variable_Symbol* variable, Checked_Expression* expression, bool is_external) {
    Checked_Variable_Statement* statement = (Checked_Variable_Statement*) Checked_Statement__create_kind(CHECKED_STATEMENT_KIND__VARIABLE, sizeof(Checked_Variable_Statement), location);
    statement->variable = variable;
    statement->expression = expression;
    statement->is_external = is_external;
    return statement;
}

typedef struct Checked_While_Statement {
    Checked_Statement super;
    Checked_Expression* condition_expression;
    Checked_Statement* body_statement;
} Checked_While_Statement;

Checked_While_Statement* Checked_While_Statement__create(Source_Location* location, Checked_Expression* condition_expression, Checked_Statement* body_statement) {
    Checked_While_Statement* statement = (Checked_While_Statement*) Checked_Statement__create_kind(CHECKED_STATEMENT_KIND__WHILE, sizeof(Checked_While_Statement), location);
    statement->condition_expression = condition_expression;
    statement->body_statement = body_statement;
    return statement;
}

typedef struct Checked_Statements {
    Checked_Statement* first_statement;
    Checked_Statement* last_statement;
} Checked_Statements;

Checked_Statements* Checked_Statements__create() {
    Checked_Statements* statements = (Checked_Statements*) malloc(sizeof(Checked_Statements));
    statements->first_statement = null;
    statements->last_statement = null;
    return statements;
}

void Checked_Statements__append(Checked_Statements* self, Checked_Statement* statement) {
    if (self->first_statement == null) {
        self->first_statement = statement;
    } else {
        self->last_statement->next_statement = statement;
    }
    self->last_statement = statement;
}

#pragma endregion
#pragma region Checked Source

typedef struct Checked_Source {
    Checked_Symbol* first_symbol;
    Checked_Statements* statements;
} Checked_Source;

#pragma endregion
#pragma region Checker

typedef struct Checker {
    Checked_Named_Type* first_type;
    Checked_Named_Type* last_type;
    Checked_Named_Type* last_builting_type;
    Checked_Symbols* symbols;
    Checked_Type* return_type;
} Checker;

void Checker__append_type(Checker* self, Checked_Named_Type* type);

Checker* Checker__create() {
    Checker* checker = (Checker*) malloc(sizeof(Checker));
    checker->first_type = null;
    checker->last_type = null;
    checker->symbols = Checked_Symbols__create(null);

    Source_Location* location = Source_Location__create(null, (uint16_t) 0, (uint16_t) 1);
    Checker__append_type(checker, Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__BOOL, sizeof(Checked_Named_Type), location, String__create_from("bool")));
    Checker__append_type(checker, Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__CHAR, sizeof(Checked_Named_Type), location, String__create_from("char")));
    Checker__append_type(checker, Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__INT16_T, sizeof(Checked_Named_Type), location, String__create_from("int16_t")));
    Checker__append_type(checker, Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__INT32_T, sizeof(Checked_Named_Type), location, String__create_from("int32_t")));
    Checker__append_type(checker, Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__INT64_T, sizeof(Checked_Named_Type), location, String__create_from("int64_t")));
    Checker__append_type(checker, Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__INT8_T, sizeof(Checked_Named_Type), location, String__create_from("int8_t")));
    Checker__append_type(checker, Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__SIZE_T, sizeof(Checked_Named_Type), location, String__create_from("size_t")));
    Checker__append_type(checker, Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__UINT16_T, sizeof(Checked_Named_Type), location, String__create_from("uint16_t")));
    Checker__append_type(checker, Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__UINT32_T, sizeof(Checked_Named_Type), location, String__create_from("uint32_t")));
    Checker__append_type(checker, Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__UINT64_T, sizeof(Checked_Named_Type), location, String__create_from("uint64_t")));
    Checker__append_type(checker, Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__UINT8_T, sizeof(Checked_Named_Type), location, String__create_from("uint8_t")));
    Checker__append_type(checker, Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__VOID, sizeof(Checked_Named_Type), location, String__create_from("void")));
    Checker__append_type(checker, Checked_Named_Type__create_kind(CHECKED_TYPE_KIND__NULL, sizeof(Checked_Named_Type), location, String__create_from("null")));
    checker->last_builting_type = checker->last_type;

    return checker;
}

void Checker__append_type(Checker* self, Checked_Named_Type* type) {
    if (self->first_type == null) {
        self->first_type = type;
    } else {
        self->last_type->super.next_type = (Checked_Type*) type;
    }
    self->last_type = type;

    Checked_Symbols__append_symbol(self->symbols, (Checked_Symbol*) Checked_Type_Symbol__create(type->super.location, type->name, type));
}

Checked_Named_Type* Checker__find_type(Checker* self, String* name) {
    Checked_Named_Type* type = self->first_type;
    while (type != null) {
        if (String__equals_string(name, type->name)) {
            break;
        }
        type = (Checked_Named_Type*) type->super.next_type;
    }
    return type;
}

Checked_Named_Type* Checker__get_builtin_type(Checker* self, Checked_Type_Kind kind) {
    Checked_Named_Type* type = self->first_type;
    Checked_Named_Type* custom_type = (Checked_Named_Type*) self->last_builting_type->super.next_type;
    while (type != custom_type) {
        if (type->super.kind == kind) {
            return type;
        }
        type = (Checked_Named_Type*) type->super.next_type;
    }
    error(String__create_from("No such builtin type"));
    abort();
}

Checked_Type* Checker__resolve_type(Checker* self, Parsed_Type* parsed_type) {
    if (parsed_type->kind == PARSED_TYPE_KIND__CONST) {
        return (Checked_Type*) Checked_Const_Type__create(parsed_type->location, Checker__resolve_type(self, ((Parsed_Const_Type*) parsed_type)->other_type));
    }
    if (parsed_type->kind == PARSED_TYPE_KIND__NAMED) {
        Checked_Named_Type* type = Checker__find_type(self, ((Parsed_Named_Type*) parsed_type)->name);
        if (type != null) {
            return (Checked_Type*) type;
        }
    }
    if (parsed_type->kind == PARSED_TYPE_KIND__POINTER) {
        return (Checked_Type*) Checked_Pointer_Type__create(parsed_type->location, Checker__resolve_type(self, ((Parsed_Pointer_Type*) parsed_type)->other_type));
    }
    if (parsed_type->kind == PARSED_TYPE_KIND__STRUCT) {
        Checked_Type* type = Checker__resolve_type(self, ((Parsed_Struct_Type*) parsed_type)->other_type);
        if (type->kind != CHECKED_TYPE_KIND__STRUCT) {
            TODO("Report unexpected type");
            abort();
        }
        return type;
    }
    TODO("Report undefined type");
    abort();
}

Checked_Expression* Checker__check_expression(Checker* self, Parsed_Expression* parsed_expression);

Checked_Expression* Checker__check_add_expression(Checker* self, Parsed_Add_Expression* parsed_expression) {
    Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
    Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
    return (Checked_Expression*) Checked_Add_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

Checked_Expression* Checker__check_address_of_expression(Checker* self, Parsed_Address_Of_Expression* parsed_expression) {
    Checked_Expression* other_expression = Checker__check_expression(self, parsed_expression->super.other_expression);
    if (other_expression->kind != CHECKED_EXPRESSION_KIND__SYMBOL) {
        Source_Location__error(parsed_expression->super.super.location, String__create_from("Not a symbol"));
        abort();
    }
    return (Checked_Expression*) Checked_Address_Of_Expression__create(parsed_expression->super.super.location, (Checked_Type*) Checked_Pointer_Type__create(other_expression->location, other_expression->type), other_expression);
}

Checked_Expression* Checker__check_array_access_expression(Checker* self, Parsed_Array_Access_Expression* parsed_expression) {
    Checked_Expression* array_expression = Checker__check_expression(self, parsed_expression->array_expression);
    Checked_Type* array_type = array_expression->type;
    if (array_type->kind == CHECKED_TYPE_KIND__CONST) {
        array_type = ((Checked_Const_Type*) array_type)->other_type;
    }
    if (array_type->kind != CHECKED_TYPE_KIND__POINTER) {
        String* message = String__create();
        String__append_char(message, '"');
        String__append_checked_type(message, array_type);
        String__append_cstring(message, "\" is not a pointer type.");
        Source_Location__error(parsed_expression->array_expression->location, message);
        abort();
    }
    Checked_Type* type = ((Checked_Pointer_Type*) array_type)->other_type;
    Checked_Expression* index_expression = Checker__check_expression(self, parsed_expression->index_expression);
    Checked_Type__expect_same_type((Checked_Type*) Checker__get_builtin_type(self, CHECKED_TYPE_KIND__SIZE_T), index_expression->type, index_expression->location);
    return (Checked_Expression*) Checked_Array_Access_Expression__create(parsed_expression->super.location, type, array_expression, index_expression);
}

Checked_Expression* Checker__check_bool_expression(Checker* self, Parsed_Bool_Expression* parsed_expression) {
    Checked_Type* expression_type = (Checked_Type*) Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL);
    bool value = parsed_expression->value;
    return (Checked_Expression*) Checked_Bool_Expression__create(parsed_expression->super.super.location, expression_type, value);
}

Checked_Expression* Checker__check_call_expression(Checker* self, Parsed_Call_Expression* parsed_expression) {
    Checked_Expression* callee_expression = Checker__check_expression(self, parsed_expression->callee_expression);
    Checked_Type* callee_type = callee_expression->type;
    if (callee_type->kind != CHECKED_TYPE_KIND__POINTER || ((Checked_Pointer_Type*) callee_type)->other_type->kind != CHECKED_TYPE_KIND__FUNCTION) {
        Source_Location__error(parsed_expression->super.location, String__create_from("Not a function"));
        abort();
    }
    Checked_Function_Type* function_type = (Checked_Function_Type*) ((Checked_Pointer_Type*) callee_type)->other_type;
    Checked_Call_Argument* first_argument = null;
    if (parsed_expression->first_argument != null) {
        Checked_Call_Argument* last_argument = null;
        Checked_Function_Parameter* function_parameter = function_type->first_parameter;
        Parsed_Call_Argument* parsed_argument = parsed_expression->first_argument;
        while (function_parameter != null && parsed_argument != null) {
            Checked_Expression* argument_expression = Checker__check_expression(self, parsed_argument->expression);
            Checked_Type__expect_same_type(function_parameter->type, argument_expression->type, argument_expression->location);
            Checked_Call_Argument* argument = Checked_Call_Argument__create(argument_expression);
            if (last_argument == null) {
                first_argument = argument;
            } else {
                last_argument->next_argument = argument;
            }
            last_argument = argument;
            function_parameter = function_parameter->next_parameter;
            parsed_argument = parsed_argument->next_argument;
        }
        if (function_parameter != null) {
            Source_Location__error(parsed_expression->super.location, String__create_from("Report too few arguments"));
            abort();
        }
        if (parsed_argument != null) {
            Source_Location__error(parsed_expression->super.location, String__create_from("Report too many arguments"));
            abort();
        }
    }
    return (Checked_Expression*) Checked_Call_Expression__create(parsed_expression->super.location, function_type->return_type, callee_expression, first_argument);
}

Checked_Expression* Checker__check_cast_expression(Checker* self, Parsed_Cast_Expression* parsed_expression) {
    Checked_Type* type = Checker__resolve_type(self, parsed_expression->type);
    Checked_Expression* other_expression = Checker__check_expression(self, parsed_expression->super.other_expression);
    Checked_Type* other_type = other_expression->type;
    bool can_cast = false;
    if (type->kind == CHECKED_TYPE_KIND__POINTER) {
        if (other_type->kind == CHECKED_TYPE_KIND__POINTER) {
            can_cast = true;
        }
    } else if (Checked_Type__is_scalar_type(type)) {
        if (Checked_Type__is_scalar_type(type)) {
            can_cast = true;
        }
    }
    if (Checked_Type__equals(type, other_type)) {
        Source_Location__warning(parsed_expression->super.super.location, String__create_from("Redundant cast"));
    }
    if (!can_cast) {
        String* message = String__create_from("Cannot cast \"");
        String__append_checked_type(message, other_expression->type);
        String__append_cstring(message, "\" to \"");
        String__append_checked_type(message, type);
        String__append_cstring(message, "\".");
        Source_Location__error(parsed_expression->super.super.location, message);
        abort();
    }
    return (Checked_Expression*) Checked_Cast_Expression__create(parsed_expression->super.super.location, type, other_expression);
}

Checked_Expression* Checker__check_character_expression(Checker* self, Parsed_Character_Expression* parsed_expression) {
    Checked_Type* expression_type = (Checked_Type*) Checker__get_builtin_type(self, CHECKED_TYPE_KIND__CHAR);
    char value = parsed_expression->value;
    return (Checked_Expression*) Checked_Character_Expression__create(parsed_expression->super.super.location, expression_type, value);
}

Checked_Expression* Checker__check_divide_expression(Checker* self, Parsed_Divide_Expression* parsed_expression) {
    Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
    Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
    return (Checked_Expression*) Checked_Divide_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

Checked_Expression* Checker__check_equals_expression(Checker* self, Parsed_Equals_Expression* parsed_expression) {
    Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
    Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
    return (Checked_Expression*) Checked_Equals_Expression__create(parsed_expression->super.super.location, (Checked_Type*) Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL), left_expression, right_expression);
}

Checked_Expression* Checker__check_greater_expression(Checker* self, Parsed_Greater_Expression* parsed_expression) {
    Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
    Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
    return (Checked_Expression*) Checked_Greater_Expression__create(parsed_expression->super.super.location, (Checked_Type*) Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL), left_expression, right_expression);
}

Checked_Expression* Checker__check_greater_or_equals_expression(Checker* self, Parsed_Greater_Or_Equals_Expression* parsed_expression) {
    Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
    Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
    return (Checked_Expression*) Checked_Greater_Or_Equals_Expression__create(parsed_expression->super.super.location, (Checked_Type*) Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL), left_expression, right_expression);
}

Checked_Expression* Checker__check_group_expression(Checker* self, Parsed_Group_Expression* parsed_expression) {
    Checked_Expression* other_expression = Checker__check_expression(self, parsed_expression->other_expression);
    return (Checked_Expression*) Checked_Group_Expression__create(parsed_expression->super.location, other_expression->type, other_expression);
}

Checked_Expression* Checker__check_integer_expression(Checker* self, Parsed_Integer_Expression* parsed_expression) {
    Checked_Type* expression_type = (Checked_Type*) Checker__get_builtin_type(self, CHECKED_TYPE_KIND__INT32_T);
    uint64_t value = parsed_expression->value;
    return (Checked_Expression*) Checked_Integer_Expression__create(parsed_expression->super.super.location, expression_type, value);
}

Checked_Expression* Checker__check_less_expression(Checker* self, Parsed_Less_Expression* parsed_expression) {
    Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
    Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
    return (Checked_Expression*) Checked_Less_Expression__create(parsed_expression->super.super.location, (Checked_Type*) Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL), left_expression, right_expression);
}

Checked_Expression* Checker__check_less_or_equals_expression(Checker* self, Parsed_Less_Or_Equals_Expression* parsed_expression) {
    Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
    Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
    return (Checked_Expression*) Checked_Less_Or_Equals_Expression__create(parsed_expression->super.super.location, (Checked_Type*) Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL), left_expression, right_expression);
}

Checked_Expression* Checker__check_logic_and_expression(Checker* self, Parsed_Logic_And_Expression* parsed_expression) {
    Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
    Checked_Type__expect_same_type((Checked_Type*) Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL), left_expression->type, left_expression->location);
    Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
    return (Checked_Expression*) Checked_Logic_And_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

Checked_Expression* Checker__check_logic_or_expression(Checker* self, Parsed_Logic_Or_Expression* parsed_expression) {
    Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
    Checked_Type__expect_same_type((Checked_Type*) Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL), left_expression->type, left_expression->location);
    Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
    return (Checked_Expression*) Checked_Logic_Or_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

Checked_Expression* Checker__check_member_access_expression(Checker* self, Parsed_Member_Access_Expression* parsed_expression) {
    Checked_Expression* object_expression = Checker__check_expression(self, parsed_expression->object_expression);
    Checked_Type* object_type = object_expression->type;
    if (object_type->kind == CHECKED_TYPE_KIND__POINTER) {
        object_type = ((Checked_Pointer_Type*) object_type)->other_type;
    }
    if (object_type->kind != CHECKED_TYPE_KIND__STRUCT) {
        Source_Location__error(object_expression->location, String__create_from("Not a struct type"));
        abort();
    }
    Checked_Struct_Type* struct_type = (Checked_Struct_Type*) object_type;
    Checked_Struct_Member* member = Checked_Struct_Type__find_member(struct_type, parsed_expression->member_name->lexeme);
    if (member == null) {
        Source_Location__error(object_expression->location, String__create_from("No such struct member"));
        abort();
    }
    return (Checked_Expression*) Checked_Member_Access_Expression__create(parsed_expression->super.location, member->type, object_expression, member);
}

Checked_Expression* Checker__check_minus_expression(Checker* self, Parsed_Minus_Expression* parsed_expression) {
    Checked_Expression* other_expression = Checker__check_expression(self, parsed_expression->super.other_expression);
    Checked_Type* other_expression_type = other_expression->type;
    Checked_Type__expect_scalar_type(other_expression_type, other_expression->location);
    return (Checked_Expression*) Checked_Minus_Expression__create(parsed_expression->super.super.location, other_expression_type, other_expression);
}

Checked_Expression* Checker__check_modulo_expression(Checker* self, Parsed_Modulo_Expression* parsed_expression) {
    Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
    Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
    return (Checked_Expression*) Checked_Modulo_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

Checked_Expression* Checker__check_multiply_expression(Checker* self, Parsed_Multiply_Expression* parsed_expression) {
    Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
    Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
    return (Checked_Expression*) Checked_Multiply_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

Checked_Expression* Checker__check_not_expression(Checker* self, Parsed_Not_Expression* parsed_expression) {
    Checked_Expression* other_expression = Checker__check_expression(self, parsed_expression->super.other_expression);
    Checked_Type* other_expression_type = other_expression->type;
    Checked_Type__expect_same_type((Checked_Type*) Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL), other_expression_type, other_expression->location);
    return (Checked_Expression*) Checked_Not_Expression__create(parsed_expression->super.super.location, other_expression_type, other_expression);
}

Checked_Expression* Checker__check_not_equals_expression(Checker* self, Parsed_Not_Equals_Expression* parsed_expression) {
    Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
    Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
    return (Checked_Expression*) Checked_Not_Equals_Expression__create(parsed_expression->super.super.location, (Checked_Type*) Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL), left_expression, right_expression);
}

Checked_Expression* Checker__check_null_expression(Checker* self, Parsed_Null_Expression* parsed_expression) {
    Checked_Type* expression_type = (Checked_Type*) Checker__get_builtin_type(self, CHECKED_TYPE_KIND__NULL);
    return (Checked_Expression*) Checked_Null_Expression__create(parsed_expression->super.literal->location, expression_type);
}

Checked_Expression* Checker__check_sizeof_expression(Checker* self, Parsed_Sizeof_Expression* parsed_expression) {
    Checked_Type* expression_type = (Checked_Type*) Checker__get_builtin_type(self, CHECKED_TYPE_KIND__SIZE_T);
    Checked_Type* sized_type = Checker__resolve_type(self, parsed_expression->type);
    return (Checked_Expression*) Checked_Sizeof_Expression__create(parsed_expression->super.location, expression_type, sized_type);
}

Checked_Expression* Checker__check_string_expression(Checker* self, Parsed_String_Expression* parsed_expression) {
    Checked_Type* char_type = (Checked_Type*) Checker__get_builtin_type(self, CHECKED_TYPE_KIND__CHAR);
    Checked_Type* char_pointer_type = (Checked_Type*) Checked_Pointer_Type__create(parsed_expression->super.literal->location, char_type);
    Checked_Type* expression_type = (Checked_Type*) Checked_Const_Type__create(parsed_expression->super.literal->location, char_pointer_type);
    String* value = parsed_expression->value;
    return (Checked_Expression*) Checked_String_Expression__create(parsed_expression->super.super.location, expression_type, value);
}

Checked_Expression* Checker__check_substract_expression(Checker* self, Parsed_Substract_Expression* parsed_expression) {
    Checked_Expression* left_expression = Checker__check_expression(self, parsed_expression->super.left_expression);
    Checked_Type__expect_scalar_type(left_expression->type, left_expression->location);
    Checked_Expression* right_expression = Checker__check_expression(self, parsed_expression->super.right_expression);
    Checked_Type__expect_same_type(left_expression->type, right_expression->type, right_expression->location);
    return (Checked_Expression*) Checked_Substract_Expression__create(parsed_expression->super.super.location, left_expression->type, left_expression, right_expression);
}

Checked_Expression* Checker__check_symbol_expression(Checker* self, Parsed_Symbol_Expression* parsed_expression) {
    Checked_Symbol* symbol = Checked_Symbols__find_symbol(self->symbols, parsed_expression->name->lexeme);
    if (symbol == null) {
        Token__error(parsed_expression->name, String__create_from("Undefined symbol"));
        abort();
    }
    if (symbol->type == null) {
        Token__error(parsed_expression->name, String__create_from("Symbol without type"));
        abort();
    }
    return (Checked_Expression*) Checked_Symbol_Expression__create(parsed_expression->super.location, symbol->type, symbol);
}

Checked_Expression* Checker__check_expression(Checker* self, Parsed_Expression* parsed_expression) {
    if (parsed_expression->kind == PARSED_EXPRESSION_KIND__ADD) {
        return Checker__check_add_expression(self, (Parsed_Add_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__ADDRESS_OF) {
        return Checker__check_address_of_expression(self, (Parsed_Address_Of_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__ARRAY_ACCESS) {
        return Checker__check_array_access_expression(self, (Parsed_Array_Access_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__BOOL) {
        return Checker__check_bool_expression(self, (Parsed_Bool_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__CALL) {
        return Checker__check_call_expression(self, (Parsed_Call_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__CAST) {
        return Checker__check_cast_expression(self, (Parsed_Cast_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__CHARACTER) {
        return Checker__check_character_expression(self, (Parsed_Character_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__DIVIDE) {
        return Checker__check_divide_expression(self, (Parsed_Divide_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__EQUALS) {
        return Checker__check_equals_expression(self, (Parsed_Equals_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__GREATER) {
        return Checker__check_greater_expression(self, (Parsed_Greater_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__GREATER_OR_EQUALS) {
        return Checker__check_greater_or_equals_expression(self, (Parsed_Greater_Or_Equals_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__GROUP) {
        return Checker__check_group_expression(self, (Parsed_Group_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__INTEGER) {
        return Checker__check_integer_expression(self, (Parsed_Integer_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__LESS) {
        return Checker__check_less_expression(self, (Parsed_Less_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__LESS_OR_EQUALS) {
        return Checker__check_less_or_equals_expression(self, (Parsed_Less_Or_Equals_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__LOGIC_AND) {
        return Checker__check_logic_and_expression(self, (Parsed_Logic_And_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__LOGIC_OR) {
        return Checker__check_logic_or_expression(self, (Parsed_Logic_Or_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__MEMBER_ACCESS) {
        return Checker__check_member_access_expression(self, (Parsed_Member_Access_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__MINUS) {
        return Checker__check_minus_expression(self, (Parsed_Minus_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__MODULO) {
        return Checker__check_modulo_expression(self, (Parsed_Modulo_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__MULTIPLY) {
        return Checker__check_multiply_expression(self, (Parsed_Multiply_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__NOT) {
        return Checker__check_not_expression(self, (Parsed_Not_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__NOT_EQUALS) {
        return Checker__check_not_equals_expression(self, (Parsed_Not_Equals_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__NULL) {
        return Checker__check_null_expression(self, (Parsed_Null_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__SIZEOF) {
        return Checker__check_sizeof_expression(self, (Parsed_Sizeof_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__STRING) {
        return Checker__check_string_expression(self, (Parsed_String_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__SUBSTRACT) {
        return Checker__check_substract_expression(self, (Parsed_Substract_Expression*) parsed_expression);
    } else if (parsed_expression->kind == PARSED_EXPRESSION_KIND__SYMBOL) {
        return Checker__check_symbol_expression(self, (Parsed_Symbol_Expression*) parsed_expression);
    }
    Source_Location__error(parsed_expression->location, String__create_from("Unsupported expression kind"));
    abort();
}

void Checker__check_enum_statement(Checker* self, Parsed_Enum_Statement* parsed_statement) {
    Checked_Enum_Type* enum_type = Checked_Enum_Type__create(parsed_statement->super.name->location, parsed_statement->super.name->lexeme);
    Checker__append_type(self, (Checked_Named_Type*) enum_type);

    Checked_Enum_Member* last_enum_member = null;
    Parsed_Enum_Member* parsed_enum_member = parsed_statement->first_member;
    while (parsed_enum_member != null) {
        Checked_Enum_Member* enum_member = Checked_Enum_Type__find_member(enum_type, parsed_enum_member->name->lexeme);
        if (enum_member != null) {
            TODO("Handle enum member duplicate");
            abort();
        }
        enum_member = Checked_Enum_Member__create(parsed_enum_member->name->location, parsed_enum_member->name->lexeme);
        if (last_enum_member == null) {
            enum_type->first_member = enum_member;
        } else {
            last_enum_member->next_member = enum_member;
        }
        last_enum_member = enum_member;
        Checked_Symbols__append_symbol(self->symbols, (Checked_Symbol*) Checked_Enum_Member_Symbol__create(enum_member->location, enum_member->name, (Checked_Type*) enum_type));
        parsed_enum_member = parsed_enum_member->next_member;
    }
}

void Checker__check_function_type_statement(Checker* self, Parsed_Function_Type_Statement* parsed_statement) {
    Checked_Named_Type* other_type = Checker__find_type(self, parsed_statement->super.name->lexeme);
    Checked_Function_Type* function_type;
    if (other_type != null) {
        TODO("Handle type redeclaration");
        abort();
    } else {
        Checked_Type* return_type = Checker__resolve_type(self, parsed_statement->return_type);
        function_type = Checked_Function_Type__create(parsed_statement->super.name->location, parsed_statement->super.name->lexeme, return_type);
        Checker__append_type(self, (Checked_Named_Type*) function_type);
    }

    if (parsed_statement->first_parameter != null) {
        Checked_Function_Parameter* last_function_parameter = null;
        Parsed_Function_Type_Parameter* parsed_parameter = parsed_statement->first_parameter;
        while (parsed_parameter != null) {
            Checked_Type* function_parameter_type = Checker__resolve_type(self, parsed_parameter->type);
            Checked_Function_Parameter* function_parameter = Checked_Function_Parameter__create(parsed_parameter->name->location, parsed_parameter->name->lexeme, function_parameter_type);
            if (last_function_parameter == null) {
                function_type->first_parameter = function_parameter;
            } else {
                last_function_parameter->next_parameter = function_parameter;
            }
            last_function_parameter = function_parameter;
            parsed_parameter = parsed_parameter->next_parameter;
        }
    }
}

void Checker__check_struct_statement(Checker* self, Parsed_Struct_Statement* parsed_statement) {
    Checked_Named_Type* other_type = Checker__find_type(self, parsed_statement->super.name->lexeme);
    Checked_Struct_Type* struct_type;
    if (other_type != null) {
        if (other_type->super.kind != CHECKED_TYPE_KIND__STRUCT || (((Checked_Struct_Type*) other_type)->first_member != null)) {
            TODO("Report type redeclaration");
            abort();
        }
        struct_type = (Checked_Struct_Type*) other_type;
    } else {
        struct_type = Checked_Struct_Type__create(parsed_statement->super.name->location, parsed_statement->super.name->lexeme);
        Checker__append_type(self, (Checked_Named_Type*) struct_type);
    }

    if (parsed_statement->first_member != null) {
        Checked_Struct_Member* last_struct_member = null;
        Parsed_Struct_Member* parsed_member = parsed_statement->first_member;
        while (parsed_member != null) {
            Checked_Struct_Member* struct_member = Checked_Struct_Type__find_member(struct_type, parsed_member->name->lexeme);
            if (struct_member != null) {
                TODO("Handle struct member duplicate");
                abort();
            }
            Checked_Type* struct_member_type = Checker__resolve_type(self, parsed_member->type);
            struct_member = Checked_Struct_Member__create(parsed_member->name->location, parsed_member->name->lexeme, struct_member_type);
            if (last_struct_member == null) {
                struct_type->first_member = struct_member;
            } else {
                last_struct_member->next_member = struct_member;
            }
            last_struct_member = struct_member;
            parsed_member = parsed_member->next_member;
        }
    }
}

Checked_Statement* Checker__check_statement(Checker* self, Parsed_Statement* parsed_statement);

Checked_Assignment_Statement* Checker__check_assignment_statement(Checker* self, Parsed_Assignment_Statement* parsed_statement) {
    Checked_Expression* object_expression = Checker__check_expression(self, parsed_statement->object_expression);
    Checked_Expression* value_expression = Checker__check_expression(self, parsed_statement->value_expression);
    Checked_Type__expect_same_type(object_expression->type, value_expression->type, value_expression->location);
    return Checked_Assignment_Statement__create(parsed_statement->super.location, object_expression, value_expression);
}

Checked_Statements* Checker__check_statements(Checker* self, Parsed_Statements* parsed_statements);

Checked_Block_Statement* Checker__check_block_statement(Checker* self, Parsed_Block_Statement* parsed_statement) {
    Checked_Statements* statements = Checker__check_statements(self, parsed_statement->statements);
    return Checked_Block_Statement__create(parsed_statement->super.location, statements);
}

Checked_Break_Statement* Checker__check_break_statement(Checker* self, Parsed_Break_Statement* parsed_statement) {
    return Checked_Break_Statement__create(parsed_statement->super.location);
}

Checked_Expression_Statement* Checker__check_expression_statement(Checker* self, Parsed_Expression_Statement* parsed_statement) {
    Checked_Expression* expression = Checker__check_expression(self, parsed_statement->expression);
    if (!Checked_Type__equals((Checked_Type*) Checker__get_builtin_type(self, CHECKED_TYPE_KIND__VOID), expression->type)) {
        // TODO: Source_Location__warning(expression->location, String__create_from("Unused result value"));
    }
    return Checked_Expression_Statement__create(parsed_statement->super.location, expression);
}

Checked_If_Statement* Checker__check_if_statement(Checker* self, Parsed_If_Statement* parsed_statement) {
    Checked_Expression* considition_expression = Checker__check_expression(self, parsed_statement->condition_expression);
    Checked_Type__expect_same_type((Checked_Type*) Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL), considition_expression->type, considition_expression->location);
    Checked_Statement* true_statement = Checker__check_statement(self, parsed_statement->true_statement);
    Checked_Statement* false_statement = null;
    if (parsed_statement->false_statement != null) {
        false_statement = Checker__check_statement(self, parsed_statement->false_statement);
    }
    return Checked_If_Statement__create(parsed_statement->super.location, considition_expression, true_statement, false_statement);
}

Checked_Return_Statement* Checker__check_return_statement(Checker* self, Parsed_Return_Statement* parsed_statement) {
    Checked_Expression* expression = null;
    if (parsed_statement->expression != null) {
        expression = Checker__check_expression(self, parsed_statement->expression);
        Checked_Type__expect_same_type(self->return_type, expression->type, expression->location);
    } else if (self->return_type->kind != CHECKED_TYPE_KIND__VOID) {
        Source_Location__error(parsed_statement->super.location, String__create_from("Missing expression"));
        abort();
    }
    return Checked_Return_Statement__create(parsed_statement->super.location, expression);
}

Checked_Variable_Statement* Checker__check_variable_statement(Checker* self, Parsed_Variable_Statement* parsed_statement) {
    Checked_Type* type = Checker__resolve_type(self, parsed_statement->type);
    Checked_Expression* expression = null;
    if (parsed_statement->expression != null) {
        expression = Checker__check_expression(self, parsed_statement->expression);
        Checked_Type__expect_same_type(type, expression->type, expression->location);
    }
    Checked_Variable_Symbol* variable = Checked_Variable__create(parsed_statement->super.name->location, parsed_statement->super.name->lexeme, type);
    Checked_Symbols__append_symbol(self->symbols, (Checked_Symbol*) variable);
    return Checked_Variable_Statement__create(parsed_statement->super.super.location, variable, expression, parsed_statement->is_external);
}

Checked_While_Statement* Checker__check_while_statement(Checker* self, Parsed_While_Statement* parsed_statement) {
    Checked_Expression* considition_expression = Checker__check_expression(self, parsed_statement->condition_expression);
    Checked_Type__expect_same_type((Checked_Type*) Checker__get_builtin_type(self, CHECKED_TYPE_KIND__BOOL), considition_expression->type, considition_expression->location);
    Checked_Statement* body_statement = Checker__check_statement(self, parsed_statement->body_statement);
    return Checked_While_Statement__create(parsed_statement->super.location, considition_expression, body_statement);
}

void Checker__check_function_declaration(Checker* self, Parsed_Function_Statement* parsed_statement) {
    String* function_name = parsed_statement->super.name->lexeme;
    Checked_Type* function_return_type = Checker__resolve_type(self, parsed_statement->return_type);
    Checked_Function_Parameter* function_first_parameter = null;
    Parsed_Function_Parameter* parsed_parameter = parsed_statement->first_parameter;
    if (parsed_parameter != null) {
        function_first_parameter = Checked_Function_Parameter__create(parsed_parameter->name->location, parsed_parameter->name->lexeme, Checker__resolve_type(self, parsed_parameter->type));
        Checked_Function_Parameter* function_last_parameter = function_first_parameter;
        parsed_parameter = parsed_parameter->next_parameter;
        while (parsed_parameter != null) {
            Checked_Function_Parameter* function_parameter = Checked_Function_Parameter__create(parsed_parameter->name->location, parsed_parameter->name->lexeme, Checker__resolve_type(self, parsed_parameter->type));
            function_last_parameter->next_parameter = function_parameter;
            function_last_parameter = function_parameter;
            parsed_parameter = parsed_parameter->next_parameter;
        }
    }
    Checked_Function_Type* function_type = Checked_Function_Type__create(parsed_statement->super.super.location, function_name, function_return_type);
    function_type->first_parameter = function_first_parameter;

    Checked_Symbol* other_symbol = Checked_Symbols__find_sibling_symbol(self->symbols, function_name);
    if (other_symbol != null) {
        if (other_symbol->kind != CHECKED_SYMBOL_KIND__FUNCTION || !Checked_Type__equals((Checked_Type*) function_type, (Checked_Type*) ((Checked_Function_Symbol*) other_symbol)->function_type)) {
            TODO("Report function redeclaration");
            abort();
        }
    } else {
        Checked_Symbols__append_symbol(self->symbols, (Checked_Symbol*) Checked_Function_Symbol__create(parsed_statement->super.name->location, function_name, function_type));
    }
}

Checked_Statement* Checker__check_statement(Checker* self, Parsed_Statement* parsed_statement) {
    if (parsed_statement->kind == PARSED_STATEMENT_KIND__ASSIGNMENT) {
        return (Checked_Statement*) Checker__check_assignment_statement(self, (Parsed_Assignment_Statement*) parsed_statement);
    } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__BLOCK) {
        return (Checked_Statement*) Checker__check_block_statement(self, (Parsed_Block_Statement*) parsed_statement);
    } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__BREAK) {
        return (Checked_Statement*) Checker__check_break_statement(self, (Parsed_Break_Statement*) parsed_statement);
    } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__EXPRESSION) {
        return (Checked_Statement*) Checker__check_expression_statement(self, (Parsed_Expression_Statement*) parsed_statement);
    } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__IF) {
        return (Checked_Statement*) Checker__check_if_statement(self, (Parsed_If_Statement*) parsed_statement);
    } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__RETURN) {
        return (Checked_Statement*) Checker__check_return_statement(self, (Parsed_Return_Statement*) parsed_statement);
    } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__VARIABLE) {
        return (Checked_Statement*) Checker__check_variable_statement(self, (Parsed_Variable_Statement*) parsed_statement);
    } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__WHILE) {
        return (Checked_Statement*) Checker__check_while_statement(self, (Parsed_While_Statement*) parsed_statement);
    }
    Source_Location__error(parsed_statement->location, String__create_from("Unsupported statement"));
    abort();
}

Checked_Statements* Checker__check_statements(Checker* self, Parsed_Statements* parsed_statements) {
    // Create and push block symbols
    self->symbols = Checked_Symbols__create(self->symbols);

    Checked_Statements* checked_statements = Checked_Statements__create();
    Parsed_Statement* parsed_statement = parsed_statements->first_statement;
    while (parsed_statement != null) {
        Checked_Statement* checked_statement = Checker__check_statement(self, parsed_statement);
        Checked_Statements__append(checked_statements, checked_statement);
        parsed_statement = parsed_statement->next_statement;
    }

    // Pop block symbols
    self->symbols = self->symbols->parent;

    return checked_statements;
}

void Checker__check_function_definition(Checker* self, Parsed_Function_Statement* parsed_statement) {
    Checked_Symbol* symbol = Checked_Symbols__find_sibling_symbol(self->symbols, parsed_statement->super.name->lexeme);
    if (symbol == null || symbol->kind != CHECKED_SYMBOL_KIND__FUNCTION) {
        TODO("Report missing function symbol");
        abort();
    }
    Checked_Function_Symbol* function_symbol = (Checked_Function_Symbol*) symbol;
    Checked_Function_Type* function_type = function_symbol->function_type;
    self->return_type = function_type->return_type;

    // Create and push function symbols
    self->symbols = Checked_Symbols__create(self->symbols);

    if (function_type->first_parameter != null) {
        // Create a symbol for each function parameter
        Checked_Function_Parameter* parameter = function_type->first_parameter;
        while (parameter != null) {
            Checked_Symbols__append_symbol(self->symbols, (Checked_Symbol*) Checked_Function_Parameter_Symbol__create(parameter->location, parameter->name, parameter->type));
            parameter = parameter->next_parameter;
        }
    }

    // Check statements
    function_symbol->checked_statements = Checker__check_statements(self, parsed_statement->statements);

    // Pop function symbols
    self->symbols = self->symbols->parent;
}

Checked_Source* Checker__check_source(Checker* self, Parsed_Source* parsed_source) {
    Checked_Statements* checked_statements = Checked_Statements__create();

    Parsed_Statement* parsed_statement;

    // Check all declared types
    parsed_statement = parsed_source->statements->first_statement;
    while (parsed_statement != null) {
        if (parsed_statement->kind == PARSED_STATEMENT_KIND__STRUCT) {
            Checker__check_struct_statement(self, (Parsed_Struct_Statement*) parsed_statement);
        } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__ENUM) {
            Checker__check_enum_statement(self, (Parsed_Enum_Statement*) parsed_statement);
        } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__FUNCTION_TYPE) {
            Checker__check_function_type_statement(self, (Parsed_Function_Type_Statement*) parsed_statement);
        }
        parsed_statement = parsed_statement->next_statement;
    }

    // Collect other declarations
    parsed_statement = parsed_source->statements->first_statement;
    while (parsed_statement != null) {
        Checked_Statement* checked_statement = null;
        if (parsed_statement->kind == PARSED_STATEMENT_KIND__FUNCTION) {
            Checker__check_function_declaration(self, (Parsed_Function_Statement*) parsed_statement);
        } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__VARIABLE) {
            checked_statement = (Checked_Statement*) Checker__check_variable_statement(self, (Parsed_Variable_Statement*) parsed_statement);
        } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__STRUCT) {
            // ignored
        } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__ENUM) {
            // ignored
        } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__FUNCTION_TYPE) {
            // ignored
        } else {
            Source_Location__error(parsed_statement->location, String__create_from("Unsupported statement"));
            abort();
        }
        if (checked_statement != null) {
            Checked_Statements__append(checked_statements, checked_statement);
        }
        parsed_statement = parsed_statement->next_statement;
    }

    // Check function definitions
    parsed_statement = parsed_source->statements->first_statement;
    while (parsed_statement != null) {
        if (parsed_statement->kind == PARSED_STATEMENT_KIND__FUNCTION) {
            Parsed_Function_Statement* function_statement = (Parsed_Function_Statement*) parsed_statement;
            if (function_statement->statements != null) {
                Checker__check_function_definition(self, function_statement);
            }
        } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__VARIABLE) {
            // ignored
        } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__STRUCT) {
            // ignored
        } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__ENUM) {
            // ignored
        } else if (parsed_statement->kind == PARSED_STATEMENT_KIND__FUNCTION_TYPE) {
            // ignored
        } else {
            Source_Location__error(parsed_statement->location, String__create_from("Unsupported statement"));
            abort();
        }
        parsed_statement = parsed_statement->next_statement;
    }

    Checked_Source* checked_source = (Checked_Source*) malloc(sizeof(Checked_Source));
    checked_source->first_symbol = self->symbols->first_symbol;
    checked_source->statements = checked_statements;
    return checked_source;
}

Checked_Source* check(Parsed_Source* parsed_source) {
    Checker* type_checker = Checker__create();

    return Checker__check_source(type_checker, parsed_source);
}

#pragma endregion
#pragma region Generator

typedef struct Generator {
    File* file;
    uint16_t identation;
} Generator;

void Generator__write_source_location(Generator* self, Source_Location* location) {
    File__write_cstring(self->file, "#line ");
    File__write_int32_t(self->file, (int32_t) location->line);
    File__write_cstring(self->file, " \"./compiler/ReCode.c\"\n");
}

void Generator__generate_expression(Generator* self, Checked_Expression* expression);

void Generator__generate_add_expression(Generator* self, Checked_Add_Expression* expression) {
    Generator__generate_expression(self, expression->super.left_expression);
    File__write_cstring(self->file, " + ");
    Generator__generate_expression(self, expression->super.right_expression);
}

void Generator__generate_address_of_expression(Generator* self, Checked_Address_Of_Expression* expression) {
    File__write_cstring(self->file, "&");
    Generator__generate_expression(self, expression->super.other_expression);
}

void Generator__generate_array_access_expression(Generator* self, Checked_Array_Access_Expression* expression) {
    Generator__generate_expression(self, expression->array_expression);
    File__write_cstring(self->file, "[");
    Generator__generate_expression(self, expression->index_expression);
    File__write_cstring(self->file, "]");
}

void Generator__generate_bool_expression(Generator* self, Checked_Bool_Expression* expression) {
    if (expression->value) {
        File__write_cstring(self->file, "true");
    } else {
        File__write_cstring(self->file, "false");
    }
}

void Generator__generate_call_expression(Generator* self, Checked_Call_Expression* expression) {
    Generator__generate_expression(self, expression->callee_expression);
    File__write_cstring(self->file, "(");
    Checked_Call_Argument* argument = expression->first_argument;
    while (argument != null) {
        Generator__generate_expression(self, argument->expression);
        argument = argument->next_argument;
        if (argument != null) {
            File__write_cstring(self->file, ", ");
        }
    }
    File__write_cstring(self->file, ")");
}

void Generator__generate_cast_expression(Generator* self, Checked_Cast_Expression* expression) {
    File__write_cstring(self->file, "(");
    File__write_checked_type(self->file, expression->super.type);
    File__write_cstring(self->file, ") ");
    Generator__generate_expression(self, expression->other_expression);
}

void File__write_octal_escaped_char(File* stream, char value) {
    File__write_char(stream, '\\');
    if (value > (char) 64) {
        File__write_char(stream, value / (char) 64 % (char) 8 + '0');
    }
    if (value > (char) 8) {
        File__write_char(stream, value / (char) 8 % (char) 8 + '0');
    }
    File__write_char(stream, value % (char) 8 + '0');
}

void File__write_escaped_char(File* stream, char ch) {
    if (ch < (char) 32) {
        if (ch == '\n') {
            File__write_cstring(stream, "\\n");
        } else if (ch == '\t') {
            File__write_cstring(stream, "\\t");
        } else {
            File__write_octal_escaped_char(stream, ch);
        }
    } else if (ch < (char) 127) {
        if (ch == '\"') {
            File__write_cstring(stream, "\\\"");
        } else if (ch == '\'') {
            File__write_cstring(stream, "\\'");
        } else if (ch == '\\') {
            File__write_cstring(stream, "\\\\");
        } else {
            File__write_char(stream, ch);
        }
    } else {
        File__write_octal_escaped_char(stream, ch);
    }
}

void Generator__generate_character_expression(Generator* self, Checked_Character_Expression* expression) {
    File__write_char(self->file, '\'');
    File__write_escaped_char(self->file, expression->value);
    File__write_char(self->file, '\'');
}

void Generator__generate_divide_expression(Generator* self, Checked_Divide_Expression* expression) {
    Generator__generate_expression(self, expression->super.left_expression);
    File__write_cstring(self->file, " / ");
    Generator__generate_expression(self, expression->super.right_expression);
}

void Generator__generate_equals_expression(Generator* self, Checked_Equals_Expression* expression) {
    Generator__generate_expression(self, expression->super.left_expression);
    File__write_cstring(self->file, " == ");
    Generator__generate_expression(self, expression->super.right_expression);
}

void Generator__generate_greater_expression(Generator* self, Checked_Greater_Expression* expression) {
    Generator__generate_expression(self, expression->super.left_expression);
    File__write_cstring(self->file, " > ");
    Generator__generate_expression(self, expression->super.right_expression);
}

void Generator__generate_greater_or_equals_expression(Generator* self, Checked_Greater_Or_Equals_Expression* expression) {
    Generator__generate_expression(self, expression->super.left_expression);
    File__write_cstring(self->file, " >= ");
    Generator__generate_expression(self, expression->super.right_expression);
}

void Generator__generate_group_expression(Generator* self, Checked_Group_Expression* expression) {
    File__write_cstring(self->file, "(");
    Generator__generate_expression(self, expression->other_expression);
    File__write_cstring(self->file, ")");
}

void Generator__generate_integer_expression(Generator* self, Checked_Integer_Expression* expression) {
    File__write_uint64_t(self->file, expression->value);
}

void Generator__generate_less_expression(Generator* self, Checked_Less_Expression* expression) {
    Generator__generate_expression(self, expression->super.left_expression);
    File__write_cstring(self->file, " < ");
    Generator__generate_expression(self, expression->super.right_expression);
}

void Generator__generate_less_or_equals_expression(Generator* self, Checked_Less_Or_Equals_Expression* expression) {
    Generator__generate_expression(self, expression->super.left_expression);
    File__write_cstring(self->file, " <= ");
    Generator__generate_expression(self, expression->super.right_expression);
}

void Generator__generate_logic_and_expression(Generator* self, Checked_Logic_And_Expression* expression) {
    Generator__generate_expression(self, expression->super.left_expression);
    File__write_cstring(self->file, " && ");
    Generator__generate_expression(self, expression->super.right_expression);
}

void Generator__generate_logic_or_expression(Generator* self, Checked_Logic_Or_Expression* expression) {
    Generator__generate_expression(self, expression->super.left_expression);
    File__write_cstring(self->file, " || ");
    Generator__generate_expression(self, expression->super.right_expression);
}

void Generator__generate_member_access_expression(Generator* self, Checked_Member_Access_Expression* expression) {
    Generator__generate_expression(self, expression->object_expression);
    if (expression->object_expression->type->kind == CHECKED_TYPE_KIND__POINTER) {
        File__write_cstring(self->file, "->");
    } else {
        File__write_cstring(self->file, ".");
    }
    File__write_string(self->file, expression->member->name);
}

void Generator__generate_minus_expression(Generator* self, Checked_Minus_Expression* expression) {
    File__write_cstring(self->file, "-");
    Generator__generate_expression(self, expression->super.other_expression);
}

void Generator__generate_modulo_expression(Generator* self, Checked_Modulo_Expression* expression) {
    Generator__generate_expression(self, expression->super.left_expression);
    File__write_cstring(self->file, " % ");
    Generator__generate_expression(self, expression->super.right_expression);
}

void Generator__generate_multiply_expression(Generator* self, Checked_Multiply_Expression* expression) {
    Generator__generate_expression(self, expression->super.left_expression);
    File__write_cstring(self->file, " * ");
    Generator__generate_expression(self, expression->super.right_expression);
}

void Generator__generate_not_expression(Generator* self, Checked_Not_Expression* expression) {
    File__write_cstring(self->file, "!");
    Generator__generate_expression(self, expression->super.other_expression);
}

void Generator__generate_not_equals_expression(Generator* self, Checked_Not_Equals_Expression* expression) {
    Generator__generate_expression(self, expression->super.left_expression);
    File__write_cstring(self->file, " != ");
    Generator__generate_expression(self, expression->super.right_expression);
}

void Generator__generate_null_expression(Generator* self, Checked_Null_Expression* expression) {
    File__write_cstring(self->file, "NULL");
}

void Generator__generate_sizeof_expression(Generator* self, Checked_Sizeof_Expression* expression) {
    File__write_cstring(self->file, "sizeof(");
    File__write_checked_type(self->file, expression->sized_type);
    File__write_cstring(self->file, ")");
}

void Generator__generate_string_expression(Generator* self, Checked_String_Expression* expression) {
    File__write_char(self->file, '"');
    size_t index = (size_t) 0;
    while (index < expression->value->length) {
        File__write_escaped_char(self->file, expression->value->data[index]);
        index = index + (size_t) 1;
    }
    File__write_char(self->file, '"');
}

void Generator__generate_substract_expression(Generator* self, Checked_Substract_Expression* expression) {
    Generator__generate_expression(self, expression->super.left_expression);
    File__write_cstring(self->file, " - ");
    Generator__generate_expression(self, expression->super.right_expression);
}

void Generator__generate_symbol_expression(Generator* self, Checked_Symbol_Expression* expression) {
    File__write_string(self->file, expression->symbol->name);
}

void Generator__generate_expression(Generator* self, Checked_Expression* expression) {
    if (expression->kind == CHECKED_EXPRESSION_KIND__ADD) {
        Generator__generate_add_expression(self, (Checked_Add_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__ADDRESS_OF) {
        Generator__generate_address_of_expression(self, (Checked_Address_Of_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__ARRAY_ACCESS) {
        Generator__generate_array_access_expression(self, (Checked_Array_Access_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__BOOL) {
        Generator__generate_bool_expression(self, (Checked_Bool_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__CALL) {
        Generator__generate_call_expression(self, (Checked_Call_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__CAST) {
        Generator__generate_cast_expression(self, (Checked_Cast_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__CHARACTER) {
        Generator__generate_character_expression(self, (Checked_Character_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__DIVIDE) {
        Generator__generate_divide_expression(self, (Checked_Divide_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__EQUALS) {
        Generator__generate_equals_expression(self, (Checked_Equals_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__GREATER) {
        Generator__generate_greater_expression(self, (Checked_Greater_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__GREATER_OR_EQUALS) {
        Generator__generate_greater_or_equals_expression(self, (Checked_Greater_Or_Equals_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__GROUP) {
        Generator__generate_group_expression(self, (Checked_Group_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__INTEGER) {
        Generator__generate_integer_expression(self, (Checked_Integer_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__LESS) {
        Generator__generate_less_expression(self, (Checked_Less_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__LESS_OR_EQUALS) {
        Generator__generate_less_or_equals_expression(self, (Checked_Less_Or_Equals_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__LOGIC_AND) {
        Generator__generate_logic_and_expression(self, (Checked_Logic_And_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__LOGIC_OR) {
        Generator__generate_logic_or_expression(self, (Checked_Logic_Or_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__MEMBER_ACCESS) {
        Generator__generate_member_access_expression(self, (Checked_Member_Access_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__MINUS) {
        Generator__generate_minus_expression(self, (Checked_Minus_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__MODULO) {
        Generator__generate_modulo_expression(self, (Checked_Modulo_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__MULTIPLY) {
        Generator__generate_multiply_expression(self, (Checked_Multiply_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__NOT) {
        Generator__generate_not_expression(self, (Checked_Not_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__NOT_EQUALS) {
        Generator__generate_not_equals_expression(self, (Checked_Not_Equals_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__NULL) {
        Generator__generate_null_expression(self, (Checked_Null_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__SIZEOF) {
        Generator__generate_sizeof_expression(self, (Checked_Sizeof_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__STRING) {
        Generator__generate_string_expression(self, (Checked_String_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__SUBSTRACT) {
        Generator__generate_substract_expression(self, (Checked_Substract_Expression*) expression);
    } else if (expression->kind == CHECKED_EXPRESSION_KIND__SYMBOL) {
        Generator__generate_symbol_expression(self, (Checked_Symbol_Expression*) expression);
    } else {
        Source_Location__error(expression->location, String__create_from("Unsupported expression"));
        abort();
    }
}

void Generator__write_identation(Generator* self) {
    uint16_t identation = self->identation;
    while (identation > (uint16_t) 0) {
        File__write_cstring(self->file, "    ");
        identation = identation - (uint16_t) 1;
    }
}

void Generator__generate_statement(Generator* self, Checked_Statement* statement);
void Generator__generate_statements(Generator* self, Checked_Statements* statements);

void Generator__generate_assignment_statement(Generator* self, Checked_Assignment_Statement* statement) {
    Generator__generate_expression(self, statement->object_expression);
    File__write_cstring(self->file, " = ");
    Generator__generate_expression(self, statement->value_expression);
    File__write_cstring(self->file, ";");
}

void Generator__generate_block_statement(Generator* self, Checked_Block_Statement* statement) {
    File__write_cstring(self->file, "{\n");
    Generator__generate_statements(self, statement->statements);
    Generator__write_identation(self);
    File__write_cstring(self->file, "}");
}

void Generator__generate_break_statement(Generator* self, Checked_Break_Statement* statement) {
    File__write_cstring(self->file, "break;");
}

void Generator__generate_expression_statement(Generator* self, Checked_Expression_Statement* statement) {
    Generator__generate_expression(self, statement->expression);
    File__write_cstring(self->file, ";");
}

void Generator__generate_if_statement(Generator* self, Checked_If_Statement* statement) {
    File__write_cstring(self->file, "if (");
    Generator__generate_expression(self, statement->condition_expression);
    File__write_cstring(self->file, ") ");
    Generator__generate_statement(self, statement->true_statement);
    if (statement->false_statement != null) {
        File__write_cstring(self->file, " else ");
        Generator__generate_statement(self, statement->false_statement);
    }
}

void Generator__generate_return_statement(Generator* self, Checked_Return_Statement* statement) {
    File__write_cstring(self->file, "return");
    if (statement->expression != null) {
        File__write_cstring(self->file, " ");
        Generator__generate_expression(self, statement->expression);
    }
    File__write_cstring(self->file, ";");
}

void Generator__generate_variable_statement(Generator* self, Checked_Variable_Statement* statement) {
    if (statement->is_external) {
        File__write_cstring(self->file, "extern ");
    }
    File__write_checked_type(self->file, statement->variable->super.type);
    File__write_char(self->file, ' ');
    File__write_string(self->file, statement->variable->super.name);
    if (statement->expression != null) {
        File__write_cstring(self->file, " = ");
        Generator__generate_expression(self, statement->expression);
    }
    File__write_cstring(self->file, ";");
}

void Generator__generate_while_statement(Generator* self, Checked_While_Statement* statement) {
    File__write_cstring(self->file, "while (");
    Generator__generate_expression(self, statement->condition_expression);
    File__write_cstring(self->file, ") ");
    Generator__generate_statement(self, statement->body_statement);
}

void Generator__generate_statement(Generator* self, Checked_Statement* statement) {
    if (statement->kind == CHECKED_STATEMENT_KIND__ASSIGNMENT) {
        Generator__generate_assignment_statement(self, (Checked_Assignment_Statement*) statement);
    } else if (statement->kind == CHECKED_STATEMENT_KIND__BLOCK) {
        Generator__generate_block_statement(self, (Checked_Block_Statement*) statement);
    } else if (statement->kind == CHECKED_STATEMENT_KIND__BREAK) {
        Generator__generate_break_statement(self, (Checked_Break_Statement*) statement);
    } else if (statement->kind == CHECKED_STATEMENT_KIND__EXPRESSION) {
        Generator__generate_expression_statement(self, (Checked_Expression_Statement*) statement);
    } else if (statement->kind == CHECKED_STATEMENT_KIND__IF) {
        Generator__generate_if_statement(self, (Checked_If_Statement*) statement);
    } else if (statement->kind == CHECKED_STATEMENT_KIND__RETURN) {
        Generator__generate_return_statement(self, (Checked_Return_Statement*) statement);
    } else if (statement->kind == CHECKED_STATEMENT_KIND__VARIABLE) {
        Generator__generate_variable_statement(self, (Checked_Variable_Statement*) statement);
    } else if (statement->kind == CHECKED_STATEMENT_KIND__WHILE) {
        Generator__generate_while_statement(self, (Checked_While_Statement*) statement);
    } else {
        Source_Location__error(statement->location, String__create_from("Unsupported statement"));
        abort();
    }
}

void Generator__generate_statements(Generator* self, Checked_Statements* statements) {
    self->identation = self->identation + (uint16_t) 1;

    Checked_Statement* statement = statements->first_statement;
    while (statement != null) {
        Generator__write_source_location(self, statement->location);

        Generator__write_identation(self);

        Generator__generate_statement(self, statement);

        File__write_cstring(self->file, "\n");

        statement = statement->next_statement;
    }

    self->identation = self->identation - (uint16_t) 1;
}

void Generator__generate_enum(Generator* self, Checked_Enum_Type* enum_type) {
    File__write_checked_type(self->file, (Checked_Type*) enum_type);
    File__write_cstring(self->file, " {\n");
    Checked_Enum_Member* enum_member = enum_type->first_member;
    while (enum_member != null) {
        File__write_char(self->file, '\t');
        File__write_string(self->file, enum_member->name);
        enum_member = enum_member->next_member;
        if (enum_member != null) {
            File__write_cstring(self->file, ",\n");
        } else {
            File__write_char(self->file, '\n');
        }
    }
    File__write_cstring(self->file, "};\n");
}

void Generator__declare_function(Generator* self, Checked_Function_Symbol* function_symbol) {
    File__write_checked_type(self->file, (Checked_Type*) function_symbol->function_type);
    File__write_cstring(self->file, ";\n");
}

void Generator__generate_function(Generator* self, Checked_Function_Symbol* function_symbol) {
    if (function_symbol->checked_statements == null) {
        return;
    }
    Generator__write_source_location(self, function_symbol->super.location);
    File__write_checked_type(self->file, (Checked_Type*) function_symbol->function_type);
    File__write_cstring(self->file, " {\n");
    Generator__generate_statements(self, function_symbol->checked_statements);
    File__write_cstring(self->file, "}\n\n");
}

void Generator__declare_struct(Generator* self, Checked_Struct_Type* struct_type) {
    File__write_checked_type(self->file, (Checked_Type*) struct_type);
    File__write_cstring(self->file, ";\n");
}

void Generator__generate_struct(Generator* self, Checked_Struct_Type* struct_type) {
    Checked_Struct_Member* struct_member = struct_type->first_member;
    if (struct_member == null) {
        return;
    }
    File__write_checked_type(self->file, (Checked_Type*) struct_type);
    File__write_cstring(self->file, " {\n");
    while (struct_member != null) {
        File__write_char(self->file, '\t');
        File__write_checked_type(self->file, struct_member->type);
        File__write_char(self->file, ' ');
        File__write_string(self->file, struct_member->name);
        File__write_cstring(self->file, ";\n");
        struct_member = struct_member->next_member;
    }
    File__write_cstring(self->file, "};\n\n");
}

void generate(File* file, Checked_Source* checked_source) {
    Generator generator;
    generator.file = file;
    generator.identation = (uint16_t) 0;

    Checked_Symbol* checked_symbol;

    File__write_cstring(generator.file, "/* Copyright (C) 2023 Stefan Selariu */\n");
    File__write_cstring(generator.file, "\n");
    File__write_cstring(generator.file, "#include <inttypes.h>\n");
    File__write_cstring(generator.file, "#include <stdbool.h>\n");
    File__write_cstring(generator.file, "#include <stddef.h>\n");
    File__write_cstring(generator.file, "\n");

    // Declare all defined types
    checked_symbol = checked_source->first_symbol;
    while (checked_symbol != null) {
        if (checked_symbol->kind == CHECKED_SYMBOL_KIND__TYPE) {
            Checked_Named_Type* named_type = ((Checked_Type_Symbol*) checked_symbol)->named_type;
            if (named_type->super.kind == CHECKED_TYPE_KIND__STRUCT) {
                Generator__declare_struct(&generator, (Checked_Struct_Type*) named_type);
            } else if (named_type->super.kind == CHECKED_TYPE_KIND__ENUM) {
                Generator__generate_enum(&generator, (Checked_Enum_Type*) named_type);
            }
        }
        checked_symbol = checked_symbol->next_symbol;
    }
    File__write_cstring(generator.file, "\n");

    // Generate all defined types
    checked_symbol = checked_source->first_symbol;
    while (checked_symbol != null) {
        if (checked_symbol->kind == CHECKED_SYMBOL_KIND__TYPE) {
            Checked_Named_Type* named_type = ((Checked_Type_Symbol*) checked_symbol)->named_type;
            if (named_type->super.kind == CHECKED_TYPE_KIND__STRUCT) {
                Generator__generate_struct(&generator, (Checked_Struct_Type*) named_type);
            }
        }
        checked_symbol = checked_symbol->next_symbol;
    }

    // Declare all global variables
    Checked_Statement* checked_statement = checked_source->statements->first_statement;
    while (checked_statement != null) {
        if (checked_statement->kind == CHECKED_STATEMENT_KIND__VARIABLE) {
            Generator__generate_variable_statement(&generator, (Checked_Variable_Statement*) checked_statement);
            File__write_cstring(generator.file, "\n");
        } else {
            Source_Location__error(checked_statement->location, String__create_from("Unsupported statement"));
            abort();
        }
        checked_statement = checked_statement->next_statement;
    }
    File__write_cstring(generator.file, "\n");

    // Declare all defined functions
    checked_symbol = checked_source->first_symbol;
    while (checked_symbol != null) {
        if (checked_symbol->kind == CHECKED_SYMBOL_KIND__FUNCTION) {
            Generator__declare_function(&generator, (Checked_Function_Symbol*) checked_symbol);
        }
        checked_symbol = checked_symbol->next_symbol;
    }
    File__write_cstring(generator.file, "\n");

    // Generate all defined functions
    checked_symbol = checked_source->first_symbol;
    while (checked_symbol != null) {
        if (checked_symbol->kind == CHECKED_SYMBOL_KIND__FUNCTION) {
            Generator__generate_function(&generator, (Checked_Function_Symbol*) checked_symbol);
        }
        checked_symbol = checked_symbol->next_symbol;
    }
}

#pragma endregion

int32_t main() {
    Source* source = Source__create(stdin);
    Parsed_Source* parsed_source = parse(source);
    Checked_Source* checked_source = check(parsed_source);
    generate(stdout, checked_source);
    return 0;
}
