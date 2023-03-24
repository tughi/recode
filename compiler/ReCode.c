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
    while (1) {
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

void File__write_string(File *self, String *string) {
    usize index = 0;
    while (index < string->length) {
        fputc(string->data[index], self);
        index = index + 1;
    }
}

// Utils

void pass() {
}

void panic(String *message) {
    File__write_string(stderr, message);
    abort();
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

    String__append_char(source_content, '\0'); // simplifies "end of source" detection

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

typedef enum {
    TOKEN_TYPE_END_OF_FILE,
    TOKEN_TYPE_OTHER,
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

typedef struct {
    Token_Type type;
    Source *source;
    String *lexeme;
    Token *next_token;
} End_Of_File_Token;

End_Of_File_Token *End_Of_File_Token__create(Token_Location *location, String *lexeme) {
    End_Of_File_Token *token = Token__create(sizeof(End_Of_File_Token), TOKEN_TYPE_END_OF_FILE, location, lexeme);
    return token;
}

typedef struct {
    Token_Type type;
    Source *source;
    String *lexeme;
    Token *next_token;
} Other_Token;

Other_Token *Other_Token__create(Token_Location *location, String *lexeme) {
    Other_Token *token = Token__create(sizeof(Other_Token), TOKEN_TYPE_OTHER, location, lexeme);
    return token;
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

Token *Scanner__scan_token(Scanner *self) {
    Token_Location *token_location = Token_Location__create(self->source, self->current_line, self->current_column);
    String *token_lexeme = String__create();

    u8 next_char = Scanner__peek_char(self);

    if (next_char == '\0') {
        Scanner__next_char(self);
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

Scanner *Scanner__create(Source *source) {
    Scanner *scanner = malloc(sizeof(Scanner));
    scanner->source = source;
    scanner->current_char_index = 0;
    scanner->current_line = 1;
    scanner->current_column = 1;

    scanner->current_token = Scanner__scan_token(scanner);

    return scanner;
}

// Main

i32 main() {
    Source *source = Source__create(stdin);
    Scanner *scanner = Scanner__create(source);

    Token *token = scanner->current_token;
    while (token->type != TOKEN_TYPE_END_OF_FILE) {
        File__write_string(stdout, token->lexeme);

        token = Scanner__next_token(scanner);
    }

    return 0;
}
