#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct Parser;

struct Tokenizer;

struct Expression;

struct Number;

struct Span;

struct Addition;

struct Division;

struct Multiplication;

struct Subtraction;

struct Plus;

struct Minus;

struct Multiply;

struct Divide;

struct Stop;

struct Error;

struct String;

struct Token;

struct Writer;

struct String_Builder;

typedef struct FILE FILE;

struct Tokenizer {
    uint8_t *data;
    int32_t index;
};

struct Parser {
    struct Tokenizer tokenizer;
};

struct Span {
    int32_t start;
    int32_t end;
};

struct Number {
    struct Span span;
    int32_t value;
};

struct Addition {
    struct Expression *left;
    struct Expression *right;
};

struct Division {
    struct Expression *left;
    struct Expression *right;
};

struct Multiplication {
    struct Expression *left;
    struct Expression *right;
};

struct Subtraction {
    struct Expression *left;
    struct Expression *right;
};

struct Expression {
    int32_t variant;
    union {
        struct Number variant_1;
        struct Addition variant_2;
        struct Division variant_3;
        struct Multiplication variant_4;
        struct Subtraction variant_5;
    };
};

struct Plus {
    struct Span span;
};

struct Minus {
    struct Span span;
};

struct Multiply {
    struct Span span;
};

struct Divide {
    struct Span span;
};

struct Stop {
    struct Span span;
};

struct String {
    uint8_t *data;
    int32_t length;
};

struct Error {
    struct Span span;
    struct String message;
};

struct Token {
    int32_t variant;
    union {
        struct Number variant_1;
        struct Plus variant_2;
        struct Minus variant_3;
        struct Multiply variant_4;
        struct Divide variant_5;
        struct Stop variant_6;
        struct Error variant_7;
    };
};

struct Writer {
    void *self;
    void (*write_char)(void *self, uint8_t c);
};

struct String_Builder {
    uint8_t *data;
    int32_t data_size;
    int32_t length;
};

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;
struct Parser *__make_Parser_value(struct Parser value);

struct Tokenizer *__make_Tokenizer_value(struct Tokenizer value);

struct Number *__make_Number_value(struct Number value);

struct Span *__make_Span_value(struct Span value);

struct Addition *__make_Addition_value(struct Addition value);

struct Division *__make_Division_value(struct Division value);

struct Multiplication *__make_Multiplication_value(struct Multiplication value);

struct Subtraction *__make_Subtraction_value(struct Subtraction value);

struct Plus *__make_Plus_value(struct Plus value);

struct Minus *__make_Minus_value(struct Minus value);

struct Multiply *__make_Multiply_value(struct Multiply value);

struct Divide *__make_Divide_value(struct Divide value);

struct Stop *__make_Stop_value(struct Stop value);

struct Error *__make_Error_value(struct Error value);

struct String *__make_String_value(struct String value);

struct Writer *__make_Writer_value(struct Writer value);

struct String_Builder *__make_String_Builder_value(struct String_Builder value);

void main(int32_t argc, uint8_t **argv);

struct Expression *pParser__parse_expression(struct Parser *self);

struct Expression *pParser__parse_additive_expression(struct Parser *self);

struct Expression *pParser__parse_multiplicative_expression(struct Parser *self);

bool pTokenizer__has_next_token(struct Tokenizer *self);

struct Token pTokenizer__next_token(struct Tokenizer *self);

struct Token pTokenizer__scan_number_token(struct Tokenizer *self);

struct Writer *pWriter__write__1_token(struct Writer *self, struct Token token);

struct Writer *pWriter__write__1_char(struct Writer *self, uint8_t c);

struct Writer *pWriter__write__1_signed(struct Writer *self, int32_t value);

struct Writer *pWriter__end_line(struct Writer *self);

struct String_Builder *pString_Builder__write__1_char(struct String_Builder *self, uint8_t c);

struct String pString_Builder__build(struct String_Builder *self);

struct String_Builder make_string_builder();

struct String_Builder make_string_builder__0_initial_data_size(int32_t initial_data_size);

void pString_Builder__write_char(struct String_Builder *self, uint8_t c);

struct Writer *pWriter__write(struct Writer *self, struct String string);

int32_t fputc(int32_t c, FILE *file);

void pFILE__write_char(FILE *self, uint8_t c);

void *malloc(uint64_t size);

void *realloc(void *block, uint64_t size);

void exit(int32_t code);

struct Parser *__make_Parser_value(struct Parser value) {
    struct Parser *result = (struct Parser *)malloc(sizeof(struct Parser));
    *result = value;
    return result;
}

