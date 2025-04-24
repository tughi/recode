#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

#include "test.h"

#line 11 "tests/04__struct/005__assign_struct_member/test.code"
int32_t test__main() {
#line 12 "tests/04__struct/005__assign_struct_member/test.code"
    struct Line line;
#line 13 "tests/04__struct/005__assign_struct_member/test.code"
    line.p2.y = 64;
#line 14 "tests/04__struct/005__assign_struct_member/test.code"
    return line.p2.y - 64;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

