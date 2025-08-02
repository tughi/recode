#include "test.h"

#line 6 "tests/04__struct/009__struct_reference_argument/test.code"
int32_t test__main() {
#line 7 "tests/04__struct/009__struct_reference_argument/test.code"
    struct test_Point point;
#line 7 "tests/04__struct/009__struct_reference_argument/test.code"
    {
#line 7 "tests/04__struct/009__struct_reference_argument/test.code"
        int32_t __001__ = 16;
#line 7 "tests/04__struct/009__struct_reference_argument/test.code"
        int32_t __002__ = 32;
#line 7 "tests/04__struct/009__struct_reference_argument/test.code"
        point = (struct test_Point){.x = __001__, .y = __002__};
    }
#line 8 "tests/04__struct/009__struct_reference_argument/test.code"
    {
#line 8 "tests/04__struct/009__struct_reference_argument/test.code"
        struct test_Point *__001__ = &point;
#line 8 "tests/04__struct/009__struct_reference_argument/test.code"
        return test__get_y(__001__) - 32;
    }
}

#line 11 "tests/04__struct/009__struct_reference_argument/test.code"
int32_t test__get_y(struct test_Point *point) {
#line 12 "tests/04__struct/009__struct_reference_argument/test.code"
    return point->y;
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

