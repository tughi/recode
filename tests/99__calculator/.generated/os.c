#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

#include "os.h"

struct io_Writer *os__stdout;
struct io_Writer *os__stderr;
#line 7 "tests/99__calculator/os.code"
void os__init() {
#line 8 "tests/99__calculator/os.code"
    os__stdout = __alloc__io_Writer__((struct io_Writer){.self = __stdoutp, .write_char = ((void (*)(void *self, uint8_t c)) plibc_FILE__write_char)});
#line 9 "tests/99__calculator/os.code"
    os__stderr = __alloc__io_Writer__((struct io_Writer){.self = __stderrp, .write_char = ((void (*)(void *self, uint8_t c)) plibc_FILE__write_char)});
}

#line 12 "tests/99__calculator/os.code"
void plibc_FILE__write_char(struct libc_FILE *self, uint8_t c) {
#line 13 "tests/99__calculator/os.code"
    fputc(((int32_t) c), self);
}

