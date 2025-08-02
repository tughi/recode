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
        {
#line 13 "tests/99__calculator/string.code"
            void *__001__ = ((void *) self->data);
#line 14 "tests/99__calculator/string.code"
            uintmax_t __002__ = self->data_size;
#line 12 "tests/99__calculator/string.code"
            self->data = ((uint8_t *) realloc(__001__, __002__));
        }
    }
#line 17 "tests/99__calculator/string.code"
    {
#line 17 "tests/99__calculator/string.code"
        uintmax_t __001__ = self->length;
#line 17 "tests/99__calculator/string.code"
        self->data[__001__] = c;
    }
#line 18 "tests/99__calculator/string.code"
    self->length = self->length + 1u;
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
        uintmax_t __002__ = self->length - 1u;
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
        uintmax_t __001__ = 4u;
#line 32 "tests/99__calculator/string.code"
        return string__make_string_builder_with_data_size(__001__);
    }
}

#line 35 "tests/99__calculator/string.code"
struct string_Builder string__make_string_builder_with_data_size(uintmax_t data_size) {
#line 36 "tests/99__calculator/string.code"
    {
#line 37 "tests/99__calculator/string.code"
        uintmax_t __001__ = data_size;
#line 37 "tests/99__calculator/string.code"
        uint8_t *__002__ = ((uint8_t *) malloc(__001__));
#line 38 "tests/99__calculator/string.code"
        uintmax_t __003__ = data_size;
#line 39 "tests/99__calculator/string.code"
        uintmax_t __004__ = 0u;
#line 36 "tests/99__calculator/string.code"
        return (struct string_Builder){.data = __002__, .data_size = __003__, .length = __004__};
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

