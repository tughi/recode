#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t test__main(int32_t argc, uint8_t **argv);

int32_t main(int argc, const char **argv) {
    return test__main(argc, (uint8_t **)argv);
}

#line 3 "tests/03__multi_pointer/005__convert_any/test.code"
int32_t test__main(int32_t argc, uint8_t **argv) {
#line 4 "tests/03__multi_pointer/005__convert_any/test.code"
    void *any = ((void *) argv[0]);
#line 5 "tests/03__multi_pointer/005__convert_any/test.code"
    uint8_t *name = ((uint8_t *) any);
#line 6 "tests/03__multi_pointer/005__convert_any/test.code"
    if (name[0] != 'b') {
#line 7 "tests/03__multi_pointer/005__convert_any/test.code"
        return 1;
    }
#line 9 "tests/03__multi_pointer/005__convert_any/test.code"
    return 0;
}

