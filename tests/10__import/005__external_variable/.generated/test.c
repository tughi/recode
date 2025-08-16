#include "test.h"
#include "libc.h"

void *malloc(uintmax_t size);

#line 3 "tests/10__import/005__external_variable/test.code"
int32_t test__main() {
#line 4 "tests/10__import/005__external_variable/test.code"
    fputc(((int32_t) '4'), __stdoutp);
#line 5 "tests/10__import/005__external_variable/test.code"
    fputc(((int32_t) '2'), __stdoutp);
#line 6 "tests/10__import/005__external_variable/test.code"
    fputc(((int32_t) '\n'), __stdoutp);
#line 8 "tests/10__import/005__external_variable/test.code"
    return 0;
#line 9 "tests/10__import/005__external_variable/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

