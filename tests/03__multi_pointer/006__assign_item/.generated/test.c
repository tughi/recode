#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/03__multi_pointer/006__assign_item/test.code"
int32_t test__main() {
#line 2 "tests/03__multi_pointer/006__assign_item/test.code"
    int32_t *array = ((int32_t *) malloc(32u));
#line 3 "tests/03__multi_pointer/006__assign_item/test.code"
    array[3] = 42;
#line 4 "tests/03__multi_pointer/006__assign_item/test.code"
    {
#line 4 "tests/03__multi_pointer/006__assign_item/test.code"
        int32_t __001__ = array[3] - 42;
#line 4 "tests/03__multi_pointer/006__assign_item/test.code"
        return __001__;
#line 4 "tests/03__multi_pointer/006__assign_item/test.code"
    }
#line 5 "tests/03__multi_pointer/006__assign_item/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

