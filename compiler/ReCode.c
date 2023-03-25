// Copyright (C) 2023 Stefan Selariu

// Types

typedef char i8;
typedef short i16;
typedef int i32;
typedef long i64;
typedef long int isize;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;
typedef unsigned long int usize;

typedef enum {
    false = 0,
    true = 1,
} bool;

// LibC

typedef struct FILE File;

extern File *stdin;
extern File *stdout;
extern File *stderr;

extern i32 fgetc(File *stream);
extern i32 fputc(i32 c, File *stream);
extern i32 fputs(const i8 *s, File *stream);

extern void *malloc(usize size);
extern void *realloc(void *ptr, usize size);
extern void free(void *ptr);

extern void abort();

// String

typedef struct {
    u8 *data;
    usize data_size;
    usize length;
} String;

String *String__create_empty(usize data_size) {
    String *string = malloc(sizeof(String));
    string->data = malloc(data_size);
    string->data_size = data_size;
    string->length = 0;
    return string;
}

String *String__create() {
    return String__create_empty(16);
}

String *String__create_from(u8 *data) {
    usize string_length = 0;
    while (true) {
        u8 c = data[string_length];
        if (c == 0) {
            break;
        }
        string_length += 1;
    }
    String *string = malloc(sizeof(String));
    string->data = data;
    string->data_size = string_length + 1;
    string->length = string_length;
    return string;
}

String *String__append_char(String *self, u8 ch) {
    if (self->length >= self->data_size) {
        self->data_size = self->data_size + 16;
        self->data = realloc(self->data, self->data_size);
    }
    self->data[self->length] = ch;
    self->length = self->length + 1;
    return self;
}

// Utils

void pass() {
}

void File__write_char(File *stream, u8 c) {
    fputc(c, stream);
}

void File__write_cstring(File *stream, const i8 *s) {
    fputs(s, stream);
}

void File__write_i32(File *stream, i32 value) {
    if (value < 0) {
        File__write_char(stream, '-');
        File__write_i32(stream, -value);
    } else {
        if (value >= 10) {
            File__write_i32(stream, value / 10);
        }
        File__write_char(stream, value % 10 + '0');
    }
}

void File__write_string(File *self, String *string) {
    usize index = 0;
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
        i32 ch = fgetc(stdin);
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
    u16 line;
    u16 column;
} Token_Location;

Token_Location *Token_Location__create(Source *source, u16 line, u16 column) {
    Token_Location *token_location = malloc(sizeof(Token_Location));
    token_location->source = source;
    token_location->line = line;
    token_location->column = column;
    return token_location;
}

