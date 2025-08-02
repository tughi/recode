#include "test.h"

void *malloc(uintmax_t size);

#line 3 "tests/01__basics/012__procedure_without_return/test.code"
int32_t test__main() {
#line 4 "tests/01__basics/012__procedure_without_return/test.code"
    test__finish();
#line 5 "tests/01__basics/012__procedure_without_return/test.code"
    return 1;
}

#line 8 "tests/01__basics/012__procedure_without_return/test.code"
void test__finish() {
#line 9 "tests/01__basics/012__procedure_without_return/test.code"
    test__nothing();
#line 10 "tests/01__basics/012__procedure_without_return/test.code"
    exit(0);
}

#line 13 "tests/01__basics/012__procedure_without_return/test.code"
void test__nothing() {
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

