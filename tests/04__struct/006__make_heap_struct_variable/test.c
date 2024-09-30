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

struct Point *__make_Point_value(struct Point value);

struct Line *__make_Line_value(struct Line value);

int32_t main();

void *malloc(uint64_t size);

struct Point *__make_Point_value(struct Point value) {
    struct Point *result = (struct Point *)malloc(sizeof(struct Point));
    *result = value;
    return result;
}

struct Line *__make_Line_value(struct Line value) {
    struct Line *result = (struct Line *)malloc(sizeof(struct Line));
    *result = value;
    return result;
}

#line 11 "tests/04__struct/006__make_heap_struct_variable/test.code"
int32_t main() {
#line 12 "tests/04__struct/006__make_heap_struct_variable/test.code"
    struct Line *line = __make_Line_value((struct Line){.p1 = (struct Point){.x = 16, .y = 32}, .p2 = (struct Point){.x = 48, .y = 64}});
#line 16 "tests/04__struct/006__make_heap_struct_variable/test.code"
    return line->p1.x + line->p1.y + line->p2.x + line->p2.y - 160;
}

