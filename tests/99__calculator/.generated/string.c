#include "test.h"
#include "calculator__expression.h"
#include "calculator__source.h"
#include "libc.h"
#include "io.h"
#include "calculator__parser.h"
#include "calculator__tokenizer.h"
#include "os.h"
#include "string.h"

void *malloc(uintmax_t size);

#line 9 "tests/99__calculator/string/builder.code"
struct string_Builder *pstring_Builder__write(struct string_Builder *self, uint8_t c) {
#line 10 "tests/99__calculator/string/builder.code"
    if (self->length == self->data_size) {
#line 11 "tests/99__calculator/string/builder.code"
        self->data_size = self->data_size + 8u;
#line 12 "tests/99__calculator/string/builder.code"
        self->data = ((uint8_t *) realloc(((void *) self->data), self->data_size));
#line 16 "tests/99__calculator/string/builder.code"
    }
#line 17 "tests/99__calculator/string/builder.code"
    self->data[self->length] = c;
#line 18 "tests/99__calculator/string/builder.code"
    self->length = self->length + 1u;
#line 19 "tests/99__calculator/string/builder.code"
    {
#line 19 "tests/99__calculator/string/builder.code"
        struct string_Builder *__001__ = self;
#line 19 "tests/99__calculator/string/builder.code"
        return __001__;
#line 19 "tests/99__calculator/string/builder.code"
    }
#line 20 "tests/99__calculator/string/builder.code"
}

#line 22 "tests/99__calculator/string/builder.code"
struct String pstring_Builder__build(struct string_Builder *self) {
#line 23 "tests/99__calculator/string/builder.code"
    pstring_Builder__write(self, 0);
#line 24 "tests/99__calculator/string/builder.code"
    struct String string = (struct String){.data = self->data, .length = self->length - 1u};
#line 28 "tests/99__calculator/string/builder.code"
    {
#line 28 "tests/99__calculator/string/builder.code"
        struct String __001__ = *((struct String *) (&string));
#line 28 "tests/99__calculator/string/builder.code"
        return __001__;
#line 28 "tests/99__calculator/string/builder.code"
    }
#line 29 "tests/99__calculator/string/builder.code"
}

#line 31 "tests/99__calculator/string/builder.code"
struct string_Builder string__make_string_builder() {
#line 32 "tests/99__calculator/string/builder.code"
    {
#line 32 "tests/99__calculator/string/builder.code"
        struct string_Builder __001__ = string__make_string_builder_with_data_size(4u);
#line 32 "tests/99__calculator/string/builder.code"
        return __001__;
#line 32 "tests/99__calculator/string/builder.code"
    }
#line 33 "tests/99__calculator/string/builder.code"
}

#line 35 "tests/99__calculator/string/builder.code"
struct string_Builder string__make_string_builder_with_data_size(uintmax_t data_size) {
#line 36 "tests/99__calculator/string/builder.code"
    {
#line 36 "tests/99__calculator/string/builder.code"
        struct string_Builder __001__ = (struct string_Builder){.data = ((uint8_t *) malloc(data_size)), .data_size = data_size, .length = 0u};
#line 36 "tests/99__calculator/string/builder.code"
        return __001__;
#line 40 "tests/99__calculator/string/builder.code"
    }
#line 41 "tests/99__calculator/string/builder.code"
}

#line 43 "tests/99__calculator/string/builder.code"
void pstring_Builder__write_char(struct string_Builder *self, uint8_t c) {
#line 44 "tests/99__calculator/string/builder.code"
    pstring_Builder__write(self, c);
#line 45 "tests/99__calculator/string/builder.code"
}

