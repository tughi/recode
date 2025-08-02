#include "test.h"
#include "calculator__expression.h"
#include "calculator__source.h"
#include "libc.h"
#include "io.h"
#include "calculator__parser.h"
#include "calculator__tokenizer.h"
#include "os.h"
#include "string.h"

struct io_Writer *os__stdout;
struct io_Writer *os__stderr;
void *malloc(uintmax_t size);

#line 7 "tests/99__calculator/os.code"
void os__init() {
#line 8 "tests/99__calculator/os.code"
    {
#line 8 "tests/99__calculator/os.code"
        struct io_Writer *__001__ = (struct io_Writer *)malloc(sizeof(struct io_Writer));
#line 8 "tests/99__calculator/os.code"
        *__001__ = (struct io_Writer){.self = __stdoutp, .write_char = ((void (*)(void *self, uint8_t c)) plibc_FILE__write_char)};
#line 8 "tests/99__calculator/os.code"
        os__stdout = __001__;
    }
#line 9 "tests/99__calculator/os.code"
    {
#line 9 "tests/99__calculator/os.code"
        struct io_Writer *__001__ = (struct io_Writer *)malloc(sizeof(struct io_Writer));
#line 9 "tests/99__calculator/os.code"
        *__001__ = (struct io_Writer){.self = __stderrp, .write_char = ((void (*)(void *self, uint8_t c)) plibc_FILE__write_char)};
#line 9 "tests/99__calculator/os.code"
        os__stderr = __001__;
    }
}

#line 12 "tests/99__calculator/os.code"
void plibc_FILE__write_char(struct libc_FILE *self, uint8_t c) {
#line 13 "tests/99__calculator/os.code"
    {
#line 13 "tests/99__calculator/os.code"
        int32_t __001__ = ((int32_t) c);
#line 13 "tests/99__calculator/os.code"
        struct libc_FILE *__002__ = self;
#line 13 "tests/99__calculator/os.code"
        fputc(__001__, __002__);
    }
}

