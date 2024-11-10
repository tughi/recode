#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct String;

struct String {
    uint8_t *data;
    uintmax_t length;
};

int32_t main();

#line 1 "tests/08__string/001__local_variable/test.code"
int32_t main() {
#line 2 "tests/08__string/001__local_variable/test.code"
    struct String string;
#line 3 "tests/08__string/001__local_variable/test.code"
    return 0;
}

