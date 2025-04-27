#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

#include "test.h"

#line 5 "tests/04__struct/012__callable_struct_member/test.code"
int32_t test__forty_two() {
#line 6 "tests/04__struct/012__callable_struct_member/test.code"
    return 42;
}

#line 9 "tests/04__struct/012__callable_struct_member/test.code"
int32_t test__main() {
#line 10 "tests/04__struct/012__callable_struct_member/test.code"
    struct test__Function procedure = (struct test__Function){.run = test__forty_two};
#line 12 "tests/04__struct/012__callable_struct_member/test.code"
    return procedure.run() - 42;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

