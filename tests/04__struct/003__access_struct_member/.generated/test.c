#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

#include "test.h"

#line 6 "tests/04__struct/003__access_struct_member/test.code"
int32_t test__main() {
#line 7 "tests/04__struct/003__access_struct_member/test.code"
    struct test__Point point = (struct test__Point){.x = 16, .y = 32};
#line 8 "tests/04__struct/003__access_struct_member/test.code"
    return point.x - 16;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

