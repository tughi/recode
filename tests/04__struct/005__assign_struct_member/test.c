#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct Point;

struct Line;

struct Point {
    int32_t x;
    int32_t y;
};

struct Line {
    struct Point p1;
    struct Point p2;
};

int32_t main();

#line 11 "tests/04__struct/005__assign_struct_member/test.code"
int32_t main() {
#line 12 "tests/04__struct/005__assign_struct_member/test.code"
    struct Line line;
#line 13 "tests/04__struct/005__assign_struct_member/test.code"
    line.p2.y = 64;
#line 14 "tests/04__struct/005__assign_struct_member/test.code"
    return line.p2.y - 64;
}

