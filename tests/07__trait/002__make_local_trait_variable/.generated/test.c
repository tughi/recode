#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

#include "test.h"

#line 5 "tests/07__trait/002__make_local_trait_variable/test.code"
int32_t test__ptest__Dog__legs(struct test__Dog *self) {
#line 6 "tests/07__trait/002__make_local_trait_variable/test.code"
    return 4;
}

#line 13 "tests/07__trait/002__make_local_trait_variable/test.code"
int32_t test__main() {
#line 14 "tests/07__trait/002__make_local_trait_variable/test.code"
    struct test__Dog dog = (struct test__Dog){.age = 10};
#line 15 "tests/07__trait/002__make_local_trait_variable/test.code"
    struct test__Animal animal = (struct test__Animal){.self = &dog, .legs = ((int32_t (*)(void *self)) test__ptest__Dog__legs)};
#line 16 "tests/07__trait/002__make_local_trait_variable/test.code"
    return 0;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

