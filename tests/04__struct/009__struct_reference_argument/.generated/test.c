#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct Point;

struct Point {
    int32_t x;
    int32_t y;
};

int32_t test__main();

int32_t test__get_y(struct Point *point);

int32_t main(int argc, const char **argv) {
    return test__main();
}

#line 6 "tests/04__struct/009__struct_reference_argument/test.code"
int32_t test__main() {
#line 7 "tests/04__struct/009__struct_reference_argument/test.code"
    struct Point point = (struct Point){.x = 16, .y = 32};
#line 8 "tests/04__struct/009__struct_reference_argument/test.code"
    return test__get_y(&point) - 32;
}

#line 11 "tests/04__struct/009__struct_reference_argument/test.code"
int32_t test__get_y(struct Point *point) {
#line 12 "tests/04__struct/009__struct_reference_argument/test.code"
    return point->y;
}

