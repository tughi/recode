#include "test.h"

#line 5 "tests/07__trait/002__make_local_trait_variable/test.code"
int32_t ptest_Dog__legs(struct test_Dog *self) {
#line 6 "tests/07__trait/002__make_local_trait_variable/test.code"
    return 4;
}

#line 13 "tests/07__trait/002__make_local_trait_variable/test.code"
int32_t test__main() {
#line 14 "tests/07__trait/002__make_local_trait_variable/test.code"
    struct test_Dog dog;
#line 14 "tests/07__trait/002__make_local_trait_variable/test.code"
    {
#line 14 "tests/07__trait/002__make_local_trait_variable/test.code"
        int32_t __001__ = 10;
#line 14 "tests/07__trait/002__make_local_trait_variable/test.code"
        dog = (struct test_Dog){.age = __001__};
    }
#line 15 "tests/07__trait/002__make_local_trait_variable/test.code"
    struct test_Animal animal;
#line 15 "tests/07__trait/002__make_local_trait_variable/test.code"
    {
#line 15 "tests/07__trait/002__make_local_trait_variable/test.code"
        void *__001__ = &dog;
#line 15 "tests/07__trait/002__make_local_trait_variable/test.code"
        int32_t (*__002__)(void *self) = ((int32_t (*)(void *self)) ptest_Dog__legs);
#line 15 "tests/07__trait/002__make_local_trait_variable/test.code"
        animal = (struct test_Animal){.self = __001__, .legs = __002__};
    }
#line 16 "tests/07__trait/002__make_local_trait_variable/test.code"
    return 0;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

