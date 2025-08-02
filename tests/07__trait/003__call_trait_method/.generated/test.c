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
    struct test_Square square;
#line 22 "tests/07__trait/003__call_trait_method/test.code"
    {
#line 22 "tests/07__trait/003__call_trait_method/test.code"
        int32_t __001__ = 10;
#line 22 "tests/07__trait/003__call_trait_method/test.code"
        square = (struct test_Square){.side = __001__};
    }
#line 23 "tests/07__trait/003__call_trait_method/test.code"
    struct test_Shape square_shape;
#line 23 "tests/07__trait/003__call_trait_method/test.code"
    {
#line 23 "tests/07__trait/003__call_trait_method/test.code"
        void *__001__ = &square;
#line 23 "tests/07__trait/003__call_trait_method/test.code"
        int32_t (*__002__)(void *self) = ((int32_t (*)(void *self)) ptest_Square__area);
#line 23 "tests/07__trait/003__call_trait_method/test.code"
        square_shape = (struct test_Shape){.self = __001__, .area = __002__};
    }
#line 24 "tests/07__trait/003__call_trait_method/test.code"
    struct test_Circle circle;
#line 24 "tests/07__trait/003__call_trait_method/test.code"
    {
#line 24 "tests/07__trait/003__call_trait_method/test.code"
        int32_t __001__ = 10;
#line 24 "tests/07__trait/003__call_trait_method/test.code"
        circle = (struct test_Circle){.radius = __001__};
    }
#line 25 "tests/07__trait/003__call_trait_method/test.code"
    struct test_Shape circle_shape;
#line 25 "tests/07__trait/003__call_trait_method/test.code"
    {
#line 25 "tests/07__trait/003__call_trait_method/test.code"
        void *__001__ = &circle;
#line 25 "tests/07__trait/003__call_trait_method/test.code"
        int32_t (*__002__)(void *self) = ((int32_t (*)(void *self)) ptest_Circle__area);
#line 25 "tests/07__trait/003__call_trait_method/test.code"
        circle_shape = (struct test_Shape){.self = __001__, .area = __002__};
    }
#line 27 "tests/07__trait/003__call_trait_method/test.code"
    {
#line 27 "tests/07__trait/003__call_trait_method/test.code"
        void *__001__ = square_shape.self;
#line 27 "tests/07__trait/003__call_trait_method/test.code"
        if (square_shape.area(__001__) != 100) {
#line 28 "tests/07__trait/003__call_trait_method/test.code"
            return 1;
        }
    }
#line 31 "tests/07__trait/003__call_trait_method/test.code"
    {
#line 31 "tests/07__trait/003__call_trait_method/test.code"
        void *__001__ = circle_shape.self;
#line 31 "tests/07__trait/003__call_trait_method/test.code"
        if (circle_shape.area(__001__) != 312) {
#line 32 "tests/07__trait/003__call_trait_method/test.code"
            return 2;
        }
    }
#line 35 "tests/07__trait/003__call_trait_method/test.code"
    return 0;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

