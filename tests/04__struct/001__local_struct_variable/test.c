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

#line 8 "tests/04__struct/001__local_struct_variable/test.code"
int32_t test__main() {
#line 9 "tests/04__struct/001__local_struct_variable/test.code"
    struct Point point;
#line 10 "tests/04__struct/001__local_struct_variable/test.code"
    return 0;
}

