#include "test.h"

#line 9 "tests/07__trait/003__call_trait_method/test.code"
int32_t ptest_Square__area(struct test_Square *self) {
#line 10 "tests/07__trait/003__call_trait_method/test.code"
    return self->side * self->side;
}

#line 17 "tests/07__trait/003__call_trait_method/test.code"
int32_t ptest_Circle__area(struct test_Circle *self) {
#line 18 "tests/07__trait/003__call_trait_method/test.code"
    return 312 * self->radius * self->radius / 100;
}

#line 21 "tests/07__trait/003__call_trait_method/test.code"
int32_t test__main() {
#line 22 "tests/07__trait/003__call_trait_method/test.code"
    struct test_Square square = (struct test_Square){.side = 10};
#line 23 "tests/07__trait/003__call_trait_method/test.code"
    struct test_Shape square_shape = (struct test_Shape){.self = &square, .area = ((int32_t (*)(void *self)) ptest_Square__area)};
#line 24 "tests/07__trait/003__call_trait_method/test.code"
    struct test_Circle circle = (struct test_Circle){.radius = 10};
#line 25 "tests/07__trait/003__call_trait_method/test.code"
    struct test_Shape circle_shape = (struct test_Shape){.self = &circle, .area = ((int32_t (*)(void *self)) ptest_Circle__area)};
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

int32_t main(int argc, const char **argv) {
    return test__main();
}

