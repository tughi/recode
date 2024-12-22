#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct FILE FILE;

extern FILE *__stdoutp;
int32_t test__main();

FILE *test__pFILE__write__1_char(FILE *self, uint8_t ch);

int32_t fputc(int32_t c, FILE *stream);

int32_t main(int argc, const char **argv) {
    return test__main();
}

#line 3 "tests/05__extensions/001__external_type_extension/test.code"
int32_t test__main() {
#line 4 "tests/05__extensions/001__external_type_extension/test.code"
    test__pFILE__write__1_char(test__pFILE__write__1_char(test__pFILE__write__1_char(__stdoutp, '4'), '2'), '\n');
#line 5 "tests/05__extensions/001__external_type_extension/test.code"
    return 0;
}

#line 8 "tests/05__extensions/001__external_type_extension/test.code"
FILE *test__pFILE__write__1_char(FILE *self, uint8_t ch) {
#line 9 "tests/05__extensions/001__external_type_extension/test.code"
    fputc(((int32_t) ch), __stdoutp);
#line 10 "tests/05__extensions/001__external_type_extension/test.code"
    return self;
}

