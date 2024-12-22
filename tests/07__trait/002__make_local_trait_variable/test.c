#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct Dog;

struct Animal;

struct Dog {
    int32_t age;
};

struct Animal {
    void *self;
    int32_t (*legs)(void *self);
};

int32_t test__pDog__legs(struct Dog *self);

int32_t test__main();

int32_t main(int argc, const char **argv) {
    return test__main();
}

#line 7 "tests/07__trait/002__make_local_trait_variable/test.code"
int32_t test__pDog__legs(struct Dog *self) {
#line 8 "tests/07__trait/002__make_local_trait_variable/test.code"
    return 4;
}

#line 15 "tests/07__trait/002__make_local_trait_variable/test.code"
int32_t test__main() {
#line 16 "tests/07__trait/002__make_local_trait_variable/test.code"
    struct Dog dog = (struct Dog){.age = 10};
#line 17 "tests/07__trait/002__make_local_trait_variable/test.code"
    struct Animal animal = (struct Animal){.self = &dog, .legs = ((int32_t (*)(void *self)) test__pDog__legs)};
#line 18 "tests/07__trait/002__make_local_trait_variable/test.code"
    return 0;
}

