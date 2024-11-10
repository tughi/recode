#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

struct String;

struct String {
    uint8_t *data;
    uintmax_t length;
};

int32_t main();

#line 1 "tests/08__string/002__init_variable/test.code"
int32_t main() {
#line 2 "tests/08__string/002__init_variable/test.code"
    struct String empty = (struct String){.data = 0, .length = 0};
#line 3 "tests/08__string/002__init_variable/test.code"
    struct String quote = (struct String){.data = "Answer to the Ultimate Question of Life, the Universe, and Everything", .length = 69};
#line 4 "tests/08__string/002__init_variable/test.code"
    return 0;
}

