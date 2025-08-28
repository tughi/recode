#include "test.h"

void *malloc(uintmax_t size);

#line 14 "tests/15__struct_super/002__pointer_conversion/test.code"
int32_t test__main() {
#line 15 "tests/15__struct_super/002__pointer_conversion/test.code"
    struct test_Vehicle *my_vehicle;
#line 15 "tests/15__struct_super/002__pointer_conversion/test.code"
    {
#line 15 "tests/15__struct_super/002__pointer_conversion/test.code"
        struct test_Sports_Car *__001__ = (struct test_Sports_Car *)malloc(sizeof(struct test_Sports_Car));
#line 15 "tests/15__struct_super/002__pointer_conversion/test.code"
        *__001__ = (struct test_Sports_Car){.super = (struct test_Car){.super = (struct test_Vehicle){.wheels = 4}}, .turbo = true};
#line 15 "tests/15__struct_super/002__pointer_conversion/test.code"
        my_vehicle = ((struct test_Vehicle *) __001__);
#line 15 "tests/15__struct_super/002__pointer_conversion/test.code"
    }
#line 16 "tests/15__struct_super/002__pointer_conversion/test.code"
    {
#line 16 "tests/15__struct_super/002__pointer_conversion/test.code"
        int32_t __002__ = my_vehicle->wheels - 4;
#line 16 "tests/15__struct_super/002__pointer_conversion/test.code"
        return __002__;
#line 16 "tests/15__struct_super/002__pointer_conversion/test.code"
    }
#line 17 "tests/15__struct_super/002__pointer_conversion/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

