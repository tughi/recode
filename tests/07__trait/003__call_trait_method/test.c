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

int32_t pSquare__area(struct Square *self);

int32_t pCircle__area(struct Circle *self);

int32_t main();

#line 8 "tests/07__trait/003__call_trait_method/test.code"
int32_t pSquare__area(struct Square *self) {
#line 9 "tests/07__trait/003__call_trait_method/test.code"
    return self->side * self->side;
}

#line 16 "tests/07__trait/003__call_trait_method/test.code"
int32_t pCircle__area(struct Circle *self) {
#line 17 "tests/07__trait/003__call_trait_method/test.code"
    return 312 * self->radius * self->radius / 100;
}

#line 21 "tests/07__trait/003__call_trait_method/test.code"
int32_t main() {
#line 22 "tests/07__trait/003__call_trait_method/test.code"
    struct Square square = (struct Square){.side = 10};
#line 23 "tests/07__trait/003__call_trait_method/test.code"
    struct Shape square_shape = (struct Shape){.self = &square, .area = (int32_t (*)(void *self)) pSquare__area};
#line 24 "tests/07__trait/003__call_trait_method/test.code"
    struct Circle circle = (struct Circle){.radius = 10};
#line 25 "tests/07__trait/003__call_trait_method/test.code"
    struct Shape circle_shape = (struct Shape){.self = &circle, .area = (int32_t (*)(void *self)) pCircle__area};
#line 27 "tests/07__trait/003__call_trait_method/test.code"
    if (square_shape.area(square_shape.self) != 100) {
#line 28 "tests/07__trait/003__call_trait_method/test.code"
        return 1;
    }
#line 31 "tests/07__trait/003__call_trait_method/test.code"
    if (circle_shape.area(circle_shape.self) != 312) {
#line 32 "tests/07__trait/003__call_trait_method/test.code"
        return 2;
    }
#line 35 "tests/07__trait/003__call_trait_method/test.code"
    return 0;
}

