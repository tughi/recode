#include "test.h"
#include "io.h"
#include "libc.h"

void *malloc(uintmax_t size);

#line 7 "tests/10__import/006__reimport/io.code"
struct io_Writer *pio_Writer__write(struct io_Writer *writer, int32_t c) {
#line 8 "tests/10__import/006__reimport/io.code"
    writer->write_char(writer->self, c);
#line 9 "tests/10__import/006__reimport/io.code"
    return writer;
#line 10 "tests/10__import/006__reimport/io.code"
}

#line 12 "tests/10__import/006__reimport/io.code"
int32_t plibc_FILE__write_char(struct libc_FILE *file, int32_t c) {
#line 13 "tests/10__import/006__reimport/io.code"
    return fputc(c, file);
#line 14 "tests/10__import/006__reimport/io.code"
}

