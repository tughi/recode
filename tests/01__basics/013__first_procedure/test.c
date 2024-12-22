#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

void exit(int32_t status);

int32_t test__main();

void test__finish();

void test__nothing();

int32_t main(int argc, const char **argv) {
    return test__main();
}

#line 5 "tests/01__basics/013__first_procedure/test.code"
int32_t test__main() {
#line 6 "tests/01__basics/013__first_procedure/test.code"
    test__finish();
#line 7 "tests/01__basics/013__first_procedure/test.code"
    return 1;
}

#line 10 "tests/01__basics/013__first_procedure/test.code"
void test__finish() {
#line 11 "tests/01__basics/013__first_procedure/test.code"
    test__nothing();
#line 12 "tests/01__basics/013__first_procedure/test.code"
    exit(0);
}

#line 15 "tests/01__basics/013__first_procedure/test.code"
void test__nothing() {
}

