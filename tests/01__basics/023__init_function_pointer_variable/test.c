#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t main();

int32_t echo(int32_t value);

#line 1 "tests/01__basics/023__init_function_pointer_variable/test.code"
int32_t main() {
#line 2 "tests/01__basics/023__init_function_pointer_variable/test.code"
    int32_t (*function_pointer)(int32_t value) = echo;
#line 4 "tests/01__basics/023__init_function_pointer_variable/test.code"
    return 0;
}

#line 7 "tests/01__basics/023__init_function_pointer_variable/test.code"
int32_t echo(int32_t value) {
#line 8 "tests/01__basics/023__init_function_pointer_variable/test.code"
    return value;
}

