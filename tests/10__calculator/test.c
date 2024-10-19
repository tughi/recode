#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct Tokenizer;

struct Token;

struct StringBuilder;

struct Writer;

typedef struct FILE FILE;

struct Tokenizer {
    uint8_t *data;
    int32_t index;
};

struct Token {
    uint8_t kind;
    uint8_t *lexeme;
    int32_t value;
};

struct StringBuilder {
    uint8_t *data;
    int32_t data_size;
    int32_t length;
};

struct Writer {
    void *self;
    void (*write_char)(void *self, uint8_t c);
};

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;
struct Tokenizer *__make_Tokenizer_value(struct Tokenizer value);

struct Token *__make_Token_value(struct Token value);

struct StringBuilder *__make_StringBuilder_value(struct StringBuilder value);

struct Writer *__make_Writer_value(struct Writer value);

void main(int32_t argc, uint8_t **argv);

bool pTokenizer__has_next_token(struct Tokenizer *self);

struct Token *pTokenizer__next_token(struct Tokenizer *self);

struct Token *pTokenizer__scan_number_token(struct Tokenizer *self, struct StringBuilder *lexeme_builder);

struct Writer *pWriter__write__1_token(struct Writer *self, struct Token *token);

struct StringBuilder *pStringBuilder__write__1_char(struct StringBuilder *self, uint8_t c);

uint8_t *pStringBuilder__build(struct StringBuilder *self);

void pStringBuilder__write_char(struct StringBuilder *self, uint8_t c);

struct Writer *pWriter__write__1_char(struct Writer *self, uint8_t c);

struct Writer *pWriter__write__1_signed(struct Writer *self, int32_t value);

struct Writer *pWriter__end_line(struct Writer *self);

int32_t fputc(int32_t c, FILE *file);

void pFILE__write_char(FILE *self, uint8_t c);

void *malloc(uint64_t size);

void *realloc(void *block, uint64_t size);

void exit(int32_t code);

struct Tokenizer *__make_Tokenizer_value(struct Tokenizer value) {
    struct Tokenizer *result = (struct Tokenizer *)malloc(sizeof(struct Tokenizer));
    *result = value;
    return result;
}

struct Token *__make_Token_value(struct Token value) {
    struct Token *result = (struct Token *)malloc(sizeof(struct Token));
    *result = value;
    return result;
}

struct StringBuilder *__make_StringBuilder_value(struct StringBuilder value) {
    struct StringBuilder *result = (struct StringBuilder *)malloc(sizeof(struct StringBuilder));
    *result = value;
    return result;
}

struct Writer *__make_Writer_value(struct Writer value) {
    struct Writer *result = (struct Writer *)malloc(sizeof(struct Writer));
    *result = value;
    return result;
}

#line 1 "tests/10__calculator/test.code"
void main(int32_t argc, uint8_t **argv) {
#line 2 "tests/10__calculator/test.code"
    if (argc != 2) {
#line 3 "tests/10__calculator/test.code"
        exit(1);
    }
#line 6 "tests/10__calculator/test.code"
    struct Tokenizer tokenizer = (struct Tokenizer){.data = argv[1], .index = 0};
#line 11 "tests/10__calculator/test.code"
    struct Writer stdout_writer = (struct Writer){.self = stdout, .write_char = (void (*)(void *self, uint8_t c)) pFILE__write_char};
#line 12 "tests/10__calculator/test.code"
    while (pTokenizer__has_next_token(&tokenizer)) {
#line 13 "tests/10__calculator/test.code"
        struct Token *token = pTokenizer__next_token(&tokenizer);
#line 14 "tests/10__calculator/test.code"
        if (token->kind == 0) {
#line 15 "tests/10__calculator/test.code"
            break;
        }
#line 17 "tests/10__calculator/test.code"
        pWriter__end_line(pWriter__write__1_token(&stdout_writer, token));
    }
}

#line 27 "tests/10__calculator/test.code"
bool pTokenizer__has_next_token(struct Tokenizer *self) {
#line 28 "tests/10__calculator/test.code"
    return self->data[self->index] != 0;
}

#line 31 "tests/10__calculator/test.code"
struct Token *pTokenizer__next_token(struct Tokenizer *self) {
#line 32 "tests/10__calculator/test.code"
    struct StringBuilder lexeme_builder = (struct StringBuilder){.data = (uint8_t *) malloc(4u), .data_size = 4, .length = 0};
#line 37 "tests/10__calculator/test.code"
    uint8_t c = self->data[self->index];
#line 38 "tests/10__calculator/test.code"
    if (c >= '0' && c <= '9') {
#line 39 "tests/10__calculator/test.code"
        return pTokenizer__scan_number_token(self, &lexeme_builder);
    }
#line 41 "tests/10__calculator/test.code"
    self->index = self->index + 1;
#line 42 "tests/10__calculator/test.code"
    return __make_Token_value((struct Token){.kind = c, .lexeme = pStringBuilder__build(pStringBuilder__write__1_char(&lexeme_builder, c)), .value = 0});
}

