#include "test.h"

#line 4 "tests/10__import/006__reimport/test.code"
int32_t test__main() {
#line 5 "tests/10__import/006__reimport/test.code"
    struct io_Writer stdout = (struct io_Writer){.self = __stdoutp, .write_char = ((int32_t (*)(void *self, int32_t c)) plibc_FILE__write_char)};
#line 7 "tests/10__import/006__reimport/test.code"
    pio_Writer__write__1_char(pio_Writer__write__1_char(pio_Writer__write__1_char(&stdout, 52), 50), 10);
#line 9 "tests/10__import/006__reimport/test.code"
    return 0;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

