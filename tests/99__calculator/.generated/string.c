#include "test.h"
#include "calculator__expression.h"
#include "calculator__source.h"
#include "libc.h"
#include "io.h"
#include "calculator__parser.h"
#include "calculator__tokenizer.h"
#include "os.h"
#include "string.h"

struct string_Builder *__alloc__string_Builder__(struct string_Builder value) {
    struct string_Builder *result = (struct string_Builder *)malloc(sizeof(struct string_Builder));
    *result = value;
    return result;
}

#line 9 "tests/99__calculator/string.code"
struct string_Builder *pstring_Builder__write(struct string_Builder *self, uint8_t c) {
#line 10 "tests/99__calculator/string.code"
    if (self->length == self->data_size) {
#line 11 "tests/99__calculator/string.code"
        self->data_size = self->data_size + 8;
#line 12 "tests/99__calculator/string.code"
        self->data = ((uint8_t *) realloc(((void *) self->data), ((uint64_t) self->data_size)));
    }
#line 17 "tests/99__calculator/string.code"
    {
#line 17 "tests/99__calculator/string.code"
        uintmax_t __001__ = self->length;
#line 17 "tests/99__calculator/string.code"
        self->data[__001__] = c;
    }
#line 18 "tests/99__calculator/string.code"
    self->length = self->length + 1;
#line 19 "tests/99__calculator/string.code"
    return self;
}

#line 22 "tests/99__calculator/string.code"
struct String pstring_Builder__build(struct string_Builder *self) {
#line 23 "tests/99__calculator/string.code"
    {
#line 23 "tests/99__calculator/string.code"
        struct string_Builder *__001__ = self;
#line 23 "tests/99__calculator/string.code"
        uint8_t __002__ = 0;
#line 23 "tests/99__calculator/string.code"
        pstring_Builder__write(__001__, __002__);
    }
#line 24 "tests/99__calculator/string.code"
    struct String string;
#line 24 "tests/99__calculator/string.code"
    {
#line 25 "tests/99__calculator/string.code"
        uint8_t *__001__ = self->data;
#line 26 "tests/99__calculator/string.code"
        uintmax_t __002__ = self->length - 1;
#line 24 "tests/99__calculator/string.code"
        string = (struct String){.data = __001__, .length = __002__};
    }
#line 28 "tests/99__calculator/string.code"
    return *((struct String *) (&string));
}

#line 31 "tests/99__calculator/string.code"
struct string_Builder string__make_string_builder() {
#line 32 "tests/99__calculator/string.code"
    {
#line 32 "tests/99__calculator/string.code"
        uintmax_t __001__ = 4;
#line 32 "tests/99__calculator/string.code"
        return string__make_string_builder_with_data_size(__001__);
    }
}

#line 35 "tests/99__calculator/string.code"
struct string_Builder string__make_string_builder_with_data_size(uintmax_t data_size) {
#line 36 "tests/99__calculator/string.code"
    {
#line 37 "tests/99__calculator/string.code"
        uint8_t *__001__ = ((uint8_t *) malloc(((uint64_t) data_size)));
#line 38 "tests/99__calculator/string.code"
        uintmax_t __002__ = data_size;
#line 39 "tests/99__calculator/string.code"
        uintmax_t __003__ = 0;
#line 36 "tests/99__calculator/string.code"
        return (struct string_Builder){.data = __001__, .data_size = __002__, .length = __003__};
    }
}

#line 43 "tests/99__calculator/string.code"
void pstring_Builder__write_char(struct string_Builder *self, uint8_t c) {
#line 44 "tests/99__calculator/string.code"
    {
#line 44 "tests/99__calculator/string.code"
        struct string_Builder *__001__ = self;
#line 44 "tests/99__calculator/string.code"
        uint8_t __002__ = c;
#line 44 "tests/99__calculator/string.code"
        pstring_Builder__write(__001__, __002__);
    }
}

