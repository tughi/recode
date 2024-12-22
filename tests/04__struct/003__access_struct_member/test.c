#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct Point;

struct Point {
    int32_t x;
    int32_t y;
};

int32_t test__main();

int32_t main(int argc, const char **argv) {
    return test__main();
}

#line 8 "tests/04__struct/003__access_struct_member/test.code"
int32_t test__main() {
#line 9 "tests/04__struct/003__access_struct_member/test.code"
    struct Point point = (struct Point){.x = 16, .y = 32};
#line 10 "tests/04__struct/003__access_struct_member/test.code"
    return point.x - 16;
}

