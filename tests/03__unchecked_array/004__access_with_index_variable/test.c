#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

int32_t main(int32_t argc, uint8_t (*(*argv)));

#line 1 "tests/03__unchecked_array/004__access_with_index_variable/test.code"
int32_t main(int32_t argc, uint8_t (*(*argv))) {
#line 2 "tests/03__unchecked_array/004__access_with_index_variable/test.code"
    int32_t i = 1;
#line 3 "tests/03__unchecked_array/004__access_with_index_variable/test.code"
    if (argv[i][i] != '0') {
#line 4 "tests/03__unchecked_array/004__access_with_index_variable/test.code"
        return 1;
    }
#line 6 "tests/03__unchecked_array/004__access_with_index_variable/test.code"
    return 0;
}