#line 49 "tests/10__calculator/test.code"
struct Token *pTokenizer__scan_number_token(struct Tokenizer *self, struct StringBuilder *lexeme_builder) {
#line 50 "tests/10__calculator/test.code"
    int32_t value = 0;
#line 51 "tests/10__calculator/test.code"
    for (;;) {
#line 52 "tests/10__calculator/test.code"
        uint8_t c = self->data[self->index];
#line 53 "tests/10__calculator/test.code"
        if (c < '0' || c > '9') {
#line 54 "tests/10__calculator/test.code"
            break;
        }
#line 56 "tests/10__calculator/test.code"
        pStringBuilder__write__1_char(lexeme_builder, c);
#line 57 "tests/10__calculator/test.code"
        value = value * 10 + (int32_t) (c - '0');
#line 58 "tests/10__calculator/test.code"
        self->index = self->index + 1;
    }
#line 60 "tests/10__calculator/test.code"
    return __make_Token_value((struct Token){.kind = 'n', .lexeme = pStringBuilder__build(lexeme_builder), .value = value});
}

#line 76 "tests/10__calculator/test.code"
struct Writer *pWriter__write__1_token(struct Writer *self, struct Token *token) {
#line 77 "tests/10__calculator/test.code"
    pWriter__write__1_char(self, token->kind);
#line 78 "tests/10__calculator/test.code"
    if (token->kind == 'n') {
#line 79 "tests/10__calculator/test.code"
        pWriter__write__1_signed(pWriter__write__1_char(pWriter__write__1_char(self, ':'), ' '), token->value);
    }
#line 81 "tests/10__calculator/test.code"
    return self;
}

#line 91 "tests/10__calculator/test.code"
struct StringBuilder *pStringBuilder__write__1_char(struct StringBuilder *self, uint8_t c) {
#line 92 "tests/10__calculator/test.code"
    if (self->length == self->data_size) {
#line 93 "tests/10__calculator/test.code"
        self->data_size = self->data_size + 8;
#line 94 "tests/10__calculator/test.code"
        self->data = (uint8_t *) realloc((void *) self->data, (uint64_t) self->data_size);
    }
#line 99 "tests/10__calculator/test.code"
    self->data[self->length] = c;
#line 100 "tests/10__calculator/test.code"
    self->length = self->length + 1;
#line 101 "tests/10__calculator/test.code"
    return self;
}

#line 104 "tests/10__calculator/test.code"
uint8_t *pStringBuilder__build(struct StringBuilder *self) {
#line 105 "tests/10__calculator/test.code"
    pStringBuilder__write__1_char(self, 0);
#line 106 "tests/10__calculator/test.code"
    return self->data;
}

#line 110 "tests/10__calculator/test.code"
void pStringBuilder__write_char(struct StringBuilder *self, uint8_t c) {
#line 111 "tests/10__calculator/test.code"
    pStringBuilder__write__1_char(self, c);
}

#line 120 "tests/10__calculator/test.code"
struct Writer *pWriter__write__1_char(struct Writer *self, uint8_t c) {
#line 121 "tests/10__calculator/test.code"
    self->write_char(self->self, c);
#line 122 "tests/10__calculator/test.code"
    return self;
}

#line 125 "tests/10__calculator/test.code"
struct Writer *pWriter__write__1_signed(struct Writer *self, int32_t value) {
#line 127 "tests/10__calculator/test.code"
    if (value < 0) {
#line 128 "tests/10__calculator/test.code"
        pWriter__write__1_char(self, '-');
#line 129 "tests/10__calculator/test.code"
        return pWriter__write__1_signed(self, -value);
    }
#line 131 "tests/10__calculator/test.code"
    if (value >= 10) {
#line 132 "tests/10__calculator/test.code"
        pWriter__write__1_signed(self, value / 10);
    }
#line 134 "tests/10__calculator/test.code"
    return pWriter__write__1_char(self, (uint8_t) (value % 10) + '0');
}

#line 137 "tests/10__calculator/test.code"
struct Writer *pWriter__end_line(struct Writer *self) {
#line 138 "tests/10__calculator/test.code"
    pWriter__write__1_char(self, '\n');
#line 139 "tests/10__calculator/test.code"
    return self;
}

#line 152 "tests/10__calculator/test.code"
void pFILE__write_char(FILE *self, uint8_t c) {
#line 153 "tests/10__calculator/test.code"
    fputc((int32_t) c, stdout);
}

