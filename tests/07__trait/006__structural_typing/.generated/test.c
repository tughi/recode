#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/07__trait/006__structural_typing/test.code"
int32_t test__main() {
#line 2 "tests/07__trait/006__structural_typing/test.code"
    struct test_Writer out = (struct test_Writer){.self = __stdoutp, .write_char = ((void (*)(void *self, uint8_t c)) ptest_FILE__write_char__anon)};
#line 7 "tests/07__trait/006__structural_typing/test.code"
    {
#line 7 "tests/07__trait/006__structural_typing/test.code"
        struct test_Writer *__001__ = &out;
#line 7 "tests/07__trait/006__structural_typing/test.code"
        struct test_Number __002__ = (struct test_Number){.value = 42};
#line 7 "tests/07__trait/006__structural_typing/test.code"
        void *__003__ = &__002__;
#line 7 "tests/07__trait/006__structural_typing/test.code"
        void (*__004__)(void *self, struct test_Writer *writer) = ((void (*)(void *self, struct test_Writer *writer)) ptest_Number__write_to__anon);
#line 7 "tests/07__trait/006__structural_typing/test.code"
        struct test_Writable __005__ = (struct test_Writable){.self = __003__, .write_to = __004__};
#line 7 "tests/07__trait/006__structural_typing/test.code"
        struct test_Writer *__006__ = ptest_Writer__write__anon(__001__, __005__);
#line 7 "tests/07__trait/006__structural_typing/test.code"
        ptest_Writer__end_line(__006__);
#line 7 "tests/07__trait/006__structural_typing/test.code"
    }
#line 12 "tests/07__trait/006__structural_typing/test.code"
    {
#line 12 "tests/07__trait/006__structural_typing/test.code"
        struct test_Writer *__007__ = &out;
#line 12 "tests/07__trait/006__structural_typing/test.code"
        int32_t __008__ = 42;
#line 12 "tests/07__trait/006__structural_typing/test.code"
        void *__009__ = &__008__;
#line 12 "tests/07__trait/006__structural_typing/test.code"
        void (*__010__)(void *self, struct test_Writer *writer) = ((void (*)(void *self, struct test_Writer *writer)) pi32__write_to__anon);
#line 12 "tests/07__trait/006__structural_typing/test.code"
        struct test_Writable __011__ = (struct test_Writable){.self = __009__, .write_to = __010__};
#line 12 "tests/07__trait/006__structural_typing/test.code"
        struct test_Writer *__012__ = ptest_Writer__write__anon(__007__, __011__);
#line 12 "tests/07__trait/006__structural_typing/test.code"
        ptest_Writer__end_line(__012__);
#line 12 "tests/07__trait/006__structural_typing/test.code"
    }
#line 14 "tests/07__trait/006__structural_typing/test.code"
    {
#line 14 "tests/07__trait/006__structural_typing/test.code"
        int32_t __013__ = 0;
#line 14 "tests/07__trait/006__structural_typing/test.code"
        return __013__;
#line 14 "tests/07__trait/006__structural_typing/test.code"
    }
#line 15 "tests/07__trait/006__structural_typing/test.code"
}

#line 21 "tests/07__trait/006__structural_typing/test.code"
void ptest_Number__write_to__anon(struct test_Number *self, struct test_Writer *writer) {
#line 22 "tests/07__trait/006__structural_typing/test.code"
    pi32__write_to__anon(&self->value, writer);
#line 23 "tests/07__trait/006__structural_typing/test.code"
}

#line 25 "tests/07__trait/006__structural_typing/test.code"
void pi32__write_to__anon(int32_t *self, struct test_Writer *writer) {
#line 26 "tests/07__trait/006__structural_typing/test.code"
    int32_t number = *self;
#line 27 "tests/07__trait/006__structural_typing/test.code"
    if (number < 0) {
#line 28 "tests/07__trait/006__structural_typing/test.code"
        writer->write_char(writer->self, '-');
#line 29 "tests/07__trait/006__structural_typing/test.code"
        number = -number;
#line 30 "tests/07__trait/006__structural_typing/test.code"
    }
#line 31 "tests/07__trait/006__structural_typing/test.code"
    if (number >= 10) {
#line 32 "tests/07__trait/006__structural_typing/test.code"
        int32_t factor = number / 10;
#line 33 "tests/07__trait/006__structural_typing/test.code"
        pi32__write_to__anon(&factor, writer);
#line 34 "tests/07__trait/006__structural_typing/test.code"
    }
#line 35 "tests/07__trait/006__structural_typing/test.code"
    writer->write_char(writer->self, ((uint8_t) (number % 10)) + '0');
#line 36 "tests/07__trait/006__structural_typing/test.code"
}

#line 44 "tests/07__trait/006__structural_typing/test.code"
struct test_Writer *ptest_Writer__end_line(struct test_Writer *self) {
#line 45 "tests/07__trait/006__structural_typing/test.code"
    self->write_char(self->self, '\n');
#line 46 "tests/07__trait/006__structural_typing/test.code"
    {
#line 46 "tests/07__trait/006__structural_typing/test.code"
        struct test_Writer *__001__ = self;
#line 46 "tests/07__trait/006__structural_typing/test.code"
        return __001__;
#line 46 "tests/07__trait/006__structural_typing/test.code"
    }
#line 47 "tests/07__trait/006__structural_typing/test.code"
}

#line 55 "tests/07__trait/006__structural_typing/test.code"
struct test_Writer *ptest_Writer__write__anon(struct test_Writer *self, struct test_Writable writable) {
#line 56 "tests/07__trait/006__structural_typing/test.code"
    writable.write_to(writable.self, self);
#line 57 "tests/07__trait/006__structural_typing/test.code"
    {
#line 57 "tests/07__trait/006__structural_typing/test.code"
        struct test_Writer *__001__ = self;
#line 57 "tests/07__trait/006__structural_typing/test.code"
        return __001__;
#line 57 "tests/07__trait/006__structural_typing/test.code"
    }
#line 58 "tests/07__trait/006__structural_typing/test.code"
}

#line 68 "tests/07__trait/006__structural_typing/test.code"
void ptest_FILE__write_char__anon(struct test_FILE *self, uint8_t c) {
#line 69 "tests/07__trait/006__structural_typing/test.code"
    fputc(((int32_t) c), self);
#line 70 "tests/07__trait/006__structural_typing/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

