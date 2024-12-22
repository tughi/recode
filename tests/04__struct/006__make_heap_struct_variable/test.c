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

struct Point *__alloc_Point_value(struct Point value);

struct Line *__alloc_Line_value(struct Line value);

int32_t test__main();

void *malloc(uint64_t size);

int32_t main(int argc, const char **argv) {
    return test__main();
}

struct Point *__alloc_Point_value(struct Point value) {
    struct Point *result = (struct Point *)malloc(sizeof(struct Point));
    *result = value;
    return result;
}

struct Line *__alloc_Line_value(struct Line value) {
    struct Line *result = (struct Line *)malloc(sizeof(struct Line));
    *result = value;
    return result;
}

#line 13 "tests/04__struct/006__make_heap_struct_variable/test.code"
int32_t test__main() {
#line 14 "tests/04__struct/006__make_heap_struct_variable/test.code"
    struct Line *line = __alloc_Line_value((struct Line){.p1 = (struct Point){.x = 16, .y = 32}, .p2 = (struct Point){.x = 48, .y = 64}});
#line 18 "tests/04__struct/006__make_heap_struct_variable/test.code"
    return line->p1.x + line->p1.y + line->p2.x + line->p2.y - 160;
}

