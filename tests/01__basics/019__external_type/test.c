#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct FILE FILE;

extern FILE *stdout;
int32_t fputc(uint32_t ch, FILE *file);

void main();

#line 7 "tests/01__basics/019__external_type/test.code"
void main() {
#line 8 "tests/01__basics/019__external_type/test.code"
    fputc('4', stdout);
#line 9 "tests/01__basics/019__external_type/test.code"
    fputc('2', stdout);
#line 10 "tests/01__basics/019__external_type/test.code"
    fputc('\n', stdout);
}
