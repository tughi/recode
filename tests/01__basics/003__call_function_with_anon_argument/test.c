#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t test__main();

int32_t test__echo(int32_t value);

int32_t main(int argc, const char **argv) {
    return test__main();
}

#line 3 "tests/01__basics/003__call_function_with_anon_argument/test.code"
int32_t test__main() {
#line 4 "tests/01__basics/003__call_function_with_anon_argument/test.code"
    return test__echo(0);
}

#line 7 "tests/01__basics/003__call_function_with_anon_argument/test.code"
int32_t test__echo(int32_t value) {
#line 8 "tests/01__basics/003__call_function_with_anon_argument/test.code"
    return value;
}

