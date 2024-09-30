#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t main(int32_t argc, uint8_t **argv);

#line 1 "tests/03__unchecked_array/003__access_first_item/test.code"
int32_t main(int32_t argc, uint8_t **argv) {
#line 2 "tests/03__unchecked_array/003__access_first_item/test.code"
    uint8_t *arg = argv[0];
#line 3 "tests/03__unchecked_array/003__access_first_item/test.code"
    uint8_t ch = arg[0];
#line 4 "tests/03__unchecked_array/003__access_first_item/test.code"
    if (ch != 'b') {
#line 5 "tests/03__unchecked_array/003__access_first_item/test.code"
        return 1;
    }
#line 7 "tests/03__unchecked_array/003__access_first_item/test.code"
    return 0;
}

