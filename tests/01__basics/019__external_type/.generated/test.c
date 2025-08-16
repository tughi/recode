#include "test.h"

void *malloc(uintmax_t size);

#line 7 "tests/01__basics/019__external_type/test.code"
int32_t test__main() {
#line 8 "tests/01__basics/019__external_type/test.code"
    fputc(52, __stdoutp);
#line 9 "tests/01__basics/019__external_type/test.code"
    fputc(50, __stdoutp);
#line 10 "tests/01__basics/019__external_type/test.code"
    fputc(10, __stdoutp);
#line 11 "tests/01__basics/019__external_type/test.code"
    return 0;
#line 12 "tests/01__basics/019__external_type/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

