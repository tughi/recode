#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t d_u8_b__length(uint8_t *self);

int32_t main(int32_t argc, uint8_t **argv);

#line 1 "tests/05__extensions/004__unchecked_array_extension/test.code"
int32_t d_u8_b__length(uint8_t *self) {
#line 2 "tests/05__extensions/004__unchecked_array_extension/test.code"
    int32_t length = 0;
#line 3 "tests/05__extensions/004__unchecked_array_extension/test.code"
    while (self[length] != 0) {
#line 4 "tests/05__extensions/004__unchecked_array_extension/test.code"
        length = length + 1;
    }
#line 6 "tests/05__extensions/004__unchecked_array_extension/test.code"
    return length;
}

#line 9 "tests/05__extensions/004__unchecked_array_extension/test.code"
int32_t main(int32_t argc, uint8_t **argv) {
#line 10 "tests/05__extensions/004__unchecked_array_extension/test.code"
    if (argc != 2) {
#line 11 "tests/05__extensions/004__unchecked_array_extension/test.code"
        return 1;
    }
#line 13 "tests/05__extensions/004__unchecked_array_extension/test.code"
    if (d_u8_b__length(argv[1]) != 4) {
#line 14 "tests/05__extensions/004__unchecked_array_extension/test.code"
        return 2;
    }
#line 16 "tests/05__extensions/004__unchecked_array_extension/test.code"
    return 0;
}

