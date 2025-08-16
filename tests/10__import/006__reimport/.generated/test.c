#include "test.h"
#include "io.h"
#include "libc.h"

void *malloc(uintmax_t size);

#line 4 "tests/10__import/006__reimport/test.code"
int32_t test__main() {
#line 5 "tests/10__import/006__reimport/test.code"
    struct io_Writer stdout = (struct io_Writer){.self = __stdoutp, .write_char = ((int32_t (*)(void *self, int32_t c)) plibc_FILE__write_char)};
#line 7 "tests/10__import/006__reimport/test.code"
    pio_Writer__write(pio_Writer__write(pio_Writer__write(&stdout, 52), 50), 10);
#line 9 "tests/10__import/006__reimport/test.code"
    {
#line 9 "tests/10__import/006__reimport/test.code"
        int32_t __001__ = 0;
#line 9 "tests/10__import/006__reimport/test.code"
        return __001__;
#line 9 "tests/10__import/006__reimport/test.code"
    }
#line 10 "tests/10__import/006__reimport/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

