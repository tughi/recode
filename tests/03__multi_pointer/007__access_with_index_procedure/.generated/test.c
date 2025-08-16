#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/03__multi_pointer/007__access_with_index_procedure/test.code"
int32_t test__main(int32_t argc, uint8_t **argv) {
#line 2 "tests/03__multi_pointer/007__access_with_index_procedure/test.code"
    if (argc < 2) {
#line 3 "tests/03__multi_pointer/007__access_with_index_procedure/test.code"
        return 1;
#line 4 "tests/03__multi_pointer/007__access_with_index_procedure/test.code"
    }
#line 5 "tests/03__multi_pointer/007__access_with_index_procedure/test.code"
    int32_t i = 1;
#line 6 "tests/03__multi_pointer/007__access_with_index_procedure/test.code"
    if (argv[test__index(i)][test__index(i)] != '0') {
#line 7 "tests/03__multi_pointer/007__access_with_index_procedure/test.code"
        return 2;
#line 8 "tests/03__multi_pointer/007__access_with_index_procedure/test.code"
    }
#line 9 "tests/03__multi_pointer/007__access_with_index_procedure/test.code"
    return 0;
#line 10 "tests/03__multi_pointer/007__access_with_index_procedure/test.code"
}

#line 12 "tests/03__multi_pointer/007__access_with_index_procedure/test.code"
int32_t test__index(int32_t value) {
#line 13 "tests/03__multi_pointer/007__access_with_index_procedure/test.code"
    return value;
#line 14 "tests/03__multi_pointer/007__access_with_index_procedure/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main(argc, (uint8_t **)argv);
}

