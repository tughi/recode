#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/01__basics/020__reference_local_variable/test.code"
int32_t test__main() {
#line 2 "tests/01__basics/020__reference_local_variable/test.code"
    int32_t value = 42;
#line 3 "tests/01__basics/020__reference_local_variable/test.code"
    int32_t *value_ref = &value;
#line 4 "tests/01__basics/020__reference_local_variable/test.code"
    return *value_ref - 42;
#line 5 "tests/01__basics/020__reference_local_variable/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

