#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

#include "test.h"

#line 1 "tests/01__basics/021__define_procedure_pointer_variable/test.code"
int32_t test__main() {
#line 2 "tests/01__basics/021__define_procedure_pointer_variable/test.code"
    int32_t (*procedure_pointer)(int32_t value);
#line 3 "tests/01__basics/021__define_procedure_pointer_variable/test.code"
    return 0;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

