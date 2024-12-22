#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct FILE FILE;

extern FILE *__stdoutp;
int32_t fputc(int32_t ch, FILE *file);

int32_t test__main();

int32_t main(int argc, const char **argv) {
    return test__main();
}

#line 9 "tests/01__basics/019__external_type/test.code"
int32_t test__main() {
#line 10 "tests/01__basics/019__external_type/test.code"
    fputc(52, __stdoutp);
#line 11 "tests/01__basics/019__external_type/test.code"
    fputc(50, __stdoutp);
#line 12 "tests/01__basics/019__external_type/test.code"
    fputc(10, __stdoutp);
#line 13 "tests/01__basics/019__external_type/test.code"
    return 0;
}

