#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct Tokenizer;

struct Span;

struct Token;

struct StringBuilder;

struct Writer;

typedef struct FILE FILE;

struct Tokenizer {
    uint8_t *data;
    int32_t index;
};

struct Span {
    uint8_t *lexeme;
};

struct Token {
    uint8_t kind;
    struct Span span;
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

struct Span *__make_Span_value(struct Span value);

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

struct Span *__make_Span_value(struct Span value) {
    struct Span *result = (struct Span *)malloc(sizeof(struct Span));
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
    return __make_Token_value((struct Token){.kind = c, .span = (struct Span){.lexeme = pStringBuilder__build(pStringBuilder__write__1_char(&lexeme_builder, c))}, .value = 0});
}

#line 51 "tests/10__calculator/test.code"
struct Token *pTokenizer__scan_number_token(struct Tokenizer *self, struct StringBuilder *lexeme_builder) {
#line 52 "tests/10__calculator/test.code"
    int32_t value = 0;
#line 53 "tests/10__calculator/test.code"
    for (;;) {
#line 54 "tests/10__calculator/test.code"
        uint8_t c = self->data[self->index];
#line 55 "tests/10__calculator/test.code"
        if (c < '0' || c > '9') {
#line 56 "tests/10__calculator/test.code"
            break;
        }
#line 58 "tests/10__calculator/test.code"
        pStringBuilder__write__1_char(lexeme_builder, c);
#line 59 "tests/10__calculator/test.code"
        value = value * 10 + (int32_t) (c - '0');
#line 60 "tests/10__calculator/test.code"
        self->index = self->index + 1;
    }
#line 62 "tests/10__calculator/test.code"
    return __make_Token_value((struct Token){.kind = 'n', .span = (struct Span){.lexeme = pStringBuilder__build(lexeme_builder)}, .value = value});
}

#line 84 "tests/10__calculator/test.code"
struct Writer *pWriter__write__1_token(struct Writer *self, struct Token *token) {
#line 85 "tests/10__calculator/test.code"
    pWriter__write__1_char(self, token->kind);
#line 86 "tests/10__calculator/test.code"
    if (token->kind == 'n') {
#line 87 "tests/10__calculator/test.code"
        pWriter__write__1_signed(pWriter__write__1_char(pWriter__write__1_char(self, ':'), ' '), token->value);
    }
#line 89 "tests/10__calculator/test.code"
    return self;
}

#line 99 "tests/10__calculator/test.code"
struct StringBuilder *pStringBuilder__write__1_char(struct StringBuilder *self, uint8_t c) {
#line 100 "tests/10__calculator/test.code"
    if (self->length == self->data_size) {
#line 101 "tests/10__calculator/test.code"
        self->data_size = self->data_size + 8;
#line 102 "tests/10__calculator/test.code"
        self->data = (uint8_t *) realloc((void *) self->data, (uint64_t) self->data_size);
    }
#line 107 "tests/10__calculator/test.code"
    self->data[self->length] = c;
#line 108 "tests/10__calculator/test.code"
    self->length = self->length + 1;
#line 109 "tests/10__calculator/test.code"
    return self;
}

#line 112 "tests/10__calculator/test.code"
uint8_t *pStringBuilder__build(struct StringBuilder *self) {
#line 113 "tests/10__calculator/test.code"
    pStringBuilder__write__1_char(self, 0);
#line 114 "tests/10__calculator/test.code"
    return self->data;
}

#line 118 "tests/10__calculator/test.code"
void pStringBuilder__write_char(struct StringBuilder *self, uint8_t c) {
#line 119 "tests/10__calculator/test.code"
    pStringBuilder__write__1_char(self, c);
}

#line 128 "tests/10__calculator/test.code"
struct Writer *pWriter__write__1_char(struct Writer *self, uint8_t c) {
#line 129 "tests/10__calculator/test.code"
    self->write_char(self->self, c);
#line 130 "tests/10__calculator/test.code"
    return self;
}

#line 133 "tests/10__calculator/test.code"
struct Writer *pWriter__write__1_signed(struct Writer *self, int32_t value) {
#line 135 "tests/10__calculator/test.code"
    if (value < 0) {
#line 136 "tests/10__calculator/test.code"
        pWriter__write__1_char(self, '-');
#line 137 "tests/10__calculator/test.code"
        return pWriter__write__1_signed(self, -value);
    }
#line 139 "tests/10__calculator/test.code"
    if (value >= 10) {
#line 140 "tests/10__calculator/test.code"
        pWriter__write__1_signed(self, value / 10);
    }
#line 142 "tests/10__calculator/test.code"
    return pWriter__write__1_char(self, (uint8_t) (value % 10) + '0');
}

#line 145 "tests/10__calculator/test.code"
struct Writer *pWriter__end_line(struct Writer *self) {
#line 146 "tests/10__calculator/test.code"
    pWriter__write__1_char(self, '\n');
#line 147 "tests/10__calculator/test.code"
    return self;
}

#line 160 "tests/10__calculator/test.code"
void pFILE__write_char(FILE *self, uint8_t c) {
#line 161 "tests/10__calculator/test.code"
    fputc((int32_t) c, stdout);
}

