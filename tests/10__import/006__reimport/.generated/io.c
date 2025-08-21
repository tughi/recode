#include "test.h"
#include "io.h"
#include "libc.h"

void *malloc(uintmax_t size);

#line 7 "tests/10__import/006__reimport/io/writer.code"
struct io_Writer *pio_Writer__write(struct io_Writer *writer, int32_t c) {
#line 8 "tests/10__import/006__reimport/io/writer.code"
    writer->write_char(writer->self, c);
#line 9 "tests/10__import/006__reimport/io/writer.code"
    {
#line 9 "tests/10__import/006__reimport/io/writer.code"
        struct io_Writer *__001__ = writer;
#line 9 "tests/10__import/006__reimport/io/writer.code"
        return __001__;
#line 9 "tests/10__import/006__reimport/io/writer.code"
    }
#line 10 "tests/10__import/006__reimport/io/writer.code"
}

#line 12 "tests/10__import/006__reimport/io/writer.code"
int32_t plibc_FILE__write_char(struct libc_FILE *file, int32_t c) {
#line 13 "tests/10__import/006__reimport/io/writer.code"
    {
#line 13 "tests/10__import/006__reimport/io/writer.code"
        int32_t __001__ = fputc(c, file);
#line 13 "tests/10__import/006__reimport/io/writer.code"
        return __001__;
#line 13 "tests/10__import/006__reimport/io/writer.code"
    }
#line 14 "tests/10__import/006__reimport/io/writer.code"
}

