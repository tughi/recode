#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

#include "test.h"

struct test__Shape *__alloc_test__Shape_value(struct test__Shape value) {
    struct test__Shape *result = (struct test__Shape *)malloc(sizeof(struct test__Shape));
    *result = value;
    return result;
}

struct test__Square *__alloc_test__Square_value(struct test__Square value) {
    struct test__Square *result = (struct test__Square *)malloc(sizeof(struct test__Square));
    *result = value;
    return result;
}

struct test__Circle *__alloc_test__Circle_value(struct test__Circle value) {
    struct test__Circle *result = (struct test__Circle *)malloc(sizeof(struct test__Circle));
    *result = value;
    return result;
}

#line 9 "tests/07__trait/004__make_heap_trait_variable/test.code"
int32_t test__ptest__Square__area(struct test__Square *self) {
#line 10 "tests/07__trait/004__make_heap_trait_variable/test.code"
    return self->side * self->side;
}

#line 17 "tests/07__trait/004__make_heap_trait_variable/test.code"
int32_t test__ptest__Circle__area(struct test__Circle *self) {
#line 18 "tests/07__trait/004__make_heap_trait_variable/test.code"
    return 312 * self->radius * self->radius / 100;
}

#line 21 "tests/07__trait/004__make_heap_trait_variable/test.code"
int32_t test__main() {
#line 22 "tests/07__trait/004__make_heap_trait_variable/test.code"
    struct test__Square *square = __alloc_test__Square_value((struct test__Square){.side = 10});
#line 23 "tests/07__trait/004__make_heap_trait_variable/test.code"
    struct test__Shape *square_shape = __alloc_test__Shape_value((struct test__Shape){.self = square, .area = ((int32_t (*)(void *self)) test__ptest__Square__area)});
#line 24 "tests/07__trait/004__make_heap_trait_variable/test.code"
    struct test__Circle *circle = __alloc_test__Circle_value((struct test__Circle){.radius = 10});
#line 25 "tests/07__trait/004__make_heap_trait_variable/test.code"
    struct test__Shape *circle_shape = __alloc_test__Shape_value((struct test__Shape){.self = circle, .area = ((int32_t (*)(void *self)) test__ptest__Circle__area)});
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