struct Tokenizer *__make_Tokenizer_value(struct Tokenizer value) {
    struct Tokenizer *result = (struct Tokenizer *)malloc(sizeof(struct Tokenizer));
    *result = value;
    return result;
}

struct Number *__make_Number_value(struct Number value) {
    struct Number *result = (struct Number *)malloc(sizeof(struct Number));
    *result = value;
    return result;
}

struct Span *__make_Span_value(struct Span value) {
    struct Span *result = (struct Span *)malloc(sizeof(struct Span));
    *result = value;
    return result;
}

struct Addition *__make_Addition_value(struct Addition value) {
    struct Addition *result = (struct Addition *)malloc(sizeof(struct Addition));
    *result = value;
    return result;
}

struct Division *__make_Division_value(struct Division value) {
    struct Division *result = (struct Division *)malloc(sizeof(struct Division));
    *result = value;
    return result;
}

struct Multiplication *__make_Multiplication_value(struct Multiplication value) {
    struct Multiplication *result = (struct Multiplication *)malloc(sizeof(struct Multiplication));
    *result = value;
    return result;
}

struct Subtraction *__make_Subtraction_value(struct Subtraction value) {
    struct Subtraction *result = (struct Subtraction *)malloc(sizeof(struct Subtraction));
    *result = value;
    return result;
}

struct Plus *__make_Plus_value(struct Plus value) {
    struct Plus *result = (struct Plus *)malloc(sizeof(struct Plus));
    *result = value;
    return result;
}

struct Minus *__make_Minus_value(struct Minus value) {
    struct Minus *result = (struct Minus *)malloc(sizeof(struct Minus));
    *result = value;
    return result;
}

struct Multiply *__make_Multiply_value(struct Multiply value) {
    struct Multiply *result = (struct Multiply *)malloc(sizeof(struct Multiply));
    *result = value;
    return result;
}

struct Divide *__make_Divide_value(struct Divide value) {
    struct Divide *result = (struct Divide *)malloc(sizeof(struct Divide));
    *result = value;
    return result;
}

struct Stop *__make_Stop_value(struct Stop value) {
    struct Stop *result = (struct Stop *)malloc(sizeof(struct Stop));
    *result = value;
    return result;
}

struct Error *__make_Error_value(struct Error value) {
    struct Error *result = (struct Error *)malloc(sizeof(struct Error));
    *result = value;
    return result;
}

struct String *__make_String_value(struct String value) {
    struct String *result = (struct String *)malloc(sizeof(struct String));
    *result = value;
    return result;
}

struct Writer *__make_Writer_value(struct Writer value) {
    struct Writer *result = (struct Writer *)malloc(sizeof(struct Writer));
    *result = value;
    return result;
}

struct String_Builder *__make_String_Builder_value(struct String_Builder value) {
    struct String_Builder *result = (struct String_Builder *)malloc(sizeof(struct String_Builder));
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
    while (pTokenizer__has_next_token(&tokenizer)) {
#line 14 "tests/10__calculator/test.code"
        struct Token token = pTokenizer__next_token(&tokenizer);
#line 15 "tests/10__calculator/test.code"
        pWriter__end_line(pWriter__write__1_token(&stdout_writer, token));
    }
#line 18 "tests/10__calculator/test.code"
    struct Token stop_token = pTokenizer__next_token(&tokenizer);
#line 19 "tests/10__calculator/test.code"
    if (stop_token.variant == 6) {
#line 20 "tests/10__calculator/test.code"
        exit(0);
    }
#line 23 "tests/10__calculator/test.code"
    exit(2);
}

#line 32 "tests/10__calculator/test.code"
struct Expression *pParser__parse_expression(struct Parser *self) {
#line 33 "tests/10__calculator/test.code"
    return pParser__parse_additive_expression(self);
}

#line 36 "tests/10__calculator/test.code"
struct Expression *pParser__parse_additive_expression(struct Parser *self) {
#line 37 "tests/10__calculator/test.code"
    struct Expression *expression = pParser__parse_multiplicative_expression(self);
}

#line 62 "tests/10__calculator/test.code"
struct Expression *pParser__parse_multiplicative_expression(struct Parser *self) {
}

#line 103 "tests/10__calculator/test.code"
bool pTokenizer__has_next_token(struct Tokenizer *self) {
#line 104 "tests/10__calculator/test.code"
    return self->data[self->index] != 0;
}

