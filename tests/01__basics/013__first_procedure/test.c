#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

void exit(int32_t status);

int32_t main();

void finish();

void nothing();

#line 3 "tests/01__basics/013__first_procedure/test.code"
int32_t main() {
#line 4 "tests/01__basics/013__first_procedure/test.code"
    finish();
#line 5 "tests/01__basics/013__first_procedure/test.code"
    return 1;
}

#line 8 "tests/01__basics/013__first_procedure/test.code"
void finish() {
#line 9 "tests/01__basics/013__first_procedure/test.code"
    nothing();
#line 10 "tests/01__basics/013__first_procedure/test.code"
    exit(0);
}

#line 13 "tests/01__basics/013__first_procedure/test.code"
void nothing() {
}

