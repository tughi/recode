#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t main(int32_t argc, uint8_t (*(*argv)));

#line 1 "tests/03__unchecked_array/005__any/test.code"
int32_t main(int32_t argc, uint8_t (*(*argv))) {
#line 2 "tests/03__unchecked_array/005__any/test.code"
    void (*any) = (void (*)) argv[0];
#line 3 "tests/03__unchecked_array/005__any/test.code"
    uint8_t (*name) = (uint8_t (*)) any;
#line 4 "tests/03__unchecked_array/005__any/test.code"
    if (name[0] != 'b') {
#line 5 "tests/03__unchecked_array/005__any/test.code"
        return 1;
    }
#line 7 "tests/03__unchecked_array/005__any/test.code"
    return 0;
}