#line 107 "tests/10__calculator/test.code"
struct Token pTokenizer__next_token(struct Tokenizer *self) {
#line 108 "tests/10__calculator/test.code"
    while (self->data[self->index] == ' ') {
#line 109 "tests/10__calculator/test.code"
        self->index = self->index + 1;
    }
#line 111 "tests/10__calculator/test.code"
    uint8_t ch = self->data[self->index];
#line 112 "tests/10__calculator/test.code"
    if (ch == 0) {
#line 113 "tests/10__calculator/test.code"
        return (struct Token){.variant = 6, .variant_6 = (struct Stop){.span = (struct Span){.start = self->index, .end = self->index}}};
    }
#line 115 "tests/10__calculator/test.code"
    if (ch != ' ') {
#line 116 "tests/10__calculator/test.code"
        if (ch >= '0' && ch <= '9') {
#line 117 "tests/10__calculator/test.code"
            return pTokenizer__scan_number_token(self);
        }
#line 119 "tests/10__calculator/test.code"
        self->index = self->index + 1;
#line 120 "tests/10__calculator/test.code"
        if (ch == '+') {
#line 121 "tests/10__calculator/test.code"
            return (struct Token){.variant = 2, .variant_2 = (struct Plus){.span = (struct Span){.start = self->index - 1, .end = self->index}}};
        }
#line 123 "tests/10__calculator/test.code"
        if (ch == '-') {
#line 124 "tests/10__calculator/test.code"
            return (struct Token){.variant = 3, .variant_3 = (struct Minus){.span = (struct Span){.start = self->index - 1, .end = self->index}}};
        }
#line 126 "tests/10__calculator/test.code"
        if (ch == '*') {
#line 127 "tests/10__calculator/test.code"
            return (struct Token){.variant = 4, .variant_4 = (struct Multiply){.span = (struct Span){.start = self->index - 1, .end = self->index}}};
        }
#line 129 "tests/10__calculator/test.code"
        if (ch == '/') {
#line 130 "tests/10__calculator/test.code"
            return (struct Token){.variant = 5, .variant_5 = (struct Divide){.span = (struct Span){.start = self->index - 1, .end = self->index}}};
        }
#line 132 "tests/10__calculator/test.code"
        return (struct Token){.variant = 7, .variant_7 = (struct Error){.span = (struct Span){.start = self->index - 1, .end = self->index}, .message = (struct String){.data = "Unexpected character", .length = 20}}};
    }
}

#line 139 "tests/10__calculator/test.code"
struct Token pTokenizer__scan_number_token(struct Tokenizer *self) {
#line 140 "tests/10__calculator/test.code"
    int32_t start = self->index;
#line 141 "tests/10__calculator/test.code"
    int32_t value = 0;
#line 142 "tests/10__calculator/test.code"
    for (;;) {
#line 143 "tests/10__calculator/test.code"
        uint8_t c = self->data[self->index];
#line 144 "tests/10__calculator/test.code"
        if (c < '0' || c > '9') {
#line 145 "tests/10__calculator/test.code"
            break;
        }
#line 147 "tests/10__calculator/test.code"
        value = value * 10 + ((int32_t) (c - '0'));
#line 148 "tests/10__calculator/test.code"
        self->index = self->index + 1;
    }
#line 150 "tests/10__calculator/test.code"
    return (struct Token){.variant = 1, .variant_1 = (struct Number){.span = (struct Span){.start = start, .end = self->index}, .value = value}};
}

#line 204 "tests/10__calculator/test.code"
struct Writer *pWriter__write__1_token(struct Writer *self, struct Token token) {
#line 205 "tests/10__calculator/test.code"
    while (false) {
    }
#line 206 "tests/10__calculator/test.code"
    if (token.variant == 1) {
#line 207 "tests/10__calculator/test.code"
        return pWriter__write__1_signed(pWriter__write(self, (struct String){.data = "Number: ", .length = 8}), token.variant_1.value);
    }
#line 209 "tests/10__calculator/test.code"
    else if (token.variant == 2) {
#line 210 "tests/10__calculator/test.code"
        return pWriter__write(self, (struct String){.data = "Plus", .length = 4});
    }
#line 212 "tests/10__calculator/test.code"
    else if (token.variant == 3) {
#line 213 "tests/10__calculator/test.code"
        return pWriter__write(self, (struct String){.data = "Minus", .length = 5});
    }
#line 215 "tests/10__calculator/test.code"
    else if (token.variant == 4) {
#line 216 "tests/10__calculator/test.code"
        return pWriter__write(self, (struct String){.data = "Multiply", .length = 8});
    }
#line 218 "tests/10__calculator/test.code"
    else if (token.variant == 5) {
#line 219 "tests/10__calculator/test.code"
        return pWriter__write(self, (struct String){.data = "Divide", .length = 6});
    }
#line 221 "tests/10__calculator/test.code"
    else if (token.variant == 6) {
#line 222 "tests/10__calculator/test.code"
        return pWriter__write(self, (struct String){.data = "Stop", .length = 4});
    }
#line 224 "tests/10__calculator/test.code"
    else if (token.variant == 7) {
#line 225 "tests/10__calculator/test.code"
        return pWriter__write(pWriter__write(self, (struct String){.data = "Error: ", .length = 7}), token.variant_7.message);
    }
#line 228 "tests/10__calculator/test.code"
    return self;
}

