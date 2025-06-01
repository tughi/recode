#include "test.h"

#line 1 "tests/01__basics/003__call_procedure_with_anon_argument/test.code"
int32_t test__main() {
#line 2 "tests/01__basics/003__call_procedure_with_anon_argument/test.code"
    return test__echo(0);
}

#line 5 "tests/01__basics/003__call_procedure_with_anon_argument/test.code"
int32_t test__echo(int32_t value) {
#line 6 "tests/01__basics/003__call_procedure_with_anon_argument/test.code"
    return value;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

