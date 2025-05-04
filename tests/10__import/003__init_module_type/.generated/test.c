#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

#include "test.h"

#line 3 "tests/10__import/003__init_module_type/test.code"
int32_t test__main() {
#line 4 "tests/10__import/003__init_module_type/test.code"
    struct foo_Foo bar = (struct foo_Foo){.value = 42};
#line 6 "tests/10__import/003__init_module_type/test.code"
    return bar.value - 42;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