#line 238 "tests/10__calculator/test.code"
struct Writer *pWriter__write__1_char(struct Writer *self, uint8_t c) {
#line 239 "tests/10__calculator/test.code"
    self->write_char(self->self, c);
#line 240 "tests/10__calculator/test.code"
    return self;
}

#line 243 "tests/10__calculator/test.code"
struct Writer *pWriter__write__1_signed(struct Writer *self, int32_t value) {
#line 245 "tests/10__calculator/test.code"
    if (value < 0) {
#line 246 "tests/10__calculator/test.code"
        pWriter__write__1_char(self, '-');
#line 247 "tests/10__calculator/test.code"
        return pWriter__write__1_signed(self, -value);
    }
#line 249 "tests/10__calculator/test.code"
    if (value >= 10) {
#line 250 "tests/10__calculator/test.code"
        pWriter__write__1_signed(self, value / 10);
    }
#line 252 "tests/10__calculator/test.code"
    return pWriter__write__1_char(self, ((uint8_t) (value % 10)) + '0');
}

#line 255 "tests/10__calculator/test.code"
struct Writer *pWriter__end_line(struct Writer *self) {
#line 256 "tests/10__calculator/test.code"
    pWriter__write__1_char(self, '\n');
#line 257 "tests/10__calculator/test.code"
    return self;
}

#line 268 "tests/10__calculator/test.code"
struct String_Builder *pString_Builder__write__1_char(struct String_Builder *self, uint8_t c) {
#line 269 "tests/10__calculator/test.code"
    if (self->length == self->data_size) {
#line 270 "tests/10__calculator/test.code"
        self->data_size = self->data_size + 8;
#line 271 "tests/10__calculator/test.code"
        self->data = ((uint8_t *) realloc(((void *) self->data), ((uint64_t) self->data_size)));
    }
#line 276 "tests/10__calculator/test.code"
    self->data[self->length] = c;
#line 277 "tests/10__calculator/test.code"
    self->length = self->length + 1;
#line 278 "tests/10__calculator/test.code"
    return self;
}

#line 281 "tests/10__calculator/test.code"
struct String pString_Builder__build(struct String_Builder *self) {
#line 282 "tests/10__calculator/test.code"
    pString_Builder__write__1_char(self, 0);
#line 283 "tests/10__calculator/test.code"
    struct String string = (struct String){.data = self->data, .length = self->length - 1};
#line 287 "tests/10__calculator/test.code"
    return *((struct String *) (&string));
}

#line 290 "tests/10__calculator/test.code"
struct String_Builder make_string_builder() {
#line 291 "tests/10__calculator/test.code"
    return make_string_builder__0_initial_data_size(4);
}

#line 294 "tests/10__calculator/test.code"
struct String_Builder make_string_builder__0_initial_data_size(int32_t initial_data_size) {
#line 295 "tests/10__calculator/test.code"
    return (struct String_Builder){.data = ((uint8_t *) malloc(((uint64_t) initial_data_size))), .data_size = initial_data_size, .length = 0};
}

#line 302 "tests/10__calculator/test.code"
void pString_Builder__write_char(struct String_Builder *self, uint8_t c) {
#line 303 "tests/10__calculator/test.code"
    pString_Builder__write__1_char(self, c);
}

#line 313 "tests/10__calculator/test.code"
struct Writer *pWriter__write(struct Writer *self, struct String string) {
#line 314 "tests/10__calculator/test.code"
    struct String string_copy = string;
#line 315 "tests/10__calculator/test.code"
    uint8_t *string_data = ((struct String *) (&string_copy))->data;
#line 316 "tests/10__calculator/test.code"
    uintmax_t index = 0;
#line 317 "tests/10__calculator/test.code"
    while (index < string.length) {
#line 318 "tests/10__calculator/test.code"
        pWriter__write__1_char(self, string_data[index]);
#line 319 "tests/10__calculator/test.code"
        index = index + 1;
    }
#line 321 "tests/10__calculator/test.code"
    return self;
}

#line 334 "tests/10__calculator/test.code"
void pFILE__write_char(FILE *self, uint8_t c) {
#line 335 "tests/10__calculator/test.code"
    fputc(((int32_t) c), stdout);
}

