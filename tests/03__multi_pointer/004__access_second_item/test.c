#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t main(int32_t argc, uint8_t **argv);

#line 1 "tests/03__multi_pointer/004__access_second_item/test.code"
int32_t main(int32_t argc, uint8_t **argv) {
#line 2 "tests/03__multi_pointer/004__access_second_item/test.code"
    if (argc < 2) {
#line 3 "tests/03__multi_pointer/004__access_second_item/test.code"
        return 1;
    }
#line 5 "tests/03__multi_pointer/004__access_second_item/test.code"
    if (argv[1][1] != '0') {
#line 6 "tests/03__multi_pointer/004__access_second_item/test.code"
        return 2;
    }
#line 8 "tests/03__multi_pointer/004__access_second_item/test.code"
    return 0;
}

