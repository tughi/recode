#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct Parser;

struct Tokenizer;

struct Token;

struct Number;

struct Span;

struct Plus;

struct Minus;

struct Multiply;

struct Divide;

struct Stop;

struct Error;

struct String;

struct Expression;

struct Addition;

struct Division;

struct Multiplication;

struct Subtraction;

struct Writer;

struct String_Builder;

typedef struct FILE FILE;

struct Span {
    int32_t start;
    int32_t end;
};

struct Number {
    struct Span span;
    int32_t value;
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

struct Tokenizer {
    uint8_t *data;
    int32_t index;
    struct Token current_token;
};

struct Parser {
    struct Tokenizer tokenizer;
};

struct Addition {
    struct Span span;
    struct Expression *left;
    struct Expression *right;
};

struct Division {
    struct Span span;
    struct Expression *left;
    struct Expression *right;
};

struct Multiplication {
    struct Span span;
    struct Expression *left;
    struct Expression *right;
};

struct Subtraction {
    struct Span span;
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

struct Plus *__make_Plus_value(struct Plus value);

struct Minus *__make_Minus_value(struct Minus value);

struct Multiply *__make_Multiply_value(struct Multiply value);

struct Divide *__make_Divide_value(struct Divide value);

struct Stop *__make_Stop_value(struct Stop value);

struct Error *__make_Error_value(struct Error value);

struct String *__make_String_value(struct String value);

struct Addition *__make_Addition_value(struct Addition value);

struct Division *__make_Division_value(struct Division value);

struct Multiplication *__make_Multiplication_value(struct Multiplication value);

struct Subtraction *__make_Subtraction_value(struct Subtraction value);

struct Writer *__make_Writer_value(struct Writer value);

struct String_Builder *__make_String_Builder_value(struct String_Builder value);

void main(int32_t argc, uint8_t **argv);

struct Span pExpression__span(struct Expression *self);

struct Token pTokenizer__peek_token(struct Tokenizer *self);

struct Token pTokenizer__next_token(struct Tokenizer *self);

struct Token pTokenizer__scan_token(struct Tokenizer *self);

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
    while (pTokenizer__peek_token(&tokenizer).variant != 6) {
#line 14 "tests/10__calculator/test.code"
        struct Token token = pTokenizer__next_token(&tokenizer);
#line 15 "tests/10__calculator/test.code"
        pWriter__end_line(pWriter__write__1_token(&stdout_writer, token));
    }
}

#line 127 "tests/10__calculator/test.code"
struct Span pExpression__span(struct Expression *self) {
#line 128 "tests/10__calculator/test.code"
    struct Expression expression = *self;
#line 129 "tests/10__calculator/test.code"
    while (false) {
    }
#line 130 "tests/10__calculator/test.code"
    if (expression.variant == 1) {
#line 131 "tests/10__calculator/test.code"
        return expression.variant_1.span;
    }
#line 133 "tests/10__calculator/test.code"
    else if (expression.variant == 2) {
#line 134 "tests/10__calculator/test.code"
        return expression.variant_2.span;
    }
#line 136 "tests/10__calculator/test.code"
    else if (expression.variant == 3) {
#line 137 "tests/10__calculator/test.code"
        return expression.variant_3.span;
    }
#line 139 "tests/10__calculator/test.code"
    else if (expression.variant == 4) {
#line 140 "tests/10__calculator/test.code"
        return expression.variant_4.span;
    }
#line 142 "tests/10__calculator/test.code"
    else if (expression.variant == 5) {
#line 143 "tests/10__calculator/test.code"
        return expression.variant_5.span;
    }
#line 145 "tests/10__calculator/test.code"
    else if (expression.variant == 0) {
#line 146 "tests/10__calculator/test.code"
        return (struct Span){.start = 0, .end = 0};
    }
}

#line 160 "tests/10__calculator/test.code"
struct Token pTokenizer__peek_token(struct Tokenizer *self) {
#line 161 "tests/10__calculator/test.code"
    if (self->current_token.variant == 0) {
#line 162 "tests/10__calculator/test.code"
        self->current_token = pTokenizer__scan_token(self);
    }
#line 164 "tests/10__calculator/test.code"
    return self->current_token;
}

#line 167 "tests/10__calculator/test.code"
struct Token pTokenizer__next_token(struct Tokenizer *self) {
#line 168 "tests/10__calculator/test.code"
    struct Token token = pTokenizer__peek_token(self);
#line 169 "tests/10__calculator/test.code"
    self->current_token = (struct Token){.variant = 0};
#line 170 "tests/10__calculator/test.code"
    return token;
}

#line 173 "tests/10__calculator/test.code"
struct Token pTokenizer__scan_token(struct Tokenizer *self) {
#line 174 "tests/10__calculator/test.code"
    while (self->data[self->index] == ' ') {
#line 175 "tests/10__calculator/test.code"
        self->index = self->index + 1;
    }
#line 177 "tests/10__calculator/test.code"
    uint8_t ch = self->data[self->index];
#line 178 "tests/10__calculator/test.code"
    if (ch == 0) {
#line 179 "tests/10__calculator/test.code"
        return (struct Token){.variant = 6, .variant_6 = (struct Stop){.span = (struct Span){.start = self->index, .end = self->index}}};
    }
#line 181 "tests/10__calculator/test.code"
    if (ch != ' ') {
#line 182 "tests/10__calculator/test.code"
        if (ch >= '0' && ch <= '9') {
#line 183 "tests/10__calculator/test.code"
            return pTokenizer__scan_number_token(self);
        }
#line 185 "tests/10__calculator/test.code"
        self->index = self->index + 1;
#line 186 "tests/10__calculator/test.code"
        if (ch == '+') {
#line 187 "tests/10__calculator/test.code"
            return (struct Token){.variant = 2, .variant_2 = (struct Plus){.span = (struct Span){.start = self->index - 1, .end = self->index}}};
        }
#line 189 "tests/10__calculator/test.code"
        if (ch == '-') {
#line 190 "tests/10__calculator/test.code"
            return (struct Token){.variant = 3, .variant_3 = (struct Minus){.span = (struct Span){.start = self->index - 1, .end = self->index}}};
        }
#line 192 "tests/10__calculator/test.code"
        if (ch == '*') {
#line 193 "tests/10__calculator/test.code"
            return (struct Token){.variant = 4, .variant_4 = (struct Multiply){.span = (struct Span){.start = self->index - 1, .end = self->index}}};
        }
#line 195 "tests/10__calculator/test.code"
        if (ch == '/') {
#line 196 "tests/10__calculator/test.code"
            return (struct Token){.variant = 5, .variant_5 = (struct Divide){.span = (struct Span){.start = self->index - 1, .end = self->index}}};
        }
#line 198 "tests/10__calculator/test.code"
        return (struct Token){.variant = 7, .variant_7 = (struct Error){.span = (struct Span){.start = self->index - 1, .end = self->index}, .message = (struct String){.data = "Unexpected character", .length = 20}}};
    }
}

#line 205 "tests/10__calculator/test.code"
struct Token pTokenizer__scan_number_token(struct Tokenizer *self) {
#line 206 "tests/10__calculator/test.code"
    int32_t start = self->index;
#line 207 "tests/10__calculator/test.code"
    int32_t value = 0;
#line 208 "tests/10__calculator/test.code"
    for (;;) {
#line 209 "tests/10__calculator/test.code"
        uint8_t c = self->data[self->index];
#line 210 "tests/10__calculator/test.code"
        if (c < '0' || c > '9') {
#line 211 "tests/10__calculator/test.code"
            break;
        }
#line 213 "tests/10__calculator/test.code"
        value = value * 10 + ((int32_t) (c - '0'));
#line 214 "tests/10__calculator/test.code"
        self->index = self->index + 1;
    }
#line 216 "tests/10__calculator/test.code"
    return (struct Token){.variant = 1, .variant_1 = (struct Number){.span = (struct Span){.start = start, .end = self->index}, .value = value}};
}

#line 270 "tests/10__calculator/test.code"
struct Writer *pWriter__write__1_token(struct Writer *self, struct Token token) {
#line 271 "tests/10__calculator/test.code"
    while (false) {
    }
#line 272 "tests/10__calculator/test.code"
    if (token.variant == 1) {
#line 273 "tests/10__calculator/test.code"
        return pWriter__write__1_signed(pWriter__write(self, (struct String){.data = "Number: ", .length = 8}), token.variant_1.value);
    }
#line 275 "tests/10__calculator/test.code"
    else if (token.variant == 2) {
#line 276 "tests/10__calculator/test.code"
        return pWriter__write(self, (struct String){.data = "Plus", .length = 4});
    }
#line 278 "tests/10__calculator/test.code"
    else if (token.variant == 3) {
#line 279 "tests/10__calculator/test.code"
        return pWriter__write(self, (struct String){.data = "Minus", .length = 5});
    }
#line 281 "tests/10__calculator/test.code"
    else if (token.variant == 4) {
#line 282 "tests/10__calculator/test.code"
        return pWriter__write(self, (struct String){.data = "Multiply", .length = 8});
    }
#line 284 "tests/10__calculator/test.code"
    else if (token.variant == 5) {
#line 285 "tests/10__calculator/test.code"
        return pWriter__write(self, (struct String){.data = "Divide", .length = 6});
    }
#line 287 "tests/10__calculator/test.code"
    else if (token.variant == 6) {
#line 288 "tests/10__calculator/test.code"
        return pWriter__write(self, (struct String){.data = "Stop", .length = 4});
    }
#line 290 "tests/10__calculator/test.code"
    else if (token.variant == 7) {
#line 291 "tests/10__calculator/test.code"
        return pWriter__write(pWriter__write(self, (struct String){.data = "Error: ", .length = 7}), token.variant_7.message);
    }
#line 293 "tests/10__calculator/test.code"
    else if (token.variant == 0) {
#line 294 "tests/10__calculator/test.code"
        return pWriter__write(self, (struct String){.data = "Nil!", .length = 4});
    }
#line 297 "tests/10__calculator/test.code"
    return self;
}

#line 307 "tests/10__calculator/test.code"
struct Writer *pWriter__write__1_char(struct Writer *self, uint8_t c) {
#line 308 "tests/10__calculator/test.code"
    self->write_char(self->self, c);
#line 309 "tests/10__calculator/test.code"
    return self;
}

#line 312 "tests/10__calculator/test.code"
struct Writer *pWriter__write__1_signed(struct Writer *self, int32_t value) {
#line 314 "tests/10__calculator/test.code"
    if (value < 0) {
#line 315 "tests/10__calculator/test.code"
        pWriter__write__1_char(self, '-');
#line 316 "tests/10__calculator/test.code"
        return pWriter__write__1_signed(self, -value);
    }
#line 318 "tests/10__calculator/test.code"
    if (value >= 10) {
#line 319 "tests/10__calculator/test.code"
        pWriter__write__1_signed(self, value / 10);
    }
#line 321 "tests/10__calculator/test.code"
    return pWriter__write__1_char(self, ((uint8_t) (value % 10)) + '0');
}

#line 324 "tests/10__calculator/test.code"
struct Writer *pWriter__end_line(struct Writer *self) {
#line 325 "tests/10__calculator/test.code"
    pWriter__write__1_char(self, '\n');
#line 326 "tests/10__calculator/test.code"
    return self;
}

#line 337 "tests/10__calculator/test.code"
struct String_Builder *pString_Builder__write__1_char(struct String_Builder *self, uint8_t c) {
#line 338 "tests/10__calculator/test.code"
    if (self->length == self->data_size) {
#line 339 "tests/10__calculator/test.code"
        self->data_size = self->data_size + 8;
#line 340 "tests/10__calculator/test.code"
        self->data = ((uint8_t *) realloc(((void *) self->data), ((uint64_t) self->data_size)));
    }
#line 345 "tests/10__calculator/test.code"
    self->data[self->length] = c;
#line 346 "tests/10__calculator/test.code"
    self->length = self->length + 1;
#line 347 "tests/10__calculator/test.code"
    return self;
}

#line 350 "tests/10__calculator/test.code"
struct String pString_Builder__build(struct String_Builder *self) {
#line 351 "tests/10__calculator/test.code"
    pString_Builder__write__1_char(self, 0);
#line 352 "tests/10__calculator/test.code"
    struct String string = (struct String){.data = self->data, .length = self->length - 1};
#line 356 "tests/10__calculator/test.code"
    return *((struct String *) (&string));
}

#line 359 "tests/10__calculator/test.code"
struct String_Builder make_string_builder() {
#line 360 "tests/10__calculator/test.code"
    return make_string_builder__0_initial_data_size(4);
}

#line 363 "tests/10__calculator/test.code"
struct String_Builder make_string_builder__0_initial_data_size(int32_t initial_data_size) {
#line 364 "tests/10__calculator/test.code"
    return (struct String_Builder){.data = ((uint8_t *) malloc(((uint64_t) initial_data_size))), .data_size = initial_data_size, .length = 0};
}

#line 371 "tests/10__calculator/test.code"
void pString_Builder__write_char(struct String_Builder *self, uint8_t c) {
#line 372 "tests/10__calculator/test.code"
    pString_Builder__write__1_char(self, c);
}

#line 382 "tests/10__calculator/test.code"
struct Writer *pWriter__write(struct Writer *self, struct String string) {
#line 383 "tests/10__calculator/test.code"
    struct String string_copy = string;
#line 384 "tests/10__calculator/test.code"
    uint8_t *string_data = ((struct String *) (&string_copy))->data;
#line 385 "tests/10__calculator/test.code"
    uintmax_t index = 0;
#line 386 "tests/10__calculator/test.code"
    while (index < string.length) {
#line 387 "tests/10__calculator/test.code"
        pWriter__write__1_char(self, string_data[index]);
#line 388 "tests/10__calculator/test.code"
        index = index + 1;
    }
#line 390 "tests/10__calculator/test.code"
    return self;
}

#line 403 "tests/10__calculator/test.code"
void pFILE__write_char(FILE *self, uint8_t c) {
#line 404 "tests/10__calculator/test.code"
    fputc(((int32_t) c), stdout);
}

