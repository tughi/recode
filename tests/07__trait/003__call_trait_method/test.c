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

int32_t test__pSquare__area(struct Square *self);

int32_t test__pCircle__area(struct Circle *self);

int32_t test__main();

int32_t main(int argc, const char **argv) {
    return test__main();
}

#line 11 "tests/07__trait/003__call_trait_method/test.code"
int32_t test__pSquare__area(struct Square *self) {
#line 12 "tests/07__trait/003__call_trait_method/test.code"
    return self->side * self->side;
}

#line 19 "tests/07__trait/003__call_trait_method/test.code"
int32_t test__pCircle__area(struct Circle *self) {
#line 20 "tests/07__trait/003__call_trait_method/test.code"
    return 312 * self->radius * self->radius / 100;
}

#line 23 "tests/07__trait/003__call_trait_method/test.code"
int32_t test__main() {
#line 24 "tests/07__trait/003__call_trait_method/test.code"
    struct Square square = (struct Square){.side = 10};
#line 25 "tests/07__trait/003__call_trait_method/test.code"
    struct Shape square_shape = (struct Shape){.self = &square, .area = ((int32_t (*)(void *self)) test__pSquare__area)};
#line 26 "tests/07__trait/003__call_trait_method/test.code"
    struct Circle circle = (struct Circle){.radius = 10};
#line 27 "tests/07__trait/003__call_trait_method/test.code"
    struct Shape circle_shape = (struct Shape){.self = &circle, .area = ((int32_t (*)(void *self)) test__pCircle__area)};
#line 29 "tests/07__trait/003__call_trait_method/test.code"
    if (square_shape.area(square_shape.self) != 100) {
#line 30 "tests/07__trait/003__call_trait_method/test.code"
        return 1;
    }
#line 33 "tests/07__trait/003__call_trait_method/test.code"
    if (circle_shape.area(circle_shape.self) != 312) {
#line 34 "tests/07__trait/003__call_trait_method/test.code"
        return 2;
    }
#line 37 "tests/07__trait/003__call_trait_method/test.code"
    return 0;
}

