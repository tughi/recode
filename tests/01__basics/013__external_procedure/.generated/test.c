#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

void exit(int32_t status);

int32_t test__main();

int32_t main(int argc, const char **argv) {
    return test__main();
}

#line 3 "tests/01__basics/013__external_procedure/test.code"
int32_t test__main() {
#line 4 "tests/01__basics/013__external_procedure/test.code"
    exit(0);
#line 5 "tests/01__basics/013__external_procedure/test.code"
    return 1;
}

