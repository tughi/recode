#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t main();

void (*malloc(uint64_t size));

#line 1 "tests/03__unchecked_array/006__assign_item/test.code"
int32_t main() {
#line 2 "tests/03__unchecked_array/006__assign_item/test.code"
    int32_t (*array) = (int32_t (*)) malloc(32u);
#line 3 "tests/03__unchecked_array/006__assign_item/test.code"
    array[3] = 42;
#line 4 "tests/03__unchecked_array/006__assign_item/test.code"
    return array[3] - 42;
}

