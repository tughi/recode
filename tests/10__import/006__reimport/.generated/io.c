#include "test.h"
#include "io.h"
#include "libc.h"

void *malloc(uintmax_t size);

#line 7 "tests/10__import/006__reimport/io.code"
struct io_Writer *pio_Writer__write(struct io_Writer *writer, int32_t c) {
#line 8 "tests/10__import/006__reimport/io.code"
    {
#line 8 "tests/10__import/006__reimport/io.code"
        void *__001__ = writer->self;
#line 8 "tests/10__import/006__reimport/io.code"
        int32_t __002__ = c;
#line 8 "tests/10__import/006__reimport/io.code"
        writer->write_char(__001__, __002__);
    }
#line 9 "tests/10__import/006__reimport/io.code"
    return writer;
}

#line 12 "tests/10__import/006__reimport/io.code"
int32_t plibc_FILE__write_char(struct libc_FILE *file, int32_t c) {
#line 13 "tests/10__import/006__reimport/io.code"
    {
#line 13 "tests/10__import/006__reimport/io.code"
        int32_t __001__ = c;
#line 13 "tests/10__import/006__reimport/io.code"
        struct libc_FILE *__002__ = file;
#line 13 "tests/10__import/006__reimport/io.code"
        return fputc(__001__, __002__);
    }
}

