#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct FILE FILE;

extern FILE *stdout;
int32_t main();

FILE *pFILE__write__1_char(FILE *self, uint8_t ch);

int32_t fputc(int32_t c, FILE *stream);

#line 1 "tests/05__extensions/001__external_type_extension/test.code"
int32_t main() {
#line 2 "tests/05__extensions/001__external_type_extension/test.code"
    pFILE__write__1_char(pFILE__write__1_char(pFILE__write__1_char(stdout, '4'), '2'), '\n');
#line 3 "tests/05__extensions/001__external_type_extension/test.code"
    return 0;
}

#line 6 "tests/05__extensions/001__external_type_extension/test.code"
FILE *pFILE__write__1_char(FILE *self, uint8_t ch) {
#line 7 "tests/05__extensions/001__external_type_extension/test.code"
    fputc((int32_t) ch, stdout);
#line 8 "tests/05__extensions/001__external_type_extension/test.code"
    return self;
}

