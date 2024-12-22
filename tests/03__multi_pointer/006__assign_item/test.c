#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t test__main();

void *malloc(uint64_t size);

int32_t main(int argc, const char **argv) {
    return test__main();
}

#line 3 "tests/03__multi_pointer/006__assign_item/test.code"
int32_t test__main() {
#line 4 "tests/03__multi_pointer/006__assign_item/test.code"
    int32_t *array = ((int32_t *) malloc(32u));
#line 5 "tests/03__multi_pointer/006__assign_item/test.code"
    array[3] = 42;
#line 6 "tests/03__multi_pointer/006__assign_item/test.code"
    return array[3] - 42;
}

