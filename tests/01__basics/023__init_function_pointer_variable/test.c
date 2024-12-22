#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t test__main();

int32_t test__echo__0_value(int32_t value);

int32_t main(int argc, const char **argv) {
    return test__main();
}

#line 3 "tests/01__basics/023__init_function_pointer_variable/test.code"
int32_t test__main() {
#line 4 "tests/01__basics/023__init_function_pointer_variable/test.code"
    int32_t (*function_pointer)(int32_t value) = test__echo__0_value;
#line 6 "tests/01__basics/023__init_function_pointer_variable/test.code"
    return 0;
}

#line 9 "tests/01__basics/023__init_function_pointer_variable/test.code"
int32_t test__echo__0_value(int32_t value) {
#line 10 "tests/01__basics/023__init_function_pointer_variable/test.code"
    return value;
}

