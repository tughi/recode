#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t test__main();

int32_t main(int argc, const char **argv) {
    return test__main();
}

#line 3 "tests/01__basics/021__define_function_pointer_variable/test.code"
int32_t test__main() {
#line 4 "tests/01__basics/021__define_function_pointer_variable/test.code"
    int32_t (*function_pointer)(int32_t value);
#line 5 "tests/01__basics/021__define_function_pointer_variable/test.code"
    return 0;
}

