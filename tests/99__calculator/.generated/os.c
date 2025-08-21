#include "test.h"
#include "calculator__expression.h"
#include "calculator__source.h"
#include "io.h"
#include "libc.h"
#include "calculator__parser.h"
#include "calculator__tokenizer.h"
#include "os.h"
#include "string.h"

struct io_Writer *os__stdout;
struct io_Writer *os__stderr;
void *malloc(uintmax_t size);

#line 7 "tests/99__calculator/os/io.code"
void os__init() {
#line 8 "tests/99__calculator/os/io.code"
    {
#line 8 "tests/99__calculator/os/io.code"
        struct io_Writer *__001__ = (struct io_Writer *)malloc(sizeof(struct io_Writer));
#line 8 "tests/99__calculator/os/io.code"
        *__001__ = (struct io_Writer){.self = __stdoutp, .write_char = ((void (*)(void *self, uint8_t c)) plibc_FILE__write_char)};
#line 8 "tests/99__calculator/os/io.code"
        os__stdout = __001__;
#line 8 "tests/99__calculator/os/io.code"
    }
#line 9 "tests/99__calculator/os/io.code"
    {
#line 9 "tests/99__calculator/os/io.code"
        struct io_Writer *__002__ = (struct io_Writer *)malloc(sizeof(struct io_Writer));
#line 9 "tests/99__calculator/os/io.code"
        *__002__ = (struct io_Writer){.self = __stderrp, .write_char = ((void (*)(void *self, uint8_t c)) plibc_FILE__write_char)};
#line 9 "tests/99__calculator/os/io.code"
        os__stderr = __002__;
#line 9 "tests/99__calculator/os/io.code"
    }
#line 10 "tests/99__calculator/os/io.code"
}

#line 12 "tests/99__calculator/os/io.code"
void plibc_FILE__write_char(struct libc_FILE *self, uint8_t c) {
#line 13 "tests/99__calculator/os/io.code"
    fputc(((int32_t) c), self);
#line 14 "tests/99__calculator/os/io.code"
}

