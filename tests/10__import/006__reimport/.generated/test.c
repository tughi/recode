#include "test.h"
#include "io.h"
#include "libc.h"

#line 4 "tests/10__import/006__reimport/test.code"
int32_t test__main() {
#line 5 "tests/10__import/006__reimport/test.code"
    struct io_Writer stdout = (struct io_Writer){.self = __stdoutp, .write_char = ((int32_t (*)(void *self, int32_t c)) plibc_FILE__write_char)};
#line 7 "tests/10__import/006__reimport/test.code"
    {
#line 7 "tests/10__import/006__reimport/test.code"
        struct io_Writer *__001__ = &stdout;
#line 7 "tests/10__import/006__reimport/test.code"
        int32_t __002__ = 52;
#line 7 "tests/10__import/006__reimport/test.code"
        struct io_Writer *__003__ = pio_Writer__write(__001__, __002__);
#line 7 "tests/10__import/006__reimport/test.code"
        int32_t __004__ = 50;
#line 7 "tests/10__import/006__reimport/test.code"
        struct io_Writer *__005__ = pio_Writer__write(__003__, __004__);
#line 7 "tests/10__import/006__reimport/test.code"
        int32_t __006__ = 10;
#line 7 "tests/10__import/006__reimport/test.code"
        pio_Writer__write(__005__, __006__);
    }
#line 9 "tests/10__import/006__reimport/test.code"
    return 0;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

