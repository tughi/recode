#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/07__trait/006__structural_typing/test.code"
int32_t test__main() {
#line 2 "tests/07__trait/006__structural_typing/test.code"
    struct test_Writer out = (struct test_Writer){.self = __stdoutp, .write_char = ((void (*)(void *self, uint8_t c)) ptest_FILE__write_char)};
#line 7 "tests/07__trait/006__structural_typing/test.code"
    {
#line 7 "tests/07__trait/006__structural_typing/test.code"
        struct test_Writer *__001__ = &out;
#line 7 "tests/07__trait/006__structural_typing/test.code"
        struct String __002__ = (struct String){.data = "Hello, World!", .length = 13};
#line 7 "tests/07__trait/006__structural_typing/test.code"
        void *__003__ = &__002__;
#line 7 "tests/07__trait/006__structural_typing/test.code"
        void (*__004__)(void *self, struct test_Writer *writer) = ((void (*)(void *self, struct test_Writer *writer)) pstr__write_to);
#line 7 "tests/07__trait/006__structural_typing/test.code"
        struct test_Writable __005__ = (struct test_Writable){.self = __003__, .write_to = __004__};
#line 7 "tests/07__trait/006__structural_typing/test.code"
        struct test_Writer *__006__ = ptest_Writer__write(__001__, __005__);
#line 7 "tests/07__trait/006__structural_typing/test.code"
        ptest_Writer__end_line(__006__);
    }
#line 12 "tests/07__trait/006__structural_typing/test.code"
    {
#line 12 "tests/07__trait/006__structural_typing/test.code"
        struct test_Writer *__001__ = &out;
#line 12 "tests/07__trait/006__structural_typing/test.code"
        int32_t __002__ = 42;
#line 12 "tests/07__trait/006__structural_typing/test.code"
        void *__003__ = &__002__;
#line 12 "tests/07__trait/006__structural_typing/test.code"
        void (*__004__)(void *self, struct test_Writer *writer) = ((void (*)(void *self, struct test_Writer *writer)) pi32__write_to);
#line 12 "tests/07__trait/006__structural_typing/test.code"
        struct test_Writable __005__ = (struct test_Writable){.self = __003__, .write_to = __004__};
#line 12 "tests/07__trait/006__structural_typing/test.code"
        struct test_Writer *__006__ = ptest_Writer__write(__001__, __005__);
#line 12 "tests/07__trait/006__structural_typing/test.code"
        ptest_Writer__end_line(__006__);
    }
#line 14 "tests/07__trait/006__structural_typing/test.code"
    return 0;
}

#line 17 "tests/07__trait/006__structural_typing/test.code"
void pi32__write_to(int32_t *self, struct test_Writer *writer) {
#line 18 "tests/07__trait/006__structural_typing/test.code"
    int32_t number = *self;
#line 19 "tests/07__trait/006__structural_typing/test.code"
    if (number < 0) {
#line 20 "tests/07__trait/006__structural_typing/test.code"
        writer->write_char(writer->self, '-');
#line 21 "tests/07__trait/006__structural_typing/test.code"
        number = -number;
    }
#line 23 "tests/07__trait/006__structural_typing/test.code"
    if (number >= 10) {
#line 24 "tests/07__trait/006__structural_typing/test.code"
        int32_t factor = number / 10;
#line 25 "tests/07__trait/006__structural_typing/test.code"
        pi32__write_to(&factor, writer);
    }
#line 27 "tests/07__trait/006__structural_typing/test.code"
    writer->write_char(writer->self, ((uint8_t) (number % 10)) + '0');
}

#line 30 "tests/07__trait/006__structural_typing/test.code"
void pstr__write_to(struct String *self, struct test_Writer *writer) {
#line 31 "tests/07__trait/006__structural_typing/test.code"
    struct String *string = ((struct String *) self);
#line 32 "tests/07__trait/006__structural_typing/test.code"
    uintmax_t index = 0u;
#line 33 "tests/07__trait/006__structural_typing/test.code"
    while (index < string->length) {
#line 34 "tests/07__trait/006__structural_typing/test.code"
        writer->write_char(writer->self, string->data[index]);
#line 35 "tests/07__trait/006__structural_typing/test.code"
        index = index + 1u;
    }
}

#line 45 "tests/07__trait/006__structural_typing/test.code"
struct test_Writer *ptest_Writer__end_line(struct test_Writer *self) {
#line 46 "tests/07__trait/006__structural_typing/test.code"
    self->write_char(self->self, '\n');
#line 47 "tests/07__trait/006__structural_typing/test.code"
    return self;
}

#line 56 "tests/07__trait/006__structural_typing/test.code"
struct test_Writer *ptest_Writer__write(struct test_Writer *self, struct test_Writable writable) {
#line 57 "tests/07__trait/006__structural_typing/test.code"
    writable.write_to(writable.self, self);
#line 58 "tests/07__trait/006__structural_typing/test.code"
    return self;
}

#line 69 "tests/07__trait/006__structural_typing/test.code"
void ptest_FILE__write_char(struct test_FILE *self, uint8_t c) {
#line 70 "tests/07__trait/006__structural_typing/test.code"
    fputc(((int32_t) c), self);
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

