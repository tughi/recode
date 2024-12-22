#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct Shape;

struct Square;

struct Circle;

struct Shape {
    void *self;
    int32_t (*area)(void *self);
};

struct Square {
    int32_t side;
};

struct Circle {
    int32_t radius;
};

struct Shape *__alloc_Shape_value(struct Shape value);

struct Square *__alloc_Square_value(struct Square value);

struct Circle *__alloc_Circle_value(struct Circle value);

int32_t test__pSquare__area(struct Square *self);

int32_t test__pCircle__area(struct Circle *self);

int32_t test__main();

void *malloc(uint64_t size);

int32_t main(int argc, const char **argv) {
    return test__main();
}

struct Shape *__alloc_Shape_value(struct Shape value) {
    struct Shape *result = (struct Shape *)malloc(sizeof(struct Shape));
    *result = value;
    return result;
}

struct Square *__alloc_Square_value(struct Square value) {
    struct Square *result = (struct Square *)malloc(sizeof(struct Square));
    *result = value;
    return result;
}

struct Circle *__alloc_Circle_value(struct Circle value) {
    struct Circle *result = (struct Circle *)malloc(sizeof(struct Circle));
    *result = value;
    return result;
}

#line 11 "tests/07__trait/004__make_heap_trait_variable/test.code"
int32_t test__pSquare__area(struct Square *self) {
#line 12 "tests/07__trait/004__make_heap_trait_variable/test.code"
    return self->side * self->side;
}

#line 19 "tests/07__trait/004__make_heap_trait_variable/test.code"
int32_t test__pCircle__area(struct Circle *self) {
#line 20 "tests/07__trait/004__make_heap_trait_variable/test.code"
    return 312 * self->radius * self->radius / 100;
}

#line 23 "tests/07__trait/004__make_heap_trait_variable/test.code"
int32_t test__main() {
#line 24 "tests/07__trait/004__make_heap_trait_variable/test.code"
    struct Square *square = __alloc_Square_value((struct Square){.side = 10});
#line 25 "tests/07__trait/004__make_heap_trait_variable/test.code"
    struct Shape *square_shape = __alloc_Shape_value((struct Shape){.self = square, .area = ((int32_t (*)(void *self)) test__pSquare__area)});
#line 26 "tests/07__trait/004__make_heap_trait_variable/test.code"
    struct Circle *circle = __alloc_Circle_value((struct Circle){.radius = 10});
#line 27 "tests/07__trait/004__make_heap_trait_variable/test.code"
    struct Shape *circle_shape = __alloc_Shape_value((struct Shape){.self = circle, .area = ((int32_t (*)(void *self)) test__pCircle__area)});
#line 29 "tests/07__trait/004__make_heap_trait_variable/test.code"
    if (square_shape->area(square_shape->self) != 100) {
#line 30 "tests/07__trait/004__make_heap_trait_variable/test.code"
        return 1;
    }
#line 33 "tests/07__trait/004__make_heap_trait_variable/test.code"
    if (circle_shape->area(circle_shape->self) != 312) {
#line 34 "tests/07__trait/004__make_heap_trait_variable/test.code"
        return 2;
    }
#line 37 "tests/07__trait/004__make_heap_trait_variable/test.code"
    return 0;
}

