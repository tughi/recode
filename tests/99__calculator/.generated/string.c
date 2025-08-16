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

#line 9 "tests/99__calculator/string.code"
struct string_Builder *pstring_Builder__write(struct string_Builder *self, uint8_t c) {
#line 10 "tests/99__calculator/string.code"
    if (self->length == self->data_size) {
#line 11 "tests/99__calculator/string.code"
        self->data_size = self->data_size + 8u;
#line 12 "tests/99__calculator/string.code"
        self->data = ((uint8_t *) realloc(((void *) self->data), self->data_size));
#line 16 "tests/99__calculator/string.code"
    }
#line 17 "tests/99__calculator/string.code"
    self->data[self->length] = c;
#line 18 "tests/99__calculator/string.code"
    self->length = self->length + 1u;
#line 19 "tests/99__calculator/string.code"
    return self;
#line 20 "tests/99__calculator/string.code"
}

#line 22 "tests/99__calculator/string.code"
struct String pstring_Builder__build(struct string_Builder *self) {
#line 23 "tests/99__calculator/string.code"
    pstring_Builder__write(self, 0);
#line 24 "tests/99__calculator/string.code"
    struct String string = (struct String){.data = self->data, .length = self->length - 1u};
#line 28 "tests/99__calculator/string.code"
    return *((struct String *) (&string));
#line 29 "tests/99__calculator/string.code"
}

#line 31 "tests/99__calculator/string.code"
struct string_Builder string__make_string_builder() {
#line 32 "tests/99__calculator/string.code"
    return string__make_string_builder_with_data_size(4u);
#line 33 "tests/99__calculator/string.code"
}

#line 35 "tests/99__calculator/string.code"
struct string_Builder string__make_string_builder_with_data_size(uintmax_t data_size) {
#line 36 "tests/99__calculator/string.code"
    return (struct string_Builder){.data = ((uint8_t *) malloc(data_size)), .data_size = data_size, .length = 0u};
#line 41 "tests/99__calculator/string.code"
}

#line 43 "tests/99__calculator/string.code"
void pstring_Builder__write_char(struct string_Builder *self, uint8_t c) {
#line 44 "tests/99__calculator/string.code"
    pstring_Builder__write(self, c);
#line 45 "tests/99__calculator/string.code"
}

