#include "test.h"

void *malloc(uintmax_t size);

#line 1 "tests/08__string/002__init_variable/test.code"
int32_t test__main() {
#line 2 "tests/08__string/002__init_variable/test.code"
    struct String empty = (struct String){.data = 0, .length = 0};
#line 3 "tests/08__string/002__init_variable/test.code"
    struct String quote = (struct String){.data = "Answer to the Ultimate Question of Life, the Universe, and Everything", .length = 69};
#line 4 "tests/08__string/002__init_variable/test.code"
    return 0;
#line 5 "tests/08__string/002__init_variable/test.code"
}

int32_t main(int argc, const char **argv) {
    return test__main();
}

