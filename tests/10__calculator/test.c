#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct Tokenizer;

struct String;

struct Span;

struct Token;

struct String_Builder;

struct Writer;

typedef struct FILE FILE;

struct Tokenizer {
    uint8_t *data;
    int32_t index;
};

struct String {
    uint8_t *data;
    int32_t length;
};

struct Span {
    struct String lexeme;
};

struct Token {
    uint8_t kind;
    struct Span span;
    int32_t value;
};

struct String_Builder {
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

struct String *__make_String_value(struct String value);

struct Span *__make_Span_value(struct Span value);

struct Token *__make_Token_value(struct Token value);

struct String_Builder *__make_String_Builder_value(struct String_Builder value);

struct Writer *__make_Writer_value(struct Writer value);

void main(int32_t argc, uint8_t **argv);

bool pTokenizer__has_next_token(struct Tokenizer *self);

struct Token *pTokenizer__next_token(struct Tokenizer *self);

struct Token *pTokenizer__scan_number_token(struct Tokenizer *self, struct String_Builder *lexeme_builder);

struct Writer *pWriter__write__1_string(struct Writer *self, struct String string);

struct Writer *pWriter__write__1_token(struct Writer *self, struct Token *token);

struct String_Builder *pString_Builder__write__1_char(struct String_Builder *self, uint8_t c);

struct String pString_Builder__build(struct String_Builder *self);

struct String_Builder make_string_builder();

struct String_Builder make_string_builder__0_initial_data_size(int32_t initial_data_size);

void pString_Builder__write_char(struct String_Builder *self, uint8_t c);

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

struct String *__make_String_value(struct String value) {
    struct String *result = (struct String *)malloc(sizeof(struct String));
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

struct String_Builder *__make_String_Builder_value(struct String_Builder value) {
    struct String_Builder *result = (struct String_Builder *)malloc(sizeof(struct String_Builder));
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
    struct Writer stdout_writer = (struct Writer){.self = stdout, .write_char = ((void (*)(void *self, uint8_t c)) pFILE__write_char)};
#line 13 "tests/10__calculator/test.code"
    pWriter__end_line(pWriter__write__1_string(&stdout_writer, (struct String){.data = "Tokens:", .length = 7}));
#line 15 "tests/10__calculator/test.code"
    while (pTokenizer__has_next_token(&tokenizer)) {
#line 16 "tests/10__calculator/test.code"
        struct Token *token = pTokenizer__next_token(&tokenizer);
#line 17 "tests/10__calculator/test.code"
        if (token->kind == 0) {
#line 18 "tests/10__calculator/test.code"
            break;
        }
#line 20 "tests/10__calculator/test.code"
        pWriter__end_line(pWriter__write__1_token(&stdout_writer, token));
    }
}

#line 31 "tests/10__calculator/test.code"
bool pTokenizer__has_next_token(struct Tokenizer *self) {
#line 32 "tests/10__calculator/test.code"
    return self->data[self->index] != 0;
}

#line 35 "tests/10__calculator/test.code"
struct Token *pTokenizer__next_token(struct Tokenizer *self) {
#line 36 "tests/10__calculator/test.code"
    struct String_Builder lexeme_builder = make_string_builder();
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
    return __make_Token_value((struct Token){.kind = c, .span = (struct Span){.lexeme = pString_Builder__build(pString_Builder__write__1_char(&lexeme_builder, c))}, .value = 0});
}

#line 51 "tests/10__calculator/test.code"
struct Token *pTokenizer__scan_number_token(struct Tokenizer *self, struct String_Builder *lexeme_builder) {
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
        pString_Builder__write__1_char(lexeme_builder, c);
#line 59 "tests/10__calculator/test.code"
        value = value * 10 + ((int32_t) (c - '0'));
#line 60 "tests/10__calculator/test.code"
        self->index = self->index + 1;
    }
#line 62 "tests/10__calculator/test.code"
    return __make_Token_value((struct Token){.kind = 'n', .span = (struct Span){.lexeme = pString_Builder__build(lexeme_builder)}, .value = value});
}

#line 78 "tests/10__calculator/test.code"
struct Writer *pWriter__write__1_string(struct Writer *self, struct String string) {
#line 79 "tests/10__calculator/test.code"
    struct String string_copy = string;
#line 80 "tests/10__calculator/test.code"
    uint8_t *string_data = ((struct String *) (&string_copy))->data;
#line 81 "tests/10__calculator/test.code"
    uintmax_t index = 0;
#line 82 "tests/10__calculator/test.code"
    while (index < string.length) {
#line 83 "tests/10__calculator/test.code"
        pWriter__write__1_char(self, string_data[index]);
#line 84 "tests/10__calculator/test.code"
        index = index + 1;
    }
#line 86 "tests/10__calculator/test.code"
    return self;
}

#line 101 "tests/10__calculator/test.code"
struct Writer *pWriter__write__1_token(struct Writer *self, struct Token *token) {
#line 102 "tests/10__calculator/test.code"
    pWriter__write__1_char(self, token->kind);
#line 103 "tests/10__calculator/test.code"
    if (token->kind == 'n') {
#line 104 "tests/10__calculator/test.code"
        pWriter__write__1_signed(pWriter__write__1_char(pWriter__write__1_char(self, ':'), ' '), token->value);
    }
#line 106 "tests/10__calculator/test.code"
    return self;
}

#line 117 "tests/10__calculator/test.code"
struct String_Builder *pString_Builder__write__1_char(struct String_Builder *self, uint8_t c) {
#line 118 "tests/10__calculator/test.code"
    if (self->length == self->data_size) {
#line 119 "tests/10__calculator/test.code"
        self->data_size = self->data_size + 8;
#line 120 "tests/10__calculator/test.code"
        self->data = ((uint8_t *) realloc(((void *) self->data), ((uint64_t) self->data_size)));
    }
#line 125 "tests/10__calculator/test.code"
    self->data[self->length] = c;
#line 126 "tests/10__calculator/test.code"
    self->length = self->length + 1;
#line 127 "tests/10__calculator/test.code"
    return self;
}

#line 130 "tests/10__calculator/test.code"
struct String pString_Builder__build(struct String_Builder *self) {
#line 131 "tests/10__calculator/test.code"
    pString_Builder__write__1_char(self, 0);
#line 132 "tests/10__calculator/test.code"
    struct String string = (struct String){.data = self->data, .length = self->length};
#line 136 "tests/10__calculator/test.code"
    return *((struct String *) (&string));
}

#line 139 "tests/10__calculator/test.code"
struct String_Builder make_string_builder() {
#line 140 "tests/10__calculator/test.code"
    return make_string_builder__0_initial_data_size(4);
}

#line 143 "tests/10__calculator/test.code"
struct String_Builder make_string_builder__0_initial_data_size(int32_t initial_data_size) {
#line 144 "tests/10__calculator/test.code"
    return (struct String_Builder){.data = ((uint8_t *) malloc(((uint64_t) initial_data_size))), .data_size = initial_data_size, .length = 0};
}

#line 151 "tests/10__calculator/test.code"
void pString_Builder__write_char(struct String_Builder *self, uint8_t c) {
#line 152 "tests/10__calculator/test.code"
    pString_Builder__write__1_char(self, c);
}

#line 161 "tests/10__calculator/test.code"
struct Writer *pWriter__write__1_char(struct Writer *self, uint8_t c) {
#line 162 "tests/10__calculator/test.code"
    self->write_char(self->self, c);
#line 163 "tests/10__calculator/test.code"
    return self;
}

#line 166 "tests/10__calculator/test.code"
struct Writer *pWriter__write__1_signed(struct Writer *self, int32_t value) {
#line 168 "tests/10__calculator/test.code"
    if (value < 0) {
#line 169 "tests/10__calculator/test.code"
        pWriter__write__1_char(self, '-');
#line 170 "tests/10__calculator/test.code"
        return pWriter__write__1_signed(self, -value);
    }
#line 172 "tests/10__calculator/test.code"
    if (value >= 10) {
#line 173 "tests/10__calculator/test.code"
        pWriter__write__1_signed(self, value / 10);
    }
#line 175 "tests/10__calculator/test.code"
    return pWriter__write__1_char(self, ((uint8_t) (value % 10)) + '0');
}

#line 178 "tests/10__calculator/test.code"
struct Writer *pWriter__end_line(struct Writer *self) {
#line 179 "tests/10__calculator/test.code"
    pWriter__write__1_char(self, '\n');
#line 180 "tests/10__calculator/test.code"
    return self;
}

#line 193 "tests/10__calculator/test.code"
void pFILE__write_char(FILE *self, uint8_t c) {
#line 194 "tests/10__calculator/test.code"
    fputc(((int32_t) c), stdout);
}

