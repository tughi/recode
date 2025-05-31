#include "test.h"

struct test_Shape *__alloc__test_Shape__(struct test_Shape value) {
    struct test_Shape *result = (struct test_Shape *)malloc(sizeof(struct test_Shape));
    *result = value;
    return result;
}

struct test_Square *__alloc__test_Square__(struct test_Square value) {
    struct test_Square *result = (struct test_Square *)malloc(sizeof(struct test_Square));
    *result = value;
    return result;
}

struct test_Circle *__alloc__test_Circle__(struct test_Circle value) {
    struct test_Circle *result = (struct test_Circle *)malloc(sizeof(struct test_Circle));
    *result = value;
    return result;
}

#line 9 "tests/07__trait/004__make_heap_trait_variable/test.code"
int32_t ptest_Square__area(struct test_Square *self) {
#line 10 "tests/07__trait/004__make_heap_trait_variable/test.code"
    return self->side * self->side;
}

#line 17 "tests/07__trait/004__make_heap_trait_variable/test.code"
int32_t ptest_Circle__area(struct test_Circle *self) {
#line 18 "tests/07__trait/004__make_heap_trait_variable/test.code"
    return 312 * self->radius * self->radius / 100;
}

#line 21 "tests/07__trait/004__make_heap_trait_variable/test.code"
int32_t test__main() {
#line 22 "tests/07__trait/004__make_heap_trait_variable/test.code"
    struct test_Square *square = __alloc__test_Square__((struct test_Square){.side = 10});
#line 23 "tests/07__trait/004__make_heap_trait_variable/test.code"
    struct test_Shape *square_shape = __alloc__test_Shape__((struct test_Shape){.self = square, .area = ((int32_t (*)(void *self)) ptest_Square__area)});
#line 24 "tests/07__trait/004__make_heap_trait_variable/test.code"
    struct test_Circle *circle = __alloc__test_Circle__((struct test_Circle){.radius = 10});
#line 25 "tests/07__trait/004__make_heap_trait_variable/test.code"
    struct test_Shape *circle_shape = __alloc__test_Shape__((struct test_Shape){.self = circle, .area = ((int32_t (*)(void *self)) ptest_Circle__area)});
#line 27 "tests/07__trait/004__make_heap_trait_variable/test.code"
    if (square_shape->area(square_shape->self) != 100) {
#line 28 "tests/07__trait/004__make_heap_trait_variable/test.code"
        return 1;
    }
#line 31 "tests/07__trait/004__make_heap_trait_variable/test.code"
    if (circle_shape->area(circle_shape->self) != 312) {
#line 32 "tests/07__trait/004__make_heap_trait_variable/test.code"
        return 2;
    }
#line 35 "tests/07__trait/004__make_heap_trait_variable/test.code"
    return 0;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

