#include "test.h"

void *malloc(uintmax_t size);

#line 9 "tests/07__trait/004__make_heap_trait_variable/test.code"
int32_t ptest_Square__area(struct test_Square *self) {
#line 10 "tests/07__trait/004__make_heap_trait_variable/test.code"
    {
#line 10 "tests/07__trait/004__make_heap_trait_variable/test.code"
        int32_t __001__ = self->side * self->side;
#line 10 "tests/07__trait/004__make_heap_trait_variable/test.code"
        return __001__;
#line 10 "tests/07__trait/004__make_heap_trait_variable/test.code"
    }
#line 11 "tests/07__trait/004__make_heap_trait_variable/test.code"
}

#line 17 "tests/07__trait/004__make_heap_trait_variable/test.code"
int32_t ptest_Circle__area(struct test_Circle *self) {
#line 18 "tests/07__trait/004__make_heap_trait_variable/test.code"
    {
#line 18 "tests/07__trait/004__make_heap_trait_variable/test.code"
        int32_t __001__ = 312 * self->radius * self->radius / 100;
#line 18 "tests/07__trait/004__make_heap_trait_variable/test.code"
        return __001__;
#line 18 "tests/07__trait/004__make_heap_trait_variable/test.code"
    }
#line 19 "tests/07__trait/004__make_heap_trait_variable/test.code"
}

#line 21 "tests/07__trait/004__make_heap_trait_variable/test.code"
int32_t test__main() {
#line 22 "tests/07__trait/004__make_heap_trait_variable/test.code"
    struct test_Square *square;
#line 22 "tests/07__trait/004__make_heap_trait_variable/test.code"
    {
#line 22 "tests/07__trait/004__make_heap_trait_variable/test.code"
        struct test_Square *__001__ = (struct test_Square *)malloc(sizeof(struct test_Square));
#line 22 "tests/07__trait/004__make_heap_trait_variable/test.code"
        *__001__ = (struct test_Square){.side = 10};
#line 22 "tests/07__trait/004__make_heap_trait_variable/test.code"
        square = __001__;
#line 22 "tests/07__trait/004__make_heap_trait_variable/test.code"
    }
#line 23 "tests/07__trait/004__make_heap_trait_variable/test.code"
    struct test_Shape *square_shape;
#line 23 "tests/07__trait/004__make_heap_trait_variable/test.code"
    {
#line 23 "tests/07__trait/004__make_heap_trait_variable/test.code"
        struct test_Shape *__002__ = (struct test_Shape *)malloc(sizeof(struct test_Shape));
#line 23 "tests/07__trait/004__make_heap_trait_variable/test.code"
        *__002__ = (struct test_Shape){.self = square, .area = ((int32_t (*)(void *self)) ptest_Square__area)};
#line 23 "tests/07__trait/004__make_heap_trait_variable/test.code"
        square_shape = __002__;
#line 23 "tests/07__trait/004__make_heap_trait_variable/test.code"
    }
#line 24 "tests/07__trait/004__make_heap_trait_variable/test.code"
    struct test_Circle *circle;
#line 24 "tests/07__trait/004__make_heap_trait_variable/test.code"
    {
#line 24 "tests/07__trait/004__make_heap_trait_variable/test.code"
        struct test_Circle *__003__ = (struct test_Circle *)malloc(sizeof(struct test_Circle));
#line 24 "tests/07__trait/004__make_heap_trait_variable/test.code"
        *__003__ = (struct test_Circle){.radius = 10};
#line 24 "tests/07__trait/004__make_heap_trait_variable/test.code"
        circle = __003__;
#line 24 "tests/07__trait/004__make_heap_trait_variable/test.code"
    }
#line 25 "tests/07__trait/004__make_heap_trait_variable/test.code"
    struct test_Shape *circle_shape;
#line 25 "tests/07__trait/004__make_heap_trait_variable/test.code"
    {
#line 25 "tests/07__trait/004__make_heap_trait_variable/test.code"
        struct test_Shape *__004__ = (struct test_Shape *)malloc(sizeof(struct test_Shape));
#line 25 "tests/07__trait/004__make_heap_trait_variable/test.code"
        *__004__ = (struct test_Shape){.self = circle, .area = ((int32_t (*)(void *self)) ptest_Circle__area)};
#line 25 "tests/07__trait/004__make_heap_trait_variable/test.code"
        circle_shape = __004__;
#line 25 "tests/07__trait/004__make_heap_trait_variable/test.code"
    }
#line 27 "tests/07__trait/004__make_heap_trait_variable/test.code"
    if (square_shape->area(square_shape->self) != 100) {
#line 28 "tests/07__trait/004__make_heap_trait_variable/test.code"
        {
#line 28 "tests/07__trait/004__make_heap_trait_variable/test.code"
            int32_t __005__ = 1;
#line 28 "tests/07__trait/004__make_heap_trait_variable/test.code"
            return __005__;
#line 28 "tests/07__trait/004__make_heap_trait_variable/test.code"
        }
#line 29 "tests/07__trait/004__make_heap_trait_variable/test.code"
    }
#line 31 "tests/07__trait/004__make_heap_trait_variable/test.code"
    if (circle_shape->area(circle_shape->self) != 312) {
#line 32 "tests/07__trait/004__make_heap_trait_variable/test.code"
        {
#line 32 "tests/07__trait/004__make_heap_trait_variable/test.code"
            int32_t __006__ = 2;
#line 32 "tests/07__trait/004__make_heap_trait_variable/test.code"
            return __006__;
#line 32 "tests/07__trait/004__make_heap_trait_variable/test.code"
        }
#line 33 "tests/07__trait/004__make_heap_trait_variable/test.code"
    }
#line 35 "tests/07__trait/004__make_heap_trait_variable/test.code"
    {
#line 35 "tests/07__trait/004__make_heap_trait_variable/test.code"
        int32_t __007__ = 0;
#line 35 "tests/07__trait/004__make_heap_trait_variable/test.code"
        return __007__;
#line 35 "tests/07__trait/004__make_heap_trait_variable/test.code"
    }
#line 36 "tests/07__trait/004__make_heap_trait_variable/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