void File__write_token_location(File *stream, Token_Location *self) {
    File__write_cstring(stream, "compiler/ReCode.c:");
    File__write_i32(stream, self->line);
    File__write_char(stream, ':');
    File__write_i32(stream, self->column);
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

void *Token__create(usize size, u16 type, Token_Location *location, String *lexeme) {
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
    u8 value;
} Character_Token;

Character_Token *Character_Token__create(Token_Location *location, String *lexeme, u8 value) {
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
    u64 value;
} Integer_Token;

Integer_Token *Integer_Token__create(Token_Location *location, String *lexeme, u64 value) {
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
    u16 count;
} Space_Token;

Space_Token *Space_Token__create(Token_Location *location, String *lexeme, u16 count) {
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
    usize current_char_index;
    usize current_line;
    usize current_column;
    Token *current_token;
} Scanner;

u8 Scanner__peek_char(Scanner *self) {
    return self->source->content->data[self->current_char_index];
}

u8 Scanner__next_char(Scanner *self) {
    u8 next_char = Scanner__peek_char(self);
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

u8 escape_char_value(u8 c) {
    if (c == 'n') return '\n';
    if (c == '"') return '\"';
    if (c == '\'') return '\'';
    if (c == '\\') return '\\';
    if (c == 't') return '\t';
    if (c == '0') return '\0';
    if (c == 'e') return '\e';
    return -1;
}

bool char_is_end_of_line(u8 c) {
    return c == '\n' || c == '\0';
}

Token *Scanner__scan_character_token(Scanner *self, Token_Location *token_location, String *token_lexeme) {
    if (Scanner__next_char(self) != '\'') {
        panic(String__create_from("Unexpected char"));
    }
    String__append_char(token_lexeme, '\'');

    u8 next_char = Scanner__peek_char(self);
    if (char_is_end_of_line(next_char) || next_char == '\t') {
        return (Token *) Error_Token__create(token_location, token_lexeme);
    }

    String__append_char(token_lexeme, Scanner__next_char(self));
    u8 value = next_char;

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
        if (value == ((u8) -1)) {
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

bool char_is_identifier_start(u8 c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool char_is_identifier_letter(u8 c) {
    return char_is_identifier_start(c) || (c >= '0' && c <= '9');
}

Token *Scanner__scan_identifier_token(Scanner *self, Token_Location *token_location, String *token_lexeme) {
    while (char_is_identifier_letter(Scanner__peek_char(self))) {
        String__append_char(token_lexeme, Scanner__next_char(self));
    }
    return (Token *) Identifier_Token__create(token_location, token_lexeme);
}

bool char_is_digit(u8 c) {
    return c >= '0' && c <= '9';
}

Token *Scanner__scan_integer_token(Scanner *self, Token_Location *token_location, String *token_lexeme) {
    u64 value = 0;
    while (char_is_digit(Scanner__peek_char(self))) {
        u8 c = Scanner__next_char(self);
        value = value * 10 + (c - '0');
        String__append_char(token_lexeme, c);
    }
    return (Token *) Integer_Token__create(token_location, token_lexeme, value);
}

bool char_is_space(u8 c) {
    return c == ' ';
}

Token *Scanner__scan_space_token(Scanner *self, Token_Location *token_location, String *token_lexeme) {
    u16 count = 0;
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
        u8 next_char = Scanner__peek_char(self);
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
            if (next_char == ((u8) -1)) {
                return (Token *) Error_Token__create(token_location, token_lexeme);
            }
        }

        String__append_char(value, next_char);
    }
}

Token *Scanner__scan_token(Scanner *self) {
    Token_Location *token_location = Token_Location__create(self->source, self->current_line, self->current_column);
    String *token_lexeme = String__create();

    u8 next_char = Scanner__peek_char(self);

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

Token *Scanner__peek_token(Scanner *self, u8 offset) {
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
    u16 current_identation;
} Parser;

Token *Parser__peek_token(Parser *self, u8 offset) {
    return Scanner__peek_token(self->scanner, offset);
}

Token *Parser__consume_token(Parser *self) {
    Token *token = self->scanner->current_token;
    Scanner__next_token(self->scanner);
    return token;
}

void Parser__consume_comment(Parser *self) {
    Token *token = Parser__consume_token(self);
    if (token->type != TOKEN_TYPE_COMMENT) {
        Token__panic(token, String__create_from("Unexpected token"));
    }
}

void Parser__consume_end_of_line(Parser *self) {
    Token *token = Parser__consume_token(self);
    if (token->type != TOKEN_TYPE_END_OF_LINE) {
        if (token->type == TOKEN_TYPE_END_OF_FILE) {
            Token__warning(token, String__create_from("Unexpected end of line"));
        } else {
            Token__panic(token, String__create_from("Unexpected token"));
        }
    }
}

void Parser__consume_space(Parser *self, u16 identation) {
    Token *token = Parser__consume_token(self);
    if (token->type != TOKEN_TYPE_SPACE) {
        Token__panic(token, String__create_from("Unexpected token"));
    }
    Space_Token *space_token = (Space_Token *) token;
    if (space_token->count != identation * 4) {
        Token__warning(token, String__create_from("Unexpected identation"));
    }
}

bool Parser__consume_empty_line(Parser *self) {
    if (Parser__peek_token(self, 0)->type == TOKEN_TYPE_SPACE && Parser__peek_token(self, 1)->type == TOKEN_TYPE_COMMENT && (Parser__peek_token(self, 2)->type == TOKEN_TYPE_END_OF_LINE || Parser__peek_token(self, 2)->type == TOKEN_TYPE_END_OF_FILE)) {
        Parser__consume_space(self, self->current_identation);
        Parser__consume_comment(self);
        Parser__consume_end_of_line(self);
        return true;
    } else if (Parser__peek_token(self, 0)->type == TOKEN_TYPE_COMMENT && (Parser__peek_token(self, 1)->type == TOKEN_TYPE_END_OF_LINE || Parser__peek_token(self, 1)->type == TOKEN_TYPE_END_OF_FILE)) {
        Parser__consume_comment(self);
        Parser__consume_end_of_line(self);
        return true;
    } else if (Parser__peek_token(self, 0)->type == TOKEN_TYPE_SPACE && (Parser__peek_token(self, 1)->type == TOKEN_TYPE_END_OF_LINE || Parser__peek_token(self, 1)->type == TOKEN_TYPE_END_OF_FILE)) {
        Parser__consume_space(self, 0);
        Parser__consume_end_of_line(self);
        return true;
    } else if (Parser__peek_token(self, 0)->type == TOKEN_TYPE_END_OF_LINE || Parser__peek_token(self, 0)->type == TOKEN_TYPE_END_OF_FILE) {
        Parser__consume_end_of_line(self);
        return true;
    }
    return false;
}

// statement
//      | typedef
AST_Statement *Parser__parse_statement(Parser *self) {
    while (Parser__consume_empty_line(self));

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

i32 main() {
    Source *source = Source__create(stdin);

    AST_Compilation_Unit *compilation_unit = parse(source);

    return 0;
}
