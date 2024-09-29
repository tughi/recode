#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct FILE FILE;

extern FILE (*stdout);
int32_t fputc(int32_t ch, FILE (*file));

int32_t main();

#line 7 "tests/01__basics/019__external_type/test.code"
int32_t main() {
#line 8 "tests/01__basics/019__external_type/test.code"
    fputc(52, stdout);
#line 9 "tests/01__basics/019__external_type/test.code"
    fputc(50, stdout);
#line 10 "tests/01__basics/019__external_type/test.code"
    fputc(10, stdout);
#line 11 "tests/01__basics/019__external_type/test.code"
    return 0;
}

