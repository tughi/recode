#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct Point;

struct Point {
    int32_t x;
    int32_t y;
};

int32_t main();

#line 6 "tests/04__struct/001__local_struct_variable/test.code"
int32_t main() {
#line 7 "tests/04__struct/001__local_struct_variable/test.code"
    struct Point point;
#line 8 "tests/04__struct/001__local_struct_variable/test.code"
    return 0;
}

