#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t test__d_u8_b__length(uint8_t *self);

int32_t test__main(int32_t argc, uint8_t **argv);

int32_t main(int argc, const char **argv) {
    return test__main(argc, (uint8_t **)argv);
}

#line 3 "tests/05__extensions/004__multi_pointer_extension/test.code"
int32_t test__d_u8_b__length(uint8_t *self) {
#line 4 "tests/05__extensions/004__multi_pointer_extension/test.code"
    int32_t length = 0;
#line 5 "tests/05__extensions/004__multi_pointer_extension/test.code"
    while (self[length] != 0) {
#line 6 "tests/05__extensions/004__multi_pointer_extension/test.code"
        length = length + 1;
    }
#line 8 "tests/05__extensions/004__multi_pointer_extension/test.code"
    return length;
}

#line 11 "tests/05__extensions/004__multi_pointer_extension/test.code"
int32_t test__main(int32_t argc, uint8_t **argv) {
#line 12 "tests/05__extensions/004__multi_pointer_extension/test.code"
    if (argc != 2) {
#line 13 "tests/05__extensions/004__multi_pointer_extension/test.code"
        return 1;
    }
#line 15 "tests/05__extensions/004__multi_pointer_extension/test.code"
    if (test__d_u8_b__length(argv[1]) != 4) {
#line 16 "tests/05__extensions/004__multi_pointer_extension/test.code"
        return 2;
    }
#line 18 "tests/05__extensions/004__multi_pointer_extension/test.code"
    return 0;
}

